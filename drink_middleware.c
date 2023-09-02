/**
 * @file drink_middleware.c
 * @brief Drink middleware function, read the data from the .txt file.
 * Use the linked list function operate the drink data.
 * @date 2021-12-08
 * 
 * 
 * 
 */
#include "drink_middleware.h"
#include "link.h"
#include <stdlib.h>
#include "account.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "account_middleware.h"
#include "input_support.h"

extern link_t * account_link;

link_t * drink_link;
link_t * coffee_type_link;
link_t * milk_type_link;
link_t * ice_type_link;

drink_t *choose_drink;
drink_t *choose_option;
link_t * purchaser_info;
order_info_t order_info;


/**
 * @brief insert new drink into linked list
 * 
 * @param p 
 * @param buffer 
 * @return link_t* 
 */
link_t * insert_drink(link_t * p, drink_t * buffer){
	link_t * temp = p;
	drink_t *data;
	int i = 0;
	if (buffer->name[0] == '\0'){/*Prevent the invalid data*/
		return p;
	}

	while (temp->next){
		temp = temp->next;
		data = temp->point;
		if (data->name[0] != '0' && *(data->name) < *(buffer->name)){

		}
		else{
			break;
		}
	}
	drink_t *save = (drink_t *)malloc(sizeof(drink_t));
	memcpy(save, buffer, sizeof(drink_t));
	return  insert_link(temp, save);
}

/**
 * @brief show all drink and its information
 * 
 * @param head : drink list head
 * @param a : row of highlight
 * @return link_t* : none
 */
link_t *show_all_drink(link_t *head,int a){
	link_t *temp;
	drink_t *data;
	int i = 0;
	system("cls");
	temp = head;
	temp = temp->next;
	for (i = 1; i <= calc_link_length(head); i++){
		data = temp->point;
		if (a == i){
			printf("\033[41m%20s           ", data->name);
			printf("$%.1f\033[0m\n", data->price);
		}
		else{
			printf("%20s           ", data->name);
			printf("$%.1f\033[0m", data->price);
			printf("\n");
		}
		temp = temp->next;
	}
}
/**
 * @brief show the option choose interface
 * 
 * @param head : option linked list header
 * @return link_t* : pointer of option
 */
link_t *show_option_choose_interface(link_t *head){
	char ch;
	int arrow_pos=1;
	link_t *temp = NULL;
	drink_t *data;
	system("cls");
	if (calc_link_length(head)==0)
	{
		/*no content*/
		printf("No content");
		while (1)
		{
			if (getch()) return NULL;
		}
	}
	while (1){
		show_all_drink(head, arrow_pos);
		printf("Press 'Enter' to select order drink\n");
		printf("Press '0' to return\n");
		switch (ch = getch())
		{
		case 72:
		/*move highlight up*/
			if (arrow_pos > 1){
				arrow_pos--;
			}
			break;
		case 80:
		/*move highlight down*/
			if (arrow_pos < calc_link_length(head)){
				arrow_pos++;
			}
			break;
		case '0':
			return NULL;
			break;
		case 13:
		/*'Enter' select this option*/
			temp = get_number_link_point(head, arrow_pos);
			return temp;
		default:
			break;
		}
	}
}
/**
 * @brief show option edit interface
 * 
 * @param head 
 * @return link_t : none
 */
link_t show_option_edit_interface(link_t *head){
	char ch;
	int arrow_pos = 1;
	link_t *temp;
	drink_t *data;
	system("cls");
	if (calc_link_length(head) == 0){
		printf("No content");
		while (1){
			if (getch()) return;
		}
	}
	while (1){
		system("cls");
		show_all_drink(head, arrow_pos);
		printf("Press 'Enter' to select option which want to be change\n");
		printf("Press '0' to return\n");
		switch (ch = getch()){
		case 72:
			if (arrow_pos > 1){
				arrow_pos--;
			}
			break;
		case 80:
			if (arrow_pos < calc_link_length(head)){
				arrow_pos++;
			}
			break;
		case '0':
			return;
			break;
		case 13:
			temp = get_number_link_point(head, arrow_pos);
			edit_drink_t(temp, head, "drink.txt");
			save_option_to_file();
		default:
			break;
		}
	}
}

/**
 * @brief show the user order drink interface
 * 
 * @return int : state of continue to buy
 */
int oredr_drink_interface(void){
	int arrow_pos = 1;
	char ch;
	int return_state;
	link_t *temp;
	while (1){
		while (1){
			choose_drink == NULL;
			show_all_drink(drink_link, arrow_pos);
			memset(&order_info, '\0', sizeof(order_info_t));
			printf("Press 'Enter' to select order drink");
			switch (ch = getch()){
			case 72:
				if (arrow_pos > 1){
					arrow_pos--;
				}
				break;
			case 80:
				if (arrow_pos < calc_link_length(drink_link)){
					arrow_pos++;
				}
				break;
			case '0':
				return 0;
				break;
			case 13:
				temp = get_number_link_point(drink_link, arrow_pos);
				choose_drink = temp->point;
				/*update buying information*/
				strcpy(&order_info.order, choose_drink->name);
				order_info.order_pay += choose_drink->price;
				return_state=show_customer_option_interface();
				if (!return_state||return_state==1){
					break;
				}
				else if (return_state = 2){
					return 2;
				}
				break;
			default:
				break;
			}
		}

	}
}
/**
 * @brief add a new drink
 * 
 */
