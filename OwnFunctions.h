#pragma once
#include <iostream>
#include <string>

namespace own
{
    std::string takeWord(const std::string& str, const int number);     // take a word from the sequence of words which are located through the commas
    int setChoice(const int min, const int max);                        // get chosen value from std::cin with correctness check
    class MyException;                                                  // my class for catch of exception
}

class own::MyException
{
public:
    MyException() : mes("Unknown") { }
    MyException(const std::string& message) : mes(message) { }
    void getMessage() const { std::cout << mes << std::endl; }
private:
    std::string mes;
};
