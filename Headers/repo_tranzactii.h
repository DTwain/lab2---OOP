#pragma once
#include "tranzaction.h"

typedef struct {
	tranzaction *arr_of_tranzactions;
	int capacity;
	int nr_of_tranzactions;
	int nr_of_tranzactions_added_from_start;
}struct_with_field_tranzactions;

struct_with_field_tranzactions *create_list_of_tranzactions();
void resize(struct_with_field_tranzactions* struct_obj);
void destroy_struct_with_field_tranzactions(struct_with_field_tranzactions *struct_obj);
struct_with_field_tranzactions *copie_struct_obj(struct_with_field_tranzactions *struct_obj);
int add_tranzaction_repo(struct_with_field_tranzactions* struct_obj, tranzaction *curr_tranzaction);
struct_with_field_tranzactions* delete_tranzaction_repo(struct_with_field_tranzactions* struct_obj, int tranzaction_id_to_be_removed);
int modify_tranzaction_repo(struct_with_field_tranzactions* struct_obj, tranzaction *modified_tranzaction);
int get_next_tranzaction_id(struct_with_field_tranzactions *struct_obj);