#ifndef __SCROLL_SELECTOR_H__
#define __SCROLL_SELECTOR_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>

class ScrollSelector: public cocos2d::Layer
{
public:

    static ScrollSelector* create(std::vector<cocos2d::Node*> nodes, float distance, float minScale = 1.0f, float maxScale = 1.2f);

    void ScrollTo(int index, float delay);
private:
    std::vector<cocos2d::Node*> m_nodes;
    float minScale;
    float maxScale;
    float spaceDistance;

    virtual bool init();
    void initView();
    void initListener();
    void update(float dt);

    int m_iCurrentIndex;

    CREATE_FUNC(ScrollSelector);
};

#endif // __HELLOWORLD_SCENE_H__
