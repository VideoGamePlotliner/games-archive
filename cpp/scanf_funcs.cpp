// This file was created on 25 Dec 2025.

#include "error_strings.hpp"
#include "scanf_funcs.hpp"

#include <cctype>
#include <cerrno>
#include <cstdbool>
#include <cstring>

#define SCANF_INT_BUFFER_SIZE 13 /* Just enough space to fit "-2147483648\n", including its null terminator. */

int scanf_int_from_to(const char *message, int lower_bound_inclusive,
                      int upper_bound_inclusive, int *int_value_chosen)
{
    if (!message)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(message);
        errno = EINVAL;
        return -1;
    }
    if (!int_value_chosen)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(int_value_chosen);
        errno = EINVAL;
        return -1;
    }
    if (lower_bound_inclusive > upper_bound_inclusive)
    {
        printf("%s(): Error: lower bound (%d) is greater "
               "than upper bound (%d).\n",
               __func__, lower_bound_inclusive, upper_bound_inclusive);
        errno = EINVAL;
        return -1;
    }

    char s[SCANF_INT_BUFFER_SIZE];
    int int_value;
    int sscanf_return_value;
    int error_number;
    bool is_error;
    bool is_eof;

    while (1)
    {
        memset(s, 0, sizeof(s));

        printf("%s\n"
               "Please choose an integer value from %d to %d.\n",
               message, lower_bound_inclusive, upper_bound_inclusive);
        errno = 0;
        if (!fgets(s, sizeof(s), stdin))
        {
            error_number = errno;
            is_error = ferror(stdin);
            is_eof = feof(stdin);

            printf("%s(): Error: NULL returned by `fgets()` "
                   "with%s error and with%s EOF "
                   "and with `errno` of %d.\n",
                   __func__,
                   is_error ? "" : "out",
                   is_eof ? "" : "out",
                   error_number);

            if (!is_error && !error_number)
            {
                errno = is_eof ? ECANCELED : EIO;
            }
            else
            {
                errno = error_number;
            }
            return -1;
        }
        else
        {
            error_number = errno;
            is_error = ferror(stdin);
            is_eof = feof(stdin);
        }

        s[sizeof(s) - 1] = 0;

        {
            char *last_place_in_s_at_which_the_character_is_new_line = strrchr(s, '\n');
            if (last_place_in_s_at_which_the_character_is_new_line)
            {
                *last_place_in_s_at_which_the_character_is_new_line = 0;
            }
        }

        printf("You entered \"%s\".\n", s);

        errno = 0;
        sscanf_return_value = sscanf(s, "%d", &int_value);

        error_number = errno;
        is_error = ferror(stdin);
        is_eof = feof(stdin);

        if (!strlen(s))
        {
            printf("Error: empty input. Try again.\n");
            continue;
        }

        {
            bool s_is_only_made_of_whitespace_characters = true;
            for (int i = 0; s[i]; i++)
            {
                if (!isspace(s[i]))
                {
                    s_is_only_made_of_whitespace_characters = false;
                    break;
                }
            }
            if (s_is_only_made_of_whitespace_characters)
            {
                printf("Error: input is only made of "
                       "whitespace characters. Try again.\n");
                continue;
            }
        }

        if (sscanf_return_value == 0)
        {
            printf("Error: could not parse input "
                   "as an integer. Try again.\n");
            continue;
        }
        if (sscanf_return_value != 1)
        {
            printf("%s(): Error: %d returned by `sscanf()` "
                   "with%s error and with%s EOF "
                   "and with `errno` of %d.\n",
                   __func__,
                   sscanf_return_value,
                   is_error ? "" : "out",
                   is_eof ? "" : "out",
                   error_number);

            if (!is_error && !error_number)
            {
                errno = is_eof ? ECANCELED : EIO;
            }
            else
            {
                errno = error_number;
            }
            return -1;
        }
        else if (int_value < lower_bound_inclusive)
        {
            printf("Error: value chosen (%d) is less "
                   "than lower bound (%d). Try again.\n",
                   int_value, lower_bound_inclusive);
            continue;
        }
        else if (int_value > upper_bound_inclusive)
        {
            printf("Error: value chosen (%d) is greater "
                   "than upper bound (%d). Try again.\n",
                   int_value, upper_bound_inclusive);
            continue;
        }
        else
        {
            printf("You have chosen %d.\n", int_value);
            *int_value_chosen = int_value;
            return 0;
        }
    }
}
