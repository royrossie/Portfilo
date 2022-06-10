/* PRINT-PCHK.C - Print the parity check matrix for a code. */

/* Copyright (c) 1995-2012 by Radford M. Neal.
 *
 * Permission is granted for anyone to copy, use, modify, and distribute
 * these programs and accompanying documents for any purpose, provided
 * this copyright notice is retained and prominently displayed, and note
 * is made of any changes made to these programs.  These programs and
 * documents are distributed without any warranty, express or implied.
 * As the programs were written for research purposes only, they have not
 * been tested to the degree that would be advisable in any important
 * application.  All use of these programs is entirely at the user's own
 * risk.
 */

/* 
	Changed for research by Bogdan Belash in KIST, 2020.

	What differences:
		added header file "program.h" for connect this file with main program;
		main function changed name to "printldpc";
		instead "argc" and "argv" arguments function receives exactly:
			pchk-file, this file is created from "make-ldpc.c" program;	
		deleted loop for checkink -d and -t keys, instead it -d key can manuanly changed in program (dprint 1 or 0);
		commented code to print parity-check matrix in a terminal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rand.h"
#include "alloc.h"
#include "open.h"
#include "mod2sparse.h"
#include "mod2dense.h"
#include "mod2convert.h"
#include "rcode.h"
#include "program.h"

//void usage(void);


/* MAIN PROGRAM. */

int printldpc (char *main_ldpc_file, int ones) {
  mod2dense *D;
  mod2sparse *T;

  char *pchk_file;
  int dprint, trans;

  dprint = 1;						//changed here for dense or not dense format
  trans = 0;
				
  read_pchk(main_ldpc_file);

  if (trans)
  { T = mod2sparse_allocate(N,M);
    mod2sparse_transpose(H,T);
  }

  if (dprint)
  { if (trans)
    { D = mod2dense_allocate(N,M);
      mod2sparse_to_dense(T,D);
      printf("\nTranspose of parity check matrix in %s (dense format):\n\n",
             pchk_file);
      mod2dense_print(stdout,D, ones);
    }
    else
    { D = mod2dense_allocate(M,N);
      mod2sparse_to_dense(H,D);
   //   printf("\nParity check matrix in %s (dense format):\n\n",pchk_file);			//commented code to print parity-check matrix in a terminal
      mod2dense_print(stdout,D, ones);
    }
  }
  else /* sparse */
  { if (trans)
    { printf("\nTranspose of parity check matrix in %s (sparse format):\n\n",
             pchk_file);
      mod2sparse_print(stdout,T);
    }
    else
    { printf("\nParity check matrix in %s (sparse format):\n\n",pchk_file);
      mod2sparse_print(stdout,H);
    }
  }

//  printf("\n");

  return 0;
}


/* PRINT USAGE MESSAGE AND EXIT. */

/*void usage(void)
{ fprintf(stderr,"Usage: print-pchk [ -d ] [ -t ] pchk-file\n");
  exit(1);
}*/
