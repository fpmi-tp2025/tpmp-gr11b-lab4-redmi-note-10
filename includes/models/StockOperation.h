#pragma once

#include <string> 

namespace MusicSalon {
namespace Models {

class StockOperation {
public:
    StockOperation(int operationId, const std::string& operationDate, 
                  const std::string& operationType, int discCode, int quantity,
                  double unitPrice, double totalPrice, int userId,
                  const std::string& createDate);
    
    // Конструктор без ID (для новых операций)
    StockOperation(const std::string& operationDate, const std::string& operationType,
                  int discCode, int quantity, double unitPrice = 0.0, double totalPrice = 0.0);
    
    // Геттеры
    int getOperationId() const;
    std::string getOperationDate() const;
    std::string getOperationType() const;
    int getDiscCode() const;
    int getQuantity() const;
    double getUnitPrice() const;
    double getTotalPrice() const;
    int getUserId() const;
    std::string getCreateDate() const;
    
    // Сеттеры
    void setOperationDate(const std::string& operationDate);
    void setOperationType(const std::string& operationType);
    void setDiscCode(int discCode);
    void setQuantity(int quantity);
    void setUnitPrice(double unitPrice);
    void setTotalPrice(double totalPrice);

private:
    int operationId;
    std::string operationDate;
    std::string operationType;
    int discCode;
    int quantity;
    double unitPrice;
    double totalPrice;
    int userId;
    std::string createDate;
};

} // namespace Models
} // namespace MusicSalon
