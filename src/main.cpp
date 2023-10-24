#include "deck.h"
#include "renderCards.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


Deck *MainDeck;


int main()
{
    MainDeck = new Deck(); // Initialize the Deck

    printf("\e[?25l]\n"); // Remove Cursor
    printf("\033[42m\n"); // Green Background

    // Switch to canonical mode, disable echo
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int quit = 0;

    int previousWin = 0;

    // Program Loop
    while(!quit)
    {
        fflush(stdout);
        // Renders
        
        RenderCards(MainDeck->HandCards);
        RenderHold(MainDeck->ReplacePositions);
        RenderWinnings(MainDeck->Winnings, previousWin, MainDeck->MaxReplace);
        
        int ch = getchar();

        switch(ch){
            case 'q':
                quit = 1;
                break;
            case '1':
                MainDeck->ReplacePositions[0]? MainDeck->NumReplaced-- : MainDeck->NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
                MainDeck->ReplacePositions[0] = !(MainDeck->ReplacePositions[0]);
                break;
            case '2':
                MainDeck->ReplacePositions[1]? MainDeck->NumReplaced-- : MainDeck->NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
                MainDeck->ReplacePositions[1] = !(MainDeck->ReplacePositions[1]);
                break;
            case '3':
                MainDeck->ReplacePositions[2]? MainDeck->NumReplaced-- : MainDeck->NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
                MainDeck->ReplacePositions[2] = !(MainDeck->ReplacePositions[2]);
                break;
            case '4':
                MainDeck->ReplacePositions[3]? MainDeck->NumReplaced-- : MainDeck->NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
                MainDeck->ReplacePositions[3] = !(MainDeck->ReplacePositions[3]);
                break;
            case '5':
                MainDeck->ReplacePositions[4]? MainDeck->NumReplaced-- : MainDeck->NumReplaced++; // If its being deactivated decrease number of replaced, vice versa
                MainDeck->ReplacePositions[4] = !(MainDeck->ReplacePositions[4]);
                break;
            case ' ':
                if (!(MainDeck->NumReplaced > MainDeck->MaxReplace))
                {
                    MainDeck->ReplaceHand();
                    MainDeck->ResetReplace();
                    int newWinnings = MainDeck->checkWinnings();
                    MainDeck->Winnings += newWinnings;
                    previousWin = newWinnings;
                    RenderCards(MainDeck->HandCards);
                    RenderHold(MainDeck->ReplacePositions);
                    RenderWinnings(MainDeck->Winnings, previousWin, MainDeck->MaxReplace);

                    sleep(2);

                    MainDeck->Draw(false);
                }
                else
                    previousWin = 500;
        }
        if ((MainDeck->Winnings) == 0)
            quit = 0;
    }
    
    // Reset
    printf("\033[0m");
    printf("\e[?25h");
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fflush(stdout);
    system("clear");
}