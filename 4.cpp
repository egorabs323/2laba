#include <iostream>
using namespace std;

// ������� algorithm ��������� ����� ����������� � �������� ������ � ������� �� ����� �� �����.
void algorithm(const int* array, int size, int target) {
    // �������� �� ���� ��������� �����������
    for (int i = 0; i < size; ++i) {
        int sum = 0;
        for (int j = i; j < size; ++j) {
            sum += array[j];  // ��������� ������� ������� � �����
            if (sum == target) {
                // ���� ����� ���������� ����� �������, ������� ���� ���������
                cout << "{ ";
                for (int k = i; k <= j; ++k) {
                    cout << array[k] << " ";
                }
                cout << "}" << endl;
            }
        }
    }
}

int main() {
    setlocale (LC_ALL , "Russian");
    int size;

    
    // ���� ������� �������
    cout << "������� ������ �������: ";
    cin >> size;
    
    int* array = new int[size];  // ������� ������������ ������
    
    // ���� ��������� �������
    for (int i = 0; i < size; ++i) {
        cout << "������� �������� ��������: ";
        cin >> array[i];
    }

    int target;
    // ���� ������� �����
    cout << "������� ����������� ����� ��������� ����������: ";
    cin >> target;

    // ������� � ������� ��� ���������� � ������� ������
    cout << "��������� ���������� � ������ " << target << ":\n";
    algorithm(array, size, target);

    delete[] array;  // ����������� ������

    return 0;
}
