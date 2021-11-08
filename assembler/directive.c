/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#include "assembler.h"
#include "directive.h"

/***************************************************** code segment *****************************************************/

/* Find the currect directive, else ilegal directive. */
void findDir(lineInfo *line, int *IC, int *DC, char *fileName, labelInfo *labelArr, dataToPrint **headDataArr){


  	if ((strcmp(line->cmdOrDirStr, "db") == 0) || (strcmp(line->cmdOrDirStr, "dh") == 0) || (strcmp(line->cmdOrDirStr, "dw") == 0)) {

		/* Read the data of the .db/.dh/.dw directive from the line and add it to data array. */
		readDbDhDw(line, IC, DC, fileName, headDataArr);
	}
	 else if(strcmp(line->cmdOrDirStr, "asciz") == 0){

		/* Read the data of the .asciz directive from the line and add it to data array. */
		readAsciz(line, IC, DC, fileName, headDataArr);
	}
	else if(strcmp(line->cmdOrDirStr, "extern") == 0){

		/* Read the data of the .extern directive from the line and add it to label array. */
		readExtern(line, fileName, labelArr);
	}
	 else if(strcmp(line->cmdOrDirStr, "entry") == 0){

		/* Read the data of the .entry directive from the line and add it to label array. */
		readEntry(line, fileName, labelArr); 
	}
	else{
		printf("[Error: File- \"%s.as\", line - %d] Ilegal directive. \n",fileName, line -> lineNum);
		line -> isError  = TRUE;
 	}
}


/* Read the data of the .db/.dh/.dw directive from the line and add it to data array. */
void readDbDhDw(lineInfo *line, int *IC, int *DC, char *fileName, dataToPrint **headDataArr){

	char *operand = line->lineString, *endOfOp = line->lineString;
	int operandValue;
	boolean isAnotherOperand;

	/* Label is a data label. */
	if (line->label){
	 	line->label->isData = TRUE;
   		line->label->address = *DC;
  	}

	/* Check if there are no parameters. */
	if (whiteCharsOnly(line->lineString)){

		printf("[Error: File- \"%s.as\", line - %d] No parameter for .%s directive.\n",fileName, line->lineNum, line->cmdOrDirStr);
		line->isError = TRUE;
		return;
	}

	/* Remove white-space characters left of string. */
	removeWhiteCharsLeft(&line -> lineString);

	if(line -> lineString[0] == ','){

		printf("[Error: File- \"%s.as\", line - %d] A comma befor the first operand.\n", fileName, line ->lineNum);
		line -> isError = TRUE;
		return;
	}

	/* Don't stop until break or return. */
	while(1){ 

		/* Check if there are no more operands. */
		if (whiteCharsOnly(line->lineString)){

			break;
		}

		/* Find the next operand. */
		operand = findNextOperand(line->lineString, &endOfOp, &isAnotherOperand);

		/* Check if ',' is missimg. */
		isMissingCommaData(&isAnotherOperand, &endOfOp, fileName, line ->lineNum, &line -> isError);
		if(line->isError){

			return;
		}

		/* Check if the operand value is valid, and if it is, add it to dataArr. */
		if (isValidNumber(operand, line->lineNum, (long int *)&operandValue, line->cmdOrDirStr, NOT_IN_USE, line->isData, line->isCode, fileName)){

			if (!addNumToDataArr(operandValue, IC, DC, line->cmdOrDirStr, fileName, headDataArr, line -> lineNum)){
				
				line->isError = TRUE; /* Not enough memory. */
				return;
			}
		}
		else{
			line->isError = TRUE; /* Illegal number. */
			return;
		}

		/* Change the line to start after the operand. */
		line->lineString = endOfOp;
	}

	/* Comma after the last operand. */
	if (isAnotherOperand){
		
		printf("[Error: File- \"%s.as\", line - %d] Comma after the last parameter.\n",fileName, line -> lineNum);
		line->isError = TRUE;
		return;
	}
}


/* Check if ',' is missing between 2 operands. */
void isMissingCommaData(boolean *isAnotherOperand, char **lineString, char *fileName, int lineNum, boolean *isError){

	if(!(*isAnotherOperand) && !whiteCharsOnly(*lineString)){

		/* Remove white-space characters left of string. */
		removeWhiteCharsLeft(lineString);

		if(((*lineString) != NULL) && ((*lineString)[0] != '\0') && ((*lineString)[0] != '\n')){

			if((*lineString)[0] == ','){

				*isAnotherOperand = TRUE;
				(*lineString)++;

				/* Remove white-space characters left of string. */
				removeWhiteCharsLeft(lineString);
			}
			else {
				printf("[Error: File- \"%s.as\", line - %d] Missimg ','.\n", fileName, lineNum);
				*isError = TRUE;
			}
		}
	}
}


