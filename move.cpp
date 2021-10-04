#include "move.h"
#include "team.h"
#include "piece.h"

bool no_piece_at(game *g, teamColor tc, int x, int y)
{
    int i;
    switch(tc)
    {
        case team_blue:
            for(i = 0; i < 16; i++)
            {
                if (g->blue.pieces[i].position[dim_x] == x && g->blue.pieces[i].position[dim_y] == y)
                {
                    return false;
                }
            }
            break;
        case team_red:
            for(i = 0; i < 16; i++)
            {
                if (g->red.pieces[i].position[dim_x] == x && g->red.pieces[i].position[dim_y] == y)
                {
                    return false;
                }
            }
            break;
        default:
            return true;
    }
    return true;
}
bool enemy_at(game *g, teamColor tc, int x, int y)
{
    int i;
    switch(tc)
    {
        case team_blue:
            for(i = 0; i < 16; i++)
            {
                if (g->red.pieces[i].position[dim_x] == x && g->red.pieces[i].position[dim_y] == y)
                {
                    return true;
                }
            }
            break;
        case team_red:
            for(i = 0; i < 16; i++)
            {
                if (g->blue.pieces[i].position[dim_x] == x && g->blue.pieces[i].position[dim_y] == y)
                {
                    return true;
                }
            }
            break;
        default:
            return false;
    }
    return false;
}
int get_moves(game *g, piece p, teamColor tc, pair moves[64])
{
    int count = 0, i, j, x, y;
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    switch(p.type)
    {
        case piece_KNIGHT:
            for (i = 0; i < 8; i++) {

                x = p.position[dim_x] + X[i];
                y = p.position[dim_y] + Y[i];

                if (x >= 0 && y >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT && no_piece_at(g, tc, x, y))
                {
                    moves[count][dim_y] = y;
                    moves[count][dim_x] = x;
                    count++;
                }
            }
            break;
        case piece_PAWN:
            if(no_piece_at(g, tc, p.position[dim_x], p.position[dim_y] + (tc == team_blue ? -1 : 1))) {
                moves[count][dim_y] = p.position[dim_y] + (tc == team_blue ? -1 : 1);
                moves[count][dim_x] = p.position[dim_x];
                count++;
                if (p.firstTurn &&
                    no_piece_at(g, tc, p.position[dim_x], p.position[dim_y] + (tc == team_blue ? -2 : 2))) {
                    moves[count][dim_y] = p.position[dim_y] + (tc == team_blue ? -2 : 2);
                    moves[count][dim_x] = p.position[dim_x];
                    count++;
                }
            }
            if(enemy_at(g, tc, p.position[dim_x] + 1, p.position[dim_y] + (tc == team_blue ? -1 : 1)))
            {
                moves[count][dim_y] = p.position[dim_y] + (tc == team_blue ? -1 : 1);
                moves[count][dim_x] = p.position[dim_x] + 1;
                count++;
            }
            if(enemy_at(g, tc, p.position[dim_x] - 1, p.position[dim_y] + (tc == team_blue ? -1 : 1)))
            {
                moves[count][dim_y] = p.position[dim_y] + (tc == team_blue ? -1 : 1);
                moves[count][dim_x] = p.position[dim_x] - 1;
                count++;
            }
            break;
        case piece_KING:
            for(i = 0; i < 3; i++)
            {
                for(j = 0; j < 3; j++)
                {
                    if(no_piece_at(g, tc, p.position[dim_x] + j - 1, p.position[dim_y] + i - 1))// && (p.position[dim_y] + i) >= 0 && (p.position[dim_y] + i) < BOARD_HEIGHT && (p.position[dim_x] + j) < BOARD_WIDTH && (p.position[dim_x] + j) >= 0)
                    {
                        if((p.position[dim_y] + i - 1) >= 0 && (p.position[dim_y] + i - 1) < BOARD_HEIGHT && (p.position[dim_x] + j - 1) < BOARD_WIDTH && (p.position[dim_x] + j - 1) >= 0)
                        {
                            moves[count][dim_y] = p.position[dim_y] + i - 1;
                            moves[count][dim_x] = p.position[dim_x] + j - 1;
                            count++;
                        }

                    }
                }
            }
            break;
        case piece_BISHOP:
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] + i, p.position[dim_y] + i) && p.position[dim_x] + i >= 0
                   && p.position[dim_x] + i < BOARD_WIDTH && p.position[dim_y] + i >= 0 && p.position[dim_y] + i < BOARD_HEIGHT)
                {
                    moves[count][dim_y] = p.position[dim_y] + i;
                    moves[count][dim_x] = p.position[dim_x] + i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] + i, p.position[dim_y] + i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] - i, p.position[dim_y] + i) && p.position[dim_x] - i >= 0
                   && p.position[dim_x] - i < BOARD_WIDTH && p.position[dim_y] + i >= 0 && p.position[dim_y] + i < BOARD_HEIGHT)
                {
                    moves[count][dim_y] = p.position[dim_y] + i;
                    moves[count][dim_x] = p.position[dim_x] - i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] - i, p.position[dim_y] + i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] - i, p.position[dim_y] - i) && p.position[dim_x] - i >= 0
                   && p.position[dim_x] - i < BOARD_WIDTH && p.position[dim_y] - i >= 0 && p.position[dim_y] - i < BOARD_HEIGHT)
                {
                    moves[count][dim_y] = p.position[dim_y] - i;
                    moves[count][dim_x] = p.position[dim_x] - i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] - i, p.position[dim_y] - i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] + i, p.position[dim_y] - i) && p.position[dim_x] + i >= 0
                   && p.position[dim_x] + i < BOARD_WIDTH && p.position[dim_y] - i >= 0 && p.position[dim_y] - i < BOARD_HEIGHT)
                {
                    moves[count][dim_y] = p.position[dim_y] - i;
                    moves[count][dim_x] = p.position[dim_x] + i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] + i, p.position[dim_y] - i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            break;
        case piece_ROOK: // !--------------------------------------------------------------------------------------------------
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if((no_piece_at(g, tc, p.position[dim_x] + i, p.position[dim_y])) && p.position[dim_x] + i >= 0
                   && p.position[dim_x] + i < BOARD_WIDTH) //check +X
                {
                    moves[count][dim_y] = p.position[dim_y];
                    moves[count][dim_x] = p.position[dim_x] + i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] + i, p.position[dim_y]))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] - i, p.position[dim_y]) && p.position[dim_x] - i >= 0
                && p.position[dim_x] - i < BOARD_WIDTH) //check -X
                {
                    moves[count][dim_y] = p.position[dim_y];
                    moves[count][dim_x] = p.position[dim_x] - i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] - i, p.position[dim_y]))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x], p.position[dim_y] + i) && p.position[dim_y] + i >= 0
                && p.position[dim_y] + i < BOARD_HEIGHT) //check +Y
                {
                    moves[count][dim_y] = p.position[dim_y] + i;
                    moves[count][dim_x] = p.position[dim_x];
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x], p.position[dim_y] + i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x], p.position[dim_y] - i) && p.position[dim_y] - i >= 0
                   && p.position[dim_y] - i < BOARD_HEIGHT) //check -Y
                {
                    moves[count][dim_y] = p.position[dim_y] - i;
                    moves[count][dim_x] = p.position[dim_x];
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x], p.position[dim_y] - i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            break;
        case piece_QUEEN: // !---------------------------------------------------------------------------------------------------
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if((no_piece_at(g, tc, p.position[dim_x] + i, p.position[dim_y])) && p.position[dim_x] + i >= 0
                   && p.position[dim_x] + i < BOARD_WIDTH) //check +X
                {
                    moves[count][dim_y] = p.position[dim_y];
                    moves[count][dim_x] = p.position[dim_x] + i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] + i, p.position[dim_y]))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] - i, p.position[dim_y]) && p.position[dim_x] - i >= 0
                   && p.position[dim_x] - i < BOARD_WIDTH) //check -X
                {
                    moves[count][dim_y] = p.position[dim_y];
                    moves[count][dim_x] = p.position[dim_x] - i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] - i, p.position[dim_y]))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x], p.position[dim_y] + i) && p.position[dim_y] + i >= 0
                   && p.position[dim_y] + i < BOARD_HEIGHT) //check +Y
                {
                    moves[count][dim_y] = p.position[dim_y] + i;
                    moves[count][dim_x] = p.position[dim_x];
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x], p.position[dim_y] + i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x], p.position[dim_y] - i) && p.position[dim_y] - i >= 0
                   && p.position[dim_y] - i < BOARD_HEIGHT) //check -Y
                {
                    moves[count][dim_y] = p.position[dim_y] - i;
                    moves[count][dim_x] = p.position[dim_x];
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x], p.position[dim_y] - i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] + i, p.position[dim_y] + i) && p.position[dim_x] + i >= 0
                   && p.position[dim_x] + i < BOARD_WIDTH && p.position[dim_y] + i >= 0 && p.position[dim_y] + i < BOARD_HEIGHT)
                {
                    moves[count][dim_y] = p.position[dim_y] + i;
                    moves[count][dim_x] = p.position[dim_x] + i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] + i, p.position[dim_y] + i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] - i, p.position[dim_y] + i) && p.position[dim_x] - i >= 0
                   && p.position[dim_x] - i < BOARD_WIDTH && p.position[dim_y] + i >= 0 && p.position[dim_y] + i < BOARD_HEIGHT)
                {
                    moves[count][dim_y] = p.position[dim_y] + i;
                    moves[count][dim_x] = p.position[dim_x] - i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] - i, p.position[dim_y] + i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] - i, p.position[dim_y] - i) && p.position[dim_x] - i >= 0
                   && p.position[dim_x] - i < BOARD_WIDTH && p.position[dim_y] - i >= 0 && p.position[dim_y] - i < BOARD_HEIGHT)
                {
                    moves[count][dim_y] = p.position[dim_y] - i;
                    moves[count][dim_x] = p.position[dim_x] - i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] - i, p.position[dim_y] - i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for(i = 1; i < BOARD_HEIGHT ; i++)
            {
                if(no_piece_at(g, tc, p.position[dim_x] + i, p.position[dim_y] - i) && p.position[dim_x] + i >= 0
                   && p.position[dim_x] + i < BOARD_WIDTH && p.position[dim_y] - i >= 0 && p.position[dim_y] - i < BOARD_HEIGHT)
                {
                    moves[count][dim_y] = p.position[dim_y] - i;
                    moves[count][dim_x] = p.position[dim_x] + i;
                    count++;
                    if(enemy_at(g, tc, p.position[dim_x] + i, p.position[dim_y] - i))
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            break;
        default:
            break;
    }
    return count - 1;
}