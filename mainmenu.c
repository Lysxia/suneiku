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

  while (1)
  {
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
