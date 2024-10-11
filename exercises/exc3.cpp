// The task was to write the programme that confirms is the year leap, isn't it
#include <iostream>
using namespace std;

int main() {
    int year;
    cout << "Введите год:" << endl;
    cin >> year;
    if (year > 0) {
        if ((year%400 == 0 or year%4 == 0)&&(year%100>0)) {
            cout << "Високосный год" << endl;
        }
        else {
            cout << "Невисокосный год" << endl;
        }
    }
    else {
        cout << "ERROR" << endl;
    }
    return 0;
}
