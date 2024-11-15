#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

class Stack {
private:
    struct Node {
        string data;
        Node* next;
    };
    
    Node* top;

public:
    Stack() : top(nullptr) {}

    // ���������� �������� � ����
    void push(const string& value) {
        Node* newNode = new Node{value, top};  // ������� ����� ����
        top = newNode;  // ����� ���� ���������� �������
        cout << "�������� �������: " << value << endl;
    }

    // �������� �������� �� �����
    string pop() {
        if (top == nullptr) {
            throw runtime_error("���� ����");
        }

        Node* temp = top;  // ��������� ������� ������� ����
        string value = temp->data;
        top = top->next;  // ���������� ������� ��������� �� ��������� ����
        delete temp;  // ������� ������ ������� ����

        cout << "������ �������: " << value << endl;
        return value;
    }

    ~Stack() {
        // ����������� ������, ����� �������� ������
        while (top != nullptr) {
            pop();
        }
    }
};

void transformation() {
    Stack stack;
    string input;

    cout << "������� ��������� � ����������� ������ (��������, \"123-+\"): ";
    cin >> input;

    int operatorCounter = 0;  // ������� ����������
    int operandCounter = 0;   // ������� ���������

    for (char& ch : input) {
        if (ch >= '0' && ch <= '9') {
            stack.push(string(1, ch));  // ��������� ����� � ����
            operandCounter++;           // ����������� ������� ���������
            continue;
        }

        operatorCounter++;  // ����������� ������� ����������

        int i1, i2;
        switch (ch) {
            case '*':
                i1 = stoi(stack.pop());
                i2 = stoi(stack.pop());
                stack.push(to_string(i1 * i2));
                break;

            case '+':
                i1 = stoi(stack.pop());
                i2 = stoi(stack.pop());
                stack.push(to_string(i1 + i2));
                break;

            case '-':
                i1 = stoi(stack.pop());
                i2 = stoi(stack.pop());
                stack.push(to_string(i2 - i1));  // �������� �������� �� ������� ���������
                break;

            case '/':
                i1 = stoi(stack.pop());
                i2 = stoi(stack.pop());
                if (i1 == 0) {
                    cout << "������� �� ���� ����������" << endl;
                } else {
                    stack.push(to_string(i2 / i1));
                }
                break;

            case '^':
                i1 = stoi(stack.pop());
                i2 = stoi(stack.pop());
                stack.push(to_string(pow(i2, i1)));
                break;

            default:
                cout << "����������� ��������: " << ch << endl;
                return;
        }
    }

    if (operandCounter == operatorCounter + 1) {
        string res = stack.pop();
        cout << "���������: " << res << endl;
    } else {
        cout << "������������ ����!" << endl;
    }
}

int main() {
    setlocale (LC_ALL , "Russian");
    transformation();
    return 0;
}
