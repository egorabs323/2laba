#include <iostream>
using namespace std;

// ��������� ��� ���� ��������� ������ ������
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ������� ��� ������� �������� � �������� ������ ������
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value); // ������� ����� ����
    }
    if (value < root->data) {
        root->left = insert(root->left, value); // ��������� � ����� ���������
    } else {
        root->right = insert(root->right, value); // ��������� � ������ ���������
    }
    return root;
}

// ������� ��� ������ � ������ ����� � ����� ������
void findNodesWithTwoChildren(Node* root) {
    if (root == nullptr) return;
    
    // ����������� ����� ������
    if (root->left != nullptr && root->right != nullptr) {
        cout << root->data << " "; // ������� ���� � ����� ������
    }

    // ������� ����� � ������ ����������
    findNodesWithTwoChildren(root->left);
    findNodesWithTwoChildren(root->right);
}

int main() {
    setlocale (LC_ALL , "Russian");
    int value;
    Node* root = nullptr;
    
    cout << "������� ������������������ ����� �����, ��������������� 0 (����):\n";
    
    // ������ �������� � ������
    while (true) {
        cin >> value;
        if (value == 0) break; // ��������� ���� �� 0
        root = insert(root, value); // ��������� ������� � ������
    }
    
    // ������� ���� � ����� ������ � ������� �����������
    cout << "���� � ����� ������: ";
    findNodesWithTwoChildren(root);
    cout << endl;
    
    return 0;
}
