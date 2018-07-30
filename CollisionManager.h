#ifndef _CollisionManager_
#define _CollisionManager_

#include "GameObject.h"

class CollisionManager {

public:
    //returns / creates singleton instance
    static CollisionManager* Instance();

    //returns true if two rectangles are colliding
    bool isCollidingRectRect(GameObject* rectA, GameObject* rectB, int buffer);

    //returns true if parameter rectangle is colliding with circle
    bool isCollidingRectCircle(GameObject* circle, GameObject* rect);

    //returns true if two circles are colliding
    bool isCollidingCircleCircle(GameObject* circleA, GameObject* circleB);

    //returns true if circle is colliding with single coordinate point
    bool isCollidingCirclePoint(GameObject* circleA, Vector2D* pointPosition);

    //should value passed in be outside the upper/lower range it is clamped to this value
    double clamp(double value, double upper, double lower);
    
private:
    static CollisionManager* s_pInstance;
};

typedef CollisionManager TheCollManager;

#endif
