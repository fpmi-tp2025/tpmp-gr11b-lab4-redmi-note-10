#include "../../includes/database/Database.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace MusicSalon {
namespace Database {

Database::Database(const std::string& dbPath) 
    : db(nullptr), connected(false) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Невозможно открыть базу данных: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    
    connected = true;
    
    if (!isInitialized()) {
        if (!initializeDatabase()) {
            std::cerr << "Не удалось инициализировать базу данных" << std::endl;
            connected = false;
            sqlite3_close(db);
            return;
        }
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

std::unique_ptr<Models::User> Database::getUserByUsername(const std::string& username) {
    if (!connected) {
        return nullptr;
    }
    
    const char* sql = "SELECT user_id, username, password_hash, full_name, email, role, "
                      "create_date, last_login, is_active FROM MUSIC_USERS WHERE username = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return nullptr;
    }
    
    int userId = sqlite3_column_int(stmt, 0);
    std::string dbUsername = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    std::string passwordHash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    std::string fullName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
    std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
    std::string createDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
    std::string lastLogin = sqlite3_column_type(stmt, 7) != SQLITE_NULL ? 
                            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)) : "";
    bool isActive = sqlite3_column_int(stmt, 8) == 1;
    
    sqlite3_finalize(stmt);
    
    return std::make_unique<Models::User>(userId, dbUsername, passwordHash, fullName, email, 
                                         role, createDate, lastLogin, isActive);
}

std::vector<std::unique_ptr<Models::CompactDisc>> Database::getAllDiscs() {
    std::vector<std::unique_ptr<Models::CompactDisc>> discs;
    
    if (!connected) {
        return discs;
    }
    
    const char* sql = "SELECT disc_code, title, manufacture_date, producer, price, "
                     "create_date, last_update, created_by FROM MUSIC_COMPACT_DISCS";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return discs;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int discCode = sqlite3_column_int(stmt, 0);
        std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string manufactureDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string producer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        double price = sqlite3_column_double(stmt, 4);
        std::string createDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        std::string lastUpdate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        int createdBy = sqlite3_column_int(stmt, 7);
        
        discs.push_back(std::make_unique<Models::CompactDisc>(
            discCode, title, manufactureDate, producer, price, createDate, lastUpdate, createdBy));
    }
    
    sqlite3_finalize(stmt);
    return discs;
}

// Реализация метода getMostPopularDisc (один из требуемых запросов)
std::pair<std::unique_ptr<Models::CompactDisc>, std::vector<std::unique_ptr<Models::MusicalWork>>> 
Database::getMostPopularDisc() {
    std::unique_ptr<Models::CompactDisc> disc = nullptr;
    std::vector<std::unique_ptr<Models::MusicalWork>> works;
    
    if (!connected) {
        return std::make_pair(std::move(disc), std::move(works));
    }
    
    // Запрос для нахождения самого популярного компакт-диска
    const char* sql1 = "SELECT cd.disc_code, cd.title, cd.manufacture_date, cd.producer, "
                      "cd.price, cd.create_date, cd.last_update, cd.created_by "
                      "FROM MUSIC_COMPACT_DISCS cd "
                      "LEFT JOIN MUSIC_STOCK_OPERATIONS so ON cd.disc_code = so.disc_code "
                      "WHERE so.operation_type = 'продажа' "
                      "GROUP BY cd.disc_code "
                      "ORDER BY SUM(so.quantity) DESC "
                      "LIMIT 1";
    
    sqlite3_stmt* stmt1;
    int rc = sqlite3_prepare_v2(db, sql1, -1, &stmt1, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return std::make_pair(std::move(disc), std::move(works));
    }
    
    if (sqlite3_step(stmt1) == SQLITE_ROW) {
        int discCode = sqlite3_column_int(stmt1, 0);
        std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt1, 1));
        std::string manufactureDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt1, 2));
        std::string producer = reinterpret_cast<const char*>(sqlite3_column_text(stmt1, 3));
        double price = sqlite3_column_double(stmt1, 4);
        std::string createDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt1, 5));
        std::string lastUpdate = reinterpret_cast<const char*>(sqlite3_column_text(stmt1, 6));
        int createdBy = sqlite3_column_int(stmt1, 7);
        
        disc = std::make_unique<Models::CompactDisc>(
            discCode, title, manufactureDate, producer, price, createDate, lastUpdate, createdBy);
        
        // Получаем музыкальные произведения для этого диска
        const char* sql2 = "SELECT mw.work_id, mw.title, mw.author_id, mw.performer_id, "
                          "mw.disc_code, mw.track_number, mw.duration, mw.create_date, "
                          "mw.last_update, mw.created_by "
                          "FROM MUSIC_WORKS mw "
                          "WHERE mw.disc_code = ?";
        
        sqlite3_stmt* stmt2;
        rc = sqlite3_prepare_v2(db, sql2, -1, &stmt2, nullptr);
        
        if (rc == SQLITE_OK) {
            sqlite3_bind_int(stmt2, 1, discCode);
            
            while (sqlite3_step(stmt2) == SQLITE_ROW) {
                int workId = sqlite3_column_int(stmt2, 0);
                std::string workTitle = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 1));
                int authorId = sqlite3_column_int(stmt2, 2);
                int performerId = sqlite3_column_int(stmt2, 3);
                int workDiscCode = sqlite3_column_int(stmt2, 4);
                int trackNumber = sqlite3_column_int(stmt2, 5);
                int duration = sqlite3_column_int(stmt2, 6);
                std::string workCreateDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 7));
                std::string workLastUpdate = reinterpret_cast<const char*>(sqlite3_column_text(stmt2, 8));
                int workCreatedBy = sqlite3_column_int(stmt2, 9);
                
                works.push_back(std::make_unique<Models::MusicalWork>(
                    workId, workTitle, authorId, performerId, workDiscCode, trackNumber,
                    duration, workCreateDate, workLastUpdate, workCreatedBy));
            }
            
            sqlite3_finalize(stmt2);
        }
    }
    
    sqlite3_finalize(stmt1);
    return std::make_pair(std::move(disc), std::move(works));
}

// Реализация сохранения изображения компакт-диска
bool Database::saveDiscImage(int discCode, const std::vector<unsigned char>& imageData) {
    if (!connected) {
        return false;
    }
    
    const char* sql = "INSERT OR REPLACE INTO MUSIC_DISC_IMAGES (disc_code, image_data) VALUES (?, ?)";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, discCode);
    sqlite3_bind_blob(stmt, 2, imageData.data(), imageData.size(), SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return rc == SQLITE_DONE;
}

// Другие методы реализованы аналогично...

bool Database::executeQuery(const std::string& query) {
    if (!connected) {
        return false;
    }
    
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL ошибка: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}

bool Database::isInitialized() {
    if (!connected) {
        return false;
    }
    
    const char* sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='MUSIC_USERS'";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    bool initialized = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    
    return initialized;
}

bool Database::initializeDatabase() {
    if (!connected) {
        return false;
    }
    
    // Считываем SQL-скрипт из файла
    std::ifstream sqlFile("music_salon_db.sql");
    if (!sqlFile.is_open()) {
        std::cerr << "Не удалось открыть файл SQL-скрипта" << std::endl;
        return false;
    }
    
    std::stringstream buffer;
    buffer << sqlFile.rdbuf();
    std::string sql = buffer.str();
    sqlFile.close();
    
    // Выполняем скрипт
    return executeQuery(sql);
}

} // namespace Database
} // namespace MusicSalon