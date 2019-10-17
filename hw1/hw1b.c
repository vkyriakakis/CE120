/* Programmer: Kyriakakis Vasileios

   Date: 3/11/2017

   Purpose: O skopos tou programmatos einai h sxediash kai ekypwsh enos arxaiou naou ths exhs morfhs:
		
	     		      ''''
          		    --    --
          		  ..        ..
     		        __            __
     		      ''                ''
    		    --                    --
  		  ..                        ..
		__                            __
		[][][][][][][][][][][][][][][][]
 		 @.==.@  @.==.@  @.==.@  @.==.@ 
  		  |''|    |''|    |''|    |''|  
  		  |''|    |''|    |''|    |''|  
 		  |''|    |''|    |''|    |''|  
 		  |''|    |''|    |''|    |''|  
 		  |''|    |''|    |''|    |''|  
  	  	  |''|    |''|    |''|    |''|  
  		  |''|    |''|    |''|    |''|  
  		  |''|____|''|____|''|____|''|
 		  ============================
 		 ==============================
		================================

	To megethos tou naou exartatai apo ton arithmo twn kionwn, ton opoio eisagei o xrhsths.

  Input: O arithmos twn kionwn column_number

  Output: O naos pou emfanizetai sthn othnonh

  Conditions: O arithmos twn kionwn einai akeraios metaxy tou 1 kai tou 16 (symperilamvanomenwn), o opoios den diaireitai 		me ton arithmo 5.

*/		    






#include <stdio.h>


int main(int argc, char *argv[]) {

	//Dhlwsh twn statherwn lower_limit kai upper_limit pou kathorizoun to euros timwn toy arithmou kionwn
		
	const int lowerlimit = 1, upperlimit = 16;

	/*Dhlwsh twn metavlhtwn
	
	*H column_number apothikeuei ton arithmo twn kionwn
	
	*H base_size ekfrazei to platos tou katwterou skaliou
	
	*H space_number xhsimopoieitai ston sxediasmo tou aetwmatos gia na ginei pio anagnwsimos o kwdikas

	*Oi c1, c2, c3 apoteloun metrhtes

	*/
	
	int column_number, base_size, space_number, c1, c2, c3;

	//Xrhsimopoiw do-while gia na periorisw tis pithanes times ths column_number
	
	do {
	
		printf("Please input the number of columns (number is an integer not divisible by 5, >= 1, <= 16) : ");
		scanf("%d", &column_number);
		
	} while ( (column_number < lowerlimit) || (column_number > upperlimit) || (column_number % 5 == 0) );


	/* Oi synarthseis ths column_number kai ths c1 pou xrhsimopoiw stis logikes synthikes twn domwn for tou programmatos   		prokyptoun apo thn parathrhsh tou zhtoumenou sxhmatos */



	//Edw vrisketai o kwdikas gia to sxediasmo tou aetwmatos tou naou


	for (c1 = 1 ; c1 <= 2*column_number ; c1++) {
	
		//Ypologismos ths space_number gia aplopoihsh tou typou pou xrhsimopoihsa sthn domh for


		space_number = (4*column_number - 2)/(1 - 2*column_number);

		for (c2 = 1 ; c2 <= space_number * (c1 - 2*column_number) ; c2++) {
			
			putchar(' ');

		}
		
		/* Parathrhsa oti to motibo tou aetwmatos parousiazei periodikothta, prwta emfanizetai o xarakthras ' ' ' ,
		  epeita o '-', meta o '.' kai telos o '_'. Xrhsimopoihsa ton telesth % kai mia domh switch_case gia na ekfrasw
		  auth thn periodikothta, afou 1 % 4 = 1, 2 % 4 = 2, 3 % 4 = 3, 4 % 4 = 0, 5 & 4 = 1 kai proxwraei me auto ton 
		  tropo */


		for (c2 = 1 ; c2 <= 2 ; c2++) {
			
			switch(c1 % 4) {
				
				case 1:
					putchar('\'');
					break;

				case 2:
					putchar('-');
					break;

				case 3:
					putchar('.');
					break;

				default:
					putchar('_');
			
			}
			
		}

		//Xrhsimopoiw kai pali thn space_number gia na apodwsw pio apla ton typo pou xrhsimopoihsa sth domh for


		space_number = (8*column_number - 4)/(2*column_number - 1);
		
		for (c2 = 1 ; c2 <= space_number*(c1 - 1) ; c2++) {
			
			putchar(' ');
		
		}

		
		for (c2 = 1 ; c2 <= 2 ; c2++) {
			
			switch(c1 % 4) {
				
				case 1:
					printf("'");
					break;

				case 2:
					putchar('-');
					break;

				case 3:
					putchar('.');
					break;

				default:
					putchar('_');
			
			}
			
		}
		
		putchar('\n');

	}

	//Xrhsimopoiw domh for gia thn emfanish tou motibou [][][]...[]

	for (c1 = 1 ; c1 <= 4*column_number ; c1++) {
		
		printf("[]");
	
	}
	
	putchar('\n');



	//Edw vrisketai o kwdikas gia to sxediasmo twn kionwn tou naou


	//Xrhshmopoiw domh for gia thn emfanish twn kionokranwn

	for (c1 = 1 ; c1 <= column_number ; c1++) {
		
		printf(" @.==.@ ");
		
	}
	
	putchar('\n');

	//Xrhsh domhs for gia thn ektypwsh twn kyriws merwn twn kionwn

	for (c1 = 1 ; c1 <= 8 ; c1++) {

		if (c1 == 8) {

			printf("  |''|");
	
				for (c2 = 1 ; c2 <= column_number-1 ; c2++) {

					for (c3 = 1 ; c3 <= 4 ; c3++) {
					
						putchar('_');
			
					}
					
					printf("|''|");
				

				}

	
		}
		
		
		else {
				
			for (c2 = 1 ; c2 <= column_number ; c2++) {
		
				printf("  |''|  ");
		
			}
		
		}
		
		putchar('\n');
	
	}



	//Edw vrisketai o kwdikas gia to sxediasmo twn skaliwn tou naou

	
	//Ypologismos ths base_size symfwna me tis zhtoumenes analogies, wste na dwsw pio aples logikes synthikes stis domes for 

	base_size = 8*column_number;


	for (c1 = 1 ; c1 <= 5 ; c1++) {

		//Xrhsimopoiw domh if, wste na typwnei grammh apo '=' otan c1 = 1, 3, 5 kai keno tis ypoloipes epanalhpseis 
		
		if (c1 % 2 == 0) {
			
			putchar('\n');
		
		}
		

		else {
		
			for (c2 = 1 ; c2 <= (5 - c1)/2 ; c2++) {
			
				putchar(' ');
				
			}
			
			for (c2 = (5 - c1)/2 + 1 ; c2 <= base_size - 2  ; c2++) {
				
				putchar('=');
			
			}
			
			for (c2 = 1 ; c2 <= (c1 - 1)/2 ; c2++) {
			
				putchar('=');
				
			}
			
		
		}

	
	}
	
	return (0);

}
