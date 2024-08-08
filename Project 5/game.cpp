#include "utilities.h"
#include <iostream>
#include <cstring>

using namespace std;

const char WORDFILENAME[] = "/Users/maddydelosreyes/Downloads/words.txt";

int playOneRound(const char words[][7], int nWords, int wordnum);
int isValidWord(char word[]);
bool isInDictionary(const char dictionary[][7], char word[]);
int numGolds(const char targetWord[], char guess[]);
int numSilvers(const char targetWord[], char guess[]);

const int MAXWORDS = 9000;

int main()
{
    char wordlist [MAXWORDS][7]; // populates array for dictionary of words to be stored in
    
    int nWords = getWords(wordlist, MAXWORDS, WORDFILENAME); // gets list of words from saved file and puts them in previous array
    
    
    if (nWords < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;// no words loaded into dictionary error message
        return -1;
        
    }
    
    int rounds;
    cout << "How many rounds do you want to play? "; // asks user how many rounds played
    cin >> rounds; // stores value in variable to use in the for loop to loop over the funciton playOneRound
    cin.ignore (10000, '\n');
    cout << endl;
    
    if (rounds < 0) // check on negative number rounds
    {
        cout << "The number of rounds must be positive.";
        return -1;
    }
    
    double accumulation = 0.0;
    int min = 1000000;
    int max = 0;
    
    for (int i = 0; i < rounds; i++)
    {
        cout << "Round " << i + 1 << endl;
        int wordnum = randInt(0, nWords - 1); // generates random number to pick the hidden word, only to boundary nwords-1 because don't want to be outside of index
        cout << "The hidden word is " << strlen(wordlist[wordnum]) << " letters long." << endl; // prints out length of hidden word
        int counter = playOneRound(wordlist, nWords, wordnum); // returns how many tries it took to guess word
        
        if (counter < 0) // if playoneround returns a negative number, terminate program
            return -1;
       
        
        accumulation += counter; //adds number of guesses to entire counter
        if (counter < min) // checks if the counter is less than the previous minimum value
            min = counter;
        if (max < counter) // checks if the returned number of guesses is greater than the previous max value
            max = counter;
        
        if (counter == 1)
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << counter << " tries." << endl;
        
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << accumulation/(i + 1) << ", minimum: " << min << ", maximum: " << max << endl << endl;
    }
    
    
}
 
int playOneRound(const char wordlist[][7], int nWords, int wordnum)
{
    if (wordnum < 0 || wordnum >= MAXWORDS)
        return -1;
    char userWord [100];
    int golds = 0;
    int counter = 0; // initialize counter for how many tries to 0
    
    while (true)
    {
        
        cout << "Probe word: "; // must reprompt until all chars are gold and if given invalid word
        cin.getline(userWord, 1000); // reads in user's word guess ** is this a part of cstrings??
                
        while (!isValidWord(userWord) || !isInDictionary(wordlist,userWord)) // checks that user's guess is all lowercase and is of length 6 or shorter
        {
            if (!isValidWord(userWord))
            {
                cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                cout << "Probe word: ";
                cin.getline(userWord,1000);
            }
            if (isValidWord(userWord) == 1 && !isInDictionary(wordlist,userWord)) // only prints error if has the right length
            {
                cout << "I don't know that word." << endl;
                cout << "Probe word: ";
                cin.getline(userWord, 1000);
            }
        }
        
            
        counter++; // only increments total guesses if given valid word
        golds = numGolds(wordlist[wordnum], userWord); // runs gold function to calculate number of gold letters
        
        
        int silvers = numSilvers(wordlist[wordnum], userWord);
        
        
        silvers = silvers - golds; // subtract gold from silver because double counted letters that appear in the hidden word
        
        if (strcmp(wordlist[wordnum], userWord) == 0 ) // only can return if the words are the exact same, not just if golds match
            return counter;
        
        cout << "Golds: " << golds << ", Silvers: " << silvers << endl;
    }
    
    return counter;
}





int isValidWord(char word[])
{
    for (int i = 0; i < strlen(word); i++)
    {
        if (!islower(word[i])) // checks for all lowercase letters, if not lower, terminates
        {
            return 0;
            
        }
    }
        
    if (strlen(word) > 6 || strlen(word) < 4) // ensures length is between 4 to 6 letters
    {
        
        return 0;
    }
    
    return 1; // only reaches this is all letters lowercase, insinuating that it is a true valid word
}



bool isInDictionary(const char dictionary[][7], char word[])
{
    for (int i = 0; i < MAXWORDS; i++)
    {
        if (strcmp(dictionary[i], word) == 0)
        {
            return true;
        }
    }
    return false;
}


int numGolds(const char targetWord[], char guess[])
{
    // which string is shorter, input or hidden word, then loop through that word
    double shorterWord;
    if (strlen(targetWord) < strlen(guess))
        shorterWord = strlen(targetWord); // stores length of shorter word so we don't index outside of a certain range
    else
        shorterWord = strlen(guess);
    int gold = 0;
    for (int i = 0; i < shorterWord; i++) // checks each letter index to see if a match
    {
        if (targetWord[i] == guess[i])
        {
            gold++; // increments if letter in the same index
        }
    }
    return gold;
}



int numSilvers(const char targetWord[], char guess[])
{
    int silver = 0;
    

    char tmpGuess[7]; // stores user guess in temporary variable becuase don't want to change original guess
    
    for (int m = 0; m < strlen(guess); m++)
    {
        tmpGuess[m] = guess[m];
    }
        
    for (int i = 0; i < strlen(targetWord); i++)
    {
        for (int j = 0; j < strlen(guess); j++)
        {
            if (targetWord[i] == tmpGuess[j])
            {
                silver++;
                tmpGuess[j] = '0'; // if it matches as a silver, changes its char to a non letter so can't match again if theres a repeat letter in hidden word
                break;
            }
        }
    }
    
    return silver;
}
