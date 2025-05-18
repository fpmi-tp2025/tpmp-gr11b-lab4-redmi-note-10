#pragma once

#include <memory>
#include "../auth/Authentication.h"
#include "../database/Database.h"

namespace MusicSalon {
namespace UI {

class ConsoleUI {
public:
    ConsoleUI(std::shared_ptr<Auth::Authentication> auth, 
              std::shared_ptr<Database::Database> db);
    
    // Запуск приложения
    void run();

private:
    std::shared_ptr<Auth::Authentication> auth;
    std::shared_ptr<Database::Database> db;
    
    // Отображение экрана входа
    bool showLoginScreen();
    
    // Отображение меню администратора
    void showAdminMenu();
    
    // Отображение меню покупателя
    void showCustomerMenu();
    
    // Операции администратора
    void manageCompactDiscs();
    void manageAuthors();
    void managePerformers();
    void manageMusicalWorks();
    void manageStockOperations();
    void viewReports();
    
    // Операции покупателя
    void viewPopularDiscs();
    void viewPopularPerformers();
    
    // Вспомогательные методы
    void displayDisc(const Models::CompactDisc& disc);
    void displayAuthor(const Models::Author& author);
    void displayPerformer(const Models::Performer& performer);
    void displayMusicalWork(const Models::MusicalWork& work);
    void displayStockOperation(const Models::StockOperation& operation);
    
    // Работа с изображениями
    void uploadDiscImage(int discCode);
    void exportDiscData(int discCode, const std::string& format);
};

} // namespace UI
} // namespace MusicSalon
