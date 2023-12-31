#include "account.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "link.h"
#include "account_middleware.h"
#include "input_support.h"
#include "drink_middleware.h"

extern link_t * drink_link;
extern link_t * account_link;
extern link_t * clerk_link;
extern link_t * logged_clerk_link;
extern order_info_t order_info;
extern link_t * purchaser_info;




/*
return 0          back to Superior Interface
return 1          Continue to buy
return 2          Exit account
*/

/**
 * @brief User registration functions
 * 
 */
void add_new_customer(void){
	while (1){
		user_acconut_t buffer;
		link_t *new;
		user_acconut_t *new_data;
		int n = 0;
		buffer.balance = 0;
		buffer.ID = 0;
		memset(buffer.History, '\0', sizeof(drink_t)*5);
		printf("Type new customer's name: ");
		get_char(buffer.name,20);/*get user name*/
		if (search_name(account_link, buffer.name) != NULL){
			printf("Username exists\n");
			printf("Type new customer's name: ");
			while (1){
				get_char(buffer.name,20);
				if (search_name(account_link, buffer.name) != NULL){
					printf("Username exists\n");
					printf("Type new customer's name: ");
				}
				else break;/*not exist, break*/
			}
		}
		printf("Type new customer's telephone: ");
		input_char_number(buffer.phone_num,sizeof(buffer.phone_num));
		new = insert_new_customer(account_link, &buffer, sizeof(user_acconut_t));/*insert it into account link and get ID*/
		new_data = new->point;
		save_file_name(account_link, sizeof(user_acconut_t), "account.txt");/*save new data to .txt*/
		printf("New user registration succeeded!\n");
		printf("Name: %s\n", new_data->name);
		printf("ID: %010d\n", new_data->ID);
		printf("Telephone number: %s\n", new_data->phone_num);
		while (1){
			printf("Press any key to return to the previous menu");
			if (getch())return 0;
		}
	}
}
void add_new_manager(void){
	while (1){
		manager_account_t *buffer = malloc(sizeof(manager_account_t));
		link_t *new;
		int n = 0;
		printf("Type new manager's name: ");
		get_char(buffer->name, 20);/*get user name*/
		if (search_name(clerk_link, buffer->name) != NULL){
			printf("Username exists\n");
			printf("Type new manager's name: ");
			while (1){
				get_char(buffer->name, 20);
				if (search_name(account_link, buffer->name) != NULL){
					printf("Username exists\n");
					printf("Type new manager's name: ");
				}
				else break;/*not exist, break*/
			}
		}
		printf("Type new manager's password: ");
		get_20_char(buffer->password, sizeof(buffer->password));
		insert_link(clerk_link, buffer);
		save_file_name(clerk_link, sizeof(manager_account_t), "clerk_data.txt");/*save new data to .txt*/
		printf("New user registration succeeded!\n");
		while (1){
			printf("Press any key to return to the previous menu");
			if (getch())return 0;
		}
	}
}
/**
 * @brief show the clerk login interface
 * 
 */
void clerk_log_interface(void){
	manager_account_t buffer;
	char password[20];
	printf("\nUser name:");
	get_char(buffer.name,20);
	link_t *state;
	manager_account_t *data;
	int comirfm_state = 1;
	char ch;
		while (1){
			state = search_clerkdata_name(clerk_link, buffer.name);
			if (state == NULL){
				printf("User name not found\n");
			}
			else break;/*find name break*/

			/*ask input again*/
			if (!input_again(buffer.name, "input your user name again:", 20, get_char)){
				return;/*not input*/
			}
		}
	data = state->point;
	printf("Password:");
	input_char_number(password,20);
	while (1){
		if (strcmp(data->password, password)){
			printf("Password wrong!\n");
		}
		else {
			/*login successfully*/
			logged_clerk_link = state;
			inner_clerk_window();
			return;
		}
		if (!input_again(password, "Password:", 20, input_char_number)){
			return;
		}
	}
}
/**
 * @brief change manager password function
 * 
 */
void clerk_change_password(void){
	system("cls");
	manager_account_t *data;
	data = logged_clerk_link->point;
	printf("Input your new password:");
	input_char_number(data->password,20);
	printf("Change the password successfully\n");
	printf("Press any key to return");
	save_clerk_info();
	while (1){
		if (getch()){
			return;
		}
	}
}
/**
 * @brief customer login interface
 * 
 */
