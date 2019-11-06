/** student.h
 *Registrar simulation file
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 4
 */
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "LLqueue.h"
#include "student.h"
using namespace std;

/**
 * Representation of a registrar's office, with windows and a queue, queueLine.
 * Reads in information from a file in order to create registrar's office model
 * Contains methods for running a simulation, and calculating statistics about said simulation.
 */
class Registrar{
  public:
    //check if all student have been helped
    bool finished;
    //number of windows in office
    int num_windows;
    //array representing windows
    Student* *windows;

    //amount of time gone by/ clock tick
    int time_pass;
    //time student arrives
    int entry_time;
    //number of students that arrive at entry_time
    int num_students;
    //time each student needs at window
    int time_needed;
    //string to read in from file
    string line;
    //read in from file
    ifstream in_file;
    //help determine what to do with the next line read from the file
    int helper;
    //a student
    Student *student;
    //student at front of line
    Student *frontOfLine;

    //queue of students
    LLQueue<Student*> queueLine;

    //default constructor
    Registrar();
    //overloaded constructor
    Registrar(string file);
    //destructor
    ~Registrar();

    //runs the simulation
    void runSim();

    void calc();

    //array of window idle times
    int *window_idle;
    //array to store student wait times
    int *wait_times;
    //used for calculations
    int total_students;
    //used to store wait times in the array
    int stud_position;

    //total wait time of all students
    float total_wait;
    //represents idle time of all windows combined
    float idle_time;
    //the mean student wait time
    float mean_wt;
    //the median student wait time
    float median_wt;
    //the longest student wait time
    float long_wt;
    //number of student with wait times greater than 10
    float ten_min_wait;
    //the mean window idle time
    float mean_idle;
    //the longest window idle time
    float long_idle;
    //the number of windows with an idle time greater than 5
    float five_min_idle;
};
//default constructor
Registrar::Registrar(){
  finished=false;
  num_windows=0;
  time_pass=0;
  entry_time=0;
  num_students=0;
  time_needed=0;
  line="";
  helper=0;
  total_students=0;
  idle_time=0;
  total_wait=0;
  mean_wt=0;
  median_wt=0;
  long_wt=0;
  ten_min_wait=0;
  mean_idle=0;
  long_idle=0;
  five_min_idle=0;
}
//destructor
Registrar::~Registrar(){
  delete student;
  delete windows;
  delete wait_times;
  delete window_idle;
}
/**
 * Overloaded constructor, creates the registrar office model
 * @param file, string representing the name of a file to read in
 */
Registrar::Registrar(string file){
  finished=false;
  time_pass=0;
  entry_time=0;
  num_students=0;
  time_needed=0;
  line="";
  helper=0;
  total_wait=0;
  idle_time=0;
  mean_wt=0;
  median_wt=0;
  long_wt=0;
  ten_min_wait=0;
  mean_idle=0;
  long_idle=0;
  five_min_idle=0;
  in_file.open(file, ios::in);
  //if file does not exist
  if(in_file.is_open()==false){
    cout<<"File not found. Try again."<<endl;
    exit(0);
  }
  //file exists
  while(in_file.is_open()){
    //formatting
    cout<<endl;
    //read file line by line
    while(getline(in_file, line)){
      //first thing in is number of windows
      if(helper==0){
        num_windows=stoi(line);
        //create an array of students to represent windows
        windows=new Student*[num_windows];
        for(int i=0; i<num_windows; ++i){
          windows[i]=new Student();
        }
        //next number is time students arrive
        helper=1;
      }
      //time student arrives
      else if(helper==1){
        entry_time=stoi(line);
        //next numbers are number of students arriving and time they each need at the window
        helper=2;
      }
      //number of students at that time
      else if(helper==2){
        num_students=stoi(line);
        //the following lines contain the amount of time each student needs
        for(int i=0; i<num_students; ++i){
          getline(in_file, line);
          time_needed=stoi(line);
          //create a student with given entry time and time needed
          student=new Student(entry_time, time_needed);
          //and place into queue
          queueLine.insert(student);
        }
        //back to student arrival time
        helper=1;
      }
    }
    in_file.close();
  }
  //array the size of the total number of students
  wait_times=new int[queueLine.size];
  total_students=queueLine.size;
  stud_position=total_students-1;
}
/**
 * Runs the simulation of a day/period of time at the registrar's office
 */
