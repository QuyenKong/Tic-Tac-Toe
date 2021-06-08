#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "AI2.h"
#include "UI.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);


    bool lastMoveWon(int row, int column, int piece);


private:
    cocos2d::Rect gridSpaces[3][3];
    cocos2d::Sprite* gridPieces[3][3];
    cocos2d::Sprite* gridSprite;

    int gridArray[3][3];

    int turn;
    int gameState;


    void InitGridRects();
    void InitGridPieces();

    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    UI* ui;
};
#endif // __GAME_SCENE_H__