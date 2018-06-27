//
// Created by ycfung on 5/19/18.
//

#ifndef IM_DATE_H
#define IM_DATE_H

#include <iostream>
#include <ctime>

class Date
{
private:
    int year;
    int month;
    int day;

public:
    int getYear()
    { return year; };

    int getMonth()
    { return month; };

    int getDay()
    { return day; };

    Date() = default;

    int getCurrentYear();

    Date(int y, int m, int d) //Basic initializer
    {
        year = y;
        month = m;
        day = d;
    }
};


#endif //IM_DATE_H
