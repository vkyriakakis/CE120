/* 

   *Programmer: Kyriakakis Vasileios

   *Date: 26/12/2018

   *Purpose: To programma auto apotelei ena hmerologio, pou dinei ston
	xrhsth thn dynatothta na organwsei ta diafora rantevou tou
	sto diasthma enos mhna 30 hmerwn, epitrepwntas tou na
	prosthesei nea rantebou, na diagrapsei rantebou symfwna me thn
	kathgoria tous, h thn perigrafh tous, kai na emfanhsei ola
	ta rantebou tou ana hmera.
	
   *Input: 
	> Orismata apo thn grammh entolwn (proairetika):
		"-debug on": Emfanizontai eidika mhnymata pou proorizontai
			gia debugging kata thn ektelesh.
		"-debug off": Den emfanizontai tetoia mhnymata (to idio
			mporei na epiteuxthei an den dwthoun orismata 
			apo thn grammh entolwn).

	> Ta diafora xarakthrhstika enos rantebou (kathgoria, xronos enarxhs,
	xronos lhxhs, perigrafh), ta opoia eisagei o xrhsths apo to
	termatiko kata thn ektelesh tou programmatos.
	
   *Output: Emfanizei sto termatiko, ta rantebou tou xrhsth gia ton mhna, ana
	hmera. Enw epistrefei 0, an leitourghsei swsta kai -1, ean yparxei
	problhma me thn dynamikh desmeush mnhmhs.
*/	


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/********************** LITERALS *************************/

#define DAYS 30  /* plithos imerwn pou kaluptei to imerologio */

#define STR_MAX 31  /* megisto megethos sumboloseiras, sumperilambanomenou tou '\0' */

#define DAY_START 8  /* To nwritero pou mporei na ksekinisei ena rantebou einai 8:00 */
#define DAY_END 15  /* To argotero pou mporei na teleiwsei ena rantebou einai 15:00 */

/********************** TYPES *************************/

enum {FALSE, TRUE};

/* tupos enum: actionT
 * Oles oi dunates leitourgies gia to imerologio.
 * ADD: Prosthiki neou rantebou
 * REMOVE_BY_DESCR: Afairesi rantebou me basi tin perigrafi tous
 * REMOVE_BY_CAT: Afairesi rantebou me basi tin katigoria tous
 * PRINT: Ektupwsi olwn twn rantebou
 * EXIT: Eksodos apo to programma
 */
typedef enum { ADD=1, REMOVE_BY_DESCR, REMOVE_BY_CAT, PRINT, EXIT } actionT;


/* tupos enum: categoryT
 * Oles oi dunates kathgories rantebou.
 */
typedef enum {MEETING, CLASS, SKYPECALL} categoryT;


/* tupos struct: timeT
 * Anaparista mia xronikh stigmh me akribeia leptou.

 *Pedia:
 * hour: Akeraios pou naparista thn wra.
 * minutes: Anaparista ta lepta.
 */
typedef struct {
	int hour;
	int minutes;
} timeT;


/* tupos struct: meetingT
 * Kombos dipla diasyndedemenhs listas, pou periexei tis 
   plhrofories gia ena rantebou.

 *Pedia:
 * description: Dynamikos pinakas xarakthrwn pou periexei 
		mia syntomh perigrafh tou rantebou.
 * category: Anaparista thn kathgoria tou rantebou (MEETING, CLASS, SKYPECALL).
 * start_time: Anaparista ton xrono enarxhs tou rantebou
 * end_time: O xronos lhxhs tou rantebou.
 * prev: Deikths sto prohgoumeno stoixeio ths listas.
 * next: Deikths sto epomeno stoixeio ths listas.
 */
struct Meeting {
	char *description;
	categoryT category;
	timeT start_time;
	timeT end_time;
	struct Meeting *prev;
	struct Meeting *next;
};
typedef struct Meeting meetingT;
	

/********************** PROTOTYPES *************************/

void calendar_init(meetingT *calendar[DAYS]);

// Synarthseis menu: 
void printMenu();
void calendarMenu(meetingT *calendar[DAYS]);
void categoryMenu();

//Synartheseis elegxomenhs eisodou:
categoryT input_category();
char* input_descr();
timeT input_start();
timeT compute_end(timeT start);
void input_day(int *day, int *repeat_interval);

//Synarthseis diaxeirhseis hmerologiou:
void add_meeting(meetingT *calendar[DAYS]);
void remove_by_cat(meetingT *calendar[DAYS]);
void remove_by_descr(meetingT *calendar[DAYS]);
void print_calendar(meetingT *calendar[DAYS]);
void destroy_calendar(meetingT *calendar[DAYS]);

