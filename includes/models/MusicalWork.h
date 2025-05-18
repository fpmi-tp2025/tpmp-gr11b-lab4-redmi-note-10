#pragma once

#include <string>

namespace MusicSalon {
namespace Models {

class MusicalWork {
public:
    MusicalWork(int workId, const std::string& title, int authorId, int performerId,
                int discCode, int trackNumber, int duration, const std::string& createDate,
                const std::string& lastUpdate, int createdBy);
    
    // Конструктор без ID (для новых произведений)
    MusicalWork(const std::string& title, int authorId, int performerId,
                int discCode, int trackNumber = 0, int duration = 0);
    
    // Геттеры
    int getWorkId() const;
    std::string getTitle() const;
    int getAuthorId() const;
    int getPerformerId() const;
    int getDiscCode() const;
    int getTrackNumber() const;
    int getDuration() const;
    std::string getCreateDate() const;
    std::string getLastUpdate() const;
    int getCreatedBy() const;
    
    // Сеттеры
    void setTitle(const std::string& title);
    void setAuthorId(int authorId);
    void setPerformerId(int performerId);
    void setDiscCode(int discCode);
    void setTrackNumber(int trackNumber);
    void setDuration(int duration);
    void setLastUpdate(const std::string& lastUpdate);

private:
    int workId;
    std::string title;
    int authorId;
    int performerId;
    int discCode;
    int trackNumber;
    int duration; // в секундах
    std::string createDate;
    std::string lastUpdate;
    int createdBy;
};

} // namespace Models
} // namespace MusicSalon
