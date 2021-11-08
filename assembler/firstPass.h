/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#ifndef FIRSTPASS_H
#define FIRSTPASS_H

/***************************************************** extern necessary for data *****************************************************/
extern int labelArrCounter;

/***************************************************** Functions declaration *****************************************************/

/* Inserts one line from 'file' into 'buffer'. Return true if the line is shorter than maxLength, else return false. */
boolean getLine(FILE *, char *, size_t , int , char *);

/* Read the line, check if label exist and add it to labelArr as needed, call for diractive or command and print errors. */
void readAndParseLine(lineInfo *, char *, int , int *, int *, char *, labelInfo *, dataToPrint **);

/* Check if the 'line' is a comment or empty. Return true if the 'line' is a comment or empty, else return false. */
boolean isLineCommentOrEmpty(lineInfo *);

/* Find label if exists and add it to label array. Return a pointer to the next char after the label or null if there is no label. */
char *findLabel(lineInfo *, char *, labelInfo *);

/* Check if the line is a command or directive line, and read it. */
void isLineCmdOrDir(lineInfo *, char *, int *, int *, char *, labelInfo *, dataToPrint **);

/* Find next segment in line- command or diractive, and return it. */
char *findCmdOrDir(char *, char **);

/* Find the currect command, and oprends if exist ,else ilegal command. */
void findCmd(lineInfo *, int *, int *, char *);
 
/* Find the currect directive, else ilegal directive. */
void findDir(lineInfo *, int *, int *, char *, labelInfo *, dataToPrint **);

/* Remove white-space characters left of string. */
void removeWhiteCharsLeft(char **);

/* Add the label to labelArr if the process was successful return pointer to the label, else return NULL. */
labelInfo *addToLabelArr(labelInfo *, lineInfo *, char *, labelInfo *); 

#endif
