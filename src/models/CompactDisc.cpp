#include "../../includes/models/CompactDisc.h"

namespace MusicSalon {
namespace Models {

CompactDisc::CompactDisc(int discCode, const std::string& title, const std::string& manufactureDate,
                       const std::string& producer, double price, const std::string& createDate,
                       const std::string& lastUpdate, int createdBy)
    : discCode(discCode), title(title), manufactureDate(manufactureDate),
      producer(producer), price(price), createDate(createDate), 
      lastUpdate(lastUpdate), createdBy(createdBy) {
}

CompactDisc::CompactDisc(const std::string& title, const std::string& manufactureDate,
                        const std::string& producer, double price)
    : discCode(-1), title(title), manufactureDate(manufactureDate),
      producer(producer), price(price), createDate(""), lastUpdate(""), createdBy(-1) {
}

int CompactDisc::getDiscCode() const {
    return discCode;
}

std::string CompactDisc::getTitle() const {
    return title;
}

std::string CompactDisc::getManufactureDate() const {
    return manufactureDate;
}

std::string CompactDisc::getProducer() const {
    return producer;
}

double CompactDisc::getPrice() const {
    return price;
}

std::string CompactDisc::getCreateDate() const {
    return createDate;
}

std::string CompactDisc::getLastUpdate() const {
    return lastUpdate;
}

int CompactDisc::getCreatedBy() const {
    return createdBy;
}

void CompactDisc::setTitle(const std::string& title) {
    this->title = title;
}

void CompactDisc::setManufactureDate(const std::string& manufactureDate) {
    this->manufactureDate = manufactureDate;
}

void CompactDisc::setProducer(const std::string& producer) {
    this->producer = producer;
}

void CompactDisc::setPrice(double price) {
    this->price = price;
}

void CompactDisc::setLastUpdate(const std::string& lastUpdate) {
    this->lastUpdate = lastUpdate;
}

} // namespace Models
} // namespace MusicSalon