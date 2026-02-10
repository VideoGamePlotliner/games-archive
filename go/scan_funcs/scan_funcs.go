// This file was created on 4 Feb 2026.

package scan_funcs

import (
	"fmt"
	"regexp"
	"strconv"
)

/**
 * This function loops until the user inputs an `int` value that is
 * 1. Greater than or equal to `lower_bound_inclusive` and
 * 2. Less than or equal to `upper_bound_inclusive`.
 *
 * This function treats `lower_bound_inclusive` being greater than
 * `upper_bound_inclusive` as an error.
 *
 * This function returns the `int` value chosen.
 */
func GetIntFromTo(message string, lower_bound_inclusive int, upper_bound_inclusive int) (int, error) {
	if lower_bound_inclusive > upper_bound_inclusive {
		return lower_bound_inclusive, fmt.Errorf("Lower bound (%d) is greater than upper bound (%d).", lower_bound_inclusive, upper_bound_inclusive)
	}

	var err error
	var line string
	var atoi_int_value_returned int
	var scanln_int_value_returned int
	var matchstring_bool_value_returned bool

	for {
		fmt.Printf("%s\nPlease choose an integer value from %d to %d.\n", message, lower_bound_inclusive, upper_bound_inclusive)

		scanln_int_value_returned, err = fmt.Scanln(&line)

		if err != nil {
			fmt.Printf("Error: `fmt.Scanln()` failed: %v.\n", err)
			if err.Error() == "EOF" {
				return lower_bound_inclusive, err
			}
			continue
		}
		if scanln_int_value_returned != 1 {
			return lower_bound_inclusive, fmt.Errorf("`scanln_int_value_returned` (%d) does not equal 1.", scanln_int_value_returned)
		}

		fmt.Printf("You entered %q.\n", line)

		if len(line) == 0 {
			fmt.Printf("Error: empty input. Try again.\n")
			continue
		}

		matchstring_bool_value_returned, err = regexp.MatchString("\\S", line)

		if err != nil {
			fmt.Printf("Error: `regexp.MatchString()` failed: %v.\n", err)
			return lower_bound_inclusive, err
		}
		if !matchstring_bool_value_returned {
			fmt.Printf("Error: input is only made of whitespace characters. Try again.\n")
			continue
		}

		atoi_int_value_returned, err = strconv.Atoi(line)

		if err != nil {
			fmt.Printf("Error: could not parse input as an integer. Try again. (%v)\n", err)
			continue
		}
		if atoi_int_value_returned < lower_bound_inclusive {
			fmt.Printf("Error: value chosen (%d) is less than lower bound (%d). Try again.\n", atoi_int_value_returned, lower_bound_inclusive)
			continue
		}
		if atoi_int_value_returned > upper_bound_inclusive {
			fmt.Printf("Error: value chosen (%d) is greater than upper bound (%d). Try again.\n", atoi_int_value_returned, upper_bound_inclusive)
			continue
		}

		fmt.Printf("You have chosen %d.\n", atoi_int_value_returned)
		return atoi_int_value_returned, nil
	}
}
