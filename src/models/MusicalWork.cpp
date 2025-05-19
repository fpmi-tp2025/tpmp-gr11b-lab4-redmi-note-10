#include "../../includes/models/MusicalWork.h"

namespace MusicSalon {
namespace Models {

MusicalWork::MusicalWork(int workId, const std::string& title, int authorId, int performerId,
                       int discCode, int trackNumber, int duration, const std::string& createDate,
                       const std::string& lastUpdate, int createdBy)
    : workId(workId), title(title), authorId(authorId), performerId(performerId),
      discCode(discCode), trackNumber(trackNumber), duration(duration),
      createDate(createDate), lastUpdate(lastUpdate), createdBy(createdBy) {
}

MusicalWork::MusicalWork(const std::string& title, int authorId, int performerId,
                       int discCode, int trackNumber, int duration)
    : workId(-1), title(title), authorId(authorId), performerId(performerId),
      discCode(discCode), trackNumber(trackNumber), duration(duration),
      createDate(""), lastUpdate(""), createdBy(-1) {
}

int MusicalWork::getWorkId() const {
    return workId;
}

std::string MusicalWork::getTitle() const {
    return title;
}

int MusicalWork::getAuthorId() const {
    return authorId;
}

int MusicalWork::getPerformerId() const {
    return performerId;
}

int MusicalWork::getDiscCode() const {
    return discCode;
}

int MusicalWork::getTrackNumber() const {
    return trackNumber;
}

int MusicalWork::getDuration() const {
    return duration;
}

std::string MusicalWork::getCreateDate() const {
    return createDate;
}

std::string MusicalWork::getLastUpdate() const {
    return lastUpdate;
}

int MusicalWork::getCreatedBy() const {
    return createdBy;
}

void MusicalWork::setTitle(const std::string& title) {
    this->title = title;
}

void MusicalWork::setAuthorId(int authorId) {
    this->authorId = authorId;
}

void MusicalWork::setPerformerId(int performerId) {
    this->performerId = performerId;
}

void MusicalWork::setDiscCode(int discCode) {
    this->discCode = discCode;
}

void MusicalWork::setTrackNumber(int trackNumber) {
    this->trackNumber = trackNumber;
}

void MusicalWork::setDuration(int duration) {
    this->duration = duration;
}

void MusicalWork::setLastUpdate(const std::string& lastUpdate) {
    this->lastUpdate = lastUpdate;
}

} // namespace Models
} // namespace MusicSalon