/*
    Kevin Lee
    Sample program for CSCI
    
    This program illustrates how ASCII characters,
    integers and floats are stored as binary bits.
    
    Some students find this a bit too much but I don't worry
    about their two-bit opinions!

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h> // Include this line to use strlen
#include <math.h>


//function prototypes
void printIntAsBinary(int source, int numBits); //function prototype
int pretendFloatIsInt(float x);
void printFloatBits(float x);
void showBinaryToDecimal(int source, int numBits);

void practice8bit2sInts(void);
void practice8bitSignMagInts(void);
void practice8bit1sComplement(void);

void practice8bit9sComplement(void);
void practice8bit10sComplement(void);
void practice8bit9sComplementArithmetic(void);

int intToNinesComplement(int numberIn);
int ninesComplementConvertSign(int);
int randRange(int numDigits);



float readBinFloat();

void eatLine();


int main()
{
  int choice;
  
   srand(time(NULL));
   
   do{
   		printf("\nWelcome to integers in binary forms\n");
   	    printf("1 for 1's complement practice\n");
		printf("2 for 2's complement practice\n");
		printf("3 for sign magnitude practice\n");
   	    printf("4 for 9's complement practice\n");
		printf("5 for 10's complement practice\n");
        printf("6 for 9's complement arithmetic practice\n");
        printf("9 for 9's TEST\n");
     	printf("0 to Quit\n");
     	scanf("%d", &choice);
   
   		if (choice == 1){
   			practice8bit1sComplement();
		}else 	if (choice == 2){
   			practice8bit2sInts();
		}else 	if (choice == 3){
   			practice8bitSignMagInts();
        } else if (choice == 4) {
            practice8bit9sComplement();
        } else if (choice == 5) {
            practice8bit10sComplement();
		} else if (choice == 6) {
            practice8bit9sComplementArithmetic();
        }// TODO: Test here
        else if (choice == 9){
   			printf("%d", randRange(2));
		}else if (choice == 0){
   			printf("Goodbye\n");
		}
   }while (choice != 0);
   	
    system("pause"); //warning! pause is a DOS command
	return EXIT_SUCCESS;  
}





/*
    given the source integer this function prints it out in binary 
    as ones and zeros
    
    numBits controls how many bits we want to printed, counted from
    the right
    
    it assumes that an int is 32 bits long
*/
void printIntAsBinary(int source, int numBits)
{
   unsigned int  mask = 0x00000001; 
   int i;
   
   if( numBits < 0 || numBits > 32) //do a little error checking
      printf("error in printIntAsBinary , numBits out of range\n");
   
   //first get the mask to the leftmost bit they want to see
   for( i = 2; i <= numBits; i++)
   {
         mask = mask << 1;
   }
   
   for( i = 1; i <= numBits; i++)
   {
      if (mask & source){ //test the bit at this position for a 1 or 0
            printf("1");
      }else 
            printf("0");
            
      if((numBits - i) % 4 == 0)
            printf(" ");
      mask = mask >> 1; //shift the mask to the right 1 place for the next bit
   
   }
   printf("\n");
}

void showBinaryToDecimal(int source, int numBits)
{
   unsigned int  mask = 0x00000001; 
   int i;
   int total = 0;
   int value = 1;
   
   if( numBits < 0 || numBits > 32) //do a little error checking
      printf("error in printIntAsBinary , numBits out of range\n");
   
   //first get the mask to the leftmost bit they want to see
   for( i = 2; i <= numBits; i++)
   {
         mask = mask << 1;
         value *= 2;
   }
   
   for( i = 1; i <= numBits; i++)
   {
      if (mask & source){ //test the bit at this position for a 1 or 0
            printf("%d + ", value);
            total += value;
      }
            
      mask = mask >> 1; //shift the mask to the right 1 place for the next bit
   	  value /= 2;
   }
   printf(" == %d\n", total);
}



/*
    first attempt, check if correct
*/

void printDoubleBits(double x)
{
     unsigned char *iPtr, mask = 0x1;
     int i,j;
     int count = 0;
     
     printf("x = %f\n", x);
     iPtr = (unsigned char*) &x; //take the address of x and pretend it is an integer
     iPtr += 7;
    
     
      for( i = 1; i <= 8; i++)
   {
           mask = 128;
      for(j = 1; j <= 8; ++j)
      {     
            ++count;
          if (mask & (*iPtr)){ //test the bit at this position for a 1 or 0
            printf("1");
          }else 
            printf("0");
            
            if(count == 1 ||  count == 12)
                   printf(" ");  
            
          if(j % 4 == 0)
            printf(" ");
           mask = mask >> 1; //shift the mask to the right 1 place for the next bit
      }
           
  //    printf("mask = %lld\n", mask);
      --iPtr;
   }
   printf("\n");   
}

