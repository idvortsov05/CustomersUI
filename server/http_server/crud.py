from typing import Optional

from fastapi import HTTPException

from sqlalchemy.orm import Session, joinedload
import models # ДЛЯ ПРОГРАММЫ
import schemas # ДЛЯ ПРОГРАММЫ

# ДЛЯ ТЕСТОВ:
# from . import models
# from . import schemas

from datetime import datetime

def get_customer_by_email(db: Session, email: str):
    return db.query(models.Customer).filter(models.Customer.Email == email).first()

def create_customer(db: Session, customer: schemas.CustomerCreate):
    db_customer = models.Customer(
        Name=customer.name,
        Phone=customer.phone,
        ContactPerson=customer.contact_person,
        Address=customer.address,
        Email=customer.email,
        PasswordHash=customer.password
    )
    db.add(db_customer)
    db.commit()
    db.refresh(db_customer)
    return db_customer

def get_customer(db: Session, customer_id: int) -> schemas.Customer:
    db_customer = db.query(models.Customer).filter(models.Customer.CustomerID == customer_id).first()
    if not db_customer:
        return None
    return schemas.Customer.model_validate(db_customer)

def update_customer(db: Session, customer_id: int, customer_update: schemas.CustomerUpdate):
    db_customer = db.query(models.Customer).filter(models.Customer.CustomerID == customer_id).first()
    if not db_customer:
        return None

    if customer_update.name is not None:
        db_customer.Name = customer_update.name
    if customer_update.phone is not None:
        db_customer.Phone = customer_update.phone
    if customer_update.contact_person is not None:
        db_customer.ContactPerson = customer_update.contact_person
    if customer_update.address is not None:
        db_customer.Address = customer_update.address
    if customer_update.email is not None:
        db_customer.Email = customer_update.email

    db.commit()
    db.refresh(db_customer)
    return db_customer

def get_or_create_cart(db: Session, customer_id: int) -> models.Cart:
    cart = db.query(models.Cart).filter(models.Cart.CustomerID == customer_id).first()
    if not cart:
        cart = models.Cart(CustomerID=customer_id)
        db.add(cart)
        db.commit()
        db.refresh(cart)
    return cart

def calculate_discount(db: Session, total_items: int, total_price: float) -> Optional[models.Discount]:
    if total_items == 0 or total_price == 0.0:
        return None

    return (
        db.query(models.Discount)
        .filter(
            models.Discount.MinQuantity <= total_items,
            models.Discount.MaxQuantity >= total_items,
            models.Discount.MinTotalPrice <= total_price
        )
        .order_by(models.Discount.DiscountRate.desc())
        .first()
    )


def get_cart_items(db: Session, customer_id: int) -> schemas.CartItemsList:
    customer = db.query(models.Customer).filter(
        models.Customer.CustomerID == customer_id
    ).first()
    if not customer:
        raise HTTPException(status_code=404, detail="Customer not found")

    cart = (
        db.query(models.Cart)
        .filter(models.Cart.CustomerID == customer_id)
        .order_by(models.Cart.LastUpdated.desc().nullslast(), models.Cart.CreatedDate.desc())
        .first()
    )
    if not cart:
        raise HTTPException(status_code=404, detail="No cart found for this customer")

    items_query = (
        db.query(
            models.CartItem,
            models.Product.Name.label("ProductName"),
            models.Product.RetailPrice.label("Price"),
            models.Product.WholesalePrice.label("WholesalePrice")
        )
        .join(models.Product, models.Product.ProductID == models.CartItem.ProductID)
        .filter(models.CartItem.CartID == cart.CartID)
        .all()
    )

    cart_items = []
    total_items = 0
    total_price = 0.0
    wholesale_total = 0.0

    for cart_item, product_name, price, wholesale_price in items_query:
        quantity = cart_item.Quantity
        total_items += quantity
        total_price += quantity * price
        wholesale_total += quantity * wholesale_price

        cart_items.append(
            schemas.CartItem(
                id=cart_item.CartItemID,
                product_id=cart_item.ProductID,
                quantity=quantity,
                product_name=product_name,
                price=price,
                added_date=cart_item.AddedDate
            )
        )

    discount = calculate_discount(db, total_items, total_price)
    discount_rate = discount.DiscountRate if discount else 0.0
    discounted_price = round(total_price * (1 - discount_rate), 2)

    return schemas.CartItemsList(
        items=cart_items,
        total_items=total_items,
        total_price=round(total_price, 2),
        discounted_price=discounted_price,
        discount_rate=discount_rate,
        discount_id=discount.DiscountID if discount else None,
        cart_id=cart.CartID,
        customer_id=cart.CustomerID
    )

