/** 
 * Contained within this file are functions that would otherwise
 * clutter up Alan's quite pretty hw2.c 
 * 
 * It is mostly anciliary functions and sem1 style tests.
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "hw2.h"

bool isLeapYear (int year) {
    
    bool result;
    result = 1;
    
    if ((year % 400) == 0) {
        result = 1;
    } else if ((year % 100) ==0) {
        result = 0;
    } else if ((year % 4) ==0){
        result = 1;
    } else {
        result = 0;
    }
    
    return result;
}

MsgNode addNode (MsgNode list, MsgNode node) {
    
    if (list == NULL) {
        list = node;
    } else {
        while (list -> next != NULL) {
            list = list -> next;
        }
    
        list -> next = node;
    }
    
    return list;
}

void printList ( MsgNode head) {
    
    while (head != NULL) {
        amIFocused(head);
        printBrief(head);
        head = head->next;
    }
    
}

void amIFocused (MsgNode msg) {
    if (msg -> focus == true) {
        printf(" --> ");
    } else {
        printf("     ");
    }
    
}

MsgNode findFocus (MsgNode head) {
    MsgNode focus = head;
    int focusCount = 0;
    
    do {
        if (head == NULL) {
            break;
        } else if (head -> focus == true) {
            focus = head;
            focusCount++;
        }
        
        head = head -> next;
    } while (head != '\0');
    
    assert(focusCount == 1 || globalMessageNum == 1);
    
    return focus;
}

void insertNode ( MsgNode focus, MsgNode node )
{
    if (focus == NULL) {
        focus = node;
    } else {
        MsgNode next_node = focus -> next;
        focus->next = node;
        node -> next = next_node;
    }
    
    
}

MsgNode sherlock (MsgNode list, int msgID) {
    MsgNode target = list;
    int i = 1; //globalMessageCount starts at 1...
    while (i < msgID) {
        target = target -> next;
        i++;
    }
    
    return target;
}

// Local Variables:
// c-basic-offset: 4
// End: