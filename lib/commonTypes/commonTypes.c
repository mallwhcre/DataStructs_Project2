#include "commonTypes.h"

#define dateIsEqual(date1, date2) ((date1).year == (date2).year && (date1).month == (date2).month && (date1).day == (date2).day)

bool dateIsGreater(Date date1, Date date2)
{
    if (date1.year > date2.year)
    {
        return true;
    }
    else if (date1.year < date2.year)
    {
        return false;
    }

    if (date1.month > date2.month)
    {
        return true;
    }
    else if (date1.month < date2.month)
    {
        return false;
    }

    if (date1.day > date2.day)
    {
        return true;
    }

    return false;
}

bool tempIsGreater(int temp1, int temp2)
{
    if (temp1 > temp2)
    {
        return true;
    }
    else if (temp1 < temp2)
    {
        return false;
    }

    return false;
}