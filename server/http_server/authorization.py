from config.config_server import get_config

import hashlib
import getpass
import argparse


def main(config_file_path):
    username = input("Введите логин: ")

    password = getpass.getpass("Введите пароль: ")
    hashed_password = hashlib.sha256(password.encode('utf-8')).hexdigest()

    config = get_config(config_file_path)
    config["auth"]["username"] = username
    config["auth"]["password_hash"] = hashed_password

    with open(config_file_path, 'r+') as configfile:
        config.write(configfile)

    print("Данные успешно обновлены в config.ini")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', required=True, help='Путь к файлу конфигурации')
    args = parser.parse_args()
    main(args.config)


