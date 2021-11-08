/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define FIRST_ADDRESS 100
#define MAX_LINE_LENGTH 80
#define SIZE_LABEL_ARRAY 3
#define MAX_MEMORY_ADDRESS (pow(2,25))			/* 2^25 byte max memory for address. */
#define MAX_LABEL_LENGTH 31
#define NUM_OF_CMD 27
#define NUM_OF_DIR 6
#define MAX_DB_VALUE ((int)((pow(2,8))/2))		/* (2^8)/2 bits max number for .db */
#define MAX_DH_VALUE ((int)((pow(2,16))/2)) 		/* (2^16)/2 bits max number for .dh */
#define MAX_DW_VALUE ((pow(2,32))/2)			/* (2^32)/2 bits max number for .dw */
#define NUM_OF_SAVE_WORDS ((NUM_OF_CMD) + (NUM_OF_DIR))
#define MAX_LENGTH_SAVE_WORD 6


typedef enum { FALSE = 0, TRUE = 1} boolean;

/***************************************************** operands *****************************************************/

typedef enum { NUMBER = 4, LABEL = 5, REGISTER = 6, REG_OR_LABEL = 7, NOT_IN_USE = 0} opTypes;

typedef struct{
	long int value;			/* value of operand */
	char *str;			/* string of name */
	opTypes type;			/* number/label/register/regOrLable/notInUse */
	int address;			/* address of operand */
} opInfo;



/***************************************************** commands *****************************************************/

typedef enum { R = 1, I = 2, J = 3} cmdTypes;

typedef union regCommand{

	/*struct of R type command*/
	struct{
		unsigned int notUsed : 6;
		unsigned int funct : 5;
		unsigned int rd : 5;
		unsigned int rt : 5;
		unsigned int rs : 5;
		unsigned int opCode : 6;
	
	}RCommand;

	/*struct of I type command*/
	struct{
		signed int immed :16;
		unsigned int rt : 5;
		unsigned int rs : 5;
		unsigned int opCode : 6;
	
	}ICommand;
	
	/*struct of J type command*/
	struct{
		unsigned int address : 25;
		unsigned int reg : 1;
		unsigned int opCode : 6;
	
	}JCommand;

	unsigned int number; 		/* save the word as an int number */

}commandTypes;

/* struct for command array. */
typedef struct{
	 char *name;			/* name of command */
	 int numOfParams;		/* number of parameters command use */
	 cmdTypes type; 		/* type of the command R/I/J in decimal */
	 int opCodeCommand; 		/* opCode in decimal */
	 int functCommand; 		/* funct (R) in decimal */
	 int regCommand; 		/* reg (J) in decimal */
} cmdInfo;



/***************************************************** data *****************************************************/

typedef enum { ONE_BYTE = 1, TWO_BYTE = 2, FOUR_BYTE = 4} addAddress; 

typedef enum { DB = 8, DH = 9, DW = 10, ASCIZ = 11, NOT_USED = 0} dirTypes;

/* struct of data numbers in binary. */
typedef union regData{

	signed int dbLength : 8;

	signed int dhLength : 16;

	signed int dwLength : 32;

	signed int asciiLength : 8;

}dataTypes;

/* struct for data array. */
typedef struct {

	int dataLengthToPrint;
	dirTypes dataTypeToPrint;

}dataToPrint;



/***************************************************** label *****************************************************/

/* struct for label array. */
typedef struct{

	int address;			/* The address of label */
	char name[MAX_LABEL_LENGTH+1];	/* +1 for The last '\0' */
	boolean isExtern;		/* Extern */
	boolean isEntry;   		/* Entry */
	boolean isData;			/* Data */
	boolean isCode;  		/* Code */
	int lineNum;  			/* line number */

} labelInfo;



/***************************************************** line *****************************************************/

/* struct for line. */
typedef struct{

	int lineNum;			/* The number of the line in the file */
	int address;			/* The address of the first word in the line */
	char *lineString;		/* The text of line */
        char *mallocStr;		/* Pointer to free the string in the end of use */
	boolean isError;		/* Is Error in line or not */
	labelInfo *label;		/* A poniter to the line's label in labelArr */
	char *cmdOrDirStr;		/* The string of the command or directive */
	boolean isData;			/* the line is Data */
	boolean isCode;			/* the line is Code */
	opInfo firstOp;			/* the first operand for command */
	opInfo secondOp;		/* the second operand for command */
	opInfo thirdOp;			/* the third operand for command */

} lineInfo;

/* linked list for the lines. */
typedef struct nodelines * ptrlines;

typedef struct nodelines {

	lineInfo linesList;
	ptrlines next;

} itemlines;



/***************************************************** print *****************************************************/

/* struct for print array. */
typedef struct{

	int number;			/* The number to print. */
	dirTypes dataLine;		/* If the line is a data line it save the type of dir. */

} printInfo; 


/* print struct */
typedef union {

	unsigned int binaryNumLength :32;
	unsigned char oneByte[4];

}numToPrint;

#endif
