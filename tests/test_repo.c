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
	assert(temp == NULL);
}

void test_copie_struct_obj() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp) == 0);
	add_tranzaction_repo(struct_obj, temp);
	struct_with_field_tranzactions *copie = copie_struct_obj(&struct_obj);
	assert(copie -> nr_of_tranzactions == 1);
	assert(copie -> nr_of_tranzactions_added_from_start == 1);
	assert(copie -> arr_of_tranzactions[1].id_tranzaction == 1);
	assert(copie -> arr_of_tranzactions[1].sum == 400);
	assert(copie -> arr_of_tranzactions[1].day == 12);
	assert(strcmp(*copie -> arr_of_tranzactions[1].type, "iesire\n") == 0);
	assert(strcmp(*copie -> arr_of_tranzactions[1].description, "datoria pe aprilie\n") == 0);

	destroy_struct_with_field_tranzactions(copie);
	destroy_tranzaction(temp);
	destroy_struct_with_field_tranzactions(struct_obj);
}

void test_add_tranzaction_repo() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp) == 0);
	assert(add_tranzaction_repo(&struct_obj, temp) == 0);
	assert(struct_obj -> nr_of_tranzactions == 1);
	assert(struct_obj -> nr_of_tranzactions_added_from_start == 1);
	assert(struct_obj -> arr_of_tranzactions[1].id_tranzaction == 1);
	assert(struct_obj -> arr_of_tranzactions[1].sum == 400);
	assert(struct_obj -> arr_of_tranzactions[1].day == 12);
	assert(strcmp(*struct_obj -> arr_of_tranzactions[1].type, "iesire\n") == 0);
	assert(strcmp(*struct_obj -> arr_of_tranzactions[1].description, "datoria pe aprilie\n") == 0);

	tranzaction *temp2 = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp2) == 0);
	assert(add_tranzaction_repo(&struct_obj, temp2) == 0);
	assert(struct_obj -> nr_of_tranzactions == 2);
	assert(struct_obj -> nr_of_tranzactions_added_from_start == 2);

	destroy_tranzaction(temp);
	destroy_tranzaction(temp2);
	destroy_struct_with_field_tranzactions(struct_obj);
}

void test_delete_tranzaction_repo() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp) == 0);
	add_tranzaction_repo(struct_obj, temp);

	tranzaction *temp2 = create_tranzaction(2, 22, 300, "intrare\n", "datoria pe iunie\n");
	assert(validate_tranzaction(temp2) == 0);
	assert(add_tranzaction_repo(struct_obj, temp2) == 0);
	assert(struct_obj -> nr_of_tranzactions == 2);
	assert(struct_obj -> nr_of_tranzactions_added_from_start == 2);


	assert(delete_tranzaction_repo(struct_obj, temp -> id_tranzaction) == 0);

	assert(struct_obj -> nr_of_tranzactions == 1);
	assert(struct_obj -> nr_of_tranzactions_added_from_start == 2);

	assert(delete_tranzaction_repo(struct_obj, temp -> id_tranzaction) == -1);

	assert(struct_obj -> arr_of_tranzactions[1].id_tranzaction == 2);
	assert(struct_obj -> arr_of_tranzactions[1].sum == 300);
	assert(struct_obj -> arr_of_tranzactions[1].day == 22);
	assert(strcmp(*struct_obj -> arr_of_tranzactions[1].type, "intrare\n") == 0);
	assert(strcmp(*struct_obj -> arr_of_tranzactions[1].description, "datoria pe iunie\n") == 0);

	destroy_tranzaction(temp);
	destroy_tranzaction(temp2);
	destroy_struct_with_field_tranzactions(struct_obj);
}

void test_modify_tranzaction_repo() {
	struct_with_field_tranzactions *struct_obj = create_list_of_tranzactions();
	tranzaction *temp = create_tranzaction(1, 12, 400, "iesire\n", "datoria pe aprilie\n");
	assert(validate_tranzaction(temp) == 0);
	assert(add_tranzaction_repo(struct_obj, temp) == 0);

	tranzaction *temp2 = create_tranzaction(2, 22, 300, "intrare\n", "datoria pe iunie\n");
	assert(validate_tranzaction(temp2) == 0);
	assert(add_tranzaction_repo(struct_obj, temp2) == 0);

	tranzaction *modified_tranzaction = create_tranzaction(2, 17, 1000, "intrare\n", "datoria pe iunie\n");
	assert(validate_tranzaction(modified_tranzaction) == 0);
	assert(modify_tranzaction_repo(struct_obj, modified_tranzaction) == 0);

	tranzaction *modified_tranzaction_2 = create_tranzaction(3, 14, 200, "iesire\n", "motorina\n");
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
