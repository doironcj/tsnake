#include"snake.h"
#include"terminal_control.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define CTRL_KEY(k) ((k) & 0x1f)
#define DEFAULT_FPS 16.0




Snake player(1);
pthread_mutex_t snake_direction_mtx;
bool exit_flag = false;
class frame_timer
{
    time_t start_time;
    time_t current_time;
    double time_between_frames;
    public:
    frame_timer(double frame_rate){
        time_between_frames = 1.0/frame_rate;
    }
    void start(){
    time(&start_time);
    }
    void wait_restart(){
        time(&current_time);
        double elapsed  = difftime(current_time,start_time);
        if(elapsed < time_between_frames)
        usleep((int)((time_between_frames - elapsed)*1000000));
        start();
    }

};

void * Snake_input_handler(void * s){
        char key;
    while(read(STDIN_FILENO,&key,1)){
pthread_mutex_lock (&snake_direction_mtx);
    switch(key){
        case 'w':
        player.change_direction(up);
        break;
        case 's':
        player.change_direction(down);
        break;
        case 'a':
        player.change_direction(left);
        break;
        case 'd':
        player.change_direction(right);
        break;
        case CTRL_KEY('q'):
        exit_flag = true;
    }
pthread_mutex_unlock (&snake_direction_mtx);
    }
    pthread_exit(NULL);
    }


int main( int argc, char ** argv){

    /*handle optional argument for fps*/
    double fps;
    if(argc > 1){
        fps = atof(argv[1]);
        if(fps <= 0){
            std::cerr << "Must provide a valid FPS value as an argument or leave no argument for the default of " << DEFAULT_FPS << std::endl;
            return 1;
        }
    }
    else
    {
       fps = DEFAULT_FPS;
    }
    
    frame_timer ftimer(fps);
    pthread_t input_handler;
    /*create thread for input */
    pthread_create(&input_handler,NULL,Snake_input_handler,NULL);
    /*create mutex for changing direction
    this will insure that if a key is registered it will be applied to 
    the change direction function before the snake moves*/
    pthread_mutex_init(&snake_direction_mtx,NULL);



enableRawMode();
ftimer.start();
while(player.print_frame() && !exit_flag){
    ftimer.wait_restart();/*this function waits for the timer to finish to return*/
    pthread_mutex_lock (&snake_direction_mtx);
    player.move();
    pthread_mutex_unlock (&snake_direction_mtx);
    
}


disableRawMode();
pthread_mutex_destroy(&snake_direction_mtx);
player.print_score();




return 0;
 }


