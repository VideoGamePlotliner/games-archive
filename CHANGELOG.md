<!-- This file was created on 7 Dec 2025. -->

# Changes
Below is a list of the changes made to this repo.

## 7 Dec 2025
- Create this repo. At first, this repo only contained [`README.md`](README.md).
- Create this file.
- Add a new comment to this repo's [`README.md`](README.md). This comment reads, "This file was created on 7 Dec 2025."
- Create [`.gitignore`](.gitignore).
- Create [`LICENSE.md`](LICENSE.md).

## 8 Dec 2025
- Create [`ci.yml`](.github/workflows/ci.yml).
- Create [`Makefile`](Makefile).
- Create [`tictactoe_main.c`](tictactoe_main.c).
- Create [`tictactoe.c`](tictactoe.c).
- Create [`tictactoe.h`](tictactoe.h).
- Add `*.o`, `*.d`, and `/tictactoe_main` to [`.gitignore`](.gitignore).

## 9 Dec 2025
Note: this section was added to this file on 16 Dec 2025.
- Create [`error_strings.h`](error_strings.h).
- Create [`scanf_funcs.c`](scanf_funcs.c).
- Create [`scanf_funcs.h`](scanf_funcs.h).
- Replace `tictactoe_main: $$@.o tictactoe.o` with `tictactoe_main: $$@.o tictactoe.o scanf_funcs.o` in [`Makefile`](Makefile).
- Add `WINNER_VALUE_*`, `tictactoe_who_won()`, and the line `#include <stdbool.h>` to [`tictactoe.h`](tictactoe.h).
- Make the following changes to [`tictactoe.c`](tictactoe.c):
  - Add the line `#include "error_strings.h"`.
  - Move the line `#include "tictactoe.h"` to right under the line `#include "error_strings.h"`.
  - Add `PRINTF___OTHER_ERROR___INVALID_CELL_VALUE()`.
  - Use `printf()` more in `tictactoe_get_cell()`.
  - Use `printf()` more in `tictactoe_set_cell()`.
  - Use `PRINTF___*()` in `tictactoe_*()`.
  - Split the first `if` block in `tictactoe_get_cell()` into many `if` blocks.
  - Split the first `if` block in `tictactoe_set_cell()` into many `if` blocks.
  - Add `tictactoe_who_won()`and `tictactoe_who_won___*()`.
- Make the following changes to [`tictactoe_main.c`](tictactoe_main.c):
  - Remove the line `#include <err.h>`.
  - Add more `#include` lines.
  - Add `scan_options()`.
  - Add `try_scanf_int_from_to()`.
  - Remove each `err(1, __func__);` line.
  - Add the line `errno = 0;` to `try_tictactoe_*()`.
  - Use `PRINTF_EXIT___FATAL_ERROR___FUNCTION_FAILURE()` in `try_tictactoe_*()`.
  - Add `print_player_info()`.
  - Add `try_tictactoe_who_won()`.
  - Add `play_game()`.
  - Add `run_demonstration()` and move into it the contents of `main()`.
  - Use `scan_options()`, `play_game()`, and `run_demonstration()` in `main()`.

## 17 Dec 2025
- Remove the line `ALL_D_FILES = $(ALL_C_FILES:.c=.d)` from [`Makefile`](Makefile).
- Remove the line `ALL_O_FILES = $(ALL_C_FILES:.c=.o)` from [`Makefile`](Makefile).
- Replace `@set` with `set` in [`Makefile`](Makefile).
- Make the following changes to `scanf_int_from_to()` in [`scanf_funcs.c`](scanf_funcs.c):
  - Move the declarations for the variables `error_number`, `is_error`, and `is_eof` to right below the declaration for the variable `sscanf_return_value`.
  - Replace the lines...
    ```c
    if (!fgets(s, sizeof(s), stdin))
    {
      bool is_error = ferror(stdin);
      bool is_eof = feof(stdin);
      int error_number = errno;
    ```
    ...with the lines...
    ```c
    if (!fgets(s, sizeof(s), stdin))
    {
      error_number = errno;
      is_error = ferror(stdin);
      is_eof = feof(stdin);
    ```
  - Add the following lines to right above the line `s[sizeof(s) - 1] = 0;`:
    ```c
    else
    {
      error_number = errno;
      is_error = ferror(stdin);
      is_eof = feof(stdin);
    }
    ```
  - Add the line `errno = 0;` to right above the line `sscanf_return_value = sscanf(s, "%d", &int_value);`.
  - Add the following lines to right below the line `sscanf_return_value = sscanf(s, "%d", &int_value);`:
    ```c
    error_number = errno;
    is_error = ferror(stdin);
    is_eof = feof(stdin);
    ```
  - Replace the lines...
    ```c
    if (sscanf_return_value != 1)
    {
      bool is_error = ferror(stdin);
      bool is_eof = feof(stdin);
      int error_number = errno;

      printf("%s(): Error: %d returned by `sscanf()` "
    ```
    ...with the lines...
    ```c
    if (sscanf_return_value != 1)
    {
      printf("%s(): Error: %d returned by `sscanf()` "
    ```
