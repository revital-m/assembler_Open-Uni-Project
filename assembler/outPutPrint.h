/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#ifndef OUTPUTPRINT_H
#define OUTPUTPRINT_H

/***************************************************** extern necessary for data *****************************************************/
extern cmdInfo commandArr[];
extern int entryLabelCounter;
extern int labelArrCounter;

/***************************************************** Functions declaration *****************************************************/

/* Print object file ,address and code in hexadecimal base. */
void printObFile(char *, int , int , printInfo *);

/* Print all command numbers in base 16 and their address to file. */
void printCodeBase16(FILE *, printInfo *, int );

/* Print all directive numbers in base 16 and their address to file. */
void printDataBase16(FILE *, printInfo *, int , int );

/* Print the number in base 16, one byte at a time to file. */
void printOneByte(FILE *, int *, int , int *, int , int , numToPrint *);

/* Check if needed to print Address or a Space char to file. */
void printAddressOrSpace(FILE *, int , int , int , int );

/* Creates the external file, with label and address for every extern label. */
void printExtFile(char *, ptrlines , int , labelInfo *);

/* Creates the entry file, with label and address for every entry label. */
void printEntFile(char *, labelInfo *);

/* Creates a file name using file prefix and suffix. Return a pointer to the file. */
FILE *openNewFile(char *, char *, const char *);

/* Find if cmdName is a command in commandArr. Return the idx of that command in commandArr, else return -1. */
int findInCmdArr(char *);

/* Check if the label alreay exists. Return a pointer to label name in labelArr if exists, else return NULL. */
labelInfo *existInLabelArr(char *, labelInfo *);

#endif
