
/**
  * Soubor:   sps.c
  * Predmet:  IZP 2020/21
  * Autor:    Vladslav Mikheda Login:xmikhe00
  * Pojekt:   čislo 2: Práce s datovými strukturami
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

#define ERRARG 5//error argument
#define ERRARC 12 //chyba zadovani argumentu v argv
#define ERRALLOC 13 // chyba allokacii
#define ERROPEN 15 // chyba otevreni a prace s souboru

#define SEL 2 //oddelovac + '\0'
#define TA 3 //zmnena typu argumentu pro dalsi zpracovani
#define NS -3 //nenastaveno
#define WSB 2 // kde se nachazi hranata zavorka od konca retezce
#define WSEM 1 //kde se nachazi strednik od konca retezce
#define SB 1 //square bracket //hranata zavorka
#define SEMIL 2 // strednik
#define EL 1 //endline
#define AMOUNT_SAVES 10
#define FA 1 // fallback argument

const char *const FLAGS[]= {"irow;","arow;","drow;","icol;","acol;","dcol;","clear;","set","swap","sum","avg","count","len","def","use","inc","[set];"};
//počet flagu
const int AMOUNT_OF_FLAGS =(sizeof(FLAGS)/sizeof(FLAGS[0]));

//všechny flagi který máme
const char *const SAVE_ARGUMENTS[]= {"_0;","_1;","_2;","_3;","_4;","_5;","_6;","_7;","_8;","_9;"};
//počet flagu
const int AMOUNT_OF_SAVE_ARGUMENTS =(sizeof(SAVE_ARGUMENTS)/sizeof(SAVE_ARGUMENTS[0]));

//všechny flagi který máme
const char *const MIN_MAX_ARGUMENTS[]= {"[min];","[max];","[_];"};
//počet flagu
const int AMOUNT_OF_MIN_MAX_ARGUMENTS =(sizeof(MIN_MAX_ARGUMENTS)/sizeof(MIN_MAX_ARGUMENTS[0]));

const char *const SELECTORS[] ={"[find","[max];","[min];","[_];"};

const int AMOUNT_SELECTORS = (sizeof(SELECTORS)/sizeof(SELECTORS[0]));


//maximální počet argumentů po flagu
const int MAX_AMOUNT_OF_ARGUMENTS = 2;

typedef struct 
{
	double num_content_cell;
	char *text_content_cell;
	char number;

}t_save;

typedef struct 
{	
	int amount_saves;
	t_save save[AMOUNT_SAVES];

} t_save_list;

typedef struct
{	
	int type;
	int row_1;
	int col_1;
	int row_2;
	int col_2;

}t_save_set;

typedef struct 
{
	int row;
	int col;
	char *string;

} t_cell_number;

typedef struct 
{	
	int type;
	int row_1;
	int col_1;
	int row_2;
	int col_2;
	char *str;

} t_selected_cell_number;

typedef struct 
{
	int argum;
	t_cell_number cell_of_argum;
	int save_number;

} t_argum;

typedef struct 
{
	t_selected_cell_number selected_cell; 
	t_argum *flags; // flags
	int amount_flags;

}t_arguments;

typedef struct 
{	
	int amount;
	char **arr;
}t_stdin_arg;

typedef struct Scell
{
	int number;
	char *content; 
	bool text;
}t_cell;

typedef struct Srow
{	
	int number_row;
	int amount_cell;	
	t_cell *rows_of_cell; 
}t_row;

typedef struct Stable
{	
	int amount_rows;
	t_row *col_of_rows;
}t_table;


bool open_quoates(bool quotes)
{
	if(!quotes)
		return quotes = true;
	if(quotes)
		return quotes = false;

return quotes;	

}

/*
	Zjesti kolik je argumentu na vstupe argv
	vystup pocet argumentu 
*/
int check_amount_arguments(char **argv,int start_number_flags, int amount_arguments)
{
	bool quotes = false;
	for(int slider = 0;argv[start_number_flags][slider] != '\0';slider++)
	{
		if(argv[start_number_flags][slider] == '"')
		{	
			quotes = open_quoates(quotes);

		}
		if((argv[start_number_flags][slider] == ';' || argv[start_number_flags][slider] == ' ') && !(quotes))
			amount_arguments++;
	}

	return amount_arguments;		
}	

/*
	Zjesti kolik je symbolu v jednotlivem argumentu
	vystup pocet symbolu v argumentu 
*/
int consider_amount_symbols_in_arguments(char **argv,int start_number_flags, int *slider)
{
	bool quotes = false;
	int amount_symbols_in_arguments = 0;

	for(;argv[start_number_flags][*slider] != '\0'; (*slider)++)
	{
		if(argv[start_number_flags][*slider] == '"')
		{	
			quotes = open_quoates(quotes);
		}

		if((argv[start_number_flags][*slider] == ' ') && !(quotes))
		{	
			(*slider)++;
			amount_symbols_in_arguments++;
			return amount_symbols_in_arguments + EL + SEMIL;
		}
		else if((argv[start_number_flags][*slider] == ';') && !(quotes))
		{
			(*slider)++;
			amount_symbols_in_arguments++;
			return amount_symbols_in_arguments + EL + SEMIL;
		}
		else
		{
			amount_symbols_in_arguments++;
		}
		
	}

	return amount_symbols_in_arguments + EL + SEMIL;
}

/*
	Nastovi retezec pro argumenty na vychozi hodnatu
*/
void set_default_std_in_arg(t_stdin_arg *std)
{
	std->amount = 0;
	std->arr = NULL;

}

/*
	Allocije prvni cast 2d pole pro argumenty
*/
int allocation_part_arr_arguments_stdin(int amount_arguments,t_stdin_arg *help_struct) //переименовать
{
	help_struct->arr = (char**) malloc((amount_arguments) * sizeof(char*));
    if(help_struct->arr == NULL)
	{
		free(help_struct->arr);
		help_struct->arr = NULL;
		return ERRALLOC;
	}

	return 0;
}
/*
	Deallokacia retezce pro arguenty
*/
void deallocation_argum_stdin(int amount_arguments, t_stdin_arg *arguments_stdin)
{
	if(arguments_stdin->arr != NULL)
	{
		for(int i = 0; i < amount_arguments; i++)
			free(arguments_stdin->arr[i]);
		free(arguments_stdin->arr);
		arguments_stdin->arr = NULL;
	}	
}

/*
	Allocije posledni cast 2d pole pro argumenty
*/
int allocation_full_arr_arguments(int amount_simbols_in_arguments, t_stdin_arg *help_struct, int number_argument)//переименовать
{
	help_struct->arr[number_argument] = (char* ) malloc(amount_simbols_in_arguments  * sizeof(char));
	
	if(help_struct->arr[number_argument] == NULL)
	{
		deallocation_argum_stdin(number_argument, help_struct);
		help_struct->arr = NULL;
		return ERRALLOC;
	}

	return 0;
}

/*
	Vola funkci pro allokovani celeho 2d pole
*/
int full_alacation(char **argv, int start_number_flags, t_stdin_arg *help_struct)
{	

	int slider = 0;
	int amount_arguments = 1;
	int amount_symbols_in_arguments = 0;
	amount_arguments = check_amount_arguments(argv,start_number_flags,amount_arguments);

	if(allocation_part_arr_arguments_stdin(amount_arguments, help_struct) == ERRALLOC)
		return ERRALLOC;

	for(int i = 0; i < amount_arguments;i++)
	{
		amount_symbols_in_arguments = consider_amount_symbols_in_arguments(argv,start_number_flags,&slider);
		if(allocation_full_arr_arguments(amount_symbols_in_arguments, help_struct,i) == ERRALLOC)
			return ERRALLOC;
	}

	help_struct->amount = amount_arguments;
	return 0;
}

/*
	Vypylni 2d pole  argumenty z argv
*/
int filling_arr_arguments_argv(char **argv, int start_number_flags,t_stdin_arg *help_struct)
{	
	bool quotes = false;
	int a = 0;
	int i = 0;

	set_default_std_in_arg(help_struct);

	if(full_alacation(argv, start_number_flags, help_struct) == ERRALLOC)
		return ERRALLOC;

	for(int slider = 0 ;argv[start_number_flags][slider] != '\0';slider++)
	{
		if(argv[start_number_flags][slider] == '"')
		{	
			quotes = open_quoates(quotes);
		}

		if((argv[start_number_flags][slider] == ' ') && !(quotes))
		{	
			help_struct->arr[i][a] = '\0';
			i++;
			a = 0;
		}
		else if((argv[start_number_flags][slider] == ';') && !(quotes))
		{
			help_struct->arr[i][a] = argv[start_number_flags][slider];
			a++;
			help_struct->arr[i][a] = '\0';
			i++;
			a = 0;
		}
		else
		{
			help_struct->arr[i][a] = argv[start_number_flags][slider];	
			a++;
		}
	}
	help_struct->arr[i][a] = ';';
	help_struct->arr[i][a+1] = '\0';


	return 0;
}


/*
	kontrola flagu
	vystup true nebo false
*/
bool flags_ownership_check(int num_argum, t_stdin_arg *arguments, int *flag_number)
{	
	bool flag_exist = false;
	for(*flag_number = 0; *flag_number < AMOUNT_OF_FLAGS; (*flag_number)++)
		if(strcmp(arguments->arr[num_argum],FLAGS[*flag_number]) == 0)
		{
			flag_exist = true;
			return flag_exist;
		}

	return flag_exist;
}

/*
	kontrola argumenu save argumentu _X
	vystup true nebo false
*/
bool save_arguments_ownership_check(int num_argum, t_stdin_arg *arguments)
{	
	bool argum_exist = false;
	for(int argum_number = 0; argum_number < AMOUNT_OF_SAVE_ARGUMENTS; argum_number++)
		if(strcmp(arguments->arr[num_argum],SAVE_ARGUMENTS[argum_number]) == 0)
		{
			argum_exist = true;
			return argum_exist;
		}

	return argum_exist;
}

/*
	kontrola argumenu [x,y]
	vystup true nebo false
*/
bool check_two_arguments_cell(t_stdin_arg *arguments_stdin, int argument_number)
{	
	int comma = 0;
	int amount_comma = 0;
	int amount_symbols = 0;

	for(;arguments_stdin->arr[argument_number][amount_symbols] != '\0'; amount_symbols++)
		if(arguments_stdin->arr[argument_number][amount_symbols] == ',')
			amount_comma++;

	if(amount_comma != 1)
		return false;

	if(amount_symbols < 6)
		return false;


	for(int i = 0; arguments_stdin->arr[argument_number][i] != '\0'; i++)
	{
		if(i == 0)
			if(arguments_stdin->arr[argument_number][i] != '[')
				return false;


		if(i == 1)
		{
			if(arguments_stdin->arr[argument_number][i] == '_')
			{
				if(arguments_stdin->arr[argument_number][i+1] != ',')
					return false;
			}

			else if(arguments_stdin->arr[argument_number][i] >= '1' && arguments_stdin->arr[argument_number][i] <= '9');
			else
				return false;
		}

		if(i > 1 && i < amount_symbols - WSB)
		{	
			if(arguments_stdin->arr[argument_number][i] == ',')
			{
				comma++;

				if(comma == 1)
				{
					if(arguments_stdin->arr[argument_number][i+1] == '_')
					{
						if(arguments_stdin->arr[argument_number][i+2] != ']')
							return false;
					}
					else if(arguments_stdin->arr[argument_number][i+1] >= '1' &&
											 arguments_stdin->arr[argument_number][i+1] <= '9');
					else
						return false;
				}
				
				if(comma == 2)
					return false;	
			}		

			else if(arguments_stdin->arr[argument_number][i] == '_')
			{
				if(arguments_stdin->arr[argument_number][i+1] != ']')
					return false;

				if(arguments_stdin->arr[argument_number][i-1] != ',')
					return false;
			}

			else if(arguments_stdin->arr[argument_number][i] >= '0' && arguments_stdin->arr[argument_number][i] <= '9');
			
			else
				return false;
		}

		if(i == amount_symbols - WSB) 
			if(arguments_stdin->arr[argument_number][i] != ']')
				return false;

		if(i == amount_symbols - WSEM) 
			if(arguments_stdin->arr[argument_number][i] != ';')
				return false;

	}
	
	return true;
}

