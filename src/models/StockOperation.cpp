#include "../../includes/models/StockOperation.h"

namespace MusicSalon {
namespace Models {

StockOperation::StockOperation(int operationId, const std::string& operationDate, 
                             const std::string& operationType, int discCode, int quantity,
                             double unitPrice, double totalPrice, int userId,
                             const std::string& createDate)
    : operationId(operationId), operationDate(operationDate), operationType(operationType),
      discCode(discCode), quantity(quantity), unitPrice(unitPrice), totalPrice(totalPrice),
      userId(userId), createDate(createDate) {
}

StockOperation::StockOperation(const std::string& operationDate, const std::string& operationType,
                             int discCode, int quantity, double unitPrice, double totalPrice)
    : operationId(-1), operationDate(operationDate), operationType(operationType),
      discCode(discCode), quantity(quantity), unitPrice(unitPrice), 
      totalPrice(totalPrice), userId(-1), createDate("") {
}

int StockOperation::getOperationId() const {
    return operationId;
}

std::string StockOperation::getOperationDate() const {
    return operationDate;
}

std::string StockOperation::getOperationType() const {
    return operationType;
}

int StockOperation::getDiscCode() const {
    return discCode;
}

int StockOperation::getQuantity() const {
    return quantity;
}

double StockOperation::getUnitPrice() const {
    return unitPrice;
}

double StockOperation::getTotalPrice() const {
    return totalPrice;
}

int StockOperation::getUserId() const {
    return userId;
}

std::string StockOperation::getCreateDate() const {
    return createDate;
}

void StockOperation::setOperationDate(const std::string& operationDate) {
    this->operationDate = operationDate;
}

void StockOperation::setOperationType(const std::string& operationType) {
    this->operationType = operationType;
}

void StockOperation::setDiscCode(int discCode) {
    this->discCode = discCode;
}

void StockOperation::setQuantity(int quantity) {
    this->quantity = quantity;
}

void StockOperation::setUnitPrice(double unitPrice) {
    this->unitPrice = unitPrice;
}

void StockOperation::setTotalPrice(double totalPrice) {
    this->totalPrice = totalPrice;
}

} // namespace Models
} // namespace MusicSalon