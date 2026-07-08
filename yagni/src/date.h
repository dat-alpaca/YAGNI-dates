#pragma once

const static int gDaysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

enum date_error
{
    DATE_OK,
    DATE_INVALID
} typedef date_error;

enum month
{
    MONTH_JAN = 1,
    MONTH_FEB,
    MONTH_MAR,
    MONTH_APR,
    MONTH_MAY,
    MONTH_JUN,
    MONTH_JUL,
    MONTH_AUG,
    MONTH_SEP,
    MONTH_OCT,
    MONTH_NOV,
    MONTH_DEC,
} typedef month;

static inline date_error date_extract_month_and_day(int inputDay, month* monthOutput, int* dayOutput)
{
    if (inputDay < 1 || inputDay > 365)
        return DATE_INVALID;

    int currentMonth = 0;

    int day = inputDay;
    while (day > gDaysInMonth[currentMonth])
    {
        day -= gDaysInMonth[currentMonth];
        ++currentMonth;
    }

    *monthOutput = (month)(currentMonth + 1);
    *dayOutput = day;

    return DATE_OK;
}