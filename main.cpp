#include <iomanip>
#include <iostream>
#include "string.h"
#include <queue>
#include "stringsubber.h"
using namespace std;

int main(int argc, char* argv[])
{
  string old_string = argv[1];
  string new_string = argv[2];
  string filename   = argv[3];

  stringsubber* sb = new stringsubber(old_string, new_string, filename);

  sb->substitute();
  return 0;
}