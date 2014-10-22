/**
 hw2.h
 
 COMP1917 Computing 1
 
 Program supplied as a starting point for
 Assignment 2: Message Board
 
 UNSW Session 2, 2014
 */

#ifndef HW2_H
#define HW2_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>


#define MAX_LINE     256
#define MAX_TEXT    4096

#define PLIST 0
#define PFULL 1
#define PTREE 2

extern int globalMessageNum;

typedef struct date    *Date;
typedef struct time    *Time;
typedef struct msgNode *MsgNode;
typedef struct tinyNode *TinyNode;

struct date {
    int day;
    int month;
    int year;
};

struct time {
    int hour;
    int minute;
    int second;
};

struct msgNode {
    int   messageNum;
    int   inReplyTo;
    int   indent;
    bool  focus;
    bool  deleted;
    char *name;
    Date  date;
    Time  time;
    char *text;
    MsgNode next;
};

struct tinyNode {
    int msgID;
    MsgNode contents;
    TinyNode next;
};

// INSERT NEW FUNCTION PROTOTYPES, AS APPROPRIATE

void printPrompt();
void   printHelp();
MsgNode getNode( void );
char    *getName( void );
char    *getText( void );
void     getDate( Date d );
int     scanDate( Date d );
void     getTime( Time t );
int     scanTime( Time t );
int       dateOK( Date d );
int       timeOK( Time t );
void printPadded( int n );
void   printDate( Date d );
void   printTime( Time t );
void  printBrief( MsgNode msg, bool t );
void   printFull( MsgNode msg );
void    freeList( MsgNode head );

// I'm taking you up on that offer Allan
// Functions declared below exist in the realm known as
// extras.c

//bool  dateCheck ();
bool isLeapYear (int year);
void printList (MsgNode head);
void amIFocused (MsgNode msg);
MsgNode findFocus (MsgNode head);
void relinker (TinyNode head, MsgNode node);
void printTree (TinyNode head);
void printIndent (int indent);
void printExpected (MsgNode list, TinyNode head,
                    MsgNode focus, int printType);
void insertNode (MsgNode focus, MsgNode node);
MsgNode sherlock (MsgNode list, int msgID);
int sniffer (MsgNode list, int repID);
MsgNode* bloodhound (MsgNode list, int repID);
MsgNode addReply (MsgNode list, MsgNode focus);

// Don't touch below this point.
#endif /* !defined(HW2_H) */

// Local Variables:
// c-basic-offset: 4
// End: