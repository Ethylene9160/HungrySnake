#include<stdio.h>
#include<stdlib.h>

#ifndef _MY_SNAKE_
#define _MY_SNAKE_ 1

#include <time.h>

enum DIRECTION
{
	UP = 0, DOWN, LEFT,RIGHT
};
//types of each cone
#define SNAKE_FOOD 2
#define SNAKE_BODY 1
#define EMPTY 0


#include"MyNode.h"

//just a struct to stroe the cartesian position.
typedef struct {
	int x, y;
}Piece;


typedef struct {
	MyNode* startNode;
	MyNode* endNode;
	int** board;
	//width of the bord
	int WIDTH;
	//current length of snake
	int snakeLength;
	//store the state whether it has generated food.
	int hasFood;
}MySnake;

/*
return a Piece* with x and y
*/
Piece* creatPiece(int x, int y);

/*
defaultly, it will start line y0.
startx, endx should be in range [0,len-1], with endx must laget than startx.
if startx<0, startx =0;
endx > len-1, endx = len-1.
and it will same initialize the board.
finally, it will return the pointer of the snake.
*/
MySnake* creatSnake(int startx, int endx, int len);

//int getLength();

/*
release the memory of snake.
*/
void destroySnake(MySnake* snake);

/*
the most important function of this file.
paras:
s: pointer of MySnake;
d: the direction.see the definition of the enum lines.
if it cannot move, or the direction is not correct, like it hit itself or hit the border.
it will return 0.
else, return 1, and reset the list of snake body, and reset the board.
*/
int moveSnake(MySnake* s, int d);

/*
see as private function.
*/
int isFaild(MySnake* snake, int x, int y);

/*
this will set the food on the board.
it;s garenteed that the food won't be set on the body of the snake.
*/
void generateFood(MySnake*s);



#endif
