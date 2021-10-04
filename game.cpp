# include "game.h"
# include "team.h"
# include "io.h"

# include <ncurses.h>

void setupStandardTeams(game *g)
{
    g->red.name = "Red";
    g->red.team_color = team_red;
    g->blue.name = "Blue";
    g->blue.team_color = team_blue;
    g->red.setupPiecesTop();
    g->blue.setupPiecesBottom();
    g->turn = team_blue;
    g->end = false;
}

void process_turn(game *g)
{
    switch(g->turn)
    {
        case team_blue:
            do_turn(g, g->blue, g->blue.team_color);
            g->turn = team_red;
            break;
        case team_red:
            do_turn(g, g->red, g->red.team_color);
            g->turn = team_blue;
            break;
        case team_none:
            break;
    }
}
