#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

// Функция для нахождения минимальной разницы между суммами двух подмножеств
void findSubsetWithMinimalDifference(int nums[], int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += nums[i];  // Вычисляем общую сумму всех элементов
    }

    // Максимальная возможная сумма одного из подмножеств
    int target = sum / 2;

    // Динамическое программирование для поиска всех возможных сумм <= sum / 2
    bool dp[target + 1];
    for (int i = 0; i <= target; ++i) {
        dp[i] = false;
    }
    dp[0] = true;  // Сумма 0 всегда достижима (пустое подмножество)

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
    bool subset1[target + 1];
    for (int i = 0; i <= target; ++i) {
        subset1[i] = false;
    }
    subset1[subsetSum1] = true;

    for (int i = n - 1; i >= 0; --i) {
        for (int j = target; j >= nums[i]; --j) {
            if (subset1[j - nums[i]]) {
                subset1[j] = true;
            }
        }
    }

    // Подмножество 1
    int subset1Arr[n];
    int idx1 = 0;
    for (int i = 0; i < n; ++i) {
        if (subset1[nums[i]]) {
            subset1Arr[idx1++] = nums[i];
        }
    }

    // Подмножество 2 (оставшиеся элементы)
    int subset2Arr[n];
    int idx2 = 0;
    for (int i = 0; i < n; ++i) {
        bool found = false;
        for (int j = 0; j < idx1; ++j) {
            if (nums[i] == subset1Arr[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            subset2Arr[idx2++] = nums[i];
        }
    }

    // Выводим результат
    cout << "Подмножество 1: { ";
    for (int i = 0; i < idx1; ++i) {
        cout << subset1Arr[i] << " ";
    }
    cout << "}" << endl;

    cout << "Подмножество 2: { ";
    for (int i = 0; i < idx2; ++i) {
        cout << subset2Arr[i] << " ";
    }
    cout << "}" << endl;

    cout << "Разница между суммами: " << diff << endl;
}

int main() {
    setlocale (LC_ALL , "Russian");
    int nums[] = {5, 8, 1, 14, 7};
    int n = sizeof(nums) / sizeof(nums[0]);

    findSubsetWithMinimalDifference(nums, n);

    return 0;
}
