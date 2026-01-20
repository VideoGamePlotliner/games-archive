// This file was created on 30 Dec 2025.

import java.util.Scanner;

public class ScannerFunctions {

    /**
     * This method loops until the user inputs an `int` value that is
     *
     * 1. Greater than or equal to `lower_bound_inclusive` and
     *
     * 2. Less than or equal to `upper_bound_inclusive`.
     *
     * This method treats `lower_bound_inclusive` being greater than
     * `upper_bound_inclusive` as an error.
     *
     * This method returns the `int` value chosen.
     */
    public static int get_int_from_to(Scanner input_scanner, String message, int lower_bound_inclusive, int upper_bound_inclusive) {
        if (input_scanner == null) {
            throw new NullPointerException("Null input scanner");
        }
        if (message == null) {
            throw new NullPointerException("Null message");
        }
        if (lower_bound_inclusive > upper_bound_inclusive) {
            throw new IllegalArgumentException(String.format("Lower bound (%d) is greater than upper bound (%d).",
                    lower_bound_inclusive, upper_bound_inclusive));
        }

        String line;
        int int_value;

        while (true) {
            System.out.printf("%s\nPlease choose an integer value from %d to %d.\n",
                    message, lower_bound_inclusive, upper_bound_inclusive);

            line = input_scanner.nextLine();

            if (line != null) {
                System.out.printf("You entered \"%s\".\n", line);
            }

            if (line == null) {
                System.out.printf("Error: null input. Try again.\n");
                continue;
            }
            if (line.length() == 0) {
                System.out.printf("Error: empty input. Try again.\n");
                continue;
            }
            if (line.matches("\\s*")) {
                System.out.printf("Error: input is only made of whitespace characters. Try again.\n");
                continue;
            }

            try {
                int_value = Integer.parseInt(line);
            } catch (NumberFormatException e) {
                System.out.printf("Error: could not parse input as an integer. Try again.\n");
                continue;
            }

            if (int_value < lower_bound_inclusive) {
                System.out.printf("Error: value chosen (%d) is less than lower bound (%d). Try again.\n",
                        int_value, lower_bound_inclusive);
                continue;
            }
            if (int_value > upper_bound_inclusive) {
                System.out.printf("Error: value chosen (%d) is greater than upper bound (%d). Try again.\n",
                        int_value, upper_bound_inclusive);
                continue;
            }

            System.out.printf("You have chosen %d.\n", int_value);
            return int_value;
        }
    }

}
