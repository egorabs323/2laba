#include <iostream>
#include <cstring>
#include <climits>

const int SIZE = 100;  // Размер хеш-таблицы

// Структура для представления элемента в хеш-таблице
struct HashTableEntry {
    char* key1;
    char* key2;
    int delay;
    bool occupied;
};

// Структура хеш-таблицы
struct HashTable {
    HashTableEntry table[SIZE];
};

// Хеш-функция
int hash(const char* key1, const char* key2) {
    int hashValue = 0;
    for (int i = 0; key1[i] != '\0'; i++) {
        hashValue += key1[i];
    }
    for (int i = 0; key2[i] != '\0'; i++) {
        hashValue += key2[i];
    }
    return hashValue % SIZE;
}

// Хеш-функция для второй пробной позиции
int hash2(const char* key1, const char* key2) {
    int hashValue = 0;
    for (int i = 0; key1[i] != '\0'; i++) {
        hashValue += key1[i];
    }
    for (int i = 0; key2[i] != '\0'; i++) {
        hashValue += key2[i];
    }
    return (hashValue + 1) % SIZE;
}

// Создание хеш-таблицы
HashTable* createHashTable() {
    HashTable* hashTable = new HashTable();
    for (int i = 0; i < SIZE; i++) {
        hashTable->table[i].key1 = nullptr;
        hashTable->table[i].key2 = nullptr;
        hashTable->table[i].occupied = false;
    }
    return hashTable;
}

// Добавление маршрута в хеш-таблицу
void addRoute(HashTable* hashTable, const char* key1, const char* key2, int delay) {
    int index = hash(key1, key2);
    int step = hash2(key1, key2);
    while (hashTable->table[index].occupied) {
        if (strcmp(hashTable->table[index].key1, key1) == 0 && strcmp(hashTable->table[index].key2, key2) == 0) {
            std::cout << "The route already exists\n";
            return;
        }
        index = (index + step) % SIZE;
    }
    hashTable->table[index].key1 = strdup(key1);
    hashTable->table[index].key2 = strdup(key2);
    hashTable->table[index].delay = delay;
    hashTable->table[index].occupied = true;
}

// Получение задержки по маршруту
int getDelay(HashTable* hashTable, const char* key1, const char* key2) {
    int index = hash(key1, key2);
    int step = hash2(key1, key2);
    while (hashTable->table[index].occupied) {
        if (strcmp(hashTable->table[index].key1, key1) == 0 && strcmp(hashTable->table[index].key2, key2) == 0) {
            return hashTable->table[index].delay;
        }
        index = (index + step) % SIZE;
    }
    return -1;  // Если маршрута нет
}

// Функция для поиска минимальной задержки
int findMinDelay(HashTable* hashTable, const char* start, const char* end) {
    int minDelay = INT_MAX;
    char* current = strdup(start);
    char* next = strdup(start);
    int delay = 0;

    while (strcmp(current, end) != 0) {
        minDelay = INT_MAX;
        // Перебираем все возможные соседние серверы
        for (int i = 0; i < SIZE; ++i) {
            if (hashTable->table[i].occupied) {
                if (strcmp(hashTable->table[i].key1, current) == 0) {
                    int routeDelay = hashTable->table[i].delay;
                    if (routeDelay < minDelay) {
                        minDelay = routeDelay;
                        next = hashTable->table[i].key2;
                    }
                }
            }
        }

        // Добавляем минимальный маршрут в путь
        if (minDelay != INT_MAX) {
            delay += minDelay;
            current = next;
        } else {
            std::cout << "No route available\n";
            return -1;
        }
    }

    return delay;
}

int main() {
    setlocale (LC_ALL , "Russian");
    HashTable* hashTable = createHashTable();

    // Добавление маршрутов в хеш-таблицу
    addRoute(hashTable, "A", "B", 1);
    addRoute(hashTable, "B", "C", 2);
    addRoute(hashTable, "A", "C", 4);

    // Задание начального и конечного сервера
    const char* start = "A";
    const char* end = "C";

    // Поиск минимальной задержки
    int minDelay = findMinDelay(hashTable, start, end);

    if (minDelay != -1) {
        std::cout << "Минимальная задержка между сервером " << start << " и сервером " << end << " = " << minDelay << std::endl;
    }

    // Освобождение памяти
    delete hashTable;
    return 0;
}
