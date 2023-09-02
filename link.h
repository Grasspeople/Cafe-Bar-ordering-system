#ifndef LINK_H
#define LINK_H
typedef struct{
	struct link_t *prev;
	void *point;
	struct link_t *next;
}link_t;

link_t *get_number_link_point(link_t *head, int num);
link_t *insert_link(link_t *positon, void *point);
link_t *delet_link(link_t *head, link_t *deleted);
int *calc_link_length(link_t *p);
link_t * init_link(void);


void read_file_name(link_t *p, int struct_length, char *file_name, int(*insert_link)(link_t *, void*, int));
void save_file_name(link_t *p, int struct_length, char *file_name);
//void save_file_pointer(link_t *p, int struct_length, FILE *account_file);
//void read_file_pointer(link_t *p, int struct_length, FILE *account_file, int(*insert_link)(link_t *, void*, int));

#endif // !LINK_SUPPORT_H