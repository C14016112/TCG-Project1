#include "Record_6tile_Rectangle_Outside.h"

Record_6tile_Rectangle_Outside::Record_6tile_Rectangle_Outside()
{
	for (int i = 0 ;i < 6 ; i++){
		index[0][i] = 4*( i / 2 ) + ( i % 2 ) ;
		index[1][i] = 4 * (i % 2 ) + ( 6 - i + 1) / 2;
		index[2][i] = 15 - 4 * (i/2) - (i % 2);
		index[3][i] = 12 + ( i / 2) - 4 * ( i % 2);
		index[4][i] = 3 + 4 * ( i / 2 ) - ( i % 2);
		index[5][i] = 15 - 4 * ( i % 2 ) - i / 2;
		index[6][i] = 12 + ( i % 2) - 4 * ( i / 2);
		index[7][i] = 4 - 4 * ( i % 2) + (i / 2);
	}
	iUpperBound = iUpperBound_6tile;
	Data = new double[iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound];
	for (int i = 0 ; i< iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound; i++){
		Data[i] = 0;
	}
	
}

Record_6tile_Rectangle_Outside::~Record_6tile_Rectangle_Outside()
{
	delete Data;
}

void Record_6tile_Rectangle_Outside::setScore(int inputindex[6], double score){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	position += inputindex[4] *iUpperBound*iUpperBound*iUpperBound*iUpperBound + inputindex[5] * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	Data[position] = score;
}

double Record_6tile_Rectangle_Outside::getScore(int inputindex[6]){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	position += inputindex[4] *iUpperBound*iUpperBound*iUpperBound*iUpperBound + inputindex[5] * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	return Data[position];
}

double Record_6tile_Rectangle_Outside::getScore(int board[4][4]){

	double value = 0;
	for (int i = 0 ; i< 8 ; i++){
		value = value + get_OneFeature_Score(board, i);
	}
	return value;
}


double Record_6tile_Rectangle_Outside::get_OneFeature_Score(int board[4][4], int no)
{
	assert(no >= 0 && no < 8);
	int index1 = board[index[no][0] / 4][index[no][0] % 4];
	int index2 = board[index[no][1] / 4][index[no][1] % 4];
	int index3 = board[index[no][2] / 4][index[no][2] % 4];
	int index4 = board[index[no][3] / 4][index[no][3] % 4];
	int index5 = board[index[no][4] / 4][index[no][4] % 4];
	int index6 = board[index[no][5] / 4][index[no][5] % 4];
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	position += index5*iUpperBound*iUpperBound*iUpperBound*iUpperBound + index6 * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	return Data[position];

}

void Record_6tile_Rectangle_Outside::set_OneFeature_Score(int board[4][4], int no, double value)
{
	assert(no >= 0 && no < 8);
	int index1 = board[index[no][0] / 4][index[no][0] % 4];
	int index2 = board[index[no][1] / 4][index[no][1] % 4];
	int index3 = board[index[no][2] / 4][index[no][2] % 4];
	int index4 = board[index[no][3] / 4][index[no][3] % 4];
	int index5 = board[index[no][4] / 4][index[no][4] % 4];
	int index6 = board[index[no][5] / 4][index[no][5] % 4];
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	position += index5*iUpperBound*iUpperBound*iUpperBound*iUpperBound + index6 * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	Data[position] = value;
	
}
