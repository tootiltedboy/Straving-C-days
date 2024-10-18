#include <iostream>
#include <string>
using namespace std;

int main() {
    unsigned rows, columns;
    int user_choice;
    cout << "Выберите тип инициализируемого массива: " << endl;
    cout << "Float - 1" << endl;
    cout << "String - 2" << endl;
    cout << "Ввод: ";
    cin >> user_choice;
    switch (user_choice) {
        case 1: {
            cout << "Введите количество строк: ";
            cin >> rows;
            cout << "Введите количество столбцов: ";
            cin >> columns;

            float** farr = new float*[rows];
            for (unsigned i{}; i< rows; i++) {
                farr[i] = new float[columns]{};
            }

            for(unsigned i{}; i<rows; i++) {
                cout << "Введите значение для " << (i+1) << " строки" << endl;
                for (unsigned j{}; j< columns; j++) {
                    cout << (j+1) << " столбец: ";
                    cin >> farr[i][j];
                }
            }
            cout << "Введенный массив:" << endl;
            for (unsigned i{}; i< rows; i++) {
                for (unsigned j{}; j< columns; j++) {
                    cout << farr[i][j] <<"\t";
                }
                cout << endl;
            }
            for (unsigned i{}; i< rows; i++) {
                delete[] farr[i];
            }
            delete[] farr;
            break;
        }
        case 2: {
            cout << "Введите количество строк: ";
            cin >> rows;
            cout << "Введите количество столбцов: ";
            cin >> columns;

            string** sarr = new std::string*[rows];
            for (unsigned i{}; i< rows; i++) {
                sarr[i] = new string[columns];
            }

            for(unsigned i{}; i<rows; i++) {
                cout << "Введите значение для " << (i+1) << " строки" << endl;
                for (unsigned j{}; j< columns; j++) {
                    cout << (j+1) << " столбец: ";
                    cin >> sarr[i][j];
                }
            }
            cout << "Введенный массив:" << endl;
            for (unsigned i{}; i< rows; i++) {
                for (unsigned j{}; j< columns; j++) {
                    cout << sarr[i][j] <<"\t";
                }
                cout << endl;
            }
            for (unsigned i{}; i< rows; i++) {
                delete[] sarr[i];
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
