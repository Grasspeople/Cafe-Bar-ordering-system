#ifndef INPUT_SUPPORT_H
#define INPUT_SUPPORT_H


void input_password(char *address, int num);
int input_again(char input[20], char hint[20], char num, void(*input_fuc)(char *ch, int num));
void get_letter(char *p, int num);
void get_char(char * p, int num);
void input_inter_num(int *num, int count);
void input_float_num(int *num, int count);
void input_char_number(char *ch, int num);
void input_float_char(char *ch, int num);
#endif // !INPUT_SUPPORT_H




