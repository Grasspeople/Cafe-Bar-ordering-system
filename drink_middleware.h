#ifndef DRINK_MIDDLEWARE_H
#define DRINK_MIDDLEWARE_H
#include "link.h"
typedef struct{
	char name[20];
	float price;
	int sales;
}drink_t;
typedef struct{
	char order[20];
	float order_pay;

	char coffee_bean[20];
	float coffee_bean_pay;

	char ice[20];
	float ice_pay;

	char milk[20];
	float milk_pay;

	int suger;
	int ext_coffee;
}order_info_t;


link_t *show_all_drink(int a);
link_t *init_drinklink(void);
void search_drink();
void add_new_drink();
link_t *init_drinklink(void);
void add_new_option();
void update_oredr_history(link_t * customer);
void read_file_name(link_t *p, int struct_length, char *file_name, int(*insert_link)(link_t *, void*, int));

#endif 