void customer_log_interface(void){
	purchaser_info = NULL;
	system("cls");
	printf("Input the username：");
	manager_account_t buffer;
	char phone_num[20];
	link_t *temp;
	user_acconut_t *data;
	int error_state=1;
	get_char(buffer.name,20);
	char ch;
	while (1){
		temp = search_name(account_link, buffer.name);
		if (temp == NULL){
			printf("Don't find user name\n");
		}
		else break;
		/*not exist, break*/
		if (!input_again(buffer.name, "input your user name again:", 20, get_char)){
			return;
		}
	}
	data = temp->point;
	printf("Phone number:");
	input_char_number(phone_num,20);
	while (1){
		if (strcmp(data->phone_num, phone_num)){
			printf("Phone number wrong\n");
		}
		else {
			purchaser_info = temp;
			printf("Login successfully\n");
			printf("Press any key to continue.");
			while (1) if (getch()) break;
			inner_customer_windows();
			/*login successfully*/
			return;
		}
		/*ask user whether input again*/
		if (!input_again(phone_num, "input your user phone number again:", 20, input_char_number)){
			return;
		}
	}
}
/**
 * @brief show the manager inner window
 * 
 */
void inner_clerk_window(void){
	char ch;
	while (1){
		system("cls");
	printf("Welcome to use\n");
	printf("1.Change customer information\n");
	printf("2.Change menu\n");
	printf("3.Change the password\n");
	printf("4.View sales\n");
	printf("5.Resistor a new manager account\n");
	printf("0.Log out\n");
	switch (ch = getch()){
	case '1':
		change_customer_info();
		system("cls");
		break;
	case'2':
		change_memu_info();
		break;
	case '3':
		clerk_change_password();
		break;
	case'4':
		show_sale_data();
		break;
	case'5':
		add_new_manager();
		break;
	case'0':
		logged_clerk_link = NULL;/*logout*/
		return;
	default:
		break;
	}
	}
}

/**
 * @brief show the  change customer information  interface
 * 
 */
void change_customer_info(void){
	char ch;
	while (1){
		system("cls");
		printf("1.Add customer information.\n");
		printf("2.Edit/Delete customer information.\n");
		printf("0.Return\n");
		switch (ch = getch()){
		case '1':
			add_new_customer();
			break;
		case '2':
			edit_account();
			break;
		case'0':
			return 0;
		default:
			break;
		}
	}
}
/**
 * @brief show user login interface
 * 
 */
void show_login_interface(){
	int error_state = 1;
	char ch1;
	while (1){
		system("cls");
		printf("1. Shop manager log in\n");
		printf("2. Customer log in\n");
		printf("0. Return");
		switch (ch1 = getch())
		{
		case'1':
			clerk_log_interface();
			purchaser_info == NULL;/*log out*/
			break;
		case'2':
			customer_log_interface();
			logged_clerk_link == NULL;/*log out*/
			break;
		case'0':
			return;
		default:
			break;
		}
	}
}
/**
 * @brief show each account and its information
 * 
 * @param a : the row which the cursor needed to show
 */
void show_all_account(int a){
	link_t *temp;
	user_acconut_t *data;
	int i = 0;
	temp = account_link;
	temp = temp->next;
	system("cls");
	printf("%20s       ", "Name");
	printf("%15s", "Phone number");
	printf("%10s", "ID");
	printf("%15s\n", "Balance");/*print the title*/
	for (i = 1; i <= calc_link_length(account_link); i++){
		/*printf all the data*/
		data = temp->point;
		if (a == i){
			/*highlight*/
			printf("\033[41m%20s", data->name);
			printf("%20s    ", data->phone_num);
			printf("%010d", data->ID);
			printf("      %.1f\033[0m\n", data->balance);
		}
		else{
			printf("%20s", data->name);
			printf("%20s    ", data->phone_num);
			printf("%010d", data->ID);
			printf("      %.1f", data->balance);
			printf("\n");
		}
		temp = temp->next;
	}
}
/**
 * @brief search account from the linked list and edit
 * 
 */
void search_account(){
	char name[20];
	char ch;
	int confirm_state = 0;
	link_t *temp;
	system("cls");
	show_all_account(-1);/*no highlight*/
	printf("Search Name:");
	get_char(name,20);
	user_acconut_t *data;
	temp = search_name(account_link, name);

	if (temp == NULL){
		printf("Not found name");
		Sleep(2000);
	}
	else {
		edit_account_content(temp);
	}
}
/**
 * @brief deletes customer element from linked list
 * 
 * @param p : need to be deleted
 * @return int : delete state
 */
int delet_account(link_t *p){
	int confirm_state = 1;
	char ch;
	link_t *temp = p;
	printf("Confirm deletion(y/n)\n");
	while (1)
	{
		switch (ch = getch())
		{
		case'y':
		/*choose delete*/
			delet_account_link(account_link, temp);
			save_file_name(account_link, sizeof(user_acconut_t), "account.txt");
			printf("Successful delet!\nPress 0 to return");
			while (getch() != '0');
			return confirm_state;
			break;
		case'n':
			confirm_state = 0;
			return confirm_state;
			break;
		}
	}
}
/**
 * @brief show edit interface
 * 
 * @return int 
 */
