#include "account.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>




#include "link.h"
#include "account_middleware.h"
#include "input_support.h"
#include "drink_middleware.h"
#include "memu.h"




extern link_t * drink_link;
extern link_t * coffee_type_link;
extern link_t * account_link;
extern drink_t * choose_drink;
extern link_t * purchaser_info;
extern order_info_t order_info;


void show_memu(void){
	
	int arrow_pos = 1;
	int ch;
	link_t *temp;
	while (1){

		while (1){
			show_all_drink(arrow_pos);
			printf("Press 'Enter' to change the selected name");
			printf("If you want to search account you can press 's' \n ");
			switch (ch = getch())
			{
			case 72:
				if (arrow_pos > 0){
					arrow_pos--;
				}
				break;
			case 80:
				if (arrow_pos < calc_link_length(drink_link)){
					arrow_pos++;
				}
				break;
			case 's':
				//serach_account();
				break;
			case '0':
				return 0;
				break;
			case '13':
				temp = get_number_link_point(drink_link, arrow_pos);
				printf("Press e to change the selected name");
				printf("If you want to search account you can press 's' \n");
			case 'd':
				delet_account(temp);
			default:
				break;
			}
		}
	}
	
}

void change_memu_info(void){
	char ch;
	int error_state = 1;
	system("cls");
	printf("1.Add new drink.\n");
	printf("2.Edit/Delete drink information.\n");
	printf("3.Add new option.\n");
	printf("4.Edit/Delete option.\n");
	printf("0.Return\n");
	while (error_state = 1)
		switch (ch = getch())
	{
		case '1':
			error_state = 0;
			add_new_drink();
			system("cls");
			printf("1.Add new drink.\n");
			printf("2.Edit/Delete drink information.\n");
			printf("3.Add new option.\n");
			printf("4.Edit/Delete option.\n");
			printf("0.Return\n");
			break;
		case '2':
			error_state = 0;
			edit_drink_link_t(drink_link);
			system("cls");
			printf("1.Add new drink.\n");
			printf("2.Edit/Delete drink information.\n");
			printf("3.Add new option.\n");
			printf("4.Edit/Delete option.\n");
			printf("0.Return\n");
			break;
		case '3':
			error_state = 0;
			manager_add_new_option_interface();
			system("cls");
			printf("1.Add new drink.\n");
			printf("2.Edit/Delete drink information.\n");
			printf("3.Add new option.\n");
			printf("4.Edit/Delete option.\n");
			printf("0.Return\n");
			break;
		case '4':
			error_state = 0;
			manager_edit_option_interface();
			system("cls");
			printf("1.Add new drink.\n");
			printf("2.Edit/Delete drink information.\n");
			printf("3.Add new option.\n");
			printf("4.Edit/Delete option.\n");
			printf("0.Return\n");
			break;
		case'0':
			return 0;
		default:
			break;
	}
}
void edit_drink_link_t(link_t *head){
	int arrow_pos = 1;
	int ch;
	link_t *temp;
	while (1){
		while (1){
			show_all_drink(head, arrow_pos);
			printf("Press 'e' to change the selected name, press 'n' to deleted drink");
			switch (ch = getch())
			{
			case 72:
				if (arrow_pos > 0){
					arrow_pos--;
				}
				break;
			case 80:
				if (arrow_pos < calc_link_length(head)){
					arrow_pos++;
				}
				break;
			case 's':
				search_account();
				break;
			case '0':
				return 0;
				break;
			case 'e':
				temp = get_number_link_point(head, arrow_pos);
				edit_drink_t(temp, head,"drink.txt");
				printf("Press e to change the selected name");
				break;
			case 'd':
				temp = get_number_link_point(head, arrow_pos);
				delet_link(head,temp);
				break;
			default:
				break;
			}
		}
	}
}
void edit_drink_t(link_t *p,link_t *head,char *file_name){
	link_t *temp = p;
	drink_t *data;
	data = p->point;
	system("cls");
	printf("%20s          ", data->name);
	printf("$%.2f", data->price);
	printf("\n");
	printf("Press 'n' to edit name, press 'p' to edit prcie£¬press 'd' to delete, press '0' to return\n");
	char ch;
	while (1){
		system("cls");
		printf("%20s          ", data->name);
		printf("$%.2f", data->price);
		printf("\n");
		printf("Press 'n' to edit name, press 'p' to edit prcie£¬press 'd' to delete, press '0' to return\n");
		switch (ch = getch())
		{
		case'n':
			printf("Type new Name:");
			get_20_char(data->name);
			save_file_name(head, sizeof(drink_t), file_name);
			printf("\nEdit name successfully!");
			break;
		case'p':
			printf("Type new price:");
			float amount = 0;
			input_float_num(&amount, 1);
			while (1){
				if (amount>0)
				{
					break;
				}
				printf("\033[31mPlease enter a positive number\n\033[0m");
				/*ask input again*/
				if (!input_again(&amount, "Input amount again:", 20, input_float_num)){
					amount = 0;
					return;/*not input*/
				}
			}
			data->price = amount;
			save_file_name(head, sizeof(drink_t), file_name);
			break;
		case'0':
			return;
			break;
		case'd':
			delet_link(head, temp);
			return;
		default:
			break;
		}
	}
}


