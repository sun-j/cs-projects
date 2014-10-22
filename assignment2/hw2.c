/*
 hw2.c
 
 COMP1917 Computing 1
 
 Program supplied as a starting point for
 Assignment 2: Message Board
 
 Additional code supplied by:
    Joshua Sun (z5014981)
 
 UNSW Session 2, 2014
 */

#include "hw2.h"

int globalMessageNum = 0;


int main( int argc, char *argv[] )
{
    MsgNode list = NULL;
    MsgNode node;
    MsgNode focus;
    TinyNode head = calloc(1, sizeof(struct tinyNode));
    Ghost undoHelper = calloc(1, sizeof(struct ghosts));
    char command[MAX_LINE];
    char c;
    int printType = PFULL;
    int mode = PLIST;
    
    printPrompt();
    
    // enter a loop, reading and executing commands from the user
    while( fgets(command,MAX_LINE,stdin) != NULL ) {
        char *p;
        
        focus = findFocus(list);
        
        // replace newline with end-of-string character
        if(( p = strchr(command,'\n')) != NULL ) {
            *p = '\0';
        }
        p = command;
        while( isspace(*p)) { // skip any initial spaces
            p++;
        }
        c = *p;
        
        if( isdigit(c)) {
            //printf("%d\n", atoi(&c);
            // INSERT CODE FOR JUMPING TO MESSAGE k
            undoHelper->focus = focus->messageNum;
            int temp = c - '0';
            if (temp > globalMessageNum) {
                printf("message %d doesn't exist\n", temp);
            } else {
                focus->focus = false;
                focus = sherlock(list, temp);
                focus->focus = true;
                printExpected(list, head, focus, printType);
            }
        }
        else switch(tolower(c)) {
                /*
                 * "Enter command (A,F,B,P,L,D,R,T,S,U,Q, H for Help): "
                 */
            case 'a': // Add item
                // MODIFY THIS CODE, AS APPROPRIATE
                node = getNode();
                node -> focus = true;
                
                
                if (list == NULL) {
                    list = node;
                    relinker(head, node);
                    //printf("list got assigned\n");
                } else {
                    undoHelper->focus = focus->messageNum;
                    insertNode(sherlock(list, globalMessageNum - 1
                                        ), node);
                    relinker(head, node);
                    focus -> focus = false;
                    focus = node;
                }
                
                printExpected(list, head, node, printType);
                break;
                
                // INSERT CODE HERE
                
                // TO IMPLEMENT OTHER COMMANDS
                
                //thankyou alan;
            case 'f':
                //moves forward
                undoHelper->focus = focus->messageNum;
                
                if (mode == PTREE &&
                    bloodhound(head, focus->messageNum)->next != NULL) {
                    focus->focus = false;
                    focus = bloodhound(head, focus->messageNum)->next->contents;
                    focus->focus = true;
                } else if (focus->next != NULL) {
                    focus -> focus = false;
                    focus = focus -> next;
                    focus -> focus = true;
                } else {
                    undoHelper->blank = true;
                    break;
                }
                
                printExpected(list, head, focus, printType);
                
                break;
            
            case 'b':
                //moves back
                undoHelper->focus = focus->messageNum;
                
                if (focus == list) {
                    undoHelper->blank = true;
                    break;
                }
                
                if (mode == PTREE) {
                    focus->focus = false;
                    focus = sherlock(list, focus->inReplyTo);
                    focus->focus = true;
                } else {
                    focus -> focus = false;
                    focus = sherlock(list, ((focus -> messageNum) - 1));
                    focus -> focus = true;
                    
                }
                
                printExpected(list, head, focus, printType);
                
                break;
            
            case 'p':
                //prints the thingos
                undoHelper->printType = printType;
                
                printFull( focus );
                printType = PFULL;
                break;
                
            case 'l':
                //lists the thingos
                undoHelper->printMode = mode;
                undoHelper->printType = printType;
                
                printList( list );
                printType = mode = PLIST;
                
                break;
                
            case 'h':
                // Help Me!
                printHelp();
                break;
                
            case 'd':
                //delete message
                focus -> deleted = true;
                printExpected(list, head, focus, printType);
                break;
            
            case 'r':
                //reply to a message
                undoHelper->focus = focus->messageNum;
                focus = addReply(list, focus);
                relinker(head, focus);
                printExpected(list, head, focus, printType);
                break;
            
            case 't':
                //toggle t mode
                undoHelper->printMode = mode;
                undoHelper->printType = printType;
                if (list != NULL) {
                    printTree(head);
                }
                
                printType = mode = PTREE;
                break;
            
            case 's':
                searchNodes(list, getString());
                break;
            
            case 'u':
                //(A,B,F,P,L,D,R,T,)
                if (undoHelper->blank == true) {
                    undoHelper->blank = false;
                    break;
                } else if (undoHelper->command == 'a' || undoHelper->command == 'r') {
                    focus->focus = false;
                    node = focus->next;
                    int beforeFocus = bloodhound(head, focus->messageNum)->prev->msgID;
                    
                    if (focus->messageNum != globalMessageNum) {
                        bloodhound(head, focus->messageNum)->next->prev =
                            bloodhound(head, focus->messageNum)->prev;
                        //
                        bloodhound(head, focus->messageNum)->prev->next =
                            bloodhound(head, focus->messageNum)->next;
                    }
                    
                    free(bloodhound(head, focus->messageNum));
                    bloodhound(head, beforeFocus)->next = NULL;
                    
                    free(focus);
                    focus = sherlock(list, undoHelper->focus);
                    focus->focus = true;
                    focus->next = node;
                    globalMessageNum--;
                } else if (undoHelper->command == 'b' ||
                           undoHelper->command == 'f' ||
                           isdigit(undoHelper->command)) {
                    focus->focus = false;
                    focus = sherlock(list, undoHelper->focus);
                    focus->focus = true;
                } else if (undoHelper->command == 'p' ||
                           undoHelper->command == 'l'||
                           undoHelper->command == 't') {
                    printType = undoHelper->printType;
                    mode = undoHelper->printMode;
                } else if (undoHelper->command == 'd') {
                    focus->deleted = false;
                }
                
                printExpected(list, head, focus, printType);
                
                break;
            case 'q':
                // Quit
                freeList( list );
                printf("Bye!\n");
                return 0;
                break;
        }
        
        undoHelper->command = tolower(c);
        putchar('\n');
        printPrompt();
    }
    
    return 0;
}

