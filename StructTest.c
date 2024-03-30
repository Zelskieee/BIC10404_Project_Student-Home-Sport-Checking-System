#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define BUFFER_SIZE 4096

//make struct Information
struct Information
{
	char Name[20];
	char Class[20];
	int Id;
	char HomeSports[20];
	char SportEvent[20];
	

};

//to change name of the struct
typedef struct Information Information;

//struct Node
struct Node
{
	//declaration of data with datatype Information
	Information data;
	struct Node *nextPtr;
};

typedef struct Node Node;
Node *headPtr=NULL,
	 *newPtr,
	 *prevPtr,
	 *currPtr,
	 *tempPtr;
	 
Information inputData;

//declaration of function
bool parse_int(char *string,int *Id);
void display();
int search(int Id);
void update();
void deleted();
void sort();
void Sorted();
void Instruction();
void menu(Information data);

int main()
{
	char Name[20];
	char Class[20];
	int Id;
	char HomeSports[20];
	char SportEvent[20];
	
	headPtr = NULL;
	int value;
	
	//switch case use for user to enter what they want to do
	while(value!=7)
	{
		printf("\n\t--Welcome to HomeSport checking program--");
		Instruction();
		
		printf("\n\tEnter your choice:");
		scanf("%d",&value);
		switch(value)
		
		{
			case 1://for user to input data
				system("cls");
				menu(inputData);
				break;
				
			case 2://for system to display data
				system("cls");
				display();
				break;
							
			case 3://for system to search data	
				system("cls");
				displayS();
				break;
				
			case 4://for system to sort data
				system("cls");
				Sorted();
				break;
				
			case 5://for system to delete data	
				system("cls");
				deleted();
				break;
					
			case 6://for system to update data
				system("cls");
				update();
				break;
				


		}
		printf("\n\tPlease choose again..");
	}
	printf("End Program");
}

//function instruction
void Instruction()
{
	
	printf("\n\tYour Choice:");
	printf("\n\t ################");
	printf("\n\t #1.Input       #");
	printf("\n\t #2.Display     #");
	printf("\n\t #3.Search      #");
	printf("\n\t #4.Sorted      #");
	printf("\n\t #5.Delete      #");
	printf("\n\t #6.Update      #");
	printf("\n\t #7.End Program #");
	printf("\n\t ################");
}

//function to check data is integer or not
bool parse_int(char *string,int *Id)
{
	int i=0;
	
	while (isspace(string[i])) i++;
	
	// strlen will return the length of the string
	int length = strlen(string);
	
	if (length == i) return false;
	
	char integer_buffer[BUFFER_SIZE];
	int integer_chars = 0;
	

	while (i < length && !isspace(string[i]))//keep on looping one character at a time
	{
		if (!isdigit (string[i]))return false;
		integer_buffer[integer_chars] = string[i];
		
		integer_chars++;
		i++;
	}
	
	integer_buffer[integer_chars] = '\0';
	
	while (isspace(string[i])) i++;//loop through
	
	if ( string[i] != '\0') return false;
	
	*Id = atoi(integer_buffer);//take the string representation integer function and make it actual integer value
	
	return true;
}

//function menu
void menu(Information data)
{
	
	
	int Id =0;
	bool parsed_correct =true;//declaration for checking data
	do
	{
		
		printf("\nPlease enter your id:");
		
		char buffer[BUFFER_SIZE];
		
		fgets(buffer, BUFFER_SIZE, stdin);//read from standard in and store the character into buffer character array up to buffer size
		
		parsed_correct = parse_int(buffer,&inputData.Id);//pass the integer pointer into integer variable
		
		if(!parsed_correct)
		{
			printf("Check again..");
		}
		
	}while(!parsed_correct);
	
	fflush (stdin);
	printf("Please enter your Name:");
	gets(inputData.Name);
	printf("Please enter your class:");
	gets(inputData.Class);
	printf("Please enter your Home Sport:");
	gets(inputData.HomeSports);
	printf("Please enter your Sport Event:");
	gets(inputData.SportEvent);
	fflush (stdin);
	
	//to allocate the memory of Node
	newPtr=malloc(sizeof(Node));
	
	
	if(newPtr !=NULL)
	{
		newPtr->data = inputData;//store data from input data
		newPtr->nextPtr = NULL;
		
		prevPtr=NULL;
		currPtr=headPtr;//head pointer assign to currennt pointer
		
		//loop to find the right position in the linked list
		while (currPtr!=NULL && inputData.Id > currPtr->data.Id)
		{
			prevPtr = currPtr;
			currPtr = currPtr->nextPtr;
		}
			//insert a new node at the beginning of a linked list
			if (prevPtr == NULL)
			{
				newPtr->nextPtr = headPtr;
				headPtr = newPtr;
			}
		
			else
			{
				//insert a new node in the middle or at the end of the linked list
				prevPtr->nextPtr = newPtr;
				newPtr->nextPtr = currPtr;
			}	
	}
		
	else
	printf("\nThe data are not inserted.Please insert back the data..");
	
}

