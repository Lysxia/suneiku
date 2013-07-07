#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<curses.h>

void menu();
void finish(int sig);

void snake_init();
void snake_update(int direction);
void snake_clear();
int pop();
void push(int bit);
void push_back();

int main(int argc, char** argv)
{
  signal(SIGINT, finish);

  initscr();

  keypad(stdscr, TRUE);
  nonl();
  cbreak();
  noecho();

  menu();

  finish(0);
}

void menu()
{
  int xmax,ymax;
  int x,y,c;

  getyx(stdscr,y,x);
  getmaxyx(stdscr,ymax,xmax);

  addstr("Press\n");
  addstr("s to start a game.\n");
  addstr("q to quit.\n");

  move(ymax-1,xmax-1);

  refresh();

  while (c != 'q')
  {
    c = getch();
    switch (c)
    {
      case 's':
        clear();
        snake_init();
        snake_clear();
    }
  }
}


void menu2()
{
  snake_init();
  const int tries = 10;
  int i;
  for (i = 0; i<tries ; i++)
    push(i & 1);

  push_back();
  push_back();

  for (i = 0; i<tries+5 ; i++)
    printf("%d",pop()!=0);
}

void finish(int sig)
{
  endwin();
  menu2();
  exit(0);
}

#define HBORDER_CHAR ACS_HLINE
#define VBORDER_CHAR ACS_VLINE
#define STARTING_SIZE 3

struct {
  int xmax, ymax;
  int *s;
  int len;
  int hd, tl, hdofs, tlofs;
  int max_size, cur_size;
  int dir;
} snake;

const int directions[] = {0,1,0,-1,0};

void snake_init()
{
  box(stdscr,VBORDER_CHAR,HBORDER_CHAR);

  getmaxyx(stdscr,snake.ymax,snake.xmax);
  snake.ymax--; // Don't keep the border
  snake.xmax--;

  snake.max_size = (snake.ymax-1)*(snake.xmax-1);
  snake.cur_size = STARTING_SIZE;

  snake.len = snake.max_size/sizeof(int)<<1;

  if (NULL == (snake.s = malloc(snake.len*sizeof(int))))
  {
    printf("Not enough memory (LOL)");
    finish(0);
  }

  snake.s[0] = 0;

  snake.hd = snake.tl = 0;
  snake.hdofs = 0;
  snake.tlofs = STARTING_SIZE;
}

void snake_update(int direction)
{
}

void snake_clear()
{
  free(snake.s);
}

int pop()
{
  if (snake.tlofs)
  {
    snake.tlofs--;
  }
  else
  {
    snake.tl = (snake.tl+1)%snake.len;
    snake.tlofs = sizeof(int)-1;
  }

  return snake.s[snake.tl] & (1 << snake.tlofs);
}

void push(int bit)
{
  if (snake.hdofs)
  {
    snake.hdofs--;
  }
  else
  {
    snake.hd = (snake.hd+1)%snake.len;
    snake.hdofs = sizeof(int)-1;
    snake.s[snake.hd] = 0;
  }

  snake.s[snake.hd] |= bit << snake.hdofs;
}

void push_back() // necessarily 0
{
  snake.s[snake.tl] &= ~(1 << snake.tlofs);

  if (++snake.tlofs == sizeof(int))
  {
    snake.tlofs = 0;
    snake.tl = (snake.tl + snake.len - 1) % snake.len;
  }
}
