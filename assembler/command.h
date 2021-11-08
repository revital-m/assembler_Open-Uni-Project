/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#ifndef COMMAND_H
#define COMMAND_H

/***************************************************** Functions declaration *****************************************************/

/* Find all operands the command has, and save their values in linesList. */
void findAllCmdOperands(lineInfo *, int , char *);

/* Define the types of all operands the command has, and save in linesList. */
void defineTypeAllOperands(lineInfo *, int , char *);

/* Check if ',' is missing between 2 operands.*/
void isMissingCommaCode(boolean *, lineInfo *, int , int , char *);

/* Check if the operand is valid, and save it in linesList (except for the type label that will be saved in the second pass). */
void isValidOperand(lineInfo *, opInfo *, int , int , char *);

/* Read and check if operand is a valid register and save it's value. Return true if is valid, else return false. */
boolean readOperandTypeReg(opInfo *, int );

/* Read and check if operand is a valid label. Return true if is valid, else return false. */
boolean readOperandTypeLabel(opInfo *, int , int , char *);

/* Read and check if operand is a valid number and save it's value. Return true if is valid, else return false. */
boolean readOperandTypeNum(opInfo *, int , char *, boolean , boolean , char *);

/* Check if the operand value is a valid register name. Return true if it is, else return false. */
boolean isValidReg(char *);

/* Find if cmdName is a command in commandArr. Return the idx of that command in commandArr, else return -1. */
int findInCmdArr(char *);

/* Remove white-space characters left of string. */
void removeWhiteCharsLeft(char **);

/* Check if the label is legal. Return true if it is legal, else return false. */
boolean isValidLabel(char *, int , boolean , char *);

/* Return ture if str contains only white-space characters, else return false. */
boolean whiteCharsOnly(char *);

/* Find the Next operand and return it. */
char *findNextOperand(char *, char **, boolean *);

/* Check if the number is a legal number for thet specific operand, and save it's value in *operandValue. Return true if it is legal, else return false. */
boolean isValidNumber(char *, int , long int *, char *, opTypes , boolean , boolean , char *);

#endif