int settlement_interface(){
	char ch;
	system("cls");
	printf("The total cost is %.1f$\n", order_info.order_pay + order_info.coffee_bean_pay + order_info.ice_pay + order_info.milk_pay);
	printf("The order is %s\n", order_info.order);
	if (order_info.milk[0] == '\0'){
		printf("The type of milk is default\n");
	}
	else{
		printf("The type of milk is %s\n",order_info.milk);
	}

	if (order_info.coffee_bean[0] == '\0'){
		printf("The type of coffee bean is default\n");
	}
	else{
		printf("The type of coffee bean is %s\n", order_info.coffee_bean);
	}



	if (order_info.ice[0] == '\0'){
		printf("The the drink will be room temperature\n");
	}
	else{
		printf("The the drink will be %s\n", order_info.ice);
	}

	printf("The additional suger %d\n", order_info.suger);
	printf("The additional coffee %d\n\n", order_info.ext_coffee);

	printf("\033[32m1.Cash pay\n");
	printf("2.Balance pay\n\033[0m");
	printf("Press '0' return");
	while (1){
		switch (ch = getch())
		{
		case'1':
			return cash_pay_interface();
			break;
		case'2':
			return balance_pay();
			break;
		case'0':
			return 0;
			break;
		default:
			break;
		}
	}

}
int cash_pay_interface(){
	char ch;
	update_oredr_history(purchaser_info);
	choose_drink->sales++;
	save_file_name(drink_link, sizeof(drink_t), "drink.txt");
	system("cls");
	printf("Purchase Success\n");
	printf("1.Continue to buy\n");
	printf("0.End purchase\n");
	memset(&order_info, '\0', sizeof(order_info_t));
	while (1){
		switch (ch = getch())
		{
		case'1':
			return 1;
			break;
		case'0':
			return 2;
			break;
		default:
			break;
		}
	}
}


void show_order_history(){
	user_acconut_t *data=purchaser_info->point;
	int i = 0;
	system("cls");
	printf("Order history:\n");
	for (i = 0; i < 5; i++){
		if (data->History[i].name[0]!='\0')
		printf("%s\n", data->History[i].name);
	}
	while (1){
		printf("Press any key to return to the previous menu");
		if (getch())return 0;
	}
}

int balance_pay(){
	char ch;
	user_acconut_t *data;
	system("cls");
	float sum = order_info.coffee_bean_pay + order_info.order_pay + order_info.ice_pay + order_info.coffee_bean_pay;
	data = purchaser_info->point;
	if (data->balance >= sum){
		update_oredr_history(purchaser_info);
		data->balance -= sum;
		choose_drink->sales++;
		save_file_name(drink_link, sizeof(drink_t), "drink.txt");
		save_file_name(account_link, sizeof(user_acconut_t), "account.txt");
		printf("Balance pay successfully, now the balance is %.f%\n", data->balance);
		printf("1.Continue to buy\n");
		printf("0.End purchase\n");
		while (1){
			switch (ch = getch())
			{
			case'1':
				return 1;
				break;
			case'0':
				return 2;
				break;
			default:
				break;
			}
		}
	}
	else if (data->balance < sum){
		printf("Insufficient balance\n");
		while (1){
			printf("Press any key to return to the previous menu");
			if (getch())return 0;
		}
	}
}
