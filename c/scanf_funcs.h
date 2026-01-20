// This file was created on 9 Dec 2025.

#ifndef SCANF_FUNCS_H
#define SCANF_FUNCS_H

/**
 * This functions loops until the user inputs an `int` value that is
 * 1. Greater than or equal to `lower_bound_inclusive` and
 * 2. Less than or equal to `upper_bound_inclusive`.
 *
 * This function treats `lower_bound_inclusive` being greater than
 * `upper_bound_inclusive` as an error.
 *
 * This function returns -1 if error or 0 otherwise.
 */
int scanf_int_from_to(const char *message, int lower_bound_inclusive, int upper_bound_inclusive, int *int_value_chosen);

#endif // SCANF_FUNCS_H
