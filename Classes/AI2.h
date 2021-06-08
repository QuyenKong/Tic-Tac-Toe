#pragma once


#include "cocos2d.h"
#include <vector>
#include <array>


//int aiPiece;
//
//int playerPiece;


bool isMoveLeft(int gridArray[3][3]);
int evaluate(int gridArray[3][3]);
int minimax(int gridArray[3][3], int depth, bool isMax);
struct Move findBestMove(int gridArray[3][3]);

