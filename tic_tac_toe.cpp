#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

void clearCon() {
    #if _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printTitle(bool include_instructions) {
    cout << "┏━━━━━━━━━━━━━┓" << endl
         << "┃ Tic Tac Toe ┃" << endl
         << "┗━━━━━━━━━━━━━┛" << endl
         << endl;
    
    if (include_instructions) {
    cout << "Players take turns entering moves.\n\n"
            "To make a move, enter the row and column.\n\n"
            "Example: to place your mark in the top-left corner:\n"
            "         Your move: A1\n\n\n";
    }
}

void printBoard(vector<vector<string>> board) {
    for (auto row : board) {
        for (auto item : row) {
            cout << item;
        }
        cout << endl;
    }
}

string mapChoice(char move, char &letter, char &number) {
    char move_lower = tolower(move);
    if (move_lower == 'a' || move_lower == 'b' || move_lower == 'c') {
        letter = move_lower;
        return "letter";
    } else if (move == '1' || move == '2' || move == '3') {
        number = move;        
        return "number";
    } else {
        return "invalid";
    }
}

string asciiMove(char number, char letter) {
    return to_string(number) + " " + to_string(letter);
}

int main() {
    vector<vector<string>> board {
        {"    A     B     C  \n"},
        {"  ", "     ", "┃", "     ", "┃", "     "},
        {"1 ", "     ", "┃", "     ", "┃", "     "},
        {"  ", "     ", "┃", "     ", "┃", "     "},
        {"  ", "━━━━━", "╋", "━━━━━", "╋", "━━━━━"},
        {"  ", "     ", "┃", "     ", "┃", "     "},
        {"2 ", "     ", "┃", "     ", "┃", "     "},
        {"  ", "     ", "┃", "     ", "┃", "     "},
        {"  ", "━━━━━", "╋", "━━━━━", "╋", "━━━━━"},
        {"  ", "     ", "┃", "     ", "┃", "     "},
        {"3 ", "     ", "┃", "     ", "┃", "     "},
        {"  ", "     ", "┃", "     ", "┃", "     "},
    };

    string move;
    char letter;
    char number;

    string first_type;
    string second_type;
    
    char player = 'X';  // first player is x
    string xMark = "  X  ";
    string oMark = "  O  ";
    vector<vector<string>> used_moves {
        {},
        {}
    };
    // main vector > vector for each player > each move is a string
    
    int num_moves = 0;
    char winner;

    while (true) {

        // Initial Print
        clearCon();
        printTitle(true); // true means instructions are also printed
        printBoard(board);

        // Get and validate user's move
        while (true) {

            // get move
            cout << endl << "Player " << player << endl << "Enter your move: ";
            getline(cin, move);

            // removes whitespaces
            for (int i = 0; move[i];) {
                if (move[i] == ' ') {
                    move.erase(i, 1);
                }
                else { // only increments if a space was not removed
                    i++;
                }
            }

            // checks the length
            if (move.length() != 2) {
                cout << "Enter one letter and one number.\n";
                continue;
            }

            // determines if first part of the coordinate is a letter, number, or invalid
            // if letter or number it will be assigned to the letter/number variable
            first_type = mapChoice(move[0], letter, number);

            // restart loop if invalid
            if (first_type == "invalid") {
                cout << "(if1)Invalid input.\n";
                continue;
            }

            // determines the status of the second part of the coordinate
            second_type = mapChoice(move[1], letter, number);

            // restart loop if invalid or if it matches the type of the first part of the coordinate
            if (second_type == "invalid") {
                cout << "(if2)Invalid input.\n";
                continue;
            }
            else if (second_type == first_type) {
                cout << "Invalid input. Enter a letter number pair.\n";
                cout << endl
                     << "hello" << endl;
                continue;
            }

            // spot taken
            bool moveMade = false;
            string current_move = asciiMove(number, letter); 
            for (auto player : used_moves) {
                for (auto move : player) {
                    if (move == current_move) {
                        cout << "Spot taken\n";
                        moveMade = true;
                        break;  // stop looking
                    }
                }                
                if (moveMade) {
                    break; // stop looking
                }
            }
            if (moveMade) {
                continue;  // restart loop to get good input
            }

            // input is valid
            num_moves++;
            break;
        }

        int row, column;

        // translate letter and number into vector coordinates
        if (number == '1') {
            row = 2;
        } else if (number == '2') {
            row = 6;
        } else if (number == '3') {
            row = 10;
        }
        
        if (letter == 'a') {
            column = 1;
        } else if (letter == 'b') {
            column = 3;
        } else if (letter == 'c') {
            column = 5;
        }
        
        // combine into a single coordinate value 
        // can't reuse 'move' for this, order needs to be consistant
        string coordinate = asciiMove(number, letter);

        // mark move then add move to used moves
        if (player == 'X') {
            board[row][column] = "  X  ";
            used_moves[0].push_back(coordinate);
        } else {
            board[row][column] = "  O  ";
            used_moves[1].push_back(coordinate);
        }
        
        // check for win
        // only need to check for the current player's mark
        string mark;
        if (player == 'X') {
            mark = "  X  ";
        } else {
            mark = "  O  ";
        }
        
        // check for win
        if ( 
            (board[2][1] == mark) && (board[2][3] == mark) && (board[2][5] == mark) ||  // row 1
            (board[6][1] == mark) && (board[6][3] == mark) && (board[6][5] == mark) ||  // row 2
            (board[10][1] == mark) && (board[10][3] == mark) && (board[10][5] == mark) ||   // row 3

            (board[2][1] == mark) && (board[6][1] == mark) && (board[10][1] == mark) ||   // column a
            (board[2][3] == mark) && (board[6][3] == mark) && (board[10][3] == mark) ||   // column b
            (board[2][5] == mark) && (board[6][5] == mark) && (board[10][5] == mark) ||   // column c

            (board[2][1] == mark) && (board[6][3] == mark) && (board[10][5] == mark) ||   // diagonal 1
            (board[10][1] == mark) && (board[6][3] == mark) && (board[2][5] == mark)      // diagonal 2
           ) { 
            cout << endl << player << " wins" << endl;
            winner = player;
            break;
        } else if (num_moves == 9) {
            cout << endl << "tie" << endl;
            winner = 'T';
            break;
        }
        
        // change player
        if (player == 'X') {
            player = 'O';
        } else {
            player = 'X';
        }
    }
    
    // Show game result
    clearCon();
    printTitle(false); // false means that the instructions will not be printed
    printBoard(board);
    if (winner == 'T') {
        cout << "\n\nTIE";
    } else {
        cout << "\n\nPlayer " << player << " wins!";
    }

    return 0;
}