void add_new_drink(){
	link_t *temp;
	system("cls");
	printf("Add new drink\n");
	printf("Input new drink name:");
	drink_t buffer;
	fflush(stdin);
	get_20_char(buffer.name);
	while (1){
		temp = search_drink_name(drink_link,buffer.name);
		if (temp == NULL){
			break;
		}
		printf("Order name is exist\n");
		if (!input_again(buffer.name, "input your order name again:", 20, get_char)){
			return;
		}
	}
	printf("Input price:");
	float amount = 0;
	input_float_num(&amount, 1);
	while (1){
		if (amount>0)
		{
			break;
		}
		printf("Please enter a positive number\n");
		/*ask input again*/
		if (!input_again(&amount, "Input amount again:", 20, input_float_num)){
			amount = 0;
			return;/*not input*/
		}
	}
	buffer.price = amount;
	buffer.sales = 0;
	insert_new_element(drink_link, &buffer,sizeof(drink_t));
	save_file_name(drink_link, sizeof(drink_t), "drink.txt");
	while (1){
		printf("Add successfully\n");
		printf("Press any key to return to the previous menu");
		if (getch())return 0;
	}
}


/**
 * @brief search drink name from data
 * 
 * @param p : header
 * @param name 
 * @return link_t* : pointer of linked list element
 */
link_t *search_drink_name(link_t *p, char *name){
	int i = 0;
	drink_t *data;
	link_t *temp = p;
	while (temp->next){
		temp = temp->next;
		data = temp->point;
		if (strcmp(data->name, name) == 0) return temp;
	} 
	return NULL;
}
/**
 * @brief add new option
 * 
 * @param head 
 */
void add_new_option(link_t  *head){
	system("cls");
	printf("Add new option\n");
	printf("Input new option name:");
	drink_t buffer;
	fflush(stdin);
	get_20_char(buffer.name);
	printf("Input price:");
	float amount = 0;
	input_float_num(&amount, 1);
	while (1){
		if (amount>=0)
		{
			break;
		}
		printf("Please enter a positive number\n");
		/*ask input again*/
		if (!input_again(&amount, "Input amount again:", 20, input_float_num)){
			amount = 0;
			return;/*not input*/
		}
	}
	buffer.price = amount;
	insert_new_element(head, &buffer, sizeof(drink_t));
	save_option_to_file();
	while (1){
		printf("Add successfully\n");
		printf("Press any key to return to the previous menu");
		if (getch())return 0;
	}
}
/**
 * @brief save option to file, save the three linked list to the .txt file
 * 
 */
void save_option_to_file(){
	FILE *option_file;
	int length;
	option_file = fopen("option.txt", "w+");
	save_file_pointer(coffee_type_link, sizeof(drink_t), option_file);
	save_file_pointer(milk_type_link, sizeof(drink_t), option_file);
	save_file_pointer(ice_type_link, sizeof(drink_t), option_file);
	fclose(option_file);
}
/**
 * @brief read option from file, read the three linked list to the .txt file
 * 
 */
void read_option_to_file(){
	FILE *option_file;
	option_file = fopen("option.txt", "a+");
	read_file_pointer(coffee_type_link, sizeof(drink_t), option_file,insert_link);
	read_file_pointer(milk_type_link, sizeof(drink_t), option_file, insert_link);
	read_file_pointer(ice_type_link, sizeof(drink_t), option_file, insert_link);
	fclose(option_file);
}
/**
 * @brief show the manger add new option interface
 * 
 */
void manager_add_new_option_interface(){
	char ch;
	int return_state;
	link_t *temp;
	drink_t *data;
	while (1){
		system("cls");
		printf("Select the type of option want to add\n");
		printf("1. Type of coffee bean\n");
		printf("2. Type of milk\n");
		printf("3. Type of hot or cold\n");
		printf("0. Return");
		switch (ch = getch())
		{
		case '1':
			add_new_option(coffee_type_link);
			break;
		case'2':
			add_new_option(milk_type_link);
			break;
		case'3':
			add_new_option(ice_type_link);
			break;
		case'0':
			return;
		default:
			break;
		}
	}
}

/**
 * @brief show the manager edit option interface
 * 
 */
