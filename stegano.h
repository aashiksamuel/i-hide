/*
 *stegano.h
 *---------
 *  Steganography Implementation
 *      perfroms encoding and decoding
 *
 *  Author: Aashik Samuel
 *  Email: codeaash@gmail.com
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int write_msg(char inImgFileName[],int tSwitch,char sMsg[],char mFileName[]);
int read_msg();

/*
 * Function: write_msg
 * -------------------
 *  A function to steganograph the secret msg(file/text) into the BMP image
 *      Every characters' each bit is extracted and saved into the LSB of each byte in image file
 *      to save 1 character 8 bytes are needed
 *
 *  inImgFileName: input image File name
 *  tSwitch: Variable value determining secret mesg's form
 *  sMsg: Contains secret msg if tSwitch=1 (i.e)text mode
 *  mFileName: Secret mesg filename if tSwitch=2
 *
 *  returns: 1 on success
 */
int write_msg(char inImgFileName[],int tSwitch,char sMsg[],char mFileName[]){
	FILE *fp;
	char fileCh,msgCh='\0',writeCh;
	int count=0;
	fp=fopen(inImgFileName,"rb+");
	fseek(fp,100,SEEK_SET);
	if(tSwitch==1){
		for(count=0;count<=strlen(sMsg);count++){
            fseek(fp,100+(count*8),SEEK_SET);
			for(int i=7;i>=0;i--){
                msgCh=sMsg[count];
                msgCh=msgCh<<i;
                msgCh=msgCh>>7;
				fileCh=fgetc(fp);
				fseek(fp,-1,SEEK_CUR);
				writeCh=fileCh&254;
				writeCh=writeCh|msgCh;
				fputc(writeCh,fp);
			}
        }
        fseek(fp,90,SEEK_SET);
        putw(count-1,fp);
    }
	else{
		FILE *tfp;
        size_t strLenCount=0;
        char tempMsgChr;
		tfp=fopen(mFileName,"r");
		while(msgCh!=EOF){
            msgCh = fgetc(tfp);
            fseek(fp,100+(strLenCount*8),SEEK_SET);
            strLenCount++;
			for(int i=7;i>=0;i--){
                tempMsgChr=msgCh;
                tempMsgChr=tempMsgChr<<i;
                tempMsgChr=tempMsgChr>>7;
			    fileCh=fgetc(fp);
				fseek(fp,-1,SEEK_CUR);
				writeCh=fileCh&254;
				writeCh=writeCh|tempMsgChr;
				fputc(writeCh,fp);
				}
		}
		fclose(tfp);
        fseek(fp,90,SEEK_SET);
        putw(strLenCount-2,fp);
	}
	fclose(fp);
	return 1;
}

/*Function: read_msg
 * -----------------
 *      A function which decodes message from a bmp file
 *          Places the decoded message in a file called Secret.txt at the working directory
 *
 */
/*int read_msg(char inImgFileName[]){
    printf("OPENED");
	FILE *fp,*otp;
	char msgCh=0,fileCh,readCh=0;
    int lenOfStr;
	fp=fopen(inImgFileName,"rb");
    if(!fp)
            printf("ERRRRRRRR");
    printf("Success");
	otp=fopen("Secret.txt","w");
    fseek(fp,90,SEEK_SET);
    lenOfStr=getw(fp);
    printf("txt size : %d",lenOfStr);
    //scanf("%c",&msgCh);
	fseek(fp,100,SEEK_SET);
	for(int i=0;i<13;i++){
        msgCh=0;
        //ftell(fp);
		for(int j=7;i>=0;j--){
			//fileCh=fgetc(fp);
			readCh=fileCh<<7;
			readCh=readCh>>j;
			msgCh=msgCh|readCh;
		}
        printf("\nCHAR - %c",msgCh);
		fputc(msgCh,otp);
	}
	fclose(fp);
	fclose(otp);
}*/

int read_msg(){
    FILE *inImgfp,*otp;
    char inImgFileNam[FILENAME_MAX],*home;
    home=getenv("HOME");
    strcat(home,"/Secret.txt");
    unsigned char msgCh,fileCh,readCh;
    size_t fileSize,lenOfStr;
l1: get_ifile(inImgFileNam);
    if(!check_file(inImgFileNam,&fileSize))
        goto l1;
    inImgfp=fopen(inImgFileNam,"rb");
    otp=fopen(home,"w");
    fseek(inImgfp,90,SEEK_SET);
    lenOfStr=getw(inImgfp);
    fseek(inImgfp,100,SEEK_SET);
    for(int i=0;i<lenOfStr+1;i++){
        msgCh='\0';
        for(int j=7;j>=0;j--){
            fileCh=fgetc(inImgfp);
            readCh=fileCh<<7;
            readCh=readCh>>j;
            msgCh=msgCh|readCh;
        }
        fputc(msgCh,otp);
    }
    fclose(inImgfp);
    fclose(otp);
    printf("\n The Secret Message is : \n\n");
    return 0;
}
