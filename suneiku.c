#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<curses.h>

static void finish(int sig);
void menu();

int main(int argc, char** argv)
{
  signal(SIGINT, finish);
  initscr();
  start_color();

  if (has_colors() == FALSE)
  {
    endwin();
    printf("No color support :(\n");
    exit(0);
  }

  keypad(stdscr, TRUE);
  nonl();
  cbreak();
  noecho();

  menu();

  finish(0);
}

void menu()
{
  int x,y;

  getyx(curscr,y,x);

  init_pair(1,COLOR_BLACK,COLOR_WHITE);
  addch(' ' | COLOR_PAIR(1));

  while (1)
  {
    sleep(1);
    int c = getch();

    switch (c)
    {
      case KEY_UP:
        y--;
        break;
      case KEY_DOWN:
        y++;
        break;
      case KEY_LEFT:
        x--;
        break;
      case KEY_RIGHT:
        x++;
        break;
    }

    move(y,x);
    //refresh();

    if (c == 'q')
      break;
  }
}

void finish(int sig)
{
  endwin();
  exit(0);
}
