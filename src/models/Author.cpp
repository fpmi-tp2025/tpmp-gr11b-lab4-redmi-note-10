#include "../../includes/models/Author.h"

namespace MusicSalon {
namespace Models {

Author::Author(int authorId, const std::string& name, const std::string& biography,
               const std::string& createDate, const std::string& lastUpdate, int createdBy)
    : authorId(authorId), name(name), biography(biography),
      createDate(createDate), lastUpdate(lastUpdate), createdBy(createdBy) {
}

Author::Author(const std::string& name, const std::string& biography)
    : authorId(-1), name(name), biography(biography),
      createDate(""), lastUpdate(""), createdBy(-1) {
}

int Author::getAuthorId() const {
    return authorId;
}

std::string Author::getName() const {
    return name;
}

std::string Author::getBiography() const {
    return biography;
}

std::string Author::getCreateDate() const {
    return createDate;
}

std::string Author::getLastUpdate() const {
    return lastUpdate;
}

int Author::getCreatedBy() const {
    return createdBy;
}

void Author::setName(const std::string& name) {
    this->name = name;
}

void Author::setBiography(const std::string& biography) {
    this->biography = biography;
}

void Author::setLastUpdate(const std::string& lastUpdate) {
    this->lastUpdate = lastUpdate;
}

} // namespace Models
} // namespace MusicSalon