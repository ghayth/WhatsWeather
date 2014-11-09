#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <curl/curl.h>
#include "utils.h"
#include "stringsDef.h"
#include "errorsConstants.h"


static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
struct MemoryStruct {
  char *memory;
  size_t size;
};

int main(void)
{
  CURL *curl_handle;
  CURLcode res;
  
  char *townName=(char *) secure_malloc(1);
  char c=' ';
  size_t townName_size=1;
  int choice=TOWN_NAME;
  char *name_validity_pointer=NULL;
  int query_strin_Size=strlen(initValue_queryValue)+1;
  char *query_string=(char *)secure_malloc(query_strin_Size);
  
  struct MemoryStruct chunk;
  

  secure_strcpy(query_string,initValue_queryValue);
  
  ////////////////////////////////begin big while LOOP
          while(1)
        {
            
            
			switch(choice)
            {

            case PRINT_TEMPERATURE:
                system("cls");
                print_temp(chunk.memory);
				printf("\nPress anything to go back..");
                _getch();
                break;
            case PRINT_HUMIDITY:
                system("cls");
                print_humidity(chunk.memory);
                printf("\nPress anything to back..");
                _getch();
                break;
            case TOWN_NAME:
                 name_validity_pointer= NULL;
				 while(name_validity_pointer==NULL){
								
							  
							  chunk.memory =(char*) secure_malloc(1);  /* will be grown as needed by the realloc above */ 
							  chunk.size = 0;    /* no data at this point */ 
 							  curl_global_init(CURL_GLOBAL_ALL);
 							  /* init the curl session */ 
							  curl_handle = curl_easy_init();
							  /* specify URL to get */ 
							  printf("\nplease enter townName:");
							  
							  if(townName)
								  {
									  free(townName);
							          townName=NULL;
							      }
							 							  
							  townName_size=1;
							  c=' ';
							  townName=(char *) secure_malloc(1);
							  							 
							while(1)
							  {
								  c=_getch();
								  if((int)c == ASCII_Code_ENTER)
									  break;
								  printf("%c",c);
								  townName[townName_size-1]=c;
								  townName[townName_size]='\0';
								  townName_size++;
								  townName=(char *) realloc(townName,townName_size+1);

							  }
							  townName[townName_size]='\0';

							  secure_strcpy(query_string,initValue_queryValue);
							  query_strin_Size = strlen(initValue_queryValue)+townName_size+strlen(lastPart_queryValue)+1;
							  query_string=(char *) realloc(query_string,query_strin_Size);
							  
							  strcat_s(query_string,townName_size,townName);
							  strcat_s(query_string,strlen(lastPart_queryValue),lastPart_queryValue);
							  query_string[query_strin_Size]='\0';
							  
							  curl_easy_setopt(curl_handle, CURLOPT_URL, query_string);
							  /* send all data to this function  */ 
							  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
							  /* we pass our 'chunk' struct to the callback function */ 
							  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
							  /* some servers don't like requests that are made without a user-agent
								 field, so we provide one */ 
							  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
							  /* get it! */ 
							  res = curl_easy_perform(curl_handle);
							  /* check for errors */ 
							  if(res != CURLE_OK) {
								fprintf(stderr, "Connection to the server failed: %s\n",	curl_easy_strerror(res));
							  }
							  else {
								/*
								 * Now, our chunk.memory points to a memory block that is chunk.size
								 * bytes big and contains the remote file.*/
								
								name_validity_pointer=strstr(chunk.memory,"Error: Not found city");
								if(name_validity_pointer!=NULL)
									{

										printf("please enter a valid town name ,you have entered %s\n",townName);
										free_dynamicVar(chunk.memory);
										name_validity_pointer=NULL;
					
									}
								else{
										
										name_validity_pointer = (char *) !NULL;
	
									}
							  }
						  
	

					  }
				 printf("\nThe town name %s is accepted",townName);
				 Sleep(SECOND);
					break;
            case ABOUT_APPLICATION:
                system("cls");
                printAbout();
				printf("\nPress anything to back..");
                _getch();
                break;
            case EXIT:
                printf("Please enter any key to exit the Weather Application..");
				_getch();
                break;

            }
			if(choice == EXIT) 
				break;
			system("cls");
            printf("Welcome to Embedded Weather Station !\n");
            printf("************The Menu ***************\n");
            printf("1) Consult the temperature\n");
            printf("2) Consult the humidity\n");
            printf("3) change the town's name\n");
            printf("4) About the application\n");
            printf("5) exit the application\n");
            printf("\nPlease enter a valid choice: (between 1 and 5):");

			choice = DEFAULT;
			choice = (int)_getch() - ASCII_Code_0;
            while((choice < PRINT_TEMPERATURE) || (choice > EXIT))
            {
				choice=(int)getchar()-ASCII_Code_0;
				
			}
        }
    
  ///////////////////////////////end big while
	 /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
  free_dynamicVar(chunk.memory);
  free_dynamicVar(query_string);
  /* we're done with libcurl, so clean it up */ 
  curl_global_cleanup();

  return 0;
}



static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory =(char *) realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