// Synarthseis diaxeirhseis listwn:
int day_add(meetingT **day_head, categoryT category, char *description, timeT start_time, timeT end_time);
meetingT *construct_entry(categoryT category, char *description, timeT start_time, timeT end_time);
char* category_to_string(categoryT category);
int day_print(meetingT *day_head);
void day_remove_by_cat(meetingT *current, meetingT **day_head, categoryT category, int day);
void day_remove_by_descr(meetingT *current, meetingT **day_head, char *description, int day);
void clear_list(meetingT *day_head);

/*********************** GLOBALS ************************/

/* debug: elegxei an tha ektupwthoun epipleon boithitika minumata 'i oxi.
 * An einai FALSE, den ektupwnontai, an einai TRUE ektupwnontai
 */
int debug = FALSE;


/********************** DEDOMENA ************************/

/*> Tha ylopoihsw to hmerologio ws enan statiko pinaka
   deiktes se meetingT kathe enas apo tous opoious 
   anaparista mia mera sthn opoia topothetountai rantebou, me kathe mera na
   anaparistatai apo mia dipla diasyndedemenh taxinomimenh kata auxousa wra enarxhs
   lista xwris termatiko apo stoixeia meetingT (rantebou)*/


/*********************** FUNCTIONS ************************/

int main (int argc, char *argv[]) {
	
	/*Pinakas apo deiktes se meetingT, kathe enas apo tous opoious 
	apotelei thn kefalh apo mia lista apo stoixeia meetingT (rantebou)*/

	meetingT *calendar[DAYS]; 

	//Elegxos orthothtas twn orismatwn pou dinontai sto programma apo thn grammh entolwn
	if (argc == 3) {
		if (strcmp(argv[1], "-debug") == 0) {
			if (strcmp(argv[2], "on") == 0) {
				debug = TRUE;
			}
			else if (strcmp(argv[2], "off") != 0) {
				printf("Ignoring incorrect arguements!\n");
			}
		}
	}
	else if (argc != 1) {
		printf("Ignoring incorrect arguements.\n");
	}
	
	//Klhsh ths calendar_init gia arxikopoihsh tou pinaka-hmerologiou
	calendar_init(calendar); 

	//Klhsh ths calendar_menu
	calendarMenu(calendar);

	return (0);
}

/***************************************************************************
 * calendar_init()                                                         *
 * Arxikopoiei ta stoixeia tou calendar[DAYS], ta opoia apoteloun kefales  *
 * dipla syndedemenwn listwn xwris termatiko se NULL.                      *
 * Parameters: Enas pinakas deiktwn se typo meetingT (hmerologio).         *           
 * Return value: kamia                                                     *
 ***************************************************************************/
void calendar_init(meetingT *calendar[DAYS]) {
	int k;
	
	for (k = 0 ; k < DAYS ; k++) {
		calendar[k] = NULL;
	}
}

//######################################################################################

// Synarthseis Menu : 

/*********************************
 * printMenu()                   *
 * Ektupwnei menou leitourgiwn.  *
 * Parameters: kamia             *
 * Return value: kamia           *
 *********************************/ 
void printMenu() {
	printf("\nSelect action:\n");
	printf("\t%d. Add appointment.\n", ADD);
	printf("\t%d. Cancel appointments by description.\n", REMOVE_BY_DESCR);
	printf("\t%d. Cancel appointments by category.\n", REMOVE_BY_CAT);
	printf("\t%d. Print appointments.\n", PRINT);
	printf("\t%d. Exit.\n--> ", EXIT);
}

/***************************************************************************
 * calendarMenu()                                                          *
 * Apotelei to menu epiloghs twn leitourgiwn tou programmatos.             *
   O xrhsths eisagei enan akeraio, kai analoga me thn timh tou typou       *
   actionT sthn opoia auth antistoixei, ekteleitai h analogh leitourgia.   *
   H diadikasia auth epanalambanetai mexri o xrhstsh na epilexei thn       *
   leitourgia EXIT.                                                        *                                        
 * Parameters: Enas pinakas deiktwn se typo meetingT (hmerologio).         *           
 * Return value: kamia                                                     *
 ***************************************************************************/

void calendarMenu(meetingT *calendar[DAYS]) {
	actionT option;

	do {
		printMenu();
		scanf("%u", &option);
		switch(option) {
			case ADD:
				add_meeting(calendar);
				break;
			case REMOVE_BY_DESCR:
				remove_by_descr(calendar);
				break;
			case REMOVE_BY_CAT:
				remove_by_cat(calendar);
				break;
			case PRINT:
				print_calendar(calendar);
				break;
			case EXIT:
				destroy_calendar(calendar);
				break;
			default:
				printf("ERROR: Incorrect selection. Try again.\n");
		}
	} while(option != EXIT);
}

/*************************************************************
 * categoryMenu()                                            *
 * Ektupwnei menu epiloghs kathgorias rantebou (categoryT).  *
 * Parameters: kamia                                         *
 * Return value: kamia                                       *
 *************************************************************/

