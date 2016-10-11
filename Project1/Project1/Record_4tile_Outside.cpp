#include "Record_4tile_Outside.h"

Record_4tile_Outside::Record_4tile_Outside()
{
	for (int i = 0 ;i < 4 ; i++){
		index[0][i] = i;
		index[1][i] = 15 - i;
		index[2][i] = 12 - 4 * i;
		index[3][i] = 4 * i + 3;
		index[4][i] = 3 - i;
		index[5][i] = 4 * i;
		index[6][i] = 12 + i;
		index[7][i] = 15 - 4 * i;
	}
	Data = new double[32*32*32*32];
	for (int i = 0 ; i< 32*32*32*32 ; i++)
		Data[i] = 0;
	iUpperBound = 32;
}

Record_4tile_Outside::~Record_4tile_Outside()
{
	delete Data;
}

void Record_4tile_Outside::setScore(int inputindex[4], double score){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = score;
}

double Record_4tile_Outside::getScore(int inputindex[4]){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];
}

double Record_4tile_Outside::getScore(int board[4][4]){
	double value = 0;
	for (int i = 0 ; i< 8 ; i++){
		value = value + get_OneFeature_Score(board, i);
	}
	return value;
}


double Record_4tile_Outside::get_OneFeature_Score(int board[4][4], int no)
{
	assert(no >= 0 && no < 8);
	int index1 = board[index[no][0] / 4][index[no][0] % 4];
	int index2 = board[index[no][1] / 4][index[no][1] % 4];
	int index3 = board[index[no][2] / 4][index[no][2] % 4];
	int index4 = board[index[no][3] / 4][index[no][3] % 4];
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	assert(position >= 0 && position < 32*32*32*32);
	return Data[position];
}

void Record_4tile_Outside::set_OneFeature_Score(int board[4][4], int no, double value)
{
	assert(no >= 0 && no < 8);
	int index1 = board[index[no][0] / 4][index[no][0] % 4];
	int index2 = board[index[no][1] / 4][index[no][1] % 4];
	int index3 = board[index[no][2] / 4][index[no][2] % 4];
	int index4 = board[index[no][3] / 4][index[no][3] % 4];
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	assert(position >= 0 && position < 32*32*32*32);
	Data[position] = value;
}

double Record_4tile_Outside::getData(int position)
{
	return Data[position] ;
}
