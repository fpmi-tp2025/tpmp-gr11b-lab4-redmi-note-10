#pragma once

#include <string>
#include <vector>

namespace MusicSalon {
namespace Utils {

class InputUtils {
public:
    // Получение строки от пользователя
    static std::string getStringInput(const std::string& prompt, bool allowEmpty = false);
    
    // Получение целого числа в заданном диапазоне
    static int getIntInput(const std::string& prompt, int min = 0, int max = 100);
    
    // Получение вещественного числа в заданном диапазоне
    static double getDoubleInput(const std::string& prompt, double min = 0.0, double max = 1000.0);
    
    // Получение пароля (без отображения вводимых символов)
    static std::string getPasswordInput(const std::string& prompt);
    
    // Получение даты в формате YYYY-MM-DD
    static std::string getDateInput(const std::string& prompt);
    
    // Выбор элемента из списка
    static int getChoice(const std::string& prompt, const std::vector<std::string>& options);
    
    // Запрос подтверждения действия (да/нет)
    static bool confirm(const std::string& prompt);
};

} // namespace Utils
} // namespace MusicSalon
