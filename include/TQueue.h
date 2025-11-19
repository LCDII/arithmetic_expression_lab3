#pragma once

#include <iostream>
#include<string>

using namespace std;

const int MAX_QUEUE_SIZE = 1000;

template<typename T>
class TQueue {

	T* mem;
	size_t sz;
	int s, f;

	int next(int i)
	{
		return ((i + 1) % sz);
	}
public:

	TQueue(size_t _sz = 1) : sz(_sz + 1), s(0), f(sz - 1)
	{
		if (_sz < 1 || _sz > MAX_QUEUE_SIZE)
			throw "Queue size should be greater than 1 and less than max";
		mem = new T[sz];
	}

	TQueue(const TQueue& q) : sz(q.sz), s(q.s), f(q.f)
	{
		mem = new T[sz];
		for (int i = s; i != next(f); i = next(i))
		{
			mem[i] = q.mem[i];
		}
	}

	TQueue& operator=(const TQueue& q)
	{
		if (this == &q) return *this;

		sz = q.sz;
		s = q.s;
		f = q.f;

		delete[]mem;
		mem = new T[sz];
		for (int i = s; i != next(f); i = next(i))
		{
			mem[i] = q.mem[i];
		}
	}

	~TQueue()
	{
		delete[] mem;
	}


	bool isFull() noexcept
	{
		return s == next(next(f));
	}
	bool isEmpty() noexcept
	{
		return s == next(f);
	}

	void push(const T& val)
	{
		if (isFull())
			throw "There's no place to push to queue";
		f = next(f);
		mem[f] = val;
	}
	const T top()
	{
		if(isEmpty())
			throw "There's nothing to top from queue";
		return mem[s];
	}
	const T pop()
	{
		if (isEmpty())
			throw "There's nothing to pop from queue";
		T res = mem[s];
		s = next(s);
		return res;
	}

	size_t getMaxSize() noexcept
	{
		return sz;
	}

	//need in arithmetics ------------------------------------------------------------------------------------------

	void clear() noexcept
	{
		while (!isEmpty())
			pop();
	}
	size_t getActualSize() noexcept
	{
		return isEmpty() ? 0 : (s <= f ? f - s + 1 : (sz - s) + f + 1);
	}

	TQueue refactor()//function to cut out  not neccesarry place in q
	{
		size_t newSize = getActualSize();
		TQueue tmp(*this);//to not change origin
		TQueue res(newSize);
		while (!tmp.isEmpty())
			res.push(tmp.pop());
		return res;
	}
	//--------------------------------------------------------------------------------------------------------------

	bool operator==(const TQueue<T>& q)
	{
		if (this == &q) return true;
		if (this->sz != q.sz) {
			return false;
		}

		// Создаем копии для сравнения (очередь нельзя обходить без извлечения)
		TQueue<T> _q1 = *this;
		TQueue<T> _q2 = q;

		while (!_q1.isEmpty()) {
			if (_q1.top() != _q2.top()) {
				return false;
			}
			_q1.pop();
			_q2.pop();
		}
		return true;
	}
	bool operator!=(const TQueue<T>& q) {
		return !(*this == q);
	}



	friend ostream& operator<<(ostream& ostr, TQueue<T> q)
	{
		TQueue<T> tmp(q);
		while (!tmp.isEmpty())
		{
			ostr << tmp.pop();
		}
		ostr << endl;
		return ostr;
	}
};

