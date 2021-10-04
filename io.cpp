#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <vector>

# include "io.h"
# include "game.h"
# include "move.h"

void init_io() {
    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
}
void makeOddLine(int offset)
{
    int i, j = 0;
    for(i = 5; j < 3;)
    {
        attron(COLOR_PAIR(COLOR_WHITE));
        mvprintw(offset + j, 3 + i, "#####");
        attroff(COLOR_PAIR(COLOR_WHITE));
        if(i > 30)
        {
            i = 5;
            j++;
        }
        else
        {
            i += 10;
        }
    }
}
void makeEvenLine(int offset)
{
    int i, j = 0;
    for(i = 0; j < 3;)
    {
        attron(COLOR_PAIR(COLOR_WHITE));
        mvprintw(offset + j, 3 + i, "#####");
        attroff(COLOR_PAIR(COLOR_WHITE));
        if(i > 20)
        {
            i = 0;
            j++;
        }
        else
        {
            i += 10;
        }
    }
}
void makeCheckered()
{
    makeOddLine(3);
    makeEvenLine( 6);
    makeOddLine(9);
    makeEvenLine( 12);
    makeOddLine(15);
    makeEvenLine( 18);
    makeOddLine(21);
    makeEvenLine( 24);
}
void print_board(game *g)
{
    int i;
    for(i = 4; i < 28; i++)
    {
        move(i, 0);
        clrtoeol();
    }
    makeCheckered();

    for(i = 0; i < 16; i++)
    {
        if(g->red.pieces[i].type != piece_EMPTY)
        {
            attron(COLOR_PAIR(COLOR_RED));
            mvaddch(4 + g->red.pieces[i].position[dim_y] * 3, (1 + g->red.pieces[i].position[dim_x]) * 5, g->red.pieces[i].symbol);
            attroff(COLOR_PAIR(COLOR_RED));
        }
        if(g->blue.pieces[i].type != piece_EMPTY) {
            attron(COLOR_PAIR(COLOR_BLUE));
            mvaddch(4 + g->blue.pieces[i].position[dim_y] * 3, (1 + g->blue.pieces[i].position[dim_x]) * 5,
                    g->blue.pieces[i].symbol);
            attroff(COLOR_PAIR(COLOR_BLUE));
        }
    }
    refresh();
}
void clearStatusLine()
{
    move(2, 0);
    clrtoeol();
}
void clearNotificationLine()
{
    move(1, 0);
    clrtoeol();
}
void clearTitleLine()
{
    move(0, 0);
    clrtoeol();
}
void clearExitLine()
{
    move(28, 0);
    clrtoeol();
}
void do_turn(game *g, team t, teamColor tc) //select piece
{
    int key;
    int color = (tc == team_red) ? COLOR_PAIR(COLOR_GREEN) : COLOR_PAIR(COLOR_YELLOW);
    int i = 0;
    bool action = false;
    mvprintw(0, 3, "%s's turn. Enter to confirm.", t.name.c_str());
    mvprintw(29, 3, "Up and Down arrows to cycle through options.");
    refresh();
    while(!action)
    {
        mvprintw(28, 3, "Q to exit program.");
        key = getch();
        clearStatusLine();
        print_board(g);
        switch(key)
        {
            case 'w':
            case 259: //up arrow
                if(i == 15)
                {
                    i = 0;
                }
                else
                {
                    i++;
                }
                while((tc == team_blue ? g->blue.pieces[i] : g->red.pieces[i]).type == piece_EMPTY)
                {
                    i++;
                    if(i == 15)
                    {
                        i = 0;
                    }
                    else
                    {
                        i++;
                    }
                }

                attron(color);
                drawPiece((tc == team_blue ? g->blue.pieces[i] : g->red.pieces[i]));
                attroff(color);
                break;
            case 's':
            case 258: //down arrow
                if(i == 0)
                {
                    i = 15;
                }
                else
                {
                    i--;
                }
                while((tc == team_blue ? g->blue.pieces[i] : g->red.pieces[i]).type == piece_EMPTY)
                {
                    i--;
                    if(i == 0)
                    {
                        i = 15;
                    }
                    else
                    {
                        i--;
                    }
                }

                attron(color);
                drawPiece((tc == team_blue ? g->blue.pieces[i] : g->red.pieces[i]));
                attroff(color);
                break;
            case 10: //Enter button
                action = move_piece(g, tc, i);
                clearNotificationLine();
                refresh();
                break;
            case 'q':
            case 'Q':
                g->end = true;
                action = true;
                break;
            default:
                mvprintw(2, 3, "Unbound key ! (%d)", key);
                break;
        }
        refresh();
    }
    clearTitleLine();
    refresh();
}
void check_take_piece(game *g, teamColor aggressor)
{
    int i, j;
    for(i = 0; i < 16; i++)
    {
        for(j = 0; j < 16; j++)
        {
            if((aggressor == team_blue ? g->blue.pieces[i] : g->red.pieces[i]).type != piece_EMPTY)
            {
                if((aggressor == team_blue ? g->blue.pieces[i] : g->red.pieces[i]).position[dim_x] == (aggressor == team_blue ? g->red.pieces[j] : g->blue.pieces[j]).position[dim_x]
                && (aggressor == team_blue ? g->blue.pieces[i] : g->red.pieces[i]).position[dim_y] == (aggressor == team_blue ? g->red.pieces[j] : g->blue.pieces[j]).position[dim_y])
                {
                    if((aggressor == team_blue ? g->red.pieces[j] : g->blue.pieces[j]).type == piece_KING)
                    {
                        g->end = true;
                        g->winner = (aggressor == team_blue ? g->blue.name : g->red.name);
                    }
                    (aggressor == team_blue ? g->red.pieces[j] : g->blue.pieces[j]).empty();
                }
            }
        }
    }
}
bool move_piece(game *g, teamColor tc, int j)
{
    pair moves[64];
    clearExitLine();
    int num = get_moves(g, (tc == team_blue ? g->blue.pieces[j] : g->red.pieces[j]), tc, moves);

    int key;
    int color = COLOR_PAIR(COLOR_YELLOW);
    int i = 0;
    bool action = false;
    refresh();
    if(num >= 0) {
        while (!action) {
            mvprintw(1, 3, "Moving %s. ESC to cancel.", g->blue.pieces[j].name.c_str());
            key = getch();
            clearStatusLine();
            print_board(g);
            switch (key) {
                case 'w':
                case 259: //up arrow
                    if (i == num) {
                        i = 0;
                    } else {
                        i++;
                    }
                    attron(color);
                    mvaddch(4 + (3 * moves[i][dim_y]), 5 + (5 * moves[i][dim_x]), '*');
                    attroff(color);
                    break;
                case 's':
                case 258: //down arrow
                    if (i == 0) {
                        i = num;
                    } else {
                        i--;
                    }
                    attron(color);
                    mvaddch(4 + (3 * moves[i][dim_y]), 5 + (5 * moves[i][dim_x]), '*');
                    attroff(color);
                    break;
                case 10: //Enter button
                    (tc == team_blue ? g->blue.pieces[j].position[dim_x] : g->red.pieces[j].position[dim_x]) = moves[i][dim_x];
                    (tc == team_blue ? g->blue.pieces[j].position[dim_y] : g->red.pieces[j].position[dim_y]) = moves[i][dim_y];
                    (tc == team_blue ? g->blue.pieces[j].firstTurn : g->red.pieces[j].firstTurn) = false;
                    check_take_piece(g, (tc == team_blue ? g->blue.team_color : g->red.team_color) );
                    print_board(g);
                    action = true;
                    break;
                case 27:
                    return false;
                    break;
                default:
                    mvprintw(2, 3, "Unbound key ! (%d)", key);
                    break;
            }
            refresh();
        }
    }
    else
    {
        mvprintw(2, 3, "No available moves for %s's %s!", (tc == team_blue ? g->blue.name.c_str() : g->red.name.c_str()),
                 (tc == team_blue ? g->blue.pieces[j].name.c_str() : g->red.pieces[j].name.c_str() ));
    }
    clearNotificationLine();
    refresh();
    return action;
}