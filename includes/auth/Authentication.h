#pragma once

#include <string>
#include <memory>
#include "../database/Database.h"

namespace MusicSalon {
namespace Auth {

class Authentication {
public:
    Authentication(std::shared_ptr<Database::Database> db);
    
    // Логин и получение ID пользователя, возвращает -1 при неудаче
    int login(const std::string& username, const std::string& password);
    
    // Проверка, является ли текущий пользователь администратором
    bool isAdmin() const;
    
    // Получение ID текущего пользователя
    int getCurrentUserId() const;
    
    // Выход из системы
    void logout();

private:
    std::shared_ptr<Database::Database> db;
    int currentUserId;
    bool admin;
};

} // namespace Auth
} // namespace MusicSalon