- Fix a typo(s) in the comment for `scanf_int_from_to()` in [`scanf_funcs.h`](scanf_funcs.h).
- Make the following changes to [`tictactoe_main.c`](tictactoe_main.c):
  - Add the following:
    - The line `// Help from https://www.man7.org/linux/man-pages/man3/getopt.3.html`
    - One or more `#include` lines
    - `TICTACTOE_MAIN_USAGE`
    - `TICTACTOE_MAIN_OPTIONS`
    - `BACKSLASH_OR_EMPTY_STRING()`
    - `explain_option_error()`
  - Fix a typo(s) in the comment for `scan_options()`.
  - Add the line `optind = 1;` to right below the line `*should_run_demo = false;`.
  - Replace `getopt(argc, argv, "d")` with `getopt(argc, argv, TICTACTOE_MAIN_OPTIONS)`.
  - Replace the lines...
    ```c
    printf("Usage: %s [-d]\n"
          "\t-d\tRun a non-interactive demonstration of this program.\n"
          "\t  \tIf this option is absent, then standard input is used\n"
          "\t  \tto let the user(s) play of this program tic-tac-toe.\n",
          argv[0]);
    ```
    ...with the lines...
    ```c
    explain_option_error(__func__, TICTACTOE_MAIN_OPTIONS, current_option, optopt);
    printf(TICTACTOE_MAIN_USAGE, argv[0]);
    ```
  - Add the following lines at the end of `scan_options()`:
    ```c
    if (optind != argc)
    {
      printf("%s(): Fatal error: `optind` (%d) does not equal `argc` (%d).\n", __func__, optind, argc);
      printf(TICTACTOE_MAIN_USAGE, argv[0]);
      exit(EXIT_FAILURE);
    }
    ```
  - Make `try_scanf_int_from_to()` static.
  - Replace `"\"winner value\" is somehow equals "` with `"\"winner value\" somehow equals "`.
  - There are lines of code between the two `switch` blocks in `play_game()`. Wrap those lines in a `while (1)` block, and add the following the lines at the end of this new `while (1)` block:
    ```c
    else
    {
      break;
    }
    ```
- Remove the following lines from `tictactoe_set_cell()` in [`tictactoe.c`](tictactoe.c):
  ```c
  if (!cell_value)
  {
    PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(cell_value);
    errno = EINVAL;
    return -1;
  }
  ```

# 18 Dec 2025
- Create [`tictactoe_main___A_FILE_TO_USE_FOR_TESTING___play_game.txt`](tictactoe_main___A_FILE_TO_USE_FOR_TESTING___play_game.txt).
- In [`ci.yml`](.github/workflows/ci.yml), replace the lines...
  ```yaml
  - name: Run
    run: ./tictactoe_main
  ```
  ...with the lines...
  ```yaml
  - name: Play game
    run: ./tictactoe_main < tictactoe_main___A_FILE_TO_USE_FOR_TESTING___play_game.txt
  - name: Run demo
    run: ./tictactoe_main -d
  ```

# 25 Dec 2025
- ***Move the following files into a new directory named [`c`](c/):***
  - `error_strings.h`
  - `Makefile`
  - `scanf_funcs.c`
  - `scanf_funcs.h`
  - `tictactoe_main___A_FILE_TO_USE_FOR_TESTING___play_game.txt`
  - `tictactoe_main.c`
  - `tictactoe.c`
  - `tictactoe.h`
