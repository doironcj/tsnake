#ifndef COORDINATES_H
#define COORDINATES_H
class Coordinates{

public:
int x;
int y;
Coordinates (){
    this->x = 0;
    this->y = 0;
}
Coordinates (int x, int y){
    this->x = x;
    this->y = y;
}
};
#endif