void categoryMenu() {
	printf("Select category:\n");
	printf("\t%d. MEETING\n", MEETING);
	printf("\t%d. CLASS\n", CLASS);
	printf("\t%d. SKYPE CALL\n", SKYPECALL);
	printf("--> ");
}


//######################################################################################

// Synarthseis elegxomenhs eisodou: 

/***************************************************************************
 * input_category()                                                        *
 * Diabazei akeraia timh apo to plhktrologio, kai an auth antistoixei      *
 * se stoixeio ths categoryT thn epistrefei, alliws epanalambanei thn      *
 * diadikasia wspou na dwthei mia apodekth timh.                           *
 * Parameters: kamia                                                       *           
 * Return value: To stoixeio ths categoryT pou antistoixei sthn timh pou   *
 *	eishgage o xrhsths.                                                *
 ***************************************************************************/

categoryT input_category() {
	categoryT input;
	
	do {
		categoryMenu(); //Klhsh ths categoryMenu gia ektypwsh tou menou kathgoriwn
		scanf("%u", &input);
		if ((input > SKYPECALL) || (input < MEETING)) {
			printf("ERROR: Incorrect selection. Try again.\n");
		}
	} while ((input > SKYPECALL) || (input < MEETING));
	
	return(input);
}

/****************************************************************************
 * input_descr()                                                            *
 * Diabazei mia symboloseira apo to plhktrologio, kai desmeuei dynamika     *
 * xwro sthn mnhmh gia thn apothikeush ths, epeita epistrefei ton deikth    *
 * sto xekinhma ths dynamika desmeumenhs mnhmhs.                            *
 * Parameters: kamia                                                        *           
 * Return value:                                                            *
 * Se periptwsh swsths leitourgias o deikths sto xekinhma ths dynamika      *
 * desmeumenhs mnhmhs opou apothikeuetai h symbloseira, alliws an apotyxei  *
 * h desmeush epistrefei NULL.                                              *
 ***************************************************************************/

char* input_descr() {
	char *description;
	char buffer[STR_MAX];
	char format[STR_MAX/4]; 

	sprintf(format, "%%%ds", STR_MAX-1);
	printf("Enter short description: ");
	scanf(format, buffer);
	
	//Ektypwsh ths eisagwmenhs symboloseiras gia logou debugging and debug == TRUE
	if (debug == TRUE) {
		printf("You entered \"%s\".\n", buffer);
	}
	
	description = strdup(buffer);

	if (description == NULL) {
		return(NULL);
	}

	return(description);
}

/***************************************************************************
 * input_start()                                                           *
 * Diabazei ton xrono enarxhs enos rantebou sth morfh wres:lepta, kai      *
 * elegxei thn orthothta ths eisodou, kai to an ypakouei sta xronika oria  *
 * DAY_START kai DAY_END. Sthn periptwsh pou h eisodos einai orthi,        *
 * epistrefetai mia timh timeT sthn opoia eisagontai h wra kai ta          *
 * lepta pou eisagwntai, alliws epanalambanetai h diadikasia.              *
 * Parameters: kamia                                                       *           
 * Return value: Mia timh timeT pou periexei thn wra kai ta lepta pou      *
 *  eishgage o xrhsths.                                                    *
 ***************************************************************************/

timeT input_start() {
	timeT input;
	int hour;
	int minutes;

	//Elegxos gia akyres times wras kai leptwn
	do {
		printf("Enter start time in the form HH:MM : ");
		scanf("%02d:%02d", &hour, &minutes); 
		if ((hour >= DAY_END) || (hour < DAY_START) || (minutes < 0) || (minutes >= 60) ){
			printf("ERROR: Invalid hour or minute. Try again.\n");
		}
	} while((hour >= DAY_END) || (hour < DAY_START) || (minutes < 0) || (minutes >= 60));
	
	input.hour = hour;
	input.minutes = minutes;
	
	return(input);
}

/***************************************************************************
 * compute_end()                                                           *
 * Diabazei ton xrono diarkeias enos rantebou, kai ypologizei ton xrono    *
 * lhxhs tou me bash auton kai ton xrono enarxhs pou dinetai ws parametros.*
 * Parameters: O xronos enarxhs start enos rantebou.                       *           
 * Return value: Mia timh timeT pou periexei thn wra kai ta lepta pou      *
 *  tou xronou lhxhs pou ypologisthkan.                                    *
 ***************************************************************************/
	
