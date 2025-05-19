#pragma once

#include <gmock/gmock.h>
#include "../../includes/database/Database.h"

namespace MusicSalon {
namespace Mocks {

// Заглушка с наследованием от Database
class MockDatabase : public Database::Database {
public:
    // Используем конструктор базового класса
    MockDatabase() : Database::Database("") {}
    
    // Метод не виртуальный в базовом классе, поэтому не используем override
    std::unique_ptr<Models::User> getUserByUsername(const std::string& username) {
        if (username == "admin") {
            return std::make_unique<Models::User>(
                1, "admin", "hash_of_password", "Admin User", "admin@example.com", 
                "administrator", "2023-01-01", "", true
            );
        } else if (username == "user") {
            return std::make_unique<Models::User>(
                2, "user", "hash_of_different_password", "Regular User", "user@example.com", 
                "customer", "2023-01-01", "", true
            );
        } else if (username == "inactive") {
            auto user = std::make_unique<Models::User>(
                3, "inactive", "hash", "Inactive User", "inactive@example.com", 
                "customer", "2023-01-01", "", false
            );
            return user;
        }
        return nullptr;
    }
};

} // namespace Mocks
} // namespace MusicSalon
