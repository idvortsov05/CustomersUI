from config.config_server import get_config
from routers import router
from database import create_table


import uvicorn
import argparse
from fastapi import FastAPI


def main(config_file_path):
    config = get_config(config_file_path)
    host = config["server"]["host"]
    port = int(config["server"]["port"])

    print(f"Создано приложение FastAPI по адресу: {host}:{port}")
    create_table()

    app = FastAPI()
    app.include_router(router)

    uvicorn.run(app, host=host, port=port)
    print("Сервер запущен!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', required=True, help='Путь к файлу конфигурации')
    args = parser.parse_args()
    main(args.config)