/* Add the operand value as a number to the dataArr and increases DC. Return true if succeeded, else return false. */
boolean addNumToDataArr(int opValueAsNum, int *IC, int *DC, char *cmdOrDirStr, char *fileName, dataToPrint **headDataArr, int lineNum){

	dataToPrint **dataArr = NULL;
	boolean addToDataArr = FALSE;
	dataTypes newData = { 0 };

	if((strcmp(cmdOrDirStr, "db") == 0) || (strcmp(cmdOrDirStr, "asciz") == 0)){ 	 

		/* Check if there is enough memory in the computer and add cells to the data array as needed */
		dataArr = enoughMemory(ONE_BYTE, IC, DC, fileName, headDataArr, lineNum);

		if(*dataArr != NULL){

			/* Add the operand value as a number to the dataArr. */
			addDbOrAscizToDataArr(opValueAsNum, DC, newData, cmdOrDirStr, *dataArr);
			addToDataArr = TRUE;
		}
	}
			
	else if(strcmp(cmdOrDirStr, "dh") == 0){

		/* Check if there is enough memory in the computer and add cells to the data array as needed */
		dataArr = enoughMemory(TWO_BYTE, IC, DC, fileName, headDataArr, lineNum);

		if(*dataArr != NULL){

			/* Add the operand value as a number to the dataArr. */
			addDhToDataArr(opValueAsNum, DC, newData, *dataArr);
			addToDataArr = TRUE;
		}		
	}

	else if(strcmp(cmdOrDirStr, "dw") == 0){

		/* Check if there is enough memory in the computer and add cells to the data array as needed */
		dataArr = enoughMemory(FOUR_BYTE, IC, DC, fileName, headDataArr, lineNum);

		if(*dataArr != NULL){

			/* Add the operand value as a number to the dataArr. */
			addDwToDataArr(opValueAsNum, DC, newData, *dataArr);
			addToDataArr = TRUE;
		}
	}
	return addToDataArr;
}


/* Check if there is enough memory in the computer and add cells to the data array as needed. Return a pointer to dataArr. */
dataToPrint **enoughMemory(addAddress byteToAdd, int *IC, int *DC, char *fileName, dataToPrint **headDataArr, int lineNum){

	dataToPrint **tempData = NULL;
	dataToPrint **dataArr = headDataArr;

	/* Check if there is enough memory in the computer */
	if ((*DC + *IC + FIRST_ADDRESS + (int)byteToAdd) < MAX_MEMORY_ADDRESS){

		tempData = (dataToPrint **)realloc(*headDataArr, (*DC + (int)byteToAdd)*sizeof(dataToPrint)); 
		if (!tempData){ 

			printf("[Error: File- \"%s.as\", line - %d] Memory not allocated.\n", fileName, lineNum);
			return tempData;
		}
		else{
			*headDataArr = (dataToPrint *)tempData;
			*dataArr = (dataToPrint *)tempData;
		}
	}
	else {
		printf("[Error: File- \"%s.as\"] Reach max Memory of the computer.\n", fileName);
		return tempData;
	}
	return dataArr;
}


/* Add the operand value, as a number in 8 bits, to the dataArr and increases DC. */
void addDbOrAscizToDataArr(int opValueAsNum, int *DC, dataTypes newData, char *cmdOrDirStr, dataToPrint *dataArr){

	/* Create the data to add. */
	newData.dbLength = opValueAsNum;

	/* Add the data to the dataArr. */
	dataArr[(*DC)].dataLengthToPrint = newData.dbLength;

	if(strcmp(cmdOrDirStr, "db") == 0){

		dataArr[(*DC)].dataTypeToPrint = DB;
	}

	else if(strcmp(cmdOrDirStr, "asciz") == 0){

		dataArr[(*DC)].dataTypeToPrint = ASCIZ;
	}

	*DC += 1;
}


/* Add the operand value, as a number in 16 bits, to the dataArr and increases DC. */
void addDhToDataArr(int opValueAsNum, int *DC, dataTypes newData, dataToPrint *dataArr){

	/* Create the data to add. */
	newData.dhLength = opValueAsNum;

	/* Add the data to the dataArr. */
	dataArr[(*DC)].dataLengthToPrint = newData.dhLength;
	dataArr[(*DC)].dataTypeToPrint = DH;
	*DC += 2;
}


/* Add the operand value, as a number in 32 bits, to the dataArr and increases DC. */
void addDwToDataArr(int opValueAsNum, int *DC, dataTypes newData, dataToPrint *dataArr){

	/* Create the data to add. */
	newData.dwLength = opValueAsNum;

	/* Add the data to the dataArr. */
	dataArr[(*DC)].dataLengthToPrint = newData.dwLength;
	dataArr[(*DC)].dataTypeToPrint = DW; 
	*DC += 4;
}


