
#include <stdio.h>
#include "inverted_index.h"

int save_DB(main_node_t **head,char *filename)
{
	FILE *fptr=fopen(filename,"w");//opening the file in which the database must be saved
	for(int i=0;i<27;i++)//loop to save all the indexes which are not null
	{
		if(head[i]!=NULL)
			write_tofile(head[i],fptr); //function to save contents of that index
	}
	fclose(fptr); //closing the opened file
	return SUCCESS;
}

void write_tofile(main_node_t *head,FILE *fptr)
{
	int ind;
	while(head!=NULL) //traverse until the last main node
	{
		ind=(toupper(head->word[0])%65); //finding the index
		if(ind>25)
			ind=26;
		fprintf(fptr,"#[%d];\n%s;%d;",ind,head->word,head->f_count); //saving the index, word and the file count

		sub_node_t *temp=head->sub_link;
		
		while(temp!=NULL) //traversing until the last sub node
		{
			fprintf(fptr,"%s;%d;",temp->f_name,temp->w_count);//saving the file name and word count 
			temp=temp->link;
		}
		fprintf(fptr,"#\n"); //# marking after the end of each index and also starts at the new line
		head=head->link;
	}
}

