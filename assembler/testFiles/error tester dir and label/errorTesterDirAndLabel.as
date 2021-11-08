;name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529
;number of errors = 94 

;******************** test data directives ********************
;*** test .db directive ***

;[error: invalid immed number]
;	line 12-(immedNumber > 127)
;	line 13-(immedNumber < -128)
;	line 14-(immedNumber.0)

	.db 128
	.db -129, 4
	.db 5.5,6

;[error: invalid operand]
;	line 21-(non number char)
;	line 22-(reg)
;	line 23-(validLabel)

	.db a,6
	.db -127, $4
	.db 5,6, validLabel

;[error: missing ',']
;	line 29-(between operands 1 and 2)
;	line 30-(between operands 2 and 3)

	.db 50 	6	,	8
	.db -127, 4 10

;[error: comma befor first operand and after last operand]
;	line 36-(befor first operand)
;	line 37-(after last operand)

	.db ,50 	,6	,	8
	.db -127, 4, 10,

;[error: not enough operands]
;	line 42-(no operand instead of at least 1)

	.db 		

;*** test .dh directive ***

;[error: invalid immed number]
;	line 51-(immedNumber > 32767)
;	line 52-(immedNumber < -32768)
;	line 53-(immedNumber.0)

	.dh 32768
	.dh -32769, 4
	.dh 5.5,6

;[error: invalid operand]
;	line 60-(non number char)
;	line 61-(reg)
;	line 62-(validLabel)

	.dh a,6
	.dh -127, $4
	.dh 5,6, validLabel

;[error: missing ',']
;	line 68-(between operands 1 and 2)
;	line 69-(between operands 2 and 3)

	.dh 50 	6	,	8
	.dh -127, 4 10

;[error: comma befor first operand and after last operand]
;	line 75-(befor first operand)
;	line 76-(after last operand)

	.dh ,50 	,6	,	8
	.dh -127, 4, 10		,		

;[error: not enough operands]
;	line 81-(no operand instead of at least 1)

	.dh 		

;*** test .dw directive ***

;[error: invalid immed number]
;	line 90,92-(immedNumber > 2147483647)
;	line 91,93-(immedNumber < -2147483648)
;	line 94-(immedNumber.0)

	.dw 2147483648
	.dw -2147483649, 4 
	.dw 214748364800
	.dw -214748364900, 4 
	.dw 5.5,6

;[error: invalid operand]
;	line 101-(non number char)
;	line 102-(reg)
;	line 103-(validLabel)

	.dw a,6
	.dw -127, $4
	.dw 5,6, validLabel

;[error: missing ',']
;	line 109-(between operands 1 and 2)
;	line 110-(between operands 2 and 3)

	.dw 		50 	6	,	8
	.dw -127, 4 10

;[error: comma befor first operand and after last operand]
;	line 116-(befor first operand)
;	line 117-(after last operand)

	.dw ,50 	,6	,	8
	.dw -127, 4, 10		,		

;[error: not enough operands]
;	line 122-(no operand instead of at least 1)

	.dw 		

;******************** test .asciz directives ********************

;[error: missing quotation mark at the beginning of the string]
;	line 129

	.asciz missing quotation mark at the beginning of the string" 

;[error: missing quotation mark at the end of the string]
;	line 134

	.asciz "missing quotation mark at the beginning of the string	

;[error: invalid string inside the quotation marks]
;	line 139,140-(non printable char)

	.asciz "invalid string (tub)		"
	.asciz "invalid string (new line) 
" 

;[error: comma befor first operand and after last operand]
;	line 147-(befor first operand)
;	line 148-(after last operand)

	.asciz ,"comma befor first operand"
	.asciz "comma after last operand",

;[error: not enough operands]
;	line 153-(no operand instead of at least 1)

	.asciz 


;*******************************************************************************
validLabel: stop
entryLabel: stop
alreadyExistsvalidLabel: stop
	.extern externLabel
	.entry entryLabel
