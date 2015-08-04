#ifndef TILEMAP_INCLUDE_H
#define TILEMAP_INCLUDE_H

/*
// depending on the size of the map, it has a different map type. it's treated differently
// by the level code. 
#define TILEMAP_LAYOUT_TYPE_UNKNOWN         0   // this would be an error.
#define TILEMAP_LAYOUT_FITS_IN_VRAM         1   // if the tilemap fits within the VDP's 8k for a background layer
#define TILEMAP_LAYOUT_STORED_VERTICALLY    2   // maps that are 64 tiles high are stored vertically. 
                                            // when scrolling left or right, a row is DMA'd into background layer memory.
*/

typedef struct
{
    unsigned short			width;
	unsigned short			height;
    //unsigned short          layoutType;
    const unsigned short*	tilemap;
} TileMap;

#endif
