/* Copyright
 * Created by Juan De Filippis
 * Spring Semester 2019 CSCE 212
 */
#include "snake.h"
void sync()
{
	while(REG_DISPLAY_VCOUNT >= 160);
	while(REG_DISPLAY_VCOUNT < 160);
}

uint16 makeColor(uint8 r, uint8 g, uint8 b)
{
	return (r & 0x1f) | ((g & 0x1f) << 5) | ((b & 0x1f) << 10);
}

uint32 clamp(int value, int min, int max)
{
	return (value < min ? min : (value > max ? max : value));
}

void drawRect(struct Rect rect, uint16 color)
{
	for(int y = 0; y < rect.h; y++)
	{
		for(int x = 0; x < rect.w; x++)
		{
			SCREENBUFFER[(rect.y + y) * SCREEN_WIDTH + rect.x + x] = color;
		}
	}
}

void moveSnake()
{
	for (int i = length - 1; i > 0; i--)
	{
		segments[i].x = segments[i - 1].x;
		segments[i].y = segments[i - 1].y;
	}
	int horizSpeed, vertSpeed;

	if (direction == DOWN)
	{
		horizSpeed = 0;
		vertSpeed = 1;
	}
	else if (direction == UP)
	{
		horizSpeed = 0;
		vertSpeed = -1;
	}
	else if (direction == RIGHT)
	{
		horizSpeed = 1;
		vertSpeed = 0;
	}
	else if (direction == LEFT)
	{
		horizSpeed = -1;
		vertSpeed = 0;
	}
	
	// where the last segment is going on the snake.
	segments[0].x = segments[1].x + horizSpeed * tileSize;
	segments[0].y = segments[1].y + vertSpeed * tileSize;
	segments[0].w = segments[0].h = tileSize - 2;
}

void createSegment()
{
	length++;
	segments[length - 1].x = segments[length - 2].x;
	segments[length - 1].y = segments[length - 2].y;
	segments[length - 1].w = segments[length - 1].h = tileSize - 2;
}

void createFood()
{
	if ((segments[0].x == food.x) & (segments[0].y == food.y))
	{   /* deletes the last location of the food
         * randomized food location
         */
		createSegment();
		drawRect(food, 0);
		food.x = (rand() % (SCREEN_WIDTH / tileSize)) * tileSize + 1;
		food.y = (rand() % (SCREEN_HEIGHT / tileSize)) * tileSize + 1;
		drawRect(food, 31);
	}
}

void reset()
{
	/* Generates apples then
     * plus tile size to move over 1
     * draw apple
     */
	drawRect(food, 0);
	direction = RIGHT;
	length = 2;
	int startX = (SCREEN_WIDTH / tileSize) / 2;
	int startY = (SCREEN_HEIGHT / tileSize) / 2;
	food.x = food.y = 1;
	food.w = food.h = tileSize - 2;
	segments[0].x = startX * tileSize + 1;
	segments[0].y = startY * tileSize + 1;
	segments[0].w = segments[0].h = segments[1].w = segments[1].h = tileSize - 2;
	segments[0].x = segments[0].x + tileSize;
	segments[1].y = segments[0].y;
	drawRect(food, 31);
}

void setCollisions()
{
	if (((segments[0].x == 1 && direction == LEFT) || (segments[0].x == (SCREEN_WIDTH - tileSize) + 1 && direction == RIGHT)) 
		|| ((segments[0].y == 1 && direction == UP)|| (segments[0].y == (SCREEN_HEIGHT - tileSize) + 1 && direction == DOWN)))
	{
    
		for (int i = 0; i < length; i++)
		{
			drawRect(segments[i], 0);  // la mow
		}
		// Call reset method
		reset();
	}
	for (int i = 1; i < length; i++)
	{
		if (segments[0].x == segments[i].x && segments[0].y == segments[i].y)
		{
			for (int i = 0; i < length; i++)
			{
				drawRect(segments[i], 0);
			}
			reset();
			break;
		}
	}
}

int main()
{
	REG_DISPLAY = VIDEOMODE | BGMODE;
	
	int frameCounter = 0;
	
	int score = 0;
	
	reset();

	// Game Loop
	while(1)
	{
		// draw the first segment
		drawRect(segments[0], makeColor(0, 0x1f, 0));
		sync();
		
		if(!((REG_KEY_INPUT) & DOWN))
		{
			if(direction != UP)
			{
				direction = DOWN;
			}
		}
		if(!((REG_KEY_INPUT) & UP))
		{
			if(direction != DOWN)
			{
				direction = UP;
			}
		}
		if(!((REG_KEY_INPUT) & RIGHT))
		{
			if(direction != LEFT)
			{
				direction = RIGHT;
			}
		}
		if(!((REG_KEY_INPUT) & LEFT))
		{
			if(direction != RIGHT)
			{
				direction = LEFT;	
			}
		}
        if(frameCounter % 10 == 0)
		{
			// BEGIN EXTRA CREDIT
			if (!((REG_KEY_INPUT) & START))
			{
				// press start for the pause menue
				for (int i = 0; i < 10; i++)
					sync();
				while (true)
					if (!((REG_KEY_INPUT) & START))
						break;
			}
            // called of the function setCollisions (extracredit)
			setCollisions();
            frameCounter = 0;
			int i;
			
			// -1 to delete last segment
            drawRect(segments[length - 1], makeColor(0,0,0));
			moveSnake();
			
			createFood();
        }
		frameCounter++;
	}
	return 0;
}
