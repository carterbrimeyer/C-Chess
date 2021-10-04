#ifndef CHESSGAME_PIECE_H
#define CHESSGAME_PIECE_H
# include <string>
# include <inttypes.h>

typedef enum dim {
    dim_x,
    dim_y,
    num_dims
} dim_t;

typedef int16_t pair[num_dims];

enum pieceType {
    piece_KING,
    piece_QUEEN,
    piece_BISHOP,
    piece_KNIGHT,
    piece_ROOK,
    piece_PAWN,
    piece_EMPTY
};

class piece {
public:
    std::string name;
    char symbol;
    pieceType type;
    pair position;
    bool firstTurn = true;
    void empty()
    {
        name = "empty";
        symbol = ' ';
        type = piece_EMPTY;
        position[dim_y] = 0;
        position[dim_x] = 0;
    }
};

piece getKing();
piece getQueen();
piece getBishop();
piece getKnight();
piece getRook();
piece getPawn();
void drawPiece(piece p);



#endif //CHESSGAME_PIECE_H
