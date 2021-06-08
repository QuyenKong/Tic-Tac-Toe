#include "AI2.h"
#include "GameScene.h"
#include "Definitions.h"
using namespace std;


bool isMoveLeft(int gridArray[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (EMPTY_PIECE == gridArray[i][j])
                return true;
        }
    }

    return false;
}

int evaluate(int gridArray[3][3])
{
    for (int column = 0; column < 3; column++)
    {
        //Check if game won vertically
        if (gridArray[0][column] == gridArray[1][column] && gridArray[1][column] == gridArray[2][column])
        {
            if (PLAYER_PIECE == gridArray[0][column])
                return -10;
            else if (AI_PIECE == gridArray[0][column])
                return 10;
        }
    }

    for (int row = 0; row < 3; row++)
    {
        //Check if game won horizontally
        if (gridArray[row][0] == gridArray[row][1] && gridArray[row][1] == gridArray[row][2])
        {
            if (PLAYER_PIECE == gridArray[row][0])
                return -10;
            else if (AI_PIECE == gridArray[row][0])
                return 10;
        }
    }

    //Check if game won diagonally
    if (gridArray[0][0] == gridArray[1][1] && gridArray[1][1] == gridArray[2][2])
    {
        if (PLAYER_PIECE == gridArray[0][0])
            return -10;
        else if (AI_PIECE == gridArray[0][0])
            return 10;
    }

    if (gridArray[0][2] == gridArray[1][1] && gridArray[1][1] == gridArray[2][0])
    {
        if (PLAYER_PIECE == gridArray[1][1])
            return -10;
        else if (AI_PIECE == gridArray[1][1])
            return 10;
    }

    //If game is not won
    return 0;
}

int minimax(int gridArray[3][3], int depth, bool isMax)
{
    int score = evaluate(gridArray);
    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth;

    if (!isMoveLeft(gridArray))
        return 0;

    //Maximizer's (AI's) move
    if (isMax)
    {
        int best = -1000;

        //loop through the board
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (EMPTY_PIECE == gridArray[i][j])
                {
                    gridArray[i][j] = AI_PIECE;
                    best = max(best, minimax(gridArray, depth + 1, !isMax));
                    gridArray[i][j] = EMPTY_PIECE;
                }
            }
        }
        return best;
    }
    else //Minimizer's (Player's) move
    {
        int best = 1000;
        //loop through the board
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (EMPTY_PIECE == gridArray[i][j])
                {
                    gridArray[i][j] = PLAYER_PIECE;
                    best = min(best, minimax(gridArray, depth + 1, !isMax));
                    gridArray[i][j] = EMPTY_PIECE;
                }
            }
        }
        return best;
    }
}

struct Move findBestMove(int gridArray[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.x = -1;
    bestMove.y = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (EMPTY_PIECE == gridArray[i][j])
            {
                gridArray[i][j] = AI_PIECE;
                int moveVal = minimax(gridArray, 0, false);
                gridArray[i][j] = EMPTY_PIECE;

                if (moveVal > bestVal)
                {
                    bestMove.x = i;
                    bestMove.y = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}