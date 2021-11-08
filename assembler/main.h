/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#ifndef MAIN_H
#define MAIN_H

/***************************************************** Functions declaration *****************************************************/

/* Read the given file: call for firstPass and secondPass, and create output files if needed. */
void readFile(char *);

/* Resets all the globals and free all the calloc blocks. */
void resetForNextFile(printInfo *, ptrlines *, labelInfo *, dataToPrint *);
  
/* Print all the files assembler requires. */
void printFiles(char *, int , int , printInfo *, ptrlines , int , labelInfo *);

/* Reading the file for the Second time, line by line. Check if entry/extern labels are legal. Set lable operands values as needed. Update address for data in labelArr. Add all code lines and dataArr to printArr. Return true if there were no errors, else return false. */
boolean secondPass(printInfo *, ptrlines , int , int , int , char *, labelInfo **, dataToPrint *);

/* Reading the file for the first time, line by line, and parse it. Return true if non of the lines had errors, else return false. */ 
boolean firstPass(FILE *, ptrlines *, int *, int *, int *, char *, labelInfo **, dataToPrint **);

/* Creates a file name using file prefix and suffix. Return a pointer to the file. */
FILE *openNewFile(char *, char *, const char *);

#endif
