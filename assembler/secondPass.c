/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#include "assembler.h"
#include "secondPass.h"

/***************************************************** code segment *****************************************************/

/* Reading the file for the Second time, line by line. Check if entry / extern labels are legal. Set lable operands values as needed. Update address for data in labelArr. Add all code lines and dataArr to printArr. Return true if there were no errors, else return false. */
boolean secondPass(printInfo *printArr, ptrlines headLinesList, int lineCounter, int IC, int DC, char *fileName, labelInfo **labelArr, dataToPrint *dataArr){

	int printCounter = 0, i;

	/* Check if the entry / extern labels are legal. */
	boolean noError = isValidEntryAndExtern(fileName, *labelArr);

	if(noError){

		/* Update the data Address in labelArr. */
		for (i = 0; i < labelArrCounter; i++){

			if ((*labelArr)[i].isData){

				/* address = address + IC */
				(*labelArr)[i].address = (*labelArr)[i].address + FIRST_ADDRESS + IC;
			}
		}

		/* Add all code lines values to printArr. */
		for (i = 0; i < lineCounter-1; i++){

			if (!addCodeLineToPrintArr(printArr, &printCounter, &headLinesList->linesList, fileName, *labelArr)){

				noError = FALSE;
			}
			headLinesList = headLinesList->next;
		}

		/* Add all data to printArr. */
		addDataToPrintArr(printArr,&printCounter,DC, dataArr);
	}
	return noError;
}


/* Check if the entry / extern labels are legal. Return true if legal, else return false. */
boolean isValidEntryAndExtern(char *fileName, labelInfo *labelArr){

	int i;
	boolean isError = TRUE;

	for (i = 0; i < labelArrCounter; i++){

		/* Check if the entry labels are legal. */
		if((labelArr[i].isEntry) && (!(labelArr[i].isData) && !(labelArr[i].isCode))){ 

			printf("[Error: File- \"%s.as\", line - %d] Undefined entry label: \"%s\".\n",fileName, labelArr[i].lineNum, labelArr[i].name);
			isError =  FALSE;
		}

		/* Check if the extern labels are legal. */
		else if((labelArr[i].isExtern) && (labelArr[i].isData || labelArr[i].isCode)){ 

			printf("[Error: File- \"%s.as\", line - %d] Extern label: \"%s\" can not be initialize in this file.\n",fileName, labelArr[i].lineNum, labelArr[i].name);
			isError =  FALSE;
		}
	}
	return isError;
}


/* Add the code lines to printArr. Return true if there were no errors, else return false. */
boolean addCodeLineToPrintArr(printInfo *printArr, int *printCounter, lineInfo *line, char *fileName, labelInfo *labelArr){

	boolean noError = TRUE;
	boolean firstOpIsLabel = FALSE;
	boolean thirdOpIsLabel = FALSE;

	/* If the line is command and isn't error. */
	if ((!(line->isError)) && (line->cmdOrDirStr != NULL) && (findInCmdArr(line-> cmdOrDirStr) != -1)){

		/* Change the label operands value. */
		firstOpIsLabel = setLableOperandValue(&line -> firstOp, line->lineNum, line-> cmdOrDirStr, line -> address, fileName, labelArr); 
		thirdOpIsLabel = setLableOperandValue(&line -> thirdOp, line->lineNum, line-> cmdOrDirStr, line -> address, fileName, labelArr); 

		if (!firstOpIsLabel || !thirdOpIsLabel){

			line->isError = TRUE;
			noError = FALSE;
		}

		/* Add the commands values to printArr. */
		printArr[(*printCounter)].number = setCmdNum((*line), fileName).number; 
		printArr[(*printCounter)++].dataLine = DW;
	}
	return noError;
}


/* Set the value of lable opernads as needed, if label exist and legal. Return true if there were no errors, else return false. */
boolean setLableOperandValue(opInfo *operand, int lineNum, char *cmdOrDirStr, int address, char *fileName, labelInfo *labelArr){

	labelInfo *label;
	boolean labelIsLegal;
	int cmdIdx;

	if (operand->type == LABEL){

		label = existInLabelArr(operand->str, labelArr);

		labelIsLegal = isValidLabel(operand->str, lineNum, TRUE, fileName);

		/* Check if operand->str is a legal label and exist in labelArr. */
		if ((label == NULL) && labelIsLegal){

			printf("[Error: File- \"%s.as\", line - %d] Undefined label: \"%s\" as an operand.\n", fileName, lineNum, operand->str);
			return FALSE;
		}

		cmdIdx = findInCmdArr(cmdOrDirStr);

		if((label != NULL) && (commandArr[cmdIdx].opCodeCommand == 30 || commandArr[cmdIdx].opCodeCommand == 31 || commandArr[cmdIdx].opCodeCommand == 32)){

			operand->value = (long int)(label -> address);
		}

		else if((label != NULL) && (commandArr[cmdIdx].opCodeCommand >= 15) && (commandArr[cmdIdx].opCodeCommand <= 18 )){

			if(label->isExtern){

				printf("[Error: File- \"%s.as\", line - %d] Command of type I can not have an extern label: \"%s\" as an operand.\n", fileName, lineNum, operand->str);
				return FALSE;
			}
			operand->value = (long int)((label -> address) - (address));
		}
	}
	return TRUE;
}


