#ifndef ACCOUNT_MIDDLEWARE_H
#define ACCOUNT_MIDDLEWARE_H
#include "drink_middleware.h"

typedef struct{
	char name[20];
	int ID;
	char phone_num[20];
	float balance;
	drink_t History[5];
}user_acconut_t;

typedef struct{
	char name[20];
	char password[10];
}manager_account_t;

void update_oredr_history(link_t * customer);
link_t* insert_new_element(link_t*p, user_acconut_t *buffer, int length);
link_t *insert_new_customer(link_t*p, user_acconut_t *buffer, int length);
void save_clerk_info(void);
link_t *search_name(link_t *p, char *name);
link_t *search_clerkdata_name(link_t *p, char *name);
link_t *delet_account_link(link_t*p, link_t *deleted_link);
void clerk_link_init(void);


void more_coffee();
void read_option_to_file();
void save_option_to_file();
link_t *search_drink_name(link_t *p, char *name);
void show_sale_data();
void more_sugar();
#endif // !ACCOUNT_MIDDLEWARE_H

