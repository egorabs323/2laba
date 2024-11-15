#include <iostream>
using namespace std;

// Структура для узла бинарного дерева поиска
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
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

// Функция для поиска и вывода узлов с двумя детьми
void findNodesWithTwoChildren(Node* root) {
    if (root == nullptr) return;
    
    // Рекурсивный обход дерева
    if (root->left != nullptr && root->right != nullptr) {
        cout << root->data << " "; // Выводим узел с двумя детьми
    }

    // Обходим левое и правое поддеревья
    findNodesWithTwoChildren(root->left);
    findNodesWithTwoChildren(root->right);
}

int main() {
    setlocale (LC_ALL , "Russian");
    int value;
    Node* root = nullptr;
    
    cout << "Введите последовательность целых чисел, заканчивающуюся 0 (ноль):\n";
    
    // Вводим элементы в дерево
    while (true) {
        cin >> value;
        if (value == 0) break; // Завершаем ввод на 0
        root = insert(root, value); // Вставляем элемент в дерево
    }
    
    // Выводим узлы с двумя детьми в порядке возрастания
    cout << "Узлы с двумя детьми: ";
    findNodesWithTwoChildren(root);
    cout << endl;
    
    return 0;
}
