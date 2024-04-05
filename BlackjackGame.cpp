/*
Name: Sissi Li
SFU ID: yla751

How the advice works: Find the average of undealt cards in the deck, and if that added to our total exceeds 21, stand.

*/

// Academic honesty statement: I hereby confirm that this is my own work and I have not violated any of SFU’s Code of Academic Integrity and Good Conduct (S10.01).


// Include headers
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;

/********************

---------PART 1---------

*********************/

// Card Struct
struct Card {
    string Suit; // the suit
    char card_desc[4]; // What is printed by the function? (Needs four because terminator character)
    int card_num; // The number on the card; 1-13
    int card_value; // The value of the card; 1-11
};

// Deck Struct
struct CardArray {
    Card *deck[52]; // The deck of cards
    int max_cards; // The amount of cards in the deck
    int unused_cards; // The unused cards in the deck
};

// Set up suit string constants
string Suits[] = {"Hearts", "Clubs", "Diamonds", "Spades"};
char SuitsDesc[] = {'H', 'C', 'D', 'S'};

// Get char value with number
char numValToChar(int value) {
    switch (value) {
        case (1):
            return 'A';
        case (11):
            return 'J';
        case (12):
            return 'Q';
        case (13):
            return 'K';
        case (10):
            return '0';
        default:
            return (char) (value + 48); // 48 is the ascii code for 48; Finds the ascii value for the value
    }
}

// Get number value of card number
char numValToCardVal(int card_num) {
    switch (card_num) {
        case (1):
            return 11;
        case (11):
        case (12):
        case (13):
            return 10;
        default:
            return card_num;
    }
}

// Create a new deck
void getNewDeck(CardArray * CardArray) {
    char desc_v; // Description for value
    
    for(int count=0; count<4; count++) { // Loop for suits
        for(int cardNum=1; cardNum<=13; cardNum++) {
            Card *temp_pointer = (Card*) malloc(sizeof(Card));
            temp_pointer->card_desc[0] = ' ';
            
            temp_pointer->card_value = numValToCardVal(cardNum); // Find card value 
            temp_pointer->card_num = cardNum; // Find card num
            temp_pointer->Suit = Suits[count]; // Change suit
            temp_pointer->card_desc[1] = SuitsDesc[count]; // Change Suit Description
            temp_pointer->card_desc[2] = '\0';
            if ((desc_v = numValToChar(cardNum)) == '0') {
                temp_pointer->card_desc[2] = temp_pointer->card_desc[1];
                temp_pointer->card_desc[0] = '1';
                temp_pointer->card_desc[1] = '0';
            } else 
                temp_pointer->card_desc[0] = desc_v;
            
            CardArray->deck[count*13 + cardNum - 1] = temp_pointer;
        }
        
    }
}

// Quick utility function for printing the card Description
void prDesc(Card card) {
    if (card.card_desc[1] == '0') {
        cout<<card.card_desc<<' ';
    } else {
        cout<<' '<<card.card_desc<<' ';
    }
}

// Another quick utility function for find a random number (from 0-51)
int rand51() {
    return rand() % 50;
}

// Print out the deck
void printDeck(CardArray CardArray) {
    for(int y=0; y<4; y++) {
        for (int x=0; x<13; x++) {
            prDesc(*CardArray.deck[x + (y*13)]);
        }
        cout<<'\n';
    }
}

// Shuffle a deck
void deckShuffle(CardArray * trial) {
    int randNum;
    Card *temp_storage;
    for(int i=0; i<52; i++) { // Loop through all of them
        randNum = rand51();
        if (randNum == i){
            continue;
        }
        
        temp_storage = trial->deck[i];
        trial->deck[i] = trial->deck[randNum];
        trial->deck[randNum] = temp_storage;
    }
}

// Free a deck once we're done
void freeDeck(CardArray * trial) {
    for(int i=0;i<52;i++) { // Loop for all card values
        free(trial->deck[i]); // Free the memory
    }
}

/* Part One Main Function
int main() {
	CardArray MyDeck;               // Declares a CardArray
	MyDeck.max_cards = 52;
	MyDeck.unused_cards = 52;
	
	getNewDeck(&MyDeck);            // Populates it with cards
	
	cout<<"Original Deck:\n\n";     // Print Unshuffled deck
	printDeck(MyDeck);              // ^^^
	
	deckShuffle(&MyDeck);           // Shuffle the Deck
	
	cout<<"\nShuffled Deck:\n\n";   // Print the Shuffled Deck
	printDeck(MyDeck);              // ^^^
	
	freeDeck(&MyDeck);              // Free MyDeck
}
*/

