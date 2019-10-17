/* 

   *Programmer: Kyriakakis Vasileios

   *Date: 3/12/2017

   *Purpose: To programma auto parexei ston xrhsth th dynatothta na epexergastei
	arxeia eikonas typou ppm. O xrhsths mporei na metatrepsei mia eikona se
	grayscale, na metavallei thn fwteinothta ths, na diplasiasei to megethos
	ths, h na thn strepsei wrologia kata 90 moires.
	
   *Input: To apolyto h to sxetiko filepath mias eikonas ppm, mesw tou opoiou
	to programma diabazei thn eikona pros epexergasia.
	
   *Output: H epexergasmenh eikona, pou apothikeuetai symfwna me filepath pou
	eisagei o xrhsths.

   *Conditions: To programma leitourgei theorwntas pws h eikona pros epexergasia
	einai typou ppm, h megisth fwteinothta einai mikroterh h ish tou 255
	kai pws to megethos ths den yperbainei to 1024x1024 (platos x ypsos).
*/	


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IMG_SIZE 1024
#define MAX_FILEPATH 256

//Dhlwsh synarthsewn:

/* H etoimh synarthsh load_image dexetai to filepath (se morfh symboloseiras) pou eisagei o
xrhsths, gemizei ton pinaka img me tis fwteinothtes twn pixel ths eikonas, kai apothikeuei 
to platos kai to ypsos ths, kathws kai thn megisth fwteinothta enos pixel stis 
antistoixes metavlhtes ths main */
int load_image(char *filepath, int img[][IMG_SIZE], int *width, int *height, int *color_depth);

/* H etoimh synarthsh save_image dexetai to filepath sto opoio tha apothikeutei h
epexergasmenh eikona, kai dhmiourgei to arxeio ppm ths, sto opoio grafei 
tis aparaithtes plhrofories gia thn eikona (platos, ypsos, megisth fwteinothta,
RGB tou kathe pixel */

int save_image(char *filepath, int img[][IMG_SIZE], int width, int height, int color_depth);

/* H synarthsh RGB_combine apothikeuei ta Byte Red, Green, Blue tou kathe pixel ths
eikonas se enan akeraio arithmo twn 4 bit gia thn pio eukolh apothikeusei tous
ston pinaka ths eikonas mesw ths load_image */

int RGB_combine(int red, int green, int blue);

/* H synarthsh RGB_decompose pairnei ton akeraio pou apothikeuetai se mia thesh tou pinaka 
ths eikonas kai ton aposynthetei sta red, green, blue bytes tou pixel autou */

void RGB_decompose(int combined, int *red_ptr, int *green_ptr, int *blue_ptr);

/* H print_image ektypwnei ta pixel ths eikonas sto terminal, me ta R, G, B tou kathe
pixel na einai sto dekaexadiko systhma */

void print_image(int img[][IMG_SIZE], int width, int height, int max_brightness);

/* H luminosity_change allazei th fwteinothta olwn twn pixel ths eikonas symphwna
me ton syntelesth metavolhs fwteinothtas pou eisagei o xrhsths */

void luminosity_change(int img[][IMG_SIZE], int width, int height, int max_brightness, double lum_factor); 

/* Metatrepei thn eikona se grayscale */
void greyscale_convert(int img[][IMG_SIZE], int width, int height);

/* Diplasiazei, efoson auto einai dynato (eikona x 2 <= 1024 x 1024), to megethos ths eikonas,
allazontas katallhla tous arithmous pou anaparistoun to platos kai to ypsos ths */

void double_size(int img[][IMG_SIZE], int *width, int *height);

/* Peristrefei thn eikona dexia kata 90 moires, allazontas katallhla to platos kai to
ypsos ths */

void rotate_clockwise_90deg(int img[][IMG_SIZE], int *width, int *height);

// Synarthsh antimetaheshs 2 akeraiwn arithmwn number1 kai number2
void swap(int *number1_ptr, int *number2_ptr);


