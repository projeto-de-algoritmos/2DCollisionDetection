#include <vector>
#include <utility>

#include "Ball.hpp"
#include "QuadTree.hpp"

Rectangle::Rectangle(){
}

Rectangle::Rectangle(int xb, int yb, int xt, int yt){
    bottom = std::make_pair(xb, yb);
    upper = std::make_pair(xb + xt, yb + yt);
}

int Rectangle::getX(){
    return bottom.first;
}

int Rectangle::getY(){
    return bottom.second;
}

int Rectangle::getHeight(){
    return upper.second - bottom.second;
}

int Rectangle::getWidth(){
    return upper.first - bottom.first;
}

bool Rectangle::contains(Ball* p){


    bool x_interval = false;
    bool y_interval = false;

    if(bottom.first <= p->getXCoordinate() and p->getXCoordinate() <= upper.first)
        x_interval = true;

    if(bottom.second <= p->getYCoordinate() and p->getYCoordinate() <= upper.second)
        y_interval = true;

    return x_interval and y_interval;

}

Rectangle QuadTree::getBoundary(){
    return bounds;
}

std::vector<Ball*> QuadTree::getObjects(){
    return objs;
}

void QuadTree::insert(Ball* p){

    objs.push_back(p);

    // create child nodes
    if(nodes[0] == NULL and level <= MAX_LEVELS)
        split();


    for(int quadrant = 0; quadrant < 4; ++quadrant){
        if(nodes[quadrant] != NULL && nodes[quadrant]->getBoundary().contains(p)){
            nodes[quadrant]->insert(p);
        }
    }

}

QuadTree::QuadTree(int blevel, Rectangle b){
    level = blevel;
    bounds = b;

    for(int quadrant = 0; quadrant < 4; ++quadrant)
        nodes[quadrant] = NULL;
}


int QuadTree::getIndex(Ball* p){


    for(int i = 0; i<4; ++i)
        if(nodes[i]!= NULL && nodes[i]->bounds.contains(p))
            return i;

    return -1;

}

std::vector<Ball*> QuadTree::retrieve(Ball* p){

    for(int quadrant = 0; quadrant < 4; ++quadrant){
        if(nodes[quadrant] != NULL && nodes[quadrant]->bounds.contains(p)){
            return nodes[quadrant]->retrieve(p);
        }
    }

    return objs;

}

void QuadTree::split(){
    int subWidth = (int)bounds.getWidth()/2; 
    int subHeight = (int)bounds.getHeight()/2; 

    int x = (int) bounds.getX();
    int y = (int) bounds.getY();


    nodes[0] = new QuadTree(level + 1, Rectangle(x + subWidth, y + subHeight, x + subWidth, y+subHeight));
    nodes[1] = new QuadTree(level + 1, Rectangle(x, y + subHeight, x+subWidth, y+subHeight));
    nodes[2] = new QuadTree(level + 1, Rectangle(x, y, x+subWidth, y+subHeight));
    nodes[3] = new QuadTree(level + 1, Rectangle(x + subWidth, y, x+subWidth, y+subHeight));
}

void QuadTree::clear(){

    objs.clear();

    for(int i = 0; i< 4; ++i){
        if(nodes[i] != NULL){
            nodes[i]->clear();
            nodes[i] = NULL;
        }
    }
}

