#include <iostream>
#include <memory>
#include "../includes/auth/Authentication.h"
#include "../includes/database/Database.h"
#include "../includes/ui/ConsoleUI.h"

int main(int argc, char* argv[]) {
    std::string dbPath = "music_salon.db";
    
    if (argc > 1) {
        dbPath = argv[1];
    }
    
    std::cout << "=== Музыкальный салон: Система управления ===" << std::endl;
    std::cout << "Версия: 1.0.0" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::cout << "Подключение к базе данных: " << dbPath << std::endl;
    auto db = std::make_shared<MusicSalon::Database::Database>(dbPath);
    auto auth = std::make_shared<MusicSalon::Auth::Authentication>(db);
    
    MusicSalon::UI::ConsoleUI ui(auth, db);
    ui.run();
    
    return 0;
}