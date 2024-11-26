#include <iostream>
using namespace std;

// Структура для динамического массива
struct DynamicArray {
    int* data;
    int size;
    int capacity;

    // Конструктор
    DynamicArray(int cap) : size(0), capacity(cap) {
        data = new int[capacity];
    }

    // Деструктор
    ~DynamicArray() {
        delete[] data;
    }

    // Метод для добавления элемента в массив
    void push_back(int value) {
        if (size >= capacity) {
            capacity *= 2;  // Увеличиваем емкость массива
            int* newData = new int[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }

    // Оператор доступа к элементам массива
    int operator[](int index) const {
        return data[index];
    }

    int& operator[](int index) {
        return data[index];
    }
};

// Функция algorithm выполняет поиск подмассивов с заданной суммой и выводит их сразу на экран.
void algorithm(const DynamicArray& array, int target) {
    int size = array.size;
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

    DynamicArray array(size);  // Создаем динамический массив

    // Ввод элементов массива
    for (int i = 0; i < size; ++i) {
        cout << "Введите значение элемента: ";
        int value;
        cin >> value;
        array.push_back(value);  // Добавляем элементы в массив
    }

    int target;
    // Ввод целевой суммы
    cout << "Введите необходимую сумму элементов подмассива: ";
    cin >> target;

    // Находим и выводим все подмассивы с целевой суммой
    cout << "Найденные подмассивы с суммой " << target << ":\n";
    algorithm(array, target);

    return 0;
}
