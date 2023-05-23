#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <cmath>
#include <grx20.h>
#include <grxkeys.h>
#include <windows.h>

#define N 6
#define GATE 150

#define WHITE 15
#define BLACK 0
#define GREEN 10
#define RED 12
#define GRAVITY 4
#define JUMP 12
#define WALL_SPEED 2
#define SHIFT 250

class Wall
{
public:
	float x;
	float y;
	float width;
	float height;
	int color;
	Wall(float fx, float fy, float fwidth, float fheight, u_short icolor)
	{
		x = fx;
		y = fy;
		width = fwidth;
		height = fheight;
		color = icolor;
	}
	Wall()
	{
		x = GrMaxX() / 2 - 100;
		y = -1000;
		width = 100;
		height = 1500;
		color = WHITE;
	}
	~Wall()
	{
	}
	void draw()
	{
		GrFilledBox(x, y, x + width, y + height, WHITE);
	}
	void move()
	{
		x -= WALL_SPEED;
	}
};

class Bird
{
public:
	float x;
	float y;
	float r;
	int color;
	Bird(float fx, float fy, float fr, int icolor)
	{
		x = fx;
		y = fy;
		r = fr;
		color = icolor;
	}
	~Bird()
	{
	}
	void draw()
	{
		GrFilledCircle(x, y, r, color);
	}
	void jump()
	{
		y -= JUMP;
	}
	bool check_collision(Wall *wall)
	{
		float distX = std::abs(x - wall->x - wall->width / 2);
		float distY = std::abs(y - wall->y - wall->height / 2);

		if (distX > (wall->width / 2 + r))
		{
			return false;
		}
		if (distY > (wall->height / 2 + r))
		{
			return false;
		}
		if (distX <= (wall->width / 2))
		{
			return true;
		}
		if (distY <= (wall->height / 2))
		{
			return true;
		}
	}
	void panic(bool check)
	{
		if (!check)
			color = GREEN;
		else
			color = RED;
	}
};

int main()
{
	GrSetMode(GR_biggest_graphics);
	// GrSetMode(GR_default_graphics);

	Wall obj[N];
	Bird bird = Bird(GrMaxX() / 3, GrMaxY() / 2, 20, GREEN);
	bird.draw();
	srand(time(0));
	int i;

	for (i = 0; i < N; i += 2)
	{
		obj[i].x += SHIFT * i;
		obj[i].draw();

		obj[i + 1].x += SHIFT * i;
		obj[i + 1].y += obj[i].height + GATE;
		obj[i + 1].draw();
	}

	bool gameOver = false;
	short escape_key, up_arrow, space;
	// TODO: респавнить стену если уехала за экран
	while (true)
	{
		GrSleep(16);
		GrClearScreen(BLACK);
		escape_key = GetAsyncKeyState(GrKey_Escape);
		up_arrow = GetAsyncKeyState(GrKey_Up);
		space = GetAsyncKeyState(GrKey_Space);
		if (escape_key || gameOver)
			exit(0);

		if (space)
			bird.jump();
		else
			bird.y += GRAVITY;

		for (i = 0; i < N; i++)
		{
			obj[i].move();
			obj[i].draw();
			if (bird.check_collision(&obj[i]))
			{
				bird.panic(true);
				bird.draw();
				GrTextXY(GrMaxX() / 2, GrMaxY() / 2, "Game Over", RED, BLACK);

				GrSleep(2000);
				exit(0);
			}
		}
		for (i = 0; i < N; i += 2)
		{
			if (obj[i].x < 0)
			{
				obj[i].x = GrMaxX();
				obj[i + 1].x = GrMaxX();
				obj[i].y += rand() % 300 - 150;
				obj[i + 1].y = obj[i].y + GATE + obj[i].height;
			}
		}
		bird.draw();
	}
	return 0;
}