;name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529
;number of errors = 425 

validLabel: stop
entryLabel: stop
	.extern externLabel
	.entry entryLabel
;******************** test R commands ********************
;*** test R commands: add, sub, and, or, nor ***

;[error: invalid reg]
;	line 17,21,25,29,33-($+regNumber)
;	line 18,22,30-(regNumber < 0 || regNumber > 31)
;	line 19,23,27,31,35-(regNumber.0)
;	line 26,34-($ regNumber || $ )

	add $+3,$19,$8
	add $32,$19,$8
	add $31,$19.0,$8

	sub $3,$19,$+8
	sub $35,$19,$8
	sub $31.0,$19,$8

	and $3,$+19,$8
	and $30,$ 19,$4
	and $8.0,$19,$8

	or $3,$+5,$8
	or $30,$-33,$4
	or $2.0,$19,$8

	nor $3,$+7,$8
	nor $30,$,$4
	nor $15.0,$19,$8

;[error: invalid operand]
;	line 43,49,55,61,67-(immed number)
;	line 44,45,50,51,56,57,62,63,68,69-(+/-immed number)
;	line 46,52,58,64,70-(regNumber.0)
;	line 47,53,59,65,71-(validLabel)

	add $3,$19,8
	add $3,-19,$0
	add +3,$5,$12
	add 3.0,$5,$12
	add validLabel,$5,$12

	sub $3,19,$8
	sub -3,$19,$0
	sub $3,$5,+12
	sub $3,5.5,$12
	sub $3,validLabel,$12

	and $3,190,$8
	and -30,$19,$0
	and $3,$5,+120
	and $3,5.0,$12
	and $3,validLabel,$12

	or $3,$19,11
	or -11,$19,$0
	or $3,$5,+11
	or $3,11.0,$12
	or $3,$11,validLabel

	nor $3,$19,12
	nor -12,$19,$0
	nor $3,$5,+12
	nor $3,12.0,$12
	nor $3,$12,validLabel

;[error: missing ',']
;	line 77,80,83,86,89-(between operands 1 and 2)
;	line 78,81,84,87,90-(between operands 2 and 3)

	add $3 $19,$8
	add $3,$19 $8

	sub $3 $19,$8
	sub $3,$19 $8

	and $3 $19,$8
	and $3,$19 $8

	or $3 $19,$8
	or $3,$19 $8

	nor $3 $19,$8
	nor $3,$19 $8

;[error: comma befor first operand and after last operand]
;	line 96,99,102,105,108-(befor first operand)
;	line 97,100,103,106,109-(after last operand)

	add 			,$3,$19,$8
	add $3,$19,$8,

	sub ,$3,$19,$8
	sub $3,$19,$8,		

	and , $3,$19,$8
	and $3,$19,$8 ,

	or , 		$3,$19,$8
	or $3,$19,$8	,

	nor	 ,$3,$19,$8
	nor $3,$19,	$8 		,

;[error: too many operands]
;	line 114,116,118,120,122-(more then 3 operands)

	add $3,$19,$8,$5

	sub $3,$19,$8	,	$5,$1

	and $3,$19,	$8	,$5

	or $3,$19	,	$8,validLabel

	nor $3,$19	,	$8	,	validLabel


;[error: not enough operands]
;	line 130,134,138,142,146,150-(2 operands instead of 3)
;	line 131,135,139,143,147,151-(1 operand instead of 3)
;	line 132,136,140,144,148,152-(no operand instead of 3)

	add $3,$19
	add $3
	add 

	sub $3,$19
	sub $3
	sub 

	add $3,$19
	add $3
	add 

	and $3,$19
	and $3
	and 

	or $3,$19
	or $3
	or 

	nor $3,$19
	nor $3
	nor 

;*** test R commands: move, mvhi, mvlo ***

