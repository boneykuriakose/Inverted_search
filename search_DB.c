
#include <stdio.h>
#include "inverted_index.h"

int search_DB(main_node_t *head,char *word)
{
	if(head==NULL) //if the address the index is null then searched word not found
		return FAILURE;
	while(head!=NULL)//traversing through all the main nodes
	{
		if(strcmp(head->word,word)==0) //checking if the words matches
		{
			printf("The word [%s] is present in %d files\n",head->word,head->f_count);
			sub_node_t *temp=head->sub_link;
			while(temp!=NULL) //traversing through the sub nodes 
			{
				printf("In file: %s %d times\n",temp->f_name,temp->w_count); //printing the files and how many times they are present
				temp=temp->link;
			}
			return SUCCESS;
		}
		head=head->link;
	}
	return FAILURE; //word not found
}


