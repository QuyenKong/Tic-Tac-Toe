
#pragma once
#include "cocos2d.h"

USING_NS_CC;
#include "extensions/cocos-ext.h" 
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
using namespace ui;

class UI
{
public:
    UI(cocos2d::Layer* layer, int& gameState);

    void ShowGameOver(cocos2d::Layer* layer);

private:
    void Retry(cocos2d::Ref* pSender);
    void GoToMainMenu(cocos2d::Ref* pSender);
    void PauseGame(cocos2d::Ref* pSender);
    void touchEvent(Ref* sender, Widget::TouchEventType type);
    int* gameState;

    cocos2d::Menu* pauseMenu;
    cocos2d::Sprite* pausebackground;
};