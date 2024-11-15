#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
};

struct HashSet {
    Node** table;
    int size;

    HashSet(int tableSize) : size(tableSize) {
        table = new Node*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashSet() {
        clear();
        delete[] table;
    }

    void clear() {
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }

    bool contains(const string& value) const {
        int index = hash(value);
        Node* current = table[index];
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void add(const string& value) {
        if (contains(value)) {
            cout << "Уже есть значение в set: " << value << endl;
            return;
        }

        int index = hash(value);
        Node* newNode = new Node{value, nullptr};

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    void remove(const string& value) {
        int index = hash(value);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void loadFromFile(const string& filePath) {
        ifstream file(filePath);
        if (!file) {
            cerr << "Ошибка открытия файла: " << filePath << endl;
            return;
        }
        string value;
        while (getline(file, value)) {
            add(value);
        }
        file.close();
    }

    void saveToFile(const string& filePath) {
        ofstream file(filePath);
        if (!file) {
            cerr << "Ошибка открытия файла для записи: " << filePath << endl;
            return;
        }
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current) {
                file << current->data << endl;
                current = current->next;
            }
        }
        file.close();
    }

private:
    int hash(const string& value) const {
        int hashValue = 0;
        for (char c : value) {
            hashValue = (hashValue * 31 + c) % size;
        }
        return hashValue;
    }
};

// Функция для обработки команд
void processQuery(HashSet& mySet, const string& operation, const string& value) {
    if (operation == "ADD") {
        mySet.add(value);
    } else if (operation == "DEL") {
        mySet.remove(value);
        cout << "Удалено: " << value << endl;
    } else if (operation == "SET_AT") {
        cout << "Содержит " << value << ": " << (mySet.contains(value) ? "Да" : "Нет") << endl;
    } else {
        cout << "Неизвестная операция: " << operation << endl;
    }
}

// Функция для парсинга аргументов командной строки
void parseArguments(int argc, char* argv[], string& filePath, string& operation, string& value) {
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filePath = argv[i + 1];
            ++i; // пропускаем следующий аргумент
        } else if (arg == "--query" && i + 1 < argc) {
            operation = argv[i + 1];
            if (i + 2 < argc) {
                value = argv[i + 2];
                ++i; // пропускаем следующий аргумент
            }
            ++i; // пропускаем operation (ADD, DEL или SET_AT)
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    string filePath;
    string operation;
    string value;

    // Парсим аргументы
    parseArguments(argc, argv, filePath, operation, value);

    // Проверяем, были ли все необходимые аргументы
    if (filePath.empty() || operation.empty() || value.empty()) {
        cerr << "Ошибка: недостаточно аргументов!" << endl;
        return 1;
    }

    // Выводим полученные аргументы
    cout << "Операция: " << operation << ", Значение: " << value << endl;

    HashSet mySet(100);
    mySet.loadFromFile(filePath); // Загружаем множество из файла

    // Обработка запроса
    processQuery(mySet, operation, value);

    mySet.saveToFile(filePath); // Сохраняем множество в файл

    return 0;
}
