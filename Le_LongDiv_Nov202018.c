/*=====================================================================================================================================
FileName: Le_LongDiv_Oct2018.c
FileType: C Source File
Author : Dung Le
Created On : 10/20/2018 10:00:00 AM
Last Modified On : 11/28/2018 10:00:00 PM
Description : Displays steps for long division/Multiplication. Slight problems with division problems
Editor: Notepad++ Ver. 7.5.9
Complier: Raspbian 6.3.0
Kernel: Linux raspberrypi 4.9.59-v7+
=====================================================================================================================================*/

#include <stdio.h>
#include <math.h>

#define MAX_X			25
#define MAX_Y			5
#define MAX_SPACES		10

/*
	Starts off program
*/
void starter()
{
	printf("This program replicates steps to perform long division and problem by hand\n");
	printf("This program, however, only receives integer values from the user\n\n");
}	

/*
	Gathers User-Inputted Dividend/Divisor
*/
void gather_values(int *num1, int *num2)
{
	printf("Enter your dividend/factor 1: ");
	scanf(" %d", num1);
	printf("Enter your divisor/factor 2: ");
	scanf(" %d", num2);
}	

/*
	Counts total digits in integer; returns total amount of digits in integer
*/
int length_find(int num)
{
	int index = 0;   
	do{
		num /= 10;
		index++;
	} while(num > 0);

	return index;
}	

/*Prints dividing line for multiplication problem*/
void divider(int length)
{
	for(int spaces_ctr = 0; spaces_ctr < 10 - length; spaces_ctr++)
		printf(" ");
	for(int underscore_ctr = 0; underscore_ctr < length; underscore_ctr++)
		printf("_");
	printf("\n");
}	

int main()
{
	int counter, exponent, spaces_ctr, spaces_limit, underscore_ctr, negative_counter;
	int	length_dividend, length_divisor, length_product; //Amount of digits in dividend and divisor
	int index_dividend, index_divisor;	//Positions of indexes of separate dividend and divisor values
	int print_spaces;	//For printing steps of division
	
	int num1, num2; //User-inpuuted variables
	int num1_tmp_min = 0, quo; //num1 minuend and quotient
	int num2_tmp;
	int disp[MAX_X][MAX_Y];	//Array for numbers
	int produc_spaces;
	
	starter();
	gather_values(&num1, &num2);
	

	if(num2 == 0){
		printf("Division: Not possible because of division by 0\n");
		printf("Multiplication: %d * %d = 0\n", num1, num2);
	} else{
		negative_counter = 0;	//Determines how many negative numbers are in the equation
		//Deal with positive numbers in the function, add negatives later
		if(num2 < 0){	
			num2 = -num2;	
			negative_counter++;
		}	
		if(num1 < 0){
			num1 = -num1;
			negative_counter++;
		}	
		length_divisor = length_find(num2);	//Determines length of divisor
		length_dividend = length_find(num1);	//Determines length of dividend
		
		index_divisor = length_divisor - 1;	//Index begins at 0, so index begins at length - 1 goes to 0
		index_dividend = length_dividend - 1;	//Attaches index to length of dividend - 1
		
		print_spaces = length_divisor + 1;
		spaces_limit = 0;
		underscore_ctr = 0;

	/*
		Prints Division Problem
	*/
		printf("\nDivision:\n");
		
		/* Prints Quotient */
		for(spaces_ctr = 0; spaces_ctr < print_spaces + 3; spaces_ctr++)
				printf(" ");
		printf("%d\n", num1/num2);
		/* Prints Divisor, Dividend */		
		//Writes separate integers of divisor into separate array indexes
		int num2_print = num2;
		do{
			disp[index_divisor][1] = num2_print % 10;	//Isolates furthest right digit
			num2_print /= 10;	//Removes furthest right digit of num2
			index_divisor--;	//Moves to the left
		} while(num2_print != 0);	
		
		//Prints Divisor
		for(index_divisor = 0; index_divisor < length_divisor; index_divisor++){
			printf("%d", disp[index_divisor][1]);
		}
		
		printf(" | ");	//Splits Divisor and Dividend
		
		//Writes separate integers of dividend into separate array indexes
		int num1_print = num1;
		do{
			disp[index_dividend][2] = num1_print % 10;	//Isolates furthest right digit
			num1_print /= 10;	//Removes furthest right digit of num1
			index_dividend--;	//Moves to position to the left
		} while(num1_print != 0);	
		
		//Prints Dividend
		for(index_dividend = 0; index_dividend < length_dividend; index_dividend++){
			printf("%d", disp[index_dividend][2]);
		}	
		printf("\n");
		
		/* Prints steps of long division */	
		index_dividend = 0; //Resets to first position of dividend
		do{
			num1_tmp_min = num1_tmp_min * 10;
			num1_tmp_min = num1_tmp_min + disp[index_dividend][2];
			index_dividend++;
			print_spaces++;
		} while(num1_tmp_min < num2);

			
		for(counter = index_dividend; counter < length_dividend; counter++){
			quo = num1_tmp_min/num2; 
			num1_tmp_min = (num1_tmp_min - num2 * quo) * 10 + disp[index_dividend][2];
			for(spaces_ctr = 0; spaces_ctr < print_spaces; spaces_ctr++)
				printf(" ");
			printf("%d\n", num2 * quo);
			print_spaces++;
			for(spaces_ctr = 0; spaces_ctr < print_spaces; spaces_ctr++)
				printf(" ");
			printf("%d\n", num1_tmp_min);
			index_dividend++;
		}

		/* Prints Remainder */
		print_spaces++;
		for(spaces_ctr = 0; spaces_ctr < print_spaces; spaces_ctr++)
				printf(" ");
				
		printf("%d\n", num1 % num2);	
	/*
		Prints multiplication problem
	*/
		printf("\nMultiplication:\n");
		
		produc_spaces = MAX_SPACES;
		
		length_product = length_find(num1 * num2);	
		/* Prints factors; Needs to make sure numbers have correct alignment */
		for(spaces_ctr = 0; spaces_ctr < produc_spaces - length_dividend; spaces_ctr++)
			printf(" ");
		printf("%d\n", num1);
		printf("*");
		for(spaces_ctr = 0; spaces_ctr < produc_spaces - length_divisor - 1; spaces_ctr++)	
			printf(" ");
		printf("%d\n", num2);
		
		//Prints line dividing
		divider(length_product);
		
		/*Prints steps of multiplication*/
		length_product = length_find(num1 * num2);	
		
		exponent = 0;
		for(index_divisor = length_divisor - 1; index_divisor >= 0; index_divisor--){
			num2_tmp = disp[index_divisor][1];
			for(counter = 0; counter < exponent; counter++)
				num2_tmp *= 10;	
			num1_tmp_min = num1 * num2_tmp;
			
			for(spaces_ctr = 0; spaces_ctr < 10 - length_find(num1_tmp_min); spaces_ctr++)
				printf(" ");
			printf("%d\n", num1_tmp_min);
			
			spaces_limit++;
			exponent++;	
		
		}	
		
		//Prints line dividing
		divider(length_product);
		
		produc_spaces = MAX_SPACES;
		/*Prints product*/
		if(negative_counter == 1){
			printf("-");
			produc_spaces--;
		}	
		for(spaces_ctr = 0; spaces_ctr < produc_spaces - length_product; spaces_ctr++)
				printf(" ");
		printf("%d\n", num1 * num2);
	}	
}

