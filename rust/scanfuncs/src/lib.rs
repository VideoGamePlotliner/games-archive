// This file was created on 18 Feb 2026.

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_i32_from_to() {
        let message = "Testing `get_i32_from_to()` with bad bounds.";
        let lower_bound_inclusive = 282;
        let upper_bound_inclusive = 120;
        let expected_err_string = format!(
            "Lower bound ({}) is greater than upper bound ({}).",
            lower_bound_inclusive, upper_bound_inclusive
        );

        match get_i32_from_to(message, lower_bound_inclusive, upper_bound_inclusive) {
            Ok(_) => panic!(
                "Function `get_i32_from_to()` did not fail with bounds {} and {}.",
                lower_bound_inclusive, upper_bound_inclusive
            ),
            Err(e) => {
                if e.to_string() != expected_err_string {
                    panic!(
                        "\n\n\nFunction `get_i32_from_to()` failed with bounds {} and {} -- but not for the expected reason:\n    Expected reason: {}\n      Actual reason: {}\n\n\n",
                        lower_bound_inclusive,
                        upper_bound_inclusive,
                        expected_err_string,
                        e.to_string()
                    );
                }
            }
        }
    }
}

/**
 * This function loops until the user inputs an `i32` value that is
 * 1. Greater than or equal to `lower_bound_inclusive` and
 * 2. Less than or equal to `upper_bound_inclusive`.
 *
 * This function treats `lower_bound_inclusive` being greater than
 * `upper_bound_inclusive` as an error.
 *
 * If `Ok(i)` is returned by this function, then `i` is the `i32`
 * value chosen.
 */
pub fn get_i32_from_to(
    message: &str,
    lower_bound_inclusive: i32,
    upper_bound_inclusive: i32,
) -> Result<i32, std::io::Error> {
    if lower_bound_inclusive > upper_bound_inclusive {
        return Err(std::io::Error::new(
            std::io::ErrorKind::Other,
            format!(
                "Lower bound ({}) is greater than upper bound ({}).",
                lower_bound_inclusive, upper_bound_inclusive
            ),
        ));
    }

    loop {
        print!(
            "{}\nPlease choose an integer value from {} to {}.\n",
            message, lower_bound_inclusive, upper_bound_inclusive
        );

        let mut s = String::new();

        let result_1 = std::io::stdin().read_line(&mut s);

        // If `s` contains '\n', then find the last '\n' in `s`,
        // and remove it and any following characters from `s`.
        match s.rfind('\n') {
            Some(i) => s.truncate(s.ceil_char_boundary(i)),
            _ => (),
        }

        print!("You entered {:?}.\n", s);

        if s.len() == 0 {
            print!("Error: empty input. Try again.\n");
            continue;
        }

        if s.trim().len() == 0 {
            print!("Error: input is only made of whitespace characters. Try again.\n");
            continue;
        }

        match result_1 {
            Ok(_) => (),
            Err(result_1_err) => return Err(result_1_err),
        }

        let result_2 = s.parse::<i32>();

        match result_2 {
            Ok(result_2_ok) => {
                if result_2_ok < lower_bound_inclusive {
                    print!(
                        "Error: value chosen ({}) is less than lower bound ({}). Try again.\n",
                        result_2_ok, lower_bound_inclusive
                    );
                    continue;
                }
                if result_2_ok > upper_bound_inclusive {
                    print!(
                        "Error: value chosen ({}) is greater than upper bound ({}). Try again.\n",
                        result_2_ok, upper_bound_inclusive
                    );
                    continue;
                }

                print!("You have chosen {}.\n", result_2_ok);
                return Ok(result_2_ok);
            }
            Err(_) => {
                print!("Error: could not parse input as an integer. Try again.\n");
                continue;
            }
        }
    }
}
