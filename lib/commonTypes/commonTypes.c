#include "commonTypes.h"


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