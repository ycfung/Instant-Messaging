//
// Created by ycfung on 5/19/18.
//

#include "Date.h"

int Date::getCurrentYear()
{
    time_t tt = time(nullptr);
    tm *t = localtime(&tt);
    return t->tm_year + 1900;
}