//The task was to write a programme that provides verification of chess queen's movement
#include <iostream>
using namespace std;

int main() {
    int x1,x2,y1,y2;
    cout << "Расчет ошибки хода ферзя" << endl;
    cout << "Исходное положение: " << endl;
    cin >> x1 >> y1;
    cout << "Ход сделан на: " << endl;
    cin >> x2 >> y2;
    if (x1>10 or x2>10 or y1>10 or y2>10) {
        cout << "ERROR" << endl;
    }
    else {
        if (abs(x1 - x2) == abs(y1 - y2) or (x1 == x2) or (y1 == y2)) {
            cout << "Верно" << endl;
        } else {
            cout << "Не верно" << endl;
        }
    }
    return 0;
}
