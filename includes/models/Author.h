
#pragma once

#include <string>


namespace MusicSalon {
namespace Models {


class Author {
public:
    Author(int authorId, const std::string& name, const std::string& biography,
           const std::string& createDate, const std::string& lastUpdate, int createdBy);
    
    // Конструктор без ID (для новых авторов)
    Author(const std::string& name, const std::string& biography = "");
    
    // Геттеры
    int getAuthorId() const;
    std::string getName() const;
    std::string getBiography() const;
    std::string getCreateDate() const;
    std::string getLastUpdate() const;
    int getCreatedBy() const;
    
    // Сеттеры
    void setName(const std::string& name);
    void setBiography(const std::string& biography);
    void setLastUpdate(const std::string& lastUpdate);

private:
    int authorId;
    std::string name;
    std::string biography;
    std::string createDate;
    std::string lastUpdate;
    int createdBy;
};

} // namespace Models
} // namespace MusicSalon