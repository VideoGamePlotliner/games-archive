// This file was created on 29 Dec 2025.

public class TicTacToe {

    /**
     * This exception is thrown by `set_cell()` if and only if the cell you're
     * trying to fill is already filled.
     */
    public class CellAlreadyFilledException extends Exception {

        public CellAlreadyFilledException(String s) {
            super(s);
        }
    }

    /**
     * Constants for `cell_value` below. Refer to `get_cell()` and `set_cell()`.
     */
    public enum CellValue {
        VALUE_FOR_EMPTY(' '),
        VALUE_FOR_X('X'),
        VALUE_FOR_O('O');

        private final char as_char;

        private CellValue(char as_char) {
            this.as_char = as_char;
        }

        public char get_as_char() {
            return as_char;
        }
    }

    /**
     * The only acceptable "winner values". Refer to `who_won()`.
     */
    public enum WinnerValue {
        PLAYER_WHO_USED_X_WON,
        PLAYER_WHO_USED_O_WON,
        DRAW,
        CAN_KEEP_PLAYING
    }

    /**
     * The number of rows and the number of columns.
     */
    public static final int SIZE = 3;

    private final CellValue[][] board = new CellValue[SIZE][SIZE];

    public TicTacToe() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                board[row][col] = CellValue.VALUE_FOR_EMPTY;
            }
        }
    }

    public void print() {
        System.out.printf("\n");
        for (int row = 0; row < SIZE; row++) {
            if (row > 0) {
                System.out.printf("---+---+---\n");
            }
            for (int col = 0; col < SIZE; col++) {
                if (col > 0) {
                    System.out.printf("|");
                }

                final CellValue cell_value = get_cell(row, col);

                if (cell_value == null) {
                    throw new Error(String.format("Cell at row %d and column %d has null cell value.", row, col));
                }
                System.out.printf(" %c ", cell_value.get_as_char());
            }
            System.out.printf("\n");
        }
        System.out.printf("\n");
    }

    public CellValue get_cell(int row, int col) {
        ensure_row_col_in_bounds(row, col);

        final CellValue cell_value = board[row][col];

        if (cell_value == null) {
            throw new Error(String.format("Cell at row %d and column %d has null cell value.", row, col));
        }
        return cell_value;
    }

    public void set_cell(int row, int col, CellValue new_cell_value) throws CellAlreadyFilledException {
        ensure_row_col_in_bounds(row, col);

        if (new_cell_value == null) {
            throw new NullPointerException("New cell value is null");
        }
        if (new_cell_value.equals(CellValue.VALUE_FOR_EMPTY)) {
            throw new IllegalArgumentException("New cell value is empty");
        }

        final CellValue old_cell_value = board[row][col];

        if (old_cell_value == null) {
            throw new Error(String.format("Cell at row %d and column %d has null cell value.", row, col));
        }
        if (!old_cell_value.equals(CellValue.VALUE_FOR_EMPTY)) {
            throw new CellAlreadyFilledException(String.format("Cell at row %d and column %d has non-empty cell value '%c'.", row, col, old_cell_value.get_as_char()));
        }

        board[row][col] = new_cell_value;
    }

    /**
     * A true/false question: Is the given number a valid row/column index for a
     * tic-tac-toe game?
     */
    private static boolean is_in_bounds(int i) {
        return (i >= 0 && i < SIZE);
    }

    private static void ensure_row_col_in_bounds(int row, int col) {
        final boolean row_is_in_bounds = is_in_bounds(row);
        final boolean col_is_in_bounds = is_in_bounds(col);

        if (!row_is_in_bounds && !col_is_in_bounds) {
            throw new IndexOutOfBoundsException(String.format("Row %d and column %d are both out of bounds.", row, col));
        }
        if (!row_is_in_bounds) {
            throw new IndexOutOfBoundsException(String.format("Row %d (but not column %d) is out of bounds.", row, col));
        }
        if (!col_is_in_bounds) {
            throw new IndexOutOfBoundsException(String.format("Column %d (but not row %d) is out of bounds.", col, row));
        }
    }

    private static void ensure_valid_winners_variable(String variable_name, boolean[] variable_itself) {
        if (variable_itself == null) {
            throw new NullPointerException(String.format("`%s` is null.", variable_name));
        }
        if (variable_itself.length != 2) {
            throw new IllegalArgumentException(String.format("`%s.length` is %d, even though it should be 2.", variable_name, variable_itself.length));
        }
    }

    /**
     * This method is only to be called by `who_won()`.
     *
     * `winners_of_this_line[0]` is whether the player who used X won this line.
     *
     * `winners_of_this_line[1]` is whether the player who used O won this line.
     */
    private static void who_won___react_to_cell_value(int row, int col, CellValue cell_value, boolean[] winners_of_this_line) {
        ensure_valid_winners_variable("winners_of_this_line", winners_of_this_line);

        switch (cell_value) {
            case VALUE_FOR_X:
                winners_of_this_line[1] = false;
                break;
            case VALUE_FOR_O:
                winners_of_this_line[0] = false;
                break;
            case VALUE_FOR_EMPTY:
                winners_of_this_line[0] = false;
                winners_of_this_line[1] = false;
                break;
            default:
                throw new Error(String.format("Cell at row %d and column %d has invalid (possibly null) cell value.", row, col));
        }
    }

    /**
     * This method is only to be called by `who_won()`.
     *
     * `winners_of_this_line[0]` is whether the player who used X won this line.
     *
     * `winners_of_this_line[1]` is whether the player who used O won this line.
     *
     * `winners_of_this_game[0]` is whether the player who used X won this game.
     *
     * `winners_of_this_game[1]` is whether the player who used O won this game.
     */
    private static void who_won___apply_line_results(String which_line_is_this, boolean[] winners_of_this_line, boolean[] winners_of_this_game) {
        ensure_valid_winners_variable("winners_of_this_line", winners_of_this_line);
        ensure_valid_winners_variable("winners_of_this_game", winners_of_this_game);

        if (winners_of_this_line[0] && winners_of_this_line[1]) {
            throw new Error(String.format("Somehow, both players won %s.", which_line_is_this));
        } else if (winners_of_this_line[0]) {
            winners_of_this_game[0] = true;
        } else if (winners_of_this_line[1]) {
            winners_of_this_game[1] = true;
        }
    }

    public WinnerValue who_won() {

        /**
         * Index 0 is for the player who used X.
         *
         * Index 1 is for the player who used O.
         */
        final boolean[] winners_of_this_game = new boolean[]{false, false};

        /**
         * Index 0 is for the player who used X.
         *
         * Index 1 is for the player who used O.
         */
        final boolean[] winners_of_this_line = new boolean[]{false, false};

        for (int row = 0; row < SIZE; row++) {
            // Within this block, "this line" refers to the row with the given index (that is, `row`).
            winners_of_this_line[0] = true;
            winners_of_this_line[1] = true;

            for (int col = 0; col < SIZE; col++) {
                who_won___react_to_cell_value(row, col, board[row][col], winners_of_this_line);
            }
            who_won___apply_line_results(String.format("row %d", row), winners_of_this_line, winners_of_this_game);
        }
        for (int col = 0; col < SIZE; col++) {
            // Within this block, "this line" refers to the column with the given index (that is, `col`).
            winners_of_this_line[0] = true;
            winners_of_this_line[1] = true;

            for (int row = 0; row < SIZE; row++) {
                who_won___react_to_cell_value(row, col, board[row][col], winners_of_this_line);
            }
            who_won___apply_line_results(String.format("column %d", col), winners_of_this_line, winners_of_this_game);
        }

        {
            // Within this block, "this line" refers to the bottom-left-to-top-right diagonal.
            winners_of_this_line[0] = true;
            winners_of_this_line[1] = true;

            for (int row = 0; row < SIZE; row++) {
                final int col = SIZE - 1 - row;
                who_won___react_to_cell_value(row, col, board[row][col], winners_of_this_line);
            }
            who_won___apply_line_results("the bottom-left-to-top-right diagonal", winners_of_this_line, winners_of_this_game);
        }

        {
            // Within this block, "this line" refers to the top-left-to-bottom-right diagonal.
            winners_of_this_line[0] = true;
            winners_of_this_line[1] = true;

            for (int row = 0; row < SIZE; row++) {
                final int col = row;
                who_won___react_to_cell_value(row, col, board[row][col], winners_of_this_line);
            }
            who_won___apply_line_results("the top-left-to-bottom-right diagonal", winners_of_this_line, winners_of_this_game);
        }

        if (winners_of_this_game[0] && winners_of_this_game[1]) {
            throw new Error("Somehow, both players won this game, but how?");
        } else if (winners_of_this_game[0]) {
            return WinnerValue.PLAYER_WHO_USED_X_WON;
        } else if (winners_of_this_game[1]) {
            return WinnerValue.PLAYER_WHO_USED_O_WON;
        } else {
            return (get_num_empty_cells() > 0) ? WinnerValue.CAN_KEEP_PLAYING : WinnerValue.DRAW;
        }
    }

    private int get_num_empty_cells() {
        int num_empty_cells = 0;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                final CellValue cell_value = board[row][col];
                if (cell_value == null) {
                    throw new Error(String.format("Cell at row %d and column %d has null cell value.", row, col));
                }
                if (cell_value.equals(CellValue.VALUE_FOR_EMPTY)) {
                    num_empty_cells++;
                }
            }
        }
        return num_empty_cells;
    }
}
