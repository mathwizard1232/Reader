#include "reader.cpp"

//extern int length(const char*);

void bar() { length("hello"); }

int main()
{
  printf("%i",length("hello"));
  return 0;
}
