#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 24


/* Dhlwsh twn global pinakwn game kai displayed, me ton game
na periexei se kathe thesh tou narkh, h ton arithmo ton narkwn gyrw apo authn
(xarakthres * kai dekadika pshfia), kai ton displayed na periexei tis times
0 (ean h thesh auth tou kamba den exei apokalyfthei) kai 1 (ean exei apokalyphthei) */

char game[MAX_SIZE][MAX_SIZE], displayed[MAX_SIZE][MAX_SIZE];


//Synarthsh epiloghs ths dyskolias tou paixnidiou, kai tou katallhlou megethous kamba
int difficulty_option(void);

//Synarthsh arxikopoihshs twn arrays game kai displayed
void array_init(int board_size); 

/* Synarthsh ypologismou tou arithmou twn narkwn gyrw apo mia thesh tou game
pou den periexei narkh */
int surrounding_number(int game_row, int game_column, int board_size); 

//Synarthsh ekypwshs twn stoixeiwn tou game pou exoun apokalyfthei ston paikth
void print_board(int board_size);

//Synarthsh pou elegxei an exoun apokalyfthei oles oi theseis pou den periexoun narkes
int revealed_check(int board_size);

//Synarthsh pou ektypwnei thn lysh meta to telos tou paixnidiou
void print_solution(int board_size);
	

int main(int argc, char *argv[]) {

	char  retry_option;
	const char MINE = '*', REVEALED = '1';
	int board_size, row, column;

	/* To loop tou paixnidiou, to opoio epanalambanetai oso o xrhsths 
	epilegei na xanapaixei */

	do {

		/*Klhsh ths difficulty_option gia ton kathorismo ths dyskolias
		tou paixnidiou ara kai tou megethous tou kamba*/
		
		board_size = difficulty_option();

		/* Klhsh ths synarthshs array_init gia thn arxikopoihsh tou paixnidiou,
		kai ths print_board gia thn prwth ektypwsh tou kamba */
	
		array_init(board_size);
		print_board(board_size);
		
		/* Domh epanalhpshs pou trexei mexri o xrhsths na kerdisei apokalyptwntas
		oles tis theseis xwris narkes, h na xasei apokalyptwntas narkh */

		while(1) {
		
			/* Elegxos twn syntetagmenwn pou eisagei o xrhsths, 
			epanalambanontas thn eisodo mexri na vriskontai sta
			oria tou kamba. An o xrhsths eisagei to 0 ws arithmo grammhs,
			diakoptetai h sygekrimenh partida tou paixnidiou */

			do {
				printf("Row> ");
				scanf("%d", &row);
				printf("Col> ");
				scanf("%d", &column);

				if ( (row < 0) || (row > board_size) ) {
					printf("Invalid Row. Try again!\n");
				}

				if ( (column <= 0) || (column > board_size) ) {
					printf("Invalid Column. Try again!\n");
				}

				if (row == 0) {
					break;
				}	

				} while ( (row < 0) || (row > board_size) || (column < 0) || (column > board_size) );
	
			if (row == 0) {
				printf("\nPuzzle interrupted!\n");
				break;
			}
			
			/* Se periptwsh pou o xrhsths apokalypsei thesh pou den periexei
			narkh, h thesh auth shmeiwnetai ws 'revealed' ston displayed,
			enw an periexei narkh teleiwnei h partida kai ektyopwnetai h lysh
			kalwntas thn print_solution */

			if (game[row-1][column-1] != MINE) {
				displayed[row-1][column-1] = REVEALED; 
			}
			else {
				printf("KABOOM!\n");
				print_solution(board_size);
				break;
			}

			/* Klhsh ths revealed_check gia na teleiwsei h partida, ean o xrhsths apokalyspei
			oles tis theseis xwris narkes tou kamba, kai ektypwsh ths lyshs mesw 
			ths print_solution */

			if (revealed_check(board_size)) {
				printf("Congratulations!\n");
				print_solution(board_size);
				break;
			}

			/* Efoson den syntrexoun logoi termatismou tou paixnidiou, ektypwnetai
			o ananewmenos kambas meta thn apokalypsh tou stoixeiou apo ton xrhsth */

			print_board(board_size);

		} 

		/* Elegxos ths eisodou tou xrhsth, an 'y' h 'Y' xekinaei nea partida, 
		an 'n' h 'N' to programma termatizei */
		
		do {
			printf("Play again? (y/n) ");
			scanf(" %c", &retry_option);
		} while ( (retry_option != 'y') && (retry_option != 'Y') && (retry_option != 'n') && (retry_option != 'N') );

	} while ( (retry_option == 'y') || (retry_option == 'Y') );
			
	return (0);
}

int difficulty_option(void) {
	
	char difficulty_option;
	int board_size;
	
	//Epilogh tou epipedou dyskolias apo ton xrhsth kai katallhlh epilogh megethous kamva

		printf("Choose difficulty level:\n");
		printf("EASY (E/e)\n");
		printf("MEDIUM (M/m) \n");
		printf("EXPERT (X/x) \n");
		printf("==> ");
		scanf(" %c", &difficulty_option);
		putchar('\n');

		switch(difficulty_option) {
			case 'E':
			case 'e':
				board_size = 6;
				break;
			case 'M':
			case 'm':
				board_size = 12;
				break;
			case 'X':
			case 'x':
				board_size = 24;	
		}

	return(board_size);
}

