#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>

int numberOfRecords;

struct StdDetail{
	int roll;
	char name[30];
	int marks;
};

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void sort_file(){
	struct StdDetail data;
	int index=0, i;
	int array[numberOfRecords];
	FILE* file = fopen("std.dat", "a+b");
	while(fread(&data, sizeof(struct StdDetail), 1, file))
		array[index++] = data.roll;
	fclose(file);
	qsort(array, numberOfRecords, sizeof(int), cmpfunc);
	FILE* file3 = fopen("temp.dat", "a+b");
	for(i=0; i<numberOfRecords; i++){
		FILE* file2 = fopen("std.dat", "a+b");
		while(fread(&data, sizeof(struct StdDetail), 1, file2)){
			if(array[i] == data.roll){
				fwrite(&data, sizeof(struct StdDetail), 1, file3);
			}
		}
	fclose(file2);
	}
	fclose(file3);
	remove("std.dat");
	rename("temp.dat", "std.dat");
}

void add(struct StdDetail data){
	FILE* file = fopen("std.dat", "a+b");
	fwrite(&data, sizeof(struct StdDetail), 1, file);
	fclose(file);
	numberOfRecords++;
	sort_file();
}

void search_by_roll(struct StdDetail data, int search_roll){
	FILE* file = fopen("std.dat", "a+b");
	int label = 1;
	while(fread(&data, sizeof(struct StdDetail), 1, file)){
		if(data.roll == search_roll){
			printf("%d    %s    %d\n", data.roll, data.name, data.marks);
			label = 0;
			break;
		}
	}
	if(label)
		printf("\nNo record found!\n");
	fclose(file);
}

void search_by_name(struct StdDetail data, char* search_name){
	FILE* file = fopen("std.dat", "a+b");
	int label = 1;
	while(fread(&data, sizeof(struct StdDetail), 1, file)){
		if(strcmp(data.name, search_name)==0){
			printf("%d    %s    %d\n", data.roll, data.name, data.marks);
			label = 0;
		}
	}
	if(label)
		printf("\nNo record found!\n");
	fclose(file);
}

void search_by_marks(struct StdDetail data, int search_marks){
	FILE* file = fopen("std.dat", "a+b");
	int label = 1;
	while(fread(&data, sizeof(struct StdDetail), 1, file)){
		if(data.marks == search_marks){
			printf("%d    %s    %d\n", data.roll, data.name, data.marks);
			label = 0;
		}
	}
	if(label)
		printf("\nNo record found!\n");
	fclose(file);
}

void view_list(struct StdDetail data){
	FILE* file = fopen("std.dat", "a+b");
	while(fread(&data, sizeof(struct StdDetail), 1, file))
        printf("%d    %s    %d\n", data.roll, data.name, data.marks);
    fclose(file);
}

void delete_record(struct StdDetail data, int delete_roll){
	FILE* file = fopen("std.dat", "a+b");
	FILE* file2 = fopen("temp.dat", "a+b");
	while(fread(&data, sizeof(struct StdDetail), 1, file)){
		if(data.roll!=delete_roll){
			fwrite(&data, sizeof(struct StdDetail), 1, file2);
		}
	}
	fclose(file);
	fclose(file2);
	remove("std.dat");
	rename("temp.dat", "std.dat");
	numberOfRecords--;
	sort_file();
}

void edit_roll(struct StdDetail data, int edit_roll_number, int new_roll){
	FILE* file = fopen("std.dat", "a+b");
	int label = 1;
	struct StdDetail replace_data;
	while(fread(&data, sizeof(struct StdDetail), 1, file)){
		if(data.roll == edit_roll_number){
			replace_data.roll = new_roll;
			strcpy(replace_data.name, data.name);
			replace_data.marks = data.marks;
			label = 0;
			break;
		}
	}
	fclose(file);
	if(label)
		printf("\nNo record found!\n");
	else{
		delete_record(data, edit_roll_number);
		FILE* file2 = fopen("std.dat", "a+b");
		fwrite(&replace_data, sizeof(struct StdDetail), 1, file2);
		fclose(file2);
	}
	sort_file();
}

void edit_name(struct StdDetail data, int edit_roll_number, char* new_name){
	FILE* file = fopen("std.dat", "a+b");
	int label = 1;
	struct StdDetail replace_data;
	while(fread(&data, sizeof(struct StdDetail), 1, file)){
		if(data.roll == edit_roll_number){
			replace_data.roll = data.roll;
			strcpy(replace_data.name, new_name);
			replace_data.marks = data.marks;
			label = 0;
			break;
		}
	}
	fclose(file);
	if(label)
		printf("\nNo record found!\n");
	else{
		delete_record(data, edit_roll_number);
		FILE* file2 = fopen("std.dat", "a+b");
		fwrite(&replace_data, sizeof(struct StdDetail), 1, file2);
		fclose(file2);
	}
	sort_file();
}

void edit_marks(struct StdDetail data, int edit_roll_number, int new_marks){
	FILE* file = fopen("std.dat", "a+b");
	int label = 1;
	struct StdDetail replace_data;
	while(fread(&data, sizeof(struct StdDetail), 1, file)){
		if(data.roll == edit_roll_number){
			replace_data.roll = data.roll;
			strcpy(replace_data.name, data.name);
			replace_data.marks = new_marks;
			label = 0;
			break;
		}
	}
	fclose(file);
	if(label)
		printf("\nNo record found!\n");
	else{
		delete_record(data, edit_roll_number);
		FILE* file2 = fopen("std.dat", "a+b");
		fwrite(&replace_data, sizeof(struct StdDetail), 1, file2);
		fclose(file2);
	}
	sort_file();
}

main(){
	int done = 0, search_roll, search_marks, delete_roll, edit_roll_number, select_edit, new_roll, new_marks;
	char search_name[30], new_name[30];
	struct StdDetail data;
	while(done!=8){
		printf("\n1. Add record\n");
		printf("2. Search by roll\n");
		printf("3. Search by name\n");
		printf("4. Search by marks\n");
		printf("5. View list\n");
		printf("6. Delete a record\n");
		printf("7. Edit a record\n");
		printf("8. Exit\n");
		printf("\nEnter your option:\n");
		scanf("%d", &done);
		switch(done){
			case 1:
				printf("Enter roll:\n");
				scanf("%d", &data.roll);
				printf("Enter name:\n");
				fflush(stdin);
				gets(data.name);
				printf("Enter marks:\n");
				scanf("%d", &data.marks);
				add(data);
				break;
			case 2:
				printf("Enter roll:\n");
				scanf("%d", &search_roll);
				search_by_roll(data, search_roll);
				break;
			case 3:
				printf("Enter name:\n");
				fflush(stdin);
				gets(search_name);
				search_by_name(data, search_name);
				break;
			case 4:
				printf("Enter marks:\n");
				scanf("%d", &search_marks);
				search_by_marks(data, search_marks);
				break;
			case 5:
				view_list(data);
				break;
			case 6:
				printf("Enter roll:\n");
				scanf("%d", &delete_roll);
				delete_record(data, delete_roll);
				break;
			case 7:
				printf("Enter roll:\n");
				scanf("%d", &edit_roll_number);
				printf("\nWhat to change?\n1. Roll\n2. Name\n3. Marks\n");
				scanf("%d", &select_edit);
				switch(select_edit){
					case 1:
						printf("Enter new roll:\n");
						scanf("%d", &new_roll);
						edit_roll(data, edit_roll_number, new_roll);
						break;
					case 2:
						printf("Enter new name:\n");
						fflush(stdin);
						gets(new_name);
						edit_name(data, edit_roll_number, new_name);
						break;
					case 3:
						printf("Enter new marks:\n");
						scanf("%d", &new_marks);
						edit_marks(data, edit_roll_number, new_marks);
						break;
				}
				break;
			case 8:
				printf("\nRecord saved successfully..");
				break;
			default:
				printf("Invalid input");
		}
	}
}