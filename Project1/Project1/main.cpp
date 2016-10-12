#include <iostream>
#include <cstdlib>
#include "GameBoard.h"
#include "MoveDirection.h"
#include "Statistic.h"
#include "Fib2584Ai.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		return 1;
	}*/
	//int iPlayRounds = atoi(argv[1]);
	int iPlayRounds = 1000;
	double start, end;
	start = clock();
	// create and initialize AI
	Fib2584Ai ai;
	ai.initialize(argc, argv);

	// initialize statistic data
	Statistic statistic;
	statistic.setStartTime();
	// play each round
	
	for(int i = 0;i < iPlayRounds;i++) {
		if( i % (iPlayRounds/10) == 0 )
			printf(" %d \n", i);

		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while(!gameBoard.terminated()) {
			

			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection = ai.generateMove(arrayBoard);
			GameBoard originalBoard = gameBoard;

			iScore += gameBoard.move(moveDirection);

			if(originalBoard == gameBoard){
				
				if (originalBoard.board_.left_ != gameBoard.board_.left_ || originalBoard.board_.right_!= gameBoard.board_.right_){
					system("pause");
					cout << "shit\n\n" ;
				}
				continue;
				}
			statistic.increaseOneMove();

			gameBoard.addRandomTile();
			
		}

		gameBoard.getArrayBoard(arrayBoard);
		ai.gameOver(arrayBoard, iScore);
		statistic.increaseOneGame();

		// update statistic data
		statistic.updateScore(iScore);
		statistic.updateMaxTile(gameBoard.getMaxTile());
	}
	statistic.setFinishTime();
	if(iPlayRounds > 99999)
		ai.WriteWeightTable();
	// output statistic data
	statistic.show();

	end = clock();
	printf(" Running time: %f \n", (end - start) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}