timeT compute_end(timeT start) {
	timeT end; //Domh timeT pou anaparista ton xrono lhxhs
	int duration; //Xronos diarkeias tou rantebou

        //Elegxos eisodou wste to rantebou na lhgei to argotero stis 15:00
	do {
		//Elegxos eisodou wste duration > 0
		do {
			printf("Enter duration in minutes : ");
			scanf("%d", &duration);
			if (duration < 0) {
				printf("ERROR: Invalid duration. Try again.\n");
			}
		} while(duration < 0);
		
		//Ypologismos tou xronou lhxhs tou rantebou 
		end.hour = start.hour + (start.minutes + duration)/60;
		end.minutes = (start.minutes + duration) % 60;
		
		if ((end.hour > DAY_END) || ((end.hour == DAY_END) && (end.minutes != 0))) {
			printf("ERROR: Appointment exceeds end of workday. Try again.\n");
		}
	} while ((end.hour > DAY_END) || ((end.hour == DAY_END) && (end.minutes != 0)));
	
        //Enktypwsh twn xronwn lhxhs kai enarxhs gia logous debugging (debug == TRUE)
	if (debug == TRUE) {
		printf("You entered:  %02d:%02d - %02d:%02d.\n", start.hour, start.minutes, 
								      end.hour, end.minutes);
	}
	
	return(end);
}

/****************************************************************************
 * input_day()                                                              *
 * Diabazei enan akeraio pou anaparista mera (1-DAYS) kai enan arithmo      *
 * pou anaparista to diasthma epanalipshs enos rantebou, kai                *
 * tous apothikeuei se katalhles topothesies sth nmnh mesw twn deiktwn pou  *
 * dinontai ws parametroi.                                                  *
 * Parameters: Deiktes se akeraio day_ptr kai repeat_interval_ptr, mesw twn *
 * opoiwn apothikeuontai sth mnhmh oi eisagwmenes times.                    *           
 * Return value: kamia                                                      *
 ***************************************************************************/

void input_day(int *day_ptr, int *repeat_interval_ptr) {
	do {
		printf("Enter day (1 - %d) and repeat interval (>= 0):", DAYS);
		scanf("%d %d", day_ptr, repeat_interval_ptr);
		if ((*day_ptr <= 0) || (*day_ptr > DAYS) || (*repeat_interval_ptr < 0)) {
			printf("ERROR: Invalid day or interval. Try again.\n");
		}
	} while((*day_ptr <= 0) || (*day_ptr > DAYS) || (*repeat_interval_ptr < 0));
	
	return;
}



//#######################################################################################

/* Synarthseis diaxeirhshs tou hmerologiou (pinakas apo kefales dipla diasyndedemenwn listwn
  xwris termatiko, mh kyklikwn, taxinomimenwn kata auxousa seira me krithrio thn wra enarxhs twn rantebou */


/***************************************************************************\
 * add_meeting()                                                            *
 * Prosthetei ena rantebou me xarakthrhstika pou prosdiorizei o xrhsths,    *
 * sthn mera pou prosdiorise o xrhsths, kai se kathe mera ana to diasthma   *
 * epanalhpshs pou prodiorizei o xrhsths, ws DAYS.                          *
 *                                                                          *
 * Parameters: Enas pinakas deiktwn se typo meetingT (hmerologio), me       *
 * kathe deikth na apotelei kefalh listas, kai kathe lista na antistoixei   *
 * se mia mera.                                                             *
 *                                                                          *
 * Topikes metavlhtes:                                                      *
 *                                                                          *
 *   > category: Metavlhth categoryT pou anaparista thn kathgoria tou       *
 *	rantebou.                                                           *
 *   > description: Dynamikos pinakas se char, pou apothikeuei thn          *
 *       symboloseira perigrafhs tou rantebou.                              *
 *   > start_time: Xronos enarxhs tou rantebou.                             *
 *   > end_time: Xronos lhxhs tou rantebou.                                 *
 *   > day: Prwth mera sthn opoia topotheteitai to rantebou (DAYS > day > 0)* 
 *  > repeat_interval: Diasthma epanalhpshs tou rantebou.                   *
 *   > k: Metrhths.                                                         *
 *   > check: Apothikeuei thn timh epistrofhs ths day_add gia kalyterh      *
 *       anagnwsimothta.                                                    *
 *                                                                          *
 * Return value: kamia                                                      *
\****************************************************************************/
void add_meeting(meetingT *calendar[DAYS]){
	categoryT category; 
	char *description; 
	timeT start_time;
	timeT end_time;
	int k, check;
	int day;
	int repeat_interval;

	//Klhsh ths input_cateogry() gia ton kathorismo ths kathgorias tou rantebou
	category = input_category(); 
	
	//Klhsh ths input_descr() gia ton kathorismo ths perigrafhs tou rantebou
	description = input_descr(); 

	/*Se periptwsh sfalmatos sthn desmeush ths mnhmhs, olh h
	dynamika desmeumenh mnhmh tou hmerologiou eleutherwnetai,
	kai to programma termatizei */
	if (description == NULL) {
		printf("Exiting due to malloc error...\n");
		destroy_calendar(calendar);
		exit(-1);
	}

	//Klhsh ths input_start() gia ton kathorismo ths wras enarxhs tou rantebou
	start_time = input_start();

	//Klhsh ths compute_end() gia ton kathorismo ths wras lhxhs tou rantebou
	end_time = compute_end(start_time);

	/* Klhsh ths input_day() gia ton kathorismo ths prwths meras, kai tou
          diasthmatos epanalipshs repeat_interval tou rantebou */
	input_day(&day, &repeat_interval);
	

	/* An repeat_interval = 0, tote to rantebou topotheteitai mono sthn mera
         pou prosdioristhke */
	if (repeat_interval == 0) { 

		/*Klhsh ths day_add() gia prosthikh tou rantebou sthn lista-mera pou antistoixei
                 sthn mera pou prosdiorise o xrhsths */
		check = day_add(&calendar[day-1], category, description, start_time, end_time); 

		/*Se periptwsh sfalmatos sthn desmeush ths mnhmhs, olh h
		dynamika desmeumenh mnhmh tou programmatos eleutherwnetai,
		kai to programma termatizei */
		if (check == -1) {
			printf("Exiting due to malloc error...\n");
			free(description);
			destroy_calendar(calendar);
			exit(-1);
		}
		
		//Gia logous debugging
		if (debug == TRUE) {
			printf("Added appointment on day %d.\n", day); 
		}
	}

	/* Aliws topotheteitai sth mera pou prosdioristhke kai se kathe l
	ista-mera ana repeat_interval */
	else {
		for (k = day-1 ; k < DAYS ; k += repeat_interval) {
			/*Klhsh ths day_add() gia prosthikh tou rantebou sth lista-mera pou antistoixei
                 	 sthn mera pou prosdiorizei o metrhths k */
			check = day_add(&calendar[k], category, description, start_time, end_time);
			
			/*Se periptwsh sfalmatos sthn desmeush ths mnhmhs, olh h
			dynamika desmeumenh mnhmh tou programmatos eleutherwnetai,
			kai to programma termatizei */
			if (check == -1) {
				printf("Exiting due to malloc error...\n");
				free(description);
				destroy_calendar(calendar);
				exit(-1);
			}

			//Gia logous debugging
			if (debug == TRUE) {
				printf("Added appointment on day %d.\n", k+1);
			}		
		}
	}

	/* Apeleutherwsh tou arxikou description, afou se ola ta antigrafa
           tou rantebou pou apothikeuthkan sth lista, exoun eisagthei deiktes
           se antigrafa ths symvoloseiras descripion (vlepe day_add() kai construct_entry())*/
	free(description);
}

