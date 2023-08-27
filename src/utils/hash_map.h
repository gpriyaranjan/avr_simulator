#ifndef ATMEGASIM_SRC_HASH_MAP_H
#define ATMEGASIM_SRC_HASH_MAP_H

// Hash node class template
template <typename K, typename V, int N>
class HashNode {
public:
    HashNode(const K &key, const V &value) :
            key(key), value(value), next(nullptr) {
    }

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    void setValue(V value) {
        HashNode::value = value;
    }

    HashNode *getNext() const {
        return next;
    }

    void setNext(HashNode *next) {
        HashNode::next = next;
    }

private:
    // key-value pair
    K key;
    V value;
    // next bucket with the same key
    HashNode *next;
};

template <typename K, int N>
struct KeyHash {
    unsigned long operator()(const K& key) const
    {
        return reinterpret_cast<unsigned long>(key) % N;
    }
};

template <typename K, typename V, int N, typename F = KeyHash<K,N>>
class HashMap {
public:
    HashMap() {
        // construct zero initialized hash table of size
        table = new HashNode<K, V, N> *[N]();
    }

    ~HashMap() {
        // destroy all buckets one by one
        for (int i = 0; i < N; ++i) {
            HashNode<K, V, N> *entry = table[i];
            while (entry != nullptr) {
                HashNode<K, V, N> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
        // destroy the hash table
        delete [] table;
    }

    bool get(const K &key, V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V, N> *entry = table[hashValue];

        while (entry != nullptr) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void put(const K &key, const V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V, N> *prev = nullptr;
        HashNode<K, V, N> *entry = table[hashValue];

        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) {
            entry = new HashNode<K, V, N>(key, value);
            if (prev == nullptr) {
                // insert as first bucket
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        } else {
            // just update the value
            entry->setValue(value);
        }
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V, N> *prev = nullptr;
        HashNode<K, V, N> *entry = table[hashValue];

        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) {
            // key not found
            return;
        }
        else {
            if (prev == nullptr) {
                // remove first bucket of the list
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }

private:
    // hash table
    HashNode<K, V, N> **table;
    F hashFunc;
};

#endif //ATMEGASIM_SRC_HASH_MAP_H
