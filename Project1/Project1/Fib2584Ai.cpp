#include "Fib2584Ai.h"


Fib2584Ai::Fib2584Ai()
{
	LEARNING_RATE = 0.0025;
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	ReadWeightTable();
	srand(time(NULL));
	int emptyboard[4][4] = {};
	emptygameboard.setBoard(TransformArrayBoardToBitBoard(emptyboard));
	lastboard = emptygameboard;
	lastdirection = static_cast<MoveDirection>(0) ;
	return;
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	BitBoard bitboard = TransformArrayBoardToBitBoard(board);
	
	Board gameboard;
	gameboard.setBoard(bitboard);
	MoveDirection currentaction = FindBestDirection(gameboard);
	if((lastboard == emptygameboard) == false)
		LearnEvaluation(gameboard, currentaction);
	
	lastboard = gameboard;
	lastdirection = currentaction;
	return lastdirection;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	int emptyboard[4][4] = {};
	emptygameboard.setBoard(TransformArrayBoardToBitBoard(emptyboard));
	lastboard = emptygameboard;
	lastdirection = static_cast<MoveDirection>(0) ;
	return;
}

double Fib2584Ai::Evaluate(Board board)
{
	int arrayboard[4][4] = {};
	board.getArrayBoard(arrayboard);

	// transform the number of board into fibonacci number
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			for (int l = 0 ; l< 32 ; l++){
				if(arrayboard[i][j] == Board::fibonacci_[l])
					arrayboard[i][j] = l;
			}
		}
	}
	return record1.getScore(arrayboard) + record2.getScore(arrayboard);
}

BitBoard Fib2584Ai::TransformArrayBoardToBitBoard(int arrayboard[4][4])
{

	// first, transform the number of array board to order of fibonacci number
	// example, 89 -> F_10
	int fibonacciboard[4][4] = {};
	for (int i = 0 ;i < 4 ; i++){
		for(int j = 0 ; j< 4 ; j++){
			for(int l = 0 ; l< 32 ; l++){
				if(arrayboard[i][j] == Board::fibonacci_[l]){
					fibonacciboard[i][j] = l;
				}
			}
		}
	}


	/*
	1   2  3  4
	5   6  7  8
	9  10 11 12
	13 14 15 16
	1~3 are in left board
	5~16 are in right board
	4 is in both boards;
	*/

	unsigned long long int left_of_bitboard = 0;
	unsigned long long int right_of_bitboard = 0;
	unsigned long long int base = 1;
	for (int i = 3 ; i> 0 ; i--){
		for (int j = 3 ; j >= 0 ; j--){
			right_of_bitboard += base * fibonacciboard[i][j];
			base *= 32;
		}
	}
	if(arrayboard[0][3] > 15){
		right_of_bitboard += base * ( fibonacciboard[0][3] - 16 );
	}
	else{
		right_of_bitboard += base * fibonacciboard[0][3];
	}

	base = 2;
	for (int i = 2 ; i >= 0  ; i--){
		left_of_bitboard += base * fibonacciboard[0][i];
		base = base * 32;
	}
	
	BitBoard bitboard(left_of_bitboard, right_of_bitboard);


	return bitboard;
}

void Fib2584Ai::LearnEvaluation(Board b2, MoveDirection currentaction)
{
	int b1_moved_array[4][4];
	int b2_moved_array[4][4];
	Board b1 = lastboard;
	Board b1_moved;
	Board b2_moved;
	b1_moved = b1;
	b1_moved.move(lastdirection);
	MoveDirection current_action = currentaction;
	/*
	COMPUTE AFTERSTATE( s'', a_next)
	*/
	int tmpaward = 0; // r_next
	b2_moved = b2;
	tmpaward = b2_moved.move(current_action);

	b1_moved.getArrayBoard(b1_moved_array);
	b2_moved.getArrayBoard(b2_moved_array);
	for (int i = 0 ;i < 4 ; i++){
		for(int j = 0 ; j< 4 ; j++){
			for(int l = 0 ; l< 32 ; l++){
				if(b1_moved_array[i][j] == Board::fibonacci_[l]){
					b1_moved_array[i][j] = l;
				}
				if(b2_moved_array[i][j] == Board::fibonacci_[l]){
					b2_moved_array[i][j] = l;
				}
			}
		}
	}
	
	double next_value = 0;
	double now_value = 0;
	double delta = 0;
	now_value = record1.getScore(b1_moved_array) + record2.getScore(b1_moved_array);
	if (b2.countEmptyTile() == 0){
		delta = LEARNING_RATE * now_value * -1;
	}
	else{
		next_value = record1.getScore(b2_moved_array) + record2.getScore(b2_moved_array);
		delta = LEARNING_RATE * ((double)tmpaward + next_value - now_value);
	}
		
	for (int i = 0; i < 8; i++){
		double new_value1 = record1.get_OneFeature_Score(b1_moved_array, i) + delta ;
		record1.set_OneFeature_Score(b1_moved_array, i, new_value1);

		new_value1 = 0;
		double new_value2 = record2.get_OneFeature_Score(b1_moved_array, i) + delta;
		record2.set_OneFeature_Score(b1_moved_array, i, new_value2);

	}
	

}

