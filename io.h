#ifndef CHESSGAME_IO_H
#define CHESSGAME_IO_H

#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

# include "game.h"


void init_io();
void print_board(game *g);
void clearStatusLine();
void clearNotificationLine();
void do_turn(game *g, team t, teamColor tc);
bool move_piece(game *g, teamColor tc, int i);

#endif //CHESSGAME_IO_H
