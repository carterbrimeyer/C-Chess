#ifndef CHESSGAME_MOVE_H
#define CHESSGAME_MOVE_H

#include "team.h"
#include "piece.h"
#include "game.h"

int get_moves(game *g, piece p, teamColor tc, pair moves[64]);

#endif //CHESSGAME_MOVE_H
