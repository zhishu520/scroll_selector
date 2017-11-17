#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ScrollSelector.h"
#include <vector>

using namespace std;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();


    vector<Node*> nodes;
    for(int i = 0;i < 5; i++){
        string name = StringUtils::format("res/%d.png", i+1);
        auto sprite = Sprite::create(name);
        nodes.push_back(sprite);
    }
    
    auto clipSize = Size(300,300);
    auto stencil = LayerColor::create(Color4B::RED, clipSize.width, clipSize.height);
    stencil->setPosition(Vec2(-clipSize.width/2, -clipSize.height/2));
    
    auto clipNode = ClippingNode::create(stencil);
    clipNode->setContentSize(clipSize);
    clipNode->setPosition(winSize/2);
    this->addChild(clipNode, 100);
    
    ScrollSelector* selector = ScrollSelector::create(nodes, 100.0f, 1.0f, 1.5f);
    selector->setContentSize(clipSize);
    clipNode->addChild(selector);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
