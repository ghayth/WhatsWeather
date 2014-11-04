#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "tomtom.h"

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

int main(void)
{
  CURL *curl_handle;
  CURLcode res;
  char townName[townName_Size];
  int choice=3;
  char *name_validity_pointer=NULL;
  char *query_string=(char *)malloc(strlen(default_queryValue)+1);
  char *oldTownName=(char *)malloc(strlen(default_townName)+1);
  struct MemoryStruct chunk;
  
  strcpy(query_string,default_queryValue);
  strcpy(oldTownName,default_townName);
  ////////////////////////////////begin big while
          while(1)
        {
            
            
			switch(choice)
            {

            case 1:
                system("cls");
                print_temp(chunk.memory);
				printf("\nPress anything to go back..");
                getch();
                break;
            case 2:
                system("cls");
                print_humidity(chunk.memory);
                printf("\nPress anything to back..");
                getch();
                break;
            case 3:
                 name_validity_pointer= NULL;
				 while(name_validity_pointer==NULL){
								
							  
							  chunk.memory =(char*) malloc(1);  /* will be grown as needed by the realloc above */ 
							  chunk.size = 0;    /* no data at this point */ 
 							  curl_global_init(CURL_GLOBAL_ALL);
 							  /* init the curl session */ 
							  curl_handle = curl_easy_init();
							  /* specify URL to get */ 
							  printf("please enter townName:");
							  scanf_s("%s",&townName,townName_Size);
							  query_string=replace_str(query_string,oldTownName,townName);
							  strncpy_s(oldTownName,townName_Size,townName,sizeof(townName));
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
								fprintf(stderr, "curl_easy_perform() failed: %s\n",	curl_easy_strerror(res));
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
				 printf("The town name %s is accepted",townName);
				 Sleep(1000);
					break;
            case 4:
                system("cls");
                printAbout();
				printf("\nPress anything to back..");
                getch();
                break;
            case 5:
                printf("Please enter any key to exit the Weather Application..");
				getch();
                break;

            }
			if(choice==5) break;
			system("cls");
            printf("Welcome to Embedded Weather Station !\n");
            printf("************The Menu ***************\n");
            printf("1) Consult the temperature\n");
            printf("2) Consult the humidity\n");
            printf("3) change the town's name\n");
            printf("4) About the application\n");
            printf("5) exit the application\n");
            printf("\nPlease enter a valid choice: (between 1 and 5):");
			choice=0;
			choice=(int)getchar()-ASCII_Code_0;
            while((choice<1)||(choice>5))
            {
				choice=(int)getchar()-ASCII_Code_0;
				
			}
        }
    
  ///////////////////////////////end big while
	 /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
  free_dynamicVar(chunk.memory);
  /* we're done with libcurl, so clean it up */ 
  curl_global_cleanup();

  return 0;
}



static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
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
