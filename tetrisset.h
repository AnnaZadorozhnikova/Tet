#ifndef TETRISSET_H
#define TETRISSET_H
#include <string>

 // namespace for constant settings of game
namespace constants
{
	const int fieldhigh = 15; // high in blocks
	const int fieldwidth = 10; //width in blocks
	const int sizeofpixelcube = 15; //size of tetromino block in pixels
	const int coordsize = 2;
	const std::string texturepath = "texturetetris.jpg";
	const std::string backgroundpath = "Backtext.jpg";
}

int field[constants::fieldhigh][constants::fieldwidth] = { 0 };

namespace timer
{
	float timer = 0;
	float delayoftime = 0.5f; //normal value of the delay
}

namespace gameset
{
	int horisontal = 0; //int for changing direction to the left/right
	bool rotation = false; //current value if rotation button is pressed
	int colorNum = 1;  //there are 8 possible random colors for tetromino
	bool Gamestart = true; //use only onse in the beginning of the game
	int n = rand() % 7;
}

//in coordinate sistem 2*4 each tetromino has values of blocks:
int tetrisfigure[7][4] =
{
	2,3,4,5, // tetromino O
	2,3,5,7, // tetromino L
	1,3,5,7, // tetromino I
	2,4,5,7, // tetromino S
	3,5,4,6, // tetromino Z
	2,4,5,6, // tetromino T
	3,5,7,6, // tetromino J

};

//structure for point with 2 int coordinates, functional and helping array
struct coord
{
	int x;
	int y;
}f[4], helper[4];

//function for checking if tetromino in collision position
bool collisionchecking()
{
	for (int i = 0; i < 4; i++)
	{
		if (f[i].x < 0 || f[i].y >= constants::fieldhigh || f[i].x >= constants::fieldwidth)
		{
			return true;
		}
		else if (field[f[i].y][f[i].x])
		{
			return true;
		}
	}
	return false;
}
#endif


