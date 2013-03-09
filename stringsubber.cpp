#include "stringsubber.h"
#include <iostream>

stringsubber::stringsubber(string o_string, string n_string, string fi_name)
                           : old_string(o_string), new_string(n_string),
                             filename(fi_name)

{
  // Convert string to char array for input file
  char * name_str = new char [filename.size() + 1];
  strcpy(name_str, filename.c_str());
  file_to_sub.open(name_str, ios::in | ios::out);
}

void stringsubber::substitute()
{

  grow_queue();
  while(!buffer.empty())
  {
    bool match = match_new_string();
    clear_error();

    if(match)
    {
      file_to_sub.seekp(putter);

      if(new_string.length() == old_string.length())
      {
        for (size_t i = 0; i < new_string.length(); i++)
        {
          clear_error();
          file_to_sub.put(new_string[i]);
          file_to_sub.tellg();
        }
      }
      else if (new_string.length() > old_string.length())
      {
        size_t i;
        for (i = 0; i < old_string.length(); i++)
        {
          clear_error();
          file_to_sub.put(new_string[i]);
          file_to_sub.tellg();
        }
        putter = file_to_sub.tellp();
        file_to_sub.seekg(getter);
        for (size_t j = i; j < new_string.length(); j++)
        {
          grow_queue();
        }
        clear_error();
        file_to_sub.seekg(putter);
        for (size_t j = i; j < new_string.length(); j++)
        {
          clear_error();
          file_to_sub.put(new_string[j]);
          file_to_sub.tellg();
        }
      }
      else
      {
        size_t i;
        for (i = 0; i < new_string.length(); i++)
        {
          file_to_sub.put(new_string[i]);
        }
        grow_queue();
        for (size_t j = i; j < old_string.length(); j++)
        {
          if(!buffer.empty())
          {
            buffer.pop();
            grow_queue();
          }
        }
      }
      putter = file_to_sub.tellp();
      file_to_sub.seekg(getter);
    }
    else
    {
      grow_queue();
    }
  }
}

bool stringsubber::match_new_string()
{
  if(old_string.length() == 0)
  {
    return false;
  }
  for (size_t i = 0; i < old_string.length(); i++)
  {
    if(!buffer.empty())
    {
      char test_c = buffer.front();
      buffer.pop();
      if(test_c != old_string[i])
      {
        clear_error();
        file_to_sub.seekp(putter);
        file_to_sub.put(test_c);
        putter = file_to_sub.tellp();
        return false;
      }
      else
      {
        grow_queue();
        getter = file_to_sub.tellg();
      }
    }
    else
    {
      return false;
    }
  }
  return true;
}

void stringsubber::grow_queue()
{
  char ch;
  if(file_to_sub.good())
  {
    file_to_sub.get(ch);
    if(file_to_sub.good())
    {
      buffer.push(ch);
    }
  }
}

void stringsubber::clear_error()
{
  if(!file_to_sub.good())
  {
    file_to_sub.clear();
  }
}

void stringsubber::clear_and_set_end()
{
  if(!file_to_sub.good())
  {
    file_to_sub.clear();
    file_to_sub.seekg(0, ios::end);
  }
}

stringsubber::~stringsubber()
{
  file_to_sub.close();
}