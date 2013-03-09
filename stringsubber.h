#ifndef STRINGSUBBER_H
#define STRINGSUBBER_H

#include <streambuf>
#include <fstream>
#include <queue>
using namespace std;

class stringsubber {
  public:
    stringsubber(string o_string, string n_string, string fi_name);
    void substitute();
    ~stringsubber();

  private:
    string old_string;
    string new_string;
    string filename;
    queue<char> buffer;
    fstream file_to_sub;
    streampos putter;
    streampos getter;

    bool match_new_string();
    void grow_queue();
    void clear_error();
    void clear_and_set_end();
};

#endif