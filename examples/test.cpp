#include "GameLoader.h"
#include "GameTree.h"

#include <iostream>
#include <limits>

void playGame(GameTree &theGame)
{
    std::string playAgain;
    bool backUpOne = false;

    do
    {
        std::cout << std::endl << std::endl;
        
        if (!backUpOne || !theGame.resetToLastState())
            theGame.resetToRoot();

        backUpOne = false;

        while (!theGame.isTerminal())
        {
            std::cout << theGame.getText() << std::endl << std::endl;
                 
            for (int i = 0, n = theGame.getNumChoices(); i < n; ++i)
            {
                std::cout << i << ": " << theGame.getChoiceLabel(i) << std::endl;
            }

            int nextState;

            do
            {
                while (!(std::cin >> nextState))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while (!theGame.advanceToState(nextState));

            std::cout << std::endl;
        }

        std::cout << theGame.getText() << std::endl;

        std::cout << std::endl << "Play again? [y/n] ";

        do
        {
            std::cin >> playAgain;
        } while ((playAgain != "y") && (playAgain != "n"));

        if (playAgain == "y")
        {
            std::cout << "Continue from one choice back? [y/n] ";
            std::string oneBack;

            do
            {
                std::cin >> oneBack;
            } while ((oneBack != "y") && (oneBack != "n"));

            if (oneBack == "y")
                backUpOne = true;
        }
    } while (playAgain == "y");

    std::cout << std::endl << "Thanks for playing!" << std::endl;
}

int main()
{
    GameLoader loader("testgame.adv");

    if (loader.isOpen())
    {
        GameTree game;

        if (loader.readGame(game))
        {
            playGame(game);
        }
        else
        {
            std::cout << "Failed to read game" << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to open file" << std::endl;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

