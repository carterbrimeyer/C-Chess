#ifndef CHESSGAME_GAME_H
#define CHESSGAME_GAME_H

# include <iostream>
# include <string>
# include <inttypes.h>

# include "team.h"

# define BOARD_WIDTH        8
# define BOARD_HEIGHT       8


class game {
public:
    team red;
    team blue;
    teamColor turn;
    bool end;
    std::string winner = "draw, no one";
    void clear()
    {
        int i;
        for(i = 0; i < 16; i++)
        {
            red.pieces[i].empty();
            blue.pieces[i].empty();
        }

    }
};

void setupStandardTeams(game *g);
void process_turn(game *g);

#endif
