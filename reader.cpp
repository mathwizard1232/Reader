#ifndef READER_CPP
#define READER_CPP

//#include <stdio.h>
#include <fstream>
#include <curses.h>
#include "print.h"
#include "utility.cpp"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
	  
int reader(int argc, char* argv[])
{
  initscr();
  timeout(0);
  curs_set(0);
  noecho();
  cbreak();
  Print out = Print();
  
  ifstream file;
  int advance = 0;

  if (argc > 1) {
    file.open(argv[1],std::ios::in);
    if (argc > 2) {
      if (argv[2][0] == 'm') {
	ifstream mark("mark.txt");
	string current;
	while ((mark >> current) && (strcmp(current.c_str(),argv[1])!=0)) {
	}
	mark >> advance;					      
	mark.close();
	if (argv[2][1] == 'r') {
	  advance -= 500;
	  if (advance < 0)
	    advance = 0;
	}
      }
      else {
	char* endptr;
	int temp = strtol(argv[2], &endptr, 10);
	if (endptr && (*endptr == '\0'))
	  advance = temp;
      }
    }
  }

  char str[2000];

  for (int i = 0; i < advance; i++)
    file >> str;

  int pos = advance;
  int lines = 3;
  int width = 40;
  int wait = 2;
  int current = 0;
  char temp[2000];
  temp[0] = '\0';

  int c;
  while(file >> str) {
    mvaddch(1,1,'a');
    refresh();
    mvaddch(3,3,'q');
    c = getch();
    mvaddch(4,4,'w');
    clrtoeol();
    if (c == 'q')
      break;

    mvaddch(1,2,'c');
    if ((length(temp) + 1 + length(str) < width) || temp[0] == '\0') {
      if (temp[0] != '\0')
	add(" ", temp);
      add(str, temp);
    }
    else if (current < lines) {
      out.print(temp);
      temp[0] = '\0';
      add(str,temp);
      current++;
      clear();
      out.refresh();
      refresh();
    }
    else {
      clear();
      out.refresh();
      refresh();
      sleep(wait);
      out.clear();
      out.print(temp);
      temp[0] = '\0';
      add(str,temp);
      current = 1;
      clear();
      out.refresh();
      refresh();
      }
    pos++;
  }

  ofstream mark("mark.txt");
  mark << argv[1] << " ";
  mark << pos;
  mark.close();

  endwin();
  return 0;
}

#endif