def add_to_cart(db: Session, customer_id: int, item: schemas.CartItemCreate) -> schemas.CartItem:
    product = db.query(models.Product).filter(models.Product.ProductID == item.product_id).first()
    if not product:
        raise HTTPException(status_code=404, detail="Product not found")

    cart = get_or_create_cart(db, customer_id)

    db_item = db.query(models.CartItem).filter(
        models.CartItem.CartID == cart.CartID,
        models.CartItem.ProductID == item.product_id
    ).first()

    if db_item:
        db_item.Quantity += item.quantity
    else:
        db_item = models.CartItem(
            CartID=cart.CartID,
            ProductID=item.product_id,
            Quantity=item.quantity
        )
        db.add(db_item)

    try:
        db.commit()
        db.refresh(db_item)
    except Exception as e:
        db.rollback()
        raise HTTPException(status_code=400, detail=str(e))

    return schemas.CartItem.model_validate({
        "CartItemID": db_item.CartItemID,
        "ProductID": db_item.ProductID,
        "Quantity": db_item.Quantity,
        "AddedDate": db_item.AddedDate,
        "ProductName": product.Name,
        "Price": product.RetailPrice
    })


def update_cart_item(db: Session, item_id: int, item_update: schemas.CartItemUpdate) -> schemas.CartItem:
    db_item = db.query(models.CartItem).filter(models.CartItem.CartItemID == item_id).first()
    if not db_item:
        return None

    db_item.Quantity = item_update.quantity
    db.commit()
    db.refresh(db_item)

    item_data = {
        "CartItemID": db_item.CartItemID,
        "ProductID": db_item.ProductID,
        "Quantity": db_item.Quantity,
        "AddedDate": db_item.AddedDate.isoformat() if db_item.AddedDate else None
    }

    return schemas.CartItem.model_validate(item_data)

def remove_from_cart(db: Session, item_id: int) -> bool:
    db_item = db.query(models.CartItem).filter(models.CartItem.CartItemID == item_id).first()
    if not db_item:
        return False

    db.delete(db_item)
    db.commit()
    return True

def clear_cart(db: Session, customer_id: int) -> bool:
    cart = get_or_create_cart(db, customer_id)
    db.query(models.CartItem).filter(models.CartItem.CartID == cart.CartID).delete()
    db.commit()
    return True

def create_order(db: Session, customer_id: int, order_data: schemas.TransactionCreate) -> schemas.TransactionResponse:
    try:
        with db.begin():
            customer = db.query(models.Customer).get(customer_id)
            if not customer:
                raise ValueError("Customer not found")
            cart = db.query(models.Cart).filter_by(CustomerID=customer_id).first()
            if not cart:
                raise ValueError("Cart not found")
            cart_items = db.query(models.CartItem).filter_by(CartID=cart.CartID).all()
            if not cart_items:
                raise ValueError("Cart is empty")
            total_quantity = sum(item.Quantity for item in cart_items)
            total_price = sum(
                item.Quantity * (item.product.WholesalePrice if order_data.is_wholesale else item.product.RetailPrice)
                for item in cart_items
            )
            discount = calculate_discount(db, total_quantity, total_price)
            discount_rate = discount.DiscountRate if discount else 0.0
            db_transaction = models.Transaction(
                CustomerID=customer_id,
                EmployeeID=order_data.employee_id,
                IsWholesale=order_data.is_wholesale,
                TransactionDate=datetime.utcnow()
            )
            db.add(db_transaction)
            db.flush()
            details_response = []
            final_total = 0.0
            for item in cart_items:
                product = item.product
                price = product.WholesalePrice if order_data.is_wholesale else product.RetailPrice
                item_total = price * item.Quantity * (1 - discount_rate)
                db_detail = models.TransactionDetail(TransactionID=db_transaction.TransactionID, ProductID=item.ProductID, Quantity=item.Quantity, Discount=discount_rate)
                db.add(db_detail)
                db.flush()
                details_response.append(schemas.TransactionDetailResponse(
                    id=db_detail.TransactionDetailID,
                    transaction_id=db_transaction.TransactionID,
                    product_id=item.ProductID,
                    quantity=item.Quantity,
                    discount=discount_rate,
                    product_name=product.Name,
                    current_price=price,
                    calculated_total=item_total
                ))
                final_total += item_total
            db.query(models.CartItem).filter_by(CartID=cart.CartID).delete()
            return schemas.TransactionResponse(
                id=db_transaction.TransactionID,
                customer_id=db_transaction.CustomerID,
                employee_id=db_transaction.EmployeeID,
                is_wholesale=db_transaction.IsWholesale,
                transaction_date=db_transaction.TransactionDate,
                total_amount=final_total,
                discount_amount=total_price * discount_rate,
                details=details_response
            )
    except Exception as e:
        db.rollback()
        raise ValueError(f"Order creation failed: {str(e)}")



