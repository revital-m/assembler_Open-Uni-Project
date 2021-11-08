/*name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529  */

#ifndef TOOLS_H
#define TOOLS_H

/***************************************************** extern necessary for data *****************************************************/
extern int labelArrCounter;
extern cmdInfo commandArr[];

/***************************************************** Functions declaration *****************************************************/

/* Remove white-space characters left of string. */
void removeWhiteCharsLeft(char **);

/* Remove white-space characters right of string. */
void  removeWhiteCharsRight(char **);

/* Check if the label is legal. Return true if it is legal, else return false. */
boolean isValidLabel(char *, int , boolean , char *);

/* Check if the label alreay exists. Return a pointer to label name in labelArr if exists, else return NULL. */
labelInfo *existInLabelArr(char *, labelInfo *);

/* Return ture if str contains only white-space characters, else return false. */
boolean whiteCharsOnly(char *);

#endif
