#pragma once

#include <iostream>
#include<string>

#ifndef __TQueue_H__
#define __TQueue_H__

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

	TQueue(size_t _sz = 2) : sz(_sz + 1), s(0), f(sz - 1)
	{
		if (_sz == 0 || _sz > MAX_QUEUE_SIZE)
			throw "Queue size should be greater than zero and less than max";
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


	bool isFull()
	{
		return s == next(next(f));
	}
	bool isEmpty()
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

	const T pop()
	{
		if (isEmpty())
			throw "There's nothing to pop from queue";
		T res = mem[s];
		s = next(s);
		return res;
	}


};

#endif