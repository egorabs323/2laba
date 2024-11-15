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

    // Добавление элемента в стек
    void push(const string& value) {
        Node* newNode = new Node{value, top};  // Создаем новый узел
        top = newNode;  // Новый узел становится верхним
        cout << "Добавлен элемент: " << value << endl;
    }

    // Удаление элемента из стека
    string pop() {
        if (top == nullptr) {
            throw runtime_error("Стек пуст");
        }

        Node* temp = top;  // Сохраняем текущий верхний узел
        string value = temp->data;
        top = top->next;  // Перемещаем верхний указатель на следующий узел
        delete temp;  // Удаляем старый верхний узел

        cout << "Удален элемент: " << value << endl;
        return value;
    }

    ~Stack() {
        // Освобождаем память, чтобы избежать утечек
        while (top != nullptr) {
            pop();
        }
    }
};

void transformation() {
    Stack stack;
    string input;

    cout << "Введите выражение в постфиксной записи (например, \"123-+\"): ";
    cin >> input;

    int operatorCounter = 0;  // Счетчик операторов
    int operandCounter = 0;   // Счетчик операндов

    for (char& ch : input) {
        if (ch >= '0' && ch <= '9') {
            stack.push(string(1, ch));  // Добавляем цифру в стек
            operandCounter++;           // Увеличиваем счетчик операндов
            continue;
        }

        operatorCounter++;  // Увеличиваем счетчик операторов

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
                stack.push(to_string(i2 - i1));  // Обратите внимание на порядок операндов
                break;

            case '/':
                i1 = stoi(stack.pop());
                i2 = stoi(stack.pop());
                if (i1 == 0) {
                    cout << "Деление на ноль невозможно" << endl;
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
                cout << "Неизвестный оператор: " << ch << endl;
                return;
        }
    }

    if (operandCounter == operatorCounter + 1) {
        string res = stack.pop();
        cout << "Результат: " << res << endl;
    } else {
        cout << "Неправильный ввод!" << endl;
    }
}

int main() {
    setlocale (LC_ALL , "Russian");
    transformation();
    return 0;
}
