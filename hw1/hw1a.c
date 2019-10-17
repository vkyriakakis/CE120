/* 

*Programmer: Kyriakakis Vasileios

   *Date: 1/11/2017

   *Purpose: Ekypwnei to hmerologio gia to mhna kai to etos gennhshs tou xrhsth.

   *Input: O mhnas kai to etos gennhshs tou xrhsth.

   *Output: To hmerologio gia to mhna kai to etos gennhshs.

   *Conditions: To programma leitourgei theorwntas pws stis 1/1/2017 h mera einai Kyriakh,  gia eth metaxy tou 1582 kai tou 2016 (symperilamvanomenwn), kai mhnes metaxy tou 1 (Ianouarios) kai tou 12 (Dekembrios) perilamvanontas ta 1 kai 12.

*/		   



#include <stdio.h>


int main(int argc, char *argv[]) {
	

	/* Dhlwsh twn metavlhtwn
	
	*H month apothikeuei ton mhna gennhshs tou xrhsth
	
	*H year apothikeuei to etos gennhshs tou xrhsth
	
	*H daymax apothikeuei ton arithmo ths teleutaias meras enos mhna

	*H startday antiprosopeuei th mera me thn opoia xekina o mhnas gennshs tou xrhsth

	*H element apothikeuei to stoixeio tou hmerologiou pros ektypwsh

	*H daytotal_january apothikeuei to plhthos twn hmerwn apo 1/1/year ews 1/1/2017
	
	*H daytotal_month apothikeuei to plhthos twn hmerwn apo 1/month/year ews 1/1/2017
	
	*Oi counter1, counter2, counter3 einai metrhtes

	*/


	int month, year, daymax, startday, element, daytotal_january = 0, daytotal_month = 0; 
	int counter1, counter2, counter3;
	
	//Xrhshmopoiw domh do-while gia ton periorismo twn pithanwn timwn twn year kai month

	do {
	
		printf("Enter birthdate (M/Y): ");
		scanf("%d/%d", &month, &year);
		
		if ( (month < 1) || (month > 12) || (year < 1582) || (year > 2016) ) {
			
			putchar('\n');
			printf("ERROR: Month must be between 1 and 12 and year between 1582 and 2016.\n");
			
		}
		
	} while ( (month < 1) || (month > 12) || (year < 1582) || (year > 2016) );


	//Xrhsh emfoleumenhs domhs for gia ton ypologismo ths daytotal_january
	

	for (counter1 = year ; counter1 <= 2016 ; counter1++) {
		
		for (counter2 = 1 ; counter2 <= 12 ; counter2++) {
			

		/* Xrhsh domhs switch-case gia thn epilogh tou katallhlou plithous hmerwn gia kathe mhna, lambanontas ypopsh thn
		periptwsh tou disektou etous */


			switch(counter2) {
				
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					daymax = 31;
					break;
				
				case 4:
				case 6:
				case 9:
				case 11:	
					daymax = 30;
					break;
				
				case 2:
					if ( ( (counter1 % 4 == 0 ) && (counter1 % 100 != 0) ) || (counter1 % 400 == 0) ) {
						
						daymax = 29;
					
					}
						
					else {
						
						daymax = 28;
				
					}
			
			}
				

			//Xrhsh domhs for gia ton ypologismo ths daytotal_january
		

			for (counter3 = 1 ; counter3 <= daymax ; counter3++) {
				
				daytotal_january++;

			}
	
		}
		
	}

	//Ektypwsh ths daytotal_january


	putchar('\n');
	printf("1/1/%d to 1/1/2017: %u days", year, daytotal_january);


	//Xrhsh domhs for gia thn pragmatopoihsh epanalipsewn oses kai oi mhnes apo 1/year ews month/year


	for (counter2 = 1 ; counter2 < month ; counter2++) {
			

		//Xrhsh switch-case xana gia thn euresh tou katallhlou plhthous hmerwn ana mhna


		switch(counter2) {
				
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				daymax = 31;
				break;
				
			case 4:
			case 6:
			case 9:
			case 11:	
				daymax = 30;
				break;
				
			default:
				if ( ( (year % 4 == 0 ) && (year % 100 != 0) ) || (year % 400 == 0) ) {
						
					daymax = 29;
				
				}
					
				else {
						
					daymax = 28;
				
				}
			
		}
			
	
		//Xrhsh domhs for gia ton ypologismo ths daytotal_month


		for (counter3 = 1 ; counter3 <= daymax ; counter3++) {
				
			daytotal_month = --daytotal_january;

		}
	
	}


	//Ektypwsh ths daytotal_month


	putchar('\n');
	printf("Birthday to 1/1/2017: %u days\n", daytotal_month);


	/* Ypologismos tou plhthous twn hmerwn tou mhna pou eishgage o xrhsths, 
	gia xrhsh sthn ektypwsh tou hmerologiou */


	switch(month) {
				
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			daymax = 31;
			break;
				
		case 4:
		case 6:
		case 9:
		case 11:	
			daymax = 30;
			break;
				
		default:
			if ( ( (year % 4 == 0 ) && (year % 100 != 0) ) || (year % 400 == 0) ) {
						
				daymax = 29;
				
			}
					
			else {
					
				daymax = 28;
			
			}
			
	}
	

	/* Antistoixhsa tis meres ths ebdomadas me arithmous (1 - Deutera, 2- Trith, ..., 7 - Kyriakh), 
	kai parathrhsa oti mporw na apodwsw thn periodikothta pou parousiazoun xrhsimopoiwntas ton telesth %, 
	etsi efoson stis 1/1/2017 exoume Kyriakh (7), k tote afairwntas to ypoloipo ths diaireshs 
	ths daytotal_month kai tou 7 apo to 7, mou bgazei ton arithmo pou antistoixei sthn mera 1/month/year. */
	

	startday = 7 - (daytotal_month % 7);


	//Ektypwsh kefalidwn tou hmerologiou


	putchar('\n');
	printf(" Mon Tue Wed Thu Fri Sat Sun\n");

	
	/* Sthn parakatw domh for, ekypwnw thn prwth seira tou hmerologiou. 
	Oso o metrhths einai mikroteros apo ton arithmo pou antistoixei sthn prwth mera tou mhna, 
	typwnontai kena, enw meto pou exisothoun, typwnontai osa stoixeia apo to 1 kai meta xwrane 
	sthn prwth grammh, enw apothikeuw kathe stoixeio pou ektypwnetai sthn metavlhth element gia
	xrhsh sthn ektypwsh twn ypoloipwn stoixeiwn */
	

	for (counter1 = 1 ; counter1 < 8 ; counter1++) {
			
		if (counter1 < startday) {
			
			printf("    ");
		
		}
		
		else {
			
			element = 1 + counter1 - startday;
			printf("%4d", element);

		}

	}

	putchar('\n');


	/* Parakatw typwnw ta stoixeia twn ypoloipwn grammwn tou hmerologiou, 
	h exwterikh for allazei th grammh, enw h emfwleumenh for typwnei kathe stoixeio element
	mexris otou na typwthei kai to stoixeio pou antistoixei sthn teleutaia mera tou mhna */

	for (counter2 = 2 ; counter2 < 7 ; counter2++) {
		
		for (counter3 = 1 ; counter3 < 8 ; counter3++) {
		
			element++;
			
			if ( element > daymax ) {
			
				break;

			}
		
			printf("%4d", element);
		
		}
			
		printf("\n");
				
	}
		
	return (0);

}