/***************************************************************************
 * remove_by_cat()                                                         *
 * Afairei ola ta rantebou mias sygekrimenhs kathgorias apo to hmerologio. *
 * Parameters: Enas pinakas deiktwn se typo meetingT (hmerologio), me      *
 * kathe deikth na apotelei kefalh listas, kai kathe lista na antistoixei  *
 * se mia mera.                                                            *
 * Return value: kamia                                                     *
 ***************************************************************************/

void remove_by_cat(meetingT *calendar[DAYS]){
	categoryT category; //H kathgoria twn rantebou pros diagrafh.
	int k;

	//Klhsh ths input_cateogry() gia ton kathorismo ths kathgorias twn rantebou
	category = input_category(); 
	
	/* Klhsh ths day_remove_by_cat gia diagrafh twn rantebou kathgorias 
 	 category apo kathe lista-mera calendar[k] pou einai apothikeunh 
         sto hmerologio */
	for (k = 0 ; k < DAYS ; k++) {
		day_remove_by_cat(calendar[k], &calendar[k], category, k+1);
	}
}

/***************************************************************************
 * remove_by_descr()                                                       *
 * Afairei ola ta rantebou pou prosdiorizontai apo mia sygekrimenh         *
 * perigrafh apo to hmerologio.                                            *
 * Parameters: Enas pinakas deiktwn se typo meetingT (hmerologio), me      *
 * kathe deikth na apotelei kefalh listas, kai kathe lista na antistoixei  *
 * se mia mera.                                                            *
 * Return value: kamia                                                     *
 ***************************************************************************/

void remove_by_descr(meetingT *calendar[DAYS]){

	char description[STR_MAX]; //H perigrafh twn rantebou pros diagrafh.
	char format[STR_MAX/4];
	int k;

	sprintf(format, "%%%ds", STR_MAX-1);
	printf("Enter short description: ");
	scanf(format, description);
	
	/* Klhsh ths day_remove_by_descr gia diagrafh twn rantebou me perigrafh 
 	 description apo kathe lista-mera calendar[k] pou einai apothikeunh 
         sto hmerologio */
	for (k = 0 ; k < DAYS ; k++) {
		day_remove_by_descr(calendar[k], &calendar[k], description, k+1);
	}
}


/***************************************************************************
 * print_calendar()                                                        *
 * Ekypwnei ola ta rantebou tou hmerologiou ana mera, opws auta exoun      *
 * taxinomithei se kathe mia apo tis epimerous meres-listes.               *
 * Parameters: Enas pinakas deiktwn se typo meetingT (hmerologio), me      *
 * kathe deikth na apotelei kefalh listas, kai kathe lista na antistoixei  *
 * se mia mera.                                                            *
 * Return value: kamia                                                     *
 ***************************************************************************/

