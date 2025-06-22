import crud, schemas
from database import get_db
from config.config_server import get_config
import models
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session

CONFIG_FILE_PATH = 'server/http_server/config/config.ini'

config = get_config(CONFIG_FILE_PATH)
router = APIRouter()

username = config["auth"]["username"]
password_hash = config["auth"]["password_hash"]

@router.post("/register", response_model=schemas.CustomerResponse)
def register(customer: schemas.CustomerCreate, db: Session = Depends(get_db)):
    db_customer = crud.get_customer_by_email(db, customer.email)
    if db_customer:
        raise HTTPException(
            status_code=400,
            detail="Email already registered"
        )
    return crud.create_customer(db, customer)


@router.post("/login", response_model=schemas.CustomerResponse)
def login(credentials: schemas.Credentials, db: Session = Depends(get_db)):
    customer = crud.get_customer_by_email(db, credentials.email)
    if not customer or customer.PasswordHash != credentials.password:
        raise HTTPException(status_code=401, detail="Incorrect credentials")
    return customer

@router.get("/customers/{customer_id}", response_model=schemas.CustomerResponse)
def get_customer(customer_id: int, db: Session = Depends(get_db)):
    db_customer = db.query(models.Customer).filter(models.Customer.CustomerID == customer_id).first()
    if not db_customer:
        raise HTTPException(status_code=404, detail="Customer not found")
    return db_customer

@router.put("/customers/{customer_id}", response_model=schemas.CustomerResponse)
def update_customer(
    customer_id: int,
    customer_update: schemas.CustomerUpdate,
    db: Session = Depends(get_db)
):
    updated_customer = crud.update_customer(db, customer_id, customer_update)
    if not updated_customer:
        raise HTTPException(status_code=404, detail="Customer not found")
    return updated_customer

@router.get("/customers/{customer_id}/cart", response_model=schemas.CartItemsList)
def get_cart(customer_id: int, db: Session = Depends(get_db)):
    return crud.get_cart_items(db, customer_id)

@router.post("/customers/{customer_id}/cart/items", response_model=schemas.CartItem)
def add_cart_item(
    customer_id: int,
    item: schemas.CartItemCreate,
    db: Session = Depends(get_db)
):
    try:
        return crud.add_to_cart(db, customer_id, item)
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@router.post("/customers/{customer_id}/orders", response_model=schemas.TransactionResponse)
def create_order(customer_id: int, order_data: schemas.TransactionCreate, db: Session = Depends(get_db)):
    try:
        return crud.create_order(db, customer_id, order_data)
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))

@router.delete("/cart/items/{item_id}")
def remove_cart_item(item_id: int, db: Session = Depends(get_db)):
    if not crud.remove_from_cart(db, item_id):
        raise HTTPException(status_code=404, detail="Cart item not found")
    return {"message": "Item removed from cart"}

@router.delete("/customers/{customer_id}/cart")
def clear_cart(customer_id: int, db: Session = Depends(get_db)):
    if not crud.clear_cart(db, customer_id):
        raise HTTPException(status_code=404, detail="Cart not found")
    return {"message": "Cart cleared"}

@router.post("/customers/{customer_id}/orders", response_model=schemas.TransactionResponse)
def create_order(
    customer_id: int,
    order_data: schemas.TransactionCreate,
    db: Session = Depends(get_db)
):
    try:
        return crud.create_order(db, customer_id, order_data)
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))

@router.get("/customers/{customer_id}/orders", response_model=schemas.TransactionsList)
def get_orders(customer_id: int, db: Session = Depends(get_db)):
    return crud.get_orders(db, customer_id)

@router.get("/orders/{order_id}", response_model=schemas.TransactionDetailResponse)
def get_order_details(order_id: int, db: Session = Depends(get_db)):
    order_details = crud.get_order_details(db, order_id)
    if not order_details:
        raise HTTPException(status_code=404, detail="Order not found")
    return order_details

@router.get("/products", response_model=schemas.ProductsList)
def get_products(
    price_lt: float = None,
    price_gt: float = None,
    name: str = None,
    sort_by: str = None,
    db: Session = Depends(get_db)
):
    return crud.get_products(db, price_lt, price_gt, name, sort_by)

@router.get("/products/search", response_model=schemas.ProductsList)
def search_products(query: str, db: Session = Depends(get_db)):
    if not query or len(query.strip()) < 2:
        raise HTTPException(
            status_code=400,
            detail="Search query must be at least 2 characters long"
        )
    return crud.search_products(db, query)

@router.get("/products/{product_id}", response_model=schemas.Product)
def get_product(product_id: int, db: Session = Depends(get_db)):
    product = crud.get_product(db, product_id)
    if not product:
        raise HTTPException(status_code=404, detail="Product not found")
    return product


