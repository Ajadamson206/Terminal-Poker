#ifndef RENDER_CARD
#define RENDER_CARD

#include "deck.h"
#include <stdio.h>
#include <string>
#include <iostream>

const std::string RED = "\033[91m";
const std::string BLACK = "\033[30m"; 

/*
┌────────┐
│ A      │
│ ♥      │
│        │
│        │
│        │
└────────┘
          
*/
std::string getValueSymbol(int value)
{
    switch (value)
    {
    case 1:
        return "A";
        break;
    case 11:
        return "J";
        break;
    case 12:
        return "Q";
        break;
    case 13:
        return "K";
    default:
        return std::to_string(value);
        break;
    }
}

std::string getSuitSymbol(int suit)
{
    switch (suit)
    {
    case 1:
        return "♦";
        break;
    case 2:
        return "♠";
        break;
    case 3:
        return "♥";
        break;
    case 4:
        return "♣";
        break;
    case 5:
        return "J";
        break; 
    }
}

void RenderWinnings(int winnings, int previousWin, int maxDiscard)
{
    std::string winStr = "Winnings: ";
    winStr.append(std::to_string(winnings));

    if (previousWin == -1)
    {
        std::cout << winStr << "\n";
        return;
    }

    switch (previousWin)
    {
        case 350:
            winStr.append("\t\t5 of a Kind");
            break;
        case 250:
            winStr.append("\t\tRoyal Straight Flush");
            break;
        case 50:
            winStr.append("\t\tStraight Flush");
            break;
        case 30:
            winStr.append("\t\t4 of a Kind");
            break;
        case 10:
            winStr.append("\t\tFull House");
            break;
        case 8:
            winStr.append("\t\tFlush");
            break;
        case 6:
            winStr.append("\t\tStraight");
            break;
        case 5:
            winStr.append("\t\t3 of a Kind");
            break;
        case 2:
            winStr.append("\t\t2 of a Kind");
            break;
        case 500:
            winStr.append("\tYou can only have ");
            winStr.append(std::to_string(maxDiscard));
            winStr.append(" discards maximum");
            break;
        case 0:
            break;
        default:
            winStr.append("\t\tUnknown Win");
            break;
    }

    std::cout << winStr << "\n";

}

void RenderHold(bool ReplacePositions[])
{
    std::string Hold;
    for(int i = 0; i < HAND_SIZE; i++)
    {
        if(ReplacePositions[i]) // True - Render Discard ; False - Leave Blank
            Hold.append(" Discard   ");
        else
            Hold.append("           ");
    }
    Hold.append("\n");
    std::cout << Hold;
}

void RenderCards(Card card[])
{
    // Set Background to Green
    system("clear");

    std::string Top;
    std::string Middle1;
    std::string Middle2;
    std::string Middle3;
    std::string Bottom;
    std::string Hold;

    // Look at Cards
    for(int i = 0; i < 5; i++)
    {
        // Set Color
        if((card[i].suit & 1) == 1) // If Card is red (Odd ones are red)
        {
            Top.append(RED);
            Middle1.append(RED);
            Middle2.append(RED);
            Middle3.append(RED);
            Bottom.append(RED);
        }
        else
        {
            Top.append(BLACK);
            Middle1.append(BLACK);
            Middle2.append(BLACK);
            Middle3.append(BLACK);
            Bottom.append(BLACK);
        }

        // Add top
        Top.append("┌────────┐ ");

        // Add Middle1
        Middle1.append("│");
        Middle1 += getValueSymbol(card[i].value);
        if(card[i].value == 10)
            Middle1.append("      │ ");
        else
            Middle1.append("       │ ");
        // Add Middle2
        Middle2.append("│");
        Middle2.append(getSuitSymbol(card[i].suit));
        Middle2.append("       │ ");

        // Middle3 and Bottom
        Middle3.append("│        │ ");
        Bottom.append("└────────┘ ");

    }
    Top.append("\n");
    Middle1.append("\n");
    Middle2.append("\n");
    Middle3.append("\n");
    Bottom.append("\n");

    

    std::cout << Top;
    std::cout << Middle1;
    std::cout << Middle2;
    std::cout << Middle3;
    std::cout << Middle3;
    std::cout << Middle3;
    std::cout << Bottom;

}

#endif