/*
 * ------
 *  Final implemenation of steganography
 *
 *  Author : Aashik Samuel
 *  Email: codeaash@gmail.com
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"checkbmp.h"
#include"secretmsg.h"
#include"stegano.h"

int main(){

	char inImgFileName[FILENAME_MAX]="\0", outImgFileName[FILENAME_MAX], mFileName[FILENAME_MAX], sMsg[1000];
 	size_t inFileSize;
 	int tSwitch,choice;
	while(1){
label: 		printf("\ni-hide\n\n1)Hide\n2)Show\n3)Exit\n\tEnter Your Choice : ");
 			scanf("%d",&choice);
 			switch(choice){
 				case 1 : l1:get_ifile(inImgFileName);
				 			if(!check_file(inImgFileName,&inFileSize)){
								printf("\n\n\tERR : Enter a valid BMP File");
								goto l1;
							}
 					 		setLSBZero(inImgFileName,inFileSize);
 					 		tSwitch=get_message();
					 		if(tSwitch == 1)
					 			get_text(sMsg,inFileSize);
					 		else
					 			get_mfile(mFileName);
					 		write_msg(inImgFileName,tSwitch,sMsg,mFileName);
					 		break;

				case 2 :  /*l2:	get_ifile(inImgFileName);
								if(!check_file(inImgFileName,&inFileSize)){
									printf("\n\n\tERR : Enter a valid BMP File");
									goto l2;}
									*/
					  			read_msg();
					  			//printf("\n\nThe Hidden Message is : \n");
					  			system("cat ~");
					  			printf("\n\n The hidden message is saved in a file Secret.txt in your home directory\n\n");
					  			break;

				case 3 : return 0;

				default: printf("\nEnter a valid choice ");
					 goto label;
 			}
	}
}
