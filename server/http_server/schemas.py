from datetime import datetime, date
from typing import List, Optional
from pydantic import BaseModel, Field, ConfigDict, model_validator, EmailStr
from typing import Optional

class Credentials(BaseModel):
    email: EmailStr
    password: str

# Customers
class CustomerBase(BaseModel):
    name: str = Field(..., max_length=100)
    phone: str = Field(..., max_length=20)
    contact_person: str = Field(..., max_length=100)
    address: str = Field(..., max_length=200)
    email: EmailStr

class CustomerCreate(CustomerBase):
    password: str = Field(..., min_length=64, max_length=64, pattern=r"^[a-f0-9]{64}$")


class CustomerResponse(CustomerBase):
    id: int = Field(..., alias="CustomerID")
    name: str = Field(..., alias="Name", max_length=100)
    phone: str = Field(..., alias="Phone", max_length=20)
    contact_person: str = Field(..., alias="ContactPerson", max_length=100)
    address: str = Field(..., alias="Address", max_length=200)
    email: EmailStr = Field(..., alias="Email")

    model_config = ConfigDict(from_attributes=True)

class CustomerUpdate(BaseModel):
    name: Optional[str] = Field(None, alias="Name", max_length=100)
    phone: Optional[str] = Field(None, alias="Phone", max_length=20)
    contact_person: Optional[str] = Field(None, alias="ContactPerson", max_length=100)
    address: Optional[str] = Field(None, alias="Address", max_length=200)
    email: Optional[EmailStr] = Field(None, alias="Email")

    model_config = ConfigDict(
        from_attributes=True,
        populate_by_name=True
    )


class Customer(BaseModel):
    id: int = Field(..., alias="CustomerID")
    name: str = Field(..., alias="Name", max_length=100)
    phone: str = Field(..., alias="Phone", max_length=20)
    contact_person: str = Field(..., alias="ContactPerson", max_length=100)
    address: str = Field(..., alias="Address", max_length=200)

    model_config = ConfigDict(from_attributes=True)

# Products
class ProductBase(BaseModel):
    name: str = Field(..., alias="Name")
    wholesale_price: float = Field(..., alias="WholesalePrice")
    retail_price: float = Field(..., alias="RetailPrice")
    description: Optional[str] = Field(None, alias="Description")  # Разрешаем None
    image: Optional[str] = Field(None, alias="Image")  # Разрешаем None


class Product(ProductBase):
    id: int = Field(..., alias="ProductID")

    @model_validator(mode='before')
    def convert_sqlalchemy_to_dict(cls, data):
        if not isinstance(data, dict):
            return {
                "ProductID": data.ProductID,
                "Name": data.Name,
                "WholesalePrice": data.WholesalePrice,
                "RetailPrice": data.RetailPrice,
                "Description": data.Description,
                "Image": data.Image
            }
        return data

    model_config = ConfigDict(from_attributes=True, populate_by_name=True)

# Cart
class CartItemBase(BaseModel):
    product_id: int = Field(..., alias="ProductID")
    quantity: int = Field(..., alias="Quantity")


    class Config:
        from_attributes = True

class CartItemCreate(CartItemBase):
    pass

class CartItemUpdate(BaseModel):
    quantity: int = Field(..., gt=0)


class CartItem(CartItemBase):
    id: int = Field(..., alias="CartItemID")
    product_name: str = Field(..., alias="ProductName")
    price: float = Field(..., alias="Price")
    added_date: datetime = Field(..., alias="AddedDate")

    class Config:
        from_attributes = True
        populate_by_name = True

class Cart(BaseModel):
    id: int = Field(..., alias="CartID")
    customer_id: int
    created_date: datetime
    last_updated: datetime
    items: Optional[list[CartItem]] = None
    model_config = ConfigDict(from_attributes=True)

# Transactions (Orders)
class TransactionDetailDB(BaseModel):
    id: int = Field(..., alias="TransactionDetailID")
    transaction_id: int = Field(..., alias="TransactionID")
    product_id: int = Field(..., alias="ProductID")
    quantity: int = Field(..., gt=0, alias="Quantity")
    discount: Optional[float] = Field(None, ge=0, le=1, alias="Discount")

    model_config = ConfigDict(from_attributes=True, populate_by_name=True)


class TransactionDetailCreate(BaseModel):
    product_id: int = Field(..., alias="ProductID")
    quantity: int = Field(..., gt=0, alias="Quantity")
    discount: Optional[float] = Field(None, ge=0, le=1, alias="Discount")

    model_config = ConfigDict(from_attributes=True, populate_by_name=True)

class TransactionDetailResponse(BaseModel):
    id: int = Field(..., alias="TransactionDetailID")
    transaction_id: int = Field(..., alias="TransactionID")
    product_id: int = Field(..., alias="ProductID")
    quantity: int = Field(..., gt=0)
    discount: Optional[float] = Field(None, ge=0, le=1)
    product_name: str
    current_price: float = Field(..., gt=0)
    calculated_total: float = Field(..., gt=0)

    @model_validator(mode='before')
    def ensure_id(cls, values):
        if values.get("id") is None:
            raise ValueError("TransactionDetailID is required")
        return values

    model_config = ConfigDict(from_attributes=True, populate_by_name=True)


class TransactionCreate(BaseModel):
    employee_id: int = Field(1, alias="EmployeeID")
    is_wholesale: bool = Field(False, alias="IsWholesale")

    model_config = ConfigDict(from_attributes=True, populate_by_name=True,  validate_default=True)


class TransactionResponse(BaseModel):
    id: int = Field(..., alias="TransactionID")
    customer_id: int = Field(..., alias="CustomerID")
    employee_id: int = Field(..., alias="EmployeeID")
    is_wholesale: bool = Field(..., alias="IsWholesale")
    transaction_date: datetime = Field(..., alias="TransactionDate")
    total_amount: float
    discount_amount: Optional[float]
    details: List[TransactionDetailResponse]

    model_config = ConfigDict(from_attributes=True, populate_by_name=True)

class DiscountBase(BaseModel):
    min_quantity: int = Field(..., alias="MinQuantity")
    max_quantity: int = Field(..., alias="MaxQuantity")
    discount_rate: float = Field(..., alias="DiscountRate")
    min_total_price: float = Field(..., alias="MinTotalPrice")


class DiscountCreate(DiscountBase):
    pass


class Discount(DiscountBase):
    discount_id: int = Field(..., alias="DiscountID")

    class Config:
        from_attributes = True
        populate_by_name = True

# Lists
class ProductsList(BaseModel):
    products: List[Product]

class CartItemsList(BaseModel):
    items: List[CartItem]
    total_items: int
    total_price: float
    discounted_price: float
    discount_rate: float
    discount_id: Optional[int] = None
    cart_id: int = Field(..., alias="CartID")
    customer_id: int = Field(..., alias="CustomerID")

    class Config:
        populate_by_name = True

class TransactionsList(BaseModel):
    transactions: List[TransactionResponse]