//function display
void display()
{
	//display content of the linked list
	currPtr = headPtr;
	if(headPtr == NULL)
	{
		printf("Your data is not found (>_<) Please try again.");
		
	}
	else
	{
		while (currPtr !=NULL)
		{
			printf("\nId Number:%d",currPtr->data.Id);
			printf("\nName:");
			puts(currPtr->data.Name);
			printf("Class:");
			puts(currPtr->data.Class);
			printf("Home Sport:");
			puts(currPtr->data.HomeSports);
			printf("Sport you entered:");
			puts(currPtr->data.SportEvent);
			currPtr = currPtr->nextPtr;
		}
	}
}

//function searching
int search(int searchingId)
{
	int Search;
	
		//to check if the Id that the user search is the same as system
		if(headPtr->data.Id == searchingId)
		{
			tempPtr = headPtr;
			Search=1;
		}
		else
		{
			prevPtr = headPtr;
			currPtr = headPtr ->nextPtr;
			
			//loop to find the right position in the linked list
			while(currPtr!=NULL && currPtr->data.Id != searchingId)
			{
				prevPtr = currPtr;
				currPtr = headPtr->nextPtr;
			}
			
				
			if( currPtr!=NULL)
	
			{
				tempPtr=currPtr;
				Search=2;
			}
			else
			Search=-1;
			
		}
	return Search;
}

int displayS()
{
	int searching;
	int location;
	
	printf("\n\n Please enter the data that you want to search:");
	scanf("%d",&searching);
	
	//to call back the function search
	location = search(searching);
	
	if(location != -1)
	{
		printf("\nId Number:%d",tempPtr->data.Id);
		printf("\nName:");
		puts(tempPtr->data.Name);
		printf("Class:");
		puts(tempPtr->data.Class);
		printf("Home Sport:");
		puts(tempPtr->data.HomeSports);
		printf("Sport you entered:");
		puts(tempPtr->data.SportEvent);
	}
	else
	{
		printf("The data that you search is not available in the store...\n");
	}
		
}

//function deleted
void deleted()
{
	int deletion;
	int location1;
	
	//prompt user to enter data to be deleted
	printf("\n\nPlease enter the data that you want to delete:");
	scanf("%d",&deletion);
	
	//to call back function search
	location1 = search(deletion);
	
	
	while(location1 ==-1)
	{
		printf("Sorry!the data is not found.Please Try again!");
		scanf("%d",&deletion);
		
		location1 = search(deletion);
	}
	if(location1 == 1)
	{
		//delete the node search
		headPtr = headPtr->nextPtr;
		free(tempPtr);
	}
	else if(location1 ==2)
	{
		//delete the node search
		prevPtr->nextPtr = currPtr->nextPtr;
		free(tempPtr);
		
	}
	printf("Data deleted...");
	currPtr=headPtr;
}

//function sort
void sort()
{
	int size=0;
	Information hold;
	
	currPtr = headPtr;//to assign headPtr into currPtr
	
	//Keep track the list of node
	while(currPtr !=NULL)
	{
		size =size+1;
		currPtr= currPtr->nextPtr;
	}
	
	
	int i;
	
	//to make node sort in ascending order
	for(i=1; i< size ; i++)
	{
		prevPtr = headPtr;
		currPtr = prevPtr->nextPtr;
		
		int j;
		
		for(j=1 ; j<size ; j++)
		{
			
			//to sort the Node in order
			if(prevPtr->data.Id > currPtr->data.Id)
			{
				hold = prevPtr->data;
				prevPtr->data= currPtr->data;
				currPtr->data = hold;
			}
		
			prevPtr = currPtr;
			currPtr = currPtr->nextPtr;
		}
	}
}

