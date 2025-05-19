#pragma once

#include <memory>
#include "../../includes/database/Database.h"

// Минимальная заглушка для тестов Authentication
namespace MusicSalon {
namespace Mocks {

class MockDatabase {
public:
    MockDatabase() {}
    
    // Главный метод, необходимый для TestAuthentication
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
    
    // Заглушки для остальных методов, используемых в тестах
    MOCK_METHOD(std::vector<std::unique_ptr<Models::User>>, getAllUsers, (), ());
    MOCK_METHOD(bool, createUser, (const Models::User&), ());
    MOCK_METHOD(bool, updateUser, (const Models::User&), ());
    MOCK_METHOD(bool, deleteUser, (int), ());
    MOCK_METHOD(std::unique_ptr<Models::CompactDisc>, getDiscById, (int), ());
    MOCK_METHOD(std::vector<std::unique_ptr<Models::CompactDisc>>, getAllDiscs, (), ());
    MOCK_METHOD(bool, createDisc, (const Models::CompactDisc&, int), ());
    MOCK_METHOD(bool, updateDisc, (const Models::CompactDisc&), ());
    MOCK_METHOD(bool, deleteDisc, (int), ());
    MOCK_METHOD(std::unique_ptr<Models::Author>, getAuthorById, (int), ());
    MOCK_METHOD(std::vector<std::unique_ptr<Models::Author>>, getAllAuthors, (), ());
    MOCK_METHOD(bool, createAuthor, (const Models::Author&, int), ());
    MOCK_METHOD(bool, updateAuthor, (const Models::Author&), ());
    MOCK_METHOD(bool, deleteAuthor, (int), ());
    MOCK_METHOD(std::unique_ptr<Models::Performer>, getPerformerById, (int), ());
    MOCK_METHOD(std::vector<std::unique_ptr<Models::Performer>>, getAllPerformers, (), ());
    MOCK_METHOD(bool, createPerformer, (const Models::Performer&, int), ());
    MOCK_METHOD(bool, updatePerformer, (const Models::Performer&), ());
    MOCK_METHOD(bool, deletePerformer, (int), ());
    MOCK_METHOD(std::unique_ptr<Models::MusicalWork>, getWorkById, (int), ());
    MOCK_METHOD(std::vector<std::unique_ptr<Models::MusicalWork>>, getWorksByDiscId, (int), ());
    MOCK_METHOD(bool, createWork, (const Models::MusicalWork&, int), ());
    MOCK_METHOD(bool, updateWork, (const Models::MusicalWork&), ());
    MOCK_METHOD(bool, deleteWork, (int), ());
    MOCK_METHOD(bool, createStockOperation, (const Models::StockOperation&, int), ());
    MOCK_METHOD(std::vector<std::unique_ptr<Models::StockOperation>>, getOperationsByDiscId, (int), ());
    // Остальные заглушки...
};

} // namespace Mocks
} // namespace MusicSalon