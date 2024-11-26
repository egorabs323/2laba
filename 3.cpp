#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

// Структура для динамического массива
struct DynamicArray {
    int* data;
    int size;
    int capacity;

    DynamicArray(int cap) : size(0), capacity(cap) {
        data = new int[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(int value) {
        if (size >= capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }

    int operator[](int index) const {
        return data[index];
    }

    int& operator[](int index) {
        return data[index];
    }
};

// Функция для нахождения минимальной разницы между суммами двух подмножеств
void findSubsetWithMinimalDifference(int nums[], int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += nums[i];  // Вычисляем общую сумму всех элементов
    }

    // Максимальная возможная сумма одного из подмножеств
    int target = sum / 2;

    // Динамическое программирование для поиска всех возможных сумм <= sum / 2
    bool* dp = new bool[target + 1];
    dp[0] = true;  // Сумма 0 всегда достижима (пустое подмножество)
    for (int i = 1; i <= target; ++i) {
        dp[i] = false;
    }

    // Для каждого числа обновляем возможные суммы
    for (int i = 0; i < n; ++i) {
        for (int j = target; j >= nums[i]; --j) {
            dp[j] = dp[j] || dp[j - nums[i]];
        }
    }

    // Ищем наибольшую возможную сумму, которая не превосходит sum / 2
    int subsetSum1 = 0;
    for (int i = target; i >= 0; --i) {
        if (dp[i]) {
            subsetSum1 = i;
            break;
        }
    }

    int subsetSum2 = sum - subsetSum1;  // Вторая сумма
    int diff = abs(subsetSum1 - subsetSum2);  // Разница между суммами

    // Восстановим элементы первого подмножества, которые составляют сумму subsetSum1
    DynamicArray subset1Arr(n);
    int remainingSum = subsetSum1;
    for (int i = n - 1; i >= 0; --i) {
        if (remainingSum >= nums[i] && dp[remainingSum - nums[i]]) {
            subset1Arr.push_back(nums[i]);
            remainingSum -= nums[i];
        }
    }

    // Подмножество 2 (оставшиеся элементы)
    DynamicArray subset2Arr(n);
    bool* used = new bool[n]();
    for (int i = 0; i < subset1Arr.size; ++i) {
        for (int j = 0; j < n; ++j) {
            if (nums[j] == subset1Arr[i] && !used[j]) {
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            subset2Arr.push_back(nums[i]);
        }
    }

    // Выводим результат
    cout << "Подмножество 1: { ";
    for (int i = 0; i < subset1Arr.size; ++i) {
        cout << subset1Arr[i] << " ";
    }
    cout << "}" << endl;

    cout << "Подмножество 2: { ";
    for (int i = 0; i < subset2Arr.size; ++i) {
        cout << subset2Arr[i] << " ";
    }
    cout << "}" << endl;

    cout << "Разница между суммами: " << diff << endl;

    // Освобождение памяти
    delete[] dp;
    delete[] used;
}

int main() {
    setlocale (LC_ALL , "Russian");
    int nums[] = {5, 8, 1, 14, 7};
    int n = sizeof(nums) / sizeof(nums[0]);

    findSubsetWithMinimalDifference(nums, n);

    return 0;
}
