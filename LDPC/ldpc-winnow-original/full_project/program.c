/*
	Created by Bogdan Belash for KIST in 2020

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "program.h"

int main (void) {
	int i, j, d, r, c, k, m, h, a, b;
	int qber_c, message_c, bit_c, same_1, same_2, change_1, change_2, change_3, found_m_1, found_m_2, found_m_3, found_s, good_c, good_c_2, all_c, all_c_2;	
	int same_syndrome;										
	int divided_my_S[50][20];							//array with divided message from original 1000-bit message
	int changed_S [message];							//here we save all changed messages
	int divided_changed_s [50][20];
	int my_syndrome [10];								//variable to save syndrome
	int changed_syndrome [10];							//here we save all changed syndromes
	int new_s [20];
	int new_syndrome [10], final_syndrome [10];
	int M = 10, N = 20;									//quantity of rows and columns in H matrix
	char *file = "make-ldpc";							//name of file, where save H matrix; inreadable for human
	long random_n;
	
	FILE *result_file, *summary_file, *summary_file_2, *qber_file, *qber_file_2;
	char result_name [100], summary_name [100], summary_name_2 [100], qber_name [100], qber_name_2 [100];
	
	random_n = time(NULL);								//initial seed from time

	//generate random fresh key from Alice
	gen_fresh_key ();	

	//divide original message for 50 parts, 20 bits in every part
	d = 0;
	for (i = 0; i < 50; i++) {
		for (j = 0; j < 20; j++) {
			divided_my_S [i][j] = (int) my_S[d];
			d++;
		}
	}

	//creating 10x20 H matrix with 4 "ones" in each column, seed is 1
	ldpc (file, M, N, my_seed, my_method, "4");
	printldpc (file, 4);
	
	sprintf (summary_name, "result.dat");
	summary_file = fopen (summary_name, "w");
	sprintf (summary_name_2, "result_2.dat");
	summary_file_2 = fopen (summary_name_2, "w");
	sprintf (qber_name, "qber.dat");
	qber_file = fopen (qber_name, "w");
	sprintf (qber_name_2, "qber_2.dat");
	qber_file_2 = fopen (qber_name_2, "w");

	//creating error bits for original message
	for (qber_c = 1; qber_c <= 250; qber_c++) {					//QBER from 0.1% to 25%
		fprintf (summary_file, "%d ", qber_c);		
		fprintf (summary_file_2, "%d ", qber_c);	
		fprintf (qber_file, "%d ", qber_c);		
		fprintf (qber_file_2, "%d ", qber_c);	
		
		good_c_2 = 0;	
		
		all_c_2 = 0;
				
		//100 repeats to check changed messages
		for (message_c = 1; message_c <= 100; message_c++) {	
			good_c = 0;
			all_c = 0;
	
			sprintf (result_name, "results/%d/%d.dat", qber_c, message_c);
			result_file = fopen (result_name, "w");		
					
			//creating message with error bits	
			for (i = 0; i < message; i++) {							
				srand(random_n);
				
				r = rand() % message;

				random_n = rand();									//random_n has new number, because system time with 1 secound is not enough

				if (r < qber_c) {
					if (0 == (int) my_S[i]) {
						changed_S[i] = 1;
					}
					else {
						changed_S[i] = 0;
					}

				}
				else {
					changed_S[i] = (int) my_S[i];
				}
			}
			
			same_syndrome = 0;
			
			//divide changed message for 50 parts	
			d = 0;
			for (i = 0; i < 50; i++) {							
				for (j = 0; j < 20; j++) {
					divided_changed_s [i][j] = changed_S[d];
					d++;
				}
				
				//create syndrome from part of original message
				k = 0;
				m = 0;
				for (j = 0; j < 10; j++) {
					for (h = 0; h < 20; h++) {
						k = (int) my_H [j][h] * divided_my_S[i][h];
						m ^= k;
					}

					my_syndrome [j] = m;

					m = 0;
				}

				//create syndrome from part of changed message
				k = 0;
				m = 0;
				for (j = 0; j < 10; j++) {
					for (h = 0; h < 20; h++) {
						k = (int) my_H [j][h] * divided_changed_s [i][h];
						m ^= k;
					}

					changed_syndrome [j] = m;

					m = 0;
				}

				//compare syndromes	
				c = 0;					
				for (j = 0; j < 10; j++) {
					if (changed_syndrome [j] == my_syndrome [j]) {						
						c++;
					}
				}
						
				if (10 == c) {
//					same_syndrome++;
					fprintf (result_file, "In %d same SYNDROME\n", i + 1);
					good_c++;
				}	
				else {
					found_m_1 = 0;
					found_m_2 = 0;
					found_m_3 = 0;
				
					for (change_1 = 0; change_1 < 20; change_1++) {
						for (j = 0; j < 20; j++) {
							new_s [j] = divided_changed_s [i][j];
						}
						
						//changing 1 bit in changed message to find original message
						if (0 == new_s [change_1]) {
							new_s [change_1] = 1;
						} 
						else {
							new_s [change_1] = 0;
						}
						
						//create new syndrome from original message
						k = 0;
						m = 0;
						for (j = 0; j < 10; j++) {
							for (h = 0; h < 20; h++) {
								k = (int) my_H [j][h] * new_s [h];
								m ^= k;
							}

							new_syndrome [j] = m;

							m = 0;
						}	
						
						same_1 = 0;
						
						for (bit_c = 0; bit_c < 10; bit_c++) {
							if (new_syndrome [bit_c] == my_syndrome [bit_c]) {
								same_1++;
							}
						}	
						
						if (10 == same_1) {
							same_2 = 0;
							
							for (j = 0; j < 20; j++) {
								if (new_s [j] == divided_my_S [i][j]) {
									same_2++;
								}
							}
							
							if (20 == same_2) {
								fprintf (result_file, "In %d ONE error, ", i + 1);
								found_m_1++;
//								good_c++;
								a = change_1;
//								break;

								//checking 1 bit another method (by syndrome)
								found_s = 0;
								
								for (j = 0; j < 20; j++) {
									new_s [j] = divided_changed_s [i][j];
								}
								
								for (j = 0; j < 10; j++) {
									final_syndrome [j] = changed_syndrome [j] ^ my_syndrome [j];
								}	
								
								for (j = 0; j < 20; j++) {
									for (h = 0; h < 10; h++) {
										if (final_syndrome [h] == my_H [h][j]) {
											found_s++;
										}
									}
									
									if (10 == found_s) {
										b = j;
										
										if (a == b) {
											fprintf (result_file, "syndrome also same with matrix column\n");
										}
										else {
											fprintf (result_file, "syndrome IS NOT SAME with matrix column\n");
										}
										
//										break;
									}
									
									found_s = 0;
								}
							}
						}
						
																	
						
						//changing 2 bits in changed message to find original message						
						for (change_2 = change_1 + 1; change_2 < 20; change_2++) {
							for (j = change_1 + 1; j < 20; j++) {
								new_s [j] = divided_changed_s [i][j];
							}
							
							if (0 == new_s [change_2]) {
								new_s [change_2] = 1;
							} 
							else {
								new_s [change_2] = 0;
							}							
				
							k = 0;
							m = 0;
							for (j = 0; j < 10; j++) {
								for (h = 0; h < 20; h++) {
									k = (int) my_H [j][h] * new_s [h];
									m ^= k;
								}

								new_syndrome [j] = m;

								m = 0;
							}
							
							same_1 = 0;
							
							for (bit_c = 0; bit_c < 10; bit_c++) {
								if (new_syndrome [bit_c] == my_syndrome [bit_c]) {
									same_1++;
								}
							}	
							
							if (10 == same_1) {
								same_2 = 0;
								
								for (j = 0; j < 20; j++) {
									if (new_s [j] == divided_my_S [i][j]) {
										same_2++;
									}
								}
								
								if (20 == same_2) {
								//	fprintf (result_file, "In %d TWO errors\n", i + 1);
									found_m_2++;
//									good_c++;
//									break;
								}
							}	
							
							//changing 3 bits in changed message to find original message
							for (change_3 = change_2 + 1; change_3 < 20; change_3++) {
								for (j = change_2 + 1; j < 20; j++) {
									new_s [j] = divided_changed_s [i][j];
								}
								
								if (0 == new_s [change_3]) {
									new_s [change_3] = 1;
								} 
								else {
									new_s [change_3] = 0;
								}							
					
								k = 0;
								m = 0;
								for (j = 0; j < 10; j++) {
									for (h = 0; h < 20; h++) {
										k = (int) my_H [j][h] * new_s [h];
										m ^= k;
									}

									new_syndrome [j] = m;

									m = 0;
								}
								
								same_1 = 0;
								
								for (bit_c = 0; bit_c < 10; bit_c++) {
									if (new_syndrome [bit_c] == my_syndrome [bit_c]) {
										same_1++;
									}
								}	
								
								if (10 == same_1) {
									same_2 = 0;
									
									for (j = 0; j < 20; j++) {
										if (new_s [j] == divided_my_S [i][j]) {
											same_2++;
										}
									}
									
									if (20 == same_2) {
										//fprintf (result_file, "In %d THREE errors\n", i + 1);
										found_m_3++;
//										good_c++;
//										break;
									}
								}															
							}														
						}											
					}
					
					if ((0 == found_m_1) && (0 == found_m_2) && (0 == found_m_3)) {
						fprintf (result_file, "In %d MORE errors\n", i + 1);
						all_c += 4;				
					}
					else if (1 == found_m_1) {
						fprintf (result_file, "In %d STILL OKAY\n", i + 1);
						good_c++;
						all_c++;
					}
					else if (found_m_1 > 1) {
						fprintf (result_file, "In %d more than ONE error!\n", i + 1);		
						all_c += 4;			
					}
					else if (1 == found_m_2) {
						fprintf (result_file, "In %d TWO errors\n", i + 1);	
						good_c++;
						all_c += 2;				
					}
					else if (found_m_2 > 1) {
						fprintf (result_file, "In %d more than TWO error!\n", i + 1);	
						all_c += 4;									
					}
					else if (1 == found_m_3) {
						fprintf (result_file, "In %d THREE errors\n", i + 1);
						good_c++;
						all_c += 3;										
					}
					else if (found_m_3 > 1) {
						fprintf (result_file, "In %d more than THREE error!\n", i + 1);	
						all_c += 4;									
					}
				}
			}	
			
			fclose (result_file);	
			
			fprintf (summary_file, "%d ", good_c);	
			
			fprintf (qber_file, "%d ", all_c);
			
			good_c_2 += good_c;
			
			all_c_2 += all_c;
		}
		
		
		
		fprintf (summary_file, "\n");
		
		fprintf (qber_file, "\n");
		
		fprintf (summary_file_2, "%d\n", good_c_2 / 100);
		
		fprintf (qber_file_2, "%d\n", all_c_2 / 100);
	}
	
	fclose (summary_file);	
	fclose (summary_file_2);
	fclose (qber_file);
	fclose (qber_file_2);		
}				