;[error: invalid reg]
;	line 162,166-($+regNumber)
;	line 163,171-(regNumber < 0 || regNumber > 31)
;	line 164,168,172-(regNumber.0)
;	line 167,170-($ regNumber || $ )

	move $+3,$19
	move $32,$19
	move $31,$19.0

	mvhi $3,$+8
	mvhi $5,$ 19
	mvhi $31.0,$8

	mvlo $ ,$8
	mvlo $30,$-19
	mvlo $8.0,$19


;[error: invalid operand]
;	line 181,187,193-(immed number)
;	line 182,183,188,189,194,195-(+/-immed number)
;	line 184,190,196-(regNumber.0)
;	line 185,191,197-(validLabel)

	move $3,8
	move -19,$0
	move +3,$5
	move 3.0,$12
	move validLabel,$5

	mvhi 19,$8
	mvhi -3,$19
	mvhi $5,+12
	mvhi $3,5.5
	mvhi $3,validLabel

	mvlo 190,$8
	mvlo -30,$0
	mvlo $5,+120
	mvlo 5.0,$12
	mvlo validLabel,$12

;[error: missing ',']
;	line 202,204,206-(between operands 1 and 2)

	move $3 $19

	mvhi $3		 $19

	mvlo $3	 $19


;[error: comma befor first operand and after last operand]
;	line 213,216,219-(befor first operand)
;	line 214,217,220-(after last operand)

	move 			,$3,$8
	move $3,$8,

	mvhi ,$3,$8
	mvhi $3	,	$8,		

	mvlo , $3	,$8	
	mvlo $3,	$8 ,		


;[error: too many operands]
;	line 226,227,229,230,232,233-(more then 2 operands)

	move $3,$19,$5
	move $3,$19,$8	,	$5,$1

	mvhi $3,$19,	$8	,$5
	mvhi $3,$19	,	$8,validLabel

	mvlo $3,$19	,	$8	,	validLabel
	mvlo $3,$19,	validLabel


;[error: not enough operands]
;	line 240,243,246-(1 operand instead of 2)
;	line 241,244,247-(no operand instead of 2)

	move $3
	move 

	mvhi $3
	mvhi 

	mvlo $3
	mvlo 



;******************** test I commands ********************
;*** test I commands: addi, subi, andi, ori, nori, lb, sb, lw, sw, lh, sh ***

;[error: invalid reg]
;	line 260,264,272,276,284,292,296-($+regNumber)
;	line 261,269,273,281,289,293,301-(regNumber < 0 || regNumber > 31)
;	line 262,266,270,274,278,282,286,290,294,298,302-(regNumber.0)
;	line 265,268,277,280,285,288,297,300-($ regNumber || $ )

	addi $+3,7,$19
	addi $32,5,$19
	addi $31,1,$19.0

	subi $3,10,$+8
	subi $5,11,$ 19
	subi $31.0,-1,$8

	andi $ ,9,$8
	andi $30,13,$-19
	andi $8.0,14,$19

	ori $+3,7,$19
	ori $32,5,$19
	ori $31,1,$19.0

	nori $3,10,$+8
	nori $5,11,$ 19
	nori $31.0,-1,$8

	lb $ ,9,$8
	lb $30,13,$-19
	lb $8.0,14,$19

	sb $3,10,$+8
	sb $5,11,$ 19
	sb $31.0,-1,$8

	lw $ ,9,$8
	lw $30,13,$-19
	lw $8.0,14,$19

	sw $+3,7,$19
	sw $32,5,$19
	sw $31,1,$19.0

	lh $3,10,$+8
	lh $5,11,$ 19
	lh $31.0,-1,$8

	sh $ ,9,$8
	sh $30,13,$-19
	sh $8.0,14,$19

