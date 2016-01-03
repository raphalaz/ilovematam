#include "pair.h"

//------------------------------------------------------------------------------
//                                  PAIR CLASS
//------------------------------------------------------------------------------

Pair::Pair(int key, int value) :
key(key), value(value) {}

Pair::Pair(const Pair& pair) :
key(pair.key), value(pair.value) {}

void Pair::operator=(const Pair& pair) {
	key = pair.key;
	value = pair.value;
}

bool Pair::operator==(const Pair& pair) const {
	return key == pair.key;
}

bool Pair::operator>(const Pair& pair) const {
	return key > pair.key;
}

bool Pair::operator<(const Pair& pair) const {
	return key < pair.key;
}

void Pair::addToValue(int i) {
	value += i;
}

void Pair::multiplyValue(int i) {
	value *= i;
}

int Pair::getKey() const {
    return key;
}

int Pair::getValue() const {
    return value;
}

void Pair::setKey(int key) {
    this->key = key;
}

void Pair::setValue(int value) {
    this->value = value;
}

//------------------------------------------------------------------------------
//                               END OF PAIR CLASS
//------------------------------------------------------------------------------