// INSERT NEW FUNCTIONS, AS APPROPRIATE

//New functions go here!!


//Alans functions below.

/************************************************************
 Print prompt only if output goes to screen
 */
void printPrompt()
{
    if (isatty(fileno(stdin))) {
        printf("Enter command (A,F,B,P,L,D,R,T,S,U,Q, H for Help): ");
    }
}

/************************************************************
 Print the list of commands available to the user,
 and a brief summary of what each command does.
 */
void printHelp()
{
    printf("\n");
    printf(" A - Add\n" );
    printf(" L - List\n" );
    printf(" P - Print\n" );
    printf(" F - Forward\n" );
    printf(" B - Back\n" );
    printf("<k>- jump to message k\n");
    printf(" D - Delete\n");
    printf(" R - Reply\n");
    printf(" T - Threads\n");
    printf(" S - Search\n");
    printf(" U - Undo\n" );
    printf(" Q - Quit\n");
    printf(" H - Help\n");
    printf("\n");
}

/************************************************************
 allocate space for a new message and get the
 name, date, time and text from standard input.
 */
MsgNode getNode( void )
{
    MsgNode newNode = calloc(1, sizeof(struct msgNode));
    
    if( newNode == NULL ) {
        printf("Error: could not allocate memory.\n");
        exit( 1 );
    }
    newNode->messageNum = ++globalMessageNum;
    newNode->name       = getName();
    newNode->date = calloc(1, sizeof(struct date));
    getDate( newNode->date );
    newNode->time = calloc(1, sizeof(struct time));
    getTime( newNode->time );
    newNode->text       = getText();
    return( newNode );
}

/************************************************************
 Read one line of text from standard input,
 store it in a string and return a pointer to the string.
 */
char * getName( void )
{
    char buffer[MAX_LINE];
    char *name;
    int length;
    int ch;
    int i;
    
    // prompt user for input
    printf( "Name: " );
    // skip any intial newline character
    if(( ch = getchar()) == '\n' ) {
        ch = getchar();
    }
    // read text initially into a buffer
    i=0;
    while( i < MAX_LINE && ch != '\n' && ch != EOF ) {
        buffer[i++] = ch;
        ch = getchar();
    }
    // trim of any trailing whitespace
    while( isspace( buffer[i-1] )) {
        i--;
    }
    // allocate just enough space to store the string
    length = i;
    name = (char *)malloc((length+1)*sizeof(char));
    if( name == NULL ) {
        printf("Error: could not allocate memory.\n");
        exit( 1 );
    }
    // copy text from buffer into new string
    for( i=0; i < length; i++ ) {
        name[i] = buffer[i];
    }
    name[i] = '\0'; // add end-of-string marker
    
    return( name );
}

/************************************************************
 Read several lines of text from standard input,
 store them in a string and return a pointer to the string.
 */
char * getText( void )
{
    char buffer[MAX_TEXT];
    char *text;
    int length;
    int ch;
    int i;
    
    printf("Text: \n");
    ch = getchar();
    i=0;
    while(( i < MAX_TEXT )&&( ch != EOF )) {
        buffer[i++] = ch;
        ch = getchar();
        // stop when you encounter a dot on a line by itself
        if( i > 1 && ch == '\n' && buffer[i-1] == '.'
           && buffer[i-2] == '\n' ) {
            ch = EOF;
            i  = i-2; // strip off the dot and newlines
        }
    }
    length = i;
    // allocate just enough space to store the string
    text = (char *)malloc((length+1)*sizeof(char));
    if( text == NULL ) {
        printf("Error: could not allocate memory.\n");
        exit( 1 );
    }
    // copy text from buffer to new string
    for( i=0; i<length; i++ ) {
        text[i] = buffer[i];
    }
    text[i] = '\0'; // add end-of-string marker
    
    return( text );
}

