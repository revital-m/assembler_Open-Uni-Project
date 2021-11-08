/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#include"assembler.h"
#include "command.h"

/***************************************************** global data *****************************************************/
/* name of command, number of parameters command use, type of the command R/I/J in decimal, opCode in decimal, funct (R) in decimal, reg (J) in decimal.
	 -1 = dose'nt exist in this type, -2 = changeble. */

cmdInfo commandArr[] =
	{{"add",3 ,R ,0 , 1, -1 } ,
	{ "sub",3 ,R ,0 , 2, -1 } ,
	{ "and",3 ,R ,0 , 3, -1 } ,
	{ "or",3 ,R ,0 , 4, -1 } ,
	{ "nor",3 ,R ,0 , 5, -1 } ,
	{ "move",2 ,R ,1 , 1, -1 } ,
	{ "mvhi",2 ,R ,1 , 2, -1 } ,
	{ "mvlo",2 ,R ,1 , 3, -1 } ,
	{ "addi",3 ,I ,10 , -1, -1 } ,
	{ "subi",3 ,I ,11 , -1, -1 } ,
	{ "andi",3 ,I ,12 , -1, -1 } ,
	{ "ori",3 ,I ,13 , -1, -1 } ,
	{ "nori",3 ,I ,14 , -1, -1 } ,
	{ "bne",3 ,I ,15 , -1, -1 } ,
	{ "beq",3 ,I ,16 , -1, -1 } ,
	{ "blt",3 ,I ,17 , -1, -1 } ,
	{ "bgt",3 ,I ,18 , -1, -1 } ,
	{ "lb",3 ,I ,19 , -1, -1 } ,
	{ "sb",3 ,I ,20 , -1, -1 } ,
	{ "lw",3 ,I ,21 , -1, -1 } ,
	{ "sw",3 ,I ,22 , -1, -1 } ,
	{ "lh",3 ,I ,23 , -1, -1 } ,
	{ "sh",3 ,I ,24 , -1, -1 } ,
	{ "jmp",1 ,J ,30 , -1, -2 } ,
	{ "la",1 ,J ,31 , -1, 0 } ,
	{ "call",1 ,J ,32 , -1, 0 } ,
	{ "stop",0 ,J ,63 , -1, 0 } };

/***************************************************** code segment *****************************************************/

/* Find the currect command, and oprends if exist ,else ilegal command. */
void findCmd(lineInfo *line, int *IC, int *DC, char *fileName){

	int cmdIdx;

	/* Search command in commandArr. */
	cmdIdx = findInCmdArr(line -> cmdOrDirStr);

	/* Check if command is ilegal command. */
	if (cmdIdx == -1 && *line -> cmdOrDirStr != '\0'){

		printf("[Error: File- \"%s.as\", line - %d] The command \"%s\" is ilegal.\n", fileName, line ->lineNum , line -> cmdOrDirStr);
		line -> isError = TRUE;
		return;
	}

	/* Find all operands if exist. */
	findAllCmdOperands(line, cmdIdx, fileName);

	/* Check if there is enough memory in the computer. */
	if((*DC + *IC + FIRST_ADDRESS + (int)FOUR_BYTE) >= MAX_MEMORY_ADDRESS){

		printf("[Error: File- \"%s.as\", line - %d] Reach max Memory of the computer.\n", fileName, line ->lineNum);
		line -> isError = TRUE;
		return;		
	}
	*IC += 4;
}


