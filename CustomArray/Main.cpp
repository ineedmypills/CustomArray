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

            std::cout << "���� 1: ���������� � ���� � �������� �������: "
                << (arr == arr2 ? "OK" : "FAIL")
                << "\n����������� ������: " << arr2 << "\n\n";
        }

        {
            std::cout << "���� 2: ����������� � ����: ";
            CustomArray arr{ 1, 3, 5, 7 };
            CustomArray arrTemp=arr;
            arr.moveToFile("test2.txt");
            
           
            std::cout << (arr.size() == 0 ? "OK" : "FAIL") << "\n����: " << arrTemp << "\n�����: " << arr << "\n\n";
        }

        {
            CustomArray arr("test1.txt");
            std::cout << "���� 3: ����������� �� �����:\n������ �� �����: " << arr << "\n\n";
        }

        {
            try {
                CustomArray arr("invalid_file.txt");
            }
            catch (const std::exception& e) {
                std::cout << "���� 4: ������ ������: OK\n������: " << e.what() << "\n\n";
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "����������� ������: " << e.what() << "\n";
        return 1;
    }

    return 0;
}