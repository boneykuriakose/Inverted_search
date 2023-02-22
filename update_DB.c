
#include "inverted_index.h"
#include <stdio.h>

int update_DB(file_node_t **file_head,main_node_t **head,char *filename)
{
	if(IsFileValid(filename)==FAILURE) //validating the inputed file
	{
		printf("File not added to file list!\n");
		return FAILURE;
	}
	else
	{
		if(store_filenames_to_list(filename,file_head)==FAILURE) //checking if the file inpted already exist in the linkedlist
		{
			printf("File already exist in the file list!\n");
			return FAILURE;
		}
		else 
		{
			printf("%s added the file list successfully\n",filename);
			read_datafile(*file_head,head); //updating the database
			return SUCCESS;
		}
	}
	return FAILURE;
}

