#include <stdio.h>
#include "inverted_index.h"

void validate_n_store_filenames(file_node_t **head,char *filename[])
{
	int i,count=0;
	while(filename[count]!=NULL)//counting the numer of files
		count++;
	for(i=1;i<count;i++) //loop to check each file
	{
		if(IsFileValid(filename[i])==SUCCESS) //function to validate the file
		{
			if(store_filenames_to_list(filename[i],head)==SUCCESS) //function to store the file in the single linkedlist
			{
				printf("The no.%d argument is valid and hence stored successfully\n",i);
			}
			else
				printf("The no.%d argument is not valid and storing failed\n",i);
		}
		else
			printf("The no.%d argument is not valid\n",i);
		printf("\n");
	}
}	
int IsFileValid(char *filename) 
{
	FILE *fptr=fopen(filename,"r"); //opening the file using file pointer
	if(fptr==NULL) //checking if the file exist
	{
		printf("File doesn't exist\t");
		//fclose(fptr);
		return FAILURE;
	}
	fseek(fptr,0,SEEK_END);
	if(ftell(fptr)==0) //checking if the file is empty 
	{
		printf("File empty\t");
		fclose(fptr);
		return FAILURE;
	}
	else
		return SUCCESS;
}
int store_filenames_to_list(char *filename,file_node_t **head)
{
	int value;
	file_node_t *new,*temp;
	if(*head==NULL) //if the list is empty
	{
		new=malloc(sizeof(file_node_t)); //creating new node for the file
		if(new==NULL)
		{
			printf("Memory allocation failed\n");
			return FAILURE;
		}
		else
		{
			strcpy(new->f_name,filename);//initializing the node
			new->link=NULL;
			*head=new; //storing address to the head
			return SUCCESS;
		}
	}
	else
	{
		temp=*head;
		while(temp!=NULL) //traversing through the linkedlist
		{
			value=strcmp(temp->f_name,filename); //checking if files match
			if(value==0)//then  failure condition not store to linkedlist
			{
				return FAILURE;
			}
			temp=temp->link;
		}
		new=malloc(sizeof(file_node_t));
		if(new==NULL)
		{
			printf("Memory allocation failed\n");
			return FAILURE;
		}
		else
		{
			strcpy(new->f_name,filename); //inserting the node at first
			new->link=*head;
			*head=new;
			return SUCCESS;
		}
	}
}
