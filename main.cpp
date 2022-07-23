//
//  main.cpp
//
//
//  Created by Vache Gasparyan on 22.07.22.
//

#include <iostream>

template <typename T>
class vec {
public:
	class iterator;
public:
	using ValueType = T;
public:
	class iterator {
	public:
		using pointer = ValueType *;
		using ref = ValueType &;
	public:
		iterator(pointer i) : m_ptr{i}
		{}
		iterator() = default;
	public:
		iterator& operator+(int n) {
			m_ptr = m_ptr + n;
			return *this;
		}

		iterator& operator-(int n) {
			m_ptr -= n;
			return *this;
		}
		
		iterator& operator++(int) {
			iterator tmp = *this;
			++m_ptr;
			return tmp;
		}
		
		iterator& operator--(int) {
			iterator tmp = *this;
			--m_ptr;
			return tmp;
		}
		
		iterator& operator++() {
			(++m_ptr);
			return  *this;
		}
		
		ref operator[](int indx) {
			return *(m_ptr + indx);
		}
		
		iterator& operator--() { return *(--m_ptr);}
		bool operator>(const iterator &iter) {return (m_ptr > iter.m_ptr);}
		bool operator<(const iterator &iter) {return (m_ptr < iter.m_ptr);}
		bool operator==(const iterator &iter) {return (m_ptr == iter.m_ptr);}
		bool operator!=(const iterator &iter) {return (m_ptr != iter.m_ptr);}
		bool operator<=(const iterator &iter) {return (m_ptr <= iter.m_ptr);}
		bool operator>=(const iterator &iter) {return (m_ptr >= iter.m_ptr);}
		T& operator*() {
			return *(m_ptr);
		}
	private:
		pointer m_ptr = nullptr;
	};
public:
	vec(int a);
	vec();
	vec(const vec<T>& cp_vec);
	vec(vec<T>&& other);
	~vec();
public:
	void insert(iterator obj, T i);
	T find(iterator obj);
	void remove(iterator obj);
	vec<T>::iterator begin();
	vec<T>::iterator end();
	void push(T item);
private:
	T *m_arr;
	unsigned int m_size;
	unsigned int m_capacity;
};

template <typename T>
vec<T>::vec() {
	m_arr = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
typename vec<T>::iterator vec<T>::begin() {
	return  iterator(m_arr);
}

template <typename T>
typename vec<T>::iterator vec<T>::end() {
	return  iterator(m_arr + m_size);
}

template <typename T>
void vec<T>::push(T item) {
	if (m_capacity > m_size + 1) {
		m_arr[m_size] = item;
	} else {
		T *t_arr = new T[m_capacity * 2];
		unsigned int i = 0;
		while (i < m_size) {
			t_arr[i] = m_arr[i];
			++i;
		}
		t_arr[i] = item;
		m_capacity *= 2;
		delete [] m_arr;
		m_arr = t_arr;
	}
	++m_size;
}

template <typename T>
vec<T>::vec(int a) {
	m_arr = new T[a];
	m_size = 0;
	m_capacity = a;
}

template <typename T>
vec<T>::vec(const vec<T>& cp_vec) {
	m_arr = new T[cp_vec.m_capacity];
	m_size = cp_vec.size;
	m_capacity = cp_vec.m_capacity;
	for (unsigned int i = 0; i < m_size; i++) {
		m_arr[i] = cp_vec[i];
	}
}

template <typename T>
vec<T>::vec(vec<T>&& other) {
	if (m_size > 0) {
		delete [] m_arr;
	}
	m_size = other.size;
	for (unsigned int i = 0; i < m_size; i++) {
		m_arr[i] = other[i];
	}
	delete other;
}

template <typename T>
vec<T>::~vec() {
	delete m_arr;
	m_size = 0;
}

template <typename T>
void vec<T>::insert(iterator obj, T item) {
	iterator it(m_arr);
	int index = 0;
	if(m_size == 0) {
		throw "Bad access";
	}
	T *t_arr;
	t_arr = new T[m_capacity + 1];
	iterator next(m_arr + 1);
	while (it != obj && index <= m_size) {
		t_arr[index] = *it;
		++it;
		index++;
		++next;
	}
	if (index > m_size) {
		delete [] t_arr;
		throw "Bad access";
	}
	t_arr[index] = item;
	index++;
	while (index < m_size + 1) {
		
		t_arr[index] = *it;
		++it;
		index++;
	}
	delete [] m_arr;
	m_arr = t_arr;
	m_size += 1;
	m_capacity += 1;
}

template <typename T>
void vec<T>::remove(iterator obj) {
	iterator it(m_arr);
	int index = 0;
	if(m_size == 0) {
		throw "Bad access";
	}
	T *t_arr;
	t_arr = new T[m_capacity];
	iterator next(m_arr + 1);
	while (it != obj && index <= m_size) {
		t_arr[index] = *it;
		++it;
		index++;
		++next;
	}
	if (index > m_size) {
		delete [] t_arr;
		throw "Bad access";
	}
	++it;
	while (index < m_size - 1) {
		t_arr[index] = *it;
		++it;
		index++;
	}
	m_size -= 1;
	m_capacity += 1;
	delete [] m_arr;
	m_arr = t_arr;

}


int main(int argc, const char * argv[]) {
	vec<int> a(3);
	a.push(7);
	a.push(8);
	a.push(9);
	a.insert(a.begin()+1, 17);
	a.remove(a.begin());
    return 0;
}
