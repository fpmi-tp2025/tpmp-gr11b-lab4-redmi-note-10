#pragma once

#include <string>

namespace MusicSalon {
namespace Models {

class User {
public:
    User(int userId, const std::string& username, const std::string& passwordHash,
         const std::string& fullName, const std::string& email, const std::string& role,
         const std::string& createDate, const std::string& lastLogin, bool isActive);
    
    // Конструктор без ID (для новых пользователей)
    User(const std::string& username, const std::string& passwordHash,
         const std::string& fullName, const std::string& email, const std::string& role);
    
    // Геттеры
    int getUserId() const;
    std::string getUsername() const;
    std::string getPasswordHash() const;
    std::string getFullName() const;
    std::string getEmail() const;
    std::string getRole() const;
    std::string getCreateDate() const;
    std::string getLastLogin() const;
    bool getIsActive() const;
    
    // Сеттеры
    void setUsername(const std::string& username);
    void setPasswordHash(const std::string& passwordHash);
    void setFullName(const std::string& fullName);
    void setEmail(const std::string& email);
    void setRole(const std::string& role);
    void setLastLogin(const std::string& lastLogin);
    void setIsActive(bool isActive);
    
    // Статические методы
    static std::string hashPassword(const std::string& password);
    static bool verifyPassword(const std::string& password, const std::string& hash);

private:
    int userId;
    std::string username;
    std::string passwordHash;
    std::string fullName;
    std::string email;
    std::string role;
    std::string createDate;
    std::string lastLogin;
    bool isActive;
};

} // namespace Models
} // namespace MusicSalon