;[error: invalid immed number]
;	line 309,313,317,321,325,329,333,337,341,345,349-(immedNumber > 32767)
;	line 310,314,318,322,326,330,334,338,342,346,350-(immedNumber < -32768)
;	line 311,315,319,323,327,331,335,339,343,347,351-(immedNumber.0)

	addi $3,32769,$19
	addi $30,-32769,$19
	addi $31,1.0,$19

	subi $3,32768,$8
	subi $5,-32770,$19
	subi $31,-1.0,$8

	andi $5,32769,$8
	andi $30,-32769,$19
	andi $8,14.4,$19

	ori $3,32768,$19
	ori $3,-32770,$19
	ori $31,1.3,$19

	nori $3,32769,$8
	nori $5,-32769,$19
	nori $1,-1.6,$8

	lb $2,32768,$8
	lb $30,-32770,$19
	lb $8,14.8,$19

	sb $3,32769,$8
	sb $5,-32769,$19
	sb $31,-1.9,$8

	lw $5,32768,$8
	lw $30,-32770,$19
	lw $8,14.3,$19

	sw $3,32769,$19
	sw $2,-32769,$19
	sw $31,1.7,$19

	lh $3,32768,$8
	lh $5,-32770,$19
	lh $31,-1.8,$8

	sh $4,32769,$8
	sh $30,-32769,$19
	sh $8,14.9,$19

;[error: invalid operand]
;	line 358,362,366,370,374,378,382,386,390,394,398-(reg instead of immedNumber)
;	line 359,363,367,371,375,379,383,387,391,395,399-(immedNumber instead of reg)
;	line 360,364,368,372,376,380,384,388,392,396,400-(validLabel)

	addi $3,$5,$19
	addi 32767,-32768,$19
	addi validLabel,0,$19

	subi $3,$6,$8
	subi $5,-32768,-32768
	subi $31,validLabel,$8

	andi $5,$9,$8
	andi $30,-32768,32767
	andi $8,14,validLabel

	ori $3,$8,$19
	ori 32767,32767,$19
	ori validLabel,-3,$19

	nori $3,$5,$19
	nori $5,-32768,-32768
	nori $31,validLabel,$8

	lb $5,$9,$8
	lb $30,-32768,32767
	lb $8,14,validLabel

	sb $3,$5,$19
	sb 32767,-32768,$19
	sb validLabel,0,$19

	lw $3,$6,$8
	lw $5,-32768,-32768
	lw $31,validLabel,$8

	sw $5,$9,$8
	sw $5,-32768,-32768
	sw $8,14,validLabel

	lh $5,$9,$8
	lh $30,-32768,32767
	lh validLabel,0,$19

	sh $3,$8,$19
	sh $5,-32768,-32768
	sh $31,validLabel,$8

;[error: missing ',']
;	line 406,409,412,415,418,421,424,427,430,433,436-(between operands 1 and 2)
;	line 407,410,413,416,419,422,425,428,431,434,437-(between operands 2 and 3)

	addi $3 32767,$19
	addi $7,-32768 $19

	subi $3 32767 , $19 
	subi $7,-32768 $19

	andi $3 32767,	$19
	andi $7,	-32768 $19

	ori $3  32767 , $19
	ori $7,-32768  $19 

	nori $3 	32767,$19
	nori $7,-32768 $19

	lb $3 32767,$19
	lb $7,-32768 	$19

	sb $3	 32767,$19
	sb $7,-32768   $19		

	lw $3	 32767,$19
	lw $7,-32768	 $19

	sw $3 32767	,$19
	sw $7,-32768 		$19

	lh $3 	32767,$19
	lh $7,-32768  $19

	sh $3 	32767,$19
	sh $7,-32768  	$19

;[error: comma befor first operand and after last operand]
;	line 443,446,449,452,455,458,461,464,467,470,473-(befor first operand)
;	line 444,447,450,453,456,459,462,465,468,471,474-(after last operand)

	addi ,$3, 32767,$19
	addi $7,-32768,$19,

	subi , $3,32767,$19 
	subi $7,-32768,$19 ,

	andi ,$3,32767,$19
	andi $7,-32768,	$19 , 

	ori ,$3	,32767,$19
	ori $7,-32768,	$19	, 

	nori 	,$3,32767,$19
	nori $7,-32768,$19,	

	lb 	,	$3	,32767	,$19
	lb $7,-32768,$19	,

	sb 	,$3,	32767,$19
	sb $7,-32768,$19	,		

	lw 	,$3,	32767,$19
	lw $7,	-32768,$19	,

	sw ,	$3,32767,$19
	sw $7,-32768	,	$19	,

	lh 	,	$3,32767,$19
	lh $7,-32768,$19,	

	sh ,	$3,32767,$19
	sh $7,-32768	,$19	,	