void Registrar::runSim(){
  //while there are still students in the registrar's office
  while(finished==false){
    //reset check for windows in use
    bool windows_full=false;
    //clock tick
    ++time_pass;
    //look at all windows
    for(int i=0; i<num_windows; ++i){
      //if window is empty
      if(windows[i]->time_needed_s==0){
        //check if there are students in line
        if(queueLine.isEmpty()==false){
          //check if there is a student in line at current clock tick
          frontOfLine=queueLine.peek();
          if(frontOfLine->entry_time_s<=time_pass){
            //remove student from line and assign to open window
            Student *curr=queueLine.remove();
            windows[i]->entry_time_s=curr->entry_time_s;
            windows[i]->time_needed_s=curr->time_needed_s;
            //time in line is how long they had to wait in queue after they arrived
            windows[i]->time_in_line_s=(time_pass-(windows[i]->entry_time_s));
            //put this wait time into the array
            wait_times[stud_position--]=windows[i]->time_in_line_s;
          }
        }
      }
      //if window is in use
      else if((windows[i]->time_needed_s)>0){
        //as time passes, time a student needs decreases
        --(windows[i]->time_needed_s);
      }
    }
    //check if any windows are in use before starting next clock tick
    //and adjust idle time
    for(int l=0; l<num_windows; ++l){
      //no student at window
      if(windows[l]->time_needed_s==0){
        idle_time++;
        windows[l]->time_idle+=1;
      }
      //there are still students at windows
      else if(windows[l]->time_needed_s>0){
        windows_full=true;
      }
    }
    //if queue is empty
    if(queueLine.isEmpty()){
      //and no one is at the windows
      if(windows_full==false){
        //all students have been helped
        finished=true;
      }
    }
  }
}

/**
 * Calculates labeled metrics for simulation and prints to console
 */
void Registrar::calc(){
  //sort wait times in ascending order
  sort(wait_times, wait_times+total_students);
  for(int j=0; j<total_students; ++j){
    total_wait+=wait_times[j];
    if(wait_times[j]>10){
      ten_min_wait++;
    }
  }
  if(total_wait==0 || total_students==0){
    mean_wt=0;
  }
  else{
    mean_wt=total_wait/total_students;
  }
  cout<<"Mean student wait time: "<<mean_wt<<endl;

  //if total is odd
  if(total_students%2==1){
    int med=total_students/2;
    //get median from its position in the array
    median_wt=wait_times[med];
  }
  //if total is even
  else{
    int med_1=total_students/2;
    int med_2=med_1-1;
    //get the average of the two middle values
    median_wt=(wait_times[med_1]+wait_times[med_2])/2;
  }
  cout<<"Median student wait time: "<<median_wt<<endl;

  //number at end of sorted list is greatest
  long_wt=wait_times[total_students-1];
  cout<<"Longest student wait time: "<<long_wt<<endl;

  cout<<"Number of students waiting over 10 minutes: "<<ten_min_wait<<endl;

  window_idle=new int[num_windows];
  long_idle=windows[0]->time_idle;
  for(int k=0; k<num_windows; ++k){
    int curr_idle=windows[k]->time_idle;
    window_idle[k]=curr_idle;
    if(curr_idle>long_idle){
      long_idle=curr_idle;
    }
    if(curr_idle>5){
      five_min_idle++;
    }
  }

  mean_idle=idle_time/num_windows;
  cout<<"Mean window idle time: "<<mean_idle<<endl;

  cout<<"Longest window idle time: "<<long_idle<<endl;

  cout<<"Number of windows idle for over 5 minutes: "<<five_min_idle<<endl;
  //formatting
  cout<<endl;
}
