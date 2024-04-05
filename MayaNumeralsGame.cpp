#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//generates random numbers 
int randomNum(int a, int b) {
    return rand() % (b - a + 1) + a;
}

//PART ONE
int solveForBiggest(int n) {
    int biggest = 1;
    
    while (n / biggest > 1) {
        biggest *= 20;
    }
    
    //always be over by 20
    return biggest / 20; 
}

void printNum(int amount) {
    // n should be between 0-20
    //the actual printing goes here 
    //constant
    const char* line = "\u2580"; 
    
    int ones;
    int fives;
    fives = amount / 5;
    ones = amount - (fives * 5);
        
    if (fives + ones) {
        for(int i=0; i<ones; i++) {
            cout << "o";
        }
        for(int i=0; i<fives; i++) {
            cout << "\n" << line << line << line << line;
        }
    } else {
        cout << "00";
    }
    cout << "\n__________\n";
}

void printMayanNumber(int n) {
    //find the biggest multiple of 5, divides into n
    //biggest variable 
    int biggest = solveForBiggest(n);
    
    // sets up int for counting divisibility
    int amount;
    
    //main Loop
    do {
        //amount of times biggest divides into n
        amount = n / biggest;
        //remainder
        n %= biggest; 
    
        printNum(amount);
        
        biggest /= 20;
    } while (biggest >= 1);
}

// PART 2
void printAllNums(int a, int b, int c) {
    // Prints a, b, and c, in it's Mayan equivalants.
    cout << "a.\n";
    printMayanNumber(a);
    cout << "b.\n";
    printMayanNumber(b);
    cout << "c.\n";
    printMayanNumber(c);
    cout << "\n\nEnter a, b, or c: ";
}

int conv(char g) {
    // Returns g, as an int.
    return (int) g - 96;
}

int getGuess() {
    // Gets a player's guess.

    // Initalizes Variables.
    char guess;
    int guess_int;
    
    cin >> guess;
    guess_int = conv(guess);
    
    // Validate guess
    while(guess_int<0 || guess_int>3) {
        cin >> guess;
        guess_int = conv(guess);
    }
    
    return guess_int;
}

void mayanNumberGame() {
    // The actual function

    // Some introductory lines
    cout << "MAYAN NUMBER GAME\n----------------" << "\n";
    cout << "Welcome to the Mayan Number Game!\n\nEnter a number greater than 10. The game will choose a number\nless than or equal to what you entered. You will then have\nto match the decimal number to its Mayan equivalent.\n\n";
    while (1) {
        cout << "Or, enter a number less than 10 to exit: ";
        
        // Get the player's number
        int choice;
        cin>>choice;
        
        if (choice < 10) {
            return;
        }

        // Generate a correct answer
        int correct = randomNum(4, choice);
        
        cout << "Which of these Mayan Numbers are equal to " << correct << "?\n";

        // Generate range
        int range_min = correct * 0.5;
        int range_max = correct * 1.5;
        
        // Find two incorrect answers, validate to make sure they aren't the same as the correct answers
        int num1 = correct;
        while (num1 == correct) {
            num1 = randomNum(range_min, range_max);
        }
         
        int num2 = correct;
        while (num2 == correct || num2 == num1) {
            num2 = randomNum(range_min, range_max);
        }
        
        // Randomize the order that they're printed
        int position = randomNum(1, 3);
        if (position == 1) {
            printAllNums(correct, num1, num2);
        } else if (position == 2) {
            printAllNums(num1, correct, num2);
        } else {
            printAllNums(num1, num2, correct);
        }
        
        // Get the player's guess
       int guessed = getGuess();

       // Check if the guess is correct
        if (guessed == position) {
            cout << "CORRECT!";
        } else {
            cout << "INCORRECT!";
        }
    
        cout << " The Mayan representation of " << correct << " is\n";
        printMayanNumber(correct);
    }
}

int main()
{
    // Print the Mayan equivalant of 5212
    printMayanNumber(5212);

    // Seperate previous output
    cout << "\n\n";

    // Run mayanNumberGame
    mayanNumberGame();

    // Return 0
    return 0;
}