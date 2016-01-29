#pragma once

#include "types.h"
#include "card.h"
#include <vector>
#include <stdexcept>

template <typename T>
class Database {
private:
	std::vector<T> _data;
public:
	T& get(u64 id);
	u64 set(T& d);
};

template<typename T>
inline T& Database<T>::get(u64 id) {
	if (id < _data.size()) {
		return _data[id];
	}
	else {
		throw new std::out_of_range("The DB index is out of range");
	}
}

template<typename T>
inline u64 Database<T>::set(T & d) {
	_data.push_back(d);
	return _data.size() - 1;
}

extern Database<Card> g_card_db;