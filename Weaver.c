/****************************
 * Program 2: Weaver
 *
 * Course: CS 211, Spring 2023
 * System: WindowsOS using Clion
 * Student Author: Zaid Khan Mohammed
 * *** **********************/


/*
* User Instructions for Weaver Game
*
* 1. Start the game by compiling and running the program.
* 2. When prompted, enter the number of letters you want in your words.
* 3. You will then be asked to provide a starting word and an ending word.
*    - You can enter 'r' for either word to select a random word from the dictionary.
* 4. The game will prompt you to enter words that are exactly one letter different from the previous word.
*    - Ensure that each entered word is a valid dictionary word of the same length.
* 5. You can type 'q' at any time to quit the game.
* 6. After successfully reaching the ending word, the game will display your move count and ask if you want to play again.
*    - You can choose to play again, change the number of letters, or exit the program.
*
* Enjoy the game!
*/


// including libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void option1Or2(int *numLetters,int *numWords,char** wordArrayPtr){
        printf("Enter starting and ending words, or 'r' for either for a random word: ");
        // accepting starting and ending values from user
        char startingWord[81];
        char endingWord[81];
        scanf("%s", startingWord);
        scanf("%s", endingWord);
        while (1) {
            // checking if it is a dictionary word
            if (strlen(startingWord) != *numLetters && strcmp(startingWord,"r")!=0) {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", startingWord, *numLetters);
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
                scanf("%s", startingWord);
                scanf("%s", endingWord);
                continue;
            }
            // checking if it is of correct length
            if (strlen(endingWord) != *numLetters && strcmp(endingWord,"r")!=0) {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", endingWord, *numLetters);
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
                scanf("%s", startingWord);
                scanf("%s", endingWord);
                continue;
            }
            // setting a flag for checking if it is a dictionary word
            int dictionaryWord1 = 0;
            for (int i = 0; i < (*numWords); ++i) {
                if (strcmp(startingWord, wordArrayPtr[i]) == 0) {
                    dictionaryWord1 = 1;
                }
            }
            if (dictionaryWord1 == 0 && strcmp(startingWord,"r")!=0) {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n", startingWord);
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
                scanf("%s", startingWord);
                scanf("%s", endingWord);
                continue;
            }
            int dictionaryWord2 = 0;
            for (int i = 0; i < *numWords; ++i) {
                if (strcmp(endingWord, wordArrayPtr[i]) == 0) {
                    dictionaryWord2 = 1;
                }
            }
            if (dictionaryWord2 == 0 && strcmp(endingWord,"r")!=0) {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n", endingWord);
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
                scanf("%s", startingWord);
                scanf("%s", endingWord);
                continue;
            }
            break;
        }
        if (strcmp(startingWord,"r")==0){
            strcpy(startingWord,wordArrayPtr[rand()%(*numWords)]);
        }
        if (strcmp(endingWord,"r")==0){
            strcpy(endingWord,wordArrayPtr[rand()%(*numWords)]);
        }
        printf("Your starting word is: %s.\n", startingWord);
        printf("Your ending word is: %s.\n\n", endingWord);
        printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
        printf("You may also type in 'q' to quit guessing.\n");
        int userMoves = 1;
        char previousWord[81];
        strcpy(previousWord, startingWord);
        char userWord[81];
        while (1) {
            printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", userMoves, previousWord,
                   endingWord);
            scanf("%s", userWord);
            if (strcmp(userWord, "q") == 0) {
                break;
            }
            if (strlen(userWord) != *numLetters) {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", userWord, *numLetters);
                continue;
            }
            int dictionaryWord = 0;
            for (int i = 0; i < *numWords; ++i) {
                if (strcmp(userWord, wordArrayPtr[i]) == 0) {
                    dictionaryWord = 1;
                }
            }
            if (dictionaryWord == 0) {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n", userWord);
                continue;
            }
            // checking if word is exactly 1 character different
            int charDiff = 0;
            for (int i = 0; i < (*numLetters); ++i) {
                if (previousWord[i] != userWord[i]) {
                    charDiff++;
                }
            }
            if (charDiff != 1) {
                printf("Your word, '%s', is not exactly 1 character different. Try again.\n", userWord);
                continue;
            }
            strcpy(previousWord, userWord);
            userMoves++;
            if (strcmp(userWord, endingWord) == 0) {
                printf("Congratulations! You changed '%s' into '%s' in %d moves.\n", startingWord, endingWord,
                       userMoves - 1);
                break;
            }
        }
        printf("\nEnter: \t1 to play again,\n");
        printf("\t2 to change the number of letters in the words and then play again, or\n");
        printf("\t3 to exit the program.\n");
        printf("Your choice --> ");
}
int main() {
    srand(1);
    int numLetters=0;
    int numWords=0;
    printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
    printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
    printf("Enjoy!\n\n");
    int userChoice=2;
    // creating array of words on the heap
    char **wordArrayPtr = (char **) malloc(sizeof(char *));
    while (1) {
        if (userChoice == 2) {
            for (int i=0;i<numWords;++i){
                free(wordArrayPtr[i]);
            }
            numLetters=0;
            numWords=0;
            printf("How many letters do you want to have in the words? ");
            scanf("%d", &numLetters);
            // reading text from file
            char filename[] = "words.txt";
            FILE *filePtr = fopen(filename, "r");

            // Check that the file was able to be opened
            if (filePtr == NULL) {
                printf("Error: could not open %s for reading\n", filename);
                exit(-1);
            }
            // Read each word from file, and print them one by one
            char inputString[81];
            while (fscanf(filePtr, "%s", inputString) != EOF) {
                if (strlen(inputString) == numLetters) {
                    // incrementing numWords
                    numWords++;
                    wordArrayPtr = (char **) realloc(wordArrayPtr, sizeof(char *) * (numLetters + 1) * numWords);
                    wordArrayPtr[numWords - 1] = (char *) malloc(sizeof(char) * (numLetters + 1));
                    strcpy(wordArrayPtr[numWords - 1], inputString);
                }
            }
            // Close the file
            fclose(filePtr);
            printf("Number of %d-letter words found: %d.\n\n", numLetters, numWords);
            if (numWords==0){
                break;
            }
        }
        if (userChoice == 1 || userChoice==2) {
            option1Or2(&numLetters,&numWords,wordArrayPtr);
            scanf("%d", &userChoice);
        }
        if (userChoice==3){
            break;
        }
        if (userChoice!=1 && userChoice!=2 && userChoice!=3){
            /*printf("Invalid choice entered.\n");
            printf("\nEnter: \t1 to play again,\n");
            printf("\t2 to change the number of letters in the words and then play again, or\n");
            printf("\t3 to exit the program.\n");
            printf("Your choice --> ");
            scanf("%d", &userChoice);
            continue;
            */
            break;
        }
    }
    printf("\nThanks for playing!\nExiting...\n\n");
    for(int i=0;i<numWords;++i){
        free(wordArrayPtr[i]);
    }
    free(wordArrayPtr);
    return 0;
}
