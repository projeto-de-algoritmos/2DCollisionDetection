#include <vector>
#include <utility>

//TODO(felipe) remove this later
#include <iostream>

//Point class wrapps Ball

class Point{
    private:
    std::pair<int, int> data;
    public:

    Point(int x, int y);
    int getX();
    int getY();
        
};

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

//QuadTree boundary
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

    bool contains(Point p);

};

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

bool Rectangle::contains(Point p){


    bool x_interval = false;
    bool y_interval = false;

    if(bottom.first <= p.getX() and p.getX() <= upper.first)
        x_interval = true;

    if(bottom.second <= p.getY() and p.getY() <= upper.second)
        y_interval = true;

    return x_interval and y_interval;

}

class QuadTree{
    private: 

    int MAX_OBJECTS = 4;
    int MAX_LEVELS = 2;

    int level;
    Rectangle bounds;

    std::vector<Point> objs;

    QuadTree* nodes[4];

    void split();

    public:

    std::vector<Point> getObjects();
    std::vector<Point> retrieve(Point p);

    QuadTree(int level, Rectangle bounds);
    int getIndex(Point p);
    void clear();

    void insert(Point p);
    Rectangle getBoundary();


};

Rectangle QuadTree::getBoundary(){
    return bounds;
}

std::vector<Point> QuadTree::getObjects(){
    return objs;
}

void QuadTree::insert(Point p){

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


int QuadTree::getIndex(Point p){


    for(int i = 0; i<4; ++i)
        if(nodes[i]!= NULL && nodes[i]->bounds.contains(p))
            return i;

    return -1;

}

std::vector<Point> QuadTree::retrieve(Point p){

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

int main(){
    auto tree = QuadTree(1, Rectangle(0, 0, 600, 600));

    tree.insert(Point(2, 2));
    tree.insert(Point(2, 3));
    tree.insert(Point(2, 4));
    tree.insert(Point(0, 350));


    for(auto each : tree.retrieve(Point(0, 400)))
        std::cout << "->" << each.getX() << " " << each.getY() << std::endl;

    return 0;
}
