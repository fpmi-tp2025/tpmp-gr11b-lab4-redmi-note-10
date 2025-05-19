#include "../../includes/database/Database.h"
#include <iostream>

namespace MusicSalon {
namespace Database {

// Заглушки для методов, используемых в ConsoleUI
std::unique_ptr<Models::CompactDisc> Database::getDiscById(int discCode) {
    // Просто создаем пустой диск с заданным кодом
    return std::make_unique<Models::CompactDisc>(
        discCode, "Заглушка диска", "2023-01-01", "Тестовый производитель", 
        9.99, "2023-01-01", "2023-01-01", 1
    );
}

std::vector<std::unique_ptr<Models::MusicalWork>> Database::getWorksByDiscId(int discCode) {
    // Возвращаем пустой вектор работ
    std::vector<std::unique_ptr<Models::MusicalWork>> works;
    
    // Для примера добавляем одну тестовую работу
    works.push_back(std::make_unique<Models::MusicalWork>(
        1, "Тестовый трек", 1, 1, discCode, 1, 180, "2023-01-01", "2023-01-01", 1
    ));
    
    return works;
}

} // namespace Database
} // namespace MusicSalon
