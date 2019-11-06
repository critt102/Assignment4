/** listnode.h
 *List Node Header file
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 4
 */
#include <iostream>
using namespace std;

/**
 * ListNode class creates and defines Nodes to be used in DLinkedList and LLqueue
 */
template <class T>
class ListNode{
  public:
    //Template to hold data of Node
    T data;
    //pointer to next node
    ListNode *next;
    //pointer to prev node
    ListNode *prev;

    //default constructor
    ListNode(){
      data=NULL;
      next=NULL;
      prev=NULL;
    }
    //overloaded constructor
    ListNode(T d){
      data=d;
      next=NULL;
      prev=NULL;
    }
    //destructor
    ~ListNode(){
      next=NULL;
      prev=NULL;
      delete next;
      delete prev;
    }
};
