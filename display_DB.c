
#include <stdio.h>
#include "inverted_index.h"

int display_DB(main_node_t **head)
{
	int i;
	printf("[index]	 word	file_count	file(s):	file_name	word_count\n");//printing the format
	for(i=0;i<27;i++) //loop to print all the indices
	{
		if(head[i]!=NULL)
		{
			print_words(head[i]);
		}
	}
	return SUCCESS;
}

void print_words(main_node_t *head)
{
	int ind=0;
	while(head!=NULL) //loop to print all contents from the index
	{
		ind=(toupper(head->word[0])%65); //finding index
		if(ind>25) //proving the index 26 for all others than alphabets
			ind=26;
		printf("[%d]	%s 	%d		file(s): ",ind,head->word,head->f_count); //printing the word and file count from main node

		sub_node_t *subhead=head->sub_link; 
		while(subhead!=NULL) //loop to print contents of sub nodes
		{
			printf("	%s		%d",subhead->f_name,subhead->w_count); //printing the filename and word count from the sub node
			subhead=subhead->link;
		}
		printf("\n");
		head=head->link;
	}
}