MoveDirection Fib2584Ai::FindBestDirection(Board board)
{
	int nextaction = 0;
	double score[4] = {};
	Board originalboard = board;
	for (int i = 0 ; i< 4 ; i++){
		Board newboard;
		newboard = board;
		newboard.move(static_cast<MoveDirection>(i));
		score[i] = Evaluate(newboard);
	}

	MoveDirection nextMove;

	for (int i = 0 ; i< 4 ; i++){
		if(score[i] > score[nextaction]){
			nextaction = i;
		}
	}

	board.move(static_cast<MoveDirection>(nextaction));
	if(originalboard == board){
		nextMove = static_cast<MoveDirection>(rand() % 4);
	}
	else{

		//printf("%d \n", gameboard.move(static_cast<MoveDirection>(nextaction)));
		nextMove = static_cast<MoveDirection>(nextaction);
	}

	return nextMove;
}

void Fib2584Ai::ReadWeightTable()
{
	/*FILE * score_data;
	FILE * score_data2;
	errno_t err;
	errno_t err2;
	char name[30] = "WeightTable1.bin";
	char name2[30] = "WeightTable2.bin";

	if ((err = fopen_s(&score_data, name, "rb")) != 0){
		printf("The file '%s' was not opened\n", name);
	}
	else
	{
		printf("The file '%s' was opened\n", name);

		for (int i = 0; i < 32; i++){
			for (int j = 0; j < 32; j++){
				for (int k = 0; k < 32; k++){
					for (int l = 0; l < 32; l++){
						double value = 0;
						fscanf_s(score_data, "%lf", &value);
						int inputindex[4] = {i, j, k, l};
						record1.setScore(inputindex, value);
					}
				}
			}
		}
		if (score_data)
		{
			if (fclose(score_data))
			{
				printf("The file '%s' was not closed\n", name);
			}
		}
	}

	if ((err2 = fopen_s(&score_data2, name2, "rb")) != 0){
		printf("The file '%s' was not opened\n", name2);
	}
	else
	{
		printf("The file '%s' was opened\n", name2);

		for (int i = 0; i < 32; i++){
			for (int j = 0; j < 32; j++){
				for (int k = 0; k < 32; k++){
					for (int l = 0; l < 32; l++){
						double value = 0;
						fscanf_s(score_data2, "%lf", &value);
						int inputindex[4] = {i, j, k, l};
						record2.setScore(inputindex, value);
					}
				}
			}
		}
		if (score_data2)
		{
			if (fclose(score_data2))
			{
				printf("The file '%s' was not closed\n", name2);
			}
		}
	}*/

	char filename[30] = "WeightTable1.bin";
	char filename2[30] = "WeightTable2.bin";

	ifstream fin(filename, ios::in | ios::binary );
	ifstream fin2(filename2, ios::in | ios::binary );
	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		abort();
	}

	if( !fin2.is_open()){
		printf("The file '%s' was not open\n", filename2);
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
}
void Fib2584Ai::WriteWeightTable()
{
	/*FILE * data;
	FILE * data2;
	errno_t err;
	errno_t err2;
	char name[30] = "WeightTable1.bin";
	char name2[30] = "WeightTable2.bin";

	if ((err = fopen_s(&data, name, "wb")) != 0)
		printf("The file '%s' was not opened\n", name);
	else
		printf("The file '%s' was opened\n", name);

	if ((err2 = fopen_s(&data2, name2, "wb")) != 0)
		printf("The file '%s' was not opened\n", name2);
	else
		printf("The file '%s' was opened\n", name2);

	for (int i = 0; i < 32; i++){
		for (int j = 0; j < 32; j++){
			for (int k = 0; k < 32; k++){
				for (int l = 0; l < 32; l++){
					int index[4] = { i, j, k, l };
					fprintf(data, "%lf \n", record1.getScore(index));
					fprintf(data2, "%lf \n", record2.getScore(index));
				}
			}
		}
	}

	if (data)
	{
		if (fclose(data))
		{
			printf("The file '%s' was not closed\n", name);
		}
	}
	if (data2){
		if(fclose(data2)){
			printf("The file '%s' was not closed\n", name2);
		}
	}*/

	char filename[30] = "WeightTable1.bin";
	char filename2[30] = "WeightTable2.bin";
	ofstream fout(filename, ios::out | ios::binary);
	ofstream fout2(filename2, ios::out | ios::binary);

	if(!fout.is_open()){
		printf("The file '%s' was not open\n", filename);
		abort();
	}

	if(!fout2.is_open()){
		printf("The file '%s' was not open\n", filename2);
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
	fout.close();
	fout2.close();
}
/**********************************
You can implement any additional functions
you may need.
**********************************/
