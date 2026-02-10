// This file was created on 4 Feb 2026.

package main

import (
	"fmt"
)

/**
 * The number of rows in a tic-tac-toe game.
 * This is also the number of columns.
 */
const TICTACTOE_SIZE = 3

/**
 * A true/false question:
 * Is the given number a valid row/column index for a tic-tac-toe game?
 */
func TicTacToe_IsInBounds(i int) bool {
	return (i >= 0 && i < TICTACTOE_SIZE)
}

/**
 * Constants for `cell_value` below.
 * Refer to `tictactoe_get_cell()` and `tictactoe_set_cell()`.
 */
const (
	TICTACTOE_CELL_VALUE_FOR_EMPTY = ' '
	TICTACTOE_CELL_VALUE_FOR_X     = 'X'
	TICTACTOE_CELL_VALUE_FOR_O     = 'O'
	TICTACTOE_BAD_CELL_VALUE       = '?'
)

/**
 * A true/false question:
 * Is the given number a valid cell value for a tic-tac-toe game?
 */
func TicTacToe_IsValidCellValue(cell_value rune) bool {
	return (cell_value == TICTACTOE_CELL_VALUE_FOR_EMPTY) || (cell_value == TICTACTOE_CELL_VALUE_FOR_X) || (cell_value == TICTACTOE_CELL_VALUE_FOR_O)
}

/**
 * A struct representing the state of a tic-tac-toe game.
 */
type TicTacToe struct {
	/**
	 * This member is not to be accessed directly.
	 * Access this member via `tictactoe_*()`.
	 */
	board [TICTACTOE_SIZE][TICTACTOE_SIZE]rune
}

/**
 * The only acceptable "winner values".
 * Refer to `tictactoe_who_won()`.
 */
const (
	WINNER_VALUE_PLAYER_WHO_USED_X_WON = 10001
	WINNER_VALUE_PLAYER_WHO_USED_O_WON = 10002
	WINNER_VALUE_DRAW                  = 10003
	WINNER_VALUE_CAN_KEEP_PLAYING      = 10004
)

func TicTacToe_Init(ttt *TicTacToe) {
	for row := range TICTACTOE_SIZE {
		for col := range TICTACTOE_SIZE {
			ttt.board[row][col] = TICTACTOE_CELL_VALUE_FOR_EMPTY
		}
	}
}

func TicTacToe_Print(ttt TicTacToe) error {
	var cell_value rune
	var err error

	fmt.Printf("\n")
	for row := range TICTACTOE_SIZE {
		if row > 0 {
			fmt.Printf("---+---+---\n")
		}
		for col := range TICTACTOE_SIZE {
			if col > 0 {
				fmt.Printf("|")
			}
			cell_value, err = TicTacToe_GetCell(ttt, row, col)
			if err != nil {
				return err
			}
			fmt.Printf(" %c ", cell_value)
		}
		fmt.Printf("\n")
	}
	fmt.Printf("\n")

	return nil
}

func TicTacToe_EnsureRowColInBounds(row int, col int) error {
	var row_is_in_bounds bool
	var col_is_in_bounds bool

	row_is_in_bounds = TicTacToe_IsInBounds(row)
	col_is_in_bounds = TicTacToe_IsInBounds(col)

	if !row_is_in_bounds && !col_is_in_bounds {
		return fmt.Errorf("Row %d and column %d are both out of bounds.", row, col)
	}
	if !row_is_in_bounds {
		return fmt.Errorf("Row %d (but not column %d) is out of bounds.", row, col)
	}
	if !col_is_in_bounds {
		return fmt.Errorf("Column %d (but not row %d) is out of bounds.", row, col)
	}
	return nil
}

func TicTacToe_GetCell(ttt TicTacToe, row int, col int) (rune, error) {
	var cell_value rune
	var err error

	err = TicTacToe_EnsureRowColInBounds(row, col)
	if err != nil {
		return 0, err
	}

	cell_value = ttt.board[row][col]

	if !TicTacToe_IsValidCellValue(cell_value) {
		return 0, fmt.Errorf("Cell at row %d and column %d has invalid cell value '%c'.", row, col, cell_value)
	}

	return cell_value, nil
}

/**
 * If the `error` value returned by this method does not equal `nil`,
 * then the `bool` value returned by this method is whether the cell in question is already non-empty.
 */
func TicTacToe_SetCell(ttt *TicTacToe, row int, col int, new_cell_value rune) (bool, error) {
	var old_cell_value rune
	var err error

	err = TicTacToe_EnsureRowColInBounds(row, col)
	if err != nil {
		return false, err
	}
	if !TicTacToe_IsValidCellValue(new_cell_value) {
		return false, fmt.Errorf("New cell value ('%c') is invalid.", new_cell_value)
	}
	if new_cell_value == TICTACTOE_CELL_VALUE_FOR_EMPTY {
		return false, fmt.Errorf("New cell value ('%c') is empty.", new_cell_value)
	}

	old_cell_value = ttt.board[row][col]

	if !TicTacToe_IsValidCellValue(old_cell_value) {
		return false, fmt.Errorf("Cell at row %d and column %d has invalid cell value '%c'.", row, col, old_cell_value)
	}
	if old_cell_value != TICTACTOE_CELL_VALUE_FOR_EMPTY {
		return true, fmt.Errorf("Cell at row %d and column %d has non-empty cell value '%c'.", row, col, old_cell_value)
	}

	ttt.board[row][col] = new_cell_value
	return false, nil
}

