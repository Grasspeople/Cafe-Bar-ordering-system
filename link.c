/**
* @file link.c
* @author Wenhao Lin (Wenhao.Lin20@student.xjtlu.edu.cn)
* @brief This is bidirectional linked list library. Contains different types of linked list operations.
* Because the link only save the pointer of address, so it can be used to any type of structure.So that
* the linked list functions of different structures can be shared. Greatly reduces the coupling degree of the code
* @date 2021-11-25
*
*
*
*/
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "link.h"
#include <stdlib.h>
#include "drink_middleware.h"

/**
* @brief init a link list head, and return a pointer as the head of link list.
*
* @return link_t*
*/
link_t * init_link(void){
	link_t * c = (link_t*)malloc(sizeof(link_t));
	c->point = NULL;
	c->prev = NULL;
	c->next = NULL;
	return c;
}
/**
* @brief Get the number of linked list elements. Not counting the header
*
* @param p : the pointer of link which needed to be calculate
* @return int* :the number of link list
*/
int *calc_link_length(link_t *p){
	int i = 0;
	while (p->next){
		p = p->next;
		i++;
	}
	return i;
}
/**
* @brief delete a element of link
*
* @param head : the header of link
* @param deleted : the element pointer needed to be deleted
* @return link_t* : return the head of link_t
*/
link_t *delet_link(link_t *head, link_t *deleted){
	link_t *temp = head;
	if (head==deleted)
	{
		return;
	}
	while (temp->next){
		if (temp == deleted){
			break;
		}
		else{
			temp = temp->next;
		}
	}
	if (temp->next == NULL){
		if (temp->prev==NULL)
		{
			return;
		}
		link_t *prelink = temp->prev;/*Prevent deleted element is the last one*/
		prelink->next = NULL;
		free(temp->point);
		free(temp);
	}
	else{
		link_t *prelink = temp->prev;
		link_t *nextlink = temp->next;
		prelink->next = temp->next;
		nextlink->prev = temp->prev;
		free(temp->point);
		free(temp);
	}
}
/**
* @brief insert a new structure data into the link, the new link element behind the position
*
* @param positon : insert a new structure data behind the position
* @param pointer : new structure data pointer
* @return link_t* : return new element link pointer
*/
link_t *insert_link(link_t *positon, void *point){
	link_t * c = (link_t*)malloc(sizeof(link_t));
	if (positon->next != NULL){
		link_t *next_link;
		next_link = positon->next;
		next_link->prev = c;
		c->next = positon->next;
		positon->next = c;
		c->prev = positon;
		c->point = point;
	}
	if (positon->next == NULL){
		c->next = NULL;
		c->point = point;
		positon->next = c;
		c->prev = positon;
	}
	return c;
}

/**
* @brief Get the number link pointer object
*
* @param head
* @param num
* @return link_t*
*/
link_t *get_number_link_point(link_t *head,int num){
	link_t *temp = head;
	int i;

	for (i = 0; i < num; i++){
		temp = temp->next;
	}
	return temp;
}


/**
* @brief read any structure data from the txt.
* Then the pointer to each structure is saved in the linked list.
*
* @param p : The newly inserted structure link list exists after it
* @param struct_length : The length of the structure to be read
* @param file_name : file name
* @param insert_link : Insert a linked list
*/
void read_file_name(link_t *p, int struct_length, char *file_name, int(*insert_link)(link_t *, void*, int)){
	FILE *account_file;
	int i = 0;
	int length;
	account_file = fopen(file_name, "a+");
	void *c = malloc(struct_length);
	fread(&length, sizeof(int), 1, account_file);
	fseek(account_file, sizeof(int), SEEK_CUR);
	for (i = 1; i <= length; i++){
		fread(c, struct_length, 1, account_file);
		fseek(account_file, struct_length, SEEK_CUR);
		insert_link(p, c, struct_length);
	}
	fclose(account_file);
	free(c);
}
/**
* @brief read any structure data from the txt.
* Then the pointer to each structure is saved in the linked list.
*
* @param p : The newly inserted structure link list exists after it
* @param struct_length : The length of the structure to be read
* @param account_file : Pointer to the file being read
* @param insert_link : Insert a linked list
*/
void read_file_pointer(link_t *p, int struct_length, FILE *account_file, int(*insert_link)(link_t *, void*, int)){
	int i = 0;
	int length;
	char ch;
	fread(&length, sizeof(int), 1, account_file);
	fseek(account_file, sizeof(int), SEEK_CUR);
	for (i = 1; i <= length; i++){
		void *c = malloc(struct_length);
		fread(c, struct_length, 1, account_file);
		fseek(account_file, struct_length, SEEK_CUR);
		insert_link(p, c, struct_length);
	}
}
/**
* @brief save the link list structure data to txt file.
*
* @param p : the link list which needed to be saved.
* @param struct_length : the number of link list elements.
* @param file_name
*/
void save_file_name(link_t *p, int struct_length, char *file_name){
	FILE *account_file;
	int length;
	length = calc_link_length(p);
	account_file = fopen(file_name, "w+");
	link_t *temp = p;
	void *data;

	fwrite(&length, sizeof(int), 1, account_file);
	fseek(account_file, sizeof(int), SEEK_CUR);

	while (temp->next){
		temp = temp->next;
		data = temp->point;
		fwrite(data, struct_length, 1, account_file);
		fseek(account_file, struct_length, SEEK_CUR);
	}
	fclose(account_file);
}
/**
* @brief save the link list structure data to txt file.
*
* @param p : the link list which needed to be saved.
* @param struct_length : the number of link list elements.
* @param account_file : txt file pointer
*/
void save_file_pointer(link_t *p, int struct_length, FILE *account_file){
	int length;
	length = calc_link_length(p);
	link_t *temp = p;
	void *data;

	fwrite(&length, sizeof(int), 1, account_file);
	fseek(account_file, sizeof(int), SEEK_CUR);

	while (temp->next){
		temp = temp->next;
		data = temp->point;
		fwrite(data, struct_length, 1, account_file);
		fseek(account_file, struct_length, SEEK_CUR);
	}
}