/* Read the data of the .asciz directive from the line and add it to data array. */
void readAsciz(lineInfo *line, int *IC, int *DC, char *fileName, dataToPrint **headDataArr){

	/* Make the label a data label (if there is one). */
	if (line->label){

		line->label->isData = TRUE;
		line->label->address = *DC;
	}

	/* Remove white-space characters left and right of string. */
	removeWhiteCharsLeft(&line->lineString);
	removeWhiteCharsRight(&line->lineString);

	if (isValidString(&line->lineString, line->lineNum, fileName)){

		char* str = line -> lineString;
		do{
			if (!addNumToDataArr((int)*str, IC, DC, line->cmdOrDirStr, fileName, headDataArr, line->lineNum)){

				line->isError = TRUE;
				return;
			}
		}/* Until the end of the string. */
		while (*str++);
	}
	else{
		line->isError = TRUE;
	}
}


/* Check if the string is enclosed in quotes, and that the string inside the quotes is printable. Return true if valid, else return false. */
boolean isValidString(char **strOperand, int lineNum, char *fileName){

	char * strCheck = NULL;
	int i;

	/* Check if the string operand is enclosed in quotes. */
	if ((*strOperand)[0] == '"' && (*strOperand)[strlen(*strOperand) - 1] == '"'){

		/* Remove the quotes. */
		(*strOperand)[strlen(*strOperand) - 1] = '\0';
		++*strOperand;
		
		strCheck = *strOperand;
		/* Check if the string inside the quotes is printable. */
		for(i = 0; i < strlen(*strOperand) ; i++){

			if(isprint(strCheck[i]) == 0){

				printf("[Error: File- \"%s.as\", line - %d] Invalid string.\n", fileName, lineNum);
				return FALSE;
			}
		}
		return TRUE;
	}
	else{
		printf("[Error: File- \"%s.as\", line - %d] String must be enclosed in quotes.\n", fileName, lineNum);
	}

	return FALSE;
}


/* Read the data of the .extern directive from the line and add it to label array. */
void readExtern(lineInfo *line, char *fileName, labelInfo *labelArr){

	labelInfo newLabel = { 0 }, *ptrLabel;

	/* If there was a label in the begining of the line, remove it from labelArr. */
	if (line->label){

		labelArrCounter--;
		printf("[Warning: File- \"%s.as\", line - %d] The program ignore the label before the .extern directive .\n", fileName, line -> lineNum);
	}

	/* Remove white-space characters left and right of string. */
	removeWhiteCharsLeft(&line -> lineString);
	removeWhiteCharsRight(&line -> lineString);

	ptrLabel = addToLabelArr(&newLabel, line, fileName, labelArr);

	/* Check if the label is an entry label already. */
	if (!line->isError && ptrLabel->isEntry){

		printf("[Error: File- \"%s.as\", line - %d] Entry label - \"%s\", can't be an extern label as well.\n",fileName, line -> lineNum, ptrLabel->name);
		line->isError = TRUE;
	}

	/* Make the label an extern label */
	if (!line->isError){

		ptrLabel->address = 0;
		ptrLabel->isExtern = TRUE;
		ptrLabel->lineNum = line -> lineNum;
	}
}


/* Read the data of the .entry directive from the line and add it to label array. */
void readEntry(lineInfo *line, char *fileName, labelInfo *labelArr){

	labelInfo newLabel = { 0 }, *ptrLabel;

	/* If there was a label in the begining of the line, remove it from labelArr. */
	if (line->label){

		labelArrCounter--;
		printf("[Warning: File- \"%s.as\", line - %d] The program ignore the label before the .entry directive.\n", fileName, line -> lineNum);
	}

	/* Remove white-space characters left and right of string. */
	removeWhiteCharsLeft(&line -> lineString);
	removeWhiteCharsRight(&line -> lineString);

	if ((isValidLabel(line->lineString, line->lineNum, TRUE, fileName)) && (line -> lineString)){

		ptrLabel =existInLabelArr(line -> lineString, labelArr);

		if(!ptrLabel){

			ptrLabel = addToLabelArr(&newLabel, line, fileName, labelArr);
		}

		/* Check if the label is an extern label already. */
		if (!line->isError && ptrLabel->isExtern){

			printf("[Error: File- \"%s.as\", line - %d] Extern label - \"%s\", can't be an entry label as well.\n",fileName, line -> lineNum, ptrLabel->name);
			line->isError = TRUE;
		}

		/* Make the label an entry label */
		if (!line->isError){

			ptrLabel->isEntry = TRUE;
			ptrLabel->lineNum = line -> lineNum;
			entryLabelCounter++;
		}
	}
}

