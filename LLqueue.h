/** LLqueue.h
 *Queue (Linked List based) Header file
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 4
 */
#include <iostream>
#include "listnode.h"
using namespace std;

/**
 * Creates and defines the parts of a queue, supporting the usual operations
 */
template <class T>
class LLQueue{
  public:
    //pointer to node at front of the list
    ListNode<T> *front;
    //pointer to node at back of the list
    ListNode<T> *back;
    //int representing size of queue
    int size;

    //default constructor
    LLQueue(){
      size=0;
      front=NULL;
      back=NULL;
    }
    //destructor
    ~LLQueue(){
      ListNode<T> *node=front;
      ListNode<T> *deleteNext=front;
      while (node!=NULL){
        deleteNext=node->next;
        delete node;
        node=deleteNext;
      }
    }

    /**
     * Removes node/data located at the front of the queue
     * @return T, represents data held at front node
     */
    T remove(){
      //if queue is empty
      if(size==0){
        return NULL;
      }
      else{
        ListNode<T> *rNode=front;
        if(front->next==NULL){
          back=NULL;
        }
        else{
          front->next->prev=NULL;
        }
        front=front->next;
        T r_data=rNode->data;
        rNode->next=NULL;
        delete rNode;
        size--;
        return r_data;
      }
    }
    /**
     * Inserts data into the queue (at the back)
     * @param d, data to be inserted
     */
    void insert(T d){
      ListNode<T> *node=new ListNode<T>(d);
      if(size==0){
        front=node;
      }
      else{
        back->next=node;
        node->prev=back;
      }
      back=node;
      ++size;
    }
    /**
     * Looks for data at front of queue without removing it
     * @return T, data at front of queue
     */
    T peek(){
      if(size==0){
        return NULL;
      }
      else{
        T p_data=front->data;
        return p_data;
      }
    }
    /**
     * Checks to see if the queue is empty
     * @return bool, true if size==0, false otherwise
     */
    bool isEmpty(){
      return(size==0);
    }
};
