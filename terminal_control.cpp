

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
/*raw mode sends all key presses without waiting untill enter is selected 
canoninical or ( ICANON ) is the flag we turn off to enter raw mode
ECHO is turned off to stop the keypresses from showing on the screen
ISIG stops cntrl c and cnrl z from sending interrupt and stop signals
IXON stops cntrl s from stoping all input*/
/*using VT100 escape sequences*/

static struct termios orig_termios;
void reposition_cursor(){
    
    /*escape sequence for placing cursor at upper left hand corner*/
    
    write(STDOUT_FILENO, "\x1b[H",3);
    


}

void disableRawMode() {
  
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
/* make the cursor visible again*/
 write(STDOUT_FILENO,"\x1b[?25h",6);
 

}
void enableRawMode() {
   tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(IXON);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
  /*hide the cursor and clear screen*/
 reposition_cursor();
 /*this will reposition the cursor to overwrite the current frame*/
  write(STDOUT_FILENO,"\x1b[?25l",6);
}
/* this may not work for all terminal interfaces*/
int window_size(int * rows, int *cols){
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}


/* sets the cursor to the upper left hand corner and clears the terminal screen*/