def get_orders(db: Session, customer_id: int) -> schemas.TransactionsList:
    orders = db.query(models.Transaction) \
        .options(joinedload(models.Transaction.details)
                 .joinedload(models.TransactionDetail.product)) \
        .filter(models.Transaction.CustomerID == customer_id) \
        .order_by(models.Transaction.TransactionDate.desc()) \
        .all()

    transactions = []
    for order in orders:
        total = sum(
            detail.Quantity * (
                detail.product.WholesalePrice if order.IsWholesale
                else detail.product.RetailPrice
            ) * (1 - (detail.Discount or 0))
            for detail in order.details
        )

        transactions.append(schemas.TransactionResponse(
            id=order.TransactionID,
            customer_id=order.CustomerID,
            employee_id=order.EmployeeID,
            is_wholesale=order.IsWholesale,
            transaction_date=order.TransactionDate,
            total_amount=total,
            discount_amount=sum(
                detail.Quantity * (
                    detail.product.WholesalePrice if order.IsWholesale
                    else detail.product.RetailPrice
                ) * (detail.Discount or 0)
                for detail in order.details
            ),
            details=[
                schemas.TransactionDetailResponse(
                    id=detail.TransactionDetailID,
                    transaction_id=detail.TransactionID,
                    product_id=detail.ProductID,
                    quantity=detail.Quantity,
                    discount=detail.Discount,
                    product_name=detail.product.Name,
                    current_price=(
                        detail.product.WholesalePrice if order.IsWholesale
                        else detail.product.RetailPrice
                    ),
                    calculated_total=(
                            detail.Quantity * (
                        detail.product.WholesalePrice if order.IsWholesale
                        else detail.product.RetailPrice
                    ) * (1 - (detail.Discount or 0))
                    )
                )
                for detail in order.details
            ]
        ))

    return schemas.TransactionsList(transactions=transactions)


def get_order_details(db: Session, order_id: int) -> schemas.TransactionResponse:
    order = db.query(models.Transaction).get(order_id)
    if not order:
        return None

    details = db.query(models.TransactionDetail).filter(
        models.TransactionDetail.TransactionID == order_id
    ).all()

    order_dict ={
        "TransactionID": order.TransactionID,
        "CustomerID": order.CustomerID,
        "EmployeeID": order.EmployeeID,
        "IsWholesale": order.IsWholesale,
        "TransactionDate": order.TransactionDate
    }

    details_list = []
    for detail in details:
        details_list.append({
            "TransactionDetailID": detail.TransactionDetailID,
            "ProductID": detail.ProductID,
            "Quantity": detail.Quantity,
            "Discount": detail.Discount
        })

    total_amount = sum(
        detail.Quantity * (detail.product.WholesalePrice if order.IsWholesale else detail.product.RetailPrice)
        for detail in details
    )

    return schemas.TransactionDetails(
        **order_dict,
        details=details_list,
        total_amount=total_amount
    )

def get_products(
    db: Session,
    price_lt: float = None,
    price_gt: float = None,
    name: str = None,
    sort_by: str = None
) -> schemas.ProductsList:
    query = db.query(models.Product)

    if price_lt is not None:
        query = query.filter(models.Product.RetailPrice < price_lt)
    if price_gt is not None:
        query = query.filter(models.Product.RetailPrice > price_gt)
    if name:
        query = query.filter(models.Product.Name.ilike(f"%{name}%"))

    sort_options = {
        "retail_price_asc": models.Product.RetailPrice.asc(),
        "retail_price_desc": models.Product.RetailPrice.desc(),
        "wholesale_price_asc": models.Product.WholesalePrice.asc(),
        "wholesale_price_desc": models.Product.WholesalePrice.desc(),
        "name_asc": models.Product.Name.asc(),
        "name_desc": models.Product.Name.desc(),
        "description_asc": models.Product.Description.asc(),
        "description_desc": models.Product.Description.desc(),
        "id_asc": models.Product.ProductID.asc(),
        "id_desc": models.Product.ProductID.desc()
    }
    if sort_by in sort_options:
        query = query.order_by(sort_options[sort_by])

    print("SQL Query:", str(query.statement.compile(compile_kwargs={"literal_binds": True})))

    products = query.all()
    return schemas.ProductsList(products=products)

def search_products(db: Session, query: str) -> schemas.ProductsList:
    try:
        query_num = float(query)
        products = db.query(models.Product).filter(
            (models.Product.ProductID == int(query_num)) |
            (models.Product.WholesalePrice == query_num) |
            (models.Product.RetailPrice == query_num) |
            (models.Product.Name.ilike(f"%{query}%")) |
            (models.Product.Description.ilike(f"%{query}%"))
        ).all()
    except ValueError:
        products = db.query(models.Product).filter(
            (models.Product.Name.ilike(f"%{query}%")) |
            (models.Product.Description.ilike(f"%{query}%"))
        ).all()

    return schemas.ProductsList(products=products)


def get_product(db: Session, product_id: int) -> schemas.Product:
    product = db.query(models.Product).filter(models.Product.ProductID == product_id).first()
    if not product:
        return None
    return schemas.Product.model_validate(product)


