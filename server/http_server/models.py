from sqlalchemy import Column, Integer, String, Date, Float, ForeignKey, Boolean, BLOB, DateTime
from sqlalchemy.orm import declarative_base, relationship
from datetime import datetime

Base = declarative_base()

class Customer(Base):
    __tablename__ = 'Customers'

    CustomerID = Column(Integer, primary_key=True, autoincrement=True)
    Name = Column(String(100), nullable=False)
    Phone = Column(String(20), nullable=False)
    ContactPerson = Column(String(100), nullable=False)
    Address = Column(String(200), nullable=False)
    Email = Column(String(100), unique=True, nullable=False)
    PasswordHash = Column(String(64), nullable=False)

    carts = relationship("Cart", back_populates="customer")
    transactions = relationship("Transaction", back_populates="customer")


class Employee(Base):
    __tablename__ = 'Employees'

    EmployeeID = Column(Integer, primary_key=True, autoincrement=True)
    Name = Column(String(100), nullable=False)
    Position = Column(String(50), nullable=False)
    Phone = Column(String(20), nullable=False)
    Email = Column(String(100), nullable=False)
    HireDate = Column(Date, nullable=False)
    Photo = Column(BLOB, nullable=False)

    transactions = relationship("Transaction", back_populates="employee")
    def __repr__(self):
        return f"<Employee(id={self.EmployeeID}, name='{self.Name}')>"


class Product(Base):
    __tablename__ = 'Products'

    ProductID = Column(Integer, primary_key=True, autoincrement=True)
    Name = Column(String, nullable=False, index=True)
    WholesalePrice = Column(Float, nullable=False)
    RetailPrice = Column(Float, nullable=False, index=True)
    Description = Column(String)
    Image = Column(String)

    cart_items = relationship("CartItem", back_populates="product")
    transaction_details = relationship("TransactionDetail", back_populates="product")

    def __repr__(self):
        return f"<Product(id={self.ProductID}, name='{self.Name}')>"


class Discount(Base):
    __tablename__ = 'Discounts'

    DiscountID = Column(Integer, primary_key=True, autoincrement=True)
    MinQuantity = Column(Integer, nullable=False)
    MaxQuantity = Column(Integer, nullable=False)
    DiscountRate = Column(Float, nullable=False)
    MinTotalPrice = Column(Float, nullable=False)

    def __repr__(self):
        return f"<Discount(id={self.DiscountID}, rate={self.DiscountRate})>"


class Transaction(Base):
    __tablename__ = 'Transactions'

    TransactionID = Column(Integer, primary_key=True, autoincrement=True)
    TransactionDate = Column(DateTime, nullable=False, default=datetime.utcnow)
    CustomerID = Column(Integer, ForeignKey('Customers.CustomerID'), nullable=False)
    EmployeeID = Column(Integer, ForeignKey('Employees.EmployeeID'), nullable=False)
    IsWholesale = Column(Boolean, nullable=False, default=False)

    customer = relationship("Customer", back_populates="transactions")
    employee = relationship("Employee", back_populates="transactions")
    details = relationship("TransactionDetail", back_populates="transaction")

    def __repr__(self):
        return f"<Transaction(id={self.TransactionID}, date={self.TransactionDate})>"


class TransactionDetail(Base):
    __tablename__ = 'TransactionDetails'

    TransactionDetailID = Column(Integer, primary_key=True, autoincrement=True)
    TransactionID = Column(Integer, ForeignKey('Transactions.TransactionID'), nullable=False)
    ProductID = Column(Integer, ForeignKey('Products.ProductID'), nullable=False)
    Quantity = Column(Integer, nullable=False, default=1)
    Discount = Column(Float)

    transaction = relationship("Transaction", back_populates="details")
    product = relationship("Product", back_populates="transaction_details")

    def __repr__(self):
        return f"<TransactionDetail(id={self.TransactionDetailID}, product={self.ProductID})>"


class Cart(Base):
    __tablename__ = 'Carts'

    CartID = Column(Integer, primary_key=True, autoincrement=True)
    CustomerID = Column(Integer, ForeignKey('Customers.CustomerID'), nullable=False)
    CreatedDate = Column(DateTime, nullable=False, default=datetime.utcnow)
    LastUpdated = Column(DateTime, onupdate=datetime.utcnow)

    customer = relationship("Customer", back_populates="carts")
    items = relationship("CartItem", back_populates="cart", cascade="all, delete-orphan")

    def __repr__(self):
        return f"<Cart(id={self.CartID}, customer={self.CustomerID})>"


class CartItem(Base):
    __tablename__ = 'CartItems'

    CartItemID = Column(Integer, primary_key=True, autoincrement=True)
    CartID = Column(Integer, ForeignKey('Carts.CartID'), nullable=False)
    ProductID = Column(Integer, ForeignKey('Products.ProductID'), nullable=False)
    Quantity = Column(Integer, nullable=False, default=1)
    AddedDate = Column(DateTime, nullable=False, default=datetime.utcnow)

    cart = relationship("Cart", back_populates="items")
    product = relationship("Product", back_populates="cart_items")

    def __repr__(self):
        return f"<CartItem(id={self.CartItemID}, product={self.ProductID}, qty={self.Quantity})>"