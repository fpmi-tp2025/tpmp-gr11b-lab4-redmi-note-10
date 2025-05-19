#pragma once

#include <gmock/gmock.h>
#include "../../includes/database/Database.h"

namespace MusicSalon {
namespace Mocks {

// Сделать макросы в стиле Google Mock работать с вашей версией GMock
#define MOCK_METHOD1(name, return_type) \
  MOCK_METHOD(return_type, name, (const std::string&), (override))

#define MOCK_METHOD0(name, return_type) \
  MOCK_METHOD(return_type, name, (), (override))

// Важное изменение: наследуемся от Database
class MockDatabase : public Database::Database {
public:
    // Используем конструктор базового класса
    MockDatabase() : Database::Database("") {}
    
    // Используем макросы старого стиля Google Mock вместо нового MOCK_METHOD
    MOCK_METHOD1(getUserByUsername, std::unique_ptr<Models::User>);
    MOCK_METHOD0(getAllUsers, std::vector<std::unique_ptr<Models::User>>);
    MOCK_METHOD1(createUser, bool);
    MOCK_METHOD1(updateUser, bool);
    MOCK_METHOD1(deleteUser, bool);
    
    // Возвращаем минимальную реализацию для getUserByUsername, чтобы тесты могли проходить
    std::unique_ptr<Models::User> getUserByUsername(const std::string& username) override {
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
        }
        return nullptr;
    }
};

} // namespace Mocks
} // namespace MusicSalon
