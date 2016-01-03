#ifndef hashTable_h
#define hashTable_h

#include <iostream>
#include <exception>
#include "list.h"
#include "pair.h"

class HashTable {
    
    static const int DEFAULT_SIZE = 128;
    
    List<Pair>* data;
    int size;
    int count;
    int loadFactor;
    
    int hashFunction(int key) const {
        return key%size;
    }
    
public:
    
    // Constructors
    
    HashTable(int factor, int defaulSize = DEFAULT_SIZE);
    ~HashTable();
    
    // Handling functions
    
    void insert(Pair pair);
    void remove(Pair pair);
    int getValue(int key) const;
    
    // Get functions
    
    int getSize() const;
    
private:
    
    void resize();
    
};

#endif /* hashTable_h */
