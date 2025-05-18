#include <gtest/gtest.h>
#include <memory>
#include <iostream>
#include <cstdio>
#include "../../includes/database/Database.h"
#include "../../includes/models/User.h"

namespace MusicSalon {
namespace Tests {

class DatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаём временную базу данных для тестов
        dbPath = "test_music_salon.db";
        
        // Удаляем файл базы, если он существует
        std::remove(dbPath.c_str());
        
        // Создаём новую базу данных
        db = std::make_unique<Database::Database>(dbPath);
    }
    
    void TearDown() override {
        db.reset();
        
        // Удаляем файл базы после тестов
        std::remove(dbPath.c_str());
    }
    
    std::string dbPath;
    std::unique_ptr<Database::Database> db;
};

TEST_F(DatabaseTest, InitializesDatabaseWithTables) {
    // Проверяем, что база данных инициализирована с таблицами
    auto users = db->getAllUsers();
    
    // Ожидаем хотя бы одного пользователя (администратора по умолчанию)
    ASSERT_GT(users.size(), 0);
    
    // Проверяем создание таблицы конфигурации
    // Поскольку метод для получения всех конфигурационных параметров
    // не реализован, проверяем косвенно через создание диска и проверку соблюдения бизнес-правил
    
    // Создаём тестовый компакт-диск
    Models::CompactDisc disc("Test Album", "2023-01-01", "Test Producer", 15.99);
    ASSERT_TRUE(db->createDisc(disc, 1));
    
    // Получаем созданный диск и проверяем его код
    auto discs = db->getAllDiscs();
    ASSERT_GT(discs.size(), 0);
    
    int discCode = discs[0]->getDiscCode();
    
    // Создаём операцию поступления
    Models::StockOperation receiveOp(
        "2023-01-02", "поступление", discCode, 10, 10.0, 100.0);
    ASSERT_TRUE(db->createStockOperation(receiveOp, 1));
    
    // Создаём операцию продажи
    Models::StockOperation saleOp(
        "2023-01-03", "продажа", discCode, 5, 15.99, 79.95);
    ASSERT_TRUE(db->createStockOperation(saleOp, 1));
    
    // Попытка продать больше, чем есть на складе, должна завершиться неудачей
    Models::StockOperation invalidSaleOp(
        "2023-01-04", "продажа", discCode, 10, 15.99, 159.90);
    ASSERT_FALSE(db->createStockOperation(invalidSaleOp, 1));
}

TEST_F(DatabaseTest, CalculatesPeriodStatistics) {
    // Создаём тестовый компакт-диск
    Models::CompactDisc disc("Test Album", "2023-01-01", "Test Producer", 15.99);
    ASSERT_TRUE(db->createDisc(disc, 1));
    
    auto discs = db->getAllDiscs();
    int discCode = discs[0]->getDiscCode();
    
    // Создаём операции поступления и продажи
    Models::StockOperation receiveOp(
        "2023-01-02", "поступление", discCode, 20, 10.0, 200.0);
    ASSERT_TRUE(db->createStockOperation(receiveOp, 1));
    
    Models::StockOperation saleOp1(
        "2023-01-03", "продажа", discCode, 5, 15.99, 79.95);
    ASSERT_TRUE(db->createStockOperation(saleOp1, 1));
    
    Models::StockOperation saleOp2(
        "2023-01-04", "продажа", discCode, 3, 15.99, 47.97);
    ASSERT_TRUE(db->createStockOperation(saleOp2, 1));
    
    // Рассчитываем статистику за период
    ASSERT_TRUE(db->calculatePeriodStatistics("2023-01-01", "2023-01-05", 1));
    
    // Проверяем результаты продаж диска за период
    auto result = db->getDiscSalesResults(discCode, "2023-01-01", "2023-01-05");
    
    // Распаковываем кортеж: количество, общая стоимость, средняя цена
    int totalQuantity = std::get<0>(result);
    double totalPrice = std::get<1>(result);
    double avgPrice = std::get<2>(result);
    
    ASSERT_EQ(totalQuantity, 8);  // 5 + 3 проданных
    ASSERT_DOUBLE_EQ(totalPrice, 127.92);  // 79.95 + 47.97
    ASSERT_DOUBLE_EQ(avgPrice, 15.99);  // средняя цена продажи
}

TEST_F(DatabaseTest, SavesAndLoadsDiscImage) {
    // Создаём тестовый компакт-диск
    Models::CompactDisc disc("Test Album", "2023-01-01", "Test Producer", 15.99);
    ASSERT_TRUE(db->createDisc(disc, 1));
    
    auto discs = db->getAllDiscs();
    int discCode = discs[0]->getDiscCode();
    
    // Создаём тестовое изображение (простой массив байтов)
    std::vector<unsigned char> imageData = {
        0xFF, 0xD8, 0xFF, 0xE0, // Начало JPEG файла
        0x00, 0x10, 0x4A, 0x46, // JFIF
        0x49, 0x46, 0x00, 0x01, // ...
        // Другие байты...
        0xFF, 0xD9               // Конец JPEG файла
    };
    
    // Сохраняем изображение
    ASSERT_TRUE(db->saveDiscImage(discCode, imageData));
    
    // Загружаем изображение
    auto loadedImageData = db->getDiscImage(discCode);
    
    // Проверяем, что загруженные данные совпадают с сохранёнными
    ASSERT_EQ(loadedImageData.size(), imageData.size());
    
    for (size_t i = 0; i < imageData.size(); i++) {
        ASSERT_EQ(loadedImageData[i], imageData[i]);
    }
}

} // namespace Tests
} // namespace MusicSalon