;[error: too many operands]
;	line 479,481,483,485,487,489,491,493,495,497,499-(more then 3 operands)

	addi $3,32767,$19,$2

	subi $3,32767,$19,$5,-700

	andi $3,32767,$19,validLabel

	ori $3,32767,$19,validLabel,$5

	nori $3,32767,$19,0,validLabel,400

	lb $3,32767,$19,validLabel,$8

	sb $3,32767,$19,$10

	lw $3,32767,$19,700

	sw $3,32767,$19,$9,validLabel

	lh $3,32767,$19,$0,7

	sh $3,32767,$19,validLabel

;[error: not enough operands]
;	line 506,510,514,518,522,526,530,534,538,542,546-(2 operands instead of 3)
;	line 507,511,515,519,523,527,531,535,539,543,547-(1 operand instead of 3)
;	line 508,512,516,520,524,528,532,536,540,544,548-(no operand instead of 3)

	addi $3,32767
	addi $3
	addi 

	subi $3,32767
	subi $3
	subi 

	andi $3,32767
	andi $3
	andi 

	ori $3,32767
	ori $3
	ori 

	nori $3,32767
	nori $3
	nori 

	lb $3,32767
	lb $3
	lb 

	sb $3,32767
	sb $3
	sb 

	lw $3,32767
	lw $3
	lw 

	sw $3,32767
	sw $3
	sw 

	lh $3,32767
	lh $3
	lh 

	sh $3,32767
	sh $3
	sh 


;*** test I commands: bne, beq, blt, bgt ***

;[error: invalid reg]
;	line 559,563,571-($+regNumber)
;	line 560,568,572-(regNumber < 0 || regNumber > 31)
;	line 561,565,569,573-(regNumber.0)
;	line 564,567-($ regNumber || $ )

	bne $+3,$7,validLabel
	bne $32,$5,validLabel
	bne $31,$1.0,validLabel

	beq $3,$+10,validLabel
	beq $5,$ 11,validLabel
	beq $31.0,$1,validLabel

	blt $ ,$9,validLabel
	blt $30,$-19,validLabel
	blt $8.0,$14,validLabel

	bgt $+3,$7,validLabel
	bgt $32,$5,validLabel
	bgt $31,$1.0,validLabel

;[error: invalid label]
;	line 579,582,585,588-(label does not exist)
;	line 580,583,586,589-(externLabel)

	bne $3,$7,notExistLabel
	bne $2,$5,externLabel

	beq $3,$10,notExistLabel
	beq $5,$11,externLabel

	blt $25,$9,notExistLabel
	blt $30,$19,externLabel

	bgt $3,$7,notExistLabel
	bgt $2,$5,externLabel

;[error: invalid operand]
;	line 596,600,604,608-(reg instead of validLabel)
;	line 597,601,605,609-(validLabel instead of reg)
;	line 598,602,606,610-(immedNumber)

	bne $3,$5,$19
	bne $7,validLabel,validLabel
	bne 32767,$0,validLabel

	beq $3,$6,$8
	beq validLabel,$5,validLabel
	beq $31,$27,32767

	blt $5,$9,$8
	blt $30,validLabel,validLabel
	blt $8,$14,-32768

	bgt $3,$8,$19
	bgt validLabel,$28,validLabel
	bgt -32768,$3,validLabel

;[error: missing ',']
;	line 616,619,622,625-(between operands 1 and 2)
;	line 617,620,623,626-(between operands 2 and 3)

	bne $3 $5,validLabel
	bne $7,$29 validLabel

	beq $3 $6,validLabel
	beq $4,$5 	validLabel

	blt $5		$9,validLabel
	blt $30 , $26     validLabel

	bgt $3   $8 ,validLabel
	bgt $24,$28 	validLabel		

