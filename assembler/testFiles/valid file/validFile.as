;name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529


entryLabel1: stop
	.extern externLabel1

	.asciz "" 
	add $3,$19,$8
add $5,$19,$8
 		add $31,$19,$8

	sub $3,$19,	$8
	sub $30		,$19,$8
	sub $31	,	$19	,	$8
	.dh 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1
	and	 $3,$19,$8				
 and     $30,  $19  ,$4
	and $8	,$19,		$8
	.entry entryLabel1
	or $3,	$3,$3
	or $3,$3	,$3
or $3,$3,$3	

	nor $3,$7,$8
	nor 		$30,$4,$4	
	nor $15	,	$19	,	$8

move $3,$19
	move	 $2,	$19
	   move $31,$31

mvhi $3,$8	   	
			mvhi $5	,	$19
 mvhi	 $31	,	$8	
aRealyLongLine: 	.dh 0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1
mvlo $19 ,	$19 
		mvlo 		$30	, $19	  
  mvlo $8 , $19	


addi $3,32767 ,$19
	addi $5,	-32768,	$19
 addi	$4	,	0	,	$19	

		subi $3, 32767, $8
subi $5,-32768,$6
Label8:  subi $31, 	-12,$8			

andi 		$5,32767,		$8
			andi $30 , -32768	 ,$7
 	andi $8,14,$8
	.entry entryLabel2
ori $3,32767,$19
		ori $8	,32767,	$19
 ori $19,-3,		$19

	nori $3,32767,$19
nori $5,	-32768,$13
                  nori $31,-700,$8

Label7: lb $5,32767,$8
        	lb $30 , -32768,$14
	lb $8,14    ,$15
	.asciz " a really long "string" "" : 34 ,76/ .,$#@!%^&*()_-=+ " 
	sb $3,32767,$19		
	Label6:	sb $16	,	-32768	,$19
	sb $17	,		0,$19
	.dw 2147483647	,	5,-17
	lw $3,32767,$8
		lw $5,	-32768,$5
	   lw $31,10    ,$8
	.asciz " " 
	sw $5,32767,$8
sw			$5,-32768,$18
	sw $8,		14,$20

	Label5:	lh $5,32767,$8
	lh $30,-32768,$21


 Label3:	 .db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

	sh $3,32767,$19
  sh $5,-32768,$23
			sh 	$31	,	-1	,	$8	


bne $3 ,$5,entryLabel1
	bne $7,$29 ,Label3

 Label4:  beq 	$3 , $6,entryLabel1
	beq $4,$5 	, Label7	
	.extern externLabel2

  blt 		$5	,	$9,entryLabel1
	blt $30 , $26   ,  validLabel
	.extern externLabel1
	bgt 	 $3 ,  $8 ,entryLabel1
	bgt $24,$28 ,	Label5			
	stop


		jmp 	$3
	jmp externLabel1
.dw -2147483648, 4 , 700,15 ,-32
  jmp 	entryLabel1
jmp 	validLabel



	la 	externLabel1
	la entryLabel1
la validLabel
		.db -11		,		30		,		45		,	0

	call 	 externLabel1
	call entryLabel1	
Label1:  .asciz " a really long "string" "" : 34 ,76/ .,$#@!%^&*()_-=+ " 
	call  validLabel	
		; Note line

.db 127,1,-56,	3	,-128

	lh $22,0,$19
	.dh 32767	,	5,-17
.dh -32768, 4 , 700,15 ,-32

validLabel: stop

	Label2:	.dw 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1


 .extern externLabel2
.asciz " a really long "string" "" : 34 ,76/ .,$#@!%^&*()_-=+ " 


	.entry entryLabel2
entryLabel2: stop

	.entry entryLabel2

.extern externLabel2
exactly31CharsInTheLabel1234567: addi $5,	-32768,	$19

