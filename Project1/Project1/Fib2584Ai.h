#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "GameBoard.h"
#include "MakeMoveTable.h"
#include "Record_4tile_Inside.h"
#include "Record_4tile_Outside.h"
#include "Record_6tile_Rectangle_Outside.h"
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
	double Evaluate(int board[4][4]);
	MoveDirection FindBestDirection(int board[4][4]);
	void Learn_Evaluation( int b1_moved[4][4], int b2_moved[4][4], int tmpaward);
	void ReadWeightTable();
	bool isFull(int board[4][4]);
	bool isEmpty(int board[4][4]);
private:
	double LEARNING_RATE;
	Record_4tile_Inside record1;
	Record_4tile_Outside record2;
	Record_6tile_Rectangle_Outside record3;
	int lastboard_moved[4][4];
	MakeMoveTable move;
};

#endif