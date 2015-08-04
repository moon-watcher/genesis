#include <genesis.h>

int x;
int y;
int oldx;
int oldy;

const u32 tile[8]=
  {
    0x00111100,
    0x01144110,
    0x11244211,
    0x11244211,
    0x11222211,
    0x11222211,
    0x01122110,
    0x00111100
  };


const u32 tile1[8]=
  {
    0x00000000,
    0x01111100,
    0x01222110,
    0x01200210,
    0x01200210,
    0x01200210,
    0x01100210,
    0x01100210
  };



void myJoyHandler( u16 joy, u16 changed, u16 state)
{
  if (joy == JOY_1)
    {
      if (state & BUTTON_UP)    { oldy=y; y=y-1; if (y<0) y=0; }
      if (state & BUTTON_DOWN)  { oldy=y; y=y+1; if (y<0) y=0; }
      if (state & BUTTON_LEFT)  { oldx=x; x=x-1; if (x<0) x=0; }
      if (state & BUTTON_RIGHT) { oldx=x; x=x+1; if (x<0) x=0; }

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
  oldx=0;
  oldy=0;

  VDP_loadTileData( (const u32 *)tile1, 1, 1, 0); 
  VDP_setTileMapXY(APLAN, 1, x+2, y+2);

  JOY_init();
  JOY_setEventHandler( &myJoyHandler );
  
  
  //VDP_drawText("Hello World!", x, y);
  
  while(1)
    {
      VDP_drawText("            ", oldx, oldy);
      VDP_drawText("Hello World!",    x,    y);
      VDP_setTileMapXY(APLAN, 1, x+2, y+2);
      VDP_waitVSync();
    }
  return (0);
}
