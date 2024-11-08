/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

#include "utils.h"

std::string kYourName = "Minskov Watt"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename)
{
  std::set<std::string> name_set;
  std::ifstream inputfs(filename);
  if (!inputfs.is_open())
  {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return name_set;
  }

  std::string name;
  while (std::getline(inputfs, name))
  {
    name_set.insert(name);
  }

  return name_set;
}

std::string getInitials(std::string name)
{
  std::string initial;
  initial += name.at(0);
  initial += name.at(name.find(" ") + 1);
  return initial;
}
/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string *> find_matches(std::string name, std::set<std::string> &students)
{
  const std::string MY_INITIALS = getInitials(name);
  std::queue<const std::string *> matches;
  for (auto it = students.begin(); it != students.end(); ++it)
  {
    if (getInitials(*it) == MY_INITIALS)
    {
      matches.push(&(*it));
    }
  }
  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string *> &matches)
{
  if (matches.empty())
  {
    std::cout << "NO STUDENT FOUND" << std::endl;
  }
  std::string match = *matches.front();
  return match;
}

/* #### Please don't modify this call to the autograder! #### */
int main() { return run_autograder(); }

/* 写在最后
 * 1. 熟悉了set和unordered_set的区别
 * 2. 学会了使用find()来查找字符串中的字符而不是手动遍历
 */