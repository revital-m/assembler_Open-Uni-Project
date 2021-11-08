/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#ifndef DIRECTIVE_H
#define DIRECTIVE_H

/***************************************************** extern necessary for data *****************************************************/
extern int labelArrCounter;
extern int entryLabelCounter;

/***************************************************** Functions declaration *****************************************************/

/* Read the data of the .db/.dh/.dw directive from the line and add it to data array. */
void readDbDhDw(lineInfo *, int *, int *, char *, dataToPrint **);

/* Add the operand value as a number to the dataArr and increases DC. Return true if succeeded, else return false. */
boolean addNumToDataArr(int , int *, int *, char *, char *, dataToPrint **, int );

/* Check if there is enough memory in the computer and add cells to the data array as needed. Return a pointer to dataArr. */
dataToPrint **enoughMemory(addAddress , int *, int *, char *, dataToPrint **, int );

/* Add the operand value, as a number in 8 bits, to the dataArr and increases DC. */
void addDbOrAscizToDataArr(int , int *, dataTypes , char *, dataToPrint *);

/* Add the operand value, as a number in 16 bits, to the dataArr and increases DC. */
void addDhToDataArr(int , int *, dataTypes , dataToPrint *);

/* Add the operand value, as a number in 32 bits, to the dataArr and increases DC. */
void addDwToDataArr(int , int *, dataTypes , dataToPrint *);

/* Read the data of the .asciz directive from the line and add it to data array. */
void readAsciz(lineInfo *, int *, int *, char *, dataToPrint **);

/* Check if the string is enclosed in quotes, and that the string inside the quotes is printable. Return true if valid, else return false. */
boolean isValidString(char **, int , char *);

/* Read the data of the .extern directive from the line and add it to label array. */
void readExtern(lineInfo *, char *, labelInfo *);

/* Read the data of the .entry directive from the line and add it to label array. */
void readEntry(lineInfo *, char *, labelInfo *);

/* Check if ',' is missing between 2 operands. */
void isMissingCommaData(boolean *, char **, char *, int , boolean *);

/* Remove white-space characters left of string. */ /* (firstPass, directive, command, tools) (in: tools) */
void removeWhiteCharsLeft(char **);

/* Remove white-space characters right of string. */ /* (directive, tools) (in: tools)*/
void  removeWhiteCharsRight(char **);

/* Add the label to labelArr if the process was successful return pointer to the label, else return NULL. */
labelInfo *addToLabelArr(labelInfo *, lineInfo *, char *, labelInfo *); 

/* Check if the label is legal. Return true if it is legal, else return false. */
boolean isValidLabel(char *, int , boolean , char *);

/* Check if the label alreay exists. Return a pointer to label name in labelArr if exists, else return NULL. */
labelInfo *existInLabelArr(char *, labelInfo *);

/* Return ture if str contains only white-space characters, else return false. */
boolean whiteCharsOnly(char *);

/* Find the Next operand and return it. */
char *findNextOperand(char *, char **, boolean *);

/* Check if the number is a legal number for thet specific operand, and save it's value in *operandValue. Return true if it is legal, else return false. */
boolean isValidNumber(char *, int , long int *, char *, opTypes , boolean , boolean , char *);

#endif
