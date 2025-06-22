#include "../src/http_client/GUI/Client_GUI/MainWindow.h"
#include "../src/http_client/GUI/Login_GUI/LoginWindow.h"

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Логин-окно
    LoginWindow login;

    // Если логин не прошел, завершаем приложение
    if (login.exec() != QDialog::Accepted) {
        return 0; // Выход из программы, если авторизация не удалась
    }

    // Главное окно
    MainWindow mainWindow;

    // Подключение сигнала выхода из профиля, чтобы при выходе показать окно логина
    QObject::connect(&mainWindow, &MainWindow::loggedOut, [&]() {
        mainWindow.close();  // Закрываем главное окно
        login.show();        // Показываем окно логина
    });

    mainWindow.show();  // Показываем главное окно

    return app.exec();  // Запуск основного цикла приложения
}

