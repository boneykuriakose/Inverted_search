
#include <stdio.h>
#include "inverted_index.h"
/*void print_list(file_node_t *head) //function to print the single linked list that contain all the file names
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s -> ", head -> f_name);
		    head = head -> link;
	    }
	    printf("NULL\n");
    }
}*/

int main(int argc, char *argv[])
{
	if(argc==1) //checking if files are given as arguments
	{
		printf("No files passed as argument\n");
		return 0;
	}
	file_node_t *head=NULL; //declaring single linked list
	main_node_t *head2[27]={NULL}; //declaring the array of pointers for indexing
	validate_n_store_filenames(&head,argv); //function to validate all the files that are given through command line
    //print_list(head); //printing the single linkedlist
	printf("\n");
	char string[30]; 
	int choice,ind;
	while(1)
	{
		printf("Select your choice among following options:\n");
		printf("1. Create DATABASE\n2. Display Database\n3. Update DATABASE\n4. Search\n5. Save Database\n6. Exit\nEnter your choice\n");
		scanf("%d",&choice);
		printf("\n");
		switch(choice) //switch case to select options
		{
			case 1:
				if(create_DB(head,head2)==SUCCESS) //function call to create database
					printf("Data base created successfully\n\n");
				else
					printf("DB creation failed\n\n");
				break;
			case 2:
				if(display_DB(head2)==SUCCESS) //function call to display the database
					printf("\nDisplayed successfully\n\n");
				else
					printf("Failure in displaying\n\n");
				break;
			case 3:
				printf("Enter the filename that needed to be updated:"); //intaking the file to be updated
				scanf("%s",string);
				if(update_DB(&head,head2,string)==SUCCESS) //updating the database
				{
					printf("\n");
				}
				else
					printf("Failure in updating Database\n\n");
				break;
			case 4:
				printf("Enter the word to be searched:"); //intaking the word that need to be searched
				scanf("%s",string);
				ind=(toupper(string[0])%65); //finding the index
				if(ind>25)
					ind=26;
				if(search_DB(head2[ind],string)==SUCCESS) //function to search the word in the database
				{
					printf("\n");
				}
				else
					printf("Word not found in Database!\n\n");
				break;
			case 5:
				printf("Enter the filename to save Database:"); //intaking the file in which the database is to be stored
				scanf("%s",string); 
				if(save_DB(head2,string)==SUCCESS) //function to save the database in the given file
				{
					printf("Database saved successfully in %s\n\n",string);
				}
				else
					printf("Database not saved\n\n");
				break;
			case 6:
				return 0;
			default:
				printf("Invalid option entered\n\n");
		}
	}
}

