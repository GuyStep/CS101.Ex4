/******************************************
*Student name: Guy Step
*Exercise name: ex4
******************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//First mission defines & functions declaration
#define MIN_PAIRS 1
#define MAX_PAIRS 10000
#define MIN_SMALL_NUM 1
#define MAX_BIG_NUM 10000000000
void mission1();
int contain(int, int);

//Second mission defines & functions declaration
#define MIN_NUM 0
#define MAX_NUM 101
void mission2();
int stepsToZero(int);
int printToZero(int);
int lowDivider(int, int);

//Third mission defines & functions declaration
#define MIN_XOR_NUM 1
#define MAX_XOR_NUM 100
int xorWizard(int, int, int);
void xorWizard();

//Fourth mission defines & functions declaration
#define ROCK_STR "Rock"
#define PAPER_STR "Paper"
#define SCISSORS_STR "Scissors"
#define LIZARD_STR "Lizard"
#define SPOCK_STR "Spock"
#define MIN_ROUNDS 1
#define MAX_ROUNDS 30
enum winnerName { ALICE = 1, BOB = 2, TIE = 3 };
enum shapeNumbers { Rock = 0, Paper = 1, Scissors = 2, Lizard = 3, Spock = 4 };
void mission4();
int whoWins(int, int);
int aliceNext(int, int, int);
int bobNext(int, int);

/************************************************************************
* function name: void main						*
* The Input: none							*
* The output: none (void)						*
* The Function operation: Main function that calls the independent	*
*			missions according to the user input.		*
*			Runs again as long as users input is valid	*
*			and represents a mission number:		*	
*			mission1: They live in us			*
*			mission2: Hero to zero				*
*			xorWizard: Wizard of XOR			*
*			Mission5: Rock, Paper, Scissors (Lizard, Spock)	*
*************************************************************************/
void main() {
	int mission;
	do {
		printf("Please enter the mission number: \n");
		scanf(" %d", &mission);
		switch (mission) {
		case 1:	{
			mission1();
			break;
		}
		case 2: {
			mission2();	
			break;
		}
		case 3: {
			xorWizard();
			break;
		}
		case 4: {
			mission4();
			break;
		}
		default:
			return;
		}
	} while (mission <= 4 && mission >= 1);
	return;
}