void print_calendar(meetingT *calendar[DAYS]){
	int k, check;
	
	for (k = 0 ; k < DAYS ; k++) {

		if (calendar[k] != 0) {
			printf("=======\n");
			printf("DAY %2d\n", k+1);

			//Klhsh ths day_print() gia ekypwsh twn rantebou ths kathe meras
			check = day_print(calendar[k]);

			/*Se periptwsh sfalmatos sthn desmeush ths mnhmhs, olh h
			dynamika desmeumenh mnhmh tou programmatos eleutherwnetai,
			kai to programma termatizei */

			if (check == -1) {
				printf("Exiting due to malloc error...\n");
				destroy_calendar(calendar);
				exit(-1);
			}
		}
	}
}

/***************************************************************************
 * destroy_calendar()                                                      *
 * Apeleutherwnei olh th dynamika desmeumenh mnhmh tou hmerologiou.        *
 * Parameters: Enas pinakas deiktwn se typo meetingT (hmerologio), me      *
 * kathe deikth na apotelei kefalh listas, kai kathe lista na antistoixei  *
 * se mia mera.                                                            *
 * Return value: kamia                                                     *
 ***************************************************************************/

void destroy_calendar(meetingT *calendar[DAYS]){

	int k;
	
	for (k = 0 ; k < DAYS ; k++) {
		/* Efoson mia lista-mera den einai adeia, kalei thn clear_list
       		   gia thn apodesmeush ths mnhmhs pou exei desmeutei gia authn */
		if (calendar[k] != NULL) {
			clear_list(calendar[k]);
		}
	}
}


//############################################################################################

/* Synarthseis diaxeirhshs ths kathe hmeras, oi opoies ylopoiountai ws dipla diasyndedemenes listes
  xwris termatiko, mh kyklikes, taxinomimenes kata auxousa seira me krithrio thn wra enarxhs twn rantebou */


/***************************************************************************
 * day_add()                                                               *
 * Prosthetei ena rantebou se mia mera tou hmerologiou.                    *                                    
 * Parameters:                                                             *
 *	 > day_head: Pointer pou deixnei sthn kefalh ths listas-meras sthn *
 *            opoia tha ginei h prosthikh tou rantebou.                    *
 *       > category: H kathgoria tou rantebou pros prosthikh.              *
 *       > description: H symvoloseira perigrafhs tou rantebou pros        *
 *            prosthikh.                                                   *
 *       > start_time: O xronos enarxhs tou rantebou pros prosthikh.       *
 *       > end_time: O xronos enarxhs tou rantebou pros prosthikh.         *
 * Return value: Enas akeraios tou opoiou h timh shmatodotei to an         *
 *      petyxe (0) h apetyxe (-1) h desmeush mnhmhs gia ton neo kombo ths  *
 *	listas.                                                            *
 ***************************************************************************/

int day_add(meetingT **day_head, categoryT category, char *description, timeT start_time, timeT end_time) {
	
	//Deiktes pou xrhsimopoiountai gia thn prospelash ths listas

	meetingT *previous, *current; 


	//Kwdikas gia thn prosthikh tou prwtou stoixeiou ths listas

	if (*day_head == NULL) {
		current = construct_entry(category, description, start_time, end_time);
		
		if (current == NULL) {
			printf("Exiting due to malloc error... \n");
			return(-1);
		}
		
		current->next = NULL;
		current->prev =NULL;
		*day_head = current;

		return(0);
	}

	/*Kwdikas gia thn euresh tou prwtou stoixeiou ths listas me wra 
	enarxhs megalyerh h ish auths tou rantebou pros prosthikh, wste
	h lista na einai taxinomimenh kata auxousa seira */
	for (previous = NULL, current = *day_head ; 
	    (current != NULL) && (((current->start_time).hour < start_time.hour) || 
		(((current->start_time).hour == start_time.hour) && ((current->start_time).minutes < start_time.minutes))); 
	         previous = current, current = current->next);

	/* Klhsh ths construct_entry gia thn desmeush mnhmhs gia thn apothikeush 
         tou rantebou pros prosthikh */
	current = construct_entry(category, description, start_time, end_time);
		
	/*Se periptwsh sfalmatos sthn desmeush ths mnhmhs, h synarthsh epistrefei -1 */
	if (current == NULL) {
		printf("Exiting due to malloc error... \n");
		return(-1);
	}
	
	/* An previous = NULL tote o current deixnei sthn kefalh ths listas kai 
          exoume thn periptwsh ths prosthikhs tou rantebou ws nea kefalh */
	if (previous == NULL) {
		current->next = *day_head;
		current->prev = NULL;
		(*day_head)->prev = current;
		*day_head = current;
		
		return(0);
	}

	/* An previous->next = NULL tote current = NULL, kai exoume thn periptwsh
 	 ths prosthikhs tou rantebou sto telos ths listas */
	if (previous->next == NULL) {
		previous->next = current;
		current->next = NULL;
		current->prev = previous;
		
		return(0);
	}

	//Prosthikh tou rantebou se endiamesh thesh ths listas

	current->next = previous->next;
	current->prev = previous;
	previous->next->prev = current;
	previous->next = current;
		
	return(0);
}

