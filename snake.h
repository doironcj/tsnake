
#ifndef SNAKE
#define SNAKE
#include "coordinates.h"
#include "frame_buffer.h"

#include <list>

enum Direction {up=0,down=1,left=2,right=3};


class Snake {
/*each snake segment and token is a coordinate*/
std::list<Coordinates> segments;
Coordinates * tokens;
/*added segments will appear as the snake moves*/
int pending_segment = 0;
/*two direction variable insure that only one valid turn can be done per frame*/
/*any turn that is not opposite of the current direction is valid*/
Direction cur_dir = up;
Direction next_dir = up;
Frame_Buffer fb;
int height, width;
int token_number;

public:
    Snake(int length);
    void add_scale();
    void change_direction(Direction dir);
    void move();
    void print_score();
    int print_frame();/*returns 1 if snake is in bounnds and 0 otherwise*/
    
    
};
#endif