/* Save the command line as a binary number (32-bit) and return it. */
commandTypes setCmdNum(lineInfo line, char *fileName){

	commandTypes newBinaryNum = { 0 };
	int cmdIdx;

	/* Write all the bits in the command word */
	if(line.isCode){

		cmdIdx = findInCmdArr(line.cmdOrDirStr);

		if(cmdIdx != -1){

			switch(commandArr[cmdIdx].type){

				case R:
					newBinaryNum = setCmdTypeR(line, cmdIdx);
					break;
				case I:
					newBinaryNum = setCmdTypeI(line, cmdIdx);
					break;
				case J:
					newBinaryNum = setCmdTypeJ(line, cmdIdx);		
					break;
				default : 
					printf("[Error: File- \"%s.as\", line - %d] Command type doesn't exist. \n", fileName, line.lineNum);
					line.isError = TRUE;
					break;
			}
		}
	}
	return newBinaryNum;
}


/* Save the type R command as a binary number (32-bit) and return it. */
commandTypes setCmdTypeR(lineInfo line, int cmdIdx){

	commandTypes newBinaryNum = { 0 };

	newBinaryNum.RCommand.notUsed = 0;
	newBinaryNum.RCommand.funct = commandArr[cmdIdx].functCommand;
	newBinaryNum.RCommand.rs = line.firstOp.value;
	newBinaryNum.RCommand.opCode = commandArr[cmdIdx].opCodeCommand;

	if(commandArr[cmdIdx].opCodeCommand == 0) {

		newBinaryNum.RCommand.rd = line.thirdOp.value;
		newBinaryNum.RCommand.rt = line.secondOp.value;
	}
	else if(commandArr[cmdIdx].opCodeCommand == 1) {

		newBinaryNum.RCommand.rd = line.secondOp.value;
		newBinaryNum.RCommand.rt = 0;
	}
	return newBinaryNum;
}


/* Save the type I command as a binary number (32-bit) and return it. */
commandTypes setCmdTypeI(lineInfo line, int cmdIdx){

	commandTypes newBinaryNum = { 0 };

	newBinaryNum.ICommand.opCode = commandArr[cmdIdx].opCodeCommand;
	newBinaryNum.ICommand.rs = line.firstOp.value;

	if(commandArr[cmdIdx].opCodeCommand >= 15 && commandArr[cmdIdx].opCodeCommand <= 18 ) {

		newBinaryNum.ICommand.immed = line.thirdOp.value;
		newBinaryNum.ICommand.rt = line.secondOp.value;
	}
	else {
		newBinaryNum.ICommand.immed = line.secondOp.value;
		newBinaryNum.ICommand.rt = line.thirdOp.value;
	}
	return newBinaryNum;
}


/* Save the type J command as a binary number (32-bit) and return it. */
commandTypes setCmdTypeJ(lineInfo line, int cmdIdx){

	commandTypes newBinaryNum = { 0 };

	newBinaryNum.JCommand.opCode = commandArr[cmdIdx].opCodeCommand;
	newBinaryNum.JCommand.address = line.firstOp.value;

	if((commandArr[cmdIdx].opCodeCommand == 30) && (line.firstOp.type == REGISTER)){

		newBinaryNum.JCommand.reg = 1;
	}
					
	else {

		newBinaryNum.JCommand.reg = 0;
	}
	return newBinaryNum;
}


/* Add all data to printArr. */
void addDataToPrintArr(printInfo *printArr, int *printCounter, int DC, dataToPrint *dataArr){

	int i;

	for (i = 0; i < DC; i++){

		/* Save data as a binary number (8-bit / 16-bit / 32-bit). */
		printArr[(*printCounter)].number = dataArr[i].dataLengthToPrint;
		printArr[(*printCounter)++].dataLine = dataArr[i].dataTypeToPrint;
	}
}

