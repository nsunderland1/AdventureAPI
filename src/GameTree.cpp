#include "GameTree.h"

GameTree::GameTree()
    : myRootState(nullptr), myCurrentState(nullptr), myLastState(nullptr),
      myValidityStatus(ValidityStatus::Unverified)
{
}

bool
GameTree::registerState(const std::string &name, GameState &state)
{
    if (myStates.find(name) != myStates.end())
    {
        return false;
    }
    else
    {
        myValidityStatus = ValidityStatus::Unverified;
        myStates.emplace(name, state);
        return true;
    }
}

bool
GameTree::initializeRoot(const std::string &rootName)
{
    auto findResult = myStates.find(rootName);

    if (findResult == myStates.end())
    {
        return false;
    }
    else
    {
        myRootState = &findResult->second;
        return true;
    }
}

bool
GameTree::isValidState(const GameState &state) const
{
    for (int i = 0, n = state.getNumChoices(); i < n; ++i)
    {
        auto stateInfo = myStates.find(state.getNextStateName(i));

        if ((stateInfo == myStates.end()) || !isValidState(stateInfo->second))
        {
            return false;
        }
    }

    return true;
}

bool
GameTree::isValidTree()
{
    if (myValidityStatus != ValidityStatus::Unverified)
        return myValidityStatus != ValidityStatus::Invalid;

    if (!myRootState)
    {
        myValidityStatus = ValidityStatus::Invalid;
        return false;
    }

    if (!isValidState(*myRootState))
    {
        myValidityStatus = ValidityStatus::Invalid;
        return false;
    }
    else
    {
        myValidityStatus = ValidityStatus::Valid;
        return true;
    }
}

const std::string
GameTree::getText() const
{
    return myCurrentState ? myCurrentState->getText() : std::string("");
}

bool
GameTree::isTerminal() const
{
    return myCurrentState ? myCurrentState->isTerminal() : true;
}

int
GameTree::getNumChoices() const
{
    return myCurrentState ? myCurrentState->getNumChoices() : 0;
}

const std::string
GameTree::getChoiceLabel(int choiceNum) const
{
    return myCurrentState ? myCurrentState->getChoiceLabel(choiceNum) : std::string("");
}

bool
GameTree::advanceToState(int choiceNum)
{
    if (!myCurrentState)
    {
        return false;
    }

    auto findResult = myStates.find(myCurrentState->getNextStateName(choiceNum));

    if (findResult == myStates.end())
    {
        return false;
    }
    else
    {
        myLastState = myCurrentState;
        myCurrentState = &findResult->second;
        return true;
    }
}

void
GameTree::resetToRoot()
{
    myCurrentState = myRootState;
    myLastState = nullptr;
}

bool
GameTree::resetToLastState()
{
    if (!myLastState)
    {
        return false;
    }
    else
    {
        myCurrentState = myLastState;
        myLastState = nullptr;
        return true;
    }
}
