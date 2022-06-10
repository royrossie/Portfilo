/*!
	Created by Bogdan Belash for KIST in 2020

	Simple program to generate Alice's message from rand() funtion by using time
	It saves result to "fresh_key_alice.dat" file
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "program.h"

void gen_fresh_key (void) {
	long ltime;
	int i;
	extern char my_S [message];		//"message" is defined in "program.h" file

	FILE *S_file;

	ltime = time(NULL);	
	srand(ltime);

	S_file = fopen("fresh_key_alice.dat", "w");

	for (i = 0; i < message; i++) {
		my_S[i] = 0;
	//	my_S[i] = rand() % 2;
		fprintf (S_file,"%d",my_S[i]);
	}

	fclose(S_file);

}

