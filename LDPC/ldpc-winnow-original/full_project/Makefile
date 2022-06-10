COMPILE	= gcc -c -g	# command to compile a module from .c to .o
LINK =    gcc -g    # command to link a program

progs:	modules
	$(COMPILE) 	program.c
	$(LINK) 		make-ldpc.o print-pchk.o rcode.o alloc.o intio.o open.o \
				mod2dense.o mod2sparse.o mod2convert.o distrib.o rand.o \
				generate_fresh_key_alice.o program.o -lm -o program

modules:
	$(COMPILE)	make-ldpc.c
	$(COMPILE)	print-pchk.c
	$(COMPILE)	rcode.c
	$(COMPILE)	alloc.c
	$(COMPILE)	intio.c
	$(COMPILE)	open.c
	$(COMPILE)	mod2dense.c
	$(COMPILE)	mod2sparse.c
	$(COMPILE)	mod2convert.c
	$(COMPILE)	distrib.c
	$(COMPILE)	-DRAND_FILE=\"`pwd`/randfile\" rand.c
	$(COMPILE)	generate_fresh_key_alice.c

clean:
	rm -f  *.o program *.dat 

