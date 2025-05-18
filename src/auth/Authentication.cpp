#include "../../includes/auth/Authentication.h"
#include "../../includes/models/User.h"
#include <iostream>

namespace MusicSalon {
namespace Auth {

Authentication::Authentication(std::shared_ptr<Database::Database> db)
    : db(db), currentUserId(-1), admin(false) {
}

int Authentication::login(const std::string& username, const std::string& password) {
    auto user = db->getUserByUsername(username);
    if (!user) {
        return -1;
    }
    
    if (!user->getIsActive()) {
        return -1;
    }
    
    if (!Models::User::verifyPassword(password, user->getPasswordHash())) {
        return -1;
    }
    
    currentUserId = user->getUserId();
    admin = (user->getRole() == "administrator");
    
    return currentUserId;
}

bool Authentication::isAdmin() const {
    return admin;
}

int Authentication::getCurrentUserId() const {
    return currentUserId;
}

void Authentication::logout() {
    currentUserId = -1;
    admin = false;
}

} // namespace Auth
} // namespace MusicSalon