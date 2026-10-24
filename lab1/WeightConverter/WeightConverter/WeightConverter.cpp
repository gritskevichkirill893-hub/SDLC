#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <windows.h>


#undef max
#undef min

using namespace std;

// Структура для хранения информации о единицах измерения
struct Unit {
    string name;
    double weightInKg;
};

// Список всех поддерживаемых единиц измерения
vector<Unit> units = {
    {"Фунт", 0.45359237},
    {"Килограмм", 1.0},
    {"Белый медведь", 450.0},
    {"Африканский слон", 6000.0},
    {"Жигули", 1000.0},
    {"Банка пива", 0.5},
    {"Цыпленок", 1.5},
    {"Лист бумаги", 0.005}
};

// Функция конвертации веса
double convertWeight(double value, int from, int to) {
    double kg = value * units[from].weightInKg;
    return kg / units[to].weightInKg;
}

// Отображение списка единиц измерения
void displayUnitsList() {
    cout << "\nДоступные единицы измерения:\n";
    cout << "----------------------------------------" << endl;
    for (size_t i = 0; i < units.size(); i++) {
        cout << setw(3) << (i + 1) << ". " << setw(20) << left
            << units[i].name << " (" << units[i].weightInKg << " кг)" << endl;
    }
    cout << "----------------------------------------" << endl;
}

// Очистка буфера ввода
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Главная функция
int main() {
    // Настройка русского языка в консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== КОНВЕРТЕР ВЕСА ===\n";
    cout << "Программа для конвертации веса между разными единицами измерения\n";

    bool running = true;
    double lastWeight = 0;
    int lastSource = 1; // Килограмм по умолчанию
    int lastTarget = 0; // Фунт по умолчанию

    while (running) {
        cout << "\n==================================================" << endl;
        cout << "ГЛАВНОЕ МЕНЮ" << endl;
        cout << "==================================================" << endl;

        if (lastWeight > 0) {
            cout << "\nПоследний ввод: " << fixed << setprecision(2)
                << lastWeight << " " << units[lastSource].name << endl;
        }

        // Ввод веса
        double weight;
        cout << "\nВведите вес: ";
        while (!(cin >> weight) || weight <= 0) {
            clearInputBuffer();
            cout << "Ошибка! Введите положительное число: ";
        }

        // Выбор исходной единицы
        displayUnitsList();
        int from;
        cout << "Выберите исходную единицу (1-" << units.size() << "): ";
        while (!(cin >> from) || from < 1 || from > static_cast<int>(units.size())) {
            clearInputBuffer();
            cout << "Ошибка! Выберите число от 1 до " << units.size() << ": ";
        }

        // Выбор целевой единицы
        int to;
        cout << "Выберите целевую единицу (1-" << units.size() << "): ";
        while (!(cin >> to) || to < 1 || to > static_cast<int>(units.size())) {
            clearInputBuffer();
            cout << "Ошибка! Выберите число от 1 до " << units.size() << ": ";
        }

        // Сохранение последнего ввода
        lastWeight = weight;
        lastSource = from - 1;
        lastTarget = to - 1;

        // Выполнение конвертации
        double result = convertWeight(weight, from - 1, to - 1);

        // Вывод результатов
        cout << "\n==================================================" << endl;
        cout << "РЕЗУЛЬТАТЫ КОНВЕРТАЦИИ" << endl;
        cout << "==================================================" << endl;

        cout << fixed << setprecision(4);
        cout << "\nОсновной результат:\n";
        cout << weight << " " << units[from - 1].name << " = "
            << result << " " << units[to - 1].name << endl;

        cout << "\nЭквиваленты в других единицах:\n";
        cout << "----------------------------------------" << endl;
        for (size_t i = 0; i < units.size(); i++) {
            if (i != static_cast<size_t>(from - 1)) {
                double equiv = convertWeight(weight, from - 1, i);
                cout << setw(20) << left << units[i].name << ": "
                    << equiv << endl;
            }
        }
        cout << "----------------------------------------" << endl;

        // Вопрос о продолжении
        char choice;
        cout << "\nПродолжить конвертацию? (y/n): ";
        cin >> choice;
        running = (choice == 'y' || choice == 'Y');

        clearInputBuffer();
    }

    cout << "\nСпасибо за использование программы!\n";
    cout << "До свидания!\n";

    system("pause");
    return 0;
}