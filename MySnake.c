#include "MySnake.h"

Piece* creatPiece(int x, int y)
{
    Piece* ps = (Piece*)malloc(sizeof(Piece));
    ps->x = x;
    ps->y = y;
    return ps;
}

MySnake* creatSnake(int startx, int endx, int len)
{
    MySnake* s = (MySnake*)malloc(sizeof(MySnake));
    s->hasFood = 0;
    if (startx < 0) startx = 0;
    if (endx > len - 1) endx = len - 1;
    
    s->board = (int**)malloc(len * sizeof(int*));
    for (int i = 0; i < len; i++) {
        s->board[i] = (int*)malloc(len * sizeof(int));
        for (int j = 0; j < len; j++) {
            s->board[i][j] = EMPTY;
        }
    }


    s->WIDTH = len;

    if (endx <= startx) endx = startx + 1;

    MyNode* startNode = creatNode(creatPiece(startx, 0));
    s->board[0][startx] = SNAKE_BODY;
    MyNode* node = startNode;
    s->snakeLength = 1;
    s->startNode = startNode;
    
    for (int i = startx + 1; i < endx; i++) {
        node->child = creatNode(creatPiece(i, 0));
        node->child->parent = node;
        node = node->child;
        s->snakeLength++;
    }

    s->endNode = node;
    return s;
}

void destroySnake(MySnake* snake)
{
    if (!snake) {
        destroyNode(&(snake->startNode));
        for (int i = 0; i < snake->WIDTH; i++) {
            free(snake->board[i]);
        }
        //free(snake->board);
        free(snake->board);
        free(snake);
    }
}

int moveSnake(MySnake* s, int direction)
{
    if (direction < 0 || direction > 3) return 0;
    Piece* p = (Piece*)s->startNode->val;
    int x = p->x, y = p->y;
    switch (direction) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case RIGHT:
        x++;
        break;
    case LEFT:
        x--;
        break;
    }

    if (isFaild(s, x, y)) {
        printf("failed!!!\n");
        return 0;
    }

    MyNode* node = creatNode(creatPiece(x, y));
    //update the start node;
    node->child = s->startNode;
    s->startNode->parent = node;
    s->startNode = node;
    if(s->board[y][x] != SNAKE_FOOD)
    {
        //get the last child node
        MyNode* n = s->endNode;

        //update "endnode" in snake
        s->endNode = s->endNode->parent;

        //reset the pointer
        //n->parent->child = NULL;
        s->endNode->child = NULL;
        //delete the last node
        Piece* p = (Piece*)n->val;
        s->board[p->y][p->x] = EMPTY;
        deleteSingleNode(n);
    }
    else if (s->board[y][x] == SNAKE_FOOD) {
        s->snakeLength++;
        s->hasFood = 0;
    }
    s->board[y][x] = SNAKE_BODY;
    generateFood(s);
    return 1;
}

/*
in this function, the property of snake will be changed.
*/
int isFaild(MySnake* snake, int x, int y) 
{
    Piece* p = (Piece*)snake->startNode->val;
    //printf("x, y of piece p: %d, %d\n", p->x, p->y);
    //printf("WIDTH of snake is:%d\n", snake->WIDTH);
    if (x < snake->WIDTH && x >= 0 &&
        y < snake->WIDTH && y >= 0) {
        
        if (snake->board[y][x] == EMPTY || snake->board[y][x] == SNAKE_FOOD) {
            return 0;
        }
        if (snake->board[y][x] == SNAKE_BODY &&
            y == ((Piece*)(snake->endNode->val))->y &&
            x == ((Piece*)(snake->endNode->val))->x) {
            return 0;
        }
        //return 0;
        printf("This will be un fine...\n");
    }
    return 1;
}

void generateFood(MySnake*s)
{
    if (s->hasFood) return;
   srand(time(NULL));
   int random_number = rand() % (s->WIDTH*s->WIDTH - s->snakeLength);
   int cou = 0;
   for (int i = 0; i < s->WIDTH; i++) {
       for (int j = 0; j < s->WIDTH; j++) {
           if (s->board[i][j] == EMPTY) {
               if (cou == random_number) {
                   s->board[i][j] = SNAKE_FOOD;
                   s->hasFood = 1;
                   return;
               }
               cou++;
           }
       }
   }
}

