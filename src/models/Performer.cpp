#include "../../includes/models/Performer.h"

namespace MusicSalon {
namespace Models {

Performer::Performer(int performerId, const std::string& name, const std::string& genre,
                   const std::string& biography, const std::string& createDate,
                   const std::string& lastUpdate, int createdBy)
    : performerId(performerId), name(name), genre(genre), biography(biography),
      createDate(createDate), lastUpdate(lastUpdate), createdBy(createdBy) {
}

Performer::Performer(const std::string& name, const std::string& genre, 
                   const std::string& biography)
    : performerId(-1), name(name), genre(genre), biography(biography),
      createDate(""), lastUpdate(""), createdBy(-1) {
}

int Performer::getPerformerId() const {
    return performerId;
}

std::string Performer::getName() const {
    return name;
}

std::string Performer::getGenre() const {
    return genre;
}

std::string Performer::getBiography() const {
    return biography;
}

std::string Performer::getCreateDate() const {
    return createDate;
}

std::string Performer::getLastUpdate() const {
    return lastUpdate;
}

int Performer::getCreatedBy() const {
    return createdBy;
}

void Performer::setName(const std::string& name) {
    this->name = name;
}

void Performer::setGenre(const std::string& genre) {
    this->genre = genre;
}

void Performer::setBiography(const std::string& biography) {
    this->biography = biography;
}

void Performer::setLastUpdate(const std::string& lastUpdate) {
    this->lastUpdate = lastUpdate;
}

} // namespace Models
} // namespace MusicSalon