void manager_edit_option_interface(){
	char ch;
	int return_state;
	link_t *temp;
	drink_t *data;
	while (1)
	{
		system("cls");
		printf("Select the type of option want to add\n");
		printf("1. Type of coffee bean\n");
		printf("2. Type of milk\n");
		printf("3. Cold and hot\n");
		printf("0. Return");
		switch (ch = getch())
		{
		case '1':
			show_option_edit_interface(coffee_type_link);
			break;
		case'2':
			show_option_edit_interface(milk_type_link);
			break;
		case'3':
			show_option_edit_interface(ice_type_link);
			break;
		case'0':
			return;
		default:
			break;
		}
	}
}
/**
 * @brief show the customer option interface
 * 
 * @return int : continue buying state
 */
int show_customer_option_interface(){
	char ch;
	int return_state;
	link_t *temp;
	drink_t *data;

	while (1)
	{
		system("cls");
		printf("Select the custom option\n");
		printf("1. Type of coffee bean\n");
		printf("2. Type of milk\n");
		printf("3. Cold and hot\n");
		printf("4. Extra shot of sugar\n");
		printf("5. Extra shot of coffee\n");
		printf("6. Check out\n");
		printf("0. Return\n");
		switch (ch=getch())
		{
		case '1':
			temp=show_option_choose_interface(coffee_type_link);
			if (temp != NULL){
				/*update buying information*/
				data = temp->point;
				strcpy(order_info.coffee_bean, data->name);
				order_info.coffee_bean_pay = data->price;
			}
			break;
		case'2':
			temp=show_option_choose_interface(milk_type_link);
			if (temp != NULL){
				/*update buying information*/
				data = temp->point;
				strcpy(order_info.milk, data->name);
				order_info.milk_pay = data->price;
			}
			break;
		case'3':
			temp=show_option_choose_interface(ice_type_link);
			if (temp != NULL){
				/*update buying information*/
				data = temp->point;
				strcpy(order_info.ice, data->name);
				order_info.ice_pay = data->price;
			}
			break;
		case'4':
			more_sugar();
			break;
		case'5':
			more_coffee();
			break;
		case'6':
			/*return*/
			return_state = settlement_interface();
			if (!return_state){
				break;
			}
			else if (return_state == 1){
				return 1;
			}
			else if (return_state == 2){
				return 2;
			}
			break;
		case'0':
		return 0;
		default:
			break;
		}

	}
}
/**
 * @brief allow user add more sugar
 * 
 */
void more_sugar(){
	system("cls");
	printf("Enter the amount of sugar you want to add\n");
	printf("Sugar number(0-3): ");
	input_inter_num(&order_info.suger,0);
	while (1){
		if (order_info.suger >=0 && order_info.suger<=3){
			/*set successfully*/
			printf("Add %d suger\n", order_info.suger);
			printf("Press any key to return");
			while (1){
				if (getch())
					return;
			}
		}
		printf("Sugar number should between 0 and 3\n");
		if (!input_again(&order_info.suger, "Enter the amount of sugar you want to add(0-3):", 0, input_inter_num)){
			return;
		}
	}
}
/**
* @brief allow user add more sugar
*
*/
void more_coffee(){
	system("cls");
	printf("Enter the amount of coffee you want to add\n");
	printf("Coffee number(0-3): ");
	input_inter_num(&order_info.suger, 0);
	while (1){
		if (order_info.suger >= 0 && order_info.suger <= 3){
			/*set successfully*/
			printf("Add %d coffee\n", order_info.suger);
			printf("Press any key to return");
			while (1){
				if (getch())
					return;
			}
		}
		printf("Coffee number should between 0 and 3\n");
		if (!input_again(&order_info.suger, "Enter the amount of coffee you want to add(0-3): ", 0, input_inter_num)){
			return;
		}
	}
}
/**
 * @brief update the order history
 * 
 * @param customer : the customer needed to be update
 */
void update_oredr_history(link_t * customer){
	user_acconut_t *data;
	data=customer->point;
	memcpy(&data->History[4], &data->History[3], sizeof(drink_t));
	memcpy(&data->History[3], &data->History[2], sizeof(drink_t));
	memcpy(&data->History[2], &data->History[1], sizeof(drink_t));
	memcpy(&data->History[1], &data->History[0], sizeof(drink_t));
	memcpy(&data->History[0], choose_drink, sizeof(drink_t));
	save_file_name(account_link, sizeof(user_acconut_t), "account.txt");
}
/**
 * @brief show the sale data for all the coffee drink
 * 
 */
void show_sale_data(){
	drink_t *data;
	link_t * temp;
	temp = drink_link;
	system("cls");
	if (temp->next==NULL){
		/*no coffee drink*/
		printf("No drink information\n");
		printf("Press any key to return");
		while (1){
			if (getch()) return;
		}
	}
	printf("%20s","Name");
	printf("     Sales\n");
	while (temp->next){
		temp = temp->next;
		data = temp->point;
		printf("%20s", data->name);
		printf("     %5d\n", data->sales);
	}
	printf("Press any key to return");
	while (1){
		if (getch()) return;
	}
}





