// This file was created on 4 Feb 2026.

package main

import (
	"fmt"
	"go_games/scan_funcs"
	"log"
)

func main() {
	var err error

	_, err = scan_funcs.GetIntFromTo("ABCDEF", 309, 208 /* SHOULD FAIL WITH THESE ARGUMENTS */)
	if err != nil {
		fmt.Printf("Function `scan_funcs.GetIntFromTo()` failed: %v\n(Failure was expected.)\n", err)
	} else {
		log.Fatalf("Fatal error: function `scan_funcs.GetIntFromTo()` did not fail.")
	}
}
