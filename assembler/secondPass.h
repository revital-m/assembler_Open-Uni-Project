/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#ifndef SECONDPASS_H
#define SECONDPASS_H

/***************************************************** extern necessary for data *****************************************************/
extern int labelArrCounter;
extern cmdInfo commandArr[];

/***************************************************** Functions declaration *****************************************************/

/* Check if the entry / extern labels are legal. Return true if legal, else return false. */
boolean isValidEntryAndExtern(char *, labelInfo *);

/* Add the code lines to printArr. Return true if there were no errors, else return false. */
boolean addCodeLineToPrintArr(printInfo *, int *, lineInfo *, char *, labelInfo *);

/* Set the value of lable opernads as needed, if label exist and legal. Return true if there were no errors, else return false. */
boolean setLableOperandValue(opInfo *, int , char *, int , char *, labelInfo *);

/* Save the command line as a binary number (32-bit) and return it. */
commandTypes setCmdNum(lineInfo , char *);

/* Save the type R command as a binary number (32-bit) and return it. */
commandTypes setCmdTypeR(lineInfo , int );

/* Save the type I command as a binary number (32-bit) and return it. */
commandTypes setCmdTypeI(lineInfo , int );

/* Save the type J command as a binary number (32-bit) and return it. */
commandTypes setCmdTypeJ(lineInfo , int );

/* Add all data to printArr. */
void addDataToPrintArr(printInfo *, int *, int , dataToPrint *);

/* Check if the label is legal. Return true if it is legal, else return false. */
boolean isValidLabel(char *, int , boolean , char *);

/* Find if cmdName is a command in commandArr. Return the idx of that command in commandArr, else return -1. */
int findInCmdArr(char *);

/* Check if the label alreay exists. Return a pointer to label name in labelArr if exists, else return NULL. */
labelInfo *existInLabelArr(char *, labelInfo *);

#endif
