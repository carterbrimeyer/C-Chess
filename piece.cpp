# include "piece.h"
# include "io.h"
# include "game.h"
# include <ncurses.h>

piece getKing()
{
    piece p;
    p.name = "King";
    p.symbol = 'K';
    p.type = piece_KING;
    return p;
}
piece getQueen()
{
    piece p;
    p.name = "Queen";
    p.symbol = 'Q';
    p.type = piece_QUEEN;
    return p;
}
piece getBishop()
{
    piece p;
    p.name = "Bishop";
    p.symbol = 'b';
    p.type = piece_BISHOP;
    return p;
}
piece getKnight()
{
    piece p;
    p.name = "Knight";
    p.symbol = 'k';
    p.type = piece_KNIGHT;
    return p;
}
piece getRook()
{
    piece p;
    p.name = "Rook";
    p.symbol = 'r';
    p.type = piece_ROOK;
    return p;
}
piece getPawn()
{
    piece p;
    p.name = "Pawn";
    p.symbol = 'p';
    p.type = piece_PAWN;
    return p;
}
void drawPiece(piece p)
{
    mvaddch( 4 + (3 * p.position[dim_y]), 5 + (5 * p.position[dim_x]), p.symbol);
}


/*bool removePiece(game *g, team t, piece p)
{
    switch(t.team_color)
    {
        case team_black:
            break;
        case team_white:
            break;
        case team_none:
            break;
    }
}*/