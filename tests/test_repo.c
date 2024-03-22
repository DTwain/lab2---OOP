#include <string.h>
#include "assert.h"
#include "tranzaction.h"
#include "repo_tranzactii.h"

void test_create_list_of_tranzactions() {
	struct_with_field_tranzactions *temp = create_list_of_tranzactions();
	assert(temp -> nr_of_tranzactions == 0);
	assert(temp -> nr_of_tranzactions_added_from_start == 0);
	assert(temp -> capacity == 20);

	destroy_struct_with_field_tranzactions(temp);
}

void test_destroy_struct_with_field_tranzactions() {
	struct_with_field_tranzactions *temp = create_list_of_tranzactions();
	destroy_struct_with_field_tranzactions(temp);
}

void test_copie_struct_obj() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp) == 0);
	add_tranzaction_repo(struct_obj, temp);
	struct_with_field_tranzactions *copie = copie_struct_obj(struct_obj);
	assert(copie -> nr_of_tranzactions == 1);
	assert(copie -> nr_of_tranzactions_added_from_start == 1);
	assert(copie -> arr_of_tranzactions[0].id_tranzaction == 0);
	assert(copie -> arr_of_tranzactions[0].sum == 400);
	assert(copie -> arr_of_tranzactions[0].day == 12);
	assert(strcmp(copie -> arr_of_tranzactions[0].type, "iesire\n") == 0);
	assert(strcmp(copie -> arr_of_tranzactions[0].description, "datoria pe aprilie\n") == 0);

	destroy_struct_with_field_tranzactions(copie);
	destroy_tranzaction(temp);
	destroy_struct_with_field_tranzactions(struct_obj);
}

void test_add_tranzaction_repo() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp) == 0);
	assert(add_tranzaction_repo(struct_obj, temp) == 0);
	assert(struct_obj -> nr_of_tranzactions == 1);
	assert(struct_obj -> nr_of_tranzactions_added_from_start == 1);
	assert(struct_obj -> arr_of_tranzactions[0].id_tranzaction == 0);
	assert(struct_obj -> arr_of_tranzactions[0].sum == 400);
	assert(struct_obj -> arr_of_tranzactions[0].day == 12);
	assert(strcmp(struct_obj -> arr_of_tranzactions[0].type, "iesire\n") == 0);
	assert(strcmp(struct_obj -> arr_of_tranzactions[0].description, "datoria pe aprilie\n") == 0);

	tranzaction *temp2 = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp2) == 0);
	assert(add_tranzaction_repo(struct_obj, temp2) == 0);
	assert(struct_obj -> nr_of_tranzactions == 2);
	assert(struct_obj -> nr_of_tranzactions_added_from_start == 2);

	destroy_tranzaction(temp);
	destroy_tranzaction(temp2);
	destroy_struct_with_field_tranzactions(struct_obj);
}

void test_delete_tranzaction_repo() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(0, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp) == 0);
	add_tranzaction_repo(struct_obj, temp);

	tranzaction *temp2 = create_tranzaction(1, 22, 300, "intrare\n", "datoria pe iunie\n");
	assert(validate_tranzaction(temp2) == 0);
	add_tranzaction_repo(struct_obj, temp2);
	assert(struct_obj -> nr_of_tranzactions == 2);
	assert(struct_obj -> nr_of_tranzactions_added_from_start == 2);


	struct_with_field_tranzactions* rezultat = delete_tranzaction_repo(struct_obj, temp->id_tranzaction);
	assert(rezultat != NULL);
	struct_obj = rezultat;

	assert(struct_obj -> nr_of_tranzactions == 1);
	assert(struct_obj -> nr_of_tranzactions_added_from_start == 2);

	assert(delete_tranzaction_repo(struct_obj, temp -> id_tranzaction) == NULL);

	assert(struct_obj -> arr_of_tranzactions[0].id_tranzaction == 1);
	assert(struct_obj -> arr_of_tranzactions[0].sum == 300);
	assert(struct_obj -> arr_of_tranzactions[0].day == 22);
	assert(strcmp(struct_obj -> arr_of_tranzactions[0].type, "intrare\n") == 0);
	assert(strcmp(struct_obj -> arr_of_tranzactions[0].description, "datoria pe iunie\n") == 0);

	destroy_tranzaction(temp);
	destroy_tranzaction(temp2);
	destroy_struct_with_field_tranzactions(struct_obj);
}

