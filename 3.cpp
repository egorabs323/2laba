#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

struct SSet {
    int* data;
    int size;
    int capacity;
    SSet(int cap) : size(0), capacity(cap) {
        data = new int[capacity];
    }
    ~SSet() {
        delete[] data;
    }
    void insert(int value) {
        // Проверяем, существует ли уже элемент
        for (int i = 0; i < size; ++i) {
            if (data[i] == value) return;  // Элемент уже существует
        }
        // Если массив заполнен, увеличиваем его размер
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

    int getSize() const {
        return size;
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

    // Для поиска всех возможных сумм <= sum / 2
    bool* dp = new bool[target + 1];
    dp[0] = true;  // Сумма 0 всегда доступная
    for (int i = 1; i <= target; ++i) {
        dp[i] = false;
    }

    // Для каждого числа обновляем возможные суммы
    for (int i = 0; i < n; ++i) {
        for (int j = target; j >= nums[i]; --j) {
            dp[j] = dp[j] || dp[j - nums[i]];
        }
    }

    // наиб сум
    int subsetSum1 = 0;
    for (int i = target; i >= 0; --i) {
        if (dp[i]) {
            subsetSum1 = i;
            break;
        }
    }

    int subsetSum2 = sum - subsetSum1;  // Вторая сумма
    int diff = abs(subsetSum1 - subsetSum2);  

    // 1 c сабсетсум
    SSet subset1Set(n);
    int remainingSum = subsetSum1;
    for (int i = n - 1; i >= 0; --i) {
        if (remainingSum >= nums[i] && dp[remainingSum - nums[i]]) {
            subset1Set.insert(nums[i]);
            remainingSum -= nums[i];
        }
    }

    //2
    SSet subset2Set(n);
    bool* used = new bool[n]();
    for (int i = 0; i < subset1Set.getSize(); ++i) {
        for (int j = 0; j < n; ++j) {
            if (nums[j] == subset1Set[i] && !used[j]) {
                used[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            subset2Set.insert(nums[i]);
        }
    }
    cout << "Подмножество 1: { ";
    for (int i = 0; i < subset1Set.getSize(); ++i) {
        cout << subset1Set[i] << " ";
    }
    cout << "}" << endl;

    cout << "Подмножество 2: { ";
    for (int i = 0; i < subset2Set.getSize(); ++i) {
        cout << subset2Set[i] << " ";
    }
    cout << "}" << endl;

    cout << "Разница между суммами: " << diff << endl;

    delete[] dp;
    delete[] used;
}
int main() {
    setlocale(LC_ALL, "Russian");
    int nums[] = {5, 8, 1, 14, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    findSubsetWithMinimalDifference(nums, n);
    return 0;
}
