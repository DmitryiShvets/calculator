//
// Created by dmirty on 11.12.2021.
//

#ifndef LESSON24_RWLIB_H
#define LESSON24_RWLIB_H


#include <iostream>
#include  "vector"

void Print();

void Print(bool boole);

template<typename T>
void Print(const T &value) {
    std::cout << value;
}

template<typename T>
void Println(const T &value) {
    std::cout << value << std::endl;
}

template<typename T>
void Print(T *value, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << value[i] << " ";
    }
}

template<typename T>
void Println(T *value, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << value[i] << " ";
    }
    Print();
}

template<class T>
void Print(const std::vector<T> &vec) {
    for (typename std::vector<T>::const_iterator iter = vec.cbegin(); iter != vec.cend(); ++iter) {
        std::cout << *iter << " ";
    }
}

template<typename T, typename... Args>
void Print(const T &text, Args... args) // recursive variadic function
{
    Print(text);
    Print(args...);
}

template<typename T>
T Read() {
    T result;
    std::cin >> result;
    return result;
}

template<typename T>
T Read(std::string text) {
    std::cout << text;
    T result;
    std::cin >> result;
    return result;
}


#endif //LESSON24_RWLIB_H