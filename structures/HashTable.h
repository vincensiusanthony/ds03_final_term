#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <functional>
#include <string>
#include <optional>

template <typename K, typename V>
class HashTable {
private:
    static const int TABLE_SIZE = 101; // prime number for better distribution
    std::vector<std::list<std::pair<K, V>>> table;

    int hashFunc(const K& key) const {
        return std::hash<K>{}(key) % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const K& key, const V& value) {
        int idx = hashFunc(key);
        for (auto& kv : table[idx]) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        table[idx].emplace_back(key, value);
    }

    std::optional<V> get(const K& key) const {
        int idx = hashFunc(key);
        for (const auto& kv : table[idx]) {
            if (kv.first == key) return kv.second;
        }
        return std::nullopt;
    }

    bool exists(const K& key) const {
        int idx = hashFunc(key);
        for (const auto& kv : table[idx]) {
            if (kv.first == key) return true;
        }
        return false;
    }

    void remove(const K& key) {
        int idx = hashFunc(key);
        table[idx].remove_if([&](const std::pair<K, V>& kv) { return kv.first == key; });
    }

    std::vector<V> getAllValues() const {
        std::vector<V> values;
        for (const auto& bucket : table) {
            for (const auto& kv : bucket)
                values.push_back(kv.second);
        }
        return values;
    }

    // PATCH: add getMutable() to allow reference access to values
    V* getMutable(const K& key) {
        int idx = hashFunc(key);
        for (auto& kv : table[idx]) {
            if (kv.first == key) return &kv.second;
        }
        return nullptr;
    }
};

#endif // HASHTABLE_H