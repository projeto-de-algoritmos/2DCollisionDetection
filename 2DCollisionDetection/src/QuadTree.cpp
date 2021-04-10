#include "Ball.h"
#include <vector>

class Point{
    private:
    pair<int, int> data;
    public:

    Point(int x, int y);
    int getX();
    int getY();
        
}

Point::Point(int x, int y){
    data.first = x;
    data.second = y;
}

int Point::getX(){
    return data.first;
}

int Point::getY(){
    return data.second;
}

class Rectangle{
    private:

    pair<int, int> bottom;
    pair<int, int> upper;

    public:

    Rectangle(int xb, int yb, int xt, int yt);

    int getX();
    int getY();

    int getHeight();
    int getWidth();

    bool contains(Point p);

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
    return upper.first - upper.first;
}

bool Rectangle::contains(Point p){

    if(p.fist < borders.


}

class QuadTree{
    private: 

    int MAX_OBJECTS = 10;
    int MAX_LEVELS = 5;

    int level;
    Rectangle bounds;

    vector<Point> objs;

    QuadTree* nodes[4];

    void split();

    public:

    QuadTree(int level, vector<Point> balls);
    void getIndex(Point p);
    void clear();

};

int QuadTree::getIndex(Point p){

    for(int i = 0; i<4; ++i)
        if(nodes[i].bounds.contains(p))
            return i;

    return -1;

}

void QuadTree::split(){
    int subWidth = (int)bounds.getWidth()/2; 
    int subHeight = (int)bounds.getHeight()/2; 

    int x = (int) bounds.getX();
    int y = (int) bounds.getY();

    nodes[0] = new QuadTree(level + 1, Rectangle(x + subWidth, y + subHeight, subWidth, subHeight));
    nodes[1] = new QuadTree(level + 1, Rectangle(x, y + subHeight, subWidth, subHeight));
    nodes[2] = new QuadTree(level + 1, Rectangle(x, y, subWidth, subHeight));
    nodes[3] = new QuadTree(level + 1, Rectangle(x + subWidth, y, subWidth, subHeight));
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

QuadTree::QuadTree(int level, Rectangle bounds){
    level = level;
    bounds = bounds;

    for(int i = 0; i < 4; ++i)
        nodes[i] = NULL;
}