void test_modify_tranzaction_repo() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(0, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction *temp2 = create_tranzaction(1, 22, 300, "intrare\n", "datoria pe iunie\n");
	tranzaction *modified_tranzaction = create_tranzaction(1, 17, 1000, "intrare\n", "datoria pe iunie\n");
	tranzaction *modified_tranzaction_2 = create_tranzaction(3, 14, 200, "iesire\n", "motorina\n");
	
	assert(validate_tranzaction(temp) == 0);
	assert(add_tranzaction_repo(struct_obj, temp) == 0);

	assert(validate_tranzaction(temp2) == 0);
	assert(add_tranzaction_repo(struct_obj, temp2) == 0);

	assert(validate_tranzaction(modified_tranzaction) == 0);
	assert(modify_tranzaction_repo(struct_obj, modified_tranzaction) == 0);

	assert(validate_tranzaction(modified_tranzaction_2) == 0);
	assert(modify_tranzaction_repo(struct_obj, modified_tranzaction_2) == -1);

	destroy_tranzaction(temp);
	destroy_tranzaction(temp2);
	destroy_tranzaction(modified_tranzaction);
	destroy_tranzaction(modified_tranzaction_2);
	destroy_struct_with_field_tranzactions(struct_obj);
}

void test_get_next_tranzaction_id() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(0, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp) == 0);
	assert(add_tranzaction_repo(struct_obj, temp) == 0);

	assert(get_next_tranzaction_id(struct_obj) == 1);
	destroy_tranzaction(temp);
	destroy_struct_with_field_tranzactions(struct_obj);
}

void test_resize() {
	struct_with_field_tranzactions* struct_obj = create_list_of_tranzactions();
	tranzaction* temp = create_tranzaction(0, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp1 = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp2 = create_tranzaction(2, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp3 = create_tranzaction(3, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp4 = create_tranzaction(4, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp5 = create_tranzaction(5, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp6 = create_tranzaction(6, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp7 = create_tranzaction(7, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp8 = create_tranzaction(8, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp9 = create_tranzaction(9, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp10 = create_tranzaction(10, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp11 = create_tranzaction(11, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp12 = create_tranzaction(12, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp13 = create_tranzaction(13, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp14 = create_tranzaction(14, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp15 = create_tranzaction(15, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp16 = create_tranzaction(16, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp17 = create_tranzaction(17, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp18 = create_tranzaction(18, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp19 = create_tranzaction(19, 12, 400, "iesire\n", "datoria pe aprilie\n");
	tranzaction* temp20 = create_tranzaction(20, 12, 400, "iesire\n", "datoria pe aprilie\n");

	add_tranzaction_repo(struct_obj, temp);
	add_tranzaction_repo(struct_obj, temp1);
	add_tranzaction_repo(struct_obj, temp2);
	add_tranzaction_repo(struct_obj, temp3);
	add_tranzaction_repo(struct_obj, temp4);
	add_tranzaction_repo(struct_obj, temp5);
	add_tranzaction_repo(struct_obj, temp6);
	add_tranzaction_repo(struct_obj, temp7);
	add_tranzaction_repo(struct_obj, temp8);
	add_tranzaction_repo(struct_obj, temp9);
	add_tranzaction_repo(struct_obj, temp10);
	add_tranzaction_repo(struct_obj, temp11);
	add_tranzaction_repo(struct_obj, temp12);
	add_tranzaction_repo(struct_obj, temp13);
	add_tranzaction_repo(struct_obj, temp14);
	add_tranzaction_repo(struct_obj, temp15);
	add_tranzaction_repo(struct_obj, temp16);
	add_tranzaction_repo(struct_obj, temp17);
	add_tranzaction_repo(struct_obj, temp18);
	add_tranzaction_repo(struct_obj, temp19);
	add_tranzaction_repo(struct_obj, temp20);

	assert(struct_obj -> capacity == 40);

	destroy_tranzaction(temp);
	destroy_tranzaction(temp1);
	destroy_tranzaction(temp2);
	destroy_tranzaction(temp3);
	destroy_tranzaction(temp4);
	destroy_tranzaction(temp5);
	destroy_tranzaction(temp6);
	destroy_tranzaction(temp7);
	destroy_tranzaction(temp8);
	destroy_tranzaction(temp9);
	destroy_tranzaction(temp10);
	destroy_tranzaction(temp11);
	destroy_tranzaction(temp12);
	destroy_tranzaction(temp13);
	destroy_tranzaction(temp14);
	destroy_tranzaction(temp15);
	destroy_tranzaction(temp16);
	destroy_tranzaction(temp17);
	destroy_tranzaction(temp18);
	destroy_tranzaction(temp19);
	destroy_tranzaction(temp20);
	destroy_struct_with_field_tranzactions(struct_obj);
}

