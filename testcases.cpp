#include "reader.cpp"
#include <stdio.h>

// Assert that the numbers are equal. If not, display error message.
void equal(int a, int b, const char str[])
{
  if (a != b)
    printf(str);
}

extern int length(const char*);

void lengthtests()
{
  equal(5,length("abcde"),"Length test failed.\n");
}

int main()
{
  lengthtests();
  printf("All tests run.\n");
  return 0;
}
