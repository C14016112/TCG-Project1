#ifndef __MAKEMOVETABLE_H__
#define __MAKEMOVETABLE_H__
#pragma once
#include "assert.h"
#include "MoveDirection.h"
#include "stdio.h"
class MakeMoveTable
{
public:
	MakeMoveTable(void);
	~MakeMoveTable(void);
	void MakeTable();
	void Move(int, int CurrentBoard[4][4], int & award);
private:
	void GetDataFromMoveTable(int i, int j, int k, int l, int index[5]);
	void MoveLeft(int CurrentBoard[4][4], int & award);
	void MoveUp(int CurrentBoard[4][4], int & award);
	void MoveDown(int CurrentBoard[4][4], int & award);
	void MoveRight(int CurrentBoard[4][4], int & award);
private:
	int iUpperbound;
	int *Move_Table ;
};

#endif