/****************************************************************************
 * construct_entry()                                                        *
 * Desmeuei dynamika mnhmh gia ena struct typou meetingT, kai eisagei       *
 * sta antistoixa pedia tis times pou dinontai ws parametroi apo ton xrhsth.* 
 * Parameters: H kathgoria enos rantebou category, mia symboloseira         *
 * description, o xronos enarxhs start_time, kai o xronos lhxhs end_time.   *           
 * Return value: O deikths meeting, pou deixnei sto xekinhma ths mnhmhs     *
 *  pou desmeuthke dynamika gia thn apothikeush meetingT.                   *
 ***************************************************************************/

meetingT *construct_entry(categoryT category, char *description, timeT start_time, timeT end_time) {
	meetingT *meeting;

	meeting = (meetingT*)malloc(sizeof(meetingT));

	if (meeting == NULL) {
		return(NULL);
	}
	
	meeting->description = strdup(description);
			
	if (meeting->description == NULL) {
		free(meeting);
		return(NULL);
	}
	
	meeting->category = category;
	meeting->start_time = start_time;
	meeting->end_time = end_time;
	
	return(meeting);
}


/***************************************************************************
 * category_to_string()                                                    *
 * Dexetai ena stoixeio ths aparithmishs categoryT, kai desmeuei dynamika  *
 * mnhmh gia thn apothikeush ws symvoloseira tou onomatos ths antistoixhs  *
 * kathgorias pou antistoixei se auto, me kefalaia grammata.               *
 * Parameters: Ena stoixeio tou typou categoryT (MEETING, CLASS, SKYPECALL)*                      
 * Return value: Deikths se xarakthra pou deixnei sthn arxh ths dynamika   *
 *   desmeumenhs mnhmhs sthn opoia apothikeutai h zhtoumenh symboloseira.  *
 ***************************************************************************/

char* category_to_string(categoryT category) {
	char *string;

	switch(category) {
		case MEETING:
			string = strdup("MEETING");
			if (string == NULL) {
				return(NULL);
			}
			break;
		case CLASS:
			string = strdup("CLASS");
			if (string == NULL) {
				return(NULL);
			}
			break;
		case SKYPECALL:
			string = strdup("SKYPE CALL");
			if (string == NULL) {
				return(NULL);
			}
			break;
	}
	
	return(string);
}

/***************************************************************************
 * day_print()                                                             *
 * Ektypwnei ta rantebou mias meras tou hmerologiou.                       *
 * Parameters: Enas pinakas deiktwn se typo meetingT (hmerologio), me      *
 * kathe deikth na apotelei kefalh listas, kai kathe lista na antistoixei  *
 * se mia mera.                                                            *
 * Return value: 0 ean oloklhrwthei epityxws h ektelesh, alliws -1.        *
 ***************************************************************************/

int day_print(meetingT *day_head) {

	//Deikths pou xrhsimopoihtai gia thn prospelash ths listas
	meetingT *current;

	//Symvoloseira pou anaparista to onoma ths kathgorias enos rantebou
	char* category_name; 
	
	//An h lista einai adeia, h synarthsh epistrefei
	if (day_head == NULL) {
		return(0);
	}
	
	for (current = day_head ; current != NULL ; current = current->next) {
		category_name = category_to_string(current->category);

		/* An den petyxei h desmeush tou category_name sthn category_to_string,
		   h synarthsh epistrefei to -1 */

		if (category_name == NULL) {
			return(-1);
		}
		printf("\t%s (%s), %02d:%02d - %02d:%02d\n", category_name, 
							 current->description, 
							 (current->start_time).hour,
							 (current->start_time).minutes,
							 (current->end_time).hour,
							 (current->end_time).minutes);
		free(category_name); 
	}

	return(0);
}							

/***************************************************************************
 * day_remove_by_cat()                                                     *
 * Afairei ola ta rantebou mias sygekrimenhs kathgorias apo mia mera tou   *
 * hmerologiou.                                                            *                                    
 * Parameters:                                                             *
 *	 > current: Deikths pou xrhsimopoihtai gia thn prospelash ths      *
 *		listas.                                                    *
 *       > day_head: Deikths sthn kefalh ths listas, prokeimenou na        *
 *               allaxei h timh ths kai ektos ths synarthshs auths, sthn   *
 *		 periptwsh diagrafhs tou prwtou rantebou.                  *
 *       > category: H kathgoria twn rantebou pros diagrafh.               *
 *       > day: Metavlhth pou paristanei thn mera sthn opoia antistoixei h *
 *           lista, xrhsimopoieitai gia ektypwsh katallhlou mhnymatos kata *
 *	     to debugging.                                                 *
 * Return value: kamia                                                     *
 ***************************************************************************/		