- Replace `/tictactoe_main` with `/c/tictactoe_main` in [`.gitignore`](.gitignore).
- Replace "games-c" with "games" in [`README.md`](README.md).
- Replace "C" with "one or more programming languages" in [`README.md`](README.md).
- In [`ci.yml`](.github/workflows/ci.yml), replace the lines...
  ```yaml
  build:

    runs-on: ubuntu-latest
  ```
  ...with the lines...
  ```yaml
  build-c:

    runs-on: ubuntu-latest
    defaults:
      run:
        working-directory: c
  ```
- Make C++ versions of the files in [`c`](c/) and put them in a new directory named [`cpp`](cpp/). Note:
  - The C++ versions of the `.c` files in [`c`](c/) are `.cpp` files.
  - The C++ versions of the `.h` files in [`c`](c/) are `.hpp` files.
- Add the line `/cpp/tictactoe_main` to [`.gitignore`](.gitignore).
- Add new job `build-cpp` to [`ci.yml`](.github/workflows/ci.yml).

# 29 Dec 2025
- All the line `/java/build/` to [`.gitignore`](.gitignore).
- Create [`tictactoe_main___test_input_1.txt`](tictactoe_main___test_input_1.txt).
- Create [`tictactoe_main___test_input_2.txt`](tictactoe_main___test_input_2.txt).
- Delete `c/tictactoe_main___A_FILE_TO_USE_FOR_TESTING___play_game.txt`.
- Delete `cpp/tictactoe_main___A_FILE_TO_USE_FOR_TESTING___play_game.txt`.
- Create [`build.xml`](java/build.xml).
- Create [`TicTacToe_Main.java`](java/src/TicTacToe_Main.java).
- Add new job `build-java` to [`ci.yml`](.github/workflows/ci.yml).
- In [`ci.yml`](.github/workflows/ci.yml), replace each occurrence of the lines...
  ```yaml
  - name: Play game
    run: ./tictactoe_main < tictactoe_main___A_FILE_TO_USE_FOR_TESTING___play_game.txt
  - name: Run demo
    run: ./tictactoe_main -d
  ```
  ...with the lines...
  ```yaml
  - name: Run test 1
    run: ./tictactoe_main < ../tictactoe_main___test_input_1.txt
  - name: Run test 2
    run: ./tictactoe_main < ../tictactoe_main___test_input_2.txt
  ```
- Change the value of `name` in [`ci.yml`](.github/workflows/ci.yml) from `C/C++ CI` to `C/C++/Java CI`.
- Add another URL to the comments at the top of [`ci.yml`](.github/workflows/ci.yml).
- Add the line `#include <stdio.h>` to [`error_strings.h`](c/error_strings.h).
- Remove the line `#include <stdio.h>` from [`scanf_funcs.c`](c/scanf_funcs.c) and [`tictactoe.c`](c/tictactoe.c).
- Add the line `#include <cstdio>` to [`error_strings.hpp`](cpp/error_strings.hpp).
- Remove the line `#include <cstdio>` from [`scanf_funcs.cpp`](cpp/scanf_funcs.cpp) and [`tictactoe.cpp`](cpp/tictactoe.cpp).
- Remove `#include` lines, `TICTACTOE_MAIN_USAGE`, `TICTACTOE_MAIN_OPTIONS`, `BACKSLASH_OR_EMPTY_STRING()`, `explain_option_error()`, `scan_options()`, `try_tictactoe_set_cell()`, and `run_demonstration()` from [`tictactoe_main.c`](c/tictactoe_main.c) and [`tictactoe_main.cpp`](cpp/tictactoe_main.cpp).
- In [`tictactoe_main.c`](c/tictactoe_main.c) and [`tictactoe_main.cpp`](cpp/tictactoe_main.cpp), replace the lines...
  ```c
  int main(int argc, char *argv[])
  {
    bool should_run_demo;

    scan_options(argc, argv, &should_run_demo);

    if (!should_run_demo)
    {
      play_game();
    }
    else
    {
      run_demonstration();
    }

    return 0;
  }
  ```
  ...with the lines...
  ```c
  int main(void)
  {
    play_game();
    return 0;
  }
  ```
- Remove the line `#include <cstdbool>` from [`tictactoe.hpp`](cpp/tictactoe.hpp).

