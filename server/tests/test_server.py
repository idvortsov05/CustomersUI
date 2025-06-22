import pytest
from unittest.mock import Mock
from fastapi import HTTPException
from sqlalchemy.orm import Session

from http_server.crud import (
    get_customer_by_email,
    create_customer,
    add_to_cart,
)
from http_server.models import Customer
from http_server.schemas import CustomerCreate, CartItemCreate


# Тест 1: Создание клиента
def test_create_customer():
    mock_db = Mock(spec=Session)

    customer_data = CustomerCreate(
        name="Test User",
        phone="1234567890",
        contact_person="Contact Person",
        address="Test Address",
        email="test1@example.com",
        password="a"*64
    )

    result = create_customer(mock_db, customer_data)
    mock_db.add.assert_called_once()
    mock_db.commit.assert_called_once()
    mock_db.refresh.assert_called_once()

    assert isinstance(result, Customer)
    assert result.Email == "test1@example.com"


# Тест 2: Получение клиента по email
def test_get_customer_by_email():
    mock_db = Mock(spec=Session)

    mock_customer = Customer(Email="test1@example.com")
    mock_db.query().filter().first.return_value = mock_customer

    result = get_customer_by_email(mock_db, "test1@example.com")

    assert result == mock_customer
    assert result.Email == "test1@example.com"

# Тест 3: Ошибка при добавлении несуществующего товара в корзину
def test_add_nonexistent_product_to_cart():
    mock_db = Mock(spec=Session)

    mock_db.query.return_value.filter.return_value.first.return_value = None

    cart_item = CartItemCreate(ProductID=999, Quantity=1)

    with pytest.raises(HTTPException) as exc_info:
        add_to_cart(mock_db, 1, cart_item)

    assert exc_info.value.status_code == 404
    assert "Product not found" in str(exc_info.value.detail)



