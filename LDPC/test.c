/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */


#include <stdio.h>
#include <stdlib.h>
#include "xil_io.h"
#include "platform.h"
#include "xil_printf.h"

#include "xparameters.h"

#include "xil_types.h"
#include "xgpiops.h"
#include <time.h>
#include <sleep.h>
#include <inttypes.h>

#define message 1000

#define BRAMBASE XPAR_BRAM_0_BASEADDR
#define BRAMHIGH XPAR_BRAM_0_HIGHADDR
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR 0x40000000U
/*
int main()//initialize bram memory load
{
    int i,k, j;*/

    /*
    //XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR은 axi_bram_ctrl_0의 주소.
    //Xil_Out32은 axi_bram_ctrl_0을 제어해서 blk_mem_gen_0에 데이터를 씀.
    for(i=0; i<1000; i+=32)
    {
       Xil_Out32(XPAR_BRAM_0_BASEADDR+i, 0x00000001);     //굳이 안써도 됨.
    }
    //XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR은 axi_bram_ctrl_1의 주소.
    //Xil_In32는 axi_bram_ctrl_0을 제어해 blk_mem_gen_0 데이터 읽음.
    //PS,PL는 blk_mem_gen_0에서 데이터를 공유
    for(i=0; i<1000; i+=32)
    {
	   k=Xil_In32(XPAR_BRAM_0_BASEADDR+i);  //XPAR_BRAM_0_BASEADDR 0x40000000U
	   //xil_printf( "\n bram address %x => %d \n\r",XPAR_BRAM_0_BASEADDR+i,k);

	   for(j=0; j<32; j++)
	   {
		   xil_printf( "\n %x , %d \n\r",XPAR_BRAM_0_BASEADDR+i+j, k & 0x00000001);
		   k=k>>1;
	   }
    }

   return 0;
}*/
/*
    for (i = 0; i < 1000; i++){
    		k = Xil_In32(XPAR_BRAM_0_BASEADDR+i*4);
    		xil_printf( "\n bram address %x => %d \n\r",XPAR_BRAM_0_BASEADDR+i*4,k);

    	}
    return 0;
}
*/
/*
for (i = 0; i < 1000; i++){
		k = Xil_In8(XPAR_BRAM_0_BASEADDR+i);
		xil_printf( "\n bram address %x => %d \n\r",XPAR_BRAM_0_BASEADDR+i,k);

	}*/


