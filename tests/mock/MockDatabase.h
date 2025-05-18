#pragma once

#include <gmock/gmock.h>
#include "../../includes/database/Database.h"

namespace MusicSalon {
namespace Mocks {

class MockDatabase : public Database::Database {
public:
    MockDatabase() : Database::Database("") {}
    
    // Операции с пользователями
    MOCK_METHOD(std::unique_ptr<Models::User>, getUserByUsername, (const std::string&), (override));
    MOCK_METHOD(std::vector<std::unique_ptr<Models::User>>, getAllUsers, (), (override));
    MOCK_METHOD(bool, createUser, (const Models::User&), (override));
    MOCK_METHOD(bool, updateUser, (const Models::User&), (override));
    MOCK_METHOD(bool, deleteUser, (int), (override));
    
    // Операции с компакт-дисками
    MOCK_METHOD(std::unique_ptr<Models::CompactDisc>, getDiscById, (int), (override));
    MOCK_METHOD(std::vector<std::unique_ptr<Models::CompactDisc>>, getAllDiscs, (), (override));
    MOCK_METHOD(bool, createDisc, (const Models::CompactDisc&, int), (override));
    MOCK_METHOD(bool, updateDisc, (const Models::CompactDisc&), (override));
    MOCK_METHOD(bool, deleteDisc, (int), (override));
    
    // Операции с авторами
    MOCK_METHOD(std::unique_ptr<Models::Author>, getAuthorById, (int), (override));
    MOCK_METHOD(std::vector<std::unique_ptr<Models::Author>>, getAllAuthors, (), (override));
    MOCK_METHOD(bool, createAuthor, (const Models::Author&, int), (override));
    MOCK_METHOD(bool, updateAuthor, (const Models::Author&), (override));
    MOCK_METHOD(bool, deleteAuthor, (int), (override));
    
    // Операции с исполнителями
    MOCK_METHOD(std::unique_ptr<Models::Performer>, getPerformerById, (int), (override));
    MOCK_METHOD(std::vector<std::unique_ptr<Models::Performer>>, getAllPerformers, (), (override));
    MOCK_METHOD(bool, createPerformer, (const Models::Performer&, int), (override));
    MOCK_METHOD(bool, updatePerformer, (const Models::Performer&), (override));
    MOCK_METHOD(bool, deletePerformer, (int), (override));
    
    // Операции с музыкальными произведениями
    MOCK_METHOD(std::unique_ptr<Models::MusicalWork>, getWorkById, (int), (override));
    MOCK_METHOD(std::vector<std::unique_ptr<Models::MusicalWork>>, getWorksByDiscId, (int), (override));
    MOCK_METHOD(bool, createWork, (const Models::MusicalWork&, int), (override));
    MOCK_METHOD(bool, updateWork, (const Models::MusicalWork&), (override));
    MOCK_METHOD(bool, deleteWork, (int), (override));
    
    // Операции со складом
    MOCK_METHOD(bool, createStockOperation, (const Models::StockOperation&, int), (override));
    MOCK_METHOD(std::vector<std::unique_ptr<Models::StockOperation>>, getOperationsByDiscId, (int), (override));
    
    // Требуемые запросы из задания
    MOCK_METHOD((std::vector<std::pair<std::unique_ptr<Models::CompactDisc>, std::pair<int, int>>>), 
                getDiscsWithSalesAndRemaining, (), (override));
    MOCK_METHOD((std::pair<int, double>), 
                getDiscSalesForPeriod, (int, const std::string&, const std::string&), (override));
    MOCK_METHOD((std::pair<std::unique_ptr<Models::CompactDisc>, std::vector<std::unique_ptr<Models::MusicalWork>>>),
                getMostPopularDisc, (), (override));
    MOCK_METHOD((std::pair<std::unique_ptr<Models::Performer>, int>),
                getMostPopularPerformer, (), (override));
    MOCK_METHOD((std::vector<std::tuple<std::unique_ptr<Models::Author>, int, double>>), 
                getAuthorSalesStats, (), (override));
    
    // Функции статистики и результатов
    MOCK_METHOD(bool, calculatePeriodStatistics, (const std::string&, const std::string&, int), (override));
    MOCK_METHOD((std::tuple<int, double, double>), 
                getDiscSalesResults, (int, const std::string&, const std::string&), (override));
    
    // Операции с изображениями
    MOCK_METHOD(bool, saveDiscImage, (int, const std::vector<unsigned char>&), (override));
    MOCK_METHOD(std::vector<unsigned char>, getDiscImage, (int), (override));
    
    // Служебные методы
    MOCK_METHOD(bool, executeQuery, (const std::string&), (override));
    MOCK_METHOD(bool, isInitialized, (), (override));
    MOCK_METHOD(bool, initializeDatabase, (), (override));
};

} // namespace Mocks
} // namespace MusicSalon