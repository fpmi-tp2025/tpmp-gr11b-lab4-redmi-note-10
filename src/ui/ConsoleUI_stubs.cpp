#include "../../includes/ui/ConsoleUI.h"
#include <iostream>

namespace MusicSalon {
namespace UI {

// Простые заглушки для методов, вызываемых в меню
void ConsoleUI::manageCompactDiscs() {
    std::cout << "Функция управления компакт-дисками еще не реализована." << std::endl;
}

void ConsoleUI::manageAuthors() {
    std::cout << "Функция управления авторами еще не реализована." << std::endl;
}

void ConsoleUI::managePerformers() {
    std::cout << "Функция управления исполнителями еще не реализована." << std::endl;
}

void ConsoleUI::manageMusicalWorks() {
    std::cout << "Функция управления музыкальными произведениями еще не реализована." << std::endl;
}

void ConsoleUI::manageStockOperations() {
    std::cout << "Функция управления складскими операциями еще не реализована." << std::endl;
}

void ConsoleUI::viewReports() {
    std::cout << "Функция просмотра отчетов еще не реализована." << std::endl;
}

void ConsoleUI::viewPopularPerformers() {
    std::cout << "Функция просмотра популярных исполнителей еще не реализована." << std::endl;
}

void ConsoleUI::displayMusicalWork(const Models::MusicalWork& work) {
    std::cout << "  ID: " << work.getWorkId() << std::endl;
    std::cout << "  Название: " << work.getTitle() << std::endl;
    std::cout << "  ID автора: " << work.getAuthorId() << std::endl;
    std::cout << "  ID исполнителя: " << work.getPerformerId() << std::endl;
    std::cout << "  Номер трека: " << work.getTrackNumber() << std::endl;
    std::cout << "  Длительность: " << work.getDuration() << " сек." << std::endl;
}

} // namespace UI
} // namespace MusicSalon