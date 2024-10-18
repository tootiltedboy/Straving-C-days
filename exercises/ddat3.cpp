#include <iostream>
#include <string>
using namespace std;

int main() {
    unsigned size;
    int user_choice;
    cout << "Выберите тип инициализируемого массива: " << endl;
    cout << "Integer - 1" << endl;
    cout << "String - 2" << endl;
    cout << "Ввод: ";
    cin >> user_choice;
    cout << "Введите размерность массива: ";
    cin >> size;
    switch (user_choice) {
        case 1: {
            int* iarr{new int[size]};
                for (unsigned i{}; i<size; i++) {
                cout << "Введите " << i + 1 << "-й элемент: ";
                cin >> iarr[i];
            }
            cout << "Введенный массив: " << endl;
            for (unsigned i{}; i<size; i++) {
                cout << iarr[i] << "\t";
            }
            delete[] iarr;
            break;
        }
        case 2: {
            string* sarr{new string[size]};
            for (unsigned i{}; i<size; i++) {
                cout << "Введите " << i + 1 << "-й элемент: ";
                cin >> sarr[i];
            }
            cout << "Введенный массив: " << endl;
            for (unsigned i{}; i<size; i++) {
                cout << sarr[i] << endl;
            }
            delete[] sarr;
            break;
        }
        default: {
            cout << "ERROR" << endl;
            break;
        }
    }
    return 0;
}
