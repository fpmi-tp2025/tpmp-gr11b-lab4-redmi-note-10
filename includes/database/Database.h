#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sqlite3.h>
#include "../models/CompactDisc.h"
#include "../models/Author.h"
#include "../models/Performer.h"
#include "../models/MusicalWork.h"
#include "../models/StockOperation.h"
#include "../models/User.h"

namespace MusicSalon {
namespace Database {

class Database {
public:
    Database(const std::string& dbPath);
    ~Database();

    // Операции с пользователями
    std::unique_ptr<Models::User> getUserByUsername(const std::string& username);
    std::vector<std::unique_ptr<Models::User>> getAllUsers();
    bool createUser(const Models::User& user);
    bool updateUser(const Models::User& user);
    bool deleteUser(int userId);

    // Операции с компакт-дисками
    std::unique_ptr<Models::CompactDisc> getDiscById(int discCode);
    std::vector<std::unique_ptr<Models::CompactDisc>> getAllDiscs();
    bool createDisc(const Models::CompactDisc& disc, int createdBy);
    bool updateDisc(const Models::CompactDisc& disc);
    bool deleteDisc(int discCode);

    // Операции с авторами
    std::unique_ptr<Models::Author> getAuthorById(int authorId);
    std::vector<std::unique_ptr<Models::Author>> getAllAuthors();
    bool createAuthor(const Models::Author& author, int createdBy);
    bool updateAuthor(const Models::Author& author);
    bool deleteAuthor(int authorId);

    // Операции с исполнителями
    std::unique_ptr<Models::Performer> getPerformerById(int performerId);
    std::vector<std::unique_ptr<Models::Performer>> getAllPerformers();
    bool createPerformer(const Models::Performer& performer, int createdBy);
    bool updatePerformer(const Models::Performer& performer);
    bool deletePerformer(int performerId);

    // Операции с музыкальными произведениями
    std::unique_ptr<Models::MusicalWork> getWorkById(int workId);
    std::vector<std::unique_ptr<Models::MusicalWork>> getWorksByDiscId(int discCode);
    bool createWork(const Models::MusicalWork& work, int createdBy);
    bool updateWork(const Models::MusicalWork& work);
    bool deleteWork(int workId);

    // Операции со складом
    bool createStockOperation(const Models::StockOperation& operation, int userId);
    std::vector<std::unique_ptr<Models::StockOperation>> getOperationsByDiscId(int discCode);
    
    // Требуемые запросы из задания
    std::vector<std::pair<std::unique_ptr<Models::CompactDisc>, std::pair<int, int>>> getDiscsWithSalesAndRemaining();
    std::pair<int, double> getDiscSalesForPeriod(int discCode, const std::string& startDate, const std::string& endDate);
    std::pair<std::unique_ptr<Models::CompactDisc>, std::vector<std::unique_ptr<Models::MusicalWork>>> getMostPopularDisc();
    std::pair<std::unique_ptr<Models::Performer>, int> getMostPopularPerformer();
    std::vector<std::tuple<std::unique_ptr<Models::Author>, int, double>> getAuthorSalesStats();
    
    // Функция для расчета статистики за период
    bool calculatePeriodStatistics(const std::string& startDate, const std::string& endDate, int userId);
    
    // Функция для получения результатов продаж диска за период
    std::tuple<int, double, double> getDiscSalesResults(int discCode, const std::string& startDate, const std::string& endDate);

    // Функция для сохранения изображения компакт-диска
    bool saveDiscImage(int discCode, const std::vector<unsigned char>& imageData);
    
    // Функция для получения изображения компакт-диска
    std::vector<unsigned char> getDiscImage(int discCode);

private:
    sqlite3* db;
    bool connected;
    
    // Служебная функция для выполнения запросов
    bool executeQuery(const std::string& query);
    
    // Проверка инициализации базы данных
    bool isInitialized();
    
    // Инициализация базы данных с базовой схемой
    bool initializeDatabase();
};

} // namespace Database
} // namespace MusicSalon