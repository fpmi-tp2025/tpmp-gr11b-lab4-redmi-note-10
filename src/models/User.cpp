#include "../../includes/models/User.h"
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

namespace MusicSalon {
namespace Models {

User::User(int userId, const std::string& username, const std::string& passwordHash,
           const std::string& fullName, const std::string& email, const std::string& role,
           const std::string& createDate, const std::string& lastLogin, bool isActive)
    : userId(userId), username(username), passwordHash(passwordHash),
      fullName(fullName), email(email), role(role),
      createDate(createDate), lastLogin(lastLogin), isActive(isActive) {
}

User::User(const std::string& username, const std::string& passwordHash,
           const std::string& fullName, const std::string& email, const std::string& role)
    : userId(-1), username(username), passwordHash(passwordHash),
      fullName(fullName), email(email), role(role),
      createDate(""), lastLogin(""), isActive(true) {
}

int User::getUserId() const {
    return userId;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPasswordHash() const {
    return passwordHash;
}

std::string User::getFullName() const {
    return fullName;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getRole() const {
    return role;
}

std::string User::getCreateDate() const {
    return createDate;
}

std::string User::getLastLogin() const {
    return lastLogin;
}

bool User::getIsActive() const {
    return isActive;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setPasswordHash(const std::string& passwordHash) {
    this->passwordHash = passwordHash;
}

void User::setFullName(const std::string& fullName) {
    this->fullName = fullName;
}

void User::setEmail(const std::string& email) {
    this->email = email;
}

void User::setRole(const std::string& role) {
    this->role = role;
}

void User::setLastLogin(const std::string& lastLogin) {
    this->lastLogin = lastLogin;
}

void User::setIsActive(bool isActive) {
    this->isActive = isActive;
}

std::string User::hashPassword(const std::string& password) {
    // Реализация SHA-256 хеширования
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    
    return ss.str();
}

bool User::verifyPassword(const std::string& password, const std::string& hash) {
    return hashPassword(password) == hash;
}

} // namespace Models
} // namespace MusicSalon