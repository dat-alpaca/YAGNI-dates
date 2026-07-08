#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "yagni/src/date.h"
#include "yagni/src/language.h"

#define LANGUAGE_EXPECTED_SIZE (16)
#define LANGUAGE_ERROR_INDEX (0)
#define LANGUAGE_PROMPT_INDEX (1)
#define LANGUAGE_ANSWER_MONTH_INDEX (2)
#define LANGUAGE_ANSWER_DAY_INDEX (3)

#define ARG_LANGUAGE (1)
#define ARG_COUNT (2)

static language load_language(const char* directory, char* languageString)
{
    char* languageSanitized = languageString;
    tolower_string(languageSanitized);

    language chosenLanguage = language_init();
    {
        char* filepath = append_filepath(directory, languageSanitized);
        language_read_file(&chosenLanguage, filepath);
        
        free(filepath);
    }

    return chosenLanguage;
}

static int input_day_of_year()
{
    int dayOfYear;
    scanf("%d", &dayOfYear);
    return dayOfYear;
}

static char* language_get_month(language* language, month month)
{
    int offset = LANGUAGE_ANSWER_DAY_INDEX + 1;
    int monthIndex = (int)month - 1 + offset;
    return language_get_text(language, monthIndex);
}

int main(int argc, char** argv)
{
    if (argc < ARG_COUNT)
    {
        fprintf(stderr, "usage: %s 'dayOfYear'\n", argv[0]);
        return 1;
    }

    language language = load_language("assets", argv[ARG_LANGUAGE]);
    if (language.data.size < LANGUAGE_EXPECTED_SIZE)
    {
        fprintf(stderr, "invalid language file\n");
        return 1;
    }

    printf("%s", language_get_text(&language, LANGUAGE_PROMPT_INDEX));
    int dayOfYear = input_day_of_year(); 

    month selectedMonth;
    int day;
    {
        date_error error = date_extract_month_and_day(dayOfYear, &selectedMonth, &day);
        if (error != DATE_OK)
        {
            printf(language_get_text(&language, LANGUAGE_ERROR_INDEX), argv[0]);
            printf("\n");
            return 1;
        }
    }

    char* monthName = language_get_month(&language, selectedMonth);
    printf(language_get_text(&language, LANGUAGE_ANSWER_MONTH_INDEX), monthName);
    printf("\n");

    printf(language_get_text(&language, LANGUAGE_ANSWER_DAY_INDEX), day);
    printf("\n");
}