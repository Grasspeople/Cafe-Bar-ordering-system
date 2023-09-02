/**
* @file input_support.c
* @author Wenhao Lin (Wenhao.Lin20@student.xjtlu.edu.cn)
* @brief This file contains input functions that can get characters of specified length, letters.
* And output corresponding hints.
*
* @date 2021-11-26
*
*
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "input_support.h"
void get_20_char(char * p){
	char buffer[9999];
	while (gets(buffer)){
		if (strlen(buffer) > 19){
			printf("\033[31mPleaser input less than 20 char\n\033[0m");
			printf("Input again: ");
		}
		else{
			memcpy(p, buffer, sizeof(char) * 20);
			return;
		}
	}
}
/**
* @brief Gets the specified number of characters without space. Output a prompt if you get more than 20 characters and ask for retyping
*
* @param p :the address of string need to be stored
*/
void get_char(char * p, int num){
	char buffer[9999];/*Prevent output out of bounds*/
	int error_state = 0;
	int i;
	while (gets(buffer)){
		error_state = 0;
		if (strlen(buffer) > num){/*there is '\0' at the end of string,only 20 chars we needed. So printf the hint and get again*/
			printf("\033[31mPlease input less than %d digits\n\033[0m", num);
		}
		if (strlen(buffer) == 0){
			printf("\033[31mInput should not be empty\n\033[0m", num);
		}
		else {
			for (i = 0; i < num; i++)
			{
				if (buffer[i] == 32 || buffer[i] == '\t')/*check if have space in the buffer*/
				{
					printf("\033[31mThe input should not contain spaces\n\033[0m");
					error_state = 1;
					break;/*if have space, break loop*/
				}
			}
			if (error_state == 0)
			{
				memcpy(p, buffer, sizeof(char) *(num + 1));/*If don't have memcpy the buffer data to the string*/
				return;
			}
		}
		printf("input again:");
	}
}

/**
* @brief use getch to get the input from the keyboard and print the * replace letter.
* There is problem of this function is that the user can not delete letter which have been inputed
* because it need update display frequently. To solve this problem, need to change the
* overall architecture of the game. Need to use the idea of rendering to render each frame,
* It also need to implement more low-level operations for the buffer.
* So I didn't try to solve it.
*
* This is the best function to use without changing the game architecture.
* @param address
* @param num
*/
void input_password(char *address, int num){
	char ch;
	int i = 0;
	while (ch = getch())
	{
		if (ch == 13)
		{
			address[i] = '\0';
			return;
		}
		else if (ch < 0){
			fflush(stdin);
		}
		else if (ch == 0x1B)
		{
			return;
		}
		else if (iscntrl(ch));
		else
		{
			printf("*");
			address[i] = ch;
			i++;
		}
		if (i == num)
		{
			printf("\nPlease enter a password of less than %d characters", num);
			memset(address, '\0', 20);
			i = 0;
		}
		fflush(stdin);
	}
}

/**
* @brief Get the letter object
*
* @param p : the address of the string
* @param num : Maximum number of saved characters
*/
void get_letter(char *p, int num){
	char buffer[9999];/*Prevent output out of bounds*/
	int error_state = 0;
	int i;
	while (gets(buffer)){
		error_state = 0;/*reset error state*/
		if (strlen(buffer) > num){/*there is '\0' at the end of string,only 20 chars we needed. So printf the hint and get again*/
			printf("Please input %d char(s)\n", num);
		}
		else {
			for (i = 0; i < strlen(buffer); i++)
			{
				if (buffer[i] == " " || (!isalpha(buffer[i])))/*check if have space in the buffer*/
				{
					printf("Only letters can be entered\n");
					error_state = 1;/*have error get char again*/
					break;/*if have space, break loop*/
				}
			}
			if (error_state == 0)
			{
				memcpy(p, buffer, sizeof(char) *num);/*If don't have memcpy the buffer data to the string*/
				return;
			}
			else
			{
				printf("input again:");
			}
		}
	}
}

/**
* @brief Output the hint, let the user choose whether to re-enter.
* Determine if the user chooses to retype by the return value
*
* @param input : the string need to be saved
* @param hint : Input instructions to help users re-enter better
* @param num : Maximum number of saved characters
* @param input_fuc : input function such as input_password(char *address,int num), or get_char(char * p,int num) ect.
* @return int
*/
int input_again(char input[20], char hint[20], char num, void(*input_fuc)(char *ch, int num)){
	printf("input again£¿£¨Y/n)\n");
	char ch;
	while (1){
		switch (ch = getch())
		{
		case 'Y': /*if user choose input again*/
		case 13:
		case 'y':
			printf("%s", hint);
			input_fuc(input, num);
			return 1;
			break;
		case 'n':
		case 'N':
			return 0;/*if user choose not input return 0 as state*/
			break;
		default:
			break;
		}
	}
}

/**
 * @brief input integer
 * 
 * @param num 
 * @param count : no use just give a interface
 */
void input_inter_num(int *num, int count){
	int error_state = 0;
	int i;
	error_state = scanf("%d", num);
	while (!error_state){
		printf("\033[31mPlease input number\n\033[0m");
		printf("Input again:");
		fflush(stdin);
		error_state = scanf("%d", num);
	}
}
/**
 * @brief input float
 * 
 * @param num 
 * @param count : no use just give a interface
 */
void input_float_num(float *num, int count){
	int error_state = 0;
	char buffer[6];
	input_float_char(buffer, 5);
	*num=strtod(buffer, NULL);
}
/**
 * @brief get string only contain number
 * 
 * @param ch 
 * @param num : length of char
 */
void input_char_number(char *ch, int num){
	int i = 0;
	int error_state = 1;
	get_char(ch, num);
	int length = strlen(ch);
	while (error_state){
		error_state = 0;
		for (i = 0; i < length; i++){
			if ((*(ch + i)>'9') || (*(ch + i) < '0')){
				printf("Please input number\n");
				printf("Input again:");
				error_state = 1;
				get_char(ch, num);
				break;
			}
		}
	}
}
void input_float_char(char *ch, int num){
	int i = 0;
	int error_state = 1;
	int point_count = 0;
	int sign = 0;
	get_char(ch, num);
	while (error_state){
		error_state = 0;
		int length = strlen(ch);
		for (i = 0; i < length; i++){
			if ((*(ch + i)>'9') || (*(ch + i) < '0')){
				if (*(ch + i) == '.')
				{
					point_count++;
				}
				else if (*(ch + i) == '-' || *(ch + i) == '+')
				{
					sign++;
				}
				else
				{
					printf("\033[31mPlease input correct number\n\033[0m");
					printf("Input again:");
					error_state = 1;
					i = 0;
					sign = 0;
					point_count = 0;
					get_char(ch, num);
					break;
				}
				if (sign==2||point_count==2)
				{
					printf("\033[31mPlease input correct number\n\033[0m");
					printf("Input again:");
					error_state = 1;
					i = 0;
					sign = 0;
					point_count = 0;
					get_char(ch, num);
					break;
				}
			}
		}
	}
}