#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "MoveDirection.h"
#include "Board.h"
#include "Record_4tile_Inside.h"
#include "Record_4tile_Outside.h"
#include <iostream>
#include <fstream>
class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);
	void WriteWeightTable();
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
private:
	double Evaluate(Board board);
	MoveDirection FindBestDirection(Board);
	void LearnEvaluation(Board b1, MoveDirection currentaction);
	BitBoard TransformArrayBoardToBitBoard(int [4][4]);
	void ReadWeightTable();
private:
	double LEARNING_RATE;
	Record_4tile_Inside record1;
	Record_4tile_Outside record2;
	Board lastboard;
	Board emptygameboard;
	MoveDirection lastdirection;
};

#endif