//function Sorted
void Sorted()
{
	sort();//call function
	
	currPtr = headPtr;
	
	while(currPtr != NULL)
	{
		printf("\nId Number:%d",currPtr->data.Id);
		printf("\nName:",currPtr->data.Name);
		printf("Class:");
		puts(currPtr->data.Class);
		printf("Home Sport:");
		puts(currPtr->data.HomeSports);
		printf("Sport you entered:");
		puts(currPtr->data.SportEvent);
		
		currPtr = currPtr->nextPtr;
	}
}

//update
void update()
{
	int updating;
	int location;
	int choice;
	
	
	//prompt user to enter which want to update
	printf("What do you want to update:");
	printf("\n1.Id");
	printf("\n2.Name");
	printf("\n3.Class");
	printf("\n4.Home Sport");
	printf("\n5.Sport Event");
	
	//prompt user to enter their choice
	printf("\nPlease enter your choice:");
	scanf("%d",&choice);
	
	switch (choice)
	{

	
		case 1:
			
			//prompt user to enter data Id to update
			printf("\n\n Please enter the Id data that you want to update:");
			scanf("%d",&updating);
	
	
	
			location = search(updating);
	
			if(location != -1)
			{
				int Id;
		
	
				printf("\nSearching Id:%d",tempPtr->data.Id);
				printf("\nlocation founded!");
				fflush(stdin);
				printf("\nEnter New Id:");
				scanf("%d",&tempPtr->data.Id);
				printf("Your new data is :%d \n",tempPtr->data.Id);	
			}
			else
			{
				printf("The data that you search is not available in the store...");
			}
			break;
			
		case 2:
			
			//prompt user to enter data Id to update
			printf("\n\n Please enter the data Id that you want to update:");
			scanf("%d",&updating);
	
	
	
			location = search(updating);
	
			if(location != -1)
			{
				int Id;
		

				printf("\nSearching Name for Id:%d",tempPtr->data.Id);
				printf("\nlocation founded!");
				fflush(stdin);
				printf("\n\nEnter New Name:");
				gets(tempPtr->data.Name);
				printf("Your new data is :");
				puts(tempPtr->data.Name);	
				printf("\n");
			}
		else
			{
				printf("The data that you search is not available in the store...");
			}
			break;
			
		case 3:
			
			//prompt user to enter data Id to update
			printf("\n\n Please enter the data Id that you want to update:");
			scanf("%d",&updating);
	
	
	
			location = search(updating);
	
			if(location != -1)
			{
				int Id;
		

				printf("\nSearching Class for Id:%d",tempPtr->data.Id);
				printf("\nlocation founded!");
				fflush(stdin);
				printf("\n\nEnter New Class:");
				gets(tempPtr->data.Class);
				printf("Your new data is :");
				puts(tempPtr->data.Class);	
				printf("\n");
			}
			else
			{
				printf("The data that you search is not available in the store...");
			}
			break;
			
		case 4:
			
			//prompt user to enter data Id to update
			printf("\n\n Please enter the data Id that you want to update:");
			scanf("%d",&updating);
	
	
	
			location = search(updating);
	
			if(location != -1)
			{
				int Id;
		
				
				printf("\nSearching Class for HomeSports:%d",tempPtr->data.Id);
				printf("\nlocation founded!");
				
				fflush(stdin);
				printf("\nEnter New HomeSport:");
				gets(tempPtr->data.HomeSports);
				printf("Your new data is :");
				puts(tempPtr->data.HomeSports);	
				printf("\n");
			}
			else
			{
				printf("The data that you search is not available in the store...");
			}
			break;
			
		case 5:
			
			//prompt user to enter data Id to update
			printf("\n\n Please enter the data Id that you want to update:");
			scanf("%d",&updating);
	
	
	
			location = search(updating);
	
			if(location != -1)
			{
				int Id;
		
				
				printf("\nSearching Class for HomeSports:%d",tempPtr->data.Id);
				printf("\nlocation founded!");
				
				fflush(stdin);
				printf("\nEnter New SportEvent:");
				gets(tempPtr->data.SportEvent);
				printf("Your new data is :");
				puts(tempPtr->data.SportEvent);	
				printf("\n");
			}
			else
			{
				printf("The data that you search is not available in the store...");
			}
			break;
			
			
	}
		
	

}
