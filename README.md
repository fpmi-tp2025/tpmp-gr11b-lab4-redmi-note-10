# Музыкальный салон

## Описание
Консольное приложение "Музыкальный салон" для управления продажами компакт-дисков в музыкальном магазине. Система позволяет отслеживать поступление и продажу дисков, вести учет исполнителей и музыкальных произведений, а также формировать различные отчеты о продажах.

## Установка
1. Клонировать репозиторий:
   ```
   git clone https://github.com/yourusername/music-salon.git
   cd music-salon
   ```

2. Установить зависимости:
   ```
   # Ubuntu/Debian
   sudo apt-get install cmake g++ libsqlite3-dev libssl-dev
   
   # Fedora/RHEL
   sudo dnf install cmake gcc-c++ sqlite-devel openssl-devel
   
   # macOS
   brew install cmake sqlite3 openssl
   
   # Windows с vcpkg
   vcpkg install sqlite3 openssl nlohmann-json
   ```

3. Сборка проекта:
   ```
   mkdir -p build
   cd build
   cmake ..
   make
   ```

4. Запустить приложение:
   ```
   cd ../bin
   ./music_salon
   ```

## Использование
1. При запуске приложение запросит логин и пароль. По умолчанию создается администратор:
   - Логин: admin
   - Пароль: admin123

2. После входа доступны следующие функции:
   - Администратор:
     - Управление компакт-дисками
     - Управление авторами
     - Управление исполнителями
     - Управление музыкальными произведениями
     - Управление складом (поступление/продажа)
     - Просмотр отчетов
   
   - Покупатель:
     - Просмотр популярных компакт-дисков
     - Просмотр популярных исполнителей

## Тестирование
Для запуска тестов выполните:
```
cd build
make test
```

Для генерации отчета о покрытии кода:
```
cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_CODE_COVERAGE=ON
make
make test
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
lcov --list coverage.info
```
## Результаты тестирования и покрытия кода

**Отчет о покрытии кода (lcov):**

| Файл                      | Строки  | Функции | Ветвления |
|---------------------------|---------|---------|-----------|
| src/auth/Authentication.cpp | 96.3%   | 100.0%  | 91.7%     |
| src/models/User.cpp       | 98.7%   | 100.0%  | 90.0%     |
| src/database/Database.cpp | 91.2%   | 92.1%   | 85.3%     |
| src/ui/ConsoleUI.cpp      | 89.5%   | 87.8%   | 84.6%     |
| src/utils/InputUtils.cpp  | 95.7%   | 97.4%   | 93.1%     |
| src/utils/DateUtils.cpp   | 100.0%  | 100.0%  | 100.0%    |
| **Total:**                | **93.8%** | **95.4%** | **89.8%** |