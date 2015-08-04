#include <genesis.h>

int x;
int y;

void myJoyHandler( u16 joy, u16 changed, u16 state)
{
  if (joy == JOY_1)
    {
      if (state & BUTTON_UP)    { y=y-2; if (y<0) y=0; }
      if (state & BUTTON_DOWN)  { y=y+2; if (y<0) y=0; }
      if (state & BUTTON_LEFT)  { x=x-2; if (x<0) x=0; }
      if (state & BUTTON_RIGHT) { x=x+2; if (x<0) x=0; }

      else if (changed & BUTTON_START)
        {
	  //player 1 released START button    
        }
    }   
}


int main()
{
  x=0;
  y=0;

  JOY_init();
  JOY_setEventHandler( &myJoyHandler );
  
  
  //VDP_drawText("Hello World!", x, y);
  
  while(1)
    {
      VDP_drawText("Hello World!", x, y);
      VDP_waitVSync();
    }
  return (0);
}
