// evenwins7.cpp
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

enum class Player{
    human,
    computer
};

Player whose_turn; 

struct Gamestate {
    int marbles_in_middle = -1;
    int human_marbles     = -1;
    int computer_marbles  = -1;

    int total_games = 0; 
    int human_wins = 0; 
    int computer_wins = 0; 
};

struct Gamestate g; 

void welcome_screen() {
    cout << "+-----------------------+ \n"; 
    cout << "| Welcome to Even Wins! |\n";
    cout << "+-----------------------+ \n"; 
    cout << "Even Wins is a two-person game. You start with\n";
    cout << "27 marbles in the middle of the table.\n";
    cout << "\n";
    cout << "Players alternate taking marbles from the middle.\n";
    cout << "A player can take 1 to 4 marbles on their turn, and\n";
    cout << "turns cannot be skipped. The game ends when there are\n";
    cout << "no marbles left, and the winner is the one with an even\n";
    cout << "number of marbles.";
    cout << "\n";
}

string marbles_str(int n) {
    if (n == 1) return "1 marble";
    return to_string(n) + " marbles";
}

void choose_first_player() {
   for (;;) {
        cout << "\nDo you want to play first? (y/n) --> ";
        string ans;
        cin >> ans;
        if (ans == "y") {
            whose_turn = Player::human;
            return;
        } else if (ans == "n") {
            whose_turn = Player::computer;
            return;
        } else {
            cout << "\nPlease enter 'y' if you want to play first,\n";
            cout << "or 'n' if you want to play second.\n";
        }
    }
} // choose_first_player

void next_player() {
    whose_turn = (whose_turn == Player::human) ? Player::computer : Player::human;     
}

void print_board() {
    cout << "\n";
    cout << " marbles in the middle: " << g.marbles_in_middle 
         << " " << string(g.marbles_in_middle, '*') << "\n";
    cout << "    # marbles you have: " << g.human_marbles << "\n";
    cout << "# marbles computer has: " << g.computer_marbles << "\n";
    cout <<  "\n";
}

void print_statistics(){
    cout << "\n";
    cout << "Statistics \n"; 
    cout << "---------- \n";
    cout << "total games: " << g.total_games << "\n";
    cout << "human wins: " << g.human_wins << "\n"; 
    cout << "computer wins: " << g.computer_wins << "\n"; 
}

bool is_int(const string& s) {
    try {
        stoi(s); // throws an invalid_argument exception if conversion fails
        return true;
    } catch (...) {
        return false;
    }
}

void human_turn() {
    // get number in range 1 to min(4, marbles_in_middle)
    int max_choice = min(4, g.marbles_in_middle);
    cout << "It's your turn!\n";
    for(;;) {
        cout << "Marbles to take? (1 - " << max_choice << ") --> ";
        string s;
        cin >> s;
        if (!is_int(s)) {
            cout << "\n  Please enter a whole number from 1 to " << max_choice
                 << "\n";
            continue;
        }

        // convert s to an int so it can be compared
        int n = stoi(s);
        if (n < 1) {
            cout << "\n  You must take at least 1 marble\n";
            continue;
        }
        if (n > max_choice) {
            cout << "\n  You can take at most " << marbles_str(max_choice)
                 << "\n";
            continue;
        }

        cout << "\nOkay, taking " << marbles_str(n) << " ...\n";
        g.marbles_in_middle -= n;
        g.human_marbles += n;

        return;
    } // for
} // human_turn


/* Computer AI:
STRATEGY FOR HOW TO WIN: 
To win the game, the player needs to go when there are less than two to 
four marbles left in the center. If the marbles in the middle and the marbles 
the player are both even or both odd, the player can just take all the marbles. 
Otherwise, the player can choose to leave one marble in the center and take the 
rest. As long as the number of marbles in the center is five or six during the 
player's turn, the player will most likely lose

HOW THE AI WORKS: 
For the first few moves, the AI will randomly select a number.  Once there 
is less than nine marbles, the computer will try to force the player to have 
a specific amount of marbles. Therefore, here is what the AI will do to win: 
- If there are only four marbles left, the AI will 100% win. 
- If there are only five marbles left, but the AI has an even amount of marbles, 
then the AI will 100% win. 
- Otherwise, the AI can try to block the player from winning. 
    - If the player has an even amount of marbles, try to have six marbles left 
    in the middle. 
    - If the player has an odd amount of marbles, try to have five marbles left 
    in the middle. 
    - If the AI cannot make this happen, it will try to make it's own number even 
    all while taking the maximum number of marbles it can.

SCENARIO FOR WHY THE AI MIGHT NOT WIN: 
    - The AI might not win if there aren't five or six marbles in the center when 
    the player goes. 
*/

void computer_turn() {
    cout << "It's the computer's turn ...\n";

    int n = g.marbles_in_middle - 1;

    if (g.marbles_in_middle >= 9) {
        int max_choice = min(4, g.marbles_in_middle);
        
        while (g.marbles_in_middle - n <= 4) {
            n = 1 + rand() % max_choice;
        }
    } else {
        int isOdd = g.computer_marbles % 2;

        if (g.marbles_in_middle <= 4) { // Check if there is four left.
            int numIsOdd = g.marbles_in_middle % 2;
            if (isOdd == numIsOdd) {
                n = g.marbles_in_middle;
            } else {
                n = g.marbles_in_middle - 1;
            }

            if (!n) {
                n = 1;
            }
        } else if (g.marbles_in_middle == 5 && !isOdd) {
            n = 4;
        } else {
            int p_isOdd = g.human_marbles % 2;

            if (p_isOdd) {
                n = g.marbles_in_middle - 5;
            } else {
                n = g.marbles_in_middle - 6;
            }

            if (!(-n == n) || n == 0) { // If neither works
                if (isOdd) {
                    n = 3;
                } else {
                    n = 4;
                }
            }
        }
    }
    cout << "Computer takes " << marbles_str(n) << " ...\n";
    g.marbles_in_middle -= n;
    g.computer_marbles += n;
}

void game_over() {
    string taunts[] = {"tremble before it's mighty brain!", "you're dumb!", "it's better!", "that's too bad!", "loser!", "sucks for you!"};

    cout << "\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
         << "!! All the marbles are taken: Game Over !!\n"
         << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    print_board();
    if (g.human_marbles % 2 == 0) {
        cout << "You are the winner! Congratulations!\n";
        g.human_wins++; 
    } else {
        string taunt = taunts[rand() % 6];
        cout << "The computer wins: " << taunt << "\n";
        g.computer_wins++; 
    }
}

void play_game() {
    // initialize the game state
    g.total_games++;
    g.marbles_in_middle = 27;
    g.human_marbles = 0;
    g.computer_marbles = 0;
    print_board();

    for (;;) {
        if (g.marbles_in_middle == 0) {
            game_over();
            return;
        } else if (whose_turn == Player::human) {
            human_turn();
            print_board();
            next_player();
        } else if (whose_turn == Player::computer) {
            computer_turn();
            print_board();
            next_player();
        }
    } // for
} // play_game

int main() {
    srand(time(NULL));

    welcome_screen();

    for(;;) {
        choose_first_player();
        play_game();
        print_statistics(); 

        // ask if the user if they want to play again
        cout << "\nWould you like to play again? (y/n) --> ";
        string again;
        cin >> again;
        if (again == "y") {
            cout << "\nOk, let's play again ...\n";
        } else {
            cout << "\nOk, thanks for playing ... goodbye!\n";
            return 0;
        }
    } // for
} // main
