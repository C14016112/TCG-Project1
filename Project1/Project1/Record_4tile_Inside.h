#ifndef RECORD_4_TILE_INSIDE_H
#define RECORD_4_TILE_INSIDE_H
#pragma once
#include "assert.h"
#include "stdio.h"
/*
Class that save the data of strategy, only deal with four tiles one time

*/
class Record_4tile_Inside
{
public:
	/*
	The constructor need the index of tiles
	Since this record use four tile, it needs 4 integers to input
	*/
	Record_4tile_Inside();
	~Record_4tile_Inside();
	void setScore(int inputindex[4], double score);
	void setScore(int board[4][4], double score);
	/*
	get the data at one position
	*/
	double getScore(int inputindex[4]);
	/*
	get the corresponding data if giving a board
	*/
	double getScore(int board[4][4]);
	double get_OneFeature_Score(int board[4][4], int no);
	void set_OneFeature_Score(int board[4][4], int no, double value);
private:
	double *Data ;
	//int index[8][4];
	int index[8][4];
	int iUpperBound;
	//void Read_Record();
};

#endif