/********************

---------PART 2---------

*********************/

// Create a Hnd Struct.
struct Hand {
    short value = 0;
    short deckAmount = 0;
    Card *deck[12];
};

// Declare functions that are changed in later 
char* cardDeal(Hand * hand, CardArray * deck);
int playerChoice(Hand hand);
int handVal(Hand * hand);
int playerChoice(Hand hand);
void dispBothDecks(Hand player, Hand dealer);

// Create a function to display the cards.
void dispCards(Hand hand) {
    for(int i=0; i<hand.deckAmount; i++) {
        cout<<hand.deck[i]->card_desc<<" ";
    }
    
    cout<<"\n";
}

// For simplicity, we will create a function that sets up a deck.
void setupDeck(CardArray * deck) {
    deck->max_cards = 52;          // Set up maximum cards
	deck->unused_cards = 52;       // Set up unused cards
	
	getNewDeck(deck);            // Again, add cards to it
}

// Find the value of a hand; Part 2 version (Modified in Part 4), but used in Part 5
int handValOld(Hand * hand) {
    int value = 0;
    for (int i=0; i<hand->deckAmount-1; i++) {
        value += hand->deck[i]->card_value;
    }
    
    return value;
}

// Deals the top card to the hand; Part 2 version (Modified in Part 3)
/*
char* cardDeal(Hand * hand, CardArray * deck) { 
    Card* onTop = deck->deck[52-deck->unused_cards]; // Find the card on top.
    
    deck->unused_cards--; // Increment down (equivilant to removing one card)
    hand->deck[hand->deckAmount] = onTop; // Add the card to the hand
    hand->deckAmount++; // Add one to the total cards we have
    
    hand->value = handVal(hand); 
    
    return onTop->card_desc;
}
*/

// For simplicity, the player's choice will also be in a function; Part 2 version (Modified in Part 5)
/*
int playerChoice(Hand hand) {
    cout<<"Enter 'h' to hit or 's' to stand: ";
    char result;
    cin>>result;
    while (result != 'h' && result != 's') {
        cout<<"Enter 'h' or 's': ";
        cin>>result;
        cin.ignore();
    }
    
    return result == 'h';
}
*/

// Dealer's AI, very simple right now
int dealerAI(Hand hand) {
    if (hand.value <= 17) {
        return 1;
    }
    
    return 0;
}

// Display both decks at the end of the game, part 2 version (edited in part 5)
/*
void dispBothDecks(Hand player, Hand dealer) {
    cout<<"PLAYER'S CARDS: ";
    dispCards(player);
    cout<<"DEALER'S CARDS: ";
    dispCards(dealer);
}
*/

// Blackjack function
int blackjack(CardArray * trial) {
    Hand player;
    Hand dealer;

    // DEAL CARDS
    
    cout<<"---Dealing First Card...---\n";
    cout<<"PLAYER'S CARD: "<<cardDeal(&player, trial)<<'\n';
    cout<<"DEALER'S CARD: "<<cardDeal(&dealer, trial)<<'\n';

    cout<<"---Dealing Second Card...---\n";
    cout<<"PLAYER'S CARD: "<<cardDeal(&player, trial)<<"\n";
    cardDeal(&dealer, trial);
    cout<<"DEALER'S CARD: ---"<<"\n-----------------------------\n";
    
    if (player.value == 21 && dealer.value == 21) {
        cout<<"IT'S A TIE! Both players got a blackjack.";
        dispBothDecks(player, dealer);
        return 1;
    }
    if (player.value == 21) {
        cout<<"BLACKJACK! You win!\n";
        dispBothDecks(player, dealer);
        return 1;
    } else if (dealer.value == 21) {
        cout<<"The dealer got a BLACKJACK! You lose!\n";
        dispBothDecks(player, dealer);
        return -1;
    }
    
    while (1) {
        if (player.value > 21) {
            cout<<"-----------------------------\nYOU LOST - You went bust!\n-----------------------------\n";
            dispBothDecks(player, dealer);
            return -1;
        } else if (player.value == 21) {
            cout<<"BLACKJACK! You win!";
            dispBothDecks(player, dealer);
            return 1;
        }
        
        if (playerChoice(player)) {
            cardDeal(&player, trial);
            cout<<"PLAYER'S CARDS: ";
            dispCards(player);
        } else {
            break;
        }
    }
    
    cout<<"-----------------------------\nDEALER'S TURN:\n";
    
    while (1) {
        if (dealer.value > 21) {
            cout<<"-----------------------------\nYOU WON - The dealer went bust!\n-----------------------------\n";
            dispBothDecks(player, dealer);
            return 1;
        } else if (dealer.value == 21) {
            cout<<"YOU LOST - The dealer got a blackjack!";
            dispBothDecks(player, dealer);
            return -1;
        }
        
        if (dealerAI(dealer)) {
            cardDeal(&dealer, trial);
            cout<<"The dealer hit.\n";
        } else {
            cout<<"Dealer stood. \n-----------------------------\n";
            break;
        }
    }
    
    if (player.value < dealer.value) {
        cout<<"YOU LOSE - The dealer beat you!\n";
        dispBothDecks(player, dealer);
        return -1;
    } else if (player.value == dealer.value) {
        cout<<"It's a TIE - You both got the same total!\n";
        dispBothDecks(player, dealer);
        return 0;
    } else {
        cout<<"YOU WON - You beat the dealer!\n";
        dispBothDecks(player, dealer);
        return 1;
    }
}

