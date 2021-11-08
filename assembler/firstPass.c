/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#include "assembler.h"
#include "firstPass.h"

/***************************************************** code segment *****************************************************/

/* Reading the file for the first time, line by line, and parse it. Return true if non of the lines had errors, else return false. */ 
boolean firstPass(FILE *file, ptrlines *headLinesList, int *lineCounter, int *IC, int *DC, char *fileName, labelInfo **headlabelArr, dataToPrint **headDataArr){

	boolean noErrors = TRUE;			/* Check if there are errors in the first pass. */
	ptrlines templines;
	ptrlines line = (ptrlines)*headLinesList;
	labelInfo **templabel;
	labelInfo **labelArr = headlabelArr;
	char lineString[MAX_LINE_LENGTH + 2];		/* +2 for the \n and \0 at the end. */ 
	*lineCounter = 0;

	/* Read lines and parse them. */
	while (!feof(file)){

		if (getLine(file, lineString, MAX_LINE_LENGTH + 2,*lineCounter + 1, fileName)){
			
			/* Parse line */
			readAndParseLine(&line->linesList, lineString, *lineCounter + 1, IC, DC, fileName, *labelArr, headDataArr);

      			if(line->linesList.isError){
			  noErrors = FALSE;
			}
		}
		++(*lineCounter);

		templines = (ptrlines) calloc(1, sizeof(itemlines));
		if (!templines){

			printf("[Error: File- \"%s.as\"] Memory not allocated.\n", fileName);
       			noErrors = FALSE;
			return noErrors;
		}
		else{
			line->next = templines;
			line = line->next;
		}

		if((labelArrCounter != 0) && ((labelArrCounter%SIZE_LABEL_ARRAY) == 0)){

			templabel = (labelInfo **)realloc(*headlabelArr, (labelArrCounter + SIZE_LABEL_ARRAY)*sizeof(labelInfo)); 
			if (!templines){ 

				printf("[Error: File- \"%s.as\"] Memory not allocated.\n", fileName);
	       			noErrors = FALSE;
				return noErrors;
			}
			else{
				*headlabelArr = (labelInfo*)templabel;
				*labelArr = (labelInfo*)templabel;
			}
		}
	}
	return noErrors;
}


/* Inserts one line from 'file' into 'buffer'. Return true if the line is shorter than maxLength, else return false. */
boolean getLine(FILE *file, char *buff, size_t maxLength, int lineNum, char *fileName){

	char *eol;	/* Pointer to end of line. */
	char temp;
	boolean end;	/* Check if reached the end of the file. */

	if (!fgets(buff, maxLength, file)){
		return FALSE;
	}

	/* Check if the line is too long (no '\n' was encountered). */
	eol = strchr(buff, '\n'); /* End of line */
	if (eol){
		*eol = '\0';
	}
	else{
		/* If reached EOF return true, else procceed until '\n' or EOF. */
		end = (feof(file)) ? TRUE : FALSE;

    		if(!end)
			printf("[Error: File- \"%s.as\", line - %d] Line is longer then %d characters.\n",fileName, lineNum, MAX_LINE_LENGTH);
		do{
			temp = fgetc(file);
		}
		/* Run until the end of the line. */
		while (temp != '\n' && temp != EOF);

       		return end;
	}

	return TRUE;
}


/* Read the line, check if label exist and add it to labelArr as needed, call for diractive or command and print errors. */
void readAndParseLine(lineInfo *line, char *lineString, int lineNum, int *IC, int *DC, char *fileName, labelInfo *labelArr, dataToPrint **headDataArr){

	char *nextSegment = lineString;
	char *string = (char*) malloc(strlen(lineString) + 1);

	if (string){

		strcpy(string, lineString);

		line->mallocStr = string;		/* Created to save the pointer to free malloc. */
		line->lineString = string;
		line->lineNum = lineNum;
		line->address = FIRST_ADDRESS + *IC;
		line->isError = FALSE;			/* FALSE - no errors in the line. */
		line->label = NULL;
		line->cmdOrDirStr = NULL;

		if (!line->lineString){
			printf("[Error: File- \"%s.as\", line - %d] Memory not allocated.\n",fileName, lineNum);
			return;
		}

		/* Check if the line is an empty or a comment line. */
		if (isLineCommentOrEmpty(line)){
			return;
		}

		/* Find label if exist and add it to labelArr. */
		if(strncmp(line->lineString, ".asciz",6)){

			nextSegment = findLabel(line, fileName, labelArr);
		}
		if (line->isError){
			return;
		}

		/* Update the line if isn't NULL. */
		if (nextSegment){
			line->lineString = nextSegment;
		}

		/* Check if the line is a command or a diractive line. */
		isLineCmdOrDir(line ,nextSegment ,IC , DC, fileName, labelArr, headDataArr);
		if(line -> isError){
			return;
		}
	}
}


/* Check if the 'line' is a comment or empty. Return true if the 'line' is a comment or empty, else return false. */
boolean isLineCommentOrEmpty(lineInfo *line){

	char *startOfText;

	/* Remove white-space characters left of string. */
	removeWhiteCharsLeft(&line->lineString);

	startOfText = line->lineString;

	/* Check if the line is comment. */
	if (*startOfText == ';'){

		return TRUE;
	}

	/* Check if the line is only white-space characters or empty. */
	if (*startOfText == '\0'){

		return TRUE;
	}

	/* Not empty or comment. */
	return FALSE;
}


/* Find label if exists and add it to label array. Return a pointer to the next char after the label or null if there is no label. */
char *findLabel(lineInfo *line, char *fileName, labelInfo *labelArr){

	char *endOfLabel = strchr(line->lineString, ':'); 
	labelInfo newLabel = {0};

	newLabel.address = line->address;

	/* If there is no label. */
	if (!endOfLabel){

		return NULL;
	}

	*endOfLabel = '\0';

	/* Add label to labelArr. */
	line->label = addToLabelArr(&newLabel, line, fileName, labelArr); 

	/* +1 to point to the char after ':' char. */
	return endOfLabel + 1;
}


/* Check if the line is a command or directive line, and read it. */
void isLineCmdOrDir(lineInfo *line, char *nextSegment, int *IC, int *DC, char *fileName, labelInfo *labelArr, dataToPrint **headDataArr){ 

	line -> cmdOrDirStr = findCmdOrDir(line -> lineString,&nextSegment);
	line -> lineString = nextSegment;

	/* The line is a directive line. */
	if(line -> cmdOrDirStr[0] == '.'){

		/* The line is a directive line. */
		line -> isData = TRUE;
		line -> cmdOrDirStr++;
		findDir(line, IC, DC, fileName, labelArr, headDataArr);
	}
	else{
		/* The line is a command line. */
		line -> isCode = TRUE;
		if(line -> label){

			line -> label->isCode = TRUE;
		}
		findCmd(line,IC,DC, fileName);
	}
}


/* Find next segment in line- command or diractive, and return it. */
char *findCmdOrDir(char *string, char **endOfWord){

  	char *startOfText = string;
	char *endOfText = NULL;

  	/* Remove white-space characters left of string. */
  	removeWhiteCharsLeft(&startOfText);

 	endOfText = startOfText;

	/* Find the end of the first word in the string. */
	for(;*endOfText != '\0' && !isspace(*endOfText);endOfText++);

	/* Add \0 at the end if needed. */
	if (*endOfText != '\0'){
		*endOfText = '\0';
		endOfText++;
	}

	if (endOfWord){
		*endOfWord = endOfText;
	}

	return startOfText;
}