/*
   Miserable function but it works

*/
void printFloatBits(float x)
{
    int source, *intPointer;

    intPointer = (int *) &x; //take the address of x and pretend it is an integer
    
    source = *intPointer; //transfer the value to result
 //   printIntAsBinary(result, 32);
    
   unsigned int  mask = 0x00000001; 
   int i;
   
   
   //first get the mask to the leftmost bit they want to see
   for( i = 2; i <= 32; i++)
   {
         mask = mask << 1;
   }
   
   for( i = 1; i <= 32; i++)
   {
      if (mask & source){ //test the bit at this position for a 1 or 0
            printf("1");
      }else 
            printf("0");
            
      if(i == 1 || i == 9)
            printf(" ");
      mask = mask >> 1; //shift the mask to the right 1 place for the next bit
   
   }
   printf("\n");
}



void eatLine()
{
	
	while(getchar() != '\n')
		; 
}

void practice8bitSignMagInts(void)
{
    int i, number, number1, answer, num_correct = 0;
    
    for( i = 0; i < 10; ++i)
    {
    	number = rand()% 255 + -127;
    	printf("What number does this sign magnitude form represent? ");
    	if (number < 0){
    		number1 = -number;
    		//now set bit 7 to indicate negative
    		number1 = number1 | 0x80;
		}else{
			number1 = number;
		}
    	printIntAsBinary(number1, 8);
    	scanf("%d", &answer);
    	if (answer == number){
    		printf("Smart!\n\n");
    		++num_correct;
		}else{
			printf("Sorry, the correct answer = %d, here is how\n", number);
			printIntAsBinary(number1, 8);
			if (number >= 0){
				printf("Since the leftmost bit is 0, this is a positive number.\n");
				printf("the remaining 7 bits tell you the magnitude\n");
			}else{
				printf("Since the leftmost bit is 1, this is a negative number.\n");
				printf("The remaining 7 bits tell you the magnitude\n");
			}
			printIntAsBinary(number1, 7);
			showBinaryToDecimal(number1, 7);
			printf("\n");
	    }
	}//for
	printf("You got %d out of 10\n", num_correct);
}


void practice8bit1sComplement(void)
{
    int i, number, number1, answer, num_correct = 0;
    
    for( i = 0; i < 10; ++i)
    {
    	number = rand()% 255 + -127;
    	printf("What number does this 1's complement form represent? ");
    	if (number < 0){
    		number1 = ~(-number); 
		}else{
			number1 = number;
		}
    	printIntAsBinary(number1, 8);
    	scanf("%d", &answer);
    	if (answer == number){
    		printf("Smart!\n");
    		++num_correct;
		}else{
			printf("Sorry, the correct answer = %d, here is how\n", number);
			printIntAsBinary(number1, 8);
			if (number >= 0){
				printf("Since the leftmost bit is 0, this is a positive number.\n");
				printf("The bits tell you the magnitude\n");
			}else{
				printf("Since the leftmost bit is 1, this is a negative number.\n");
				
				printf("You must form the 1's complement (flip the bits) to find the magnitude\n");
				number1 = ~number1;
				printIntAsBinary(number1, 8);
			}
			showBinaryToDecimal(number1, 8);
			printf("\n");
	    }
	}//for
	printf("You got %d out of 10\n", num_correct);
}

void practice8bit2sInts(void)
{
    int i, number, answer, num_correct = 0;
    
    for( i = 0; i < 10; ++i)
    {
    	number = rand()% 256 + -128;
    	printf("What number does this 2's complement form represent? ");
    	printIntAsBinary(number, 8);
    	scanf("%d", &answer);
    	if (answer == number){
    		printf("Smart!\n");
    		++num_correct;
		}else{
			printf("Sorry, the correct answer = %d, here is how\n", number);
			printIntAsBinary(number, 8);
			if (number >= 0){
				printf("Since the leftmost bit is 0, this is a positive number.\n");
				printf("The bits tell you the magnitude\n");
			}else{
				printf("Since the leftmost bit is 1, this is a negative number.\n");
				
				printf("You must first form the 1's complement (flip the bits)\n");
				number = ~number;
				printIntAsBinary(number, 8);
				printf("Then add 1 to get the 2's complement\n");
				number += 1;
				printIntAsBinary(number, 8);
			}
			showBinaryToDecimal(number, 8);
			printf("\n");
	    }
	}//for
	printf("You got %d out of 10\n", num_correct);	
}

// Function to convert an integer to its 9's complement
int intToNinesComplement(int randomNumber) {
    
    // Convert integer to string
    char numberString[8];
    sprintf(numberString, "%d", randomNumber); 
    
    int numStrLength = strlen(numberString);
    static char result[20]; // Assuming the maximum length of the resulting string won't exceed 20 characters
    
    // Calculate 9's complement
    for (int i = 0; i < numStrLength; i++) {
        result[i] = '9' - (numberString[i] - '0');
    } 
    result[numStrLength] = '\0'; // Null-terminate the string
    
    // Convert the resulting string back to an integer
    int intResult = atoi(result); 
    return intResult;
}

