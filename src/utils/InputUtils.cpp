#include "../../includes/utils/InputUtils.h"
#include <iostream>
#include <limits>

namespace MusicSalon {
namespace Utils {

std::string InputUtils::getStringInput(const std::string& prompt, bool allowEmpty) {
    std::string input;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (input.empty() && !allowEmpty) {
            std::cout << "Ввод не может быть пустым. Пожалуйста, попробуйте снова." << std::endl;
        } else {
            break;
        }
    }
    
    return input;
}

int InputUtils::getIntInput(const std::string& prompt, int min, int max) {
    int input;
    std::string inputStr;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, inputStr);
        
        try {
            input = std::stoi(inputStr);
            
            if (input < min || input > max) {
                std::cout << "Ввод должен быть между " << min << " и " << max << ". Пожалуйста, попробуйте снова." << std::endl;
            } else {
                break;
            }
        } catch (const std::exception&) {
            std::cout << "Неверный ввод. Пожалуйста, введите целое число." << std::endl;
        }
    }
    
    return input;
}

double InputUtils::getDoubleInput(const std::string& prompt, double min, double max) {
    double input;
    std::string inputStr;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, inputStr);
        
        try {
            input = std::stod(inputStr);
            
            if (input < min || input > max) {
                std::cout << "Ввод должен быть между " << min << " и " << max << ". Пожалуйста, попробуйте снова." << std::endl;
            } else {
                break;
            }
        } catch (const std::exception&) {
            std::cout << "Неверный ввод. Пожалуйста, введите число." << std::endl;
        }
    }
    
    return input;
}

std::string InputUtils::getPasswordInput(const std::string& prompt) {
    // В консольном приложении без специальных библиотек мы не можем скрыть ввод
    // В реальном приложении здесь был бы использован системно-зависимый код для скрытия ввода
    std::string password;
    std::cout << prompt;
    std::getline(std::cin, password);
    return password;
}

std::string InputUtils::getDateInput(const std::string& prompt) {
    std::string date;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, date);
        
        // Простая проверка формата YYYY-MM-DD
        if (date.length() == 10 && date[4] == '-' && date[7] == '-') {
            break;
        } else {
            std::cout << "Неверный формат даты. Используйте формат YYYY-MM-DD." << std::endl;
        }
    }
    
    return date;
}

int InputUtils::getChoice(const std::string& prompt, const std::vector<std::string>& options) {
    std::cout << prompt << std::endl;
    
    for (size_t i = 0; i < options.size(); i++) {
        std::cout << (i + 1) << ". " << options[i] << std::endl;
    }
    
    return getIntInput("Выберите опцию: ", 1, options.size()) - 1;
}

bool InputUtils::confirm(const std::string& prompt) {
    std::string input;
    
    while (true) {
        std::cout << prompt << " (д/н): ";
        std::getline(std::cin, input);
        
        if (input == "д" || input == "Д" || input == "y" || input == "Y" || input == "yes" || input == "да") {
            return true;
        } else if (input == "н" || input == "Н" || input == "n" || input == "N" || input == "no" || input == "нет") {
            return false;
        } else {
            std::cout << "Пожалуйста, ответьте 'д' (да) или 'н' (нет)." << std::endl;
        }
    }
}

} // namespace Utils
} // namespace MusicSalon