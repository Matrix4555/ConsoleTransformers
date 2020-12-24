#include "OwnFunctions.h"

std::string own::takeWord(const std::string& str, const int number)
{
    int firstComma = 0;
    int comma = 0;
    int pos = 0;
    for (auto symbol : str)
    {
        if (symbol == ',' && ++comma == number)
        {
            pos -= firstComma;
            break;
        }
        if (symbol == ',')
        {
            firstComma = pos + 1;
            if (str[firstComma] == ' ')
                firstComma++;
        }
        pos++;
    }
    return str.substr(firstComma, pos);
}

int own::setChoice(const int min, const int max)
{
    int select;
    std::cin >> select;
    while (true)
        if (select < min || select > max)
        {
            std::cout << "Incorrect Input. Please Repeat: ";
            std::cin >> select;
        }
        else
            return select;
}