;*******************************************************************************

;******************** test .entry directives ********************

;[error: invalid label as an operand]
;	line 170-(already an extern label)
;	line 171-(not used entry label)

	.entry externLabel
	.entry notUsedEntryLabel

;[error: invalid operand]
;	line 177-(reg)
;	line 178-(immedNumber)

	.entry $5
	.entry -5

;[error: comma befor first operand and after last operand]
;	line 184,185-(befor first operand)
;	line 186,187-(after last operand)

	.entry ,validLabel
	.entry , validLabel
	.entry validLabel,
	.entry validLabel	,	

;[error: too many operands]
;	line 192-(more then 1 operand)

	.entry validLabel,validLabel

;[error: not enough operands]
;	line 197-(no operand instead of at least 1)

	.entry 

;******************** test .extern directives ********************

;[error: invalid label]
;	line 204-(already an entry label)

	.extern entryLabel

;[error: invalid operand]
;	line 210-(reg)
;	line 211-(immedNumber)

	.extern $5
	.extern -5

;[error: comma befor first operand and after last operand]
;	line 217,218-(befor first operand)
;	line 219,220-(after last operand)

	.extern ,externLabel
	.extern , externLabel
	.extern externLabel,
	.extern externLabel	,	

;[error: too many operands]
;	line 225-(more then 1 operand)

	.extern externLabel,externLabel

;[error: not enough operands]
;	line 230-(no operand instead of at least 1)

	.extern

;******************** test ilegal directive ********************
;	line 236-(ilegal directive)
;	line 237,238-(no space between the directive and the first operand)

	.Entry validLabel
	.asciz"no space befor first operand"	
	.externexternLabel,externLabel



;******************** test label ********************

;[error: invalid label]
;	line 255,256,257-(no : at the end of the label)
;	line 259,260,261-(space between label and : at the end of the label)
;	line 263,264,265-(1 char is not Alphabet letter)
;	line 267,268,269-(char is not Alphabet letter or number)
;	line 271,272,273-(more then 31 chars)
;	line 275,276,277-(label is a save word)
;	line 279,280,281-(already an extern label)
;	line 283,284,285-(label already exists, not extern)
;	line 287,288,289-(empty line after the label)

noColonAtEndOfLabel .db 127,1,-56,	3	,-128
 noColonAtEndOfLabel	.dh 32767	,	5,-17
	noColonAtEndOfLabel	.dw 2147483647	,	5,-17

SpacebeforColonAtEndOfLabel : .db 127,1,-56,	3	,-128
 SpacebeforColonAtEndOfLabel :	.dh 32767	,	5,-17
	SpacebeforColonAtEndOfLabel :	.dw 2147483647	,	5,-17

1Label:	nori $3,32767,$19
 1Label:	lb $8,14    ,$15
	1Label:	sb $17	,		0,$19

Label\:	   lw $31,10    ,$8
 Label":	sw $5,32767,$8
	Label,:	lh $5,32767,$8

moreThen31CharsInTheLabel1234567:	sh $3,32767,$19
  moreThen31CharsInTheLabel12345674566: 	move	 $2,	$19
		moreThen31CharsInTheLabel1234561234567: mvlo $19 ,	$19 

extern: 	sub $3,$19,	$8
	add: 	or $3,	$3,$3
 db: 	nor $15	,	$19	,	$8

externLabel: 	addi $5,	-32768,	$19
 externLabel: bne $3 ,$5,entryLabel
	externLabel: 	jmp externLabel

validLabel: 	call  validLabel	
	alreadyExistsvalidLabel: 	.dw 2147483647	,	5,-17
entryLabel: 	.dh 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1

emptyLineAfterLabel: 
	emptyLineAfterLabel: 	
 emptyLineAfterLabel:     		


;******************** test line ********************

;[error: invalid line]
;	line 298-(more then 80 chars)
;	line 299-(ilegal line)

aRealyLongLine: 	.dh 0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,11
Ilegal line

