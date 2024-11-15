#include <iostream>
using namespace std;

// Функция algorithm выполняет поиск подмассивов с заданной суммой и выводит их сразу на экран.
void algorithm(const int* array, int size, int target) {
    // Проходим по всем возможным подмассивам
    for (int i = 0; i < size; ++i) {
        int sum = 0;
        for (int j = i; j < size; ++j) {
            sum += array[j];  // Добавляем текущий элемент к сумме
            if (sum == target) {
                // Если сумма подмассива равна целевой, выводим этот подмассив
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

    
    // Ввод размера массива
    cout << "Введите размер массива: ";
    cin >> size;
    
    int* array = new int[size];  // Создаем динамический массив
    
    // Ввод элементов массива
    for (int i = 0; i < size; ++i) {
        cout << "Введите значение элемента: ";
        cin >> array[i];
    }

    int target;
    // Ввод целевой суммы
    cout << "Введите необходимую сумму элементов подмассива: ";
    cin >> target;

    // Находим и выводим все подмассивы с целевой суммой
    cout << "Найденные подмассивы с суммой " << target << ":\n";
    algorithm(array, size, target);

    delete[] array;  // Освобождаем память

    return 0;
}
