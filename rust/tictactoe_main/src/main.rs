// This file was created on 18 Feb 2026.

use tictactoe::{TICTACTOE_SIZE, TicTacToe, TicTacToeCellValue, TicTacToeWinnerValue};

fn print_player_info(which_player_is_using_x: i32, which_player_has_turn_right_now: i32) -> Result<(), String> {
    if which_player_has_turn_right_now < 1 || which_player_has_turn_right_now > 2 {
        return Err(format!(
            "Fatal error: it is somehow Player {}'s turn right now.\n",
            which_player_has_turn_right_now
        ));
    }
    if which_player_is_using_x < 1 || which_player_is_using_x > 2 {
        return Err(format!(
            "Fatal error: it is somehow Player {} who is using X.\n",
            which_player_is_using_x
        ));
    }

    let cell_value_for_x_as_char = TicTacToeCellValue::ValueForX.get_as_char();
    let cell_value_for_o_as_char = TicTacToeCellValue::ValueForO.get_as_char();

    let mut what_player_1_is_using = cell_value_for_o_as_char;
    if which_player_is_using_x == 1 {
        what_player_1_is_using = cell_value_for_x_as_char;
    }

    let mut what_player_2_is_using = cell_value_for_o_as_char;
    if which_player_is_using_x == 2 {
        what_player_2_is_using = cell_value_for_x_as_char;
    }

    print!(
        "\n\n\n\n\nPlayer 1 is using {}.\nPlayer 2 is using {}.\nIt is Player {}'s turn.\n\n",
        what_player_1_is_using, what_player_2_is_using, which_player_has_turn_right_now
    );
    return Ok(());
}

fn play_game() -> Result<(), String> {
    let mut ttt = TicTacToe::new();

    /* Is it Player 1 or Player 2 who's using X? */
    let which_player_is_using_x =
        match scanfuncs::get_i32_from_to("Who will be playing as X? Player 1 or Player 2?", 1, 2) {
            Ok(i) => i,
            Err(e) => return Err(e.to_string()),
        };

    /* Which player's turn is it right now? */
    let mut which_player_has_turn_right_now = 1;

    loop {
        match print_player_info(which_player_is_using_x, which_player_has_turn_right_now) {
            Ok(_) => (),
            Err(s) => return Err(s),
        }

        match ttt.print() {
            Ok(_) => (),
            Err(s) => return Err(s),
        }

        let winner_value = match ttt.who_won() {
            Ok(v) => v,
            Err(s) => return Err(s),
        };

        match winner_value {
            TicTacToeWinnerValue::PlayerWhoUsedXWon => {
                if which_player_is_using_x == 1 {
                    print!("Game over. The winner is Player 1.\n");
                } else {
                    print!("Game over. The winner is Player 2.\n");
                }
                return Ok(());
            }
            TicTacToeWinnerValue::PlayerWhoUsedOWon => {
                if which_player_is_using_x == 1 {
                    print!("Game over. The winner is Player 2.\n");
                } else {
                    print!("Game over. The winner is Player 1.\n");
                }
                return Ok(());
            }
            TicTacToeWinnerValue::Draw => {
                print!("Game over. The game is a draw.\n");
                return Ok(());
            }
            TicTacToeWinnerValue::CanKeepPlaying => {
                print!("The game continues.\n");
            }
        }

        loop {
            let tictactoe_size_i32: i32 = match TICTACTOE_SIZE.try_into() {
                Ok(i) => i,
                Err(e) => return Err(e.to_string()),
            };

            let row_i32 = match scanfuncs::get_i32_from_to(
                "In which row do you want to place your piece? (Note: 0 represents the top row.)",
                0,
                tictactoe_size_i32 - 1,
            ) {
                Ok(i) => i,
                Err(e) => return Err(e.to_string()),
            };

            let row: usize = match row_i32.try_into() {
                Ok(i) => i,
                Err(e) => return Err(e.to_string()),
            };

            let col_i32 = match scanfuncs::get_i32_from_to(
                "In which column do you want to place your piece? (Note: 0 represents the leftmost column.)",
                0,
                tictactoe_size_i32 - 1,
            ) {
                Ok(i) => i,
                Err(e) => return Err(e.to_string()),
            };

            let col: usize = match col_i32.try_into() {
                Ok(i) => i,
                Err(e) => return Err(e.to_string()),
            };

            let mut cell_value = TicTacToeCellValue::ValueForO;
            if which_player_has_turn_right_now == which_player_is_using_x {
                cell_value = TicTacToeCellValue::ValueForX;
            }

            match ttt.set_cell(row, col, cell_value) {
                Ok(_) => (),
                Err((cell_already_filled, s)) => {
                    if cell_already_filled {
                        print!("Failed to place piece. Try again.\n");
                        continue;
                    }
                    return Err(s);
                }
            }
            break;
        }

        if which_player_has_turn_right_now < 1 || which_player_has_turn_right_now > 2 {
            return Err(format!(
                "Fatal error: it is somehow Player {}'s turn right now.\n",
                which_player_has_turn_right_now
            ));
        } else {
            which_player_has_turn_right_now = 3 - which_player_has_turn_right_now;
        }
    }
}

fn main() {
    match play_game() {
        Ok(_) => (),
        Err(s) => panic!("{}", s),
    }
}
