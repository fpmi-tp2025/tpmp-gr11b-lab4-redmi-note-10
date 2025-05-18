cmake_minimum_required(VERSION 3.14)
project(music_salon VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции покрытия кода
option(ENABLE_CODE_COVERAGE "Enable code coverage reporting" OFF)

# Директории проекта
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Установка выходных директорий
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})

# Поиск зависимостей
find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)

# Если сборка тестов включена, добавить Google Test
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR ENABLE_CODE_COVERAGE)
    enable_testing()
    find_package(GTest REQUIRED)
    include(GoogleTest)
endif()

# Сборка основных исходных файлов
file(GLOB_RECURSE SOURCES 
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/auth/*.cpp
    ${SRC_DIR}/database/*.cpp
    ${SRC_DIR}/models/*.cpp
    ${SRC_DIR}/ui/*.cpp
    ${SRC_DIR}/utils/*.cpp
)

# Заголовочные файлы
file(GLOB_RECURSE HEADERS 
    ${INCLUDE_DIR}/*.h
    ${INCLUDE_DIR}/auth/*.h
    ${INCLUDE_DIR}/database/*.h
    ${INCLUDE_DIR}/models/*.h
    ${INCLUDE_DIR}/ui/*.h
    ${INCLUDE_DIR}/utils/*.h
)

# Определение исполняемого файла
add_executable(music_salon ${SOURCES} ${HEADERS})

# Настройка включаемых директорий
target_include_directories(music_salon PRIVATE 
    ${INCLUDE_DIR}
    ${SQLite3_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)

# Подключение библиотек
target_link_libraries(music_salon PRIVATE 
    ${SQLite3_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    nlohmann_json::nlohmann_json
)

# Копирование SQL скрипта и ресурсов в бинарную директорию
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/music_salon_db.db ${BIN_DIR}/music_salon_db.db COPYONLY)
file(GLOB RESOURCE_FILES ${RESOURCES_DIR}/*)
foreach(RESOURCE_FILE ${RESOURCE_FILES})
    get_filename_component(FILENAME ${RESOURCE_FILE} NAME)
    configure_file(${RESOURCE_FILE} ${BIN_DIR}/${FILENAME} COPYONLY)
endforeach()

# Если сборка тестов включена, собрать тесты
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR ENABLE_CODE_COVERAGE)
    # Исходники тестов
    file(GLOB_RECURSE TEST_SOURCES 
        ${TEST_DIR}/*.cpp
        ${TEST_DIR}/auth/*.cpp
        ${TEST_DIR}/database/*.cpp
        ${TEST_DIR}/models/*.cpp
        ${TEST_DIR}/utils/*.cpp
    )
    
    # Исключаем main.cpp из списка исходников для тестов
    list(REMOVE_ITEM SOURCES ${SRC_DIR}/main.cpp)
    
    # Добавление тестового приложения
    add_executable(music_salon_tests ${TEST_SOURCES} ${SOURCES})
    
    # Настройка включаемых директорий для тестов
    target_include_directories(music_salon_tests PRIVATE 
        ${INCLUDE_DIR}
        ${TEST_DIR}
        ${GTEST_INCLUDE_DIRS}
        ${SQLite3_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
    )
    
    # Подключение библиотек для тестов
    target_link_libraries(music_salon_tests PRIVATE 
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        ${SQLite3_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        nlohmann_json::nlohmann_json
        pthread
    )
    
    # Настройка тестирования
    gtest_discover_tests(music_salon_tests)
    
    # Если включено покрытие кода, настроить его
    if(ENABLE_CODE_COVERAGE)
        target_compile_options(music_salon_tests PRIVATE --coverage)
        target_link_options(music_salon_tests PRIVATE --coverage)
    endif()
endif()

# Настройка установки
install(TARGETS music_salon DESTINATION bin)
install(FILES ${BIN_DIR}/music_salon_db.sql DESTINATION bin)
install(DIRECTORY ${RESOURCES_DIR}/ DESTINATION bin/resources)