;[error: comma befor first operand and after last operand]
;	line 632,635,638,641-(befor first operand)
;	line 633,636,639,642-(after last operand)

	bne ,$3 ,$5,validLabel
	bne $7,$29 ,validLabel,

	beq ,	$3 , $6,validLabel
	beq $4,$5 	, validLabel	,

	blt ,		$5	,	$9,validLabel
	blt $30 , $26   ,  validLabel,

	bgt 	, $3 ,  $8 ,validLabel
	bgt $24,$28 ,	validLabel		,				

;[error: too many operands]
;	line 647,649,651,653-(more then 3 operands)

	bne $3 ,$5,validLabel,$4

	beq 	$3 , $6,validLabel, validLabel

	blt 		$5	,	$9,validLabel, $5,validLabel

	bgt 	$3 ,  $8 ,validLabel, validLabel, $3,$0

;[error: not enough operands]
;	line 660,664,668,672-(2 operands instead of 3)
;	line 661,665,669,673-(1 operand instead of 3)
;	line 662,666,670,674-(no operand instead of 3)

	bne $3,$7
	bne $3
	bne 

	beq $3,$6
	beq $3
	beq 

	blt $3,$10
	blt $3
	blt 

	bgt $3,$2
	bgt $3
	bgt 

;******************** test J commands ********************
;*** test J commands: jmp ***

;[error: invalid reg]
;	line 685-($+regNumber)
;	line 686,687-(regNumber < 0 || regNumber > 31)
;	line 688-(regNumber.0)
;	line 689,690-($ regNumber || $ )

	jmp $+3
	jmp $32
	jmp $-31
	jmp $1.0
	jmp $ 31
	jmp $ 

;[error: invalid label]
;	line 695-(label does not exist)

	jmp notExistLabel

;[error: invalid operand]
;	line 700,701-(immedNumber)

	jmp 32767
	jmp -32768	

;[error: comma befor first operand and after last operand]
;	line 707,708-(befor first operand)
;	line 709,710-(after last operand)

	jmp ,	$3
	jmp ,validLabel
	jmp 	$3, 
	jmp validLabel	,

;[error: too many operands]
;	line 715,716,717-(more then 1 operand)

	jmp $3 ,validLabel
	jmp 	validLabel , $6,validLabel
	jmp 		$5	,	$9,validLabel, $5,validLabel

;[error: not enough operands]
;	line 722-(no operand instead of 1)

	jmp 


;*** test J commands: la, call ***

;[error: invalid label]
;	line 730,732-(label does not exist)

	la notExistLabel

	call notExistLabel

;[error: invalid operand]
;	line 738,741-(immedNumber)
;	line 739,742-(reg)

	la 32767
	la $2

	call -32768	
	call $5

;[error: comma befor first operand and after last operand]
;	line 748,751-(befor first operand)
;	line 749,752-(after last operand)

	la ,	validLabel
	la validLabel,

	call 	, validLabel 
	call validLabel	,

;[error: too many operands]
;	line 757,759-(more then 1 operand)

	la validLabel ,validLabel

	call 	validLabel , validLabel,validLabel

;[error: not enough operands]
;	line 764,766-(no operand instead of 1)

	la

	call

;*** test J commands: stop ***

;[error: invalid operand / too many operands]
;	line 775,776-(immedNumber)
;	line 777-(reg)
;	line 778-(validLabel)

	stop 32767
	stop -32768
	stop $2
	stop validLabel	

;******************** test ilegal commands ********************
;	line 784,785,786,787,788,789,790,791-(ilegal commands)
;	line 792-(no space between the command and the first operand)

	aDd $3,$19,$8
	Sub $3,$19,	$8
	andd	 $3,$19,$8			
	OR $3,	$3,$3
	noR $3,$7,$8
mov $3,$19
mvHi $3,$8	   	
mvvlo $19 ,	$19 
  mvlo$8 , $19	
