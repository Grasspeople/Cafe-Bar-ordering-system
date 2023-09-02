/**
 * @file account_middleware.c
 * @brief Customer and clerk middleware function, read the data from the .txt file.
 * Use the linked list function operate the customer clerk data.
 * @date 2021-12-08
 * 
 * 
 * 
 */
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "link.h"
#include <stdlib.h>
#include <fcntl.h>
#include "account_middleware.h"

#define SUPER_ADMIN_NAME1 "Admin"
#define SUPER_ADMIN_PASSWORD1 "1234"


#define SUPER_ADMIN_NAME2 "WenhaoLin"
#define SUPER_ADMIN_PASSWORD2 "20180910"


link_t * account_link;
link_t * clerk_link;
link_t * logged_clerk_link;


/**
 * @brief insert new element as the last of the linked list
 * 
 * @param p : linked list header
 * @param buffer : new element data
 * @param length : length of the structure data
 * @return link_t* : return new element address.
 */
link_t* insert_new_element(link_t*p, user_acconut_t *buffer,int length){
	link_t * temp = p;
	int i = 0;
	if (buffer->name[0] == '\0'){/*Prevent the invalid data*/
		return p;
	}
	
	while (temp->next){
		temp = temp->next;
	}
	void *save = malloc(length);
	memcpy(save, buffer,length);
	return  insert_link(temp, save);
}
/**
 * @brief insert a new as the last of the linked list customer and get the new user ID
 * 
 * @param p : linked list header
 * @param buffer : new element data
 * @param length : length of the structure data
 * @return link_t* : return new element address.
 */
link_t *insert_new_customer(link_t*p, user_acconut_t *buffer, int length){
	link_t * temp = p;
	int i = 0;
	if (buffer->name[0] == '\0'){/*Prevent the invalid data*/
		return p;
	}

	while (temp->next){
		temp = temp->next;
	}
	
	user_acconut_t *data = temp->point;
	if (data == NULL){
		buffer->ID = 1;//first user is 1
	}
	else{
		buffer->ID = data->ID + 1;//new ID is the last user ID + 1
	}
	void *save = malloc(length);
	memcpy(save, buffer, length);
	return  insert_link(temp, save);
}

/**
 * @brief save clerk information to the .txt file
 * 
 */
void save_clerk_info(void){
	FILE *account_file;
	int length;
	length = calc_link_length(clerk_link);
	account_file = fopen("clerk_data.txt", "w+");
	link_t *temp = clerk_link;
	manager_account_t *data;

	fwrite(&length, sizeof(int), 1, account_file);
	fseek(account_file, sizeof(int), SEEK_CUR);

	while (temp->next){
		temp = temp->next;
		data = temp->point;
		fwrite(data, sizeof(manager_account_t), 1, account_file);
		fseek(account_file, sizeof(manager_account_t), SEEK_CUR);
	}
	fclose(account_file);
}

/**
 * @brief search name from the customer or clerk linked list.
 * 
 * @param p : header
 * @param name : name wanted to be search
 * @return link_t* : return the address of the element which have the same name,
 * if don't have same name in the linked list, return NULL
 * 
 * 
 */
link_t *search_name(link_t *p, char *name){
	char input_name[20];
	int i = 0;
	link_t *temp = p;
	user_acconut_t *data;
	while (temp->next)
	{
		temp = temp->next;
		data = temp->point;
		if (strcmp(data->name, name) == 0) return temp;
	}
	return NULL;
}

/**
 * @brief search name from the customer or clerk linked list.
 * 
 * @param p : header
 * @param name : name wanted to be search
 * @return link_t* : return the address of the element which have the same name,
 * if don't have same name in the linked list, return NULL
 * 
 * 
 * NOTE: Although the structure of the clerk and customer is different, but the first 20 Bytes is stored name, 
 * so it can use same function to search different sturcture. That mean the this function can be repalce by the
 * previous function.
 */
link_t *search_clerkdata_name(link_t *p, char *name){
	char input_name[20];
	int i = 0;
	manager_account_t *data;
	link_t *temp = p;
	while (temp->next){
		temp = temp->next;
		data = temp->point;
		if (strcmp(data->name, name) == 0) return temp;
	}
	return NULL;
}


/**
 * @brief An interface for deleting structures
 * 
 * @param p : header of linked list
 * @param deleted_link : element needed to be delete
 * @return link_t* : new header
 */
link_t *delet_account_link(link_t*p, link_t *deleted_link){
	delet_link(p, deleted_link);
}


/**
 * @brief read the clerk account data form the .txt, if the .txt don't store the data,
 * Use the original account in the code as admin account, and then save it in the .txt file.
 * 
 */
void clerk_link_init(void){
	FILE *account_file;
	int i = 0;
	if (fopen("clerk_data.txt", "r")==NULL){
		manager_account_t *buffer1 = (manager_account_t *)malloc(sizeof(manager_account_t));;
		/*Create first account*/
		strcpy(buffer1->name, SUPER_ADMIN_NAME1);
		strcpy(buffer1->password, SUPER_ADMIN_PASSWORD1);
		insert_link(clerk_link, buffer1);
		/*Create second account*/
		manager_account_t *buffer2 = (manager_account_t *)malloc(sizeof(manager_account_t));;
		strcpy(buffer2->name, SUPER_ADMIN_NAME2);
		strcpy(buffer2->password, SUPER_ADMIN_PASSWORD2);
		insert_link(clerk_link, buffer2);
		save_clerk_info();
	}
	else{//the file store the information, read it from it.
		read_file_name(clerk_link, sizeof(manager_account_t), "clerk_data.txt", insert_new_element);
	}
}