int main(void) {
	//initialize variables
	int i,j,d,k,h,r,s,m;
	int bit1, bit2;
	int result[50];
	int found = 0;
	int Alice_key[message], Bob_key[message];
	int divided_Alice_key[50][20], divided_Bob_key[50][20];
	int Alice_syndrome[50][10], Bob_syndrome[50][10];
	int divided_Bob_test_key[20];
	int Bob_test_syndrome[10];
	int check_vector[10];
	int corrected_size = 0;	//size of sifted key array
	int *Alice_corrected_key, *Bob_corrected_key;
	long ltime;

	//here take alice sifted key from file
	for (i = 0; i < message; i++){
		Alice_key[i] = Xil_In32(XPAR_BRAM_0_BASEADDR+i*4);
		xil_printf( "\n bram address %x => %d \n\r",XPAR_BRAM_0_BASEADDR+i*4,Alice_key[i]);

	}

	printf("Alice Key is : \n");
//////////////////////////
	for(i=0;i<message;i++){
		printf("%d",Alice_key[i]);
	}
	printf("\n");

	for (i = 0; i < message; i++) {
			srand(ltime);
			r = rand() % message;
			ltime = rand();	//ltime has new number, because system time with 1 secound is not enough

			if (r < 50) {
				if (0 == Alice_key[i]) {
					Bob_key[i] = 1;
				}
				else {
					Bob_key[i] = 0;
				}
			}
			else {
				Bob_key[i] = Alice_key[i];
			}
		}
	//check bob sifted key
	printf("Bob Key is : \n");
	for(i=0;i<message;i++){
		printf("%d",Bob_key[i]);
	}
	printf("\n");

	//initializing parity-check matrix by an array in memtory
	int H_matrix[10][20]={
		{1,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
		{0,1,0,0,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1},
		{0,0,0,0,0,1,0,0,1,0,1,1,0,1,1,0,0,1,1,0},
		{1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,1},
		{0,0,0,0,1,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0},
		{1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,1,0,1,0,0},
		{0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,0,0,0},
		{0,1,1,1,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,1},
		{1,0,1,0,0,1,1,0,1,0,1,1,1,1,0,0,0,0,0,0},
		{0,1,1,0,0,1,0,0,1,1,0,0,0,1,0,0,1,0,1,0}
	};

	//divide alice's key for 50 parts for more convenient
	//calc part
	d = 0;
	for (i = 0; i < 47; i++) {
		for (j = 0; j < 20; j++) {
			divided_Alice_key [i][j] = Alice_key[d];
			d++;
		}
		//create syndrome from part of original message
		for (j = 0; j < 10; j++) {
			k = 0;
			for (h = 0; h < 20; h++) {
				k ^= H_matrix [j][h] * divided_Alice_key[i][h];
			}
			Alice_syndrome [i][j] = k;
		}
		i=i;
	}

	//check alice divided key
	printf("Alice divided keys are : \n");
	for(i = 0; i < 47; i++){
		for (j = 0; j < 20; j++) {
			printf("%d ", divided_Alice_key[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//check alice syndromes
	printf("Alice syndromes are : \n");
	//problem
	for(i = 0; i < 47; i++){
		printf ("%d ", i);
		for (j = 0; j < 10; j++) {
			xil_printf("%d ", Alice_syndrome [i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//divide bob's key for 50 parts for more convenient
	d = 0;
	for (i = 0; i < 47; i++) {
		for (j = 0; j < 20; j++) {
			divided_Bob_key [i][j] = Bob_key[d];
			d++;
		}
		//create syndrome from part of original message
		for (j = 0; j < 10; j++) {
			k = 0;
			for (h = 0; h < 20; h++) {
				k ^= H_matrix [j][h] * divided_Bob_key[i][h];
			}
			Bob_syndrome [i][j] = k;
		}
	}
	//check bob syndromes
	printf("Bob syndromes are : \n");
	for(i = 0; i < 47; i++){
		for (j = 0; j < 10; j++) {
			printf("%d ", Bob_syndrome [i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//clear result array that will be sended to alice
	for (i = 0; i < 47; i++){
		result [i] = 1;
	}

	for (i = 0; i < 47; i++) {
		printf ("%d ", result[i]);
	}
	printf("\n");



	//compare alice and bob syndromes//heere
	for (i = 0; i < 47; i++) {

		//this part for checking alice and bob message, DELETE later
		printf("alice syndrome # %d\n", i);
		for (j = 0; j < 10; j++) {
			printf("%d ", Alice_syndrome[i][j]);
		}
		printf("\n");
		printf("bob syndrome # %d\n", i);
		for (j = 0; j < 10; j++) {
			printf("%d ", Bob_syndrome[i][j]);
		}
		printf("\n");
		//end of this part

		found = 0;

		s = 0;
		for (j = 0; j < 10; j++) {
			if (Bob_syndrome[i][j] == Alice_syndrome[i][j]) {
				s++;
			}
		}
		//if syndromes are same, save result to result array and start compare next syndromes
		if (10 == s) {
			found++;

			result[i] = 0;

			//this part for checking alice and bob message, DELETE later
			printf("syndromes # %d are same\n\n", i);
			//end of this part
		}
		else {
			//checking syndrome by 1-bit error
			//firstly, we do XOR between alice and bob syndrome to fins new vector; this vector we will compare with H matrix
			for (j = 0; j < 10; j++) {
				check_vector[j] = Alice_syndrome[i][j] ^ Bob_syndrome[i][j];
			}

			//in this cycle we check matrix with comparing bob syndrome with every column in H matrix; we try to recognize 1 error if it is
			for (j = 0; j < 20; j++) {
				//check syndrome and every column in matrix to find one error
				s = 0;

				for(k = 0; k < 10; k++){
					if (check_vector[k] == H_matrix[k][j]){
						s++;
					}
				}

				//if some column of matrix and syndrome are same - we found 1 error
				if (10 == s) {
					found = 1;

					//change error bit in bob message
					if (0 == divided_Bob_key[i][j]){
						divided_Bob_key[i][j] = 1;
					}
					else{
						divided_Bob_key[i][j] = 0;
					}

					//this part for checking alice and bob message, DELETE later
					printf("messages # %d were different by *ONE* bit. check it now: \n", i);
					//creating a new syndrome for checking
					for (k = 0; k < 10; k++) {
						m = 0;
						for (h = 0; h < 20; h++) {
							m ^= H_matrix [k][h] * divided_Bob_key[i][h];
						}
						Bob_syndrome [i][k] = m;
					}
					printf("alice syndrome # %d\n", i);
					for (k = 0; k < 10; k++) {
						printf("%d ", Alice_syndrome[i][k]);
					}
					printf("\n");
					printf("bob syndrome # %d\n", i);
					for (k = 0; k < 10; k++) {
						printf("%d ", Bob_syndrome[i][k]);
					}
					printf("\n\n");
					//end of this part

					break;
				}
			}
			if (1 == found) {
				result[i] = 0;
			}
			else {
				found = 0;
				//checking syndrome by 2-bits error

				//in this part we will change step-by-step bits for recognizing errors
				//we change any one bit in bob message untill find correct syndrome
				for (bit1 = 0; bit1 < 20; bit1++) {
					//save temporal bob message from original message
					for (j = 0; j < 20; j++) {
						divided_Bob_test_key[j] = divided_Bob_key[i][j];
					}

					//change first bit in temporal bob message
					if (0 == divided_Bob_test_key[bit1]) {
						divided_Bob_test_key[bit1] = 1;
					}
					else {
						divided_Bob_test_key[bit1] = 0;
					}

					//clean bob test syndrome
					for (j = 0; j < 10; j++) {
						Bob_test_syndrome[j] = 0;
					}

					//create new test syndrome from bob test message
					for (j = 0; j < 10; j++) {
						k = 0;

						for (h = 0; h < 20; h++) {
							k ^= H_matrix [j][h] * divided_Bob_test_key[h];
                        }

                        Bob_test_syndrome [j] = k;
                	}

		 			//do XOR between alice and bob test syndrome to fins new vector; this vector we will compare with H matrix
					for (j = 0; j < 10; j++) {
						check_vector[j] = Alice_syndrome[i][j] ^ Bob_test_syndrome[j];
					}

					//in this cycle we check matrix with comparing check vector with every column in H matrix; we try to recognize 2 error if it is
					for (j = 0; j < 20; j++) {
						//check vector and every column in matrix to find one error
						s = 0;

						for (k = 0; k < 10; k++){
							if (check_vector[k] == H_matrix[k][j]){
								s++;
							}
						}

						//if some column of matrix and syndrome are same - we found 2 errors
						if (10 == s) {
							found++;

							//change second error bit in bob test message
							if (0 == divided_Bob_test_key[j]){
								divided_Bob_test_key [j] = 1;
							}
							else{
								divided_Bob_test_key [j] = 0;
							}

							//write result to bob array
							for (k = 0; k < 20; k++) {
								divided_Bob_key[i][k] = divided_Bob_test_key[k];
							}

							//this part for checking alice and bob message, DELETE later
							printf("messages # %d were different by **TWO** bit. check it now: \n", i);
							//creating a new syndrome for checking
							for (k = 0; k < 10; k++) {
								m = 0;

								for (h = 0; h < 20; h++) {
									m ^= H_matrix [k][h] * divided_Bob_test_key[h];
								}
								Bob_syndrome [i][k] = m;
							}
							printf("alice syndrome # %d\n", i);
							for (k = 0; k < 10; k++) {
								printf("%d ", Alice_syndrome[i][k]);
							}
							printf("\n");
							printf("bob syndrome # %d\n", i);
							for (k = 0; k < 10; k++) {
								printf("%d ", Bob_syndrome[i][k]);
							}
							printf("\n\n");
							//end of this part

							break;
						}
					}

					if (1 == found) {
						result[i] = 0;
					}
					else {
						result[i] = 1;
					}
				}
			}
		}

		if (0 == found){
			printf("DID NOT FOUND SOLUTION!!!\n\n");
		}
	}

	for (i = 0; i < 47; i++) {
		printf ("%d ", result[i]);
	}
	printf("\n");

	//check size of good and bad cases
	for (i = 0; i < 50; i++) {
		if (0 == result[i]) {
			corrected_size++;
		}
	}

	//receiving result of bob error correction
	//in this part receive information from bob by xilinx socket

	printf ("result of correction is:\n");
	for (i = 0; i < 47; i++) {
		printf("%d ", result[i]);
	}
	printf ("\n");

	//check size of good and bad cases
	for (i = 0; i < 47; i++) {
		if (0 == result[i]) {
			corrected_size++;
		}
	}

	printf("Size of final corrected key is: %d\n\n", corrected_size);

	//create a dynamic array for alice corrected key
	Alice_corrected_key = (int*)malloc(20 * corrected_size * sizeof(int));

	//put corrected messages to alice corrected key
	k = 0;
	for (i = 0; i < 47; i++) {
		if (0 == result[i]) {
			for (j = 0; j < 20; j++) {
				Alice_corrected_key[k] = divided_Alice_key[i][j];
				k++;
			}
		}
	}

	//create a dynamic array for Bob corrected key
	Bob_corrected_key = (int*)malloc(20 * corrected_size * sizeof(int));

	//put corrected messages to bob corrected key
	k = 0;
	for (i = 0; i < 47; i++) {
		if (0 == result[i]) {
			for (j = 0; j < 20; j++) {
				Bob_corrected_key[k] = divided_Bob_key[i][j];
				k++;
			}
		}
	}
}
