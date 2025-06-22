import time

from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

def test_swagger_ui_loads(browser):
    browser.get("http://127.0.0.1:8080/docs")
    assert "Swagger UI" in browser.title

    WebDriverWait(browser, 10).until(
        EC.presence_of_element_located((By.XPATH, "//h2[text()='FastAPI']"))
    )


def test_register_new_customer(browser):
    browser.get("http://127.0.0.1:8080/docs")
    WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.CLASS_NAME, "swagger-ui")))
    WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.XPATH, "//div[contains(@class, 'opblock-post') and .//span[contains(text(), '/register')]]")))
    register_section = browser.find_element(By.XPATH,"//div[contains(@class, 'opblock-post') and .//span[contains(text(), '/register')]]")
    register_section.click()
    try_it_out = WebDriverWait(browser, 10).until(EC.element_to_be_clickable((By.XPATH, ".//button[contains(text(), 'Try it out')]")))
    try_it_out.click()
    time.sleep(3)

    request_body = WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.XPATH, ".//textarea[contains(@class, 'body-param__text')]")))
    request_body.clear()
    time.sleep(3)

    request_body.send_keys('''
    {
        "name": "string",
        "phone": "string",
        "contact_person": "string",
        "address": "string",
        "email": "user123456@example.com",
        "password": "4c964b34f4e43600168fe23ffe568b4e9e21c24e0491b69dada4bbd95180b21e"
    }
    ''')
    time.sleep(3)

    execute_button = WebDriverWait(browser, 10).until(EC.element_to_be_clickable((By.XPATH, ".//button[contains(text(), 'Execute')]")))
    execute_button.click()
    time.sleep(3)

    response_code = WebDriverWait(browser, 10).until(EC.presence_of_element_located((By.XPATH, ".//td[@class='response-col_status']")))

    assert "200" in response_code.text or "201" in response_code.text, f"Expected 200 or 201, but got {response_code.text}"