/* Find all operands the command has, and save their values in linesList. */
void findAllCmdOperands(lineInfo *line, int cmdIdx, char *fileName){

	char *nextOperand = line -> lineString;
	boolean isAnotherOperand = FALSE;
	int i;

	/* Define the types of all operands the command has, and save in linesList. */
	defineTypeAllOperands(line, cmdIdx, fileName);

	for(i = 0; i < commandArr[cmdIdx].numOfParams ; i++){

		/* If there aren't enough operands. */
		if(whiteCharsOnly(line ->lineString)){

			printf("[Error: File- \"%s.as\", line - %d] Not enough paramters.\n", fileName, line ->lineNum);
			line -> isError = TRUE;
			return;
		}

		/* Find the next operand. */
		if(i == 0){

			/* Remove white-space characters left of string. */
			removeWhiteCharsLeft(&line -> lineString);

			if(line -> lineString[0] == ','){

				printf("[Error: File- \"%s.as\", line - %d] A comma befor the first operand.\n", fileName, line ->lineNum);
				line -> isError = TRUE;
				return;
			}

			line -> firstOp.str = findNextOperand(line -> lineString, &nextOperand ,&isAnotherOperand);
			line -> lineString = nextOperand;

			/* Check if the operand is valid, and save it. */
			isValidOperand(line,&line -> firstOp, i, cmdIdx, fileName);
		}
		else if(i == 1){

			line -> secondOp.str = findNextOperand(line -> lineString, &nextOperand ,&isAnotherOperand);
			line -> lineString = nextOperand;	

			/* Check if the operand is valid, and save it. */
			isValidOperand(line,&line -> secondOp, i, cmdIdx, fileName);	
		}
		else if(i == 2){

			line -> thirdOp.str = findNextOperand(line -> lineString, &nextOperand ,&isAnotherOperand);
			line -> lineString = nextOperand;

			/* Check if the operand is valid, and save it. */
			isValidOperand(line,&line -> thirdOp, i, cmdIdx, fileName);			
		}

		/* Check if ',' is missing. */
		isMissingCommaCode(&isAnotherOperand, line, cmdIdx, i, fileName);

		if(line -> isError == TRUE){
			return;
		}
	}

	/* Check if too many operands. */
	if(!whiteCharsOnly(line ->lineString) || isAnotherOperand){
		printf("[Error: File- \"%s.as\", line - %d] Non white character after last operand. (comma after last opernd / too many paramters).\n", fileName, line ->lineNum);
		line -> isError = TRUE;
	}
}


/* Define the types of all operands the command has, and save in linesList. */
void defineTypeAllOperands(lineInfo *line, int cmdIdx, char *fileName){

	switch (commandArr[cmdIdx].type){

		case R:
			line -> firstOp.type = REGISTER;
			line -> secondOp.type = REGISTER;

			if(commandArr[cmdIdx].numOfParams == 3) {

				line -> thirdOp.type = REGISTER;
			}
			else if(commandArr[cmdIdx].numOfParams == 2) {

				line -> thirdOp.type = NOT_IN_USE;
				line -> thirdOp.value = 0;
			}
			break;

		case I:
			line -> firstOp.type = REGISTER;

			if(commandArr[cmdIdx].opCodeCommand >= 15 && commandArr[cmdIdx].opCodeCommand <= 18 ) {

				line -> secondOp.type = REGISTER;
				line -> thirdOp.type = LABEL;
			}
			else {
				line -> secondOp.type = NUMBER;
				line -> thirdOp.type = REGISTER;
			}
			break;

		case J:
			line -> secondOp.type = NOT_IN_USE;
			line -> secondOp.value = 0;

			line -> thirdOp.type = NOT_IN_USE;
			line -> thirdOp.value = 0;

			if(commandArr[cmdIdx].opCodeCommand == 31 || commandArr[cmdIdx].opCodeCommand == 32 ){

				line -> firstOp.type = LABEL;
			}
			else if(commandArr[cmdIdx].opCodeCommand == 30 ){

				line -> firstOp.type = REG_OR_LABEL;
			}
			else if(commandArr[cmdIdx].opCodeCommand == 63 ){

				line -> firstOp.type = NOT_IN_USE;
				line -> firstOp.value = 0;
			}
			break;

		default : 
			printf("[Error: File- \"%s.as\", line - %d] Command type doesn't exist. \n", fileName, line ->lineNum);
			line -> isError = TRUE;
			return;
	}	
}


/* Check if ',' is missing between 2 operands.*/
void isMissingCommaCode(boolean *isAnotherOperand, lineInfo *line, int cmdIdx, int i, char *fileName){

	if(!(*isAnotherOperand) && !whiteCharsOnly(line-> lineString) && ((i == 0 && ((commandArr[cmdIdx].type == R) || (commandArr[cmdIdx].type == I))) || (i == 1 && (((commandArr[cmdIdx].type == R) && (commandArr[cmdIdx].opCodeCommand == 0)) || (commandArr[cmdIdx].type == I))))){

		/* Remove white-space characters left of string. */
		removeWhiteCharsLeft(&line-> lineString);

		if(line-> lineString){

			if(line-> lineString[0] == ','){

				*isAnotherOperand = TRUE;
				line-> lineString++;

				/* Remove white-space characters left of string. */
				removeWhiteCharsLeft(&line-> lineString);
			}
			else {
				printf("[Error: File- \"%s.as\", line - %d] Missimg ','.\n", fileName, line -> lineNum);
				line -> isError = TRUE;
			}
		}
	}
}