/* Part Two Main Function
int main() {
    srand(time(NULL));
    
	CardArray MyDeck;               // Declares a CardArray
	setupDeck(&MyDeck);
	
	cout<<"Original Deck:\n\n";     // Print Unshuffled deck
	printDeck(MyDeck);              // ^^^
	
	deckShuffle(&MyDeck);           // Shuffle the Deck
	
	cout<<"\nShuffled Deck:\n\n";   // Print the Shuffled Deck
	printDeck(MyDeck);              // ^^^
	
	cout<<"\n"; // Add a newline for clarity
	
	cout<<blackjack(&MyDeck);
	
	freeDeck(&MyDeck);              // Free MyDeck
}
*/

/********************

---------PART 3---------

*********************/

// Deals the top card to the hand; Part 3 version
char* cardDeal(Hand * hand, CardArray * deck) { 
    if (deck->unused_cards == 0) {
        deckShuffle(deck);
        deck->unused_cards = 52;
    }
    
    Card* onTop = deck->deck[52-deck->unused_cards]; // Find the card on top.
    
    deck->unused_cards--; // Increment down (equivilant to removing one card)
    hand->deck[hand->deckAmount] = onTop; // Add the card to the hand
    hand->deckAmount++; // Add one to the total cards we have
    
    hand->value = handVal(hand); 
    
    return onTop->card_desc;
}

int getYN() {
    char yn;
    cout<<"Would you like to play again? (y/n) ";
    cin>>yn;
    cin.ignore();
    while (yn != 'y' && yn != 'n') {
        cout<<"Please enter 'y' for yes and 'n' for no: ";
        cin>>yn;
        cin.ignore();
    }
    
    return yn == 'y';
};

// Actual Function for playing games
void playMultipleGames(CardArray * deck) {
    int wins = 0; int ties = 0; int losses = 0;
    int result;
    
    do {
        result = blackjack(deck);
        if (result == 1)
            wins++;
        else if (result == 0)
            ties++;
        else
            losses++;
            
    } while (getYN());
    
    cout<<"-----------------------------\nRESULTS:\n";
    cout<<"\nWins:   "<<wins;
    cout<<"\nTies:   "<<ties;
    cout<<"\nLosses: "<<losses;
}

// Part 3 main function (And the actual main function)
/*
int main(){
    srand(time(NULL));
    
	CardArray MyDeck;               // Declares a CardArray
	setupDeck(&MyDeck);
	
	cout<<"Original Deck:\n\n";     // Print Unshuffled deck
	printDeck(MyDeck);              // ^^^
	
	deckShuffle(&MyDeck);           // Shuffle the Deck
	
	cout<<"\nShuffled Deck:\n\n";   // Print the Shuffled Deck
	printDeck(MyDeck);              // ^^^
	
	cout<<"\n";                     // Add a newline for clarity
	
	playMultipleGames(&MyDeck);
	
	freeDeck(&MyDeck);              // Free MyDeck
}
*/

/********************

---------PART 4---------

*********************/

// HOW SHOULD THIS FUNCTION WORK? 
/*

1) Since 2 aces would equal to a total of 22, it is only possible to have one ace with value 11.
   Therefore, we will treat other aces as 1.
2) Since choosing 11 as the value would always equal to the bigger value, as long as we don't bust, the value should be 11.

*/

