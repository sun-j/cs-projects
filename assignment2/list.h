/*
   list.h

   Sample program for COMP1917

   Header file for list.c
*/

#include "hw2.h"

MsgNode * makeNode( int data );    // create new node
MsgNode * findNode( int data, MsgNode *head );

MsgNode * push( MsgNode *new_node, MsgNode *head );// to front
MsgNode * pop ( MsgNode *head );                 // first item

void    printList( MsgNode *head ); // print all items
//void free_List ( MsgNode *head ); // clear entire list

MsgNode * insert( MsgNode *new_node, MsgNode *head );// in order
MsgNode * excise( MsgNode *old_node, MsgNode *head );
