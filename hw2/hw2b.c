/* 

   *Programmer: Kyriakakis Vasileios

   *Date: 17/11/2017

   *Purpose: O orthografikos elegxos mia lexhs pou eisagei o xrhsths,	
	mesw lexikou to opoio diabazetai apo arxeio, kai sthn periptwsh
	pou h lexh den periexetai sto lexiko, na dinontai sto xrhsth
	ws protaseis oi kontinoteres lexeis pou periexei to lexiko.
	
   *Input: H lexh thn opoia tha anazhthsei sto lexiko, kai oi lexeis pou
	periexontai sto lexiko
	
   *Output: Ean h lexh periexetai sto lexiko, enhmerwnetai gia auto o xrhsths,
	enw ean oxi, to programma ektypwnei sthn othonh tis dyo kontinoteres
	lexeis tou lexikou ws protaseis.

   *Conditions: To programma leitourgei theorwntas pws oi lexh pou tha eisagei o 
	xrhsths kai oi lexeis tou lexikou exoun to poly 29 grammata (an kai
	auto mporei na allaxei eukola mesw to #define SIZE), kai pws to
	lexiko pou diabazetai periexei toulaxiston mia fora th lexh EndofDictionary.

*/		


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 30

//Dhlwsh synarthsewn:

//Synarthsh gia thn euresh tou megistou 2 akeraiwn

int maximum(int number1, int number2); 

//Synarthsh gia thn euresh tou elaxistou 2 akeraiwn

int minimum(int number1, int number2);

int main(int argc, char *argv[]) {
	
	char input_word[SIZE], dictionary_word[SIZE], format[SIZE/4],
	/* Oi closer_word arxikopoiountai se '\0' gia ton elegxo tou arithmou twn
	protwinomenwn lexewn sto telos */
	closer_word1[SIZE] = {'\0'}, closer_word2[SIZE] = {'\0'}; 
	//Oi min_distance arxikopoiountai se SIZE gia tis anagkes ths sygrishs
	int k, distance = 0, min_distance1 = SIZE, min_distance2 = SIZE; 
	int input_length, dict_length;

	//Eisodos ths lexhs tou xrhsth, kai elegxos mesw format string

	printf("Word to check: ");
	sprintf(format, "%%%ds", SIZE - 1);
	scanf(format, input_word);
	putchar('\n');
	input_length = strlen(input_word); 

	//Anagnwsh lexewn apo to arxeio mexri na diavastei h "EndOfDictionary"

	while (1) {

		distance = 0; 
		scanf(format, dictionary_word);

		//Me to pou diavastei h EndOfDictionary stamataei h anagnwsh
		if (strcmp(dictionary_word, "EndOfDictionary") == 0) {
			break;
		}

		dict_length = strlen(dictionary_word);

		/* Ypologismos ths apostashs ths lexhs pou diavazetai apo to lexiko,
		apo thn lexh pou eishgage o xrhsths, mesw ths sygrishs twn 
		antistoixwn xarakthrwn mexri to telos ths lexhs me to mikrotero
		mhkos, kai epeita auxhsh ths kata ena gia kathe xarakthra mexri
		to telos ths lexhs me to megalytero mhkos. Na shmeiwthei oti
		xrhsimopoihtai h synarthsh tolower gia na mporw na sygrinw kai
		lexeis pou periexoun kefalaia grammata */

		for (k = 0 ; k < maximum(input_length, dict_length) ; k++) {
			if (k < minimum(input_length, dict_length) ) {
				if (tolower(input_word[k]) != tolower(dictionary_word[k]) ) {
					distance++;
				}
			}	
			else {
				distance++;
			}
		}

		/* Ean h lexh tou xrhsth vrisketai sto lexiko (apostash 0), tote 
		to programma termatizei */

		if (distance == 0) {
			printf("\"%s\" is in the dictionary.\n", input_word);
			return (0);
		}

		printf("Distance: %2d, Word: %s\n", distance, dictionary_word);
		
		/* Sygrish twn apostasewn twn pio kontinwn lexewn, kai antikatastash
		auths pou apexei perissotero me thn lexh tou lexikou, efoson auth 
		apexei ligotero. Na shmeiwthei pws h prwth lexh pou diavazetai,
		eisagetai sthn closer_word1,kai pws sthn periptwsh pou oi 2 lexeis 
		kai h lexh pou diabazetai isapexoun, den apothikeuetai h kainourgia lexh */
	
		if (min_distance2 > min_distance1) {
			if (min_distance2 > distance) {
				min_distance2 = distance;
				strcpy(closer_word2, dictionary_word);
			}
		}
		else if (min_distance1 > min_distance2) {
			if (min_distance1 > distance) {
				min_distance1 = distance;
				strcpy(closer_word1, dictionary_word);
			}
		}
		else {
			if (min_distance1 > distance) {
				min_distance1 = distance;
				strcpy(closer_word1, dictionary_word);
			}
		}
	}

	printf("\"%s\" is not in the dictionary!\n", input_word);
	printf("Suggestions:\n");
	
	/* Efoson arxikopoihsa parapanw tis closer_word1, closer_word2 sto '\0',
	gia na elegxw an exoun eisagthei toulaxistwn dyo lexeis, tha elegxw an to
	mhkos ths kathe mias einai 0, wste na ektypwsw ton katallhlo arithmo protasewn. 
	Ean exw dyo kontinoteres lexeis, tis ektypwnw kata auxousa lexikografikh seira */
	
	if (strlen(closer_word1) != 0) {
		if (strlen(closer_word2) != 0) {
			if (strcmp(closer_word1, closer_word2) > 0) {
				printf("\"%s\", %d\n", closer_word2, min_distance2);
				printf("\"%s\", %d\n", closer_word1, min_distance1);
			}

			else if (strcmp(closer_word1, closer_word2) <= 0) {
				printf("\"%s\", %d\n", closer_word1, min_distance1);
				printf("\"%s\", %d\n", closer_word2, min_distance2);
			}
		}
		else {	
			printf("\"%s\", %d\n", closer_word1, min_distance1);
		}
	}

	return (0);	
}

//Synarthseis pou xrhsimopoiw kata ton ypologismo ths apostashs distance

int maximum(int number1, int number2) {
	int max = number2;
	if (number1 > number2) {
		max = number1;
	}

	return (max);
}

int minimum(int number1, int number2) {
	int min = number2;
	if (number1 < number2) {	
		min = number1;
	}

	return (min);
}
