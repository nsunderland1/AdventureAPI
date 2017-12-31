#include "GameState.h"
#include <initializer_list>

GameChoice::GameChoice(const std::string &label, const std::string &nextState)
    : label(label), nextState(nextState)
{
}

GameState::GameState(const std::string &text, std::initializer_list<GameChoice> choices)
    : myText(text), myChoices(choices)
{
}

void
GameState::setText(const std::string &text)
{
    myText = text;
}

void
GameState::addChoice(const std::string &label, const std::string &nextState)
{
    myChoices.emplace_back(label, nextState);
}

const std::string
GameState::getText() const
{
    return myText;
}

bool
GameState::isTerminal() const
{
    return myChoices.size() == 0;
}

int
GameState::getNumChoices() const
{
    return myChoices.size();
}

const std::string
GameState::getChoiceLabel(int choiceNum) const
{
    if ((choiceNum >= 0) && (choiceNum < myChoices.size()))
        return myChoices[choiceNum].label;

    return std::string("");
}

const std::string
GameState::getNextStateName(int choiceNum) const
{
    if ((choiceNum >= 0) && (choiceNum < myChoices.size()))
        return myChoices[choiceNum].nextState;

    return std::string("");
}
