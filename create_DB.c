
#include <stdio.h>
#include "inverted_index.h"

int create_DB(file_node_t *file_head,main_node_t **head)
{
	while(file_head!=NULL) //loop to provide the files to read_datafile function
	{
		read_datafile(file_head,head); 
		file_head=file_head->link;
	}
	return SUCCESS;
}
void read_datafile(file_node_t *filehead,main_node_t **head)
{
	FILE *fptr=fopen(filehead->f_name,"r"); //opening the file in read mode
	rewind(fptr);
	char word[20];
	int flag,ind=0;
	while(fscanf(fptr,"%s",word)!=EOF) //intaking each word from the file to the charater string word
	{
		flag=1;
		ind=(toupper(word[0])%65); //finding index of word
		if(ind>25)
			ind=26;
		
		if(head[ind]!=NULL) //checking if the address at index value is not null
		{
			main_node_t *temp=head[ind]; //temporary variable to traverse throught the main nodes
			while(temp!=NULL)
			{
				if(strcmp(temp->word,word)==0) //checking if word is already present in any main nodes 
				{
					update_word_count(&head[ind],filehead->f_name); //if present function is called to update the word count
					flag=0; //setting flag to 0
				}
				temp=temp->link; //traverse
			}
		}
		if(flag==1) //if none of the words in the main nodes matched the current word
		{
			insert_at_last_main(&head[ind],word,filehead->f_name); //function is called to create a new main node
		}
	}
	printf("Database created for %s\n",filehead->f_name);
}

int insert_at_last_main(main_node_t **head,char *word,char *filename)
{
	main_node_t *new=malloc(sizeof(main_node_t));

	new->f_count=1; //initializing the main node 
	strcpy(new->word,word);
	new->link=NULL;

	update_link_table(&new,filename); //function call to update the sub node to the main node

	if(*head==NULL) //if the address at the index is null
	{
		*head=new;
		return SUCCESS;
	}
	main_node_t *temp=*head;
	while(temp->link!=NULL) //if the address at the index is not null then traverse untill the end
		temp=temp->link;
	temp->link=new; //then putting address of new to the link part of last node
	return SUCCESS;
}

int update_link_table(main_node_t **head,char *filename)
{
	sub_node_t *new2=malloc(sizeof(sub_node_t));
	if(new2==NULL) 
		return FAILURE;
	new2->w_count=1; //initializing the sub node with required values
	strcpy(new2->f_name,filename);
	new2->link=NULL;

	(*head)->sub_link=new2; //updating the sub link part of the main node with the address of new2
	return SUCCESS;
}

int update_word_count(main_node_t **head,char *filename)
{
	main_node_t *temp2=*head;
	sub_node_t *temp=(*head)->sub_link; //taking temp and prev pointer variables of type sub node
	sub_node_t *prev=(*head)->sub_link;

	while(temp!=NULL) //traversing through all the sub nodes
	{
		if(strcmp(temp->f_name,filename)==0) //checking if the file names are same
		{
			temp->w_count++; //if yes incrementing the word count
			return SUCCESS;
		}
		prev=temp;
		temp=temp->link;
	}

	sub_node_t *new=malloc(sizeof(sub_node_t)); //if the files are not same then new sub node is to be created
	if(new==NULL)
		return FAILURE;
	new->w_count=1;  //initializing the sub node
	strcpy(new->f_name,filename);
	new->link=NULL;

	prev->link=new; //updating the link of prev with the address of new sub node

	temp2->f_count=temp2->f_count+1; //now incrementing the file count in the main node
	return SUCCESS;
}
