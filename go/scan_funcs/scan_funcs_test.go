// This file was created on 10 Feb 2026.

package scan_funcs

import (
	"fmt"
	"testing"
)

func TestGetIntFromTo(t *testing.T) {
	var message string
	var lower_bound_inclusive int
	var upper_bound_inclusive int
	var err error
	var expected_err_string string

	message = "Testing `GetIntFromTo()` with bad bounds."
	lower_bound_inclusive = 282
	upper_bound_inclusive = 120
	expected_err_string = fmt.Sprintf("Lower bound (%d) is greater than upper bound (%d).", lower_bound_inclusive, upper_bound_inclusive)

	_, err = GetIntFromTo(message, lower_bound_inclusive, upper_bound_inclusive)
	if err == nil {
		t.Errorf("Function `GetIntFromTo()` did not fail with bounds %d and %d.", lower_bound_inclusive, upper_bound_inclusive)
	} else if err.Error() != expected_err_string {
		t.Logf("Function `GetIntFromTo()` failed with bounds %d and %d -- but not for the expected reason:", lower_bound_inclusive, upper_bound_inclusive)
		t.Logf("    Expected reason: %s", expected_err_string)
		t.Logf("      Actual reason: %s", err.Error())
		t.Fail()
	}
}
