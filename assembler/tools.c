/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#include "assembler.h"
#include "tools.h"

/***************************************************** global data *****************************************************/
char saveWords[NUM_OF_SAVE_WORDS][MAX_LENGTH_SAVE_WORD+1] = {"add","sub","and","or","nor","move","mvhi","mvlo","addi","subi","andi","ori","nori","bne","beq","blt","bgt","lb","sb","lw","sw",
"lh","sh","jmp","la","call","stop","db","dh","dw","asciz","extern","entry"};

/***************************************************** code segment *****************************************************/

/* Creates a file name using file prefix and suffix. Return a pointer to the file. */
FILE *openNewFile(char *prefix, char *suffix, const char *mode){

	FILE *file;
	char *mallocStr, *fileName;

	/* Check if prefix already end with .as */
	if((prefix[strlen(prefix)-3] == '.') && (prefix[strlen(prefix)-2] == 'a') && (prefix[strlen(prefix)-1] == 's')){

		prefix[strlen(prefix)-3] = '\0';
	}
	
	mallocStr = (char *)malloc(strlen(prefix) + strlen(suffix) + 1);
	fileName = mallocStr;
	
	/* file.suffix */
	sprintf(fileName, "%s%s", prefix, suffix);
	
	/* Open file.sufiix*/
	file = fopen(fileName, mode);
	free(mallocStr);

	return file;
}


/* Remove white-space characters left of string. */
void removeWhiteCharsLeft(char **ptrString){

	/* Return if it's NULL. */
	if (!ptrString)
	{
		return;
	}

	/* The start of the text. */
	while(isspace(**ptrString))
	{
		++*ptrString;
	}
}


/* Remove white-space characters right of string. */
void  removeWhiteCharsRight(char **ptrString){

	char *endString = *ptrString + strlen(*ptrString) -1 ;

	/* Remove spaces from the end of the string. */
	while (isspace(*endString) && endString != *ptrString){

		*endString-- = '\0';
	}
}


/* Return ture if str contains only white-space characters, else return false. */
boolean whiteCharsOnly(char *str){

	while (*str){

		if (!isspace(*str++))
		{
			return FALSE;
		}
	}
	return TRUE;
}


/* Add the label to labelArr if the process was successful return pointer to the label, else return NULL. */
labelInfo *addToLabelArr(labelInfo *newLabel, lineInfo *line, char *fileName, labelInfo *labelArr){ 

	labelInfo *isExist; 
	char *startOfLabel = line->lineString;

	/* Remove white-space characters left of label. */ 
	removeWhiteCharsLeft(&startOfLabel);

	/* Check if the label is legal. */
	if (!isValidLabel(startOfLabel, line->lineNum, TRUE, fileName)){

		/* Illegal label name. */
		line->isError = TRUE;
		return NULL;
	}

	/* Check if the label exists already. */
	isExist = existInLabelArr(startOfLabel, labelArr);
	if ((isExist) && !(isExist->isData) && !(isExist->isCode)){

		if(isExist->isEntry){
			isExist->address = (*newLabel).address;
		}
		return isExist;
	}
	else if(isExist){ 

		printf("[Error: File- \"%s.as\", line - %d] Label already exists.\n", fileName, line->lineNum);
		line->isError = TRUE;
		return NULL;
	}

	strcpy((*newLabel).name, startOfLabel); 

	/* Add the new label to labelArr and return a pionter for line->label. */
	labelArr[labelArrCounter] = *newLabel;
	return &labelArr[labelArrCounter++];
}


/* Check if the label is legal. Return true if it is legal, else return false. */ 
boolean isValidLabel(char *labelName, int lineNum, boolean toPrint, char *fileName){

	int labelLength = strlen(labelName), i;

	/* Check if the label isn't an empty string. */
	if (*labelName == '\0'){
		if(toPrint && printf("[Error: File- \"%s.as\", line - %d] Label name is empty.\n", fileName, lineNum)){}
    		return FALSE;
	}

	/* Check if the label is equal or shorter then MAX_LABEL_LENGTH. */
	if (strlen(labelName) > MAX_LABEL_LENGTH){
    		if(toPrint && printf("[Error: File- \"%s.as\", line - %d] Label name is longer then %d characters.\n", fileName, lineNum, MAX_LABEL_LENGTH)){}
    		return FALSE;
	}

	/* Check if there are white-space characters between the lable and the char ':' . */
	if(isspace(labelName[labelLength-1])){
		if(toPrint && printf( "[Error: File- \"%s.as\", line - %d] Illegal label - there is a white char between the lable and the char ':' .\n", fileName, lineNum)){}
    		return FALSE;
	}

	/* Check if the first char is a letter. */
	if (!isalpha(*labelName)){
    		if(toPrint && printf( "[Error: File- \"%s.as\", line - %d] Illegal label - first char must be a letter.\n", fileName, lineNum)){}
    		return FALSE;
	}

	/* Check if the label is letters and numbers only. */
	for (i = 1; i < labelLength; i++){
		if (!isalnum(labelName[i])){
      			if(toPrint && printf("[Error: File- \"%s.as\", line - %d] Illegal label - label name must be letters and numbers only.\n", fileName, lineNum)){}
      			return FALSE;
		}
	}

	/* Check if the label is a save word. */
	for (i = 0; i < NUM_OF_SAVE_WORDS; i++){
		if (!strcmp(labelName,saveWords[i])){
      			if(toPrint && printf("[Error: File- \"%s.as\", line - %d] Label name can't be the same as a save word.\n", fileName, lineNum)){}
      			return FALSE;
		}
	}	
	return TRUE;
}


