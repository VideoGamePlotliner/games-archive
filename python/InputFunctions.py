# This file was created on 16 Jan 2026.

import re



#
# This method loops until the user inputs an `int` value that is
# 1. Greater than or equal to `lower_bound_inclusive` and
# 2. Less than or equal to `upper_bound_inclusive`.
#
# This method treats `lower_bound_inclusive` being greater than
# `upper_bound_inclusive` as an error.
#
# This method returns the `int` value chosen.
#
def get_int_from_to(message: str, lower_bound_inclusive: int, upper_bound_inclusive: int) -> int:
    if lower_bound_inclusive > upper_bound_inclusive:
        raise RuntimeError(f"Lower bound ({lower_bound_inclusive}) is greater than upper bound ({upper_bound_inclusive}).")

    while True:
        line = input(f"{message}\nPlease choose an integer value from {lower_bound_inclusive} to {upper_bound_inclusive}.\n")

        print(f"You entered \"{line}\".")

        if len(line) == 0:
            print("Error: empty input. Try again.")
            continue
        if re.search("\\S", line) == None:
            print("Error: input is only made of whitespace characters. Try again.")
            continue

        try:
            int_value = int(line)
        except ValueError:
            print("Error: could not parse input as an integer. Try again.")
            continue

        if int_value < lower_bound_inclusive:
            print(f"Error: value chosen ({int_value}) is less than lower bound ({lower_bound_inclusive}). Try again.")
            continue
        if int_value > upper_bound_inclusive:
            print(f"Error: value chosen ({int_value}) is greater than upper bound ({upper_bound_inclusive}). Try again.")
            continue

        print(f"You have chosen {int_value}.")
        return int_value
