#ifndef RECORD_4_TILE_OUTSIDE_H
#define RECORD_4_TILE_OUTSIDE_H
#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
/*
Class that save the data of strategy, only deal with four tiles one time

*/
class Record_4tile_Outside
{
public:
	/*
	The constructor need the index of tiles
	Since this record use four tile, it needs 4 integers to input
	*/
	Record_4tile_Outside();
	~Record_4tile_Outside();
	void setScore(int inputindex[4], double score); // use to write data from weight table file
	void setScore(int board[4][4], double score);
	/*
	get the data at one position
	*/
	double getScore(int inputindex[4]); // use to write the data of weight table into a file
	/*
	get the corresopnding data if giving a board
	*/
	double getScore(int board[4][4]);
	double get_OneFeature_Score(int board[4][4], int no);
	void set_OneFeature_Score(int board[4][4], int no, double value);
	double getData(int position);
private:
	double *Data;
	int index[8][4];
	int iUpperBound;
};

#endif