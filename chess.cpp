# include "game.h"
# include "io.h"
# include <iostream>
# include <string>
# include <ncurses.h>

int main()
{
    game g;
    g.clear();
    setupStandardTeams(&g);
    init_io();
    print_board(&g);
    while(!g.end)
    {
        process_turn(&g);
    }
    getch();
    endwin();
    std::cout << g.winner << " won!\n";
}