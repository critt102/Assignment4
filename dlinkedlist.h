/** dlinkedlist.h
 *Doubly Linked List Header file
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
 * DLinkedList creates and defines the parts of a doubly linked list,
 * supporting the usual operations
 */
template <class T>
class DLinkedList{
  private:
    //size of the linked list
    unsigned int size;
    //pointer to node at front of list
    ListNode<T> *front;
    //pointer to node at back of list
    ListNode<T> *back;
  public:
    //default constructor
    DLinkedList(){
      front=NULL;
      back=NULL;
      size=0;
    }
    //destructor
    ~DLinkedList(){
      ListNode<T> *node=front;
      ListNode<T> *deleteNext=front;
      while (node!=NULL){
        deleteNext=node->next;
        delete node;
        node=deleteNext;
      }
    }
    /**
     * Checks to see if there is anything in the list
     * @return bool false if list contains at least 1 not NULL node, true if empty
     */
    bool isEmpty(){
      //if empty
      if(front==NULL && back==NULL)
        return true;
      else
        return false;
    }
    /**
     * Returns the size of the linked list
     * @return int, representing the size of the linked list
     */
    int getSize(){
      return size;
    }
    /**
     * Inserts a node with given data into the list at the front
     * @param d, representing the data to be inserted
     */
    void insertFront(T d){
      //create a new node with given data
      ListNode<T> *node=new ListNode<T>(d);
      //if empty
      if(size==0){
        //back and front are the same node
        back=node;
      }
      else{
        node->next=front;
        front->prev=node;
      }
      //node is now in the front
      front=node;
      ++size;
    }
    /**
     * Inserts a node with given data into the list at the back
     * @param d, representing the data to be inserted
     */
    void insertBack(T d){
      ListNode<T> *node=new ListNode<T>(d);
      //if empty
      if(size==0){
        //front and back are the same node
        front=node;
      }
      else{
        node->prev=back;
        back->next=node;
      }
      //node is now at the back
      back=node;
      size++;
    }
    /**
     * Removes the node located at the front of the list
     * @return T, template item representing the data removed from the list
     */
    T removeFront(){
      ListNode<T> *ft=front;
      if(front->next==NULL){
        back=NULL;
      }
      else{
        front->next->prev=NULL;
      }
      front=front->next;
      T temp=ft->data;
      ft->next=NULL;
      delete ft;
      --size;
      return temp;
    }
    /**
     * Removes the node located at the back of the list
     * @return T, template item representing the data removed from the list
     */
    T removeBack(){
      ListNode<T> *bk=back;
      if(back->prev==NULL){
        front==NULL;
      }
      else{
        back->prev->next=NULL;
      }
      back=back->prev;
      T temp=bk->data;
      bk->prev=NULL;
      delete bk;
      --size;
      return temp;
    }
    /**
     * Finds node containing data d and removes entire node from the list
     * @param  d, data to be found
     * @return ListNode<T>*, list node containing data matching d
     */
    ListNode<T>* remove(T d){
      ListNode<T> *current=front;
      //recursive search for node containing data d
      while(current->data!=d){
        current=current->next;
        //if matching data is not found
        if(current=NULL){
          return NULL;
        }
      }
      if(current==front)
        front=current->next;
      else
        current->prev->next=current->next;
      if(current==back)
        back=current->prev;
      else
        current->next->prev=current->prev;
      current->next=NULL;
      current->prev=NULL;
      size--;
      return current;
    }
};
