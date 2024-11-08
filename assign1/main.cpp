/*
 * CS106L Assignment 1: SimpleEnroll
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * You must fill in the types of the fields in this struct.
 * Hint: Remember what types C++ streams work with?!
 */
struct Course
{
  std::string title;
  std::string number_of_units;
  std::string quarter;
};

/**
 * Note:
 * We need to #include utils.cpp _after_ we declare the Course struct above
 * so that the code inside utils.cpp knows what a Course is.
 * Recall that #include literally copies and pastes file contents.
 */
#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide in utils.cpp
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!
 *
 * @param filename The name of the file to parse.
 * @param courses  A vector of courses to populate.
 */
void parse_csv(std::string filename, std::vector<Course> &courses)
{
  std::ifstream fs(filename);
  if (!fs.is_open())
  {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::string first_line;
  std::getline(fs, first_line); // Ignore the first line

  std::string line;
  while (std::getline(fs, line))
  {
    auto split_line = split(line, ',');
    courses.emplace_back(Course{split_line[0], split_line[1], split_line[2]});
  }

  fs.close();
}

/**
 * This function has TWO requirements.
 *
 * 1) Write the courses that are offered to the file
 * "student_output/courses_offered.csv"
 *
 * 2) Delete the courses that are offered from the `all_courses` vector.
 * IMPORTANT: do this after you write out to the file!
 *
 * HINTS:
 * 1) Keep track of the classes that you need to delete!
 * 2) Use the delete_elem_from_vector function we give you!
 * 3) Remember to write the CSV column headers at the beginning of the output!
 *    See courses.csv for reference.
 *
 * @param all_courses A vector of all courses gotten by calling `parse_csv`.
 *                    This vector will be modified by removing all offered courses.
 */
void write_courses_offered(std::vector<Course> &all_courses)
{
  std::ofstream fs(COURSES_OFFERED_PATH);
  if (!fs.is_open())
  {
    std::cerr << "Error opening file: " << COURSES_OFFERED_PATH << std::endl;
    return;
  }
  std::cout << all_courses.begin()->title << all_courses.begin()->number_of_units << all_courses.begin()->quarter << std::endl;

  fs << "Title,Number of Units,Quarter" << std::endl;

  int i = 0;
  std::vector<int> to_delete;

  for (auto it = all_courses.begin(); it != all_courses.end(); ++it, ++i)
  {
    if (it->quarter != "null")
    {
      fs << it->title << "," << it->number_of_units << "," << it->quarter << std::endl;
      to_delete.push_back(i);
    }
  }
  for (auto it = to_delete.rbegin(); it != to_delete.rend(); ++it)
  {
    all_courses.erase(all_courses.begin() + *it);
  }
  fs.close();
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 *
 * @param unlisted_courses A vector of courses that are not offered.
 */
void write_courses_not_offered(std::vector<Course> &unlisted_courses)
{
  std::ofstream fs(COURSES_NOT_OFFERED_PATH);
  if (!fs.is_open())
  {
    std::cerr << "Error opening file: " << COURSES_OFFERED_PATH << std::endl;
    return;
  }
  std::cout << unlisted_courses.begin()->title << unlisted_courses.begin()->number_of_units << unlisted_courses.begin()->quarter << std::endl;

  fs << "Title,Number of Units,Quarter" << std::endl;

  for (auto it = unlisted_courses.begin(); it != unlisted_courses.end(); ++it)
  {
    fs << it->title << "," << it->number_of_units << "," << it->quarter << std::endl;
  }
  fs.close();
}

int main()
{
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  // print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}

/* 写在最后(本次Assignment的学会的内容)
 * 1. 基本的文件流的读写
 * 2. 通过在调用函数时传入引用来修改函数外的变量，保证变量的生命周期在同个作用域
 * 3. 在vector中删除元素时，要注意删除的顺序
 * ---分割比较不重要的部分---
 * 4. 学会了使用emplace_back()直接构造一个对象并添加到vector中
 */