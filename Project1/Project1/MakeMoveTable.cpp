#include "MakeMoveTable.h"


MakeMoveTable::MakeMoveTable(void)
{
	iUpperbound = 20;
	Move_Table = new int[iUpperbound*iUpperbound*iUpperbound*iUpperbound*5];
	for (int i = 0 ; i< iUpperbound*iUpperbound*iUpperbound*iUpperbound*5 ; i++)
		Move_Table[i] = 0;
}


MakeMoveTable::~MakeMoveTable(void)
{
}

void MakeMoveTable::MakeTable()
{
	// move table for moving to left
	for (int i = 0 ; i< iUpperbound ; i++){
		for (int j = 0 ; j< iUpperbound ; j++){
			for (int k = 0 ; k< iUpperbound ; k++){
				for (int l = 0 ; l < iUpperbound ; l++){
					// the fifth element is award

					int index[5] = {i, j, k, l, 0};

					// pull the element to the left side
					int head = 0; 
					int tail = 0;
					while(tail < 4){
						if(index[tail] != 0){
							int tmp = index[head];
							index[head] = index[tail];
							index[tail] = tmp;
							head++;
							tail++;
						}
						else{
							tail++;
						}
					}

					int check_position = 0;
					while(check_position < 3){
						if(index[check_position] != 0 && index[check_position + 1] != 0 && (index[check_position] == index[check_position + 1] + 1 || index[check_position] == index[check_position + 1] - 1)){
							if(index[check_position] == index[check_position + 1] + 1){
								index[check_position] = index[check_position] + 1;
								index[check_position + 1] = 0;
								index[4] = index[4] + (2 << index[check_position]);
							}
							else{
								index[check_position] = index[check_position] + 2;
								index[check_position + 1] = 0;
								index[4] = index[4] + ( 2 << index[check_position]);
							}
							check_position = check_position + 2;
						}
						else{
							check_position = check_position + 1;
						}
					}

					// pull to left again
					head = 0; 
					tail = 0;
					while(tail < 4){
						if(index[tail] != 0 ){
							int tmp = index[head];
							index[head] = index[tail];
							index[tail] = tmp;
							head++;
							tail++;
						}
						else{
							tail++;
						}
					}
					for (int m = 0 ; m < 5 ; m++){
						Move_Table[5 * i + 5 * j * iUpperbound + 5 * k * iUpperbound * iUpperbound + 5 * l * iUpperbound*iUpperbound*iUpperbound + m] = index[m];
					}
				}
			}
		}
	}
}

void MakeMoveTable::MoveLeft(int CurrentBoard[4][4], int & award)
{
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] ={};
		for (int j = 0 ; j< 4 ;j ++){
			boardindex[j] = CurrentBoard[i][j];
		}

		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[i][j] = newindex[j];
		}
	}
}

void MakeMoveTable::MoveRight(int CurrentBoard[4][4], int & award)
{
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] ={};
		for (int j = 0 ; j< 4 ;j ++){
			boardindex[j] = CurrentBoard[i][3 - j];
		}

		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[i][3-j] = newindex[j];
		}
	}
}

void MakeMoveTable::MoveUp(int CurrentBoard[4][4], int & award)
{
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int index[4] = {i, 4 + i, 8 + i, 12 + i};
		int boardindex[4] ={};
		for (int j = 0 ; j< 4 ;j ++){
			boardindex[j] = CurrentBoard[j][i];
		}

		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[j][i] = newindex[j];
		}
	}
}

void MakeMoveTable::MoveDown(int CurrentBoard[4][4], int & award)
{
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int index[4] = {12 + i, 8 + i, 4 + i, i};
		int boardindex[4] ={};
		for (int j = 0 ; j< 4 ;j ++){
			boardindex[j] = CurrentBoard[3 - j][i];
		}

		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[3-j][i] = newindex[j];
		}
	}
}

void MakeMoveTable::Move(int action, int CurrentBoard[4][4], int & award){
	assert(action >= 0 && action < 4);
	if (static_cast<MoveDirection>(action) == MOVE_DOWN){
		MoveDown(CurrentBoard, award);
		return ;
	}
	if (static_cast<MoveDirection>(action) == MOVE_UP){
		MoveUp(CurrentBoard, award);
		return ;
	}
	if (static_cast<MoveDirection>(action) == MOVE_RIGHT){
		MoveRight(CurrentBoard, award);
		return ;
	}
	if (static_cast<MoveDirection>(action) == MOVE_LEFT){
		MoveLeft(CurrentBoard, award);
		return ;
	}
}


void MakeMoveTable::GetDataFromMoveTable(int i, int j, int k, int l, int index[5])
{
	index[0] = Move_Table[5 * i + 5 * j * iUpperbound + 5 * k * iUpperbound*iUpperbound + 5 * l *iUpperbound*iUpperbound*iUpperbound+ 0];
	index[1] = Move_Table[5 * i + 5 * j * iUpperbound + 5 * k * iUpperbound*iUpperbound + 5 * l *iUpperbound*iUpperbound*iUpperbound+ 1];
	index[2] = Move_Table[5 * i + 5 * j * iUpperbound + 5 * k * iUpperbound*iUpperbound + 5 * l *iUpperbound*iUpperbound*iUpperbound+ 2];
	index[3] = Move_Table[5 * i + 5 * j * iUpperbound + 5 * k * iUpperbound*iUpperbound + 5 * l *iUpperbound*iUpperbound*iUpperbound+ 3];
	index[4] = Move_Table[5 * i + 5 * j * iUpperbound + 5 * k * iUpperbound*iUpperbound + 5 * l *iUpperbound*iUpperbound*iUpperbound+ 4];
}
