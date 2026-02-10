// This file was created on 4 Feb 2026.

package main

import (
	"fmt"
	"go_games/scan_funcs"
	"log"
)

func TicTacToe_Main_PrintPlayerInfo(which_player_is_using_x int, which_player_has_turn_right_now int) error {
	if which_player_has_turn_right_now < 1 || which_player_has_turn_right_now > 2 {
		return fmt.Errorf("Fatal error: it is somehow Player %d's turn right now.\n",
			which_player_has_turn_right_now)
	}
	if which_player_is_using_x < 1 || which_player_is_using_x > 2 {
		return fmt.Errorf("Fatal error: it is somehow Player %d who is using X.\n",
			which_player_is_using_x)
	}

	if which_player_is_using_x == 1 {
		fmt.Printf("\n\n\n\n\nPlayer 1 is using %c.\nPlayer 2 is using %c.\nIt is Player %d's turn.\n\n",
			TICTACTOE_CELL_VALUE_FOR_X,
			TICTACTOE_CELL_VALUE_FOR_O,
			which_player_has_turn_right_now)
	} else {
		fmt.Printf("\n\n\n\n\nPlayer 1 is using %c.\nPlayer 2 is using %c.\nIt is Player %d's turn.\n\n",
			TICTACTOE_CELL_VALUE_FOR_O,
			TICTACTOE_CELL_VALUE_FOR_X,
			which_player_has_turn_right_now)
	}
	return nil
}

func TicTacToe_Main_PlayGame() error {
	var ttt TicTacToe
	var err error
	var winner_value int

	/* Is it Player 1 or Player 2 who's using X? */
	var which_player_is_using_x int

	/* Which player's turn is it right now? */
	var which_player_has_turn_right_now int

	TicTacToe_Init(&ttt)

	which_player_is_using_x, err = scan_funcs.GetIntFromTo("Who will be playing as X? Player 1 or Player 2?", 1, 2)
	if err != nil {
		return err
	}

	which_player_has_turn_right_now = 1

	for {
		err = TicTacToe_Main_PrintPlayerInfo(which_player_is_using_x, which_player_has_turn_right_now)
		if err != nil {
			return err
		}

		err = TicTacToe_Print(ttt)
		if err != nil {
			return err
		}

		winner_value, err = TicTacToe_WhoWon(ttt)
		if err != nil {
			return err
		}

		switch winner_value {
		default:
			return fmt.Errorf("Fatal error: this game's \"winner value\" somehow equals %d.", winner_value)
		case WINNER_VALUE_PLAYER_WHO_USED_X_WON:
			fmt.Printf("Game over. The winner is Player %d.\n", which_player_is_using_x)
			return nil
		case WINNER_VALUE_PLAYER_WHO_USED_O_WON:
			fmt.Printf("Game over. The winner is Player %d.\n", 3-which_player_is_using_x)
			return nil
		case WINNER_VALUE_DRAW:
			fmt.Printf("Game over. The game is a draw.\n")
			return nil
		case WINNER_VALUE_CAN_KEEP_PLAYING:
			fmt.Printf("The game continues.\n")
		}

		for {
			var row int
			var col int
			var cell_already_fllled bool

			row, err = scan_funcs.GetIntFromTo("In which row do you want to place your piece? (Note: 0 represents the top row.)", 0, TICTACTOE_SIZE-1)
			if err != nil {
				return err
			}

			col, err = scan_funcs.GetIntFromTo("In which column do you want to place your piece? (Note: 0 represents the leftmost column.)", 0, TICTACTOE_SIZE-1)
			if err != nil {
				return err
			}

			if which_player_has_turn_right_now == which_player_is_using_x {
				cell_already_fllled, err = TicTacToe_SetCell(&ttt, row, col, TICTACTOE_CELL_VALUE_FOR_X)
			} else {
				cell_already_fllled, err = TicTacToe_SetCell(&ttt, row, col, TICTACTOE_CELL_VALUE_FOR_O)
			}

			if err != nil {
				if cell_already_fllled {
					fmt.Printf("Failed to place piece. Try again.\n")
					continue
				}
				return err
			}
			break
		}

		switch which_player_has_turn_right_now {
		default:
			return fmt.Errorf("Fatal error: it is somehow Player %d's turn right now.\n", which_player_has_turn_right_now)
		case 1, 2:
			which_player_has_turn_right_now = 3 - which_player_has_turn_right_now
		}
	}
}

func main() {
	var err error = TicTacToe_Main_PlayGame()
	if err != nil {
		log.Fatalf("`TicTacToe_Main_PlayGame()` failed: %v", err)
	}
}
