#include <iostream>
using namespace std;

int partition(int list[], int start, int pivot) {
    int i = start;
    while (i < pivot) {
        if (list[i] > list[pivot] && i == pivot - 1) {
            swap(list[i], list[pivot]);
            pivot--;
        } else if (list[i] > list[pivot]) {
            swap(list[pivot - 1], list[pivot]);
            swap(list[i], list[pivot]);
            pivot--;
        } else i++;
    }
    return pivot;
}

void quickSort(int list[], int start, int end) {
    if (start < end) {
        int pivot = partition(list, start, end);

        quickSort(list, start, pivot - 1);
        quickSort(list, pivot + 1, end);
    }
}

int main() {
    short int N;
    int list[N];
    cout << "Введите размер массива: ";
    cin >> N;
    for (int i = 0; i < N; i++) {
        cout << "Введите " << i + 1 << "-ый элемент массива: ";
        cin >> list[i];
    }

    quickSort(list, 0, N);

    cout << "Наибольшими элементами массива являются:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << list[N - i] << "\t";
    }

    return 0;
}
