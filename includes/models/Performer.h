
#pragma once

#include <string>


namespace MusicSalon {
namespace Models {

class Performer {
public:
    Performer(int performerId, const std::string& name, const std::string& genre,
              const std::string& biography, const std::string& createDate,
              const std::string& lastUpdate, int createdBy);
    
    // Конструктор без ID (для новых исполнителей)
    Performer(const std::string& name, const std::string& genre = "", 
              const std::string& biography = "");
    
    // Геттеры
    int getPerformerId() const;
    std::string getName() const;
    std::string getGenre() const;
    std::string getBiography() const;
    std::string getCreateDate() const;
    std::string getLastUpdate() const;
    int getCreatedBy() const;
    
    // Сеттеры
    void setName(const std::string& name);
    void setGenre(const std::string& genre);
    void setBiography(const std::string& biography);
    void setLastUpdate(const std::string& lastUpdate);

private:
    int performerId;
    std::string name;
    std::string genre;
    std::string biography;
    std::string createDate;
    std::string lastUpdate;
    int createdBy;
};

} // namespace Models
} // namespace MusicSalon