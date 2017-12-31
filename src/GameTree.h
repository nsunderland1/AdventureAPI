#ifndef __GAMETREE_H__
#define __GAMETREE_H__

#include <string>
#include <unordered_map>

#include "GameState.h"

class GameTree
{
public:
    GameTree();

    bool                 registerState(const std::string &name, GameState &state);
    bool                 initializeRoot(const std::string &rootName);

    bool                 isValidTree();

    const std::string    getText() const;
    bool                 isTerminal() const;
    int                  getNumChoices() const;
    const std::string    getChoiceLabel(int choiceNum) const;
    
    bool                 advanceToState(int choiceNum);
    void                 resetToRoot();

    bool                 resetToLastState();

private:
    bool                 isValidState(const GameState &state) const;

    enum class ValidityStatus
    {
        Unverified,
        Invalid,
        Valid
    };

    std::unordered_map<std::string, GameState> myStates;
    GameState *myRootState;
    GameState *myCurrentState;
    GameState *myLastState;

    ValidityStatus myValidityStatus;
};

#endif
