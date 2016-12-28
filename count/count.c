#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

typedef struct Node{
    unsigned long int data;
    struct Node *next;
} Node;

typedef struct LinkedList{
    struct Node *head;
} LinkedList;

typedef struct HashTable{
    LinkedList *hashlist;
} HashTable;

Node *createNode(unsigned long int data, Node *next)
{
    Node *new= malloc(sizeof(Node));
    new->data = data;
    new->next = next;
    return new;
}

void addToFront(struct LinkedList *list, unsigned long int data){
	Node *addition= createNode(data,NULL);
	if(list->head==NULL){
		list->head=addition;
	}
	else{
	addition->next=list->head;
	list->head=addition;
	}
	return;
}

int existsInList(struct LinkedList *list,unsigned long int target){
	Node *ptr;
	ptr=list->head;
	while(ptr!=NULL){
		if(ptr->data==target){
			return 1;
		}
		else{
			ptr=ptr->next;
		}
	}
	return 0;
}

int createHashKey(unsigned long int dnum){
	if (dnum < 0)
	        dnum *= -1;
	    return dnum % 1000;
}

int addToTable(struct HashTable *yolo, unsigned long int num){
	int key= createHashKey(num);
/*printf("%d and num is %lx\n",key,num);*/
	if((existsInList(&yolo->hashlist[key],num))==0){
		addToFront(&yolo->hashlist[key],num);
		return 1;
	}
	else{
		return 0;
	}

}


int main(int argc, char **argv){
FILE *fp;
int counter;
char *name;
unsigned long int hex;
HashTable *t;

if(argc!=2){
		printf("error");
		        return 0;
	}
	
	
	
	
	
	t= malloc(sizeof(HashTable*));
	t->hashlist = malloc(1000 * sizeof(LinkedList));
	counter=0;
	name= argv[1];
	fp= fopen(name,"r");
	if( fp == NULL ){
			printf("error");
			exit(0);
		}
	while((fscanf(fp,"%lx\n",&hex))==1){

if(addToTable(t,hex)==1){
		counter++;
	}

	}
	printf("%d",counter);
	free(t);
fclose(fp);
	return 0;
}
