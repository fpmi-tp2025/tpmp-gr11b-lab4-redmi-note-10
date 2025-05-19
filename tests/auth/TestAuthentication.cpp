#include <gtest/gtest.h>
#include <memory>
#include "../../includes/auth/Authentication.h"
#include "../../includes/database/Database.h"
#include "../mock/MockDatabase.h"

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
    int result = auth->login("admin", "password");
    ASSERT_EQ(result, 1);
    ASSERT_TRUE(auth->isAdmin());
    ASSERT_EQ(auth->getCurrentUserId(), 1);
}

TEST_F(AuthenticationTest, LoginFailedWrongUsername) {
    int result = auth->login("nonexistent", "password");
    ASSERT_EQ(result, -1);
    ASSERT_FALSE(auth->isAdmin());
    ASSERT_EQ(auth->getCurrentUserId(), -1);
}

TEST_F(AuthenticationTest, LoginFailedWrongPassword) {
    int result = auth->login("user", "wrong_password");
    ASSERT_EQ(result, -1);
    ASSERT_FALSE(auth->isAdmin());
    ASSERT_EQ(auth->getCurrentUserId(), -1);
}

TEST_F(AuthenticationTest, LogoutWorks) {
    // Сначала выполняем успешный вход
    auth->login("admin", "password");
    
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
