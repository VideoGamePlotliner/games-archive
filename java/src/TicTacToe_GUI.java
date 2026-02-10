// This file was created on 1 Feb 2026.

// Help from...
// - https://docs.oracle.com/javase/tutorial/uiswing/components/frame.html
// - https://docs.oracle.com/javase/tutorial/uiswing/components/label.html
// - https://docs.oracle.com/en/java/javase/11/docs/api/java.desktop/java/awt/GridBagLayout.html
// - https://docs.oracle.com/en/java/javase/11/docs/api/java.desktop/java/awt/Component.html
// - https://developer.classpath.org/doc/javax/swing/JOptionPane-source.html
// - https://docs.oracle.com/en/java/javase/11/docs/api/java.desktop/javax/swing/JOptionPane.html
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class TicTacToe_GUI extends JFrame {

    private class TicTacToe_Board extends JPanel {

        private final boolean player_1_is_using_x;

        private final JLabel jLabel_for_what_player_1_is_using = new JLabel();
        private final JLabel jLabel_for_what_player_2_is_using = new JLabel();
        private final JLabel jLabel_for_whose_turn_it_is_right_now = new JLabel();

        private final JButton[][] jButtons_for_board = new JButton[TicTacToe.SIZE][TicTacToe.SIZE];

        private boolean player_1_has_turn_right_now = true;

        private final TicTacToe ttt = new TicTacToe();

        public TicTacToe_Board(boolean player_1_is_using_x) {

            this.player_1_is_using_x = player_1_is_using_x;

            set_layout_and_add_things(new GridBagLayout(), new GridBagConstraints());

            update_things();
        }

        private void set_layout_and_add_things(GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints) {
            setLayout(gridBagLayout);
            add_each_JLabel(gridBagLayout, gridBagConstraints);
            add_each_JButton(gridBagLayout, gridBagConstraints);
        }

        private void add_each_JLabel(GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints) {
            add_JLabel(gridBagLayout, gridBagConstraints, jLabel_for_what_player_1_is_using);
            add_JLabel(gridBagLayout, gridBagConstraints, jLabel_for_what_player_2_is_using);
            add_JLabel(gridBagLayout, gridBagConstraints, jLabel_for_whose_turn_it_is_right_now);
        }

        private void add_JLabel(GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints, JLabel jLabel) {

            gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;

            gridBagLayout.setConstraints(jLabel, gridBagConstraints);

            add(jLabel);
        }

        private void add_each_JButton(GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints) {
            gridBagConstraints.fill = GridBagConstraints.BOTH;
            gridBagConstraints.weightx = 1.0;
            gridBagConstraints.weighty = 1.0;
            for (int board_row = 0; board_row < TicTacToe.SIZE; board_row++) {
                for (int board_col = 0; board_col < TicTacToe.SIZE; board_col++) {
                    add_JButton(gridBagLayout, gridBagConstraints, board_row, board_col);
                }
            }
        }

        private void add_JButton(GridBagLayout gridBagLayout, GridBagConstraints gridBagConstraints, int board_row, int board_col) {

            jButtons_for_board[board_row][board_col] = new JButton();
            jButtons_for_board[board_row][board_col].setFont(new Font(Font.DIALOG, Font.PLAIN, 50));
            jButtons_for_board[board_row][board_col].setMinimumSize(new Dimension(100, 100));
            jButtons_for_board[board_row][board_col].addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent actionEvent) {
                    System.out.println(String.format("Selected row %d and column %d.", board_row, board_col));

                    final TicTacToe.CellValue cell_value = (player_1_has_turn_right_now == player_1_is_using_x)
                            ? TicTacToe.CellValue.VALUE_FOR_X
                            : TicTacToe.CellValue.VALUE_FOR_O;

                    try {
                        ttt.set_cell(board_row, board_col, cell_value);
                    } catch (TicTacToe.CellAlreadyFilledException e) {
                        System.out.println("Failed to place piece. Try again.");
                        return;
                    }

                    update_things();

                    player_1_has_turn_right_now = !player_1_has_turn_right_now;
                }
            });

            gridBagConstraints.gridwidth = (board_col == TicTacToe.SIZE - 1) ? GridBagConstraints.REMAINDER : 1;

            gridBagLayout.setConstraints(jButtons_for_board[board_row][board_col], gridBagConstraints);

            add(jButtons_for_board[board_row][board_col]);
        }

        @Override
        public void paint(Graphics g) {
            update_things();
            super.paint(g);
        }

        private void update_things() {
            update_text_of_each_JLabel();
            update_text_of_each_JButton();
            update_from_winner_value();
        }

        private void update_text_of_each_JLabel() {
            final char cell_value_for_x_as_char = TicTacToe.CellValue.VALUE_FOR_X.get_as_char();
            final char cell_value_for_o_as_char = TicTacToe.CellValue.VALUE_FOR_O.get_as_char();

            jLabel_for_what_player_1_is_using.setText(String.format("Player 1 is using %c.", player_1_is_using_x ? cell_value_for_x_as_char : cell_value_for_o_as_char));
            jLabel_for_what_player_2_is_using.setText(String.format("Player 2 is using %c.", player_1_is_using_x ? cell_value_for_o_as_char : cell_value_for_x_as_char));
            jLabel_for_whose_turn_it_is_right_now.setText(String.format("It is Player %d's turn.", player_1_has_turn_right_now ? 1 : 2));
        }

        private void update_text_of_each_JButton() {
            for (int board_row = 0; board_row < TicTacToe.SIZE; board_row++) {
                for (int board_col = 0; board_col < TicTacToe.SIZE; board_col++) {
                    update_text_of_a_JButton(board_row, board_col);
                }
            }
        }

        private void update_text_of_a_JButton(int board_row, int board_col) {

            final TicTacToe.CellValue cell_value = ttt.get_cell(board_row, board_col);

            final String newText = (cell_value == null) ? String.valueOf(cell_value) : String.format("%c", cell_value.get_as_char());

            jButtons_for_board[board_row][board_col].setText(newText);
        }

        private void update_from_winner_value() {
            switch (ttt.who_won()) {
                case PLAYER_WHO_USED_X_WON:
                    display_a_game_over_message(String.format("Game over. The winner is Player %d.", player_1_is_using_x ? 1 : 2));
                    break;
                case PLAYER_WHO_USED_O_WON:
                    display_a_game_over_message(String.format("Game over. The winner is Player %d.", player_1_is_using_x ? 2 : 1));
                    break;
                case DRAW:
                    display_a_game_over_message("Game over. The game is a draw.");
                    break;
                default:
                    break;
            }
        }
    }

    private TicTacToe_GUI() {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setTitle(getClass().getName());
    }

    private void ask_whether_player_1_is_using_x() {
        switch_component_of_content_pane(
                getPreferredSize(),
                new JOptionPane(
                        "Will Player 1 be playing as X? If not, Player 2 will be.",
                        JOptionPane.QUESTION_MESSAGE,
                        JOptionPane.YES_NO_OPTION) {
            @Override
            public void setValue(Object newValue) {
                super.setValue(newValue);
                if (newValue == null) {
                    System.out.println("Warning: the new value for this JOptionPane is null.");
                } else if (newValue.equals(YES_OPTION)) {
                    display_the_game_board(true);
                } else if (newValue.equals(NO_OPTION)) {
                    display_the_game_board(false);
                } else {
                    System.out.println("Warning: the new value for this JOptionPane is neither null nor YES_OPTION nor NO_OPTION.");
                }
            }
        });
    }

    private void display_the_game_board(boolean player_1_is_using_x) {
        switch_component_of_content_pane(
                getMinimumSize(),
                new TicTacToe_Board(player_1_is_using_x));
    }

    private void display_a_game_over_message(String message) {
        switch_component_of_content_pane(
                getPreferredSize(),
                new JOptionPane(message) {
            @Override
            public void setValue(Object newValue) {
                super.setValue(newValue);
                if (newValue == null) {
                    System.out.println("Warning: the new value for this JOptionPane is null.");
                } else if (newValue.equals(OK_OPTION)) {
                    fully_exit();
                } else {
                    System.out.println("Warning: the new value for this JOptionPane is neither null nor OK_OPTION.");
                }
            }
        });
    }

    private void switch_component_of_content_pane(Dimension newSize, Component newComponent) {
        if (newSize == null) {
            throw new NullPointerException("Null size");
        }
        if (newComponent == null) {
            throw new NullPointerException("Null component");
        }
        getContentPane().removeAll();
        getContentPane().add(newComponent);
        pack();
        setSize(newSize);
        setVisible(true);
    }

    private void fully_exit() {
        System.out.println("Exiting...");
        dispose();
    }

    private static void play_game() {
        new TicTacToe_GUI().ask_whether_player_1_is_using_x();
    }

    public static void main(String[] args) {
        play_game();
    }
}
