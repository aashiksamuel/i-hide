/*
 *checkbmp.h
 *----------
 *  Function to Check whether a given input image file is valid
 *
 *  Author : Aashik Samuel
 *  Email : codeaash@gmail.com
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int get_ifile(char inImgFileName[]);									    //Gets the name of input Image File
int check_file(char inImgFileName[],size_t *inFileSize);					//Checks if the file is valid or not
int setLSBZero(char inImgFileName[],size_t inFileSize);                     //Sets the LSB of input Image file as zero

/*
 * Function : get_ifile
 * --------------------
 *  Input function to get the file from user
 *
 *  inImgFileName : Variable holding filename, passwd by reference
 *
 *  returns: 1 if the function is executed successfully
 *
 */
int get_ifile(char inImgFileName[]){
	printf("\nEnter the path of file : ");
	scanf("%s",inImgFileName);
    return 1;
}

/*
 * Function : check_file
 * ---------------------
 *  Checks if the file provided by the user is a valid BMP image
 *      Works by checking the Magic Number of the file
 *
 *  magicNum : String holding the magicnumber value of input file
 *  inFileSize : Referenced variable holding the image file size from 2nd byte of magic number
 *
 *  returns: 0 - If the file is invalid or doesn't exist
 *           1 - If the file is valid
 *
 */
int check_file(char inImgFileName[],size_t *inFileSize){
	FILE *fp;
	char magicNum[3]="\0";
	fp = fopen(inImgFileName,"rb");
	if(fp==NULL){
		return 0;															//Returns 0 if file doesn't exist
	}
	else{
		magicNum[0]=fgetc(fp);
		magicNum[1]=fgetc(fp);
		if(!strcmp(magicNum,"BM")){
			*inFileSize=getw(fp);                                           //Reading file size from magic numbers of file
			fclose(fp);
			return 1;														//Returns 1 if file is valid
		}
		else{
			fclose(fp);
			return 0;														//Returns 0 if the file is invalid

		}

	}
}

/*
 *Function :  setLSBZero
 *----------------------
   Sets the LSB of all bytes as 0, starting from 100th byte
    by right shifting and left shifting

 * ch : Temporary variable holding one byte at a time
 *
 */
int setLSBZero(char inImgFileName[],size_t inFileSize){
	FILE *fp;
	char ch;
	fp=fopen(inImgFileName,"rb+");
	fseek(fp,100,SEEK_SET);
	while((ch = getc(fp))!= EOF){
		ch=ch>>1;
		ch=ch<<1;

		fseek(fp,-1,SEEK_CUR);
		fwrite(&ch,sizeof(ch),1,fp);
	}
	fclose(fp);
    return 1;
}