int edit_account(void){
	int arrow_pos = 1;
	int ch;
	link_t *temp;
	while (1){

		system("cls");
		while (1){
			if (account_link->next != NULL){
				show_all_account(arrow_pos);
				/*show all the user information*/
				printf("Press 'e' to change the selected name\n");
				printf("Press 'd' to delete the selected name\n");
				printf("If you want to search account you can press 's' \n");
				switch (ch = getch())
				{
				case 72:
				/*arrow_pos move up*/
					if (arrow_pos > 1){
						arrow_pos--;
					}
					break;
				case 80:
				/*arrow_pos move down*/
					if (arrow_pos < calc_link_length(account_link)){
						arrow_pos++;
					}
					break;
				case 's':
					search_account();/*search account form linked list*/
					break;
				case '0':
					return 0;
					break;
				case 'e':
				/*get the arrow_pos corresponding element*/
					temp = get_number_link_point(account_link, arrow_pos);
					edit_account_content(temp);
					system("cls");
					printf("Press e to change the selected name\n");
					printf("If you want to search account you can press 's' \n");
					break;
				case 'd':
				/*get the arrow_pos corresponding element*/
					temp = get_number_link_point(account_link, arrow_pos);
					delet_account(temp);
				default:
					break;
				}
			}
			else{
				system("cls");
				printf("No content\n");
				printf("Press 0 to return\n");
				while (getch() != '0');
				return;
			}
		}
	}
}
/**
 * @brief edit one user account information
 * 
 * @param p 
 */
void edit_account_content(link_t *p){
	link_t *temp = p;
	user_acconut_t *data;
	data = p->point;
	system("cls");
	printf("%20s", data->name);
	printf("%20s    ", data->phone_num);
	printf("%010d     ", data->ID);
	printf("%f", data->balance);
	printf("\n");
	printf("Press 'n' to edit name\npress 'p' to edit telephone number\npress '0' to return\npress 'c' to recharge\n");
	char ch;
	while (1){
		switch (ch = getch()){
		case'n':
			printf("Type new name:");
			get_char(data->name,20);
			save_file_name(account_link, sizeof(user_acconut_t), "account.txt");
			printf("Edit name successfully!");
			printf("Press 0 to return");
			while (getch() != '0');
			return;
			break;
		case'p':
			printf("Type new number:");
			/*get new number*/
			input_char_number(data->phone_num,sizeof(data->phone_num));
			save_file_name(account_link, sizeof(user_acconut_t), "account.txt");
			printf("\nEdit  successfully!");
			printf("Press 0 to return");
			while (getch() != '0');
			return;
			break;
		case'c':
			printf("Enter the recharge amount:");
			/*get new amount*/
			float amount=0;
			input_float_num(&amount, sizeof(amount));
			while (1){
				if (amount>0)
				{
					break;
				}
				printf("\033[31mPlease enter a positive number\n\033[0m");
				/*ask input again*/
				if (!input_again(&amount, "Input amount again:", 20, input_float_num)){
					amount = 0;
					break;/*not input*/
				}
			}
			data->balance += amount;
			save_file_name(account_link, sizeof(user_acconut_t), "account.txt");

			return;
			break;
		case'0':
			return;
			break;
		default:
			break;

		}
	}
}
/**
 * @brief show inner customer windows
 * 
 */
void inner_customer_windows(){
	char ch;
	while (1){
		system("cls");
		printf("1.Order\n");
		printf("2.Show order history\n");
		printf("3.Balance recharge\n");
		printf("0.Log out");
		switch (ch=getch()){
		case '1':
			oredr_drink_interface();
			break;
		case '2':
			show_order_history();
			break;
		case '3':
			balacne_recharge_interface();
			break;
		case '0':
			purchaser_info = NULL;
			return;
			break;
		default:
			break;
		}
	}
}

/**
 * @brief show the balacn recharge interface
 * 
 */
void balacne_recharge_interface(){
	char ch;
	user_acconut_t *data;
	system("cls");
	printf("Enter recharge amount:");
	data = purchaser_info->point;

	float amount = 0;
	input_float_num(&amount, sizeof(amount));
	while (1){
		if (amount>0)
		{
			break;
		}
		printf("Please enter a positive number\n");
		/*ask input again*/
		if (!input_again(&amount, "Input amount again:", 20, input_float_num)){
			amount = 0;
			break;/*not input*/
		}
	}
	data->balance += amount;
	save_file_name(account_link, sizeof(user_acconut_t), "account.txt");
	printf("Recharge successfully\n");
	while (1){
		printf("Press any key to return to the previous menu");
		if (getch())return;

	}
}