/*
	kontrola argumenu [x,y,z,c]
	vystup true nebo false
*/
bool check_four_arguments_cell(t_stdin_arg *arguments_stdin, int argument_number)
{
	int amount_comma = 0;
	int comma = 0; 
	int amount_symbols = 0;

	for(;arguments_stdin->arr[argument_number][amount_symbols] != '\0'; amount_symbols++)
		if(arguments_stdin->arr[argument_number][amount_symbols] == ',')
			amount_comma++;

	if(amount_comma != 3)
		return false;
	

	if(amount_symbols < 10)
		return false;
	

	for(int i = 0; arguments_stdin->arr[argument_number][i] != '\0'; i++)
	{
		if(i == 0)
			if(arguments_stdin->arr[argument_number][i] != '[')
				return false;
				

		if(i == 1)
		{
			if(arguments_stdin->arr[argument_number][i] >= '1' && arguments_stdin->arr[argument_number][i] <= '9');
			else
				return false;
		}

		if(i > 1 && i < amount_symbols - 2)
		{	
			if(arguments_stdin->arr[argument_number][i] == ',')
			{	
				comma++; 

				if(comma == 1)
				{
					if(arguments_stdin->arr[argument_number][i+1] >= '1' && arguments_stdin->arr[argument_number][i+1] <= '9');
					else
						return false;
				}

				else if(comma == 2)
				{
					if(arguments_stdin->arr[argument_number][i+1] == '-')
					{
						if(arguments_stdin->arr[argument_number][i+2] != ',')
							return false;
					}

					else if(arguments_stdin->arr[argument_number][i+1] >= '1' &&
											 arguments_stdin->arr[argument_number][i+1] <= '9');
					else
						return false;	
				}

				else if(comma == 3)
				{
					if(arguments_stdin->arr[argument_number][i+1] == '-')
					{	
						if(arguments_stdin->arr[argument_number][i+2] != ']')
							return false;
					}

					else if(arguments_stdin->arr[argument_number][i+1] >= '1' &&
											 arguments_stdin->arr[argument_number][i+1] <= '9');
					else
						return false;	
				}

				else if(comma == 4)
					return false;
					
			}

			else if(arguments_stdin->arr[argument_number][i] == '-')
			{
				if(arguments_stdin->arr[argument_number][i-1] != ',')
					return false;

				if(arguments_stdin->arr[argument_number][i+1] != ',' && arguments_stdin->arr[argument_number][i+1] != ']')
					return false;
			}

			else if(arguments_stdin->arr[argument_number][i] >= '0' && arguments_stdin->arr[argument_number][i] <= '9');
			
			else
				return false;
		}

		if(i == amount_symbols - WSB) 
			if(arguments_stdin->arr[argument_number][i] != ']')
				return false;

		if(i == amount_symbols - WSEM) 
			if(arguments_stdin->arr[argument_number][i] != ';')
				return false;
	}
	
	return true;

}

/*
	kontrola argumenu [min] [max] 
	vystup true nebo false
*/
bool check_min_max(t_stdin_arg *arguments, int argument_number)
{
	bool argum_exist = false;
	for(int i = 0; i < AMOUNT_OF_MIN_MAX_ARGUMENTS; i++)
		if(strcmp(arguments->arr[argument_number],MIN_MAX_ARGUMENTS[i]) == 0)
		{
			argum_exist = true;
			return argum_exist;
		}

	return argum_exist;
}

/*
	kontrola argumenu find 
	vystup true nebo false
*/

bool check_find_STR(t_stdin_arg *arguments_stdin, int argument_number)
{
	const char FIND[] = "[find";
	bool argum_exist = false;

	if(strcmp(arguments_stdin->arr[argument_number],FIND) == 0)
	{	
		argument_number++;
		argum_exist = true;
	}

	if(argum_exist)
	{
		int amount_symbols = 0;
		for(;arguments_stdin->arr[argument_number][amount_symbols] != '\0'; amount_symbols++);

		for(int i = 0; arguments_stdin->arr[argument_number][i] != '\0'; i++)
		{


			if(i == amount_symbols - WSB)
			{
				if(arguments_stdin->arr[argument_number][i] != ']')
				{
					return false;
				}
			}	

			if(i == amount_symbols - WSEM)
			{
				if(arguments_stdin->arr[argument_number][i] != ';')
				{
					return false;
				}

			}


		}


	}

	return argum_exist;
}

/*
	Kontrola radku argumentu set
	vystup true nebo false
*/
bool check_set_str(t_stdin_arg *arguments_stdin, int argument_number)
{
	int amount_symbols = 0;
	for(;arguments_stdin->arr[argument_number][amount_symbols] != '\0'; amount_symbols++);

	if(arguments_stdin->arr[argument_number][ amount_symbols - WSEM] != ';')
	{
		return false;
	}
	
return true;
}

/*
	kontrola flagu a argumentu
	vystup spravne nebo ne 
*/
int check_flags(t_stdin_arg *arguments_stdin, int *amoun_of_selection_cell) 
{	
	bool open = false;
	int flag_number = 0;
	for(int argument_number = 0; argument_number < arguments_stdin->amount; argument_number++)
	{
		if((flags_ownership_check(argument_number, arguments_stdin, &flag_number)) && open) //zjesti to je flag nebo argument
		{	
			if(flag_number == 7)
			{
				if(argument_number + 1 <= arguments_stdin->amount)
				{	
					argument_number++;

					if(check_set_str(arguments_stdin,argument_number));
					
					else
					{
						return ERRARG;
					}
				}
				else
				{
					return ERRARG;
				}	

			}

			if(flag_number >= 8 && flag_number <= 12)
			{
				if(argument_number + 1 <= arguments_stdin->amount)
				{	
					argument_number++;

					for(int i = 0; arguments_stdin->arr[argument_number][i] != '\0'; i++)
						if(arguments_stdin->arr[argument_number][i] == '_')
						{
							return ERRARG;
						}

					if(check_two_arguments_cell(arguments_stdin,argument_number));
					
					else
					{
						return ERRARG;
					}
				}
				else
				{
					return ERRARG;
				}	
			}
			else if(flag_number >= 13 && flag_number <= 15)
			{	
				if(argument_number + 1 <= arguments_stdin->amount)
				{
					argument_number++;

					if(save_arguments_ownership_check(argument_number,arguments_stdin));

					else
					{
						return ERRARG;
					}
				}
				else
				{
					return ERRARG;
				}	

			}

		}
		else
		{
			bool exist_argum = false;
			
			if((check_find_STR(arguments_stdin,argument_number)) && open)
			{	(*amoun_of_selection_cell)++;
				argument_number++;
				exist_argum = true;
			}
		
			else if(check_two_arguments_cell(arguments_stdin,argument_number))
			{	
				if(!(argument_number))
					open = true;

				(*amoun_of_selection_cell)++;
				exist_argum = true;
			}
			
			else if(check_four_arguments_cell(arguments_stdin,argument_number))
			{	
				if(!(argument_number))
					open = true;

				(*amoun_of_selection_cell)++;
				exist_argum = true;
			}
			
			else if((check_min_max(arguments_stdin,argument_number)) && open)
			{
				(*amoun_of_selection_cell)++;
				exist_argum = true;
			}

			if(!(exist_argum))
			{	
				return ERRARG;
			}
		}
	}
	return 0;
}

/*
	Nastavi vyber aktualni bunce v strukture argumentu na vychazi hodnotu
*/
void set_default_selected_arguments(t_arguments *sel_arguments)
{
	
	sel_arguments->selected_cell.type = NS;
	sel_arguments->selected_cell.row_1 = NS;
	sel_arguments->selected_cell.col_1 = NS;
	sel_arguments->selected_cell.row_2 = NS;
	sel_arguments->selected_cell.col_2 = NS;
	sel_arguments->selected_cell.str = NULL;
	sel_arguments->flags = NULL;
	sel_arguments->amount_flags = 0;

}

/*
	Nastavi honotu pro pouzivani v retezce ktery zacina od 0 
*/
void programm_def_selected_arguments(t_arguments *sel_arguments)
{
	
	sel_arguments->selected_cell.row_1 -= 1;
	sel_arguments->selected_cell.col_1 -= 1;
	sel_arguments->selected_cell.row_2 -= 1;
	sel_arguments->selected_cell.col_2 -= 1;
	
	if(sel_arguments->flags != NULL)
	{
		for(int i = 0; i < sel_arguments->amount_flags; i++)
		{	
			sel_arguments->flags[i].cell_of_argum.row -= 1;
			sel_arguments->flags[i].cell_of_argum.col -= 1;
		
		}

	}
}

/*
	Nastavi honotu pro pouzivani v retezce ktery zacina od 0 
*/
void programm_def_number_rows(t_table *table)
{
	for(int i = 0; i < table->amount_rows; i++)
	{
		table->col_of_rows[i].number_row -= 1;
	}
}

/*
	Nastavi vyber bunky flagu na vychazi hodnotu
*/
void set_default_flags(t_arguments *help_arg_struct)
{	
	if(help_arg_struct->flags != NULL)
	{
		for(int i = 0; i < help_arg_struct->amount_flags; i++)
		{	
			help_arg_struct->flags[i].argum = NS;
			help_arg_struct->flags[i].save_number = NS;
			help_arg_struct->flags[i].cell_of_argum.row = NS;
			help_arg_struct->flags[i].cell_of_argum.col = NS;
			help_arg_struct->flags[i].cell_of_argum.string = NULL;
		
		}
	}
}

/*
	Zjesti to ptri do argument do grupy selektoru
	Vystup true nebo false
*/
bool selectors_ownership_check(int num_argum, t_stdin_arg *arguments, int *flag_number)
{	
	bool selector = false;
	for( *flag_number = 0; *flag_number < AMOUNT_SELECTORS; (*flag_number)++) 
		if(strcmp(arguments->arr[num_argum],SELECTORS[*flag_number]) == 0)
		{
			selector = true;
			return selector;
		}

	return selector;
}

/*
	Zjesti kolil symbolu v str find
	Vystup pocet symbolu
*/
int check_amount_symbols_find(t_stdin_arg *arguments_stdin, int slider)
{
	int amount_symbols = 0;
	for(;arguments_stdin->arr[slider][amount_symbols] != '\0'; amount_symbols++);
	return amount_symbols - SB;
}

/*
	Zjesti kolil symbolu v str set
	Vystup pocet symbolu
*/

int check_amount_symbols_set(t_stdin_arg *arguments_stdin, int slider)
{
	int amount_symbols = 0;
	for(;arguments_stdin->arr[slider][amount_symbols] != '\0'; amount_symbols++);
	return amount_symbols;
}

/*
	Provodi allokaciu pro find
*/
void allocation_find(int amount_symbols_find, t_arguments *help_arg_struct,int *err_aloc)
{
	help_arg_struct->selected_cell.str = malloc(amount_symbols_find * sizeof(char));

	if(help_arg_struct->selected_cell.str == NULL)
	{
		*err_aloc = 1;
	}

}

void deallocation_sel_arguments(t_arguments *sel_arguments_struct);

/*
	Provodi allokaciu pro str set
*/
void allocation_set(int amount_symbols, t_arguments *help_arg_struct, int flag_number, int *err_aloc)
{
	help_arg_struct->flags[flag_number].cell_of_argum.string = malloc(amount_symbols * sizeof(char));

	if(help_arg_struct->flags[flag_number].cell_of_argum.string == NULL)
	{
		*err_aloc = 1;
	}

}

/*
	Zjesti pres kolik argumentu bude priste selektor
	Vystup pocet argumentu do pristeho selektoru
*/
void check_next_selector(t_stdin_arg *arguments_stdin, int slider, int *amount_flags)
{	
	*amount_flags = 0;
	int flag_number = 0;
	for(; slider < arguments_stdin->amount; slider++)
		if(flags_ownership_check(slider, arguments_stdin, &flag_number))
		{
			if(flag_number >= 0 && flag_number <= 6)
				(*amount_flags)++;

			else if(flag_number >= 7 && flag_number <= 15)
			{
				(*amount_flags)++;
				slider++;
			}

			else if(flag_number == 16)
				(*amount_flags)++;
		}
		else
			break;
}


/*
	Allokacia structury pro argumenty
*/
void allocation_argument_struct(int amount_flags, t_arguments *help_arg_struct, int *err_aloc)//переименовать
{
	help_arg_struct->flags = malloc(amount_flags * sizeof(t_argum));

	if(help_arg_struct->flags == NULL)
	{
		*err_aloc = 1;
	}

	help_arg_struct->amount_flags = amount_flags;

}

/*
	Zjesti je to bunka [x,y]
	Vystup true false
*/
bool selectors_cell_two_check(t_stdin_arg *arguments_stdin, int argument_number)
{
	int amount_comma = 0;

	for(int i = 0; arguments_stdin->arr[argument_number][i] != '\0'; i++)
		if(arguments_stdin->arr[argument_number][i] == ',')
			amount_comma++;

	if(amount_comma == 1)
		return true;

	return false;
}

/*
	Zjesti je to bunka [x,y,z,a]
	Vystup true false
*/
bool selectors_cell_four_check(t_stdin_arg *arguments_stdin, int argument_number)
{
	int amount_comma = 0;

	for(int i = 0;arguments_stdin->arr[argument_number][i] != '\0'; i++)
		if(arguments_stdin->arr[argument_number][i] == ',')
			amount_comma++;

	if(amount_comma == 3)
		return true;

	return false;
}

/*
	Zjesti koli symbolu v bunce []
	Vystup pocet symbolu
*/
int check_amount_symbols_selected_cell(int *slider_3, t_stdin_arg *arguments_stdin, int argument_number)
{
	int amount_symbols = 0;
	for(;arguments_stdin->arr[argument_number][*slider_3] != ',' && arguments_stdin->arr[argument_number][*slider_3] != ']' ; (*slider_3)++)
		amount_symbols++;

	(*slider_3)++;
	return amount_symbols + EL;
}

/*
	Deallokui strukturu argumentu
*/
void deallocation_sel_arguments(t_arguments *sel_arguments_struct)
{
	if(sel_arguments_struct->selected_cell.str != NULL)
	{
		free(sel_arguments_struct->selected_cell.str);
		sel_arguments_struct->selected_cell.str = NULL;
	}

	if(sel_arguments_struct->flags != NULL)
	{
		for(int i = 0; i < sel_arguments_struct->amount_flags; i++)
		{
			if(sel_arguments_struct->flags[i].cell_of_argum.string != NULL)
			{
				free(sel_arguments_struct->flags[i].cell_of_argum.string);
				sel_arguments_struct->flags[i].cell_of_argum.string = NULL;
			}
		}	

		free(sel_arguments_struct->flags);
		sel_arguments_struct->flags = NULL;

	}
}

/*
	Logika rozdeleni argumentu do struktury
	Vystup strukra ktera obsahuje 1 aktualni bunku a flagi pro zpracovani z ni
*/
t_arguments logic_of_loading_arguments(t_stdin_arg *arguments_stdin, int *select_slider, int *err_aloc)
{	
	int flag_number_in_const = 0;
	int flag_number = 0;
	t_arguments help_arg_struct;
	int amount_flags = 0;
	int type_selector = 0;

	int slider = *select_slider;
	
	set_default_selected_arguments(&help_arg_struct);
	
	if(selectors_ownership_check(slider, arguments_stdin, &type_selector)) //zjesti ktery to je argument
	{	
		amount_flags = 0;
		type_selector += TA; 

		if(type_selector == 3) //type 3 je type pro find
		{	
			slider++;
			int amount_symbols_find = check_amount_symbols_find(arguments_stdin,slider);
			allocation_find(amount_symbols_find, &help_arg_struct, err_aloc);

			help_arg_struct.selected_cell.type = type_selector;

			int slider_2 = 0;
			for(;slider_2 < amount_symbols_find; slider_2++)
				help_arg_struct.selected_cell.str[slider_2] = arguments_stdin->arr[slider][slider_2];
			slider_2--;
			help_arg_struct.selected_cell.str[slider_2] = '\0';
		}


		else if(type_selector == 4) // je type pro [max]
			help_arg_struct.selected_cell.type = type_selector;

		else if(type_selector == 5) // je type pro [min]
			help_arg_struct.selected_cell.type = type_selector;

		else if(type_selector == 6) // je type pro [_]
			help_arg_struct.selected_cell.type = type_selector;
			
		slider++;
		check_next_selector(arguments_stdin,slider,&amount_flags); // zjesti kolik flagu do pristego selektora 

		if(amount_flags != 0)
		{
			allocation_argument_struct(amount_flags, &help_arg_struct, err_aloc);

		}	set_default_flags(&help_arg_struct);

		amount_flags += slider;
	}

	else if(selectors_cell_two_check(arguments_stdin, slider) || selectors_cell_four_check(arguments_stdin, slider)) //zjesti ktera je to bunka [x,y] nebo [x,y,z,a]
	{																												// pak prepise argumenta row a col do structury
		amount_flags = 0;
		int arg = 0;
		int slider_2 = 1;
		int slider_3 = 0;
		int numb_of_passes = 0;
		if(selectors_cell_two_check(arguments_stdin, slider))
		{
			help_arg_struct.selected_cell.type = 1;
			arg = 2;
		}

		if(selectors_cell_four_check(arguments_stdin, slider))
		{
			help_arg_struct.selected_cell.type = 2;
			arg = 4;
		}

		while(arg)
		{
				
			int amount_symbols = check_amount_symbols_selected_cell(&slider_3, arguments_stdin, slider);
			char help_arr[amount_symbols];

			int slider_records = 0;
			for(;arguments_stdin->arr[slider][slider_2] != ',' && arguments_stdin->arr[slider][slider_2] != ']'; slider_2++)
			{
				help_arr[slider_records] = arguments_stdin->arr[slider][slider_2];
				slider_records++;
			}

			help_arr[slider_records] = '\0';

			slider_2++;

			if(help_arr[0] == '_' || help_arr[0] == '-')
				help_arr[0] = '0';

			if(numb_of_passes == 0)
				help_arg_struct.selected_cell.row_1 = atoi(help_arr);

			else if(numb_of_passes == 1)
				help_arg_struct.selected_cell.col_1 = atoi(help_arr);

			else if(numb_of_passes == 2)
				help_arg_struct.selected_cell.row_2 = atoi(help_arr);

			else if(numb_of_passes == 3)
				help_arg_struct.selected_cell.col_2 = atoi(help_arr);

			arg--;
			numb_of_passes++;
		}	

		slider++;

		check_next_selector(arguments_stdin,slider,&amount_flags);

		if(amount_flags != 0)
		{	
			allocation_argument_struct(amount_flags, &help_arg_struct, err_aloc);

			set_default_flags(&help_arg_struct);
		}	

		amount_flags += slider;
	}	


	for(; slider < amount_flags;slider++)
	{	
		//flags 0"irow" 1"arow" 2"drow" 3"icol" 4"acol" 5"dcol" 6"clear" 7"set" 8"swap" 9"sum" 10"avg" 11"count" 12"len" 13"def" 14"use" 15"inc" 16"[set]"
		if(flags_ownership_check(slider, arguments_stdin, &flag_number_in_const)) //zjesti jaky je to flag pak prepise do structury
		{
			if((flag_number_in_const >= 0 && flag_number_in_const <= 6) || (flag_number_in_const == 16))
			{
				help_arg_struct.flags[flag_number].argum = flag_number_in_const;
			}

			else if(flag_number_in_const == 7)
			{
				help_arg_struct.flags[flag_number].argum = flag_number_in_const;

				slider++;
				amount_flags++;

				int amount_symbols = check_amount_symbols_set(arguments_stdin,slider);

				allocation_set(amount_symbols,&help_arg_struct,flag_number, err_aloc);

				int slider_2 = 0;

				for(;arguments_stdin->arr[slider][slider_2] != '\0' ; slider_2++)
					help_arg_struct.flags[flag_number].cell_of_argum.string[slider_2] = arguments_stdin->arr[slider][slider_2];

				slider_2--;
				help_arg_struct.flags[flag_number].cell_of_argum.string[slider_2] = '\0';

			}

			else if(flag_number_in_const >= 8 && flag_number_in_const <= 12)
			{
				int slider_3 = 1;
				int slider_2 = 1;
				int arg = 2;
				help_arg_struct.flags[flag_number].argum = flag_number_in_const;

				slider++;
				amount_flags++;


					while(arg)
				{
				
					int amount_symbols = check_amount_symbols_selected_cell(&slider_3, arguments_stdin, slider);
					char help_arr[amount_symbols];

					int slider_records = 0;
					for(;arguments_stdin->arr[slider][slider_2] != ',' && arguments_stdin->arr[slider][slider_2] != ']'; slider_2++)
					{
						help_arr[slider_records] = arguments_stdin->arr[slider][slider_2];
						slider_records++;
					}

					help_arr[slider_records] = '\0';

					slider_2++;

					if( arg == 2)
						help_arg_struct.flags[flag_number].cell_of_argum.row = atoi(help_arr);

					else if(arg == 1)
						help_arg_struct.flags[flag_number].cell_of_argum.col = atoi(help_arr);

					arg--;
				}	
			}

			else if(flag_number_in_const >= 13 && flag_number_in_const <= 15)
			{
				help_arg_struct.flags[flag_number].argum = flag_number_in_const;

				slider++;
				amount_flags++;


				for(int save_argum_number = 0; save_argum_number < AMOUNT_OF_SAVE_ARGUMENTS; save_argum_number++)
					if(strcmp(arguments_stdin->arr[slider],SAVE_ARGUMENTS[save_argum_number]) == 0)
					{
						help_arg_struct.flags[flag_number].save_number = save_argum_number;
					}
			}

			flag_number++;

		}

	}

	*select_slider = slider;

	return help_arg_struct;
	
}

/*
	Zjesti kde se zacina 
	Vystup cislo symbolu nutne bunce od zacatku retezce
*/
int cell_search(int nead_cell, char *str_bufer,char *sep)
{	
	bool quotes = false;
	int slider = 0;
	int num_cell_find = 0;
	
	while(num_cell_find != nead_cell)
	{	
		if(str_bufer[slider] == '"')
			quotes = open_quoates(quotes);

		if(str_bufer[slider] == sep[0] && !(quotes))
			num_cell_find++;

		if(str_bufer[slider] == '\0')
		{
			slider = -1;
			break;
		}
		slider++;
	}

	return slider;
}

/*
	Zjesti kolik je symbolu v bunce 
	Vystup cislo symbolu v bunce 
*/
int counting_amount_symbol_cell(int nead_cell, char *str_bufer, char *sep)
{
	int slider = cell_search(nead_cell,str_bufer,sep);
	int amount_symbol = 1;
	bool quotes = false;

	if(slider != -1)
	{
		for(;str_bufer[slider] != sep[0] && str_bufer[slider] != '\0';slider++)
			amount_symbol++;

		for(;str_bufer[slider] != '\0';slider++)
		{
			if(str_bufer[slider] == '"')
				quotes = open_quoates(quotes);

			if(str_bufer[slider] == sep[0] && !(quotes))
				break;

			amount_symbol++;
		}

		if(str_bufer[slider] == sep[0])
	 		amount_symbol++;
	}

	return amount_symbol + EL;
}

/*
	Nachazi delku nazvu souboru
	Vystup delka retezce
*/
int find_leng_file_name(int start_number_flags,int *file_name_location, int argc, char **argv) //нади мне где начинается имя файла
{	
	*file_name_location = start_number_flags + 1;
	int leng_file_name = 0;

	if(argc <= *file_name_location)
	{
		fprintf(stderr, "CHÝBA: Nespravně zadan fail\n");
		exit(10);
	}

	for(int i = 0; argv[*file_name_location][i] != '\0'; i++)
		leng_file_name++;

	return leng_file_name + EL;
} 

/*
	Perepise nazev souboru
*/
void filling_file_name(char *file_name,char **argv, int file_name_location) //заполни мне имя файла
{	
	int slider = 0;
	for(; argv[file_name_location][slider] != '\0'; slider++)
		file_name[slider] = argv[file_name_location][slider];

	file_name[slider] = '\0';
}

/*
	Zmnena separatoru
*/
void replaces_the_separator(char *len_bufer, char *sep, int *amount_coll_str)
{	
	bool quotes = false;
	for(int i = 0; len_bufer[i] != '\0'; i++)
	{	
		if(len_bufer[i] == '"')
		{
			quotes = open_quoates(quotes);
		}

		for(int a = 0; sep[a] != '\0';a++)
		{
			if((len_bufer[i] == sep[a]) && !(quotes))
			{	
				len_bufer[i] = sep[0];
				(*amount_coll_str)++;
			}	
		}
	}		
}

/*
	nachazi pocet argumetu 
*/
int discover_amount_symbol_stringbuf(char *file_name,int *amount_symbol_in_line, long int *cursor_position,bool *konec)
{	
	FILE *f;
	f = NULL;
	char read_bufer;
	f = fopen(file_name,"r");
	if(f == NULL)
	{
		return ERROPEN;
	}
	 if(!(fseek(f,*cursor_position,SEEK_SET) == 0))
	 	return ERROPEN;

	while(read_bufer != '\n')
	{
		if(!(fscanf(f,"%c",&read_bufer) == EOF))
			(*amount_symbol_in_line)++;
		else
		{
			*konec = false;
			break;
		}
	}

	*cursor_position = ftell(f);
	if(*cursor_position == -1)
		return ERROPEN;

	fclose(f);
	return 0;
}

/*
	Allocovani buferu pro row 
*/
char* stringbuf_construct(char *str_bufer, char *file_name,int *amount_symbol_in_line, long int *cursor_position,bool *konec, int *err_read_f)
{
	if(discover_amount_symbol_stringbuf(file_name,amount_symbol_in_line,cursor_position,konec) == ERROPEN)
		*err_read_f = ERROPEN;

	if(*konec)
	{
		str_bufer = malloc(sizeof(char) * (*amount_symbol_in_line));
		if(str_bufer == NULL)
		{
			*err_read_f = ERROPEN;
		}
		
	}	
	return str_bufer;
}


char* filling_stringbuf(char *str_bufer, char *file_name,int *amount_symbol_in_line, long int *cursor_position, bool *konec, int *err_read_f)
{	
	long int old_cursor_position = *cursor_position;
	FILE *f;
	f = NULL;
	str_bufer = stringbuf_construct(str_bufer,file_name,amount_symbol_in_line,cursor_position,konec, err_read_f);
	if(*konec)
	{	
		f = fopen(file_name,"r");
		if(f == NULL)
		{
			fprintf(stderr,"CHYBA:Soubor nemůže být otevřen\n");
			(*err_read_f)++;
			return str_bufer;
		}
	
		if(!(fseek(f,old_cursor_position,SEEK_SET) == 0))
		{
			fprintf(stderr,"CHYBA: Volání kurzoru\n");
			(*err_read_f)++;
			return str_bufer;
		}

		fgets(str_bufer,*amount_symbol_in_line,f);
		fclose(f);
	}
	return str_bufer;

}
/*
	nachazi pocet delicu
*/
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
int writes_separators(char **argv, int amount_separators, char *separators, int *start_number_flags)
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
			if(argv[2][slider] == 92 || argv[2][slider] == 34 )
			{
				fprintf(stderr,"CHYBA: Nespravne zadane udaje v retezce delim\n");
				separators[slider] = '\0';
				exit(1);
			}
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
	return 0;
}

void set_default_cell(t_cell *cell)
{
	cell->number =0;
	cell->content = NULL;
}

void set_default_row(t_row *row)
{
	row->number_row = 0;
	row->amount_cell = 0;
	row->rows_of_cell = NULL;
}

void set_default_table(t_table *table)
{
	table->amount_rows = 0;
	table->col_of_rows = NULL;
}

t_cell create_cell()
{
	t_cell new_cell;

	set_default_cell(&new_cell);

	return new_cell;
}

t_row create_row()
{	
	t_row new_row;
	
	set_default_row(&new_row);

	return new_row;
}

/*
	Allocovani misto pro radek 
*/
int allocation_col_of_rows(t_table *table, int amount_rows_table)
{	
	t_row *p = realloc(table->col_of_rows,sizeof(t_row) * (amount_rows_table));
	if(p == NULL)
	{
		return ERRALLOC;
	}
	table->col_of_rows = p;
	
	for(int i = table->amount_rows; i < amount_rows_table; i++)
		set_default_row(&table->col_of_rows[i]);

	table->amount_rows = amount_rows_table;
	return 0;
}	
/*
	Allocovani misto pro bunky 
*/
int allocation_row(t_table *table, int amount_colls_line)
{	
	t_cell *p = realloc(table->col_of_rows[(table->amount_rows) - EL].rows_of_cell,sizeof(t_cell) * (amount_colls_line));
	if(p == NULL)
	{
		return ERRALLOC;
	}

	table->col_of_rows[table->amount_rows - EL].number_row = table->amount_rows;
	table->col_of_rows[table->amount_rows - EL].amount_cell = amount_colls_line;
	table->col_of_rows[table->amount_rows - EL].rows_of_cell = p;
	return 0;
}	
/*
	Allocovani misto pro hodnotu bunce
*/
int allocation_cell(t_table *table, int amount_symbol_in_cell, int nead_cell)
{	
	char *p = realloc(table->col_of_rows[table->amount_rows - EL].rows_of_cell[nead_cell].content,sizeof(char) * (amount_symbol_in_cell));
	if(p == NULL)
	{
		return ERRALLOC;
	}
	table->col_of_rows[table->amount_rows - EL].rows_of_cell[nead_cell].number = nead_cell; 
	table->col_of_rows[table->amount_rows - EL].rows_of_cell[nead_cell].content = p;
	return 0;
}	
/*
	Allocovani misto pro celou tabulku 
*/
int allocation_table(t_table *table,int amount_rows_table,int amount_colls_line)
{	
	if(allocation_col_of_rows(table, amount_rows_table) == ERRALLOC)
		return ERRALLOC;

	table->col_of_rows[amount_rows_table - EL] = create_row();

	if(allocation_row(table, amount_colls_line) == ERRALLOC)
		return ERRALLOC;

	for(int i = 0; i < amount_colls_line; i++)
	table->col_of_rows[amount_rows_table - EL].rows_of_cell[i] = create_cell();

	return 0;
}

/*
	Prepisuje hodnotu bunek
*/
void filling_cells(t_table *table, char *str_bufer, char *sep)
{
	bool quotes = false;
	int a = 0; 
	int slider = 0;

	for(int i = 0; i < table->col_of_rows[table->amount_rows - EL].amount_cell; i++)
	{
		for( a = 0; str_bufer[slider] != '\0'; a++)
		{	if(str_bufer[slider] == '"')
				quotes = open_quoates(quotes);
			if(str_bufer[slider] == sep[0] && !(quotes))
				break;
			table->col_of_rows[table->amount_rows - EL].rows_of_cell[i].content[a] = str_bufer[slider];
			slider++;
		}


		if(str_bufer[slider] == sep[0])
		{
			table->col_of_rows[table->amount_rows - EL].rows_of_cell[i].content[a] = str_bufer[slider];
			a++;
			slider++;
		}
		table->col_of_rows[table->amount_rows - EL].rows_of_cell[i].content[a] = '\0';
	}

}

/*
	Allocovani misto pro radek 
*/
int filling_table(t_table *table, char *str_bufer, char *sep)
{	
	int amount_symbol = 0;
	for( int nead_cell = 0; nead_cell < table->col_of_rows[table->amount_rows - EL].amount_cell; nead_cell++)
	{
		amount_symbol = counting_amount_symbol_cell(nead_cell,str_bufer,sep);	
		if(allocation_cell(table, amount_symbol + 2, nead_cell) == ERRALLOC)
		{
			return ERRALLOC;
		}
	}

	filling_cells(table, str_bufer, sep);
	return 0;
}

/*
	Dellocovani tabulki
*/
void deallocation_table(t_table *table)
{
	if(table->col_of_rows != NULL)
	{	
		for(int i = 0; i < table->amount_rows; i++)
		{
			if(table->col_of_rows[i].rows_of_cell != NULL)
			{
				for(int a = 0; a < table->col_of_rows[i].amount_cell; a++)
				{
					if(table->col_of_rows[i].rows_of_cell[a].content != NULL)
					{
						free(table->col_of_rows[i].rows_of_cell[a].content);
						table->col_of_rows[i].rows_of_cell[a].content = NULL;
					}
				}

				free(table->col_of_rows[i].rows_of_cell);
				table->col_of_rows[i].rows_of_cell = NULL;
			}

		}
		free(table->col_of_rows);
		table->col_of_rows = NULL;
	}	

	if(table == NULL)
	{
		free(table);
		table = NULL;
	}

}

/*
	Zjisti maximalni pocet radku 
*/
int check_max_amount_cell(t_table *table)
{
	int max_amount_cell = 0; 
	for(int i = 0; i < table->amount_rows; i++)
	{	
		if(table->col_of_rows[i].amount_cell  > max_amount_cell)
		{
			max_amount_cell = table->col_of_rows[i].amount_cell;
		}

	}
	return max_amount_cell;
}

/*
	Pridovava misto pro hodnotu v bunce
*/
int add_content_in_cell(t_table *table, int string_number,int number_cell,int amount_symbols)
{
	char *p = realloc(table->col_of_rows[string_number].rows_of_cell[number_cell].content,sizeof(char) * (amount_symbols));
	if(p == NULL)
	{
		return ERRALLOC;
	}
	table->col_of_rows[string_number].rows_of_cell[number_cell].number = number_cell; 
	table->col_of_rows[string_number].rows_of_cell[number_cell].content = p;
	return 0;
}
/*
	Pridovava bunku do radku 
*/
int add_cell(t_table *table, int string_number, int amount_cell, int amount_symbols)
{		
	t_cell *p = realloc(table->col_of_rows[string_number].rows_of_cell,sizeof(t_cell) * (amount_cell));
	if(p == NULL)
	{
		return ERRALLOC;
	}

	table->col_of_rows[string_number].rows_of_cell = p;

	if(amount_symbols != 0)
	{	
		for(int number_cell = table->col_of_rows[string_number].amount_cell; number_cell < amount_cell; number_cell++)
		{
			table->col_of_rows[string_number].rows_of_cell[number_cell] = create_cell();
			add_content_in_cell(table, string_number, number_cell, amount_symbols);
		}
	}	

	table->col_of_rows[string_number].amount_cell = amount_cell;

	return 0;

}

/*
	Pridovava nakonec bunce oddelovac
*/
int add_end_of_cell(int str_num, int col_num, t_table *table, char *sep)
{	
	int len = 0;

	for(int a = 0;table->col_of_rows[str_num].rows_of_cell[col_num].content[a] != '\0';a++)
		len++;
	len++;
	if(add_content_in_cell(table,str_num,col_num,len + 1) == ERRALLOC)
		return ERRALLOC;
	table->col_of_rows[str_num].rows_of_cell[col_num].content[len - 1] = sep[0];
	table->col_of_rows[str_num].rows_of_cell[col_num].content[len] = '\0';
	return 0;
}

void set_default_save_list(t_save_list *save_list)
{		
	save_list->amount_saves = AMOUNT_SAVES;
	for(int i = 0; i < save_list->amount_saves;i++)
	{
		save_list->save[i].num_content_cell = 0;
		save_list->save[i].text_content_cell = NULL;
		save_list->save[i].number = '-';

	}

}

void set_default_save_set(t_save_set *save_set)
{
	save_set->type = 1;
	save_set->row_1 = 1;
	save_set->col_1 = 1;
	save_set->row_2 = -4;
	save_set->col_2 = -4; 
}

int allocation_save_list(t_save_list *save_list, int save_number, int amount_symbols)
{
	char *p = realloc(save_list->save[save_number].text_content_cell,sizeof(char)*amount_symbols);
	if(p == NULL)
		return ERRALLOC;
	save_list->save[save_number].text_content_cell = p;
	return 0;
}

/*
	Udela rovny pocet bunek v radkach
*/
int alignment_of_cells(t_table *table, char *sep , int str_num, int max_amount_cell) // принемает сколько ты ячеек хочешь добить
{
	int amount_symbols = 2;

	if(table->col_of_rows[str_num].amount_cell  < max_amount_cell)
	{
		int old_amount_cell = table->col_of_rows[str_num].amount_cell;
		if(add_cell(table, str_num, max_amount_cell, amount_symbols) ==  ERRALLOC)
			return ERRALLOC;
		if(old_amount_cell != 0)
		{	
			if(add_end_of_cell(str_num,old_amount_cell - 1, table, sep) == ERRALLOC)
				return ERRALLOC;
		}	

		for(;old_amount_cell < max_amount_cell; old_amount_cell++)
		{
			if(old_amount_cell != max_amount_cell -1)
			{	
				table->col_of_rows[str_num].rows_of_cell[old_amount_cell].content[0] = sep[0];
				table->col_of_rows[str_num].rows_of_cell[old_amount_cell].content[1] = '\0';
			}
			else
			{	
				table->col_of_rows[str_num].rows_of_cell[old_amount_cell].content[0] = '\0';
			}	
		}
	}

	return 0;
	
}

/*
	Pridovava radek
*/
int add_rows(t_table *table, int amount_rows_table) 
{
	if(allocation_col_of_rows(table, amount_rows_table)== ERRALLOC)
		return ERRALLOC;

	return 0;
}

/*
	Zjesti v bunce je cislo nebo ne
	Vystup true nebo false
*/
bool find_number(t_table *table, int row, int col, char *sep)
{	
	int dot = 0;
	int minus = 0;
	bool numeric = false;
	if(table->col_of_rows[row].rows_of_cell[col].content[0] == sep[0])
		numeric = false;

	for(int slider = 0;table->col_of_rows[row].rows_of_cell[col].content[slider]!= sep[0] && table->col_of_rows[row].rows_of_cell[col].content[slider] != '\0' ; slider++)
	{	
		if(table->col_of_rows[row].rows_of_cell[col].content[slider] == '-')
		{
			minus++;
			if(minus == 2)
				return false;
		}

		else if (table->col_of_rows[row].rows_of_cell[col].content[slider] == '.')	
		{
			dot++;
			if(dot == 2)
				return false;
		}
		
		else if(table->col_of_rows[row].rows_of_cell[col].content[slider] >= '0' && table->col_of_rows[row].rows_of_cell[col].content[slider]<= '9')
		{
			numeric = true;
		}
		else
		{
			numeric = false;
			return numeric;
		}
	}
	return numeric;
}

/*
	Nachazi maximalni hodnotu mezi vybranych bunek a nastavi na aktualni vyber
*/
void min_max(t_table *table, t_arguments *arg, int amount_past_cells, char *sep)
{	
	double new_num = 0.0;
	double old_num = 0.0;
	int row = -1;
	int col = -1;
	int i = 0;
	int len_str = 1;

	for(; i < amount_past_cells; i++)
	{	
		if(arg[i].selected_cell.type == 1 || arg[i].selected_cell.type == 2 || arg[i].selected_cell.type == 4 || arg[i].selected_cell.type == 5)
		{	
			int work_row = 0;
			int work_col = 0;
			int max_row = 0;
			int max_col = 0;

			if(arg[i].selected_cell.type == 1 || arg[i].selected_cell.type == 4 || arg[i].selected_cell.type == 5)
			{
				work_row = arg[i].selected_cell.row_1;
				work_col = arg[i].selected_cell.col_1;

				max_row = work_row;
				max_col = work_col;

				if(work_row == -1)
				{
					work_row = 0;
					max_row = table->amount_rows - 1;
				}

				if(work_col == -1)
				{
					work_col = 0;
					max_col = table->col_of_rows[0].amount_cell - 1;

				}
			}	

			else if(arg[i].selected_cell.type == 2)
			{	
				work_row = arg[i].selected_cell.row_1;
				max_row = arg[i].selected_cell.row_2;
				max_col = arg[i].selected_cell.col_2;

				if(max_row == -1)
					max_row = table->amount_rows - 1;
				
				if(max_col == -1)
					max_col = table->col_of_rows[0].amount_cell - 1;
			}	

			for(; work_row <= max_row; work_row++ )
			{	

				work_col = arg[i].selected_cell.col_1;
				if(work_col == -1)
				{
					work_col = 0;
				}

				for(; work_col <= max_col; work_col++ )
				{
					if(find_number(table, work_row, work_col, sep))
					{	
						len_str = 1;
						for(int a = 0; table->col_of_rows[work_row].rows_of_cell[work_col].content[a] != '\0' && table->col_of_rows[work_row].rows_of_cell[work_col].content[a] != sep[0]; a++)
							len_str++;

						char num[len_str];

						int len = 0;
						for(; table->col_of_rows[work_row].rows_of_cell[work_col].content[len] != '\0' && table->col_of_rows[work_row].rows_of_cell[work_col].content[len] != sep[0]; len++)
							num[len] = table->col_of_rows[work_row].rows_of_cell[work_col].content[len];
						
						num[len] = '\0';

						new_num = atof(num);
			
						if(arg[amount_past_cells].selected_cell.type == 4)
						{	
							if(row == -1)
							{
								old_num = new_num;
								row = work_row;
								col = work_col;
							}
							else if(old_num <= new_num)
							{
								
								old_num = new_num;
								row = work_row;
								col = work_col;
							}
						}	

						else if(arg[amount_past_cells].selected_cell.type == 5)
						{	
							if(row == -1)
							{
								old_num = new_num;
								row = work_row;
								col = work_col;
							}
							else if(old_num >= new_num)
							{
								
								old_num = new_num;
								row = work_row;
								col = work_col;
							}
						}	

					}
				}
			}		

		}
		
	}

	if(row != -1 && col != -1)
	{
		arg[amount_past_cells].selected_cell.row_1 = row;
		arg[amount_past_cells].selected_cell.col_1 = col;
	}
	else
	{
		arg[amount_past_cells].selected_cell.row_1 = 0;
		arg[amount_past_cells].selected_cell.col_1 = 0;
	}
}	

/*
	Nachazi radek v bunce
*/
int find(t_table *table, t_arguments *arg, int amount_past_cells, char *sep)
{	
	int i = 0;

	for(; i < amount_past_cells; i++)
	{	
		if(arg[i].selected_cell.type == 1 || arg[i].selected_cell.type == 2 || arg[i].selected_cell.type == 4 || arg[i].selected_cell.type == 5)
		{	
			int work_row = 0;
			int work_col = 0;
			int max_row = 0;
			int max_col = 0;
			int slider_2 = 0;
			int slider = 0;

			if(arg[i].selected_cell.type == 1 || arg[i].selected_cell.type == 4 || arg[i].selected_cell.type == 5)
			{
				work_row = arg[i].selected_cell.row_1;
				work_col = arg[i].selected_cell.col_1;

				max_row = work_row;
				max_col = work_col;

				if(work_row == -1)
				{
					work_row = 0;
					max_row = table->amount_rows - 1;
				}

				if(work_col == -1)
				{
					work_col = 0;
					max_col = table->col_of_rows[0].amount_cell - 1;

				}
			}	

			else if(arg[i].selected_cell.type == 2)
			{	
				work_row = arg[i].selected_cell.row_1;
				max_row = arg[i].selected_cell.row_2;
				max_col = arg[i].selected_cell.col_2;

				if(max_row == -1)
					max_row = table->amount_rows - 1;
				
				if(max_col == -1)
					max_col = table->col_of_rows[0].amount_cell - 1;
			}	

			for(; work_row <= max_row; work_row++ )
			{	

				work_col = arg[i].selected_cell.col_1;
				if(work_col == -1)
				{
					work_col = 0;
				}
			
				for(; work_col <= max_col; work_col++ )
				{
					slider_2 = 0; 
					slider = 0;
					while (arg[amount_past_cells].selected_cell.str[slider_2] != '\0')
					{	
						if(table->col_of_rows[work_row].rows_of_cell[work_col].content[slider] == sep[0] || table->col_of_rows[work_row].rows_of_cell[work_col].content[slider] == '\0')
							break;
						if(arg[amount_past_cells].selected_cell.str[slider_2] == table->col_of_rows[work_row].rows_of_cell[work_col].content[slider])
						{
							slider_2++;
							slider++;
						}
						else
						{	
							slider_2 = 0;

							if(arg[amount_past_cells].selected_cell.str[slider_2] == table->col_of_rows[work_row].rows_of_cell[work_col].content[slider])
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
					if(arg[amount_past_cells].selected_cell.str[slider_2] == '\0')
					{
						arg[amount_past_cells].selected_cell.row_1 = work_row;
						arg[amount_past_cells].selected_cell.col_1 = work_col;
						return 0;
					}
				}
			}		

		}
		
	}
	
	arg[amount_past_cells].selected_cell.row_1 = 0;
	arg[amount_past_cells].selected_cell.col_1 = 0;
	return 0;								
}

/*
	Nastavuje hodnost radu
*/
void shifts_lines(t_table *table)
{
	for(int i = 0; i < table->amount_rows; i++)
		table->col_of_rows[i].number_row = i;
}
/*
	Nastavuje vber pro minimalni a maximalni vybrany radek a sloupec
*/
void dcl (int *work_row, int *work_col, int *max_row, int *max_col, t_arguments *arg,t_table *table, int num_arg)
{
	*work_row = arg[num_arg].selected_cell.row_1;
	*work_col = arg[num_arg].selected_cell.col_1;

	*max_row = *work_row;
	*max_col = *work_col;

	if(arg[num_arg].selected_cell.type == 2)
	{	
		*work_row = arg[num_arg].selected_cell.row_1;
		*max_row = arg[num_arg].selected_cell.row_2;
		*max_col = arg[num_arg].selected_cell.col_2;
		if(*max_row == -1)
			*max_row = table->amount_rows - 1;
		if(*max_col == -1)
		{
			if(table->col_of_rows == NULL || table->col_of_rows[num_arg].amount_cell == 0)
				*max_col = 0;
			else
				*max_col = table->col_of_rows[num_arg].amount_cell - 1;
		}

	}
	if(*work_row == -1)
	{
		*work_row = 0;
		if(table->amount_rows == 0)
			*max_row = 0;
		else
			*max_row = table->amount_rows - 1;
	}

	if(*work_col == -1)
	{
		*work_col = 0;
		if(table->col_of_rows == NULL || table->col_of_rows[num_arg].amount_cell == 0)
			*max_col = 0;
		else
			*max_col = table->col_of_rows[num_arg].amount_cell - 1;
	}
			
}

/*
	Zmneni a overi hodnoty a nastavi aktualni bunki pro prace s tabulkou
*/
int pre_prepares(t_table *table, t_arguments *arg, char *sep, int slider, t_save_set *save_set)
{
	if(arg[slider].selected_cell.type == 2)
		{
			if(arg[slider].selected_cell.row_2 == -1);
			else
			{
				if(arg[slider].selected_cell.row_1 > arg[slider].selected_cell.row_2)
					return ERRARG;
			}
			if(arg[slider].selected_cell.col_2 == -1);
			else
			{
				if(arg[slider].selected_cell.col_1 > arg[slider].selected_cell.col_2)
					return ERRARG;
			}
		}

		if(arg[slider].selected_cell.type == 4 || arg[slider].selected_cell.type == 5)
		{	
			min_max(table, arg, slider, sep);
		}
		if(arg[slider].selected_cell.type == 3)
		{	
			find(table, arg, slider, sep);
		}
		
		if(arg[slider].selected_cell.type == 6)
		{
			arg[slider].selected_cell.type = save_set->type;
			arg[slider].selected_cell.row_1 = 	save_set->row_1;
			arg[slider].selected_cell.col_1 = 	save_set->col_1;
			arg[slider].selected_cell.row_2 = 	save_set->row_2;
			arg[slider].selected_cell.col_2 = 	save_set->col_2;
		}
		if(1)
		{	
			int max_row = 1;
			int max_col = 1;

			if(arg[slider].selected_cell.type == 1 || arg[slider].selected_cell.type == 4 || arg[slider].selected_cell.type == 5)
			{
				max_row += arg[slider].selected_cell.row_1;
				max_col += arg[slider].selected_cell.col_1;
			}
			else if(arg[slider].selected_cell.type == 2)
			{
				max_row += arg[slider].selected_cell.row_2;
				max_col += arg[slider].selected_cell.col_2;
			}


			if(max_row >= table->amount_rows)
			{	
				int str_num = table->amount_rows;
				add_rows(table, max_row);
				for(;str_num < table->amount_rows;str_num++)
				{
					if(alignment_of_cells(table,sep , str_num, check_max_amount_cell(table)) == ERRALLOC)
						return ERRALLOC;
				}
				shifts_lines(table);
				
			}

			if(max_col >= check_max_amount_cell(table))
			{
				for(int i = 0; i < table->amount_rows;i++)
					alignment_of_cells(table, sep ,i, max_col);
			}
		}
		return 0;
}

void deallocation_row(int num_rows, t_table *table)
{
	if(table->col_of_rows[num_rows].rows_of_cell != NULL)
	{
		for(int num_cell = 0;num_cell < table->col_of_rows[num_rows].amount_cell; num_cell++)
		{
			if(table->col_of_rows[num_rows].rows_of_cell[num_cell].content != NULL)
			{
				free(table->col_of_rows[num_rows].rows_of_cell[num_cell].content);
				table->col_of_rows[num_rows].rows_of_cell[num_cell].content = NULL;
			}
		}

		free(table->col_of_rows[num_rows].rows_of_cell);
		table->col_of_rows[num_rows].rows_of_cell = NULL;
	}
}

/*
	Nastavuje hodnost sloupcu
*/
void shifts_colum(t_table *table)
{
	for(int i = 0; i < table->amount_rows;i++)
		for(int a = 0; a < table->col_of_rows[i].amount_cell;a++)
			table->col_of_rows[i].rows_of_cell[a].number = a;
}

int flag_irow_arow (t_table *table, char *sep, int row_work_cell,t_arguments *arg, int num_arg, int num_flag)
{	
	if(table->amount_rows == 0 || table->col_of_rows == NULL)
		return 0;

	int from_where = 0;
	int where_to = 0;
	if(add_rows(table, table->amount_rows + 1) == ERRALLOC)
		return ERRALLOC;	

	from_where = table->amount_rows - 2;
	where_to = from_where + 1; 
	if(arg[num_arg].flags[num_flag].argum == 0)
	{
		while(from_where >= row_work_cell)
		{	
			table->col_of_rows[where_to] = table->col_of_rows[from_where];
			from_where--;
			where_to--;
		}
	}	
	if(arg[num_arg].flags[num_flag].argum == 1)
	{
		while(from_where >row_work_cell)
		{	
			table->col_of_rows[where_to] = table->col_of_rows[from_where];
			from_where--;
			where_to--;
		}
		row_work_cell++;
	}	

	table->col_of_rows[row_work_cell] = create_row();
	alignment_of_cells(table, sep , row_work_cell,check_max_amount_cell(table));
	shifts_lines(table);

	return 0;
}

int flag_drow (t_table *table, int row_work_cell)
{	
	int from_where = 0;
	int where_to = 0;


	from_where = row_work_cell + 1;
	where_to = row_work_cell;
	if(row_work_cell < table->amount_rows && table->col_of_rows != NULL ) 
		deallocation_row(row_work_cell, table);

	while(from_where < table->amount_rows)
	{	
		table->col_of_rows[where_to] = table->col_of_rows[from_where];
		from_where++;
		where_to++;
	}
	if(table->amount_rows == 1 && table->col_of_rows != NULL)
	{
		free(table->col_of_rows);
		table->col_of_rows = NULL;
		table->amount_rows = 0;
	}

	if(table->amount_rows > 1)
	{
		if(add_rows(table,table->amount_rows -1) == ERRALLOC)
			return ERRALLOC;
		shifts_lines(table);
	}
	return 0;
}

int flag_icol(int col_work_cell, t_table *table, char *sep)
{	
	for(int num_str = 0; num_str < table->amount_rows; num_str++)
	{	
		add_cell(table, num_str,table->col_of_rows[num_str].amount_cell + 1,0);

		int from_where = table->col_of_rows[num_str].amount_cell - 2;
		int where_to = from_where + 1; 
	
		while(from_where >= col_work_cell)
		{	
			table->col_of_rows[num_str].rows_of_cell[where_to] = table->col_of_rows[num_str].rows_of_cell[from_where];
			from_where--;
			where_to--;
		}

		table->col_of_rows[num_str].rows_of_cell[col_work_cell] = create_cell();
		if(add_content_in_cell(table, num_str,col_work_cell, SEL) == ERRALLOC)
			return ERRALLOC;

		table->col_of_rows[num_str].rows_of_cell[col_work_cell].content[0] = sep[0];
		table->col_of_rows[num_str].rows_of_cell[col_work_cell].content[1] = '\0' ;
	}
	shifts_colum(table);
	return 0;
}

int flag_acol(int col_work_cell, t_table *table, char *sep)
{	
	for(int num_str = 0; num_str < table->amount_rows; num_str++)
	{	
		if(add_cell(table, num_str,table->col_of_rows[num_str].amount_cell + 1,0) == ERRALLOC)
			return ERRALLOC;

		int from_where = table->col_of_rows[num_str].amount_cell - 2;
		int where_to = from_where + 1; 
		
		if(num_str != 0)
			col_work_cell--;

		while(from_where > col_work_cell)
		{	
			table->col_of_rows[num_str].rows_of_cell[where_to] = table->col_of_rows[num_str].rows_of_cell[from_where];
			from_where--;
			where_to--;
		}

		col_work_cell++;

		table->col_of_rows[num_str].rows_of_cell[col_work_cell] = create_cell();
			
		if(col_work_cell == table->col_of_rows[num_str].amount_cell - 1)
		{
			table->col_of_rows[num_str].rows_of_cell[col_work_cell] = create_cell();
			if(add_end_of_cell(num_str, col_work_cell -1 , table, sep) == ERRALLOC)
				return ERRALLOC;
			if(add_content_in_cell(table, num_str,col_work_cell, SEL) == ERRALLOC)
				return ERRALLOC;
			table->col_of_rows[num_str].rows_of_cell[col_work_cell].content[0] = '\0' ;

		}
		else
		{
			if(add_content_in_cell(table, num_str,col_work_cell, SEL) == ERRALLOC)
				return ERRALLOC;
			table->col_of_rows[num_str].rows_of_cell[col_work_cell].content[0] = sep[0];
			table->col_of_rows[num_str].rows_of_cell[col_work_cell].content[1] = '\0' ;
		}
	}
	shifts_colum(table);
	return 0;	

}

int flag_dcol(int col_work_cell, t_table *table)
{	
	for(int num_str = 0; num_str < table->amount_rows; num_str++)
	{	
		if(col_work_cell == table->col_of_rows[num_str].amount_cell - 1 && table->col_of_rows[num_str].amount_cell != 1)
		{
			int len_set_str = 0;
			int befor_col = col_work_cell - 1;
			for(;table->col_of_rows[num_str].rows_of_cell[befor_col].content[len_set_str] != '\0' ;len_set_str++);
			if(add_content_in_cell(table, num_str, befor_col, len_set_str) == ERRALLOC)
				return ERRALLOC;
			table->col_of_rows[num_str].rows_of_cell[befor_col].content[len_set_str - 1] = '\0';
		}

		if(table->col_of_rows[num_str].rows_of_cell != NULL && col_work_cell < table->col_of_rows[num_str].amount_cell)
			free(table->col_of_rows[num_str].rows_of_cell[col_work_cell].content);

		int from_where = col_work_cell + 1;
		int where_to = col_work_cell; 
	
		while(from_where < table->col_of_rows[num_str].amount_cell)
		{	
			table->col_of_rows[num_str].rows_of_cell[where_to] = table->col_of_rows[num_str].rows_of_cell[from_where];
			from_where++;
			where_to++;
		}

		if(table->col_of_rows[num_str].amount_cell == 1 && table->col_of_rows[num_str].rows_of_cell != NULL)
		{	
			free(table->col_of_rows[num_str].rows_of_cell);
			table->col_of_rows[num_str].amount_cell = 0;
			table->col_of_rows[num_str].rows_of_cell = NULL;
		}

		if(table->col_of_rows[num_str].amount_cell > 1)
		{
			int amount_symbols = 0;
			if(add_cell(table, num_str,table->col_of_rows[num_str].amount_cell - 1,amount_symbols) == ERRALLOC)
				return ERRALLOC;
			shifts_lines(table);
			shifts_colum(table);
		}
		
	}
	return 0;
}

int flag_set(t_table *table, int row_work_cell, int col_work_cell, char *sep, t_arguments *arg, int num_arg, int num_flag)
{
	int len_set_str = 0;

	for(;arg[num_arg].flags[num_flag].cell_of_argum.string[len_set_str] != '\0' ;len_set_str++);
	len_set_str++;
	if(table->col_of_rows[row_work_cell].rows_of_cell != NULL)
		if(add_content_in_cell(table, row_work_cell, col_work_cell,len_set_str + 1) ==  ERRALLOC)
			return ERRALLOC;
	
	int i = 0;
	for(; arg[num_arg].flags[num_flag].cell_of_argum.string[i] != '\0'; i++)
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[i] = arg[num_arg].flags[num_flag].cell_of_argum.string[i];
	
	if(table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].number == table->col_of_rows[row_work_cell].amount_cell - 1)
	{
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[i] = '\0';
	}
	else
	{
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[i] = sep[0];
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[i + 1] = '\0';
	}
	
	return 0;

}

int flag_clear(t_table *table, int row_work_cell, int col_work_cell, char *sep)
{	
	if(table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].number == table->col_of_rows[row_work_cell].amount_cell - 1)
	{
		if(table->col_of_rows[row_work_cell].rows_of_cell != NULL)
			if(add_content_in_cell(table, row_work_cell, row_work_cell, SEL) == ERRALLOC)
				return ERRALLOC;

		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[0] = '\0';
	}
	else
	{
		if(table->col_of_rows[row_work_cell].rows_of_cell != NULL)
			if(add_content_in_cell(table, row_work_cell, row_work_cell, SEL) == ERRALLOC)
				return ERRALLOC;

		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[0] = sep[0];
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[1] = '\0';
	}
	return 0;
}
int flag_swap(t_table *table, int row_work_cell, int col_work_cell, char *sep, t_arguments *arg, int num_arg, int num_flag)
{
	t_cell help_cell;
	int flag_row = arg[num_arg].flags[num_flag].cell_of_argum.row;
	int flag_col = arg[num_arg].flags[num_flag].cell_of_argum.col;

	if(flag_row == row_work_cell && flag_col == col_work_cell)
		return 0;

	if(col_work_cell == table->col_of_rows[row_work_cell].amount_cell - 1 && flag_col != table->col_of_rows[row_work_cell].amount_cell - 1)
	{
		if(add_end_of_cell(row_work_cell, col_work_cell, table, sep) == ERRALLOC)
			return ERRALLOC;

		int len_set_str = 0;
		for(;table->col_of_rows[flag_row].rows_of_cell[flag_col].content[len_set_str] != '\0' ;len_set_str++);
		if(len_set_str == 0)
			len_set_str++;
		if(add_content_in_cell(table, flag_row, flag_col, len_set_str) == ERRALLOC)
			return ERRALLOC;
		table->col_of_rows[flag_row].rows_of_cell[flag_col].content[len_set_str - 1] = '\0';

	}

	if(col_work_cell != table->col_of_rows[row_work_cell].amount_cell - 1 && flag_col == table->col_of_rows[row_work_cell].amount_cell - 1)
	{
		if(add_end_of_cell(flag_row, flag_col, table, sep) == ERRALLOC)
			return ERRALLOC;

		int len_set_str = 0;
		for(;table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[len_set_str] != '\0' ;len_set_str++);
		if(len_set_str == 0)
			len_set_str++;
		if(add_content_in_cell(table, row_work_cell, col_work_cell, len_set_str) == ERRALLOC)
			return ERRALLOC;
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[len_set_str - 1] = '\0';

	}

	help_cell = table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell];

	table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell] = table->col_of_rows[flag_row].rows_of_cell[flag_col];

	table->col_of_rows[flag_row].rows_of_cell[flag_col] = help_cell;

	return 0;
}

void flag_sum_avg_start(t_arguments *arg, int num_flag, int num_arg, t_table *table, int row_work_cell, int col_work_cell, double *sum, char* sum_line, char *sep, int *number_pased_cell, int *cell_with_content, int *len_cells)
{	
	if(table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[0] != '\0' && table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[0] != sep[0])
	{
		(*cell_with_content)++;
	}

	if(arg[num_arg].flags[num_flag].argum == 12)
	{	
		int len_work_cell = 0;
		for(; table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[len_work_cell] != '\0'; len_work_cell++)
			(*len_cells)++;

		if(table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[len_work_cell - 1] == sep[0])
			(*len_cells)--;

	}

	if(find_number(table, row_work_cell,col_work_cell, sep) && (arg[num_arg].flags[num_flag].argum == 10 || arg[num_arg].flags[num_flag].argum == 9))
	{
		double new_num = 0.0;
		int len_str = 1;
		for(int a = 0; table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[a] != '\0' && table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[a] != sep[0]; a++)
			len_str++;

		char num[len_str];

		int len = 0;
		for(; table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[len] != '\0' && table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[len] != sep[0]; len++)
			num[len] = table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[len];
						
		num[len] = '\0';

		new_num = atof(num);

		(*sum) = (*sum) + new_num;
		(*number_pased_cell)++;
	}	
	sum_line[0] = '+';
}

int flag_sum_avg_finish(t_arguments *arg, t_table *table, int num_flag, int num_arg, double *sum, char *sum_line, char *sep, int *number_pased_cell, int *cell_with_content, int *len_cells)
{	
	int flag_row = arg[num_arg].flags[num_flag].cell_of_argum.row;
	int flag_col = arg[num_arg].flags[num_flag].cell_of_argum.col;

	int len = 0;

	if(arg[num_arg].flags[num_flag].argum == 10)
	{	
		if((*number_pased_cell) == 0)
		{
			*sum = 0;
		}
		else
		{
			*sum = (*sum) / (*number_pased_cell);
		}
	}
	else if(arg[num_arg].flags[num_flag].argum == 11)
	{
		*sum = *cell_with_content;
	}
	else if(arg[num_arg].flags[num_flag].argum == 12)
	{
		*sum = *len_cells;
	}
	sprintf(sum_line, "%g",*sum);
	for(;sum_line[len] != '\0';len++);
	len++;
	len++;

	if(add_content_in_cell(table, flag_row, flag_col, len) == ERRALLOC)
		return ERRALLOC;
	int slider = 0;
	for(; sum_line[slider] != '\0';slider++)
		table->col_of_rows[flag_row].rows_of_cell[flag_col].content[slider] = sum_line[slider];
	table->col_of_rows[flag_row].rows_of_cell[flag_col].content[slider] = '\0';

	if(table->col_of_rows[flag_row].rows_of_cell[flag_col].number != table->col_of_rows[flag_row].amount_cell - 1)
	{
		table->col_of_rows[flag_row].rows_of_cell[flag_col].content[len - 2] = sep[0];
		table->col_of_rows[flag_row].rows_of_cell[flag_col].content[len - 1] = '\0';
	}
	

	sum_line[0] = '#';
	*sum = 0.0;
	*cell_with_content = 0;
	*number_pased_cell = 0;
	*len_cells = 0;

	return 0;
}

int flag_def(t_table *table, t_arguments *arg, int row_work_cell, int col_work_cell, int num_arg, int num_flag, char *sep, t_save_list *save_list)
{	
	int len_str = 0;
	double new_num = 0.0;
	for(;table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[len_str] != '\0' ;len_str++);
	len_str++;

	if(allocation_save_list(save_list, arg[num_arg].flags[num_flag].save_number, len_str) == ERRALLOC)
		return ERRALLOC;

	int slider = 0;
	for(;table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[slider] != '\0'; slider++)
		save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[slider] = table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[slider];


	save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[slider] = '\0';

	
	if(table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].number != table->col_of_rows[row_work_cell].amount_cell - 1)
	{
		
		save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[slider -1 ] = '\0';
	}


	if(find_number(table, row_work_cell, col_work_cell, sep))
	{	
		new_num = atof(save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell);
		save_list->save[arg[num_arg].flags[num_flag].save_number].num_content_cell = new_num;
		save_list->save[arg[num_arg].flags[num_flag].save_number].number = '+';
	}

	return 0;
}	

int flag_use(t_table *table, int row_work_cell, int col_work_cell, char *sep, t_arguments *arg, int num_arg, int num_flag, t_save_list *save_list)
{
	int len_set_str = 0;
	if(save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell != NULL)
	{
		for(;save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[len_set_str] != '\0' ;len_set_str++);
	}
	else 
		return 1;
	len_set_str++;
	if(table->col_of_rows[row_work_cell].rows_of_cell != NULL)
		if(add_content_in_cell(table, row_work_cell, col_work_cell,len_set_str + 1) == ERRALLOC)
			return ERRALLOC;
	
	int i = 0;
	for(; save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[i] != '\0'; i++)
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[i] = save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[i];
	

	if(table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].number == table->col_of_rows[row_work_cell].amount_cell - 1)
	{
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[i] = '\0';
	}
	else
	{
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[i] = sep[0];
		table->col_of_rows[row_work_cell].rows_of_cell[col_work_cell].content[i + 1] = '\0';
	}

	return 0;
}	

int flag_inc(t_arguments *arg, int num_arg, int num_flag, t_save_list *save_list, char *save_line)
{
	if(save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell != NULL && save_list->save[arg[num_arg].flags[num_flag].save_number].number == '-')
	{
		free(save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell);
		save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell = NULL;	
	}

	if(save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell == NULL)
	{
		int len_str = 2;
		if(allocation_save_list(save_list, arg[num_arg].flags[num_flag].save_number, len_str) == ERRALLOC)
			return ERRALLOC;

		save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[0] = '1';
		save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[1] = '\0';

		save_list->save[arg[num_arg].flags[num_flag].save_number].num_content_cell = 1;
		save_list->save[arg[num_arg].flags[num_flag].save_number].number = '+';

	}
	else if(save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell != NULL && save_list->save[arg[num_arg].flags[num_flag].save_number].number == '+')
	{
		int len = 0;
		save_list->save[arg[num_arg].flags[num_flag].save_number].num_content_cell++;
		
		sprintf(save_line, "%g",save_list->save[arg[num_arg].flags[num_flag].save_number].num_content_cell);
		for(;save_line[len] != '\0';len++);
		len++;

		if(allocation_save_list(save_list, arg[num_arg].flags[num_flag].save_number, len) == ERRALLOC)
			return ERRALLOC;
		int slider = 0;
		for(; save_line[slider] != '\0';slider++)
			save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[slider] = save_line[slider];
		save_list->save[arg[num_arg].flags[num_flag].save_number].text_content_cell[slider] = '\0';
	}

	return 0;
}

void flag_save_set(t_save_set *save_set, t_arguments *arg, int num_arg)
{
	save_set->type = arg[num_arg].selected_cell.type;
	save_set->row_1 = arg[num_arg].selected_cell.row_1;
	save_set->col_1 = arg[num_arg].selected_cell.col_1;
	save_set->row_2 = arg[num_arg].selected_cell.row_2;
	save_set->col_2 = arg[num_arg].selected_cell.col_2;
}

/*
	ditribuje prikazy upravy nad tabulkou
	Vystup tabulka po uprave 
*/
int distributor(t_table *table, t_arguments *arg, int amount_arg, char *sep, t_save_list *save_list)
{
	double sum = 0.0;
	int number_pased_cell = 0;
	int cell_with_content = 0;
	int len_cells = 0;
	char sum_line[9] = {[0] = '0',[1] = '\0' };
	char save_line[9] = {[0] = '0',[1] = '\0' };
	bool open = false;
	t_save_set save_set;
	set_default_save_set(&save_set);
	for(int num_arg = 0; num_arg < amount_arg; num_arg++) 
	{
		int err = pre_prepares(table, arg, sep, num_arg, &save_set);
		if(err > 0)
			return err;

		for(int num_flag = 0; num_flag < arg[num_arg].amount_flags; num_flag++)
		{	
			open = true;
			int work_row = 0;
			int work_col = 0;
			int max_row = 0;
			int max_col = 0;

			dcl(&work_row, &work_col, &max_row, &max_col, arg, table, num_arg);

			for(; work_row <= max_row; work_row++ )
			{	
				work_col = arg[num_arg].selected_cell.col_1;
				if(work_col == -1)
					work_col = 0;
				
				for(; work_col <= max_col; work_col++ )
				{
					switch(arg[num_arg].flags[num_flag].argum)
					{
						case 0:
						{
							if(flag_irow_arow (table, sep, work_row, arg, num_arg, num_flag) == ERRALLOC)
								return ERRALLOC;
						}
						break;

						case 1:
						{
							if(flag_irow_arow (table, sep, work_row, arg, num_arg, num_flag) == ERRALLOC)
								return ERRALLOC;
						}
						break;

						case 2:
						{	
							if(flag_drow (table,work_row) == ERRALLOC)
								return ERRALLOC;
						}
						break;

						case 3:
						{	
							if(flag_icol( work_col, table, sep) == ERRALLOC)
								return ERRALLOC;
						}
						break;

						case 4:
						{	
							if(flag_acol( work_col, table, sep) == ERRALLOC)
								return ERRALLOC;
						}
						break;

						case 5:
						{	
							if(flag_dcol( work_col, table) == ERRALLOC)
								return ERRALLOC;
						}
						break;

						case 7:
						{
							if(flag_set (table, work_row, work_col, sep, arg, num_arg, num_flag) == ERRALLOC)
								return ERRALLOC;
						}
						break;

						case 6:
						{	
							if(flag_clear(table, work_row, work_col, sep) == ERRALLOC)
								return ERRALLOC;
						}
						break;

						case 8:
						if(arg[num_arg].flags[num_flag].cell_of_argum.row < table->amount_rows && arg[num_arg].flags[num_flag].cell_of_argum.col < table->col_of_rows[work_row].amount_cell)
						{	
							if(flag_swap(table,work_row, work_col, sep, arg, num_arg, num_flag) == ERRALLOC)
								return ERRALLOC;

						}
						break;

						case 9:
						if(arg[num_arg].flags[num_flag].cell_of_argum.row < table->amount_rows && arg[num_arg].flags[num_flag].cell_of_argum.col < table->col_of_rows[work_row].amount_cell)
						{	
							flag_sum_avg_start(arg, num_flag, num_arg, table, work_row, work_col, &sum, sum_line, sep, &number_pased_cell, &cell_with_content, &len_cells);	
						}
						break;

						case 10:
						if(arg[num_arg].flags[num_flag].cell_of_argum.row < table->amount_rows && arg[num_arg].flags[num_flag].cell_of_argum.col < table->col_of_rows[work_row].amount_cell)
						{	
							flag_sum_avg_start(arg, num_flag, num_arg, table, work_row, work_col, &sum, sum_line, sep, &number_pased_cell, &cell_with_content, &len_cells);	
						}
						break;

						case 11:
						if(arg[num_arg].flags[num_flag].cell_of_argum.row < table->amount_rows && arg[num_arg].flags[num_flag].cell_of_argum.col < table->col_of_rows[work_row].amount_cell)
						{	
							flag_sum_avg_start(arg, num_flag, num_arg, table, work_row, work_col, &sum, sum_line, sep, &number_pased_cell, &cell_with_content, &len_cells);	
						}
						break;

						case 12:
						if(arg[num_arg].flags[num_flag].cell_of_argum.row < table->amount_rows && arg[num_arg].flags[num_flag].cell_of_argum.col < table->col_of_rows[work_row].amount_cell)
						{	
							flag_sum_avg_start(arg, num_flag, num_arg, table, work_row, work_col, &sum, sum_line, sep, &number_pased_cell, &cell_with_content, &len_cells);	
						}
						break;

						case 13:
						{	
							flag_def(table,arg,work_row,work_col, num_arg, num_flag, sep, save_list);	
						}
						break;

						case 14:
						{	
							flag_use(table, work_row, work_col, sep, arg, num_arg, num_flag, save_list);	
						}
						break;

						case 15:
						if(open)
						{	
							flag_inc(arg, num_arg, num_flag, save_list, save_line);
							open = false;
						}
						break;

						case 16:
						{	
							flag_save_set(&save_set, arg, num_arg);
							
						}
						break;

					}
				}
			}

			if(sum_line[0] == '+')
			{
				if(flag_sum_avg_finish(arg, table, num_flag, num_arg, &sum, sum_line, sep, &number_pased_cell, &cell_with_content, &len_cells) == ERRALLOC)
					return ERRALLOC;
			}


		}	
	}
	return 0;
}

/*
	Odstrani prazdne sloupci
*/
int removing_excess(t_table *table, char *sep)
{
	bool empty = false;
	int work_row = 0; 
	int work_col = table->col_of_rows[0].amount_cell - 1;
	if(table->col_of_rows[0].amount_cell == 0)
	{
		for(int i = 0; i < table->amount_rows;i++)
			flag_drow (table,i);
		return 0;

	}
	for(;work_row < table->amount_rows; work_row++)
		if(table->col_of_rows[work_row].rows_of_cell[work_col].content[0] != sep[0] && table->col_of_rows[work_row].rows_of_cell[work_col].content[0] != '\0')
		{
			empty = true;
		}
	if(empty)
	{
		return 0;
	}

	if(!empty)
	{
		flag_dcol(work_col,table);
		removing_excess(table, sep);
	}

	return 0;
}

/*
	Vypisuje tabulku do souboru 
*/
int writing(t_table *table, char *file_name, char *sep)
{	
	int max_cell = check_max_amount_cell(table);
	shifts_colum(table);
	for(int i = 0; i < table->amount_rows; i++)
	{
		alignment_of_cells(table, sep, i, max_cell);
	}
	if(table->col_of_rows != NULL && table->col_of_rows[0].rows_of_cell != NULL && table->col_of_rows[0].rows_of_cell[0].content != NULL)
		removing_excess(table, sep);

	FILE *f = NULL;

	f = fopen(file_name,"w");
	if(f == NULL)
	{
		fprintf(stderr, "CHYBA: Soubor ne může být otevřen\n");
		return ERROPEN;
	}

	for(int i = 0; i < table->amount_rows;i++)
	{	
		for(int a = 0; a < table->col_of_rows[i].amount_cell; a++)
		{	
			fprintf(f,"%s",table->col_of_rows[i].rows_of_cell[a].content);
		}
		fprintf(f,"%c",'\n');
	}	

	fprintf(f,"%c",'\0');

	fclose(f);

	return 0;
}

void zero_row_deletion(t_table *table)
{
	if(table->amount_rows == 1 && table->col_of_rows[0].amount_cell == 1 && table->col_of_rows[0].rows_of_cell[0].content[0] == '\0')
	{
		free(table->col_of_rows[0].rows_of_cell[0].content);
		table->col_of_rows[0].rows_of_cell[0].content = NULL;
		free(table->col_of_rows[0].rows_of_cell);
		table->col_of_rows[0].rows_of_cell = NULL;
		table->col_of_rows[0].amount_cell = 0;
		free(table->col_of_rows);
		table->col_of_rows = NULL;
		table->amount_rows = 0;
	}
}

void deallocation_save_list(t_save_list *save_list)
{
	for(int i = 0; i < save_list->amount_saves;i++)
	{	
		if(save_list->save[i].text_content_cell != NULL)
			free(save_list->save[i].text_content_cell);

		save_list->save[i].text_content_cell = NULL;
		save_list->save[i].num_content_cell = 0;
		save_list->save[i].number = '-';
	}
}	

int main(int argc, char **argv)
{	
	setlocale(LC_ALL,"Cz");

	int amoun_of_selection_cell = 0;
	int select_slider = 0;
	int amount_separators = 0;
	int start_number_flags = 0;
	int file_name_location = 0;
	long int cursor_position =  0;
	int amount_symbol_in_line = 0;
	char *str_bufer = NULL;
	int amount_colls_line = 1;
	bool konec = true;
	int amount_rows_table = 0;
	int err_aloc = 0;
	int err_read_f =0;
	int err_dis =0;


	t_stdin_arg arguments_stdin;
	t_table table;
	set_default_table(&table);

	t_save_list save_list;
	set_default_save_list(&save_list);

	if(finde_quantity_of_separate(&amount_separators,argv,argc))
	{
		fprintf(stderr, "CHYBA: Nespravně zadane udaje v retezce delim\n");
		return 104;
	} 

	if(argc < 3)
	{
		fprintf(stderr, "CHÝBA: Nespravně zadane udaje \n");
		return ERRARC;
	}
	char separators[amount_separators];

	//Volání funkce zaplnění řetězce rozdělovačů
	writes_separators(argv,amount_separators, separators, &start_number_flags);

	//Zaplneni file name
	char file_name[find_leng_file_name(start_number_flags, &file_name_location, argc,argv) + EL];
	filling_file_name(file_name, argv, file_name_location);

	//Zaplneni argumentu
	if(filling_arr_arguments_argv(argv, start_number_flags, &arguments_stdin) == ERRALLOC)
	{	
		fprintf(stderr, "CHÝBA: Neprovedla se allokacia \n");
		deallocation_argum_stdin(arguments_stdin.amount, &arguments_stdin);
		return ERRALLOC;
	}
	//Kontrola argumentu
	if(check_flags(&arguments_stdin,&amoun_of_selection_cell) == ERRARG)
	{
		fprintf(stderr, "CHÝBA: Nespravně zadane udaje \n");
		deallocation_argum_stdin(arguments_stdin.amount, &arguments_stdin);
		return ERRARG;
	}
	t_arguments sel_arguments[amoun_of_selection_cell];

	//Zapolneni strucktury argumentu
	for(int i = 0; i < amoun_of_selection_cell; i++)
		sel_arguments[i] = logic_of_loading_arguments(&arguments_stdin,&select_slider, &err_aloc);

	if(err_aloc)
	{
		for(int i = 0; i <amoun_of_selection_cell; i++)
		deallocation_sel_arguments(&sel_arguments[i]);
	}

	for(int i = 0; i < amoun_of_selection_cell; i++)
		programm_def_selected_arguments(&sel_arguments[i]);

	//Ciklus nacteni z souboru
	do
	{
		amount_symbol_in_line = 0;
		amount_colls_line = 1;
		str_bufer = filling_stringbuf(str_bufer,file_name,&amount_symbol_in_line,&cursor_position,&konec, &err_read_f);
		
		if(str_bufer != NULL)
		{
			amount_rows_table++;
			replaces_the_separator(str_bufer, separators, &amount_colls_line);
			if(err_read_f != 0)
				break;
			if(allocation_table(&table,amount_rows_table,amount_colls_line) == ERRALLOC)
			{
				deallocation_argum_stdin(arguments_stdin.amount, &arguments_stdin);

				for(int i = 0; i <amoun_of_selection_cell; i++)
				{
					deallocation_sel_arguments(&sel_arguments[i]);
				}

				deallocation_table(&table);
				free(str_bufer);
				return ERRALLOC;

			}

			if(filling_table(&table,str_bufer,separators) == ERRALLOC)
			{
				err_read_f++;
				break;
			}
			free(str_bufer);
			str_bufer = NULL;
		}

	}while(konec);

	if(err_read_f != 0)
	{
		fprintf(stderr, "CHYBA: Soubor nemůže být otevřen\n");
		deallocation_argum_stdin(arguments_stdin.amount, &arguments_stdin);

		for(int i = 0; i <amoun_of_selection_cell; i++)
		{
			deallocation_sel_arguments(&sel_arguments[i]);
		}

		deallocation_table(&table);
		return ERROPEN;
	}
	//Zarovnani radku
	int max_cell = check_max_amount_cell(&table);
	programm_def_number_rows(&table);
	for(int i = 0; i < table.amount_rows; i++)
	{
		alignment_of_cells(&table, separators, i, max_cell);
	}

	// for(int i = 0; i < amoun_of_selection_cell; i++)
	// {	
	// 	printf("selected argument: \n \t type = %d  [%d,%d,%d,%d], %s, \n",sel_arguments[i].selected_cell.type, sel_arguments[i].selected_cell.row_1,sel_arguments[i].selected_cell.col_1,sel_arguments[i].selected_cell.row_2,sel_arguments[i].selected_cell.col_2,sel_arguments[i].selected_cell.str);
	// 	for(int a = 0; a < sel_arguments[i].amount_flags; a++)
	// 	{
	// 		printf("flag = %d cell =[%d,%d], string = %s save_number =  %d\n",sel_arguments[i].flags[a].argum,sel_arguments[i].flags[a].cell_of_argum.row,sel_arguments[i].flags[a].cell_of_argum.col,sel_arguments[i].flags[a].cell_of_argum.string,sel_arguments[i].flags[a].save_number);
	// 	}
	// }



	//Zmena tabulky
	err_dis = distributor(&table, sel_arguments,amoun_of_selection_cell,separators, &save_list);

	if(err_dis == ERRARG)
	{
		fprintf(stderr, "CHÝBA: Nespravně zadane udaje \n");
		return ERRARG;
	}

	if(err_dis == ERRALLOC)
	{
		deallocation_argum_stdin(arguments_stdin.amount, &arguments_stdin);

		for(int i = 0; i <amoun_of_selection_cell; i++)
		{
			deallocation_sel_arguments(&sel_arguments[i]);
		}
		deallocation_save_list(&save_list);
		deallocation_table(&table);
	}

	//Odstranni nuleveho radku
	zero_row_deletion(&table);

	//Vystup do souboru
	int err_w =writing(&table, file_name, separators);

	// for(int i =0; i < table.amount_rows; i++)
	// {	
	// 	for(int a = 0; a < table.col_of_rows[i].amount_cell;a++)
	// 		printf("%s",table.col_of_rows[i].rows_of_cell[a].content);

	// 	printf("\n");
	// }	
	

	//Deallocacia
	deallocation_argum_stdin(arguments_stdin.amount, &arguments_stdin);

	for(int i = 0; i <amoun_of_selection_cell; i++)
		deallocation_sel_arguments(&sel_arguments[i]);

	deallocation_table(&table);
	deallocation_save_list(&save_list);

	if(err_w > 0)
		return ERROPEN;

	return 0;
} 