// an inproved calculator
#define __STDC_WANT_LIB_EXT1__ 1
#include<stdio.h>           // sandard input/output
#include<string.h>          // for string functions
#include<ctype.h>           // for classifying characters
#include<stdlib.h>          // for converting strings to numeric values
#include<stdbool.h>         // for bool values
#include<math.h>            // for power() function
#define BUF_LEN 256         // length of input buffer

int main(void)
{
	char buf[BUF_LEN];      // input expression
	char op = 0;            //stores an operator
	size_t index = 0;       // index of the current character inbuf
	size_t to = 0;          // to index for copying buf to itself
	size_t buf_length = 0;  // length of the string in buf
	double result = 0.0;    // the result of an operation
	double number = 0.0;    // stores the value of number_string
	char* endptr = NULL;    // stores address of character following a number
	
	printf("to use this calculator, enter any expression with"
		                                    "or without spaces.");
	printf("\nan expression may include the operators");
	printf(" +, -, *, /, %%, or ^(raise to a power).");
	printf("\nuse  = at the beginning of a line to opera on ");
	printf("\nthe result of the previous calculation.");
	printf("\nenter quit to stop the calculator.\n\n");

	// the main calculator loop
	char *ptr = NULL;
	while(true)
	{
		ptr = fgets(buf, BUF_LEN, stdin);
		if(!ptr)           // check for read error
		{
			printf("error reading input.\n");
			return 1;
		}

		if(strcmp(buf,"quit\n") == 0) break;  // quit check
		buf_length = strnlen_s(buf, BUF_LEN); // get the input string length
		buf[--buf_length] = '\0';             // remove newline at the end

		// remove spaces from the input by copying the string to itself
		for(to = 0, index = 0; index <= buf_length; ++index)
		{
			if(*(buf + index) != ' ') // if it is not a space...
				*(buf + to++) = *(buf + index); // ...copy the character
		}

		buf_length = strnlen_s(buf,BUF_LEN); // get the new string length

		index = 0;          // start at the first character
		if(buf[index] == '=') // if there's = ...
			index++;  // ...skip over it
		else
		{
			// no =, so look for left operand
			result = strtod(buf + index, &endptr); // store the number
			index = endptr - buf; // get index for next character
		}

			// now look for 'op number' combinations
			while(index < buf_length)
			{
				op = *(buf + index++);  // get the operator
				number = strtod(buf + index, &endptr); // convert & store the number
				index = endptr - buf;  // get index for next character

				// execute the operation, as 'result op= number'
				switch(op)
				{
					case '+':    // addition
						result += number;
						break;
					case '-':    // subtraction
						result -= number;
						break;
					case '*':    // multiplication
						result *= number;
						break;
					case '/':    // division
						// check second operand for zero
						if(number == 0)printf("\n\n\aDivision bu zero error!\n");
						else
							result /= number;
						break;
					case '%':    // modulus operator - remainder
						// check second operand for zero
						if((long long)number == 0LL)printf("\n\n\aDivision bu zero error!\n");
						else
							result = (double)((long long)result % (long long)number);
						break;
					case '^':    // raise to a power
						result = pow(result,number);
						break;
					default:     // invalid operation or bad input
						printf("\n\n\aIllegal operation!\n");
						break;
				}
			}
		    printf("= %f\n",result);     // output the result
	}
	return 0;
}