int main(int argc, char *argv[]) {
	
	//Dhlwsh metavlhtwn:

	/*
	> Oi height, width, max_brightness apothikeuoun to ypsos, to platos, kai th 
	megisth fwteinothta twn pixel ths eikonas antistoixa 
	>H error_check veltiwnei thn anagnwsimothta twn synthikwn
	>O pinakas image apothikeuei se kathe thesh tou ton akeraio pou syndyazei
	ta R, G. B gia kathe pixel ths eikonas
	>H filepath apothikeuei to filepath pou eisagei o xrhsths
	>H luminosity_factor ton syntelesth metavolhs ths fwtienothtas
	*/

	int height, width, max_brightness, error_check;
	int image[IMG_SIZE][IMG_SIZE];
	char option, filepath[MAX_FILEPATH], format[MAX_FILEPATH/20];
	double luminosity_factor;
	
	/* Elegxos me do-while gia thn yparxh tou filepath pou eisagei o xrhsths,
	an yparxei, h eikona fortwnetai sto programma */

	do {
		printf("Enter file path to load image: ");
		sprintf(format, "%%%ds", MAX_FILEPATH-1);
		scanf(format, filepath);
		error_check = load_image(filepath, image, &width, &height, &max_brightness);
		if (error_check == -1) {
			printf("Invalid path!\n");
		}
	} while (error_check == -1);

	printf("Load OK!\n");

	//To menu tou programmatos

	do {
		printf("Enter option:\n");
		printf("Print image to screen: (P/p)\n");
		printf("Load another image: (L/l)\n");
		printf("Save image: (S/s)\n");
		printf("Change luminosity (U/u)\n");	
		printf("Convert to grayscale: (G/g)\n");
		printf("Duplicate size: (D/d)\n");
		printf("Rotation: (R/r)\n");
		printf("Quit: (Q/q)\n");
		scanf(" %c", &option);
		switch(option) {
			case 'P':
			case 'p':
				print_image(image, width, height, max_brightness);
				break;
			case 'l':
			case 'L':
				/*Elegxos gia thn yparxh tou filepath pou eisagei
				o xrhsths, ean yparxei tote fortwnetai nea eikona sto programma */
				do {
					printf("Enter file path to load image: ");
					scanf(format, filepath);
					error_check = load_image(filepath, image, &width, &height, &max_brightness);
					if (error_check == -1) {
						printf("Invalid path!\n");
					}
				} while (error_check == -1);
				break;
			case 'S':
			case 's':
				/*Elegxos gia thn yparxh tou filepath pou eisagei o xrhsths, ean
				yparxei tote h epexergasmenh eikona apothikeuetai symfwna me auto */
				do {
					printf("Enter file path to save image: ");
					scanf(format, filepath);
					error_check = save_image(filepath, image, width, height, max_brightness);
					if (error_check == -1) {
							printf("Invalid path!\n");
					}
				} while (error_check == -1);
				break;
			case 'u':
			case 'U':
				/* Elegxos ths timhs tou syntelesth metabolhs fwteinothtas pou
				eisagei o xrhsths */
				do {
					printf("Enter luminocity factor (factor>0 &&factor<=2): ");
					scanf("%lf", &luminosity_factor);
					if ((luminosity_factor <= 0) || (luminosity_factor > 2)){
						printf("Factor should be between (0,2]\n");
					}
				} while ((luminosity_factor < 0) || (luminosity_factor > 2));
				luminosity_change(image, width, height, max_brightness, luminosity_factor);
				printf("Conversion OK!\n");
				break;
			case 'g':
			case 'G':
				greyscale_convert(image, width, height);
				printf("Conversion OK!\n");
				break;
			case 'd':
			case 'D':
				double_size(image, &width, &height);
				break;
			case 'r':
			case 'R':
				rotate_clockwise_90deg(image, &width, &height);
				printf("Rotation OK!\n");
				break;
			case 'q':
			case 'Q':
				return(0);
		}
	} while(1);
	
	return (0);
}
	


