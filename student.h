/** student.h
 *Student class header file
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 4
 */
#include <iostream>
#include <fstream>
using namespace std;

/**
 * Student class represents a student getting help at the registrar's office
 * holds a set of integers representing various data
 * related to students and the simulation
 */
class Student{
  public:
    //time student entered the queue
    int entry_time_s;
    //time student needs at a window to be helped
    int time_needed_s;
    //how long the student is waiting in the queue
    int time_in_line_s;
    //time a window is idle
    int time_idle;
    //default constructor
    Student();
    //overloaded constructor
    Student(int entry_s, int time_s);
    //destructor
    ~Student();
};

//default constructor
Student::Student(){
  entry_time_s=0;
  time_needed_s=0;
  time_in_line_s=0;
  time_idle=0;
}
/**
 * overloaded constructor
 * @param entry_s, integer representing the time the student entered the queue
 * @param time_s, integer representing the time the student needs at the window
 */
Student::Student(int entry_s, int time_s){
  entry_time_s=entry_s;
  time_needed_s=time_s;
  time_in_line_s=0;
  time_idle=0;
}
//destructor
Student::~Student(){};
