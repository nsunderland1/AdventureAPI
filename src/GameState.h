#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <string>
#include <vector>

struct GameChoice
{
public:
    GameChoice(const std::string &label, const std::string &nextState);

    std::string label;
    std::string nextState;
};

class GameState
{
public:
    GameState(const std::string &text = "", std::initializer_list<GameChoice> choices = {});

    void                 setText(const std::string &text);
    void                 addChoice(const std::string &label, const std::string &nextState);

    const std::string    getText() const;
    bool                 isTerminal() const;
    int                  getNumChoices() const;
    const std::string    getChoiceLabel(int choiceNum) const;
    const std::string    getNextStateName(int choiceNum) const;

private:
    std::string             myText;
    std::vector<GameChoice> myChoices;
};

#endif
