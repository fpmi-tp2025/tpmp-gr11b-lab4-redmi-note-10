
#pragma once

#include <string>


namespace MusicSalon {
namespace Models {


class CompactDisc {
public:
    CompactDisc(int discCode, const std::string& title, const std::string& manufactureDate,
               const std::string& producer, double price, const std::string& createDate,
               const std::string& lastUpdate, int createdBy);
    
    // Конструктор без ID (для новых дисков)
    CompactDisc(const std::string& title, const std::string& manufactureDate,
                const std::string& producer, double price);
    
    // Геттеры
    int getDiscCode() const;
    std::string getTitle() const;
    std::string getManufactureDate() const;
    std::string getProducer() const;
    double getPrice() const;
    std::string getCreateDate() const;
    std::string getLastUpdate() const;
    int getCreatedBy() const;
    
    // Сеттеры
    void setTitle(const std::string& title);
    void setManufactureDate(const std::string& manufactureDate);
    void setProducer(const std::string& producer);
    void setPrice(double price);
    void setLastUpdate(const std::string& lastUpdate);

private:
    int discCode;
    std::string title;
    std::string manufactureDate;
    std::string producer;
    double price;
    std::string createDate;
    std::string lastUpdate;
    int createdBy;
};

} // namespace Models
} // namespace MusicSalon