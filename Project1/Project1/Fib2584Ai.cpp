#include "Fib2584Ai.h"


Fib2584Ai::Fib2584Ai()
{
	LEARNING_RATE = 0.0025;
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	ReadWeightTable();
	srand(time(NULL));
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			lastboard_moved[i][j] = 0;
		}
	}
	move.MakeTable();
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	for (int i = 0 ;i<4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			for (int k = 0 ; k<32 ; k++){
				if(board[i][j] == GameBoard::fibonacci_[k]){
					board[i][j] = k;
				}
			}
		}
	}

	MoveDirection currentaction = FindBestDirection(board);
	int tmpaward;
	move.Move((int)currentaction, board, tmpaward);
	if(isEmpty(lastboard_moved) == false){
		Learn_Evaluation(lastboard_moved, board, tmpaward);
	}

	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			lastboard_moved[i][j] = board[i][j];
		}
	}
	
	return currentaction;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			lastboard_moved[i][j] = 0;
		}
	}
}

double Fib2584Ai::Evaluate(int board[4][4])
{
	return record1.getScore(board) + record2.getScore(board) + record3.getScore(board);

}


void Fib2584Ai::Learn_Evaluation( int b1_moved[4][4], int b2_moved[4][4], int tmpaward)
{

	double next_value = 0;
	double now_value = 0;
	double delta = 0;
	now_value = record1.getScore(b1_moved) + record2.getScore(b1_moved) + record3.getScore(b1_moved);
	if (isFull(b2_moved) == true){
		delta = LEARNING_RATE * now_value * -1;
	}
	else{
		next_value = record1.getScore(b2_moved) + record2.getScore(b2_moved) + record3.getScore(b2_moved);
		delta = LEARNING_RATE * ((double)tmpaward + next_value - now_value);
	}
		
	for (int i = 0; i < 8; i++){
		double new_value1 = record1.get_OneFeature_Score(b1_moved, i) + delta ;
		record1.set_OneFeature_Score(b1_moved, i, new_value1);

		double new_value2 = record2.get_OneFeature_Score(b1_moved, i) + delta;
		record2.set_OneFeature_Score(b1_moved, i, new_value2);

		double new_value3 = record3.get_OneFeature_Score(b1_moved, i) + delta;
		record3.set_OneFeature_Score(b1_moved, i, new_value3);
	}
}

MoveDirection Fib2584Ai::FindBestDirection(int board[4][4])
{
	int nextaction = 0;
	double score[4] = {};
	int tmpboard[4][4][4] = {};

	for (int i = 0 ; i<4 ; i++){
		int moveboard[4][4] = {};
		for (int j = 0 ; j<4 ; j++){
			for (int k = 0 ;k<4 ;k++){
				moveboard[j][k] = board[j][k];
			}
		}

		int tmpaward = 0;
		move.Move(i, moveboard, tmpaward);
		score[i] = Evaluate(moveboard) + tmpaward;
		
		if(score[i] > score[nextaction]){
			nextaction = i;
		}
		for (int j = 0 ; j<4 ; j++){
			for (int k = 0 ;k<4 ;k++){
				tmpboard[i][j][k] = moveboard[j][k];
			}
		}
	}

	bool isSame = true;

	
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j<4 ; j++){
			if(tmpboard[nextaction][i][j] != board[i][j]){
				isSame = false;
				return static_cast<MoveDirection>(nextaction);
			}
		}
	}
	
	return static_cast<MoveDirection>(rand() % 4);
}

void Fib2584Ai::ReadWeightTable()
{
	char filename[30] = "WeightTable1.bin";
	char filename2[30] = "WeightTable2.bin";
	char filename3[30] = "WeightTable3.bin";
	ifstream fin(filename, ios::in | ios::binary );
	ifstream fin2(filename2, ios::in | ios::binary );
	ifstream fin3(filename3, ios::in | ios::binary );
	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		abort();
	}

	if( !fin2.is_open()){
		printf("The file '%s' was not open\n", filename2);
		abort();
	}

	if( !fin3.is_open()){
		printf("The file '%s' was not open\n", filename3);
		abort();
	}

	for (int i = 0; i < 32; i++){
		for (int j = 0; j < 32; j++){
			for (int k = 0; k < 32; k++){
				for (int l = 0; l < 32; l++){
					double value = 0;
					double value2 = 0;
					fin.read((char *)&value, sizeof(double));
					fin2.read((char *)&value2, sizeof(double));
					int inputindex[4] = {i, j, k, l};
					record1.setScore(inputindex, value);
					record2.setScore(inputindex, value);
				}
			}
		}
	}

	for (int i = 0 ; i<iUpperBound_6tile;i ++){
		for (int j = 0 ; j<iUpperBound_6tile ; j++){
			for (int k = 0 ; k<iUpperBound_6tile ; k++){
				for (int l = 0 ; l<iUpperBound_6tile ; l++){
					for (int m = 0 ; m < iUpperBound_6tile ; m++){
						for (int n = 0 ; n < iUpperBound_6tile ; n++){
							double value = 0 ;
							fin3.read((char *)&value, sizeof(double));
							int inputindex[6] = {i, j, k, l, m, n};
							record3.setScore(inputindex, value);
						}
					}
				}
			}
		}
	}
	fin.close();
	fin2.close();
	fin3.close();
}
void Fib2584Ai::WriteWeightTable()
{

	char filename[30] = "WeightTable1.bin";
	char filename2[30] = "WeightTable2.bin";
	char filename3[30] = "WeightTable3.bin";
	ofstream fout(filename, ios::out | ios::binary);
	ofstream fout2(filename2, ios::out | ios::binary);
	ofstream fout3(filename3, ios::out | ios::binary);

	if(!fout.is_open()){
		printf("The file '%s' was not open\n", filename);
		abort();
	}

	if(!fout2.is_open()){
		printf("The file '%s' was not open\n", filename2);
		abort();
	}
	
	if(!fout3.is_open()){
		printf("The file '%s' was not open\n", filename3);
		abort();
	}

	for (int i = 0; i < 32; i++){
		for (int j = 0; j < 32; j++){
			for (int k = 0; k < 32; k++){
				for (int l = 0; l < 32; l++){
					int inputindex[4] = { i, j, k, l };
					double value = record1.getScore(inputindex);
					double value2 = record2.getScore(inputindex);
					fout.write((char *)&value, sizeof(double));
					fout2.write((char *)&value2, sizeof(double));
				}
			}
		}
	}

	for (int i = 0 ; i<iUpperBound_6tile;i ++){
		for (int j = 0 ; j<iUpperBound_6tile ; j++){
			for (int k = 0 ; k<iUpperBound_6tile ; k++){
				for (int l = 0 ; l<iUpperBound_6tile ; l++){
					for (int m = 0 ; m < iUpperBound_6tile ; m++){
						for (int n = 0 ; n < iUpperBound_6tile ; n++){
							int inputindex[6] = {i, j, k, l, m, n};
							double value = record3.getScore(inputindex);
							fout3.write((char *)&value, sizeof(double));
						}
					}
				}
			}
		}
	}

	fout.close();
	fout2.close();
	fout3.close();
}

bool Fib2584Ai::isFull(int board[4][4])
{
	for (int i = 0 ;i < 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			if(board[i][j] == 0)
				return false;
		}
	}
	return true;
}

bool Fib2584Ai::isEmpty(int board[4][4])
{
	for (int i = 0 ;i < 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			if(board[i][j] != 0)
				return false;
		}
	}
	return true;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
