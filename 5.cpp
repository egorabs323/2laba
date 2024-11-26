#include <iostream>
#include <algorithm> 
using namespace std;

// Структура для узла бинарного дерева поиска
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

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

    int operator[](int index) const {
        return data[index];
    }

    int& operator[](int index) {
        return data[index];
    }
};

// Функция для вставки элемента в бинарное дерево поиска
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value); // Создаем новый узел
    }
    if (value < root->data) {
        root->left = insert(root->left, value); // Вставляем в левое поддерево
    } else {
        root->right = insert(root->right, value); // Вставляем в правое поддерево
    }
    return root;
}

// Функция для сбора узлов с двумя детьми в контейнер
void collectNodesWithTwoChildren(Node* root, DynamicArray& result) {
    if (root == nullptr) return;

    // Рекурсивный обход дерева
    collectNodesWithTwoChildren(root->left, result);
    
    // Если у текущего узла есть два потомка, добавляем его в результат
    if (root->left != nullptr && root->right != nullptr) {
        result.push_back(root->data); // Добавляем узел с двумя детьми
    }

    collectNodesWithTwoChildren(root->right, result);
}

int main() {
    setlocale (LC_ALL , "Russian");
    int value;
    Node* root = nullptr;
    
    cout << "Введите последовательность целых чисел, заканчивающуюся 0 :\n";
    
    // Вводим элементы
    while (true) {
        cin >> value;
        if (value == 0) break; // Завершаем ввод на 0
        root = insert(root, value); // Вставляем элемент в дерево
    }
    
    // Динамический массив для сбора узлов с двумя детьми
    DynamicArray result(10);  // Начальная емкость 10
    
    // Собираем узлы с двумя детьми
    collectNodesWithTwoChildren(root, result);
    
    // Сортируем результат по возрастанию
    sort(result.data, result.data + result.size);
    
    // Выводим узлы с двумя детьми в порядке возрастания
    cout << "Узлы с двумя детьми: ";
    for (int i = 0; i < result.size; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}