// Generates a number in range [lower, upper]
int randRange(int numDigits) { 
    int upper, lower; 

    upper = pow(10, numDigits) - 1;
    lower = pow(10, numDigits - 1);
    int num = (rand() % (upper - lower + 1)) + lower; 

    return num;
} 

// calculate the number of digits in a number
int numDigits(int number) {
    char* digitsString;
    int numDigitsInt;


    sprintf(digitsString, "%d", number);

    numDigitsInt = strlen(digitsString);
    
    return numDigitsInt;
}

int ninesComplementBigNumber (int randomNumber) {

    // Convert integer to string
    char numberString[8];
    sprintf(numberString, "%d", randomNumber); 
    
    int numStrLength = strlen(numberString);
    static char result[20]; // Assuming the maximum length of the resulting string won't exceed 20 characters
    
    // Calculate 9's complement
    for (int i = 0; i < numStrLength; i++) {
        // ASCII Code Subtraction for each index in the string
        result[i] = '9' - (numberString[i] - '0');
    } 
    result[numStrLength] = '\0'; // Null-terminate the string
    
    // Convert the resulting string back to an integer
    int intResult = atoi(result); 
    return (intResult + randomNumber);

}


int ninesComplementConvertSign(int numberIn) { // TODO: this should take big number as a parameter
    
    int ninesComplement = 0;
    int bigNumber = 0;

    // figure out the number of digits the int is and create a 'big' 9 number out of it
    bigNumber = ninesComplementBigNumber(numberIn);

    if (numberIn > (bigNumber/2)) {
        // if the number is bigNumber or greater convert it to negative 
        ninesComplement = intToNinesComplement(numberIn);
        return (ninesComplement * -1);
    } else{
        // just return the original number
        return numberIn;
    }
}

// Function to practice 9's complement
void practice8bit9sComplement(void) {
    int i, randomNumber, userAnswer, correctAnswer, num_correct = 0;

    // Loop for 10 iterations
    for (i = 0; i < 10; ++i) {
        // Generate a random number
        randomNumber = rand() % 256;
        
        printf("What number does this 9's complement form represent? \n");
        printf("%d \n", randomNumber);
        
        // Read user's answer
        scanf("%d", &userAnswer);
        
        // Get correct answer using 9's complement function
        correctAnswer = intToNinesComplement(randomNumber);
        
        // Check user's answer against correct answer
        if (correctAnswer == userAnswer) {
            printf("Smart!\n");
            ++num_correct;
        } else {
            printf("Sorry, the correct answer = %d\n", correctAnswer);
        }
    }
    printf("You got %d out of 10\n", num_correct);
}

// Function to practice 10's complement
void practice8bit10sComplement(void) {
    int i, randomNumber, userAnswer, correctAnswer, num_correct = 0;

    // Loop for 10 iterations
    for (i = 0; i < 10; ++i) {
        // Generate a random number
        randomNumber = rand() % 256;
        
        printf("What number does this 10's complement form represent? \n");
        printf("%d \n", randomNumber);
        
        // Read user's answer
        scanf("%d", &userAnswer);
        
        // Get correct answer using 9's complement function
        correctAnswer = intToNinesComplement(randomNumber);
        
        // Increment correct answer to simulate 10's complement
        ++correctAnswer;
        
        // Check user's answer against correct answer
        if (correctAnswer == userAnswer) {
            printf("Smart!\n");
            ++num_correct;
        } else {
            printf("Sorry, the correct answer = %d\n", correctAnswer);
        }
    }
    printf("You got %d out of 10\n", num_correct);
}

// Function to practice 9's complement addition
void practice8bit9sComplementArithmetic(void) {
    int i, randomNumber, randomAddend, userAnswer, correctAnswer, digits = 0;
    int num_correct = 0;
    // Loop for 10 iterations
    for (i = 0; i < 10; ++i) {
        // Generate random number
        randomNumber = rand() % 256;
        digits = numDigits(randomNumber);
        // use randRange and numDigits to figure out random addend
        randomAddend = randRange(digits);
        
        printf("What number does this 9's complement addition/subtraction equal? \n");
        printf("%d + %d\n", randomNumber, randomAddend);
        
        // Read user's answer
        scanf("%d", &userAnswer);
        
        // Get correct answer using 9's complement function
        correctAnswer = ninesComplementConvertSign(randomNumber) + ninesComplementConvertSign(randomAddend);
        
        // Check user's answer against correct answer
        if (correctAnswer == userAnswer) {
            printf("Smart!\n");
            ++num_correct;
        } else {
            printf("Sorry, the correct answer = %d\n", correctAnswer);
        }
    }
    printf("You got %d out of 10\n", num_correct);
}