;name: Revital Maor, ID: 316541168 ; name: Rajaa Ghanem, ID: 204668529

;file ps.as
;sample source code

.entry	Next
.extern	wNumber
STR:	.asciz	"aBcd"
MAIN:	add	$3,$5,$9
LOOP:	ori	$9,-5,$2
	la	vall
	jmp	Next
Next:	move	$20,$4
LIST:	.db	6,-9
	bgt	$4,$2,END
	la	K
	sw	$0,4,$10
	bne	$31,$9,LOOP
	call	vall
	jmp	$4
	la	wNumber
.extern	vall
	.dh	27056
K:	.dw	31,-12
END:	stop
.entry	K
