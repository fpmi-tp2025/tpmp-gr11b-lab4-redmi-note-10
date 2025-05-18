#pragma once

#include <string>
#include <chrono> 

namespace MusicSalon {
namespace Utils {

class DateUtils {
public:
    // Получение текущей даты в формате YYYY-MM-DD
    static std::string getCurrentDate();
    
    // Получение текущей даты и времени в формате YYYY-MM-DD HH:MM:SS
    static std::string getCurrentDateTime();
    
    // Проверка корректности даты в формате YYYY-MM-DD
    static bool isValidDate(const std::string& date);
    
    // Форматирование даты
    static std::string formatDate(const std::chrono::system_clock::time_point& timePoint);
    
    // Получение разницы между датами в днях
    static int getDaysDifference(const std::string& date1, const std::string& date2);
    
    // Добавление дней к дате
    static std::string addDays(const std::string& date, int days);
    
    // Сравнение дат (возвращает -1, если date1 < date2, 0, если date1 == date2, 1, если date1 > date2)
    static int compareDates(const std::string& date1, const std::string& date2);
};

} // namespace Utils
} // namespace MusicSalon