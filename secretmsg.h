/*
 *secretmsg.h
 *------------
 * Functions to process secret message data/file
 *
 * Author : Aashik Samuel
 * Email : codeaash@gmail.com
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get_message();															//Gets the input secret message mode
int get_text(char message[],size_t fileSizeLimit);							//Gets the secret message as text input
int get_mfile(char mFileName[]);											//Gets the secret message as a file

/*
 * Function: get_message
 * ---------------------
 *      A simple Function to choose the specified input mode of secret message
 *
 *  returns: 1 if text
 *           2 if file
 */
int get_message(){
	int choice;
l1:	printf("\nSecret Message as \n\t1)Text\n\t2)File\nChoice : ");
	scanf("%d",&choice);
	if(choice==1)
		return 1;
	else if(choice==2)
		return 2;
	else{
		printf("\n\n\tERR : Enter a valid Choice ");
		goto l1;
	}
}

/*
 * Function: get_text
 * -----------------
 *      A simple Function to get the input secret message as text (~ acts as a delimitter)
 *
 *  returns 1 on success
 */
int get_text(char message[],size_t fileSizeLimit){
	strcpy(message,"null");
	printf("\n Characters Limit : %d",(fileSizeLimit-100)/8);
	printf(/*"\nNote:  '~' is limiting character*/"\nEnter Secret Message :\n\n--> ");
	scanf("\n%[^\n]s",message);
	return 1;
}

/* Function: get_mfile
 * -------------------
 *      A simple function to get the secret message as a file
 *
 * returns 1 on success
 */
int get_mfile(char mFileName[]){
	FILE *mFile;
	char ch;
l1:	printf("\nEnter path of text file : ");
	scanf("%s",mFileName);
	mFile=fopen(mFileName,"r");
	if(!mFile){
l2:		printf("\nEnter a valid File :(");
		goto l1;
	}
	else{
		while((ch=getc(mFile))!=EOF){
			if(ch<0 || ch>127){
				printf("\nNot a txt file");
				goto l2;
			}
		}
		return 1;
	}
}