/* Check if the label alreay exists. Return a pointer to label name in labelArr if exists, else return NULL. */
labelInfo *existInLabelArr(char *labelName, labelInfo *labelArr){

	int i;

	if (labelName){

    		/* Check if labels names are equals. */
		for (i = 0; i < labelArrCounter; i++){

			if (strcmp(labelName, labelArr[i].name) == 0 ){ 

				return &labelArr[i];
			}
		}
	}
	return NULL;
}


/* Find the Next operand and return it. */
char *findNextOperand(char *line, char **endOfOp, boolean *isAnotherOperand){

	char *end;

	if (!whiteCharsOnly(line))
	{
		/* Find the end of the operand. */ 
		end = line; 

		/* Find the first comma or white-space char. */
		while((end) && (end[0] != '\0') && (!isspace(*end)) && (end[0] != ',')){

			++end;
		}

		if ((end) && (end[0] != '\0') && (end[0] != '\n')){
		
			if(end[0] == ','){

				*isAnotherOperand = TRUE;
			}
			else {	
				*isAnotherOperand = FALSE;
			}

			*end = '\0';
			end++;

			/* Remove white-space characters left of string. */ 
			removeWhiteCharsLeft(&end);
		}
		else{
			*isAnotherOperand = FALSE;
		}

		/* If isn't NULL, set endOfOp to point at the next char after the operand, or at the end of the operand if it's the end of the line. */
		if (endOfOp){

			if (end){
				*endOfOp = end;
			}
			else{
				*endOfOp = strchr(line, '\0');
			}
		}
	}

	/* Remove white-space characters left and right of string. */ 
	removeWhiteCharsLeft(&line);
	removeWhiteCharsRight(&line);

	return line;
}


/* Check if the number is a legal number for thet specific operand, and save it's value in *operandValue. Return true if it is legal, else return false. */
boolean isValidNumber(char *numAsStr, int lineNum, long int *operandValue, char *cmdOrDirStr, opTypes codeType, boolean isData, boolean isCode, char *fileName){

	char *endOfNum;
	double isNumMoreThenDwMax = 0;
	char *endOfNumDw;

	/* Check if the operand is empty. */
	if (whiteCharsOnly(numAsStr)){

		printf("[Error: File- \"%s.as\", line - %d] Empty operand.\n", fileName, lineNum);
		return FALSE;
	}

	*operandValue = strtol(numAsStr, &endOfNum, 0);
	isNumMoreThenDwMax = strtod(numAsStr, &endOfNumDw);

	/* Check if numAsStr is a legal number, endOfNum and endOfNumDw should be NULL. */
	if (*endOfNum || *endOfNumDw){
		printf("[Error: File- \"%s.as\", line - %d] Invalid number.\n", fileName, lineNum);
		return FALSE;
	}

	/* Check if the number is small enough to fit into 8 bits. */
	if (isData && (strcmp(cmdOrDirStr, "db") == 0) && (*operandValue > MAX_DB_VALUE-1 || *operandValue < -MAX_DB_VALUE)){

			printf("[Error: File- \"%s.as\", line - %d] \"%s\" is too %s, must be between %d and %d.\n", fileName, lineNum, numAsStr, (*operandValue > 0) ? "big" : "small", -MAX_DB_VALUE, MAX_DB_VALUE-1);
			return FALSE;
	}
	/* Check if the number is small enough to fit into 16 bits. */
	else if (((isData && strcmp(cmdOrDirStr, "dh") == 0) || (isCode && codeType == NUMBER)) && (*operandValue > MAX_DH_VALUE-1 || *operandValue < -MAX_DH_VALUE)){

			printf("[Error: File- \"%s.as\", line - %d] \"%s\" is too %s, must be between %d and %d.\n", fileName, lineNum, numAsStr, (*operandValue > 0) ? "big" : "small", -MAX_DH_VALUE, MAX_DH_VALUE-1);
			return FALSE;
	}
	/* Check if the number is small enough to fit into 32 bits. */
	else if (isData && (strcmp(cmdOrDirStr, "dw") == 0)){

		if(isNumMoreThenDwMax > (MAX_DW_VALUE-1) || isNumMoreThenDwMax < (-MAX_DW_VALUE)){

			printf("[Error: File- \"%s.as\", line - %d] \"%s\" is too %s, must be between %.0f and %.0f.\n", fileName, lineNum, numAsStr, (isNumMoreThenDwMax > 0) ? "big" : "small", -MAX_DW_VALUE, MAX_DW_VALUE-1);
			return FALSE;
		}
	}
	return TRUE;
}

