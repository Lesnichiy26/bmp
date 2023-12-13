#include <cstdint>
#include <iostream>
#include <string>
#pragma once

template <typename T>
class vector {
public:
    vector() {
        arr = new T[100];
        capacity = 100;
        sizet = 0;
    }

    vector(const vector<T>& a) {
        
        arr = new T[a.capacity];
        sizet = a.sizet;
        capacity = a.capacity;
        for (uint64_t i = 0; i < sizet; i++) {
            arr[i] = a.arr[i];
        }
    }

    ~vector() {
        delete [] arr;
    }

    vector(uint64_t len) {
        arr = new T[len];
        capacity = len;
        sizet = len;
        for (int i = 0; i < len; i++) {
            arr[i] = 0;
        }
    }

    void pushback(T el) {
        if (capacity == sizet) {
            T* temp = new T[capacity + 100];

            for (uint64_t i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }

            capacity += 100;
            delete [] arr;
            arr = temp;
        }

        arr[sizet] = el;
        sizet++;
    }

    void insert(T el)
    {
        T* temp = new T[capacity + 1];

        for (uint64_t i = 1; i < capacity + 1; i++) {
            temp[i] = arr[i - 1];
        }

        capacity++;
        delete [] arr;
        arr = temp;

        arr[0] = el;
        sizet++;
    }

    void clear() {
        sizet = 0;
    }

    void print()
    {
        for (int i = 0; i < sizet; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
    }

    void pop() {
        sizet--;
    }

    uint64_t size() const {
        return sizet;
    }

    const T& operator[](uint64_t ind) const{
        if (ind < sizet) {
            return arr[ind];
        }
        return arr[sizet - 1];
    }

    T& operator[](uint64_t ind) {
        if (ind < sizet) {
            return arr[ind];
        }
        return arr[sizet - 1];
    }

    vector<T>& operator=(const vector<T>& a) {
        if (this != &a) {
            delete [] arr;
            arr = new T[a.capacity];
            sizet = a.sizet;
            capacity = a.capacity;
            for (uint64_t i = 0; i < sizet; i++) {
                arr[i] = a.arr[i];
            }
        }
        return *this;
    }
private:
    T* arr;
    uint64_t capacity;
    uint64_t sizet;
};
