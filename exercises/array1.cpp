#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
using namespace std;

int main() {
    int max_value;
    short int variable;

    cout << "Каким образом вы хотите инициализировать массив:" << endl;
    this_thread::sleep_for(250ms);
    cout << "1 - вручную" << endl;
    this_thread::sleep_for(250ms);
    cout << "0 - автоматически" << endl;
    this_thread::sleep_for(250ms);
    cout << "Введите выбранную опцию: ";
    cin >> variable;

    switch(variable) {
    case 1 : {
        int N;
        cout << "Введите кол-во элементов массива: ";
        cin >> N;

        int arr[N];
        for (int i = 0; i < N; i++) {
            cout << "Введите " << i + 1 << "-й элемент массива: ";
            cin >> arr[i];
        }

        max_value = arr[0];
        for (int j = 1; j < N; j++) {
            if (arr[j] > max_value) {
                max_value = arr[j];
            }
        }
        cout << "Наибольший элемент массива это: " << max_value << endl;
        break;
    }
    case 0 : {
        srand(static_cast<unsigned int>(time(nullptr)));
        int r = rand() % 257 + 1;
        unsigned int arr[r];

        for (int i = 0; i < r; i++) {
            arr[i] = rand() % 256;
        }

        max_value = arr[0];
        for (int j = 1; j < r; j++) {
            if (arr[j] > max_value) {
                max_value = arr[j];
            }
        }
        cout << "Наибольший элемент массива это: " << max_value << endl;
        break;
    }
        default:
            cout << "Error" << endl;
        break;
    }
    return 0;
}
