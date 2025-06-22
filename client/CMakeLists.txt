cmake_minimum_required(VERSION 3.22.0)
cmake_policy(SET CMP0016 NEW)

project(http_client VERSION 1.0.0 DESCRIPTION "GUI-клиент редактирования БД")

set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5/share/qt5")

find_package(Qt5 COMPONENTS Core Widgets Network PrintSupport REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/http_client/main.cpp
        ${CMAKE_SOURCE_DIR}/src/http_client/http_requests/Requests.cpp
        ${CMAKE_SOURCE_DIR}/src/http_client/GUI/Client_GUI/MainWindow.cpp
        ${CMAKE_SOURCE_DIR}/src/http_client/GUI/Client_GUI/Profile/EditProfileWindow.cpp
        ${CMAKE_SOURCE_DIR}/src/http_client/GUI/Login_GUI/LoginWindow.cpp
        ${CMAKE_SOURCE_DIR}/src/http_client/GUI/Login_GUI/RegisterDialog.cpp
        ${CMAKE_SOURCE_DIR}/src/http_client/GUI/Client_GUI/Cart/CartWindow.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network Qt5::Core Qt5::PrintSupport)


