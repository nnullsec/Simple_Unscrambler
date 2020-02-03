#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int main(int argc, char **argv){
	FILE *list;
	int sz;
	if(!(list=fopen(argv[1],"r"))){
		perror("error");
		printf("error code: %d\n",errno);
		exit(-1);
	}
	else{
		fseek(list,0L,2);
		sz=ftell(list);
		rewind(list);
	}
	char buff[sz];
	int i=0;
	while(i<sz)	buff[i++]=fgetc(list);
	fclose(list);
    
/*************************************************
*************************************************/

	FILE *parsed_list;
	parsed_list=fopen("parsed_list.txt","w+");
	int count=0;
	for(i=0;i<sz;i++){			//NEW_LINE '\n'
		if(isspace(buff[i])&&buff[i]!=0x0a){
			continue;
		}
		else if(buff[i]==0x0a){
			fputc(0x0a/*'\0'*/,parsed_list);
			int j=i;
			while(isspace(buff[j])){
				i=j++;
			}
		}
		else if(isgraph(buff[i])){
			fputc(buff[i],parsed_list);
		}
	}
	fclose(parsed_list);
    
/*************************************************
*************************************************/

	parsed_list=fopen("parsed_list.txt","r");
	FILE *wordlist;
	if(!(wordlist=fopen(argv[2],"r"))){
		perror("error");
		printf("error code: %d\n",errno);
		exit(-1);
	}
    
/*************************************************
*************************************************/
	
    int flag,cnt=0;
	char buff1[16],buff2[16];
	while(fgets(buff1,16,parsed_list)!=NULL){
		flag=0;
		rewind(wordlist);
		while((fgets(buff2,16,wordlist)!=NULL)&&(flag==0)){
			if(strlen(buff1)==strlen(buff2)-1){
				if(strspn(buff1,buff2)==strlen(buff1)){
					if(flag=1)	++cnt;
					for(i=0;isprint(*(buff2+i));i++)
						printf("%c",*(buff2+i));
					if(cnt<10)
						printf(",");
				}
			}
		}
	}
	fclose(parsed_list);
	fclose(wordlist);
	printf("\n");
	return 0;
}
