#include <iostream>
using namespace std;

int main() {
    int user_choice;
    int *input1;
    char *input2;
    std::string *input3;
    cout << "Выберите тип вводимой переменной" << endl;
    cout << "1 - Integer" << endl;
    cout << "2 - Char" << endl;
    cout << "3 - String" << endl;
    cin >> user_choice;
    switch (user_choice) {
        case 1: {
            input1 = new int;
            cout << "Введите переменную: ";
            cin >> *input1;
            cout << "Вы ввели: " <<*input1;
            delete input1;
            break;
        }
        case 2: {
            input2 = new char;
            cout << "Введите переменную: ";
            cin >> *input2;
            cout << "Вы ввели: "<< *input2;
            delete input2;
            break;
        }
        case 3: {
            input3 = new std::string;
            cout << "Введите переменную: ";
            cin >> *input3;
            cout << "Вы ввели: "<< *input3;
            delete input3;
            break;
        }
        default: {
            cout << "ERROR" << endl;
            break;
        }
    }
    return 0;
}