#ifndef CHESSGAME_TEAM_H
#define CHESSGAME_TEAM_H

# include "piece.h"

enum teamColor {
    team_red,
    team_blue,
    team_none
};

class team {
public:
    std::string name;
    teamColor team_color;
    int numPieces;
    piece pieces[16];
    void setupPiecesTop()
    {
        int i;
        numPieces = 16;
        pieces[0] = getKing();
        pieces[0].position[dim_y] = 0;
        pieces[0].position[dim_x] = 4;

        pieces[1] = getQueen();
        pieces[1].position[dim_y] = 0;
        pieces[1].position[dim_x] = 3;

        pieces[2] = getBishop();
        pieces[2].position[dim_y] = 0;
        pieces[2].position[dim_x] = 2;

        pieces[3] = getBishop();
        pieces[3].position[dim_y] = 0;
        pieces[3].position[dim_x] = 5;

        pieces[4] = getKnight();
        pieces[4].position[dim_y] = 0;
        pieces[4].position[dim_x] = 1;

        pieces[5] = getKnight();
        pieces[5].position[dim_y] = 0;
        pieces[5].position[dim_x] = 6;

        pieces[6] = getRook();
        pieces[6].position[dim_y] = 0;
        pieces[6].position[dim_x] = 0;

        pieces[7] = getRook();
        pieces[7].position[dim_y] = 0;
        pieces[7].position[dim_x] = 7;

        for(i = 8; i < 16; i++)
        {
            pieces[i] = getPawn();
            pieces[i].position[dim_y] = 1;
            pieces[i].position[dim_x] = 15 - i;
        }
    }
    void setupPiecesBottom()
    {
        int i;
        numPieces = 16;
        pieces[0] = getKing();
        pieces[0].position[dim_y] = 7;
        pieces[0].position[dim_x] = 4;

        pieces[1] = getQueen();
        pieces[1].position[dim_y] = 7;
        pieces[1].position[dim_x] = 3;

        pieces[2] = getBishop();
        pieces[2].position[dim_y] = 7;
        pieces[2].position[dim_x] = 2;

        pieces[3] = getBishop();
        pieces[3].position[dim_y] = 7;
        pieces[3].position[dim_x] = 5;

        pieces[4] = getKnight();
        pieces[4].position[dim_y] = 7;
        pieces[4].position[dim_x] = 1;

        pieces[5] = getKnight();
        pieces[5].position[dim_y] = 7;
        pieces[5].position[dim_x] = 6;

        pieces[6] = getRook();
        pieces[6].position[dim_y] = 7;
        pieces[6].position[dim_x] = 0;

        pieces[7] = getRook();
        pieces[7].position[dim_y] = 7;
        pieces[7].position[dim_x] = 7;

        for(i = 8; i < 16; i++)
        {
            pieces[i] = getPawn();
            pieces[i].position[dim_y] = 6;
            pieces[i].position[dim_x] = 15 - i;
        }
    }
};


#endif //CHESSGAME_TEAM_H
