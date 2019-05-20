/* Copyright
 * Created by Juan De Filippis
 * Spring Semester 2019 CSCE 212
 */
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned int 	uint32;

#define MEM_IO 			0x04000000
#define VRAM			0x06000000

#define VIDEOMODE		0x0003
#define BGMODE			0x0400

#define REG_DISPLAY			(*(volatile uint32 *) (MEM_IO))
#define REG_DISPLAY_VCOUNT	(*(volatile uint32 *) (MEM_IO + 0x0006))
#define REG_KEY_INPUT		(*(volatile uint32 *) (MEM_IO + 0x0130))

// bits out of input memory address
#define A			1
#define B			2
#define SELECT		4
#define START		8
#define RIGHT		16
#define LEFT		32
#define UP			64
#define DOWN		128
#define R			256
#define L 			512

// intermediary values :(
#define DIR_UP		0
#define DIR_RIGHT	1
#define DIR_DOWN	2
#define DIR_LEFT	3

#define MAX_LENGTH 	30
#define tileSize 8

#define SCREENBUFFER	((volatile uint16 *) VRAM)

int lastSegment = 1;

// length and direction
uint16 length;
uint16 direction;
struct Rect {
	uint32 x, y;
	uint32 w, h;
} 	segments[MAX_LENGTH], food;
