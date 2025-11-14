#pragma once
#include<iostream>
#include<vector>
#ifndef __TStack_H__
#define __TStack_H__


using namespace std;

const int MAX_STACK_SIZE = 1000;

template<typename T>
class TStack
{
protected:
    int curr;
    size_t sz;
    T* mem;
public:
    TStack(size_t _sz = 1) : curr(-1)
    {
        if (_sz == 0 || _sz > MAX_STACK_SIZE)
            throw out_of_range("Stack size should be greater than zero and less than max");
        sz = _sz;
        mem = new T[sz];
    };

    TStack(const TStack& s) : curr(s.curr), sz(s.sz)
    {
        mem = new T[s.sz];
        for (int i = 0; i <= curr; i++)
        {
            mem[i] = s.mem[i];
        }
    }

    TStack& operator=(const TStack& s)
    {
        if (this == &s) return *this;

        curr = s.curr;
        sz = s.sz;

        delete[]mem;
        mem = new T[sz];
        for (int i = 0; i <= curr; i++)
        {
            mem[i] = s.mem[i];
        }
    }

    ~TStack()
    {
        delete[] mem;
    }

    bool isEmpty() const {
        return (curr == -1);
    }

    bool isFull() const {
        return (curr == sz - 1);
    }
    void push(const T& v)
    {
        if (isFull())
            throw out_of_range("There's no place to push to stack");

        mem[++curr] = v;
    }

    const T& pop()
    {
        if (isEmpty())
            throw out_of_range("There's nothing to pop from stack");
        return mem[curr--];
    }

    const T& top()
    {
        if (isEmpty())
            throw out_of_range("There's nothing on stack top, its empty");
        return mem[curr];
    }


    friend ostream& operator<<(ostream& ostr, TStack& st)
    {
        if (st.isEmpty())
            return ostr;
        for (size_t i = 0; i <= st.curr; i++)
        {
            cout << st.mem[i] << " ";
        }
        cout << endl;
        return ostr;
    }

};

#endif