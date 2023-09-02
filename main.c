/**
 * @file main.c
 * @brief 
 * @date 2021-12-08
 * 
 * 
 * 
 */
#include "account.h"
#include "link.h"
#include "account_middleware.h"
#include "drink_middleware.h"
extern link_t * account_link;
extern link_t * clerk_link;
extern link_t * drink_link;
extern link_t * coffee_type_link;
extern link_t * milk_type_link;
extern link_t * ice_type_link;
void init();
void show_main_interface();

int main(){
	init();
	while (1){
		show_main_interface();
	}
}
/**
 * @brief init all of data
 * 
 */
void init(){
	account_link = init_link();
	clerk_link = init_link();
	drink_link = init_link();
	coffee_type_link = init_link();
	milk_type_link = init_link();
	ice_type_link = init_link();
	clerk_link_init();
	read_file_name(account_link, sizeof(user_acconut_t), "account.txt", insert_new_element);
	read_file_name(drink_link, sizeof(drink_t), "drink.txt", insert_new_element);
	read_option_to_file();
}
/**
 * @brief show main interface
 * 
 */
void show_main_interface(){
	system("cls");
	printf("1.Log in\n");
	printf("2.New customer registration\n");
	printf("Press number key to enter the corresponding menu\n");
	int error_state = 1;
	char ch;
	while (error_state = 1)
		switch (ch = getch())
	{
		case'1':
			show_login_interface();
			system("cls");
			printf("1.Log in\n");
			printf("2.New customer registration\n");
			error_state = 0;
			break;
		case'2':
			add_new_customer();
			system("cls");
			printf("1.Log in\n");
			printf("2.New customer registration\n");
			break;
		default:
			break;
	}
}
