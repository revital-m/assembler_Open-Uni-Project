# replace filenames in the following lists with your own file names

EXEC_FILE = assembler
C_FILES = main.c firstPass.c secondPass.c directive.c command.c outPutPrint.c tools.c
H_FILES = assembler.h main.h firstPass.h directive.h command.h secondPass.h outPutPrint.h tools.h

# if there are no header files, change the previous line to: H_FILES =

# ==> to flush stdout after each line, insert in main() the statement: FLUSH_STDOUT;
# ==> to flush stderr after each line, insert in main() the statement: FLUSH_STDERR;

#--------------------------------------------
# no changes should be made beyond this line

# definitions for flushing after earch line
D_OFLUSH = -DFLUSH_STDOUT='setvbuf(stdout,NULL,_IOLBF,BUFSIZ);'
D_EFLUSH = -DFLUSH_STDERR='setvbuf(stderr,NULL,_IOLBF,BUFSIZ);'
D_FLUSH = $(D_OFLUSH) $(D_EFLUSH)

O_FILES = $(C_FILES:.c=.o)

all: $(EXEC_FILE)

$(EXEC_FILE): $(O_FILES)
	gcc -Wall -ansi -pedantic -g $(O_FILES) -o $(EXEC_FILE) -lm

%.o: %.c $(H_FILES)
	gcc -Wall -ansi -pedantic -g -c $(D_FLUSH) -o $@ $<

clean:
	rm -f *.o $(EXEC_FILE)
