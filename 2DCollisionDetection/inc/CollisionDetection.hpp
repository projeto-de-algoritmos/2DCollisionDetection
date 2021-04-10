#ifndef _COLLISION_DETECTION_HPP_
#define _COLLISION_DETECTION_HPP_

#include "Ball.hpp"

#include <cstdint>
#include <vector>

class Rectangle{
    private:
    public:
}

class QuadTree{
    private:
        int MAX_OBJECTS = 40;
        int MAX_LEVELS = 3;
        int level;
        vector<Ball *> balls;
        Rectangle bounds;

        QuadTree nodes[4];

    void clear(){
        balls.clear();
        for(int i = 0; i < 4; ++i){
            if(nodes[i] != NULL){
                nodes[i].clear();
                nodes[i] = NULL;
            }
        }
    }

    void split(){
        int subWith = (int)bounds.getWidth()/2;
        int subHeight = (int)bounds.getHeight()/2;

        int x = (int)bounds.getX();
        int y = (int)bounds.getY();

        nodes[0] = new QuadTree(level + 1, new Rectangle(
    }

    public:

        QuadTree(int plevel, Rectangle pbounds){
            level = plevel;
            bounds = pbounds;
        }

}

namespace ColDetect
{
    void EfficientCollisionDetection(const std::vector<Ball *> & balls, int32_t table_width, int32_t table_height);
    void NaiveCollisionDetection(const std::vector<Ball *> & balls);
}

#endif
