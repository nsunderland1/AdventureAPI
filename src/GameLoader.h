#ifndef __GAMELOADER_H__
#define __GAMELOADER_H__

#include <fstream>

class GameTree;

class GameLoader
{
public:
    GameLoader(const std::string &fileName);

    bool            isOpen() const;
    bool            readGame(GameTree &game);

private:
    bool            getNonEmptyLine(std::string &dest);

    std::ifstream   mySrc;
};

#endif
