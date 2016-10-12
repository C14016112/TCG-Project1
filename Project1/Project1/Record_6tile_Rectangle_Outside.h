#ifndef RECORD_6_TILE_RECTANGLE_OUTSIDE_H
#define RECORD_6_TILE_RECTANGLE_OUTSIDE_H
#pragma once
#include "assert.h"
#include "stdio.h"
/*
Class that save the data of strategy, only deal with four tiles one time

*/

const int iUpperBound_6tile = 20;
class Record_6tile_Rectangle_Outside
{
public:
	/*
	The constructor need the index of tiles
	Since this record use four tile, it needs 4 integers to input
	*/
	Record_6tile_Rectangle_Outside();
	~Record_6tile_Rectangle_Outside();
	void setScore(int inputindex[6], double score);
	void setScore(int board[4][4], double score);
	/*
	get the data at one position
	*/
	double getScore(int inputindex[6]);
	/*
	get the corresponding data if giving a board
	*/
	double getScore(int board[4][4]);
	double get_OneFeature_Score(int board[4][4], int no);
	void set_OneFeature_Score(int board[4][4], int no, double value);
private:
	double *Data ;
	int index[8][6];
	int iUpperBound;
};

#endif