#include "ScrollSelector.h"


using namespace std;
USING_NS_CC;


ScrollSelector* ScrollSelector::create(vector<Node*> nodes, float distance, float minScale /*= 1.0f*/, float maxScale /*= 1.2f*/)
{
    auto ret = ScrollSelector::create();
    ret->nodes = nodes;
    ret->spaceDistance = distance;
    ret->minScale = minScale;
    ret->maxScale = maxScale;
    ret->initView();
    ret->scheduleUpdate();
    return ret;
}


void ScrollSelector::initView()
{
    this->setAnchorPoint(Vec2(0.5f, 0.5f));

    unsigned long cnt = this->nodes.size();
    for(int i = 0; i< cnt; i++){
        if(this->nodes[i] != NULL){
            this->nodes[i]->setPosition(Vec2(i * spaceDistance, 0));// TODO
            this->addChild(this->nodes[i]);
        }
    }

    this->initListener();
    this->ScrollTo(0, 0);
}


void ScrollSelector::ScrollTo(int index, float delay){
    if(index < 0 || index >= this->nodes.size())
        return;

    Size contentSize = this->getContentSize();

    float distance = contentSize.width/2 - this->nodes[index]->getPositionX();
    for(auto i : this->nodes)
        i->runAction(MoveBy::create(delay, Vec2(distance, 0)));
}


bool ScrollSelector::init()
{
    return true;
}

void ScrollSelector::initListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event) {

        for(auto i : this->nodes) {
            Vec2 point = convertToNodeSpace(touch->getLocation());
            if( i->getBoundingBox().containsPoint(point)) {
                return true;
            }
        }

        return false;
    };

    listener->onTouchMoved = [this](Touch* touch, Event* event) {
        float disX = touch->getDelta().x;
        for(auto i : this->nodes)
            i->setPositionX(i->getPositionX() + disX);
    };

    listener->onTouchEnded = [this](Touch* touch, Event* event) {

        float startDistance = touch->getLocation().distance(touch->getStartLocation());

        bool clickFlag = false;
        int cnt = 0;

        if(startDistance < 10) // click
        {
            float minDis = 0.0f;

            for(auto i : this->nodes) {
                Vec2 point = convertToNodeSpace(touch->getLocation());
                if( i->getBoundingBox().containsPoint(point)) {
                    minDis = - i->getPositionX();
                    clickFlag = true;
                    currentIndex = cnt;
                    break;
                }
                cnt ++;
            }

            if(clickFlag)
                for(auto i : this->nodes)
                    i->runAction(MoveBy::create(0.3f, Vec2(minDis, 0)));
        }

        if(!clickFlag) {
            float minDis = 0;
            if(! this->nodes.empty())
                minDis =  - this->nodes[0]->getPositionX();

            currentIndex = 0;
            cnt = 0;
            for(auto i : this->nodes) {
                if(abs( - i->getPositionX()) < abs(minDis)) {
                    minDis =  - i->getPositionX();
                    currentIndex = cnt;
                }
                cnt ++;
            }

            for(auto i : this->nodes)
                i->runAction(MoveBy::create(0.3f, Vec2(minDis, 0)));
        }

    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ScrollSelector::update(float dt)
{
    for(auto i : this->nodes) {
        float distance = abs(i->getPositionX());

        float scale = maxScale - (maxScale - minScale) * distance / spaceDistance;
        if(scale < minScale)
            scale = minScale;
        i->setScale(scale);
    }
}