void array_init(int board_size) {

	int total_number, mine_row, mine_column, k, j;

	char const MINE = '*', HIDDEN = '0';

	//Arxikopoihsh tou displayed me 0 (HIDDEN)

	for (k = 0 ; k < board_size ; k++) {
		for (j = 0 ; j < board_size ; j++) {
			displayed[k][j] = HIDDEN;
		}
	}

	//Arxikopoihsh tou game me 0
	
	for (k = 0 ; k < board_size ; k++) {
		for (j = 0 ; j < board_size ; j++) {
			game[k][j] = '0';
		}
	}

	//Klhsh ths srand gia thn arxikopoihsh ths gennhtrias tyxaiwn arithmwn

	srand(time(NULL));

	//Ypologismos tou synolikou arithmou twn narkwn

	total_number = (2*board_size*board_size)/10; 

	/* Topothethsh twn narkwn se tyxaies theseis tou game,
	mesw ths rand() kai tou telesth % gia ton periorismo twn tyxaiwn timwn,
	me tetoio tropo wste na mhn topothetithei narkh panw apo mia fora se mia 
	thesh */

	for (k = 0 ; k < total_number ; k++) {
		do {
			mine_row = rand() % board_size;
			mine_column = rand() % board_size;
		} while (game[mine_row][mine_column] == MINE);
	
		game[mine_row][mine_column] = MINE;

	}
	
	/* Ypologismos twn arithmwn 0-8 se kathe thesh pou den periexei narkh
	me klhsh ths synarthshs surrounding_number */

	for (k = 0 ; k < board_size ; k++) {
		for(j = 0 ; j < board_size ; j++) {
			if ( (game[k][j] != MINE) ) {
				game[k][j] = '0' + surrounding_number(k, j, board_size);
			}
		}
	}
}

int surrounding_number(int game_row, int game_column, int board_size) {

	int i, j, start_row, start_column, end_row, end_column, mine_number = 0;
	char const MINE = '*';
	
	/* Elegxos olwn twn periptwsewn gia mia thesh tou kamba xwris narkh,
	dhladh an vrisketai sthn prwth h thn teleutai sthlh, antisoixa gia grammes,
	wste nam hn bgw apo ta oria tou pinaka */

	if (game_row == 0) {
		start_row = 0;
		end_row = 1;
	}
	else if (game_row == board_size - 1) {
		start_row = board_size - 2;
		end_row = board_size - 1;
	}
	else {
		start_row = game_row - 1;
		end_row = game_row + 1;
	}
	
	if (game_column == 0) {
		start_column = 0;
		end_column = 1;
	}
	else if (game_column == board_size - 1) {
		start_column = board_size - 2;
		end_column = board_size - 1;
	}
	else {
		start_column = game_column - 1;
		end_column = game_column + 1;
	}	
	
	/* Ypologismos tou arithmou 0-8 mesw ths metrhshs tou arithmou twn narkwn
	se ena tetragwno gyrw apo thn thesh ths opoias oi syntetagmenes 
	perasthkan sth synarthsh */
	
	for (i = start_row ; i <= end_row ; i++) {
		for (j = start_column ; j <= end_column ; j++) {
			if (game[i][j] == MINE) {
				mine_number++;
			}
		}
	}
	
	return(mine_number);
}

int revealed_check(int board_size) {

	int no_mine_total, no_mine_revealed = 0, k, j;
	const char REVEALED = '1', MINE = '*';

	no_mine_total = (8*board_size*board_size)/10 + 1; 
	
	/* Elegxos an exoun apokalyfthei (h antistoixh thesh tou displayed na einai 1),
	oles oi theseis tou kamba xwris narkh, epistrefontas to 1, ean nai, kai
	to 0 ean oxi */

	for (k = 0 ; k < board_size ; k++) {
		for (j = 0 ; j < board_size ; j++) {
			if ( (displayed[k][j] == REVEALED) && (game[k][j] != MINE) ) {
				no_mine_revealed++;
			}
		}
	}

	if (no_mine_revealed == no_mine_total) {
		return (1);
	}
	
	return (0); 

}

void print_board(int board_size) {

	int k, j; 
	const char REVEALED = '1';

	putchar(' ');
	putchar(' ');
	
	//Ektypwsh twn arithmwn twn sthlwn
	
	for (k = 1 ; k <= board_size ; k++) {
		printf(" %2d", k);
	}
	
	printf("\n\n");
	
	/* Ektypwsh tou kamva me '=' sth thesh oswn stoixeiwn tou game den exoun 
	apokalypthei (antistoixh thesh displayed einai 0) apo ton xrhsth */

	for (k = 0 ; k < board_size ; k++) {
		printf("%2d", k + 1);
		for (j = 0 ; j < board_size ; j++) {
			if (displayed[k][j] == REVEALED) {
				printf(" %2c", game[k][j]);
			}
			else {
				printf("  -");
			}
		}

		putchar('\n');
	}

	printf("\n\n");
}

void print_solution(int board_size) {
	
	int k, j; 
		
	putchar(' ');
	putchar(' ');

	//Ektypwsh twn arithmwn twn sthlwn

	for (k = 1 ; k <= board_size ; k++) {
		printf(" %2d", k);
	}
	
	printf("\n\n");
	
	//Ektypwsh twn stoixeiwn tou pinaka game, dhladh ths lyshs tou paixnidiou

	for (k = 0 ; k < board_size ; k++) {
		printf("%2d", k + 1);
		for (j = 0 ; j < board_size ; j++) {
			printf(" %2c", game[k][j]);
		}

		putchar('\n');
	}

	printf("\n\n");
}
		
		

	
	