int load_image(char *filepath, int img[][IMG_SIZE], int *width, int *height, int *color_depth) {
	char str[5];
	int row, col, red, green, blue;

	FILE *fp = fopen(filepath, "r");
	if(!fp) {
		return -1;
	}	
	fscanf(fp, "%4s", str);
	if(strcmp(str, "P3")) {
		printf("Wrong magic number! Expected P3. Exiting...\n");
		exit(-1);
	}
	fscanf(fp, "%d", width);
	fscanf(fp, "%d", height);
	fscanf(fp, "%d", color_depth);
	
	for(row=0; row<*height; row++) 
		for(col=0; col<*width; col++) {
			fscanf(fp, "%d", &red);
			fscanf(fp, "%d", &green);
			fscanf(fp, "%d", &blue);
			/* Klhsh ths RGB_combine gia ton syndyasmo twn red, green, blue 
			se enan akeraio gia kathe pixel kai apothikeush sthn katallhlh thesh
			tou img */ 
			img[row][col] = RGB_combine(red, green, blue);
		}
	fclose(fp);
	return 0;
}

int RGB_combine(int red, int green, int blue) {
	int combined; 
	/* Xrhsh tou telesth << gia katallhlh metatopish twn 8bit twn red, green kai
	tou telesth | gia ton syndyasmo twn red, green, blue sthn timh combined (afou
	p.x 0101 0000 | 0000 1010 = 0101 1010 logw twn X | 1 = 1 kai X | 0 = x) */
	combined = (red<<16);
	combined = combined | (green<<8);
	combined = combined | blue;
	return(combined);
}

void RGB_decompose(int combined, int *red_ptr, int *green_ptr, int *blue_ptr) { 
	
	/* Xrhsh maskas (me ton telesth &, afou X & 1 = X kai X & 0 = 0 gia opoiodhpote bit X), p.x.
	 0101 1110 & 0000 1111 = 0000 1110 gia thn aposynthesh tou combined 
	stis times red, green, blue gia ena pixel */
	*red_ptr = combined >> 16;
	*green_ptr = (combined>>8) & 255; 
	*blue_ptr = combined & 255;
}
	

void print_image(int img[][IMG_SIZE], int width, int height, int max_brightness) {
	int row, col;
	int red, green, blue;

	//Ektypwsh twn xarakthristhkwn ths eikonas sto terminal
	
	printf("###########   IMAGE   ###########\n");
	printf("%d %d %d\n", width, height, max_brightness);
	
	/* Ektypwsh twn red, green, blue kathe pixel sto terminal, ekfrasmena sto dekaexadiko systhma,
	me xrhsh ths RGB_decompose gia ton diaxwrismo kathe stoixeiou tou pinaka img */
	
	for (row = 0 ; row < height ; row++) { 
		for (col = 0 ; col < width ; col++) {
			RGB_decompose(img[row][col], &red, &green, &blue);
			printf("%x %x %x ", red, green, blue);
		}
		putchar('\n');
	}
	
	printf("############################\n\n");
}
	
int save_image(char *filepath, int img[][IMG_SIZE], int width, int height, int color_depth) {
	int row, col, red, green, blue;
	
	FILE *fp = fopen(filepath, "w");
	if(!fp) {
		return -1;
	}
	fprintf(fp, "P3\n");
	fprintf(fp, "%d %d %d\n", width, height, color_depth);

	/* Xrhsh ths RGB_decompose gia thn aposynthesh tou kathe stoixeiou tou img,
	sta red, green, blue tou pixel sto opoio antistoixei gia thn apothikeush sto arxeio
	ppm */
	
	for(row=0; row<height; row++)
		for(col=0; col<width; col++) {
			RGB_decompose(img[row][col], &red, &green, &blue);
			fprintf(fp,"%d %d %d\n", red, green, blue);
		}
	fclose(fp);
	return 0;
}

void luminosity_change(int img[][IMG_SIZE], int width, int height, int max_brightness, double lum_factor) {
	int row, col; 
	int red, green, blue;

	for (row = 0 ; row < height ; row++) {
		for (col = 0 ; col < width ; col++) {
		/* Xrhsh ths RGB_decompose gia na apokthsw prosbash sta red, green, blue tou
		   kathe pixel, kai xrhsh ths RGB_compose gia na ta xanaenwsw se enan akeraio
		   afou prwta ta pollaplasiasw me ton syntelesth metavolhs fwteinothtas.
	           Na shmeiwthei o elegxos gia na mhn yperboun oi times twn red, green,
		   blue thn megisth fwteinothta, kai to typecast se int gia thn
		   swsth apothikeush twn color*lum_factor sta color */
				
			RGB_decompose(img[row][col], &red, &green, &blue);
			red = (int)(red*lum_factor);
			if (red > max_brightness) {red = max_brightness;}
			green = (int)(green*lum_factor);
			if (green > max_brightness) {green = max_brightness;}
			blue = (int)(blue*lum_factor);
			if (blue > max_brightness) {blue = max_brightness;}
			img[row][col] = RGB_combine(red, green, blue);

		}
	}
}