# From 29 Dec 2025 to 30 Dec 2025
- Add `debug="true"` to the `javac` task in [`build.xml`](java/build.xml).
- Create [`TicTacToe.java`](java/src/TicTacToe.java).
- Make the following changes to [`TicTacToe_Main.java`](java/src/TicTacToe_Main.java):
  - Add the line `import java.util.Scanner;`.
  - Add `print_player_info()` to `class TicTacToe_Main`.
  - Add `play_game()` to `class TicTacToe_Main`.
  - In `main()`, replace the lines...
    ```java
    System.out.println("Hello World");
    ```
    ...with the lines...
    ```java
    try (Scanner input_scanner = new Scanner(System.in)) {
      play_game(input_scanner);
    }
    ```

# 30 Dec 2025
- In [`tictactoe.c`](c/tictactoe.c) and [`tictactoe.cpp`](cpp/tictactoe.cpp), make the following changes:
  - Replace `Error: new cell value ('%c') is non-empty.` with `Error: new cell value ('%c') is empty.`.
  - Replace each instance of `"diagonal"` with either `"the bottom-left-to-top-right diagonal"` or `"the top-left-to-bottom-right diagonal"`.
- Create [`ScannerFunctions.java`](java/src/ScannerFunctions.java).

# 15 Jan 2026
- Create a new directory called [`python`](python/).
- Create [`TicTacToe_Main.py`](python/TicTacToe_Main.py).

# 16 Jan 2026
- Add new job `build-python` to [`ci.yml`](.github/workflows/ci.yml).
- Replace `"C/C++/Java CI"` with `"C/C++/Java/Python CI"` in [`ci.yml`](.github/workflows/ci.yml).
- Add the line `/python/__pycache__/` to [`.gitignore`](.gitignore).
- Create [`InputFunctions.py`](python/InputFunctions.py).
- Create [`TicTacToe.py`](python/TicTacToe.py).
- Make the following changes to [`TicTacToe_Main.py`](python/TicTacToe_Main.py):
  - Remove `class TicTacToe`.
  - Remove `get_int_from_to()`.
  - Add two blank lines to right above the line `if __name__ == "__main__":`.
  - Replace the lines...
    ```python
    from enum import Enum

    import re
    ```
    ...with the lines...
    ```python
    from InputFunctions import get_int_from_to
    from TicTacToe import TicTacToe
    ```

# From 1 Feb 2026 to 2 Feb 2026
- Create [`TicTacToe_GUI.java`](java/src/TicTacToe_GUI.java).
- Add the following line to [`build.xml`](java/build.xml):
  ```xml
  <property name="gui_class_TicTacToe" value="TicTacToe_GUI"/>
  ```
- Add the following lines to [`build.xml`](java/build.xml):
  ```xml
  <target name="gui">
      <echo message="GUI..."/>
      <java classname="${gui_class_TicTacToe}" dir="${build_dest_dir}" fork="true"/>
      <echo message="Done with GUI."/>
  </target>
  ```

# From 4 Feb 2026 to 10 Feb 2026
- Add the lines `/go/abc/abc` and `/go/tictactoe/tictactoe` to [`.gitignore`](.gitignore).
- Add new jobs `build-go`, `test-go`, and `run-go` to [`ci.yml`](.github/workflows/ci.yml).
- Change the value of `name` in [`ci.yml`](.github/workflows/ci.yml) from `C/C++/Java/Python CI` to `C/C++/Java/Python/Go CI`.
- Add another URL to the comments at the top of [`ci.yml`](.github/workflows/ci.yml).
- Create the following files:
  - [`go/abc/abc.go`](go/abc/abc.go)
  - [`go/abc/go.mod`](go/abc/go.mod)
  - [`go/scan_funcs/go.mod`](go/scan_funcs/go.mod)
  - [`go/scan_funcs/scan_funcs_test.go`](go/scan_funcs/scan_funcs_test.go)
  - [`go/scan_funcs/scan_funcs.go`](go/scan_funcs/scan_funcs.go)
  - [`go/tictactoe/go.mod`](go/tictactoe/go.mod)
  - [`go/tictactoe/tictactoe_main.go`](go/tictactoe/tictactoe_main.go)
  - [`go/tictactoe/tictactoe.go`](go/tictactoe/tictactoe.go)
