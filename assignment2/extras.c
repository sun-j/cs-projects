/** 
 * Contained within this file are functions that would otherwise
 * clutter up Alan's quite pretty hw2.c 
 * 
 * It is mostly anciliary functions.
 *
 */

#include "hw2.h"

bool isLeapYear (int year) {
    
    bool result;
    
    if ((year % 400) == 0) {
        result = true;
    } else if ((year % 100) == 0) {
        result = false;
    } else if ((year % 4) == 0){
        result = true;
    } else {
        result = false;
    }
    
    return result;
}

void printList ( MsgNode head) {
    
    while (head != NULL) {
        amIFocused(head);
        printBrief(head, false);
        head = head->next;
    }
    
}

void amIFocused (MsgNode msg) {
    if (msg -> focus == true) {
        printf("-> ");
    } else {
        printf("   ");
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
    
    assert(focusCount == 1 || globalMessageNum == 0);
    
    return focus;
}

void relinker (TinyNode head, MsgNode node) {
    //implementation of the function using extra tree
    if (head->contents == NULL) { //initialisation
        head->contents = node;
        head->msgID = node->messageNum;
    } else if (node->inReplyTo > 0) {
        TinyNode temp;
        assert(node->inReplyTo < globalMessageNum);
        for (; head->msgID != node->inReplyTo; head = head->next);
        temp = calloc(1, sizeof(struct tinyNode));
        temp->next = head->next;
        head->next = temp;
        head = head->next;
        head->contents = node;
        head->msgID = node->messageNum;
    } else { //case where its just an a
        for (; head->next != NULL; head = head->next);
        head->next = calloc(1, sizeof(struct tinyNode));
        head = head->next;
        head->contents = node;
        head->msgID = node->messageNum;
    }
}


void printTree (TinyNode head) {
    //printing the node tree
    while (head != NULL) {
        amIFocused(head -> contents);
        printBrief(head -> contents, true);
        head = head -> next;
    }
}

void printIndent (int indent) {
    int i = 0;
    while (i < indent * 3) {
        printf(" ");
        i++;
    }
}

void printExpected (MsgNode list, TinyNode head,
                    MsgNode focus, int printType) {
    switch (printType) {
        case PFULL:
            printFull(focus);
            break;
        case PLIST:
            printList(list);
            break;
        case PTREE:
            printTree(head);
            break;
    }
}
/** inserts a node after another (the focus).
 *
 */
void insertNode ( MsgNode focus, MsgNode node )
{
    if (focus == NULL) {
        focus = node;
    } else {
        MsgNode next_node = focus->next;
        focus->next = node;
        node->next = next_node;
    }
}

/** just like eponymous hero, this function searches along the list
 * to find the message you want given a messageID (messageNum)
 */
MsgNode sherlock (MsgNode list, int msgID) {
    MsgNode target = list;
    int i = 1; //globalMessageCount starts at 1...
    while (i < msgID) {
        target = target -> next;
        i++;
    }
    
    return target;
}

/** just like its sister function, bloodhound scans along the
 * TinyNode struct to find the pointer to the tinyNode the repID
 * referring to.
 */
TinyNode bloodhound (TinyNode head, int repID) {
    TinyNode target = head;
    while (target->msgID != repID) {
        target = target -> next;
    }
    
    return target;
}

/** Function to reply to a focused message. Takes in a list and focus
 * returns the address of the node.
 */
MsgNode addReply (MsgNode list, MsgNode focus) {
    
    if (list == NULL) {
        return NULL;
    }
    
    MsgNode node;
    node = getNode();
    node->focus = true;
    node->inReplyTo = focus->messageNum;
    node->indent = focus->indent + 1;
    
    insertNode(sherlock(list, globalMessageNum - 1
                        ), node);
    
    focus->focus = false;
    return node;
}

/** Function to add a node. Takes in list and focus 
 * and returns the address of the new node.
 */
MsgNode addNode (MsgNode list, MsgNode focus) {
    MsgNode node;
    
    node = getNode();
    printFull( node );
    node -> focus = true;
    
    if (list == NULL) {
        list = node;
        //printf("list got assigned\n");
    } else {
        //grrr... alan and his i++ usage.
        insertNode(sherlock(list, globalMessageNum - 1
                            ), node);
        focus -> focus = false;
    }
    
    return node;
}

char *getString (void) {
    
    char string[MAX_LINE];
    char c;
    int i = 0;
    char *shortString;
    
    printf("Search text: ");
    
    putchar('\n');
    
    while ((c=getchar()) != '\n') {
        if (c >= ' ' && c < 127) {
            string[i] = toupper(c);
            i++;
        }
    }
    
    string[i] = '\0'; //cap off the string
    
    
    shortString = malloc(strlen(string)*sizeof(char));
    for (i = 0; i < (int) strlen(string); i++) {
        *(shortString+i) = string[i];
    }
    
    return shortString;
}

void searchNodes (MsgNode list, char *string) {
    
    MsgNode head = list;
    int i = 0;
    MsgNode toPrint = calloc(1, sizeof(struct msgNode));
    
    while (head != NULL) {
        char name[MAX_LINE];
        char *substituteName = malloc(strlen(head->text)*sizeof(char));
        strcpy(name, head->name);
        strcpy(substituteName, head->name);
        
        char message[MAX_TEXT];
        char *substituteMessage = malloc(strlen(head->text)*sizeof(char));
        strcpy(message, head->text);
        strcpy(substituteMessage, head->text);
        
        bool match = false;
        
        //control sequence for name
        for (i = 0; i < (int) strlen(name); i++) {
            name[i] = toupper(name[i]);
        }
        
        for (i = 0; i < (int) strlen(substituteName); i++) {
            if (strncmp(&name[i], string, strlen(string)) == 0) {
                memcpy((substituteName+i), string, strlen(string));
                match = true;
                i+=strlen(string);
            }
        }
        
        //control sequence for message
        for (i = 0; i < (int) strlen(message); i++) {
            message[i] = toupper(message[i]);
        }
        
        for (i = 0; i < (int) strlen(substituteMessage); i++) {
            if (strncmp(&message[i], string, strlen(string)) == 0) {
                memcpy((substituteMessage+i), string, strlen(string));
                match = true;
                i+=strlen(string);
            }
        }
        
        if (match) {
            memcpy(toPrint, head, sizeof(struct msgNode));
            toPrint->name = substituteName;
            toPrint->text = substituteMessage;
            printFull(toPrint);
        }
        
        head = head->next;
        free(substituteMessage);
        free(substituteName);
    }
    
    free(string);
    free(toPrint);
}

// Local Variables:
// c-basic-offset: 4
// End: