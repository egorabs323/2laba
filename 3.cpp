#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

// ������� ��� ���������� ����������� ������� ����� ������� ���� �����������
void findSubsetWithMinimalDifference(int nums[], int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += nums[i];  // ��������� ����� ����� ���� ���������
    }

    // ������������ ��������� ����� ������ �� �����������
    int target = sum / 2;

    // ������������ ���������������� ��� ������ ���� ��������� ���� <= sum / 2
    bool dp[target + 1];
    for (int i = 0; i <= target; ++i) {
        dp[i] = false;
    }
    dp[0] = true;  // ����� 0 ������ ��������� (������ ������������)

    // ��� ������� ����� ��������� ��������� �����
    for (int i = 0; i < n; ++i) {
        for (int j = target; j >= nums[i]; --j) {
            dp[j] = dp[j] || dp[j - nums[i]];
        }
    }

    // ���� ���������� ��������� �����, ������� �� ����������� sum / 2
    int subsetSum1 = 0;
    for (int i = target; i >= 0; --i) {
        if (dp[i]) {
            subsetSum1 = i;
            break;
        }
    }

    int subsetSum2 = sum - subsetSum1;  // ������ �����
    int diff = abs(subsetSum1 - subsetSum2);  // ������� ����� �������

    // ����������� �������� ������� ������������, ������� ���������� ����� subsetSum1
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

    // ������������ 1
    int subset1Arr[n];
    int idx1 = 0;
    for (int i = 0; i < n; ++i) {
        if (subset1[nums[i]]) {
            subset1Arr[idx1++] = nums[i];
        }
    }

    // ������������ 2 (���������� ��������)
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

    // ������� ���������
    cout << "������������ 1: { ";
    for (int i = 0; i < idx1; ++i) {
        cout << subset1Arr[i] << " ";
    }
    cout << "}" << endl;

    cout << "������������ 2: { ";
    for (int i = 0; i < idx2; ++i) {
        cout << subset2Arr[i] << " ";
    }
    cout << "}" << endl;

    cout << "������� ����� �������: " << diff << endl;
}

int main() {
    setlocale (LC_ALL , "Russian");
    int nums[] = {5, 8, 1, 14, 7};
    int n = sizeof(nums) / sizeof(nums[0]);

    findSubsetWithMinimalDifference(nums, n);

    return 0;
}
