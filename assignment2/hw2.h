/**
 hw2.h
 
 COMP1917 Computing 1
 
 Program supplied as a starting point for
 Assignment 2: Message Board
 
 UNSW Session 2, 2014
 */

#ifndef HW2_H
#define HW2_H

#include <stdbool.h>
#include <time.h>

#define TRUE           1
#define FALSE          0

#define MAX_LINE     256
#define MAX_TEXT    4096

extern int globalMessageNum;

typedef struct date    *Date;
typedef struct time    *Time;
typedef struct msgNode *MsgNode;

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
void  printBrief( MsgNode msg );
void   printFull( MsgNode msg );
void    freeList( MsgNode head );

// I'm taking you up on that offer Allan
// Functions declared below exist in the realm known as
// extras.c

//bool  dateCheck ();
bool isLeapYear (int year);
MsgNode addNode (MsgNode list, MsgNode node);
void printList (MsgNode head);
void amIFocused (MsgNode msg);
MsgNode findFocus (MsgNode head);
void insertNode (MsgNode focus, MsgNode node);
#endif /* !defined(HW2_H) */

// Local Variables:
// c-basic-offset: 4
// End: