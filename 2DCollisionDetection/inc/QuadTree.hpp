#ifndef _QUADTREE_HPP_
#define _QUADTREE_HPP_

#include <vector>
#include <utility>

#include "Ball.hpp"

class Rectangle{
    private:

    std::pair<int, int> bottom;
    std::pair<int, int> upper;

    public:

    Rectangle(int xb, int yb, int xt, int yt);
    Rectangle();

    int getX();
    int getY();

    int getHeight();
    int getWidth();

    bool contains(Ball* p);

};

class QuadTree{
    private: 

    int MAX_OBJECTS = 4;
    int MAX_LEVELS = 2;

    int level;
    Rectangle bounds;

    std::vector<Ball*> objs;

    QuadTree* nodes[4];

    void split();

    public:

    std::vector<Ball*> getObjects();
    std::vector<Ball*> retrieve(Ball* p);

    QuadTree(int level, Rectangle bounds);
    int getIndex(Ball* p);
    void clear();

    void insert(Ball* p);
    Rectangle getBoundary();


};

#endif
