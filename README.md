# Игра в змейку
**Pet-проект**, реализованный на **C++17** с использованием **Qt6**.  
Классическая игра в змейку с простым интерфейсом, меню настроек и таблицей счёта.

## Версия
Текущая версия: **1.0.0**

## Установка зависимостей
```
sudo apt update
sudo apt-get install build-essential libgl1-mesa-dev
sudo apt install qt6-base-dev qt6-base-dev-tools qt6-tools-dev
sudo apt install qt6-wayland
sudo apt install libxkbcommon-dev
sudo apt install libspdlog-dev
sudo apt install doxygen
sudo apt install graphviz
```

## Запуск приложения
```
mkdir build
cd build
cmake .. && make
./main
```