/************************************************************
 Get date from standard input;
 if date is invalid, ask the user to re-enter it.
 */
void getDate( Date d )
{
    printf("Date: ");
    while( !scanDate( d ) || !dateOK( d )) {
        printf("Re-enter date in format dd/mm/yy: ");
    }
}

/************************************************************
 scan date in the format dd/mm/yyyy
 */
int scanDate( Date d )
{
    char s[MAX_LINE];
    
    fgets( s, MAX_LINE, stdin );
    if(sscanf(s,"%d/%d/%d",&d->day,&d->month,&d->year)<3){
        return false;
    }
    if( d->year < 100 ) { // turn /12 into /2012, etc.
        d->year = 2000 + d->year;
    }
    return true;
}

/************************************************************
 Get time from standard input;
 if time is invalid, ask the user to re-enter it.
 */
void getTime( Time t )
{
    printf("Time: ");
    while( !scanTime( t ) || !timeOK( t )) {
        printf("Re-enter time in format hh:mm:ss: ");
    }
}

/************************************************************
 scan time in the format hh:mm:ss
 */
int scanTime( Time t )
{
    char s[MAX_LINE];
    
    fgets( s, MAX_LINE, stdin );
    return(
           sscanf(s,"%d:%d:%d",&t->hour,&t->minute,&t->second)==3);
}

/************************************************************
 Return TRUE if date is valid; FALSE otherwise.
 */
int dateOK( Date d )
{
    
    if (d->day <= 0||d->month <= 0||d->year < 0) {
        return false;
    }
    
    if (d->month > 12) {
        return false;
    }
    
    switch (d->month) {
        case 4: case 6: case 9: case 11:
            if (d->day>30) {
                return false;
            }
            break;
        case 2:
            if (isLeapYear(d->year)) {
                if (d->day > 29) {
                    return false;
                }
            } else if (d->day > 28) {
                return false;
            }
            break;
        default:
            if (d->day > 31) {
                return false;
            }
            break;
    }
    
    return true;
}

/************************************************************
 Return TRUE if time is valid; FALSE otherwise.
 */
int timeOK( Time t )
{
    return(   t->hour   >= 0 && t->hour   < 24
           && t->minute >= 0 && t->minute < 60
           && t->second >= 0 && t->second < 60 );
}

// INSERT NEW FUNCTIONS, AS APPROPRIATE

/************************************************************
 Print the specified integer in two digits
 (prefixed with '0' if necessary)
 */
void printPadded( int n )
{
    if( n < 10 ) {
        putchar('0');
    }
    printf("%d",n );
}

/************************************************************
 Print date in the format dd/mm/yyyy
 */
void printDate( Date d )
{
    printPadded( d->day );
    putchar('/');
    printPadded( d->month );
    putchar('/');
    printf("%d", d->year );
}

/************************************************************
 Print time in the format hh:mm:ss
 */
void printTime( Time t )
{
    printPadded( t->hour );
    putchar(':');
    printPadded( t->minute );
    putchar(':');
    printPadded( t->second );
}

/************************************************************
 Print the Name, followed by the first line of the Text.
 */
void printBrief( MsgNode msg , bool t)
{
    char *text=msg->text;
    int i=0,j=0;
    printf("%d ", msg->messageNum);
    if( msg->deleted ) {
        printf("[deleted]\n");
    }
    else {
        if (t == true) {
            printIndent(msg -> indent);
        }
        printf("%s: ", msg->name );
        while( isspace( text[i] )) {
            i++;
        }
        while( j < 40 && text[i+j] != '\0'
              && text[i+j] != '\n' ) {
            putchar( text[i+j] );
            j++;
        }
        putchar('\n');
    }
}

/************************************************************
 Print message in Full
 */
void printFull( MsgNode msg )
{
    if( msg != NULL ) {
        printf("Message %d", msg->messageNum );
        if( msg->deleted ) {
            printf(" has been deleted.\n");
        }
        else {
            printf("\nDate: ");
            printDate( msg->date );
            printf("\nTime: ");
            printTime( msg->time );
            printf("\nName: %s\n", msg->name );
            printf("Text: %s\n", msg->text );
        }
    }
}

/************************************************************
 Free all memory occupied by linked list of messages
 */
void freeList( MsgNode head )
{
    MsgNode node;
    while( head != NULL ) {
        node = head;
        head = head->next;
        free( node->name );
        free( node->text );
        free( node );
    }
}

// Local Variables:
// c-basic-offset: 4
// End: