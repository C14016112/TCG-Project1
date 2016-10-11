#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include "MoveDirection.h"
#include "MoveTable.h"
#include "BitBoard.h"
#include "Random.h"

using namespace std;

class Board
{
public:
	static const int fibonacci_[32];
private:
	static Random random_;
public:
	Board();
	void initialize();
	int move(MoveDirection moveDirection);
	void addRandomTile();
	bool terminated();
	void getArrayBoard(int board[4][4]);
	int getMaxTile();
	void showBoard();
	bool operator==(Board Board);
	void setBoard(BitBoard);
	int getFibonacci(int index);
	int countEmptyTile();
private:
	BitBoard getRow(int row);
	BitBoard getColumn(int column);
	BitBoard restoreRow(BitBoard rowBits, int row);
	BitBoard restoreColumn(BitBoard columnBits, int column);
	int getTile(int row, int column);
private:
	BitBoard board_;
};

#endif