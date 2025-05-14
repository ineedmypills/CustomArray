#include "CustomArray.hpp"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        {
            CustomArray arr{ 10, 20, 30, 40, 50 };
            arr.saveToFile("test1.txt");

            CustomArray arr2 (5);
            arr2.loadFromFile("test1.txt");

            std::cout << "Тест 1: Сохранение в файл и загрузка обратно: "
                << (arr == arr2 ? "OK" : "FAIL")
                << "\nЗагруженный массив: " << arr2 << "\n\n";
        }

        {
            std::cout << "Тест 2: Перемещение в файл: ";
            CustomArray arr{ 1, 3, 5, 7 };
            CustomArray arrTemp=arr;
            arr.moveToFile("test2.txt");
            
           
            std::cout << (arr.size() == 0 ? "OK" : "FAIL") << "\nБыло: " << arrTemp << "\nСтало: " << arr << "\n\n";
        }

        {
            CustomArray arr("test1.txt");
            std::cout << "Тест 3: Конструктор из файла:\nМассив из файла: " << arr << "\n\n";
        }

        {
            try {
                CustomArray arr("invalid_file.txt");
            }
            catch (const std::exception& e) {
                std::cout << "Тест 4: Ошибка чтения: OK\nОшибка: " << e.what() << "\n\n";
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}