/* Check if the operand is valid, and save it in linesList (except for the type label that will be saved in the second pass). */
void isValidOperand(lineInfo *line, opInfo *operand, int i, int cmdIdx, char *fileName){

	boolean legalRegOp = FALSE;
	boolean legalLabelOp = FALSE;
	boolean legalNumOp = FALSE;

	/* Check if operand is a register. */
	legalRegOp = readOperandTypeReg(operand, cmdIdx);

	if((!legalRegOp) && (i == 0 || i == 2)){

		/* Check if operand is a label. */
		legalLabelOp = readOperandTypeLabel(operand, cmdIdx, line ->lineNum, fileName);

		if(!legalLabelOp){

			printf("[Error: File- \"%s.as\", line - %d] Invalid operand.\n", fileName, line ->lineNum);
			line -> isError = TRUE;
		}
	}
	else if((!legalRegOp) && (i == 1)){

		/* Check if operand is a number. */
		legalNumOp = readOperandTypeNum(operand, line ->lineNum, line->cmdOrDirStr, line->isData, line->isCode, fileName);
		if((!legalNumOp) && (operand->type != NUMBER)){

			printf("[Error: File- \"%s.as\", line - %d] Invalid operand.\n", fileName, line ->lineNum);
			line -> isError = TRUE;
		}
	}
}


/* Read and check if operand is a valid register and save it's value. Return true if is valid, else return false. */
boolean readOperandTypeReg(opInfo *operand, int cmdIdx){

	char *remainStr = NULL; /* Save the remaining string. */
	boolean isReg= FALSE;

	/* Check if operand is a register. */
	if((operand->type == REGISTER) || ((operand->type == REG_OR_LABEL) && (commandArr[cmdIdx].opCodeCommand == 30))){

		/* Check if the operand is a lagal register. */
		if(isValidReg(operand->str)){

			operand->str++;
			operand->value = strtol(operand->str, &remainStr, 0);
			isReg= TRUE;

			if(commandArr[cmdIdx].opCodeCommand == 30){
				operand->type = REGISTER;
			}
		}
	}
	return isReg;
}


/* Read and check if operand is a valid label. Return true if is valid, else return false. */
boolean readOperandTypeLabel(opInfo *operand, int cmdIdx, int lineNum, char *fileName){

	boolean isLabel= FALSE;

	/* Check if operand is a label. */
	if((operand->type == LABEL) || ((operand->type == REG_OR_LABEL) && (commandArr[cmdIdx].opCodeCommand == 30))){

		/* Check if the operand is a lagal label. */
		if(isValidLabel(operand -> str,lineNum, FALSE, fileName)){

			isLabel= TRUE;

			if(commandArr[cmdIdx].opCodeCommand == 30){
				operand->type = LABEL;
			}
		}
	}
	return isLabel;
}


/* Read and check if operand is a valid number and save it's value. Return true if is valid, else return false. */
boolean readOperandTypeNum(opInfo *operand, int lineNum, char *cmdOrDirStr, boolean isData, boolean isCode, char *fileName){

	char *remainStr = NULL; /* Save the remaining string. */
	boolean isNum= FALSE;

	/* Check if operand is a number. */
	if(operand->type == NUMBER){

		/* Check if the operand is a lagal number. */
		if(isValidNumber(operand->str ,lineNum, &operand->value, cmdOrDirStr, operand->type, isData, isCode, fileName)){

			operand->value = strtol(operand->str, &remainStr, 0);
			isNum= TRUE;		
		}
	}
	return isNum;
}


/* Check if the operand value is a valid register name. Return true if it is, else return false. */
boolean isValidReg(char *operandValue){

	if(operandValue[0] == '$'){ 
	
		/* Check if operandValue is equal to registers $0 - $9 */
		if((operandValue[1] -'0' >= 0 ) && (9 >= operandValue[1] - '0') && (operandValue[2] == '\0')){
			return TRUE;
		}

		/* Check if operandValue is equal to registers $10 - $29 */
		else if((operandValue[1] -'0' >= 1 ) && (2 >= operandValue[1] - '0') && (operandValue[2] -'0' >= 0) && (9 >= operandValue[2] - '0') && (operandValue[3] == '\0')){
			return TRUE;
		}

		/* Check if operandValue is equal to registers $30 or $31 */
		else if((operandValue[1] -'0' ==3 ) && ((operandValue[2] -'0' == 0) || (1 == operandValue[2] - '0')) && (operandValue[3] == '\0')){
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}


/* Find if cmdName is a command in commandArr. Return the idx of that command in commandArr, else return -1. */
int findInCmdArr(char *cmdName){

	int i;

	/* Check all the commands in commandArr. */
	for(i = 0; i < NUM_OF_CMD; i++){

		if((cmdName != NULL) && !strcmp(cmdName,commandArr[i].name)){

			return i;
		}
	}
	return -1;
}

