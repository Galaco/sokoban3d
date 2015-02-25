/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Game Board
Description: 
*********************************************************************/
#ifndef GAMEBOARD_H
#define GAMEBOARD_H


class GameBoard {
public:
	GameBoard();
	~GameBoard();

	void addConnection(GameBoard*, int);
	void reset();

	void set(int, int, int);

private:
	int board[8][8];
	GameBoard* connections[4];
};
#endif