/************************************************************************
* function name: void mission1						*
* The Input: none							*
* The output: none (void), prints only					*
* The Function operation: Recieves pairs of numbers from user (through  *
*			 scanf) and counts in how many of the pairs	*
*                        the small num is contained in the bigger one.	*
*			Uses contain(int,int) function.			*
*************************************************************************/
void mission1() {
	//Variables declaration & initialization after previous mission run
	int pairsNum, i, bigNum, smallNum, counter=0;
	printf("Please enter the number of pairs:\n");
	scanf(" %d", &pairsNum);
	//Loop gets two number and checks and counts if the small one is contained in the bigger one 
	for (i = 1; i <= pairsNum; i++) {
		printf("Please enter the larger number of pair %d (a):\n", i);
		scanf(" %d", &bigNum);
		printf("Please enter the smaller number of pair %d (b):\n", i);
		scanf(" %d", &smallNum);
		counter += contain(bigNum, smallNum);
	}
	printf("The number of pairs satisfying the condition is: %d\n", counter);
	return;
}
/************************************************************************
* function name: contain						*
* The Input: int bigNum, int smallNum (the numbers were given by user)	*
* The output: 1/0 (1-contains, 2-Doesn't contain)			*
* The Function operation: checks if the smallNum contained in bigNum,   *
*			  returns 1 if contained, 0 if not.		*
*************************************************************************/
int contain(bigNum, smallNum) {
	int modulu = 1;
	int smallTemp = smallNum;
	//Checks how many digits in the small number, calculates a modulu number according to the digits number
	while ((smallTemp % 10) != 0) {
		smallTemp /= 10;
		modulu *= 10;
	}
	smallTemp = smallNum;
	//Loop runs untill we checked every big num's digit
	while (bigNum != 0) {
		//Loop runs untill found a match or finished checking the big number. 
		while (((bigNum % modulu) != smallTemp) && (bigNum != 0)) {
			bigNum /= 10;
		}
		//Example: bignum=1234, modulu=1000, smallnum=34: 1234%100=34
		if ((bigNum % modulu) == smallTemp)
			return 1;
		bigNum /= 10;
	}
	return 0;
}
/************************************************************************
* function name: void mission2						*
* The Input: none							*
* The output: none (void), prints only					*
* The Function operation: Recieves a number from user (through		*
*			  scanf), counts how many steps it takes to	*
*			  reach zero using:				*
*			(number-1) and (number/lowest divider).		*
*			Uses printToZero(int) function.			*
*************************************************************************/
void mission2() {
	//Second mission variables
	int number;
	printf("Please enter the number:\n");
	scanf(" %d", &number);
	printf("The sequence of numbers produced by the actions is:\n");
	printf("The minimum number of moves is %d\n", printToZero(number));
}
/************************************************************************
* function name: stepsToZero						*
* The Input: int number (the number from which we find the way to zero )*
* The output: int Shortest number of steps to reach 0			*
* The Function operation: Recursive, counts and returns the minimal	*
*			 number of steps to reach zero.			*
*			 Calls to "stepsToZero" to find how many steps.	*
*		  	 Uses lowDivider(int,int) function		*
*************************************************************************/
int stepsToZero(number) {
	int divider, steps1 = 0, steps2 = 0;
	divider = lowDivider(number, 2);
	if (number < 3)
		return number;
	//If the number isn't prime, try: 1. divide by the lowest divider, 2. reduce by 1
	if (divider != number) {
		steps1 = 1 + stepsToZero(number / divider);
		steps2 = 1 + stepsToZero(number - 1);
		//Check which one of the ways is shorter
		if (steps1 <= steps2)
			return steps1;
		else
			return steps2;
	}
	//If the number is prime, there's only the option to reduce by 1
	return 1 + stepsToZero(number - 1);
}
/************************************************************************
* function name: printToZero						*
* The Input: int number	(the number from which we print the way to zero)*
* The output: int Shortest number of steps to reach 0			*
* The Function operation: Recursive, checks and prints all steps to zero*
*			that takes to reach 0 using two operatrions:	*
*			decrease by 1, divide by lowest divider.	*
*			counts how  many steps and returns it.		*
*			Uses stepsToZero(int), lowDivider(int,int) funcs*
*************************************************************************/
int printToZero(number) {
	int divider, steps1 = 0, steps2 = 0;
	divider = lowDivider(number, 2);
	if (number == 0) 
		return 0;
	
	if (divider != number) {
		steps1 = 1 + stepsToZero(number / divider);
		steps2 = 1 + stepsToZero(number - 1);
		if (steps1 <= steps2) {
			printf("%d\n", (number / divider));
			return 1 + printToZero(number / divider);
		}

		else {
			printf("%d\n", (number - 1));
			return 1 + printToZero(number - 1);
		}
	}
	printf("%d\n", (number - 1));
	return 1 + printToZero(number - 1);
}
/************************************************************************
* function name: lowDivider						*
* The Input: int number (from which we find the way to zero),		*
*		int divider (number we check as the lowest divider)	*
* The output: int lowest divider of "number"				*
* The Function operation: Recursive, finds the lowest divider of the	* 
*		 inputed number and returns it				*
*************************************************************************/
int lowDivider(number, divider) {
	if (number < 2)
		return number;
	if (divider == number)
		return divider;
	if ((number % divider) == 0)
		return divider;
	else
		return lowDivider(number, divider + 1);
}
/************************************************************************
* function name: void xorWizard						*
* The Input: none							*
* The output: none (void), prints only					*
* The Function operation: Recieves a number from user (through		*
*			  scanf), checks how many smaller		*
*			  numbers in xor with the number will produce	*
*			  a larger number than the original one.	*
*			  Uses xorWizard(int,int,int) function.		*
*************************************************************************/
void xorWizard() {
	int numberXor;
	printf("Please enter the number:\n");
	scanf(" %d", &numberXor);
	printf("The numbers are:\n");
	printf("A total of %d numbers \n", xorWizard(numberXor, 1, 0));
}
/************************************************************************
* function name: int xorWizard						*
* The Input: int nummber, int checkNumber, int amountOfNumbers		*
* The output: int amount of numbers that satisfy the condition		*
* The Function operation: Recursive, inputs number, checks how many 	*
*			smaller numbers xored with the number will 	*
*			produce a larger number than the original one.	*
*************************************************************************/
int xorWizard(number, checkNumber, amountOfNumbers) {
	//checks if we finished checking all possible numbers smaller than the original one
	if (checkNumber == number)
		return(amountOfNumbers);
	//checkNumber is in the range: 0<checkNumber<number 
	if (checkNumber < number && checkNumber>0) { 
		//checkNumber XOR number > number
		if ((checkNumber^number) > number) { 
			printf("%d\n", checkNumber);
			return xorWizard(number, checkNumber + 1, amountOfNumbers + 1);
		}
		else
			return xorWizard(number, checkNumber + 1, amountOfNumbers);
	}
	else
		return 0;
}
/************************************************************************************************
* function name: void mission4									*
* The Input: none										*
* The output: none (void), prints only								*
* The Function operation: Rock-Paper-Scissors-Lizard-Spock game.				*
*			Recieves a number of rounds, initial shapes forAlice and Bob from user	* 
*			(through scanf), checks	who wins in the game, prints all the rounds,	*
*			the score and winner's name.						*
*			Uses whoWins(int,int), aliceNext(int,int,int), bobNext(int,int) funcs.	*
************************************************************************************************/
void mission4() {
	//Variables declaration & initialization after previous mission run
	int i, alicesWins = 0, bobsWins=0, ties = 0, roundWinner = 0;
	int rounds, aliceShape, bobShape;

	printf("Please enter the shape Alice chose:\n");
	scanf(" %d", &aliceShape);
	printf("Please enter the shape Bob chose:\n");
	scanf(" %d", &bobShape);
	printf("Please enter the number of rounds:\n");
	scanf(" %d", &rounds);
	//Loop runns "rounds" times, each itaration repressents a game round.
	for (i = 0; i < rounds; i++) {
		roundWinner = whoWins(bobShape, aliceShape);
		//Switch counts every player's wins
		switch (roundWinner) {
		case (ALICE):
			alicesWins++;
			break;
		case (BOB):
			bobsWins++;
			break;
		case (TIE):
			ties++;
			break;
		default:
			break;
		}
		//Call for the players next round shapes functions
		aliceShape = aliceNext(aliceShape, roundWinner, bobShape);
		bobShape = bobNext(bobShape, roundWinner);
	}
	if (bobsWins > alicesWins) {
		printf("Bob wins, by winning %d game(s) and tying %d game(s)\n", bobsWins, ties);
		return;
	}
	else if (bobsWins < alicesWins) {
		printf("Alice wins, by winning %d game(s) and tying %d game(s)\n", alicesWins, ties);
		return;
	}
	else {
		printf("Alice and Bob tie, each winning %d game(s) and tying %d game(s)\n", alicesWins, ties);
		return;
	}
}
/************************************************************************
* function name: int whoWins						*
* The Input: int bobShape, int aliceShape				*
* The output: int number of the winner (1-ALICE, 2-BOB, 3-TIE)		*
* The Function operation: Prints every round's shapes,			*
*			  returns the winners serial number.		*
*************************************************************************/
int whoWins(bobShape, aliceShape) {
	switch (aliceShape) {

	case (Rock):
		switch (bobShape) {
		case Rock:
			printf("%s = %s\n", ROCK_STR, ROCK_STR);
			return TIE;
		case Paper:
			printf("%s < %s\n", ROCK_STR, PAPER_STR);
			return BOB;
		case Scissors:
			printf("%s > %s\n", ROCK_STR, SCISSORS_STR);
			return ALICE;
		case Lizard:
			printf("%s > %s\n", ROCK_STR, LIZARD_STR);
			return ALICE;
		case Spock:
			printf("%s < %s\n", ROCK_STR, SPOCK_STR);
			return BOB;
		default:
			break;
		}
	case (Paper):
		switch (bobShape) {
		case Rock:
			printf("%s > %s\n", PAPER_STR, ROCK_STR);
			return ALICE;
		case Paper:
			printf("%s = %s\n", PAPER_STR, PAPER_STR);
			return TIE;
		case Scissors:
			printf("%s < %s\n", PAPER_STR, SCISSORS_STR);
			return BOB;
		case Lizard:
			printf("%s < %s\n", PAPER_STR, LIZARD_STR);
			return BOB;
		case Spock:
			printf("%s > %s\n", PAPER_STR, SPOCK_STR);
			return ALICE;
		default:
			break;
		}
	case (Scissors):
		switch (bobShape) {
		case Rock:
			printf("%s < %s\n", SCISSORS_STR, ROCK_STR);
			return BOB;
		case Paper:
			printf("%s > %s\n", SCISSORS_STR, PAPER_STR);
			return ALICE;
		case Scissors:
			printf("%s = %s\n", SCISSORS_STR, SCISSORS_STR);
			return TIE;
		case Lizard:
			printf("%s > %s\n", SCISSORS_STR, LIZARD_STR);
			return ALICE;
		case Spock:
			printf("%s < %s\n", SCISSORS_STR, SPOCK_STR);
			return BOB;
		default:
			break;
		}
	case (Lizard):
		switch (bobShape) {
		case Rock:
			printf("%s < %s\n", LIZARD_STR, ROCK_STR);
			return BOB;
		case Paper:
			printf("%s > %s\n", LIZARD_STR, PAPER_STR);
			return ALICE;
		case Scissors:
			printf("%s < %s\n", LIZARD_STR, SCISSORS_STR);
			return BOB;
		case Lizard:
			printf("%s = %s\n", LIZARD_STR, LIZARD_STR);
			return TIE;
		case Spock:
			printf("%s > %s\n", LIZARD_STR, SPOCK_STR);
			return ALICE;
		default:
			break;
		}		
	case (Spock):
		switch (bobShape) {
		case Rock:
			printf("%s > %s\n", SPOCK_STR, ROCK_STR);
			return ALICE;
		case Paper:
			printf("%s < %s\n", SPOCK_STR, PAPER_STR);
			return BOB;
		case Scissors:
			printf("%s > %s\n", SPOCK_STR, SCISSORS_STR);
			return ALICE;
		case Lizard:
			printf("%s < %s\n", SPOCK_STR, LIZARD_STR);
			return BOB;
		case Spock:
			printf("%s = %s\n", SPOCK_STR, SPOCK_STR);
			return TIE;
		default:
			break;
		}
	default:
		break;
	}
}
/************************************************************************
* function name: int aliceNext						*
* The Input: int currentMove, int winnerName, int bobShape		*
* The output: int next Alice's shape for the next round  		*
* The Function operation: Returns Alice's shape for the next round	*
*			according to who won the current round,		*
*			what shape she used, and what shape Bob used.	*
*************************************************************************/
int aliceNext(currentMove, winnerName, bobShape) {
	switch (winnerName) {
	//Alice won the previous round
	case(1): 
		return currentMove;
	//Alice lost the previous round
	case(2): 
		switch (bobShape) {
		case (Rock):
			//Paper & Spock beat Paper, Paper covers Spock
			return Paper; 
		case (Paper):
			return Scissors;  
			//Scissors&Lizard beat Paper, Scissors beat Lizard
		case (Scissors):
			//Spock & Rock beat Scissors, Spock vaporizes Rock
			return Spock; 
		case (Lizard):
			//Scissors & Rock beat Lizard, Rock crushes scissors 
			return Rock;
		case (Spock):
			//Paper & Lizard beat Spock, Lizard eats Paper 
			return Lizard;
		default:
			break;
		}
	//Alice tied the previous round
	case(3): 
		switch (currentMove) {
		case (Rock):
			//Paper & Spock beat Paper, Paper covers Spock
			return Paper; 
		case (Paper):
			//Scissors&Lizard beat Paper, Scissors beat Lizard 
			return Scissors; 
		case (Scissors):
			//Spock & Rock beat Scissors, Spock vaporizes Rock 
			return Spock; 
		case (Lizard):
			//Scissors & Rock beat Lizard, Rock crushes scissors 
			return Rock; 
		case (Spock):
			//Paper & Lizard beat Spock, Lizard eats Paper
			return Lizard;  
		default:
			break;
		}
	default:
		return 0;
	}
}
/************************************************************************
* function name: int bobNext						*
* The Input: int currentMove, int winnerName				*
* The output: int next Bobs's shape for the next round  		*
* The Function operation: Returns Bob's shape for the next round	*
*			according to who won the current round,		*
*			what shape he used.				*
*************************************************************************/
int bobNext(currentMove, winnerName) {
	switch (currentMove) {
	case(Spock):
		switch (winnerName) {
		//Bob lost the previous game, chooses Paper
		case (ALICE):
			return Paper;
		//Bob won the previous game, chooses Rock
		case (BOB):
			return Rock;
		//Bob tied the previous game, chooses Lizard
		case (TIE):
			return Lizard;
		}
	default:
		return Spock;
	}
}
