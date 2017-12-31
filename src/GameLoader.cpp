#include "GameLoader.h"
#include "GameTree.h"

#include <string>
#include <algorithm>
#include <cctype>

GameLoader::GameLoader(const std::string &fileName) :
    mySrc(fileName)
{
}

bool
GameLoader::isOpen() const
{
    return mySrc.is_open();
}

bool
GameLoader::getNonEmptyLine(std::string &dest)
{
    while (std::getline(mySrc, dest))
    {
	auto f = [] (char c) { return std::isspace(static_cast<unsigned char>(c)); };

        if (!std::all_of(dest.begin(), dest.end(), f))
            return true;
    }

    return false;
}

bool
GameLoader::readGame(GameTree &game)
{
    if (!isOpen())
        return false;

    std::string rootName;

    if (!getNonEmptyLine(rootName))
        return false;

    std::string stateName;

    while (getNonEmptyLine(stateName))
    {
        GameState newState;

        int numChoices;

        if (!(mySrc >> numChoices))
            return false;

		std::string trash;
		std::getline(mySrc, trash);

        std::string choiceLabel;
        std::string choiceTarget;

        for (int i = 0; i < numChoices; ++i)
        {
            if (!(getNonEmptyLine(choiceLabel) && getNonEmptyLine(choiceTarget)))
                return false;

            newState.addChoice(choiceLabel, choiceTarget);
        }

        int numTextLines;

        if (!(mySrc >> numTextLines))
            return false;

		std::getline(mySrc, trash);

        std::string textBlock;
        std::string textLine;

        for (int i = 0; i < numTextLines; ++i)
        {
            if (!std::getline(mySrc, textLine))
                return false;

            textBlock += textLine;
            textBlock += "\n";
        }

        newState.setText(textBlock);

        if (!game.registerState(stateName, newState))
            return false;
    }

    return game.initializeRoot(rootName);
}
