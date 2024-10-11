// This programme outputs the day amount of given month/year input data
#include <iostream>
using namespace std;

int main() {
    int month,year;
    cout << "Календарь" << endl;
    cout << "Введите дату в данном формате:" << endl;
    cout << " MM YYYY " << endl;
    cout << "Ваша дата: " << endl;
    cin >> month >> year;
    if ((month>12) or (month<0)) {
        cout << "Invalid mounth" << endl;
    }
    switch (month) {
        case 1:
            cout << "31" << endl;
            break;
        case 2:
            if ((year%400 == 0 or year%4 == 0)&&(year%100>0))
            {
                cout << "29" << endl;
            }
            else {
                cout << "28" << endl;
            }
            break;
        case 3:
            cout << "31" << endl;
            break;
        case 4:
            cout << "30" << endl;
            break;
        case 5:
            cout << "31" << endl;
            break;
        case 6:
            cout << "30" << endl;
            break;
        case 7:
            cout << "31" << endl;
            break;
        case 8:
            cout << "31" << endl;
            break;
        case 9:
            cout << "30" << endl;
            break;
        case 10:
            cout << "31" << endl;
            break;
        case 11:
            cout << "30" << endl;
            break;
        case 12:
            cout << "31" << endl;
            break;
        default:
            cout << "ERROR" << endl;
    }
    return 0;
}
