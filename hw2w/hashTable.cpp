#include "hashTable.h"

using namespace std;

HashTable::HashTable(int factor, int defaultSize) :
size(defaultSize), loadFactor(factor) {
    data = new List<Pair>[size];
}

HashTable::~HashTable() {
    delete[] data;
}

void HashTable::insert(Pair pair) {
    int index = hashFunction(pair.getKey());
    data[index].insertHead(pair);
    int listSize = data[index].getSize();
    // If the hash table is overloaded
    if (listSize >= loadFactor) {
        resize();
    }
}

void HashTable::remove(Pair pair) {
    int index = hashFunction(pair.getKey());
    // Will throw ListException::ElementNotFound if pair is not found
    data[index].remove(pair);
}

int HashTable::getValue(int key) const {
    Pair dummy(key, 0);
    int index = hashFunction(key);
    // Will throw ListException::ElementNotFound if dummy is not found
    NodeL<Pair>* ptr = data[index].find(dummy);
    return (ptr->getData()).getValue();
}

int HashTable::getSize() const {
    return size;
}

void HashTable::resize() {
    List<Pair> buffer;
    // Empty all chains into the buffer
    for (int i = 0; i < size; i++) {
        while (data[i].getSize() > 0) {
            Pair pair = (data[i].getHead())->getData();
            buffer.insertHead(pair);
            data[i].remove(pair);
        }
    }
    // Resize data to be twice as long
    delete [] data;
    size *= 2;
    data = new List<Pair>[size];
    // Reinsert all pairs with the updated data and hash function
    while (buffer.getSize() > 0) {
        Pair pair = (buffer.getHead())->getData();
        insert(pair);
        buffer.remove(pair);
    }
}