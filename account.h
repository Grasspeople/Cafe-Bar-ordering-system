#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "link.h"
void add_new_manager(void);
void add_new_customer(void);
void clerk_log_interface(void);
void clerk_change_password(void);
void customer_log_interface(void);
void inner_clerk_window(void);
void change_customer_info(void);
void show_login_interface();
void show_all_account(int a);
void search_account();
int delet_account(link_t *p);
int edit_account(void);
void edit_account_content(link_t *p);
void inner_customer_windows();
void balacne_recharge_interface();
#endif