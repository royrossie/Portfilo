/*!
	Created by Bogdan Belash for KIST in 2020

	additional header file to connect make-ldpc.c, print-pchk.c, generate_fresh_key_alice.c files with main program
	external variables to use in functions everywhere
*/

void gen_fresh_key (void);									//main function in generate_fresh_key_alice.c file
int ldpc (char *, int, int, int, char *, char *);			//main function in make-ldpc.c file
int printldpc (char *, int);								//main function in print-pchk.c file

#define message 1000										//length of message; must be only even number
#define my_method "evenboth"								//method how to create matrix: evencol or evenboth											
#define my_seed 1											//seed will use 1 every time

char my_H [10][20];											//variable to save H matrix
char my_S [message];										//variable to save Alice's random message
