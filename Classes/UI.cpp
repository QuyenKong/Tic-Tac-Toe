//
//  UI.cpp
//  TicTacToePractise
//
//  Created by Sonar Systems on 22/03/2016.
//
//

#include "UI.h"
#include "c/SonarFrameworks.h"
#include "Definitions.h"
#include "GameScene.h"
#include "MainMenuScene.h"

UI::UI(cocos2d::Layer* layer, int& gameState)
{
    this->gameState = &gameState;

    Size screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    Button* pauseItem = Button::create(HOME_BUTTON_PRESSED, HOME_BUTTON_PRESSED);
    pauseItem->setPosition(Vec2(screenSize.width - (pauseItem->getContentSize().width / 2) + origin.x, screenSize.height - (pauseItem->getContentSize().height / 2) + origin.y));

    layer->addChild(pauseItem);

    pauseItem->addTouchEventListener(CC_CALLBACK_2(UI::touchEvent, this));
    pauseItem->setTag(TAG_MAIN_MENU_HOME_BUTTON);


}

void UI::ShowGameOver(cocos2d::Layer* layer)
{
    Size screenSize = Director::getInstance()->getVisibleSize();

    Sprite* background = Sprite::create(GAME_OVER_WINDOW);
    background->setPosition(Vec2(SonarCocosHelper::UI::GetScreenCenter().x,
        SonarCocosHelper::UI::GetScreenCenter().y + screenSize.height));
    background->setOpacity(255);
    layer->addChild(background);
    background->runAction(Sequence::create(
        DelayTime::create(2 ),
        MoveTo::create(0.5, SonarCocosHelper::UI::GetScreenCenter()), NULL));


    Button* retryItem = Button::create(RETRY_BUTTON, RETRY_BUTTON);
    retryItem->setPosition(Vec2(background->getContentSize().width *1.5/2, background->getContentSize().height / 2));
    background->addChild(retryItem);

    retryItem->addTouchEventListener(CC_CALLBACK_2(UI::touchEvent, this));
    retryItem->setTag(TAG_MAIN_MENU_HOME_BUTTON);


    Button* mainMenuItem = Button::create(HOME_BUTTON_PRESSED, HOME_BUTTON_PRESSED);
    mainMenuItem->setPosition(Vec2(background->getContentSize().width/4, background->getContentSize().height / 2));
    background->addChild(mainMenuItem);

    mainMenuItem->addTouchEventListener(CC_CALLBACK_2(UI::touchEvent, this));
    mainMenuItem->setTag(TAG_MAIN_MENU_HOME_BUTTON);

}

void UI::Retry(cocos2d::Ref* pSender)
{
    Scene* scene = GameScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

    Director::getInstance()->replaceScene(transition);
}

void UI::GoToMainMenu(cocos2d::Ref* pSender)
{
    Scene* scene = MainMenuScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

    Director::getInstance()->replaceScene(transition);
}

void UI::PauseGame(cocos2d::Ref* pSender)
{
    Size screenSize = Director::getInstance()->getVisibleSize();

    if (STATE_PLAYING == *gameState)
    {
        *gameState = STATE_PAUSED;
        pausebackground->runAction(FadeIn::create(PAUSE_BACKGROUND_FADE_TIME));

        EaseBounceOut* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION,
            SonarCocosHelper::UI::GetScreenCenter()));
        pauseMenu->runAction(menuActionEasing);
    }
    else if (STATE_PAUSED == *gameState)
    {
        *gameState = STATE_PLAYING;
        pausebackground->runAction(FadeOut::create(PAUSE_BACKGROUND_FADE_TIME));

        EaseBounceOut* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION,
            Vec2(SonarCocosHelper::UI::GetScreenCenter().x, SonarCocosHelper::UI::GetScreenCenter().y + screenSize.height)));
        pauseMenu->runAction(menuActionEasing);
    }
}

void UI::touchEvent(Ref* sender, Widget::TouchEventType type) {
    Node* node = (Node*)sender;
    switch (type) {
    case Widget::TouchEventType::BEGAN:

        break;
    case Widget::TouchEventType::CANCELED:

        break;
    case Widget::TouchEventType::ENDED:
        if (TAG_MAIN_MENU_HOME_BUTTON == node->getTag())
        {
            Scene* scene = MainMenuScene::createScene();
            TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

            Director::getInstance()->replaceScene(transition);
            break;
        }
        else if (TAG_MAIN_MENU_RETRY_BUTTON == node->getTag())
        {
            Scene* scene = GameScene::createScene();
            TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

            Director::getInstance()->replaceScene(transition);
        }
        break;
    case Widget::TouchEventType::MOVED:

        break;
    default:
        break;
    }
}