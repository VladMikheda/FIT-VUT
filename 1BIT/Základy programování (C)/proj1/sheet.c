
/**
  * Soubor:   sheet.c
  * Predmet:  IZP 2020/21
  * Autor:    Vladslaav Mikheda Login:xmikhe00
  * Pojekt:   čislo 1: Práce s textem
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

//všechny flagi který máme
const char *const FLAGS[]= {"irow","arow","drow","drows","icol","acol","dcol","dcols","cset","tolower","toupper"
												,"round","int","copy","swap","move","rows","beginswith","contains"};
//počet flagu
const int AMOUNT_OF_FLAGS =(sizeof(FLAGS)/sizeof(FLAGS[0]));

//maximální počet argumentů po flagu
const int MAX_AMOUNT_OF_ARGUMENTS = 2;

struct Srows
{
	int number;
	int amount_cols;
	char string_bufer[10340]; //10kib(10240) + 100 protože potřebujeme te bunky perepisovat
	char new_string_bufer[10240];
	bool treatment;
};

struct Sflags
{	
	int number; 
	int arg1;
	int arg2;
	char str[101];
};

//nachází počet děličů
int finde_quantity_of_separate(int *quantity_separate,char **argv, int argc)
{	int slider = 0;
	if(argv[1][0] == '-' && argv[1][1] == 'd')
	{ 	if(argc == 2)
			return 104;
		for(; argv[2][slider] !='\0';)
			slider++;
	}
	*quantity_separate = slider;
	return 0;
}
//přepíšeme děličů
void writes_separators(char **argv, int amount_separators, char *separators, int *start_number_flags)
{
	//pokud nemáme žádný oddělovač, vyplním pole mezerou a označíme začátek prvního flagu
	if(amount_separators < 1)
	{
		*start_number_flags = 1; 
		separators[0] = ' ';
		separators[1] = '\0';
	}
	else //pokud máme
	{	
		*start_number_flags = 3; 
		separators[0] = '\0';
		int slider_rewrite_separators = 0;
		int slider = 0;

		for(slider = 0; argv[2][slider] != '\0';slider++)
		{
			separators[slider] = argv[2][slider];
		}
		separators[slider] = '\0';


		for(int slider_now_separators = 0; slider_now_separators < amount_separators; slider_now_separators++)
		{
			for(int slider_repid_separators = slider_now_separators+1; slider_repid_separators < amount_separators;slider_repid_separators++)
			{
				if(separators[slider_repid_separators] == separators[slider_now_separators])
				{
					for(slider_rewrite_separators = slider_repid_separators; slider_rewrite_separators + 1 < amount_separators;slider_rewrite_separators++)
					{
						separators[slider_rewrite_separators] = separators[slider_rewrite_separators + 1];
					}
					slider_repid_separators--;
					amount_separators--;
					separators[slider_rewrite_separators] = '\0';
				}	
			}
		}
	}
}

//zjistíme je to flag, nebo ne(vrací true nebo false)
bool flags_ownership_check(int num_str, char **argv)
{	
	bool flag_exist = false;
	for(int i = 0; i < AMOUNT_OF_FLAGS; i++)
		if(strcmp(argv[num_str],FLAGS[i]) == 0)
		{
			flag_exist = true;
			return flag_exist;
		}

	return flag_exist;
}

//узнает количество столбов в строке
int amount_cols_in_string(struct Srows read_str, char *sep)
{
	read_str.amount_cols = 1;
	for(int i = 0; read_str.new_string_bufer[i] != '\0'; i++)
			if(read_str.string_bufer[i] == sep[0])
				read_str.amount_cols++;
	return read_str.amount_cols;
}

//Zjesti bunka je  čislo nebo ne
bool find_number(struct Srows work_line, int slider_n, char *sep)
{	
	bool numeric = false;
	if(work_line.string_bufer[slider_n] == sep[0])
		fprintf(stderr, "UPOZORNĚNÍ: Ve bunce ve řadku %d pro zpracovaní flagu round/int nemáte nic\n",work_line.number);

	for(;work_line.string_bufer[slider_n] != sep[0] && work_line.string_bufer[slider_n] != '\0' ; slider_n++)
	{
		if((work_line.string_bufer[slider_n] >= '0' && work_line.string_bufer[slider_n] <= '9') || (work_line.string_bufer[slider_n] == '-') || (work_line.string_bufer[slider_n] == '.'))
		{
			numeric = true;
		}
		else
		{
			numeric = false;
			fprintf(stderr, "UPOZORNĚNÍ: Ve bunce ve řadku %d pro zpracovaní flagu round/int máte(žadne čislo) ne jen čislo\n",work_line.number);
			return numeric;
		}
	}
	return numeric;
}

//výměna oddělovačů
struct Srows replaces_the_separator(struct Srows read_str, char *sep)
{	
	for(int i = 0; read_str.new_string_bufer[i] != '\0'; i++)
		for(int a = 0; sep[a] != '\0';a++)
			if(read_str.new_string_bufer[i] == sep[a])	
				read_str.new_string_bufer[i] = sep[0];
	return read_str;
}
//kontrolování argumentů
int arguments_control(int number_flag,char **argv, int argc, int start_flag)
{
	if(number_flag >= 0 && number_flag <= 12 && number_flag != 1 && number_flag != 5 
											&& number_flag != 3 && number_flag != 7 && number_flag != 8)
		{	
			if((start_flag+1) < argc && argv[start_flag+1][0] >= '1' && argv[start_flag+1][0] <= '9');


			else
			{
				fprintf(stderr, "CHYBA: Máte není správný 1 argument ve flagu'%s'\n",FLAGS[number_flag]);
				return 102;
			}
			if((start_flag+2) < argc)
			{	
				if(flags_ownership_check(start_flag+2,argv));

				else
				{
					fprintf(stderr, "CHYBA: Máte není správný 2 argument ve flagu '%s'\n",FLAGS[number_flag]);
					return 102;
				}
			}	
			return 0;	
		}
		if(number_flag == 1 || number_flag == 5)
		{
			if((start_flag+1) < argc)
				if(!(flags_ownership_check(start_flag+1,argv)))
				{
					fprintf(stderr, "CHYBA: Máte více argumentů ve flagu '%s'\n",FLAGS[number_flag]);
					return 102;
				}
			return 0;	
		}

		if(number_flag == 3 || number_flag == 7 || (number_flag >=13 && number_flag <=15))
		{
			if((start_flag+1) < argc && argv[start_flag+1][0] >= '1' && argv[start_flag+1][0] <= '9');
			
			else
			{
				fprintf(stderr, "CHYBA: Máte není správný 1 argument ve flagu '%s'\n",FLAGS[number_flag]);
				return 102;
			}
			if((start_flag+2) < argc && argv[start_flag+2][0] >= '1' && argv[start_flag+2][0] <= '9');

			else
			{
				fprintf(stderr, "CHYBA: Máte není správný 2 argument ve flagu '%s'\n",FLAGS[number_flag]);
				return 102;
			}

			if(number_flag == 3 || number_flag == 7)
			{
				if(argv[start_flag+1][0] > argv[start_flag+2][0])
				{
					fprintf(stderr, "CHYBA: Máte 1 argument > než 2 argument ve flagu '%s'\n",FLAGS[number_flag]);
					return 102;
				}
			}
		}

		if(number_flag == 8 || (number_flag >=17 && number_flag <=18))
		{
			if((start_flag+1) < argc && argv[start_flag+1][0] >= '1' && argv[start_flag+1][0] <= '9');
			
			else
			{
				fprintf(stderr, "CHYBA: Máte není správný 1 argument ve flagu '%s'\n",FLAGS[number_flag]);
				return 102;
			}
			if ((start_flag+2) < argc)
			{
				if(flags_ownership_check(start_flag+2,argv))
				{
					fprintf(stderr, "CHYBA: Máte není správný 2 argument ve flagu '%s'\n",FLAGS[number_flag]);
					return 102;
				}
				for(int i = 0; argv[start_flag+2][i] != '\0' ; i++)
				{
					if(i == 99)
					{
						fprintf(stderr,"CHYBA:Mate příliš dlouhý řádek ve flagu '%s'\n",FLAGS[number_flag]);
						return 103;
					}
				}	
			}	
			else
			{
				fprintf(stderr, "CHYBA: Máte není správný 2 argument ve flagu '%s'\n",FLAGS[number_flag]);
				return 102;
			}	
			return 0;	

		}

		if(number_flag == 16)
		{	
			if(((start_flag+1) < argc && argv[start_flag+1][0] >= '1' && argv[start_flag+1][0] <= '9') 
						|| ((start_flag+1) < argc && argv[start_flag+1][0] == '-' && argv[start_flag+2][1] == '\0'));

			
			else
			{
				fprintf(stderr, "CHYBA: Máte není správný 1 argument ve flagu %s\n",FLAGS[number_flag]);
				return 102;
			}
			if(((start_flag+2) < argc && argv[start_flag+2][0] >= '1' && argv[start_flag+2][0] <= '9') 
						|| ((start_flag+2) < argc && argv[start_flag+2][0] == '-'&& argv[start_flag+2][1] == '\0'))
			{
				if(argv[start_flag+2][0] != '-')
					if(argv[start_flag+1][0] == '-')
					{
						fprintf(stderr, "CHYBA: Máte není správný 1 argument ve flagu %s\n",FLAGS[number_flag]);
						return 102;
					}
			}

			else
			{
				fprintf(stderr, "CHYBA: Máte není správný 2 argument ve flagu %s\n",FLAGS[number_flag]);
				return 102;
			}
			return 0;
		}


return 0;

}
//kontroluji flagy
int check_flags (int start_flag, char **argv, int argc,int *quantity_flags)
{	
	bool flag_exist = false ;
	int numb_of_attempts = 2;
	int number_flag = 0; 

	for(; start_flag < argc && numb_of_attempts <= MAX_AMOUNT_OF_ARGUMENTS; start_flag++)
	{	
		flag_exist = false;
		for(number_flag = 0; number_flag < AMOUNT_OF_FLAGS; number_flag++)//kontrola je to flag nebo ne
		{	
			if(strcmp(argv[start_flag],FLAGS[number_flag]) == 0)
			{	
				flag_exist = true;
				numb_of_attempts = 0;
				(*quantity_flags)++;
				break;
			}	
		}		
		
		if(flag_exist)
		{
			if(arguments_control(number_flag,argv,argc,start_flag))
			{
				return 102;
			}
		}

		if(flag_exist == false)
		{
			numb_of_attempts++;
		}
	}
	//příliš mnoho argumentů		
	if(numb_of_attempts >= MAX_AMOUNT_OF_ARGUMENTS + 1)
	{
		return 101;
	}
	//флаг не задан 
	else if(*quantity_flags == 0) 
	{
		return 101;
	}	
	//kontrola posledniho flagu 
	if(start_flag >= argc)
	{
		return 0;
	}	

	return 0;
}
//logika rozdělení flagů a argumentú
struct Sflags loading_arguments(int *start_flag,char **argv,int argc)
{
	struct Sflags argum;
	for(int i = 0; i < AMOUNT_OF_FLAGS; i++)
		if((strcmp(argv[*start_flag],FLAGS[i]) == 0))	
			argum.number = i;

	if((*start_flag + 1) >= argc)
	{
		argum.arg1 = -1;
	    argum.arg2 = -1;
	    sprintf(argum.str,"#");
	    *start_flag = -100;
		return argum;

	}
	if(flags_ownership_check(*start_flag + 1,argv))
	{	
		argum.arg1 = -1;
	    argum.arg2 = -1;
	    sprintf(argum.str,"#");
	    *start_flag = *start_flag + 1;
		return argum;
	}else
	{ 

		if(argv[*start_flag+1][0] >= '1' && argv[*start_flag+1][0] <= '9')
		{
		
			argum.arg1 = atoi(argv[*start_flag+1]);
	   	 	argum.arg2 = -1;
	    	sprintf(argum.str,"#");
	
	    }
	    else
	    {
	    	if(argv[*start_flag+1][0] == '-')
			{	
				argum.arg1 = -2;
	   	 		argum.arg2 = -1;
	    		sprintf(argum.str,"#");
			}
	    	else
	    	{	
	    		argum.arg1 = -1;
	   	 		argum.arg2 = -1;
	    		sprintf(argum.str,"#");
	    	}

	    }	
	}
	if((*start_flag + 2) >= argc)
	{
	    *start_flag = -100;
		return argum;
	}	
	if(flags_ownership_check(*start_flag + 2,argv))
	{	
		*start_flag = *start_flag + 2;
		return argum;
	}else
	{ 	
		if(argv[*start_flag+2][0] >= '1' && argv[*start_flag+2][0] <= '9')
		{
	    	argum.arg2 = atoi(argv[*start_flag+2]);
	    	if(argum.number == 8 || argum.number == 17 || argum.number == 18)
	    	sprintf(argum.str,argv[*start_flag+2]);
		}
	    else
	    {
	    	if(argv[*start_flag+2][0] == '-' && argum.number == 16)
	    		argum.arg2 = -2;
	    	else
	    		sprintf(argum.str,argv[*start_flag+2]);
	    }
	    *start_flag = *start_flag + 3;
	}
	
	
	return argum;

}

//čte řadek
struct Srows read(char *separators, struct Srows row)
{	
	int i = 0;

	if((row.new_string_bufer[i]=getchar ()) != EOF)
	{	
		i++;
		while((row.new_string_bufer[i]=getchar ()) != '\n')
		{
			if(i >= 10240)
			{	
				row.amount_cols = -1;
				return row;
			}
			i++;
		}
		row.new_string_bufer[i] = '\0'; 
		row  = replaces_the_separator(row,separators);
	}
	else //nacházíme poslední řádek
	{
		row.new_string_bufer[0] = '\0';
	}	
	return row;
}
//vyplní řádky
struct Srows fills_lines(char *separators, int str_numb,struct Srows readed)
{
	
	if(str_numb == 1)
		readed = read(separators,readed);

	
	int a =0;

	for(; readed.new_string_bufer[a] != '\0';a++)
		readed.string_bufer[a] = readed.new_string_bufer[a];
	readed.string_bufer[a] = '\0';

	if(readed.amount_cols == -1)//
		return readed;

	if(readed.string_bufer[0] !='\0')
	{
		readed.amount_cols = amount_cols_in_string(readed, separators);
		readed.number = str_numb;
		readed.treatment = true;
		readed = read(separators,readed);
	}	
	return readed;
}

//zjesti kolik sloupců bude na konci programu
void find_output_cols_amount(int *out_cols,struct Sflags *arr_argum,int quantity_flags)
{
	for(int i = 0; i < quantity_flags; i++)
	{
		if(arr_argum[i].number == 4 || arr_argum[i].number == 5)
			(*out_cols)++;
		if(arr_argum[i].number == 6)
			(*out_cols)--;
		if(arr_argum[i].number == 7)
		{
			*out_cols = *out_cols - (arr_argum[i].arg2 - arr_argum[i].arg1 + 1);
		}
	}
}

//vyhledávání buněk
int cols_search(int nead_cell, struct Srows work_line,char *sep)
{	
	int slider = 0;
	int num_col_find = 1;
	if(nead_cell <= work_line.amount_cols)
	{
		while(num_col_find != nead_cell)
		{
			if(work_line.string_bufer[slider] == sep[0])
				num_col_find++;
			slider++;
		}
	}	
	return slider;
}

//vloží řádek tabulky před řádek
void flag_irow (char *sep,int out_cols)
{
	for(int i = 0; i < out_cols; i++)
	{
		if(i+1 != out_cols)
			printf("%c",sep[0]);
	}	

	printf("\n");

}
//přidá nový řádek tabulky na konec tabulky
void flag_arow(char *sep,int out_cols)
{
	for(int i = 0; i < out_cols; i++)
	{
		if(i+1 != out_cols)
			printf("%c",sep[0]);
	}	

	printf("\n");

}
//dodává prazdný sloupec před sloupcem
struct Srows flag_icol (struct Srows work_line,char *sep, int num_cols)
{	
	int num_col_find = 1;
	int len = strlen(work_line.string_bufer);
	char copy_str[len+1];
	int slider = 0;
	strncpy(copy_str, work_line.string_bufer,sizeof(copy_str) - 1);
	copy_str[sizeof(copy_str) - 1] = '\0';
	
	for(; work_line.string_bufer[slider] != '\0'; slider++)
	{
		if((num_cols != 1) && (work_line.string_bufer[slider] == sep[0]))
			num_col_find++;
		if(num_col_find == num_cols)
		{	
			if(num_cols == 1) 
			{
				slider = 0;
				work_line.string_bufer[slider] = sep[0];
				num_col_find++;
			}else
			{
				work_line.string_bufer[slider+1] = sep[0];
				num_col_find++;
			}
			
			break;
		}
	}

	for(; slider < (len+1);slider++)
	{
		work_line.string_bufer[slider+1] = copy_str[slider];
	}
	return work_line;

}
//přidá prázdný sloupec za poslední sloupec.
struct Srows flag_acol(struct Srows work_line,char *sep)
{
	int slider = 0;
	while(work_line.string_bufer[slider] != '\0')
		slider++;
	work_line.string_bufer[slider] = sep[0];
	work_line.string_bufer[slider+1] = '\0';
	return work_line;
}
//odstraní sloupec / sloupcy
struct Srows flag_dcol_s(struct Srows work_line,char *sep, int num_cols, int num_cols_2)
{	

	int slider = 0;
	int slider_2 = 0;
	int num_col_find = 1;

	
	while(num_col_find != num_cols)
	{
		if(work_line.string_bufer[slider] == sep[0])
			num_col_find++;
		slider++;

	}

	slider_2 = slider;
	if(num_cols_2 != -1) //zjesti dcol nebo dcols
	{	
		while(num_col_find != num_cols_2 + 1 && work_line.string_bufer[slider_2] != '\0')
		{
			if(work_line.string_bufer[slider_2] == sep[0])
				num_col_find++;
			slider_2++;
		}
	}
	else 
	{
		while(work_line.string_bufer[slider_2] != sep[0] && work_line.string_bufer[slider_2] != '\0')
			slider_2++;
		if(work_line.string_bufer[slider_2] != '\0')
		slider_2++;
	}

	if(work_line.string_bufer[slider_2] == '\0')
	{	
		if(num_cols == 1)
			slider ++;
		work_line.string_bufer[slider-1] = '\0';
	}
	else
	{	
		for(;work_line.string_bufer[slider_2]!= '\0'; slider_2++)
		{	
			work_line.string_bufer[slider] = work_line.string_bufer[slider_2];
			slider++;
		}
		work_line.string_bufer[slider] ='\0';
	}	
	return work_line; 
}
//zjesti jaky řadky budeme upravovat(např od 1 do 3)
struct Srows flag_rows (struct Srows work_line,int number_str1,int number_str2)
{	

	work_line.treatment = false;


	if(number_str1 == -2 && number_str2 == -2 && work_line.new_string_bufer[0] == '\0')
	{
		work_line.treatment = true;
		return work_line;
	}


	if(number_str2 == -2 && number_str1 != -2)
	{	
		if(work_line.number >= number_str1)
			work_line.treatment = true;
		return work_line;
	}	

	if(number_str1 <= work_line.number && number_str2 >= work_line.number && number_str1 > 0 && number_str2 > 0)
	{
		work_line.treatment = true;
		return work_line;
	}
	
	return work_line;
}
//zjesti jaky řadky budeme upravovat, tě řadky ve kterých obsah buňky ve sloupci začíná řetězcem 
struct Srows flag_beginswith(struct Srows work_line, struct Sflags *arr_argum, int number_argum_in_arr, char *sep)
{
	work_line.treatment = false;
	int slider = 0;
	int slider_2 = 0;
	
	slider = cols_search(arr_argum[number_argum_in_arr].arg1,work_line,sep);

	while (arr_argum[number_argum_in_arr].str[slider_2] != '\0')
	{
		if(arr_argum[number_argum_in_arr].str[slider_2] == work_line.string_bufer[slider])
		{
			slider_2++;
			slider++;
		}
		else
		{
			return work_line;
		}
	}
	work_line.treatment = true;
	return work_line;
}
//zjesti jaky řadky budeme upravovat, tě řadky buňky kterých obsah obsahují řetězec 
struct Srows flag_contains(struct Srows work_line, struct Sflags *arr_argum, int number_argum_in_arr, char *sep)
{
	work_line.treatment = false;
	int slider = 0;
	int slider_2 = 0;
	

	slider = cols_search(arr_argum[number_argum_in_arr].arg1,work_line,sep);	

	while (arr_argum[number_argum_in_arr].str[slider_2] != '\0')
	{	
		if(work_line.string_bufer[slider] == sep[0] || work_line.string_bufer[slider] == '\0')
			return work_line;
		if(arr_argum[number_argum_in_arr].str[slider_2] == work_line.string_bufer[slider])
		{
			slider_2++;
			slider++;
		}
		else
		{	
			slider_2 = 0;

			if(arr_argum[number_argum_in_arr].str[slider_2] == work_line.string_bufer[slider])
			{
				slider_2++;
				slider++;
			}
			else
			{
				slider++;
			}
		}
	}

	work_line.treatment = true;
	return work_line;
}
//do buňky ve sloupci bude nastaven řetězec
struct Srows flag_cset(struct Srows work_line, struct Sflags *arr_argum, int number_argum_in_arr, char *sep)
{
	int slider = 0;
	int slider_2 = 0;
	int len = strlen(work_line.string_bufer); 
	char copy_str[len+1];

	strncpy(copy_str, work_line.string_bufer,sizeof(copy_str) - 1);
	copy_str[sizeof(copy_str) - 1] = '\0';


	slider = cols_search(arr_argum[number_argum_in_arr].arg1,work_line,sep);

	//slider_2 = slider;
	slider_2 = (cols_search(arr_argum[number_argum_in_arr].arg1+1,work_line,sep) -1);

	for(int a = 0; arr_argum[number_argum_in_arr].str[a] != '\0';a++)
	{
		work_line.string_bufer[slider] = arr_argum[number_argum_in_arr].str[a];
		slider++;
	}

	for(; slider_2 <(len+1) ;slider_2++)
	{
		work_line.string_bufer[slider] = copy_str[slider_2];
		slider++;
	}
	work_line.string_bufer[slider] = '\0';
	return work_line;
}
// řetězec ve sloupci bude převeden na malá písmena
struct Srows flag_tolower(struct Srows work_line, int number_cols, char *sep)
{	
	int slider = 0;
	slider = cols_search(number_cols,work_line,sep);

	for(; work_line.string_bufer[slider] != sep[0]; slider++)
		if(work_line.string_bufer[slider] >= 65 && work_line.string_bufer[slider] <= 90)
			work_line.string_bufer[slider] = work_line.string_bufer[slider] + 32;

	return work_line;	

}
//řetězec ve sloupce bude převeden na velká písmena
struct Srows flag_toupper(struct Srows work_line, int number_cols, char *sep)
{
	int slider = 0;
	slider = cols_search(number_cols,work_line,sep);

	for(; work_line.string_bufer[slider] != sep[0]; slider++)
		if(work_line.string_bufer[slider] >= 97 && work_line.string_bufer[slider] <= 122)
			work_line.string_bufer[slider] = work_line.string_bufer[slider] - 32;

	return work_line;	
}
//ve sloupci zaokrouhlí číslo na celé číslo
struct Srows flag_round(struct Srows work_line, int number_cols, char *sep)
{
	int num = 0;
	float num1 =0.0;
	char number[100];
	int slider = 0;
	int slider_2 = 0;
	int slider_3 = 0;

	slider = cols_search(number_cols,work_line,sep);
	slider_3 = slider;

	if(find_number(work_line, slider, sep))
	{	

		for(;work_line.string_bufer[slider] != sep[0] && work_line.string_bufer[slider] != '\0' ; slider++)
		{	
			
			number[slider_2] = work_line.string_bufer[slider];
			slider_2++;
		}
		number[slider_2] = '\0';

		num1 = atof(number);
		
		if(num1 >= 0)
			num = (int)(num1+0.5);
		else
			num = (int)(num1-0.5);
		
	
		sprintf(number, "%d", num);

		for(int i = 0; number[i] != '\0';i++)
		{
			work_line.string_bufer[slider_3] = number[i];
			slider_3++;
		}	

		if(work_line.string_bufer[slider] != '\0')
		{	
			for(;work_line.string_bufer[slider] != '\0' ; slider++)
			{
				work_line.string_bufer[slider_3] = work_line.string_bufer[slider];
				slider_3++;
			}
		}
		work_line.string_bufer[slider_3] = '\0';
	}
	return work_line;
}
//odstraní desetinnou část čísla ve sloupci
struct Srows flag_int(struct Srows work_line, int number_cols, char *sep)
{	
	int slider = 0;
	int slider_2 = 0;
	
	slider = cols_search(number_cols,work_line,sep);

	if(find_number(work_line, slider, sep))
	{

		for(;work_line.string_bufer[slider] != sep[0] && work_line.string_bufer[slider] != '.' && work_line.string_bufer[slider] != '\0' ; slider++ );
	
		if(work_line.string_bufer[slider] == '.') 
		{	
			slider_2 = slider;
			for(;work_line.string_bufer[slider] != sep[0] &&  work_line.string_bufer[slider] != '\0' ; slider++ );
			for(;work_line.string_bufer[slider] != '\0';slider++)
			{
				work_line.string_bufer[slider_2] = work_line.string_bufer[slider];
				slider_2++;
			}
			work_line.string_bufer[slider_2] ='\0';
	}
	}
	return work_line;
}
//přepíše obsah buněk ve sloupci M hodnotami ze sloupce N
struct Srows flag_copy(struct Srows work_line, struct Sflags *arr_argum, int number_argum_in_arr, char *sep)
{
	int slider = 0;
	int slider_2 = 0;
	int slider_3 = 0;

	int len = strlen(work_line.string_bufer);
	char copy_str[len+1];

	strncpy(copy_str, work_line.string_bufer,sizeof(copy_str) - 1); 
	copy_str[sizeof(copy_str) - 1] = '\0';

	slider = cols_search(arr_argum[number_argum_in_arr].arg1,work_line,sep);

	slider_2 = cols_search(arr_argum[number_argum_in_arr].arg2,work_line,sep);

	if(arr_argum[number_argum_in_arr].arg2 == work_line.amount_cols)
		slider_3 = -1;
	else 
		slider_3 = (cols_search((arr_argum[number_argum_in_arr].arg2+1),work_line,sep) -1);

	for(; work_line.string_bufer[slider] != sep[0] &&  work_line.string_bufer[slider] != '\0'; slider++)
	{

		work_line.string_bufer[slider_2] = work_line.string_bufer[slider];
		slider_2++;
	}
	if(slider_3 != -1) 
	{
		for(;copy_str[slider_3] != '\0'; slider_3++)
		{
			work_line.string_bufer[slider_2] = copy_str[slider_3];
			slider_2++;
		}
	}
	work_line.string_bufer[slider_2] = '\0';

	return work_line;

}
//zamění hodnoty buněk ve sloupcích N a M
struct Srows flag_swap(struct Srows work_line, struct Sflags *arr_argum, int number_argum_in_arr, char *sep)
{
	int slider = 0;
	int slider_2 = 0;
	int arg1 = arr_argum[number_argum_in_arr].arg1;
	int arg2 = arr_argum[number_argum_in_arr].arg2;
	struct Srows copy_line = work_line;
	
	if(arr_argum[number_argum_in_arr].arg1 < arr_argum[number_argum_in_arr].arg2) 
	{
		arr_argum[number_argum_in_arr].arg1 = arg2;
		arr_argum[number_argum_in_arr].arg2 = arg1;
	}

	slider_2 = cols_search(arr_argum[number_argum_in_arr].arg2,copy_line,sep);

	work_line = flag_copy(work_line,arr_argum, number_argum_in_arr,sep);

	slider = cols_search(arr_argum[number_argum_in_arr].arg1,work_line,sep);
	
	int delit_last_cols = arr_argum[number_argum_in_arr].arg1;
	int delit_first_cols = arr_argum[number_argum_in_arr].arg2 + 1;

	copy_line = flag_dcol_s(copy_line,sep, delit_first_cols, delit_last_cols);


	for(;copy_line.string_bufer[slider_2] !='\0';slider_2++)
	{
		work_line.string_bufer[slider] = copy_line.string_bufer[slider_2];
		slider++;
	}
	work_line.string_bufer[slider] = '\0';

	arr_argum[number_argum_in_arr].arg1 = arg1;
	arr_argum[number_argum_in_arr].arg2 = arg2;

	return work_line;
}
//přesune sloupec N před sloupec M
struct Srows flag_move(struct Srows work_line, struct Sflags *arr_argum, int number_argum_in_arr, char *sep)
{

	int arg1 = arr_argum[number_argum_in_arr].arg1;
	int arg2 = arr_argum[number_argum_in_arr].arg2;

	if(arr_argum[number_argum_in_arr].arg2 > arr_argum[number_argum_in_arr].arg1)
	{	 
		int quantity = (arr_argum[number_argum_in_arr].arg2 - arr_argum[number_argum_in_arr].arg1) -1;

		for(int  a = 0; a< quantity; a++)
		{	
			arr_argum[number_argum_in_arr].arg1 = arg1 + a;
			arr_argum[number_argum_in_arr].arg2 = arg2 - quantity + a;

			work_line = flag_swap(work_line,arr_argum,number_argum_in_arr,sep);
		}

		arr_argum[number_argum_in_arr].arg1 = arg1;
		arr_argum[number_argum_in_arr].arg2 = arg2;
		return work_line;
	}
	if(arr_argum[number_argum_in_arr].arg2 < arr_argum[number_argum_in_arr].arg1)
	{	
		int quantity = arr_argum[number_argum_in_arr].arg1 - arr_argum[number_argum_in_arr].arg2;

		for(int  a = 0; a < quantity; a++)
		{	
			arr_argum[number_argum_in_arr].arg1 = arg1 - a;
			arr_argum[number_argum_in_arr].arg2 = arg1 - (1 + a);

			work_line = flag_swap(work_line,arr_argum,number_argum_in_arr,sep);
		}

		arr_argum[number_argum_in_arr].arg1 = arg1;
		arr_argum[number_argum_in_arr].arg2 = arg2;
		return work_line;
	}

	arr_argum[number_argum_in_arr].arg1 = arg1;
	arr_argum[number_argum_in_arr].arg2 = arg2;
	return work_line;
}
//výstup do dokumentu
int out(struct Srows work_line)
{
	if(work_line.string_bufer[0] != '\0')
		printf("%s\n",work_line.string_bufer);
	return 0;
}

int distributor(struct Sflags *arr_argum, int quantity_flags, struct Srows working_line, int out_cols, char *separators)
{	

	for(int i = 0; i < quantity_flags; i++)
	{	
		switch(arr_argum[i].number)
		{
			//irow
			case 0:
			if (working_line.number == arr_argum[i].arg1 && working_line.string_bufer[0] != '\0')
				flag_irow(separators,out_cols);
			break;

			//arow
			case 1:
			if(working_line.string_bufer[0] == '\0')
				flag_arow(separators,out_cols);
			break;

			//drow
			case 2:
			if(working_line.number == arr_argum[i].arg1)
				return 0;
			break;

			//drows
			case 3:
			if(working_line.number >= arr_argum[i].arg1 && working_line.number <= arr_argum[i].arg2)
				return 0;
			break;

			//icol
			case 4:
			if (arr_argum[i].arg1 > 0 && arr_argum[i].arg1 <= working_line.amount_cols)
			{	
				int num_cols = arr_argum[i].arg1;
				working_line = flag_icol(working_line,separators,num_cols);
			}
			break;

			//acols
			case 5:
			if(working_line.string_bufer[0] != '\0')
				working_line = flag_acol(working_line,separators); 
			break;

			//dcol
			case 6:
			if (arr_argum[i].arg1 > 0 && arr_argum[i].arg2 == -1 && arr_argum[i].arg1 <= working_line.amount_cols 
																				&& working_line.string_bufer[0] != '\0')
			{
				int num_cols = arr_argum[i].arg1;
				int num_cols_2 = arr_argum[i].arg2;
				working_line = flag_dcol_s(working_line,separators,num_cols,num_cols_2);
			}
			break;

			//dcols
			case 7:
			if(arr_argum[i].arg1 <= arr_argum[i].arg2 && arr_argum[i].arg1 > 0 && arr_argum[i].arg2 > 0 
				&& arr_argum[i].arg1 <= working_line.amount_cols && arr_argum[i].arg2 <= working_line.amount_cols 
																				&& working_line.string_bufer[0] != '\0')
			{
				int num_cols = arr_argum[i].arg1;
				int num_cols_2 = arr_argum[i].arg2;
				working_line = flag_dcol_s(working_line,separators,num_cols,num_cols_2);
			}
			break;

			//rows
			case 16:
			if((arr_argum[i].arg1 <= arr_argum[i].arg2 && working_line.string_bufer[0] != '\0') || (arr_argum[i].arg2 == -2 && working_line.string_bufer[0] != '\0'))
			{	
				int number_str1 = arr_argum[i].arg1;
				int number_str2 = arr_argum[i].arg2;
				working_line = flag_rows(working_line,number_str1,number_str2);
			}
			else
			{
				working_line.treatment = false;
			}
			break;

			//beginswith
			case 17:
			if(arr_argum[i].arg1 <= working_line.amount_cols && working_line.string_bufer[0] != '\0')
				working_line = flag_beginswith(working_line,arr_argum,i,separators);
			else
			{
				working_line.treatment = false;
			}
			break;

			//contains
			case 18:
			if(arr_argum[i].arg1 <= working_line.amount_cols && working_line.string_bufer[0] != '\0')
				working_line = flag_contains(working_line,arr_argum,i,separators);
			else
			{
				working_line.treatment = false;
			}
			break;

			//cset
			case 8:
			if(arr_argum[i].arg1 > 0 && arr_argum[i].str[0] != '#' &&  working_line.treatment 
									&& arr_argum[i].arg1 <= working_line.amount_cols && working_line.string_bufer[0] != '\0')
				working_line = flag_cset(working_line,arr_argum,i,separators);
			break;

			//tolower
			case 9:
			if(arr_argum[i].arg1 > 0 && arr_argum[i].arg1 <= working_line.amount_cols && working_line.treatment 
																						&& working_line.string_bufer[0] != '\0')
			{
				int number_col = arr_argum[i].arg1;
				working_line = flag_tolower(working_line,number_col,separators);
			}
			break;

			//toupper
			case 10:
			if(arr_argum[i].arg1 > 0 && arr_argum[i].arg1 <= working_line.amount_cols 
											&& working_line.treatment && working_line.string_bufer[0] != '\0')
			{
				int number_col = arr_argum[i].arg1;
				working_line = flag_toupper(working_line,number_col,separators);
			}
			break;

			//round
			case 11:
			if(arr_argum[i].arg1 > 0 && arr_argum[i].arg1 <= working_line.amount_cols && 
													working_line.treatment && working_line.string_bufer[0] != '\0')	
			{
				int number_col = arr_argum[i].arg1;
				working_line = flag_round(working_line,number_col,separators);
			}
			break;

			//int
			case 12:
			if(arr_argum[i].arg1 > 0 && arr_argum[i].arg1 <= working_line.amount_cols && 
														working_line.treatment && working_line.string_bufer[0] != '\0')
			{
				int number_col = arr_argum[i].arg1;
				working_line = flag_int(working_line,number_col,separators);
			}
			break;

			//copy
			case 13:
			if(working_line.treatment && working_line.string_bufer[0] != '\0' && arr_argum[i].arg1 > 0 && arr_argum[i].arg2 > 0 
								&& arr_argum[i].arg1 <= working_line.amount_cols && arr_argum[i].arg2 <= working_line.amount_cols)
				working_line = flag_copy(working_line,arr_argum,i,separators);
			break;

			//swap
			case 14:
			if(working_line.treatment && working_line.string_bufer[0] != '\0' && arr_argum[i].arg1 > 0 && arr_argum[i].arg2 > 0 
								&& arr_argum[i].arg1 <= working_line.amount_cols && arr_argum[i].arg2 <= working_line.amount_cols)
				working_line = flag_swap(working_line,arr_argum,i,separators);
			break;

			//move
			case 15:
			if(working_line.treatment && working_line.string_bufer[0] != '\0' && arr_argum[i].arg1 > 0 && arr_argum[i].arg2 > 0 
								&& arr_argum[i].arg1 <= working_line.amount_cols && arr_argum[i].arg2 <= working_line.amount_cols)
				working_line = flag_move(working_line,arr_argum,i,separators);
			break;


		}

	}
	out(working_line);

	return 0;
} 



int main(int argc, char  **argv)
{	
	setlocale(LC_ALL,"Cz");

	int output_cols = 0;
	int string_number = 1;
	int amount_flags = 0;
	int amount_separators = 0; 
	int start_number_flags = 0;
	struct Srows readed_row;
	int err = 0;

	//kontrola počtu argumentů
	if(argc == 1)
	{	
		fprintf(stderr, "CHYBA: Zadny argument\n");
		return 105;
	}

	//Nachození maximálního počtu rozdělovačů a vytvoření řetězce
	if(finde_quantity_of_separate(&amount_separators,argv,argc))
	{
		fprintf(stderr, "CHYBA: Nespravne zadane udaje v retezce delim\n");
		return 104;
	} 
	char separators[amount_separators];

	//Volání funkce zaplnění řetězce rozdělovačů
	writes_separators(argv,amount_separators, separators, &start_number_flags);


	//Kontrola argumentu(flag)
	if((err = check_flags(start_number_flags, argv, argc, &amount_flags)))
	{	
		if(err == 101)
		{
			fprintf(stderr, "CHÝBA: Nespravně zadane udaje\n");
			return 101;
		}
		else if(err == 102)
			return 102;
		else if(err == 103)
			return 103;
		else 
			return 111;
	}

	//Vytvoření řetězce a zaplnění řetězce argumenty
	struct Sflags arr_arguments[amount_flags];
	for(int slider = 0; slider < amount_flags && start_number_flags < argc && start_number_flags != -100; slider++)
		arr_arguments[slider] = loading_arguments(&start_number_flags,argv,argc);
	

	do
	{	
		readed_row = fills_lines(separators,string_number,readed_row);
		if(readed_row.amount_cols == -1)
		{
			fprintf(stderr,"CHYBA:Mate prilis dlouhy radek\n");
			return 103;
		}

		//Zjištění počtu sloupců
		if(string_number == 1)
		{	
			if(readed_row.string_bufer[0] == '\0')
			{
				fprintf(stderr, "CHYBA: Prazdny sobor\n");
				return 106;
			}
			output_cols = readed_row.amount_cols;
			find_output_cols_amount(&output_cols, arr_arguments, amount_flags);
		}
		distributor(arr_arguments, amount_flags, readed_row,output_cols,separators);
		string_number ++;

	}while(readed_row.string_bufer[0] != '\0');

	return 0;
}
