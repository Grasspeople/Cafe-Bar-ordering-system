#ifndef MEMU_H
#define MEMU_H
#include "link.h"
#include "drink_middleware.h"
void show_memu(void);
void change_order_interface();
void edit_drink_t(link_t *p, link_t *head, char *file_name);
int cash_pay_interface();
void show_order_history();
int settlement_interface();
int balance_pay();
void edit_drink_link_t(link_t *head);
#endif // !MEMU_H