// Find the value of a hand; Part 4 version
int handVal(Hand * hand) {
    int value = 0;
    int aces = 0; // Keep track of the aces
    for (int i=0; i<hand->deckAmount; i++) {
        if (hand->deck[i]->card_num == 1) {
            if (!aces) {
                aces = 1;
            } else {
                value++;
            }
        } else {
            value += hand->deck[i]->card_value;
        }
    }
    
    if (aces) {
        if (value + 11 > 21) {
            value += 1;
        } else {
            value += 11;
        }
    }
    
    return value;
}

// We'll use this in Part 5 to calculate the best score with another extra number
int handValPlusExtra(Hand * hand, int extra) {
    int value = extra;
    int aces = 0; // Keep track of the aces
    for (int i=0; i<hand->deckAmount; i++) {
        if (hand->deck[i]->card_num == 1) {
            if (!aces) {
                aces = 1;
            } else {
                value++;
            }
        } else {
            value += hand->deck[i]->card_value;
        }
    }
    
    if (aces) {
        if (value + 11 > 21) {
            value += 1;
        } else {
            value += 11;
        }
    }
    
    return value;
}

// Part 4 Main Function (Same as part 3)
/*
int main(){
    srand(time(NULL));
    
	CardArray MyDeck;               // Declares a CardArray
	setupDeck(&MyDeck);
	
	cout<<"Original Deck:\n\n";     // Print Unshuffled deck
	printDeck(MyDeck);              // ^^^
	
	deckShuffle(&MyDeck);           // Shuffle the Deck
	
	cout<<"\nShuffled Deck:\n\n";   // Print the Shuffled Deck
	printDeck(MyDeck);              // ^^^
	
	cout<<"\n";                     // Add a newline for clarity
	
	playMultipleGames(&MyDeck);
	
	freeDeck(&MyDeck);              // Free MyDeck
}
*/

/********************

---------PART 5---------

*********************/

int total = 420; // The total of all the values of cards in the deck added together; used later while calculating averages etc. (Aces are just 11.)
int cardDeckAmount = 52; // Keep track of the amount of cards still unused; do this so we don't need to pass the CardArray to all functions

// The actual "AI" part that determines whether or not we hit
int shouldHit(Hand hand) {
    // First, get the value of the hand (counting aces as 11)
    int cur_handVal = handValOld(&hand);
    int average_card_value = (int) (total - cur_handVal) / cardDeckAmount;
    
    return handValPlusExtra(&hand, average_card_value) <= 21;
}

// For simplicity, the player's choice will also be in a function; Part 5 version
int playerChoice(Hand hand) {
    cout<<"Enter 'h' to hit or 's' to stand.\n";
    cout<<"The computer recommends that you ";
    if (shouldHit(hand)) {
        cout<<"hit";
    } else {
        cout<<"stand";
    }
    cout<<": ";
    char result;
    cin>>result;
    cin.ignore();
    while (result != 'h' && result != 's') {
        cout<<"Enter 'h' or 's': ";
        cin>>result;
        cin.ignore();
    }
    
    return result == 'h';
}

// Display both decks at the end of the game, part 2 version (edited in part 5)
void dispBothDecks(Hand player, Hand dealer) {
    cout<<"PLAYER'S CARDS: ";
    dispCards(player);
    cout<<"DEALER'S CARDS: ";
    dispCards(dealer);
    
    // Change total and deckAmount for next game
    total -= handValOld(&player);
    cardDeckAmount -= player.deckAmount;
    total -= handValOld(&dealer);
    cardDeckAmount -= dealer.deckAmount;
}

// FINAL MAIN FUNCTION
int main(){
    srand(time(NULL));
    
	CardArray MyDeck;               // Declares a CardArray
	setupDeck(&MyDeck);
	
	cout<<"Original Deck:\n\n";     // Print Unshuffled deck
	printDeck(MyDeck);              // ^^^
	
	deckShuffle(&MyDeck);           // Shuffle the Deck
	
	cout<<"\nShuffled Deck:\n\n";   // Print the Shuffled Deck
	printDeck(MyDeck);              // ^^^
	
	cout<<"\n";                     // Add a newline for clarity
	
	playMultipleGames(&MyDeck);
	
	freeDeck(&MyDeck);              // Free MyDeck
}