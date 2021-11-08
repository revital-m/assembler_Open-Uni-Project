/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#include"assembler.h"
#include "outPutPrint.h"

/***************************************************** code segment *****************************************************/

/* Print all the files assembler requires. */
void printFiles(char *fileName, int IC, int DC, printInfo *printArr, ptrlines headLinesList, int lineCounter, labelInfo *labelArr){

	/* Print object file. */
	printObFile(fileName, IC, DC, printArr);

	/* Print extern file if needed. */
	printExtFile(fileName, headLinesList, lineCounter, labelArr);

	/* Print entry file if needed. */
	printEntFile(fileName, labelArr);
}


/* Print object file ,address and code in hexadecimal base. */
void printObFile(char *fileName, int IC, int DC, printInfo *printArr){

	FILE *file;

	file = openNewFile(fileName, ".ob", "w");

	/* Print IC and DC */
	fprintf(file,"     %d %d\n",IC , DC);

	/* Print code and data in hexadecimal base. */
	printCodeBase16(file,printArr, IC);
	printDataBase16(file,printArr, IC, DC);
	
	fclose(file);
}


/* Print all command numbers in base 16 and their address to file. */
void printCodeBase16(FILE *file, printInfo *printArr, int IC){

	numToPrint newNum ={0};
	int i;
  
	/* Print all of the code lines in printArr and their address ( only IC). */
	for (i = 0; i < (IC/4) ; i++){ 

		newNum.binaryNumLength = printArr[i].number;

		if(i == 0){

			fprintf(file, "%04d ",FIRST_ADDRESS + (i*4));
		}
		else{
			fprintf(file, "\n%04d ",FIRST_ADDRESS + (i*4));
		}

		fprintf(file,"%02X ",newNum.oneByte[0]);
		fprintf(file,"%02X ",newNum.oneByte[1]);
		fprintf(file,"%02X ",newNum.oneByte[2]);
		fprintf(file,"%02X",newNum.oneByte[3]);
	}
}


/* Print all directive numbers in base 16 and their address to file. */
void printDataBase16(FILE *file, printInfo *printArr, int IC, int DC){

	numToPrint newNum ={0};
	int count = 0;		/* count the byte that was printed. */
	int i;

  	/* Print all of the data lines in printArr and their address ( only DC).*/
	for (i = (IC/4); i < ((IC/4) + DC);){ 

		newNum.binaryNumLength = printArr[i].number;

		if(i == 0){

			fprintf(file, "%04d ",FIRST_ADDRESS + IC);
		}
		else if(i == (IC/4)){

			fprintf(file, "\n%04d ",FIRST_ADDRESS + IC);
		}
		if((printArr[i].dataLine == DB) || (printArr[i].dataLine == ASCIZ)){

			/* Print the number in base 16, one byte at a time to file. */
			printOneByte(file, &i, 1, &count, IC, DC, &newNum);
		}
		else if(printArr[i].dataLine == DH){

			/* Print the number in base 16, one byte at a time to file. */
			printOneByte(file, &i, 2, &count, IC, DC, &newNum);
		}
		else if(printArr[i].dataLine == DW){

			/* Print the number in base 16, one byte at a time to file. */
			printOneByte(file, &i, 4, &count, IC, DC, &newNum);
		}
	}
}


/* Print the number in base 16, one byte at a time to file. */
void printOneByte(FILE *file, int *i, int num, int *count, int IC, int DC, numToPrint *newNum){

	int j;

	for(j = 0; j < num; j++){

		fprintf(file,"%02X",newNum->oneByte[j]);
		*count += 1;
		*i += 1;

		/* Check if needed to print Address or to print a Space char. */
		printAddressOrSpace(file, (int)*i, ((IC/4) + DC), (int)*count, IC);
	}
}


/* Check if needed to print Address or a Space char to file. */
void printAddressOrSpace(FILE *file, int i, int endOfPrintArr, int count, int IC){

	if((count%4) == 0){
				
		fprintf(file, "\n%04d ",FIRST_ADDRESS + count + IC);
	}
	else if(i < endOfPrintArr){

		fprintf(file," ");
	}
}


/* Creates the external file, with label and address for every extern label. */
void printExtFile(char *fileName, ptrlines headLinesList, int lineCounter, labelInfo *labelArr){

	int i;
	labelInfo *label;
	boolean firstPrint = TRUE;
	FILE *file = NULL;

	for (i = 0; i < lineCounter; i++){

		/* Check if the command is J and if the first operand type is extern label, and print it. */
		if ((findInCmdArr(headLinesList->linesList.cmdOrDirStr) != -1) && (commandArr[findInCmdArr(headLinesList->linesList.cmdOrDirStr)].type == J) && (headLinesList->linesList.firstOp.type == LABEL)){

			label = existInLabelArr(headLinesList->linesList.firstOp.str, labelArr); 

			/* Check if the label is extern. */
			if (label && label->isExtern){

				if (firstPrint){

					/* Create the file only if there is at least -1- extern label. */
					file = openNewFile(fileName, ".ext", "w");
				}
				else{
					fprintf(file, "\n");
				}

				fprintf(file, "%s %04d", label->name, headLinesList->linesList.address);
				firstPrint = FALSE;
			}
		}
		headLinesList = headLinesList->next;
	}

	if (file){
		fclose(file);
	}
}


/* Creates the entry file, with label and address for every entry label. */
void printEntFile(char *fileName, labelInfo *labelArr){

	int i;
	FILE *file;

	/* Create the file only if there is at least -1- entry label. */
	if (!entryLabelCounter){
		return;
	}

	file = openNewFile(fileName, ".ent", "w");

	for (i = 0 ; i < labelArrCounter; i++){

		if(labelArr[i].isEntry){

			/* Print entry label and address. */
			fprintf(file,"%s %04d" ,labelArr[i].name, labelArr[i].address); 
			entryLabelCounter--;

			/* If there are more entry label to print. */
			if (entryLabelCounter != 0){

				fprintf(file, "\n");
			}
		}
	}

	/* close the file */
	fclose(file);
}

