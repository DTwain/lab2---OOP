#pragma once
#include <repo_tranzactii.h>
int add_tranzaction(struct_with_field_tranzactions* struct_obj, int day, int sum, char type[10], char description[100]);
int delete_tranzaction(struct_with_field_tranzactions* struct_obj, int tranzaction_ID_to_be_deleted);
int modify_tranzaction(struct_with_field_tranzactions* struct_obj, int id, int day, int sum, char type[], char description[]);
struct_with_field_tranzactions lista_de_tranzactii(struct_with_field_tranzactions* struct_obj);
struct_with_field_tranzactions filters_on_tranzactions(struct_with_field_tranzactions* struct_obj, char type_filter[], int sum_filter, char mod_h_or_l);
struct_with_field_tranzactions sorting_based_of_criteria(struct_with_field_tranzactions* struct_obj, char sorting_mode, char suma_or_zi[]);