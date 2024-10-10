// Math calculation of summary for ln 2 progression series of n members
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int max;
    cout << "Введите количество членов прогрессии: " << endl;
    cin >> max;
    double s = 0.0;
    double d = 0.0;
    for (int n = 1; n <= max; ++n) {
        s += (pow(-1, (n + 1))) / n;
    }
    cout << "Sum = " << s << endl;
}
