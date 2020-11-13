#include "frame_buffer.h"
#include "terminal_control.h"
#include <algorithm>
#include <iostream>
#include <unistd.h>
#define FULL "\u2588"
#define UHALF "\u2580"
#define LHALF "\u2584"

Frame_Buffer::Frame_Buffer(){
    if(window_size(&height,&width) != 0){/*safe default sizes if window size was unsuccessful*/ 
        height  = 25;
        width  = 50;
    }
    
    size = height*2*width;
    frame_buffer = new bool[size];

    clear_buffer();
}
void Frame_Buffer::get_Frame(int * height, int * width){
    *height  = this->height * 2;/*each line is 2 grids high*/
    *width   = this->width;

}
void Frame_Buffer::clear_buffer(){
    for( int i = 0; i < size; i++)
    frame_buffer[i] = false;
}
/*print buffer*/
void Frame_Buffer::print_buffer(){
    /*first line will be the printed score*/
    /*every line is equal to two grids on the snake feild*/
    reposition_cursor();
    for( int line = 0 ; line < height; ++line){
        for( int col = 0; col < width; col++){
            int y = line*2;
            int y2 = line*2 +1;
            bool pixel_upper = frame_buffer[y*width + col];
            bool pixel_lower = frame_buffer[y2*width + col];
            
            if(pixel_upper || pixel_lower){
                if(pixel_upper && !pixel_lower){
                    std::cout << LHALF;
                }
                else if(pixel_lower && !pixel_upper){
                    std::cout << UHALF;
                }
                else
                    std::cout << ' ';
                }
                else{
                    std::cout << FULL;
                }
    }
    if( line != height - 1 )
    std::cout << std::endl;

    
    
}
std::cout << std::flush;
}

/*draw coordinates to buffer
the draw function returns 0 if a set of coordinates was drawn to twice or 
they are out of bounds to allow for collision detection*/

int Frame_Buffer::draw(std::deque<Coordinates> coords){

int no_collision = 1;
for( Coordinates c : coords){
    if(c.y < height*2 && c.x < width && c.y >= 0 && c.x >= 0){
    int index = c.y*width + c.x;

    if(frame_buffer[index])
    no_collision = 0;

    frame_buffer[index] = true;
    
    
    }
    else{
        /*coordinates are out of bounds */
        return 0;
    }
}
 return no_collision;

}

int Frame_Buffer::draw(Coordinates * coords, int length){
    for( int i  = 0 ; i < length; i++){
        if(coords[i].y < height*2 && coords[i].x < width && coords[i].y >= 0 && coords[i].x >= 0){
        int index = coords[i].y*width + coords[i].x;
        frame_buffer[index] = true;
        }
        else
        {
            return 0;
        }
        
        
    }
    return 1;

}