
#include "snake.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>




Snake::Snake(int length){
        
        fb.get_Frame(&height,&width);
        Coordinates new_c = Coordinates(width/2,height/2);
        segments.push_back(new_c);
        pending_segment = length -1;
        token_number = 1+ height*width/40; /*the token number should be proportional to the size of the window of snake grid*/
        tokens = new Coordinates[token_number];
        srand(time(NULL));
        for(int i = 0 ; i < token_number; i++){
            tokens[i].x = rand() %width;
            tokens[i].y = rand() %height;
        }
        
       
        
    }
    void Snake::add_scale(){
        pending_segment++;
    }
    void Snake::change_direction(Direction dir){
        /* make sure the direction is valid 
        the snake cannot move in the opposite direction*/
      switch(dir){
          case up:
          case down:
            if(cur_dir > 1){
                next_dir = dir;
            }
          break;
          case left:
          case right:
            if(cur_dir < 2){
                next_dir = dir;
            }
      }
        
    }
    void Snake::move(){
        /*push to the front and pop back if there is not pending scale*/
        
        switch(next_dir){
            case up:
                segments.push_front(Coordinates(segments.front().x,segments.front().y-1));
                break;
            case down:
                segments.push_front(Coordinates(segments.front().x,segments.front().y+1));
                break;
            case left:
                segments.push_front(Coordinates(segments.front().x-1,segments.front().y));
                break;
            case right:
                segments.push_front(Coordinates(segments.front().x+1,segments.front().y));
                break;
        }
        cur_dir = next_dir;
        if(pending_segment == 0){
            segments.pop_back();
        }
        else{
            pending_segment--;
        }
        /*after every move the head should be tested to see if a token has been eaten*/
        for( int i = 0; i < token_number; i++){
            Coordinates head = segments.front();
            if( tokens[i].x == head.x && tokens[i].y == head.y ){
            tokens[i].x = rand() %width;
            tokens[i].y = rand() %height;    
            pending_segment++;
            }    


        }
        
    }

    
    void Snake::print_score(){
            std::cout << "your score is: " << segments.size()-1<< std::endl << std::flush;
    }
    
    int Snake::print_frame(){
       
        fb.clear_buffer();
        if(fb.draw(segments)){
        fb.draw(tokens,token_number);
        fb.print_buffer();

        return 1;


        }
        else{
        std::cout<< std::endl;
        return 0;

        } 
    }

    