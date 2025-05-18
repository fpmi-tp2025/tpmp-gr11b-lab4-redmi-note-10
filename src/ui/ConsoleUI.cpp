#include "../../includes/ui/ConsoleUI.h"
#include "../../includes/utils/InputUtils.h"
#include "../../includes/utils/DateUtils.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>

namespace MusicSalon {
namespace UI {

ConsoleUI::ConsoleUI(std::shared_ptr<Auth::Authentication> auth, 
                     std::shared_ptr<Database::Database> db)
    : auth(auth), db(db) {
}

void ConsoleUI::run() {
    bool running = true;
    
    while (running) {
        if (auth->getCurrentUserId() == -1) {
            if (!showLoginScreen()) {
                running = false;
                break;
            }
        }
        
        if (auth->isAdmin()) {
            showAdminMenu();
        } else {
            showCustomerMenu();
        }
    }
    
    std::cout << "Спасибо за использование Музыкального салона!" << std::endl;
}

bool ConsoleUI::showLoginScreen() {
    std::cout << "\n=== Музыкальный салон: Вход в систему ===" << std::endl;
    
    std::string username = Utils::InputUtils::getStringInput("Имя пользователя (или 'exit' для выхода): ");
    if (username == "exit") {
        return false;
    }
    
    std::string password = Utils::InputUtils::getPasswordInput("Пароль: ");
    
    int userId = auth->login(username, password);
    if (userId == -1) {
        std::cout << "Ошибка: Неверное имя пользователя или пароль." << std::endl;
        return true;
    }
    
    std::cout << "Вход успешно выполнен!" << std::endl;
    return true;
}

void ConsoleUI::showAdminMenu() {
    bool running = true;
    
    while (running) {
        std::cout << "\n=== Меню администратора ===" << std::endl;
        std::cout << "1. Управление компакт-дисками" << std::endl;
        std::cout << "2. Управление авторами" << std::endl;
        std::cout << "3. Управление исполнителями" << std::endl;
        std::cout << "4. Управление музыкальными произведениями" << std::endl;
        std::cout << "5. Управление складом (поступление/продажа)" << std::endl;
        std::cout << "6. Просмотр отчетов" << std::endl;
        std::cout << "0. Выйти из системы" << std::endl;
        
        int choice = Utils::InputUtils::getIntInput("Выберите опцию: ", 0, 6);
        
        switch (choice) {
            case 1:
                manageCompactDiscs();
                break;
            case 2:
                manageAuthors();
                break;
            case 3:
                managePerformers();
                break;
            case 4:
                manageMusicalWorks();
                break;
            case 5:
                manageStockOperations();
                break;
            case 6:
                viewReports();
                break;
            case 0:
                auth->logout();
                running = false;
                break;
        }
    }
}

void ConsoleUI::showCustomerMenu() {
    bool running = true;
    
    while (running) {
        std::cout << "\n=== Меню покупателя ===" << std::endl;
        std::cout << "1. Просмотр популярных компакт-дисков" << std::endl;
        std::cout << "2. Просмотр популярных исполнителей" << std::endl;
        std::cout << "0. Выйти из системы" << std::endl;
        
        int choice = Utils::InputUtils::getIntInput("Выберите опцию: ", 0, 2);
        
        switch (choice) {
            case 1:
                viewPopularDiscs();
                break;
            case 2:
                viewPopularPerformers();
                break;
            case 0:
                auth->logout();
                running = false;
                break;
        }
    }
}

void ConsoleUI::viewPopularDiscs() {
    std::cout << "\n=== Популярные компакт-диски ===" << std::endl;
    
    auto result = db->getMostPopularDisc();
    auto& disc = result.first;
    auto& works = result.second;
    
    if (!disc) {
        std::cout << "Нет данных о продажах компакт-дисков." << std::endl;
        return;
    }
    
    std::cout << "Самый популярный компакт-диск:" << std::endl;
    displayDisc(*disc);
    
    std::cout << "\nМузыкальные произведения на диске:" << std::endl;
    if (works.empty()) {
        std::cout << "  Нет данных о музыкальных произведениях." << std::endl;
    } else {
        for (const auto& work : works) {
            displayMusicalWork(*work);
        }
    }
    
    // Предложение экспорта в JSON
    if (Utils::InputUtils::confirm("\nЭкспортировать информацию в JSON?")) {
        exportDiscData(disc->getDiscCode(), "json");
    }
    
    Utils::InputUtils::getStringInput("\nНажмите Enter, чтобы продолжить...", true);
}

void ConsoleUI::displayDisc(const Models::CompactDisc& disc) {
    std::cout << "  Код: " << disc.getDiscCode() << std::endl;
    std::cout << "  Название: " << disc.getTitle() << std::endl;
    std::cout << "  Дата изготовления: " << disc.getManufactureDate() << std::endl;
    std::cout << "  Производитель: " << disc.getProducer() << std::endl;
    std::cout << "  Цена: " << std::fixed << std::setprecision(2) << disc.getPrice() << std::endl;
}

void ConsoleUI::exportDiscData(int discCode, const std::string& format) {
    auto disc = db->getDiscById(discCode);
    if (!disc) {
        std::cout << "Ошибка: Компакт-диск не найден." << std::endl;
        return;
    }
    
    auto works = db->getWorksByDiscId(discCode);
    
    if (format == "json") {
        nlohmann::json j;
        j["disc_code"] = disc->getDiscCode();
        j["title"] = disc->getTitle();
        j["manufacture_date"] = disc->getManufactureDate();
        j["producer"] = disc->getProducer();
        j["price"] = disc->getPrice();
        
        nlohmann::json worksJson = nlohmann::json::array();
        for (const auto& work : works) {
            nlohmann::json workJson;
            workJson["work_id"] = work->getWorkId();
            workJson["title"] = work->getTitle();
            workJson["author_id"] = work->getAuthorId();
            workJson["performer_id"] = work->getPerformerId();
            workJson["track_number"] = work->getTrackNumber();
            workJson["duration"] = work->getDuration();
            worksJson.push_back(workJson);
        }
        j["works"] = worksJson;
        
        std::string filename = "disc_" + std::to_string(discCode) + ".json";
        std::ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4); // Pretty printing with 4 spaces
            file.close();
            std::cout << "Данные экспортированы в " << filename << std::endl;
        } else {
            std::cout << "Ошибка: Не удалось создать файл " << filename << std::endl;
        }
    } else if (format == "xml") {
        // Реализация экспорта в XML
        std::string filename = "disc_" + std::to_string(discCode) + ".xml";
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            file << "<disc>\n";
            file << "  <disc_code>" << disc->getDiscCode() << "</disc_code>\n";
            file << "  <title>" << disc->getTitle() << "</title>\n";
            file << "  <manufacture_date>" << disc->getManufactureDate() << "</manufacture_date>\n";
            file << "  <producer>" << disc->getProducer() << "</producer>\n";
            file << "  <price>" << disc->getPrice() << "</price>\n";
            file << "  <works>\n";
            
            for (const auto& work : works) {
                file << "    <work>\n";
                file << "      <work_id>" << work->getWorkId() << "</work_id>\n";
                file << "      <title>" << work->getTitle() << "</title>\n";
                file << "      <author_id>" << work->getAuthorId() << "</author_id>\n";
                file << "      <performer_id>" << work->getPerformerId() << "</performer_id>\n";
                file << "      <track_number>" << work->getTrackNumber() << "</track_number>\n";
                file << "      <duration>" << work->getDuration() << "</duration>\n";
                file << "    </work>\n";
            }
            
            file << "  </works>\n";
            file << "</disc>";
            file.close();
            std::cout << "Данные экспортированы в " << filename << std::endl;
        } else {
            std::cout << "Ошибка: Не удалось создать файл " << filename << std::endl;
        }
    } else {
        std::cout << "Ошибка: Неподдерживаемый формат " << format << std::endl;
    }
}

// Другие методы реализуются аналогично
} // namespace UI
} // namespace MusicSalon