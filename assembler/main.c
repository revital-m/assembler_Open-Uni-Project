/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

/* 	
This program translates assembly language code into hexadecimal code by two readings.
First reading- The program collects all the necessary information and saves it in a linked list and dynamic arrays.
Second reading- The program transforms the data collected into binary lines and saves them in printArr.
After both readings, if there were no errors, the program will create three outPut files: ".ob" , ".ext" , ".ent" . And print the information in hexadecimal to those files.
The files ".ext" , ".ent" are created only if there is at least one extern/entry label respectively.
*/

#include "assembler.h"
#include "main.h"

/***************************************************** global data *****************************************************/
int labelArrCounter = 0;
int entryLabelCounter = 0; 

/***************************************************** code segment *****************************************************/

int main (int argc, char *argv[]){

	int i;

	/* if file name is'nt found */
	if (argc < 2){
		printf("\nNo file names.\n");
		return 1;
	}

	/*read all files*/
	for (i = 1; i < argc; i++)
	{
		readFile(argv[i]);
		printf("\n");
	}
	return 0;
}


/* Read the given file: call for firstPass and secondPass, and create output files if needed. */
void readFile(char *fileName){

	boolean isFirstPassOk, isSecondPassOk;	/* isFirstPassOk - true if non of the lines had errors , isSecondPassOk - true if non of the lines had errors. */
	int IC = 0, DC = 0, lineCounter = 0;	/* IC - counter for command , DC - counter for directive , lineCounter - counter for the lines found. */ 
	dataToPrint *dataArr = NULL;		/* Pointer for the dataArr. */
	labelInfo *labelArr = NULL;		/* Pointer for the labelArr. */
	ptrlines headLinesList;			/* Pointer for the LinesList. */
	printInfo *printArr = NULL;		/* Pointer for the printArr. */

 	FILE *file = openNewFile(fileName, ".as", "r");
	
	/* If file doesn't open. */
	if (file == NULL){
		printf("[File- \"%s.as\"] Opening failed!\n", fileName);
		return;
	}
	printf("[File- \"%s.as\"] Successfully opened!\n", fileName);

	dataArr = (dataToPrint *) calloc(1, sizeof(dataToPrint)); 
	labelArr = (labelInfo *) calloc(SIZE_LABEL_ARRAY, sizeof(labelInfo));
	headLinesList = (ptrlines) calloc(1, sizeof(itemlines));
	/* Check if the memory has been successfully allocated by calloc or not. */
	if (!headLinesList && !labelArr && !dataArr){

		printf("[Error: File- \"%s.as\"] Memory not allocated.\n", fileName);
		resetForNextFile(printArr, &headLinesList, labelArr, dataArr);
		fclose(file);
		exit(0);
	}

	/* First pass. */
	isFirstPassOk = firstPass(file, &headLinesList, &lineCounter, &IC, &DC, fileName, &labelArr, &dataArr);

	printArr = (printInfo *) calloc((IC+DC), sizeof(printInfo));
	/*Check if the memory has been successfully allocated by calloc or not.*/
	if (!printArr){

		printf("[Error: File- \"%s.as\"] Memory not allocated.\n", fileName);
		resetForNextFile(printArr, &headLinesList, labelArr, dataArr);
		fclose(file);
		exit(0);
	}

	/* Second pass. */
	isSecondPassOk = secondPass(printArr, headLinesList, lineCounter, IC, DC, fileName, &labelArr, dataArr);

	/*check if there isnt error in file before print */
	if(isFirstPassOk && isSecondPassOk){

		printFiles(fileName, IC, DC, printArr, headLinesList, lineCounter, labelArr);
    		printf("[File- \"%s.as\"] Created output files!\n", fileName);
	}
	else{
		printf("[File- \"%s.as\"] Didn't create output files!\n", fileName);
	}

	/* Free calloc pointers, and reset global counters. */
	resetForNextFile(printArr, &headLinesList, labelArr, dataArr);

	/* Close File. */
	fclose(file);
	printf("[File- \"%s.as\"] Successfully closed!\n", fileName);
}


/* Resets all the globals and free all the calloc blocks. */
void resetForNextFile(printInfo *printArr, ptrlines *headLinesList, labelInfo *labelArr, dataToPrint *dataArr){

	ptrlines freeLinesList;

	/* Reset global counters. */
	labelArrCounter = 0;	
	entryLabelCounter = 0;

	/* Free LinesList. */
	while (*headLinesList){

		freeLinesList = *headLinesList;
		*headLinesList = (*headLinesList)->next;
		free(freeLinesList->linesList.mallocStr);
		free(freeLinesList);
	}

	/* Free calloc. */
	free(printArr);
	free(labelArr);
	free(dataArr);
}

