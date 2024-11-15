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
            cout << "��� ���� �������� � set: " << value << endl;
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
            cerr << "������ �������� �����: " << filePath << endl;
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
            cerr << "������ �������� ����� ��� ������: " << filePath << endl;
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

// ������� ��� ��������� ������
void processQuery(HashSet& mySet, const string& operation, const string& value) {
    if (operation == "ADD") {
        mySet.add(value);
    } else if (operation == "DEL") {
        mySet.remove(value);
        cout << "�������: " << value << endl;
    } else if (operation == "SET_AT") {
        cout << "�������� " << value << ": " << (mySet.contains(value) ? "��" : "���") << endl;
    } else {
        cout << "����������� ��������: " << operation << endl;
    }
}

// ������� ��� �������� ���������� ��������� ������
void parseArguments(int argc, char* argv[], string& filePath, string& operation, string& value) {
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filePath = argv[i + 1];
            ++i; // ���������� ��������� ��������
        } else if (arg == "--query" && i + 1 < argc) {
            operation = argv[i + 1];
            if (i + 2 < argc) {
                value = argv[i + 2];
                ++i; // ���������� ��������� ��������
            }
            ++i; // ���������� operation (ADD, DEL ��� SET_AT)
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    string filePath;
    string operation;
    string value;

    // ������ ���������
    parseArguments(argc, argv, filePath, operation, value);

    // ���������, ���� �� ��� ����������� ���������
    if (filePath.empty() || operation.empty() || value.empty()) {
        cerr << "������: ������������ ����������!" << endl;
        return 1;
    }

    // ������� ���������� ���������
    cout << "��������: " << operation << ", ��������: " << value << endl;

    HashSet mySet(100);
    mySet.loadFromFile(filePath); // ��������� ��������� �� �����

    // ��������� �������
    processQuery(mySet, operation, value);

    mySet.saveToFile(filePath); // ��������� ��������� � ����

    return 0;
}
