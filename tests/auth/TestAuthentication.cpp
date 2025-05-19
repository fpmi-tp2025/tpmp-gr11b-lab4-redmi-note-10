#include <gtest/gtest.h>
#include <memory>
#include "../../includes/auth/Authentication.h"
#include "../../includes/database/Database.h"
#include "../mock/MockDatabase.h"

using ::testing::Return;
using ::testing::_;

namespace MusicSalon {
namespace Tests {

class AuthenticationTest : public ::testing::Test {
protected:
    void SetUp() override {
        mockDb = std::make_shared<Mocks::MockDatabase>();
        auth = std::make_unique<Auth::Authentication>(mockDb);
    }
    
    void TearDown() override {
        auth.reset();
        mockDb.reset();
    }
    
    std::shared_ptr<Mocks::MockDatabase> mockDb;
    std::unique_ptr<Auth::Authentication> auth;
};

TEST_F(AuthenticationTest, LoginSuccessAsAdmin) {
    // Подготовка тестового пользователя-администратора
    auto user = std::make_unique<Models::User>(
        1, "admin", "hash_of_password", "Admin User", "admin@example.com", 
        "administrator", "2023-01-01", "", true);
    
    // Настройка мока базы данных
    EXPECT_CALL(*mockDb, getUserByUsername("admin"))
        .WillOnce(Return(std::move(user)));
    
    // Переопределение статической функции верификации пароля
    // (в реальном тесте можно использовать Mock для Models::User)
    testing::internal::CaptureStdout();
    int result = auth->login("admin", "password");
    testing::internal::GetCapturedStdout();
    
    ASSERT_EQ(result, 1);
    ASSERT_TRUE(auth->isAdmin());
    ASSERT_EQ(auth->getCurrentUserId(), 1);
}

TEST_F(AuthenticationTest, LoginFailedWrongUsername) {
    // Настройка мока базы данных для возврата nullptr (пользователь не найден)
    EXPECT_CALL(*mockDb, getUserByUsername("nonexistent"))
        .WillOnce(Return(nullptr));
    
    int result = auth->login("nonexistent", "password");
    
    ASSERT_EQ(result, -1);
    ASSERT_FALSE(auth->isAdmin());
    ASSERT_EQ(auth->getCurrentUserId(), -1);
}

TEST_F(AuthenticationTest, LoginFailedWrongPassword) {
    // Подготовка тестового пользователя
    auto user = std::make_unique<Models::User>(
        2, "user", "hash_of_different_password", "Regular User", "user@example.com", 
        "customer", "2023-01-01", "", true);
    
    // Настройка мока базы данных
    EXPECT_CALL(*mockDb, getUserByUsername("user"))
        .WillOnce(Return(std::move(user)));
    
    // Переопределение статической функции верификации пароля
    // (в реальном тесте можно использовать Mock для Models::User)
    testing::internal::CaptureStdout();
    int result = auth->login("user", "wrong_password");
    testing::internal::GetCapturedStdout();
    
    ASSERT_EQ(result, -1);
    ASSERT_FALSE(auth->isAdmin());
    ASSERT_EQ(auth->getCurrentUserId(), -1);
}

TEST_F(AuthenticationTest, LogoutWorks) {
    // Сначала выполняем успешный вход
    auto user = std::make_unique<Models::User>(
        1, "admin", "hash_of_password", "Admin User", "admin@example.com", 
        "administrator", "2023-01-01", "", true);
    
    EXPECT_CALL(*mockDb, getUserByUsername("admin"))
        .WillOnce(Return(std::move(user)));
    
    testing::internal::CaptureStdout();
    auth->login("admin", "password");
    testing::internal::GetCapturedStdout();
    
    // Проверяем, что пользователь вошел
    ASSERT_EQ(auth->getCurrentUserId(), 1);
    
    // Выполняем выход
    auth->logout();
    
    // Проверяем, что пользователь вышел
    ASSERT_EQ(auth->getCurrentUserId(), -1);
    ASSERT_FALSE(auth->isAdmin());
}

} // namespace Tests
} // namespace MusicSalon