void day_remove_by_cat(meetingT *current, meetingT **day_head, categoryT category, int day) {

	//Basikh periptwsh, h lista na einai adeia
	if (current == NULL) {
		return;
	}
	
	/* Anadromiko bhma, h diagrafh tou rantebou, efoson auto exei kathgoria
	  category ginetai meta thn anadromikh klhsh, wste h diagrafh tou na
	  afhsei analloiwth thn oura ths listas */
	else {
		day_remove_by_cat(current->next, day_head, category, day);
		if (current->category == category) {
			
			// Periptwsh opou h lista apoteleitai mono apo ena rantebou
			if ((current == *day_head) && (current->next == NULL)) {
				free(current->description);
				free(current);
				*day_head = NULL;
			}
			// Periptwsh opou to rantebou pros diagrafh apotelei thn kefalh ths listas
			else if (current == *day_head) {
				current->next->prev = NULL;
				*day_head = current->next;
				free(current->description);
				free(current);
			}
			// Periptwsh opou to rantebou pros diagrafh vrisketai sto telos ths listas
			else if (current->next == NULL) {
				current->prev->next = NULL;
				free(current->description);
				free(current);
			}
			// Kwdikas gia endiamesh diagrafh rantebou
			else {
				current->prev->next = current->next;
				current->next->prev = current->prev;
				free(current->description);
				free(current);
			}
			// Ektypwsh mhnymatos kata to debugging
			if (debug == TRUE){
				printf("Removed appointment on day %d.\n", day); 
			}
		}
	}

}

/***************************************************************************
 * day_remove_by_descr()                                                   *
 * Afairei ola ta rantebou mias sygekrimenhs perigrafhs apo mia mera tou   *
 * hmerologiou.                                                            *                                    
 * Parameters:                                                             *
 *	 > current: Deikths pou xrhsimopoihtai gia thn prospelash ths      *
 *		listas.                                                    *
 *       > day_head: Deikths sthn kefalh ths listas, prokeimenou na        *
 *               allaxei h timh ths kai ektos ths synarthshs auths, sthn   *
 *		 periptwsh diagrafhs tou prwtou rantebou.                  *
 *       > description: H perigrafh twn rantebou pros diagrafh.            *
 *       > day: Metavlhth pou paristanei thn mera sthn opoia antistoixei h *
 *           lista, xrhsimopoieitai gia ektypwsh katallhlou mhnymatos kata *
 *	     to debugging.                                                 *
 * Return value: kamia                                                     *
 ***************************************************************************/		

void day_remove_by_descr(meetingT *current, meetingT **day_head, char *description, int day) {

	//Basikh periptwsh, h lista na einai adeia
	if (current == NULL) {
		return;
	}

	/* Anadromiko bhma, h diagrafh tou rantebou, efoson auto exei perigrafh
	  description ginetai meta thn anadromikh klhsh, wste h diagrafh tou na
	  afhsei analloiwth thn oura ths listas */
	else {
		day_remove_by_descr(current->next, day_head, description, day);
		if (strcmp(current->description, description) == 0) {

			// Periptwsh opou h lista apoteleitai mono apo ena rantebou
			if ((current == *day_head) && (current->next == NULL)) {
				free(current->description);
				free(current);
				*day_head = NULL;
			}
			// Periptwsh opou to rantebou pros diagrafh apotelei thn kefalh ths listas
			else if (current == *day_head) {
				current->next->prev = NULL;
				*day_head = current->next;
				free(current->description);
				free(current);
			}
			// Periptwsh opou to rantebou pros diagrafh vrisketai sto telos ths listas
			else if (current->next == NULL) {
				current->prev->next = NULL;
				free(current->description);
				free(current);
			}
			// Kwdikas gia endiamesh diagrafh rantebou
			else {
				current->prev->next = current->next;
				current->next->prev = current->prev;
				free(current->description);
				free(current);
			}
			// Ektypwsh mhnymatos kata to debugging
			if (debug == TRUE){
				printf("Removed appointment on day %d.\n", day); 
			}
		
		}
	}

}

/***************************************************************************
 * clear_list()                                                            *
 * Apeleutherwnei olh th desmeumenh mnhmh mias meras-listas.               *
 * Parameters: H kefalh mias listas-meras.                                 *
 * Return value: kamia                                                     *
 ***************************************************************************/

void clear_list(meetingT *day_head) {
	// Basikh periptwsh, h lista na einai adeia
	if (day_head == NULL) {
		return;
	}

	// Anadromiko bhma
	else {
		clear_list(day_head->next);
		free(day_head->description);
		free(day_head);
		return;
	}
}
	
