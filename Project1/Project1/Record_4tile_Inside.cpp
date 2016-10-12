#include "Record_4tile_Inside.h"

Record_4tile_Inside::Record_4tile_Inside()
{
	for (int i = 0 ;i < 4 ; i++){
		index[0][i] = i + 4;
		index[1][i] = 13 - 4 * i;
		index[2][i] = 2 + 4 * i;
		index[3][i] = 11 - i;
		index[4][i] = 7 - i;
		index[5][i] = 1 + 4 * i;
		index[6][i] = 8 + i;
		index[7][i] = 14 - 4 * i;
	}
	Data = new double[32*32*32*32];
	for (int i = 0 ; i< 32 * 32 * 32 * 32; i++){
		Data[i] = 0;
	}

	iUpperBound = 32;
}

Record_4tile_Inside::~Record_4tile_Inside()
{
	delete Data;
}

void Record_4tile_Inside::setScore(int inputindex[4], double score){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = score;
}

double Record_4tile_Inside::getScore(int inputindex[4]){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];
}

double Record_4tile_Inside::getScore(int board[4][4]){

	double value = 0;
	for (int i = 0 ; i< 8 ; i++){
		value = value + get_OneFeature_Score(board, i);
	}
	return value;
}


double Record_4tile_Inside::get_OneFeature_Score(int board[4][4], int no)
{
	assert(no >= 0 && no < 8);
	int index1 = board[index[no][0] / 4][index[no][0] % 4];
	int index2 = board[index[no][1] / 4][index[no][1] % 4];
	int index3 = board[index[no][2] / 4][index[no][2] % 4];
	int index4 = board[index[no][3] / 4][index[no][3] % 4];
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];

}

void Record_4tile_Inside::set_OneFeature_Score(int board[4][4], int no, double value)
{
	assert(no >= 0 && no < 8);
	int index1 = board[index[no][0] / 4][index[no][0] % 4];
	int index2 = board[index[no][1] / 4][index[no][1] % 4];
	int index3 = board[index[no][2] / 4][index[no][2] % 4];
	int index4 = board[index[no][3] / 4][index[no][3] % 4];
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = value;
}