void greyscale_convert(int img[][IMG_SIZE], int width, int height) {
	int row, col;
	int red, green, blue, grey;
	
	/* Metatroph ths eikonas se grayscale, symfwna me ton typo 
	GREY = 0.3*red + 0.59*green + 0.11*blue, kai me thn xrhsh twn
	synarthsewn RGB_decompose kai RGB_combine gia ton diaxwrismo kai thn
	epanenwsh twn red, green, blue se enan akeraio gia kathe pixel ths
	eikonas */

	for (row = 0 ; row < height ; row++) {
		for (col = 0 ; col < width ; col++) {
			RGB_decompose(img[row][col], &red, &green, &blue);
			grey = (int)(red*0.3 + green*0.59 + blue*0.11);	
			red = green = blue = grey;
			img[row][col] = RGB_combine(red, green, blue);
		}
	}
}

void double_size(int img[][IMG_SIZE], int *width, int *height) {
	int row, col;

	/* Elegxos gia to an xwraei h diplasiasmenh eikona sto tetragwno 1024 x 1024 */
	if ((2*(*width) <= IMG_SIZE) && (2*(*height) <= IMG_SIZE)) {

		for (row = (*height) - 1 ; row >= 0 ; row--) {
			for (col = (*width) - 1 ; col >= 0 ; col--) {
				img[2*row][2*col] = img[row][col];
				img[2*row + 1][2*col] = img[row][col];
				img[2*row][2*col + 1] = img[row][col];
				img[2*row + 1][2*col + 1] = img[row][col];
			}
		}

	//Metabolh tou ypsous kai tou platous ths eikonas stis times tous meta ton diplasiasmo
		(*width) *= 2;
		(*height) *= 2;
		printf("Duplication OK!\n"); 
		return;
	}
	else {
		printf("Image is too large!\n");
	}
}


void rotate_clockwise_90deg(int img[][IMG_SIZE], int *width, int *height) { 
	int row, col;

	/* Sthn periptwsh pou h eikona exei platos >= toy ypsous, ylopoiw thn peristrofh
	prwta me antimetatheseis kathe stoixeiou img[row][col] panw apo thn kyria diagwnio
	(opou vriskontai ta img[k][k]), me to stoixeio img[col][row] */

	if (*width >= *height) {
		for (row = 0 ; row < *height ; row++) {
			for (col = row + 1 ; col < *width ; col++) { 
				swap(&img[row][col], &img[col][row]);
			}
		}
	}

	/* Sthn periptwsh pou h eikona exei ypsos > platous, ylopoiw thn peristrofh
	prwta me antimetatheseis kathe stoixeiou img[row][col] katw apo thn kyria diagwnio
	(opou vriskontai ta img[k][k]), me to stoixeio img[col][row] */
	else {
		for (row = 0 ; row < (*height) ; row++) {
			for (col = 0 ; col < row ; col++) {
				swap(&img[row][col], &img[col][row]);
			}
		}
	}

	//Antimetathetw ta height, width meta thn anastrofh tou pinaka
	swap(height, width); 

	/* Telos antimetathetw tis sthles me tetoio tropo wste na antistrafei h seira tous, p.x.
	0,1,2 ==> 2,1,0 */
	for (col = 0 ; col < (*width/2) ; col++) { 
		for (row = 0 ; row < *height ; row++) {
			swap(&img[row][col], &img[row][*width - 1 - col]);
		}
	}
}
		
void swap(int *number1_ptr, int *number2_ptr) {
	int temp;
	
	temp = *number1_ptr;
	*number1_ptr = *number2_ptr;
	*number2_ptr = temp;

}
			
		
