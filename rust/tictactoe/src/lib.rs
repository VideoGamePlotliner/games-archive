// This file was created on 18 Feb 2026.

/**
 * The number of rows and the number of columns.
 */
pub const TICTACTOE_SIZE: usize = 3;

/**
 * Constants for `cell_value` below. Refer to `get_cell()` and `set_cell()`.
 */
#[derive(Clone, Copy, Debug)]
pub enum TicTacToeCellValue {
    ValueForEmpty,
    ValueForX,
    ValueForO,
}

impl TicTacToeCellValue {
    pub fn get_as_char(&self) -> char {
        return match self {
            Self::ValueForEmpty => ' ',
            Self::ValueForX => 'X',
            Self::ValueForO => 'O',
        };
    }
}

/**
 * The only acceptable "winner values". Refer to `who_won()`.
 */
pub enum TicTacToeWinnerValue {
    PlayerWhoUsedXWon,
    PlayerWhoUsedOWon,
    Draw,
    CanKeepPlaying,
}

/**
 * A struct representing the state of a tic-tac-toe game.
 */
pub struct TicTacToe {
    board: [[TicTacToeCellValue; TICTACTOE_SIZE]; TICTACTOE_SIZE],
}

impl TicTacToe {
    pub fn new() -> Self {
        Self {
            board: [[TicTacToeCellValue::ValueForEmpty; TICTACTOE_SIZE]; TICTACTOE_SIZE],
        }
    }

    pub fn print(&self) -> Result<(), String> {
        print!("\n");
        for row in 0..TICTACTOE_SIZE {
            if row > 0 {
                print!("---+---+---\n");
            }
            for col in 0..TICTACTOE_SIZE {
                if col > 0 {
                    print!("|");
                }

                match self.get_cell(row, col) {
                    Ok(cell_value) => print!(" {} ", cell_value.get_as_char()),
                    Err(s) => return Err(s),
                }
            }
            print!("\n");
        }
        print!("\n");
        return Ok(());
    }

    pub fn get_cell(&self, row: usize, col: usize) -> Result<TicTacToeCellValue, String> {
        match Self::ensure_row_col_in_bounds(row, col) {
            Ok(_) => (),
            Err(s) => return Err(s),
        }

        let cell_value = self.board[row][col];

        return Ok(cell_value);
    }

    /**
     * If `Err((b, ...))` is returned by this method,
     * then `b` is whether the cell in question is already non-empty.
     */
    pub fn set_cell(
        &mut self,
        row: usize,
        col: usize,
        new_cell_value: TicTacToeCellValue,
    ) -> Result<(), (bool, String)> {
        match Self::ensure_row_col_in_bounds(row, col) {
            Ok(_) => (),
            Err(s) => return Err((false, s)),
        }
        match new_cell_value {
            TicTacToeCellValue::ValueForEmpty => {
                return Err((false, format!("New cell value is empty")));
            }
            _ => (),
        }

        let old_cell_value = self.board[row][col];

        match old_cell_value {
            TicTacToeCellValue::ValueForEmpty => (),
            _ => {
                return Err((
                    true,
                    format!(
                        "Cell at row {} and column {} has non-empty cell value '{}'.",
                        row,
                        col,
                        old_cell_value.get_as_char()
                    ),
                ));
            }
        }

        self.board[row][col] = new_cell_value;
        return Ok(());
    }

    /**
     * A true/false question: Is the given number a valid row/column index for a
     * tic-tac-toe game?
     */
    fn is_in_bounds(i: usize) -> bool {
        return /* i >= 0 && */ i < TICTACTOE_SIZE;
    }

    fn ensure_row_col_in_bounds(row: usize, col: usize) -> Result<(), String> {
        let row_is_in_bounds = Self::is_in_bounds(row);
        let col_is_in_bounds = Self::is_in_bounds(col);

        if !row_is_in_bounds && !col_is_in_bounds {
            return Err(format!(
                "Row {} and column {} are both out of bounds.",
                row, col
            ));
        }
        if !row_is_in_bounds {
            return Err(format!(
                "Row {} (but not column {}) is out of bounds.",
                row, col
            ));
        }
        if !col_is_in_bounds {
            return Err(format!(
                "Column {} (but not row {}) is out of bounds.",
                col, row
            ));
        }
        return Ok(());
    }

    /**
     * This method is only to be called by `who_won()`.
     *
     * `winners_of_this_line[0]` is whether the player who used X won this line.
     * `winners_of_this_line[1]` is whether the player who used O won this line.
     */
    fn who_won_react_to_cell_value(
        cell_value: TicTacToeCellValue,
        winners_of_this_line: &mut [bool; 2],
    ) {
        match cell_value {
            TicTacToeCellValue::ValueForX => winners_of_this_line[1] = false,
            TicTacToeCellValue::ValueForO => winners_of_this_line[0] = false,
            TicTacToeCellValue::ValueForEmpty => {
                winners_of_this_line[0] = false;
                winners_of_this_line[1] = false
            }
        }
    }