/**
 * This method is only to be called by `TicTacToe_WhoWon()`.
 *
 * `winners_of_this_line[0]` is whether the player who used X won this line.
 * `winners_of_this_line[1]` is whether the player who used O won this line.
 */
func TicTacToe_WhoWon_ReactToCellValue(row int, col int, cell_value rune, winners_of_this_line *[2]bool) error {
	switch cell_value {
	case TICTACTOE_CELL_VALUE_FOR_X:
		winners_of_this_line[1] = false
		return nil
	case TICTACTOE_CELL_VALUE_FOR_O:
		winners_of_this_line[0] = false
		return nil
	case TICTACTOE_CELL_VALUE_FOR_EMPTY:
		winners_of_this_line[0] = false
		winners_of_this_line[1] = false
		return nil
	default:
		return fmt.Errorf("Cell at row %d and column %d has invalid cell value '%c'.", row, col, cell_value)
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
func TicTacToe_WhoWon_ApplyLineResults(which_line_is_this string, winners_of_this_line [2]bool, winners_of_this_game *[2]bool) error {
	if winners_of_this_line[0] && winners_of_this_line[1] {
		return fmt.Errorf("Somehow, both players won %s.", which_line_is_this)
	} else if winners_of_this_line[0] {
		winners_of_this_game[0] = true
	} else if winners_of_this_line[1] {
		winners_of_this_game[1] = true
	}
	return nil
}

func TicTacToe_WhoWon(ttt TicTacToe) (int, error) {
	/**
	 * Index 0 is for the player who used X.
	 * Index 1 is for the player who used O.
	 */
	var winners_of_this_game [2]bool
	var winners_of_this_line [2]bool
	var err error

	winners_of_this_game[0] = false
	winners_of_this_game[1] = false
	winners_of_this_line[0] = false
	winners_of_this_line[1] = false

	for row := range TICTACTOE_SIZE {
		// Within this block, "this line" refers to the row with the given index (that is, `row`).
		winners_of_this_line[0] = true
		winners_of_this_line[1] = true

		for col := range TICTACTOE_SIZE {
			err = TicTacToe_WhoWon_ReactToCellValue(row, col, ttt.board[row][col], &winners_of_this_line)
			if err != nil {
				return 0, err
			}
		}
		err = TicTacToe_WhoWon_ApplyLineResults(fmt.Sprintf("row %d", row), winners_of_this_line, &winners_of_this_game)
		if err != nil {
			return 0, err
		}
	}
	for col := range TICTACTOE_SIZE {
		// Within this block, "this line" refers to the column with the given index (that is, `col`).
		winners_of_this_line[0] = true
		winners_of_this_line[1] = true

		for row := range TICTACTOE_SIZE {
			err = TicTacToe_WhoWon_ReactToCellValue(row, col, ttt.board[row][col], &winners_of_this_line)
			if err != nil {
				return 0, err
			}

		}
		err = TicTacToe_WhoWon_ApplyLineResults(fmt.Sprintf("column %d", col), winners_of_this_line, &winners_of_this_game)
		if err != nil {
			return 0, err
		}
	}

	{
		// Within this block, "this line" refers to the bottom-left-to-top-right diagonal.
		winners_of_this_line[0] = true
		winners_of_this_line[1] = true

		for row := range TICTACTOE_SIZE {
			var col int = TICTACTOE_SIZE - 1 - row
			err = TicTacToe_WhoWon_ReactToCellValue(row, col, ttt.board[row][col], &winners_of_this_line)
			if err != nil {
				return 0, err
			}
		}
		err = TicTacToe_WhoWon_ApplyLineResults("the bottom-left-to-top-right diagonal", winners_of_this_line, &winners_of_this_game)
		if err != nil {
			return 0, err
		}
	}

	{
		// Within this block, "this line" refers to the top-left-to-bottom-right diagonal.
		winners_of_this_line[0] = true
		winners_of_this_line[1] = true

		for row := range TICTACTOE_SIZE {
			var col int = row
			err = TicTacToe_WhoWon_ReactToCellValue(row, col, ttt.board[row][col], &winners_of_this_line)
			if err != nil {
				return 0, err
			}
		}
		err = TicTacToe_WhoWon_ApplyLineResults("the top-left-to-bottom-right diagonal", winners_of_this_line, &winners_of_this_game)
		if err != nil {
			return 0, err
		}
	}

	if winners_of_this_game[0] && winners_of_this_game[1] {
		return 0, fmt.Errorf("Somehow, both players won this game, but how?")
	} else if winners_of_this_game[0] {
		return WINNER_VALUE_PLAYER_WHO_USED_X_WON, nil
	} else if winners_of_this_game[1] {
		return WINNER_VALUE_PLAYER_WHO_USED_O_WON, nil
	} else if TicTacToe_GetNumEmptyCells(ttt) > 0 {
		return WINNER_VALUE_CAN_KEEP_PLAYING, nil
	} else {
		return WINNER_VALUE_DRAW, nil
	}
}

func TicTacToe_GetNumEmptyCells(ttt TicTacToe) int {
	var num_empty_cells int = 0
	for row := range TICTACTOE_SIZE {
		for col := range TICTACTOE_SIZE {
			if ttt.board[row][col] == TICTACTOE_CELL_VALUE_FOR_EMPTY {
				num_empty_cells++
			}
		}
	}
	return num_empty_cells
}
