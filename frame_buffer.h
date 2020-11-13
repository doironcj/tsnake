
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include "coordinates.h"
#include <deque>

class Frame_Buffer{
    int width;
    int height;
    bool * frame_buffer;
  
    /*have size pre-computed to avoid calculating on every clear*/
    int size;
    public:
    Frame_Buffer();
    void get_Frame(int*, int*);
    void print_buffer();
    void clear_buffer();
    /*returns integer to wether the snake is a valid position or not*/
    int draw(std::deque<Coordinates>);
    int draw(Coordinates *,int);
};
#endif