    /**
     * This method is only to be called by `who_won()`.
     *
     * `winners_of_this_line[0]` is whether the player who used X won this line.
     * `winners_of_this_line[1]` is whether the player who used O won this line.
     *
     * `winners_of_this_game[0]` is whether the player who used X won this game.
     * `winners_of_this_game[1]` is whether the player who used O won this game.
     */
    fn who_won_apply_line_results(
        which_line_is_this: String,
        winners_of_this_line: &[bool; 2],
        winners_of_this_game: &mut [bool; 2],
    ) -> Result<(), String> {
        if winners_of_this_line[0] && winners_of_this_line[1] {
            return Err(format!("Somehow, both players won {}.", which_line_is_this));
        } else if winners_of_this_line[0] {
            winners_of_this_game[0] = true;
        } else if winners_of_this_line[1] {
            winners_of_this_game[1] = true;
        }
        return Ok(());
    }

    pub fn who_won(&self) -> Result<TicTacToeWinnerValue, String> {
        /*
         * Index 0 is for the player who used X.
         * Index 1 is for the player who used O.
         */
        let mut winners_of_this_game = [false; 2];

        /*
         * Index 0 is for the player who used X.
         * Index 1 is for the player who used O.
         */
        let mut winners_of_this_line = [false; 2];

        for row in 0..TICTACTOE_SIZE {
            // Within this block, "this line" refers to the row with the given index (that is, `row`).
            winners_of_this_line[0] = true;
            winners_of_this_line[1] = true;

            for col in 0..TICTACTOE_SIZE {
                Self::who_won_react_to_cell_value(self.board[row][col], &mut winners_of_this_line);
            }
            match Self::who_won_apply_line_results(
                format!("row {}", row),
                &winners_of_this_line,
                &mut winners_of_this_game,
            ) {
                Ok(_) => (),
                Err(s) => return Err(s),
            }
        }
        for col in 0..TICTACTOE_SIZE {
            // Within this block, "this line" refers to the column with the given index (that is, `col`).
            winners_of_this_line[0] = true;
            winners_of_this_line[1] = true;

            for row in 0..TICTACTOE_SIZE {
                Self::who_won_react_to_cell_value(self.board[row][col], &mut winners_of_this_line);
            }
            match Self::who_won_apply_line_results(
                format!("column {}", col),
                &winners_of_this_line,
                &mut winners_of_this_game,
            ) {
                Ok(_) => (),
                Err(s) => return Err(s),
            }
        }

        {
            // Within this block, "this line" refers to the bottom-left-to-top-right diagonal.
            winners_of_this_line[0] = true;
            winners_of_this_line[1] = true;

            for row in 0..TICTACTOE_SIZE {
                let col = TICTACTOE_SIZE - 1 - row;
                Self::who_won_react_to_cell_value(self.board[row][col], &mut winners_of_this_line);
            }
            match Self::who_won_apply_line_results(
                format!("the bottom-left-to-top-right diagonal"),
                &winners_of_this_line,
                &mut winners_of_this_game,
            ) {
                Ok(_) => (),
                Err(s) => return Err(s),
            }
        }

        {
            // Within this block, "this line" refers to the top-left-to-bottom-right diagonal.
            winners_of_this_line[0] = true;
            winners_of_this_line[1] = true;

            for row in 0..TICTACTOE_SIZE {
                let col = row;
                Self::who_won_react_to_cell_value(self.board[row][col], &mut winners_of_this_line);
            }
            match Self::who_won_apply_line_results(
                format!("the top-left-to-bottom-right diagonal"),
                &winners_of_this_line,
                &mut winners_of_this_game,
            ) {
                Ok(_) => (),
                Err(s) => return Err(s),
            }
        }

        if winners_of_this_game[0] && winners_of_this_game[1] {
            return Err(format!("Somehow, both players won this game, but how?"));
        } else if winners_of_this_game[0] {
            return Ok(TicTacToeWinnerValue::PlayerWhoUsedXWon);
        } else if winners_of_this_game[1] {
            return Ok(TicTacToeWinnerValue::PlayerWhoUsedOWon);
        } else if self.get_num_empty_cells() > 0 {
            return Ok(TicTacToeWinnerValue::CanKeepPlaying);
        } else {
            return Ok(TicTacToeWinnerValue::Draw);
        }
    }

    fn get_num_empty_cells(&self) -> i32 {
        let mut num_empty_cells = 0;
        for row in 0..TICTACTOE_SIZE {
            for col in 0..TICTACTOE_SIZE {
                match self.board[row][col] {
                    TicTacToeCellValue::ValueForEmpty => {
                        num_empty_cells += 1;
                    }
                    _ => (),
                }
            }
        }
        return num_empty_cells;
    }
}
