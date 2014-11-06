#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "errorsConstants.h"
#include "stringsDef.h"

void printAbout(){
    printf("%s", ABOUT);
}

char *replace_str(const char *original_str, const char *old_str, const char *new_str)
{
	char *result_str, *r;
	const char *p, *q;
	
	ptrdiff_t ptr_difference;
	size_t count=0, result_len;
	size_t old_strlen = strlen(old_str);
	size_t new_strlen = strlen(new_str);

	if (old_strlen != new_strlen) {
		for (p = original_str; (q = strstr(p, old_str)) != NULL; p = q + old_strlen)
		{
			count++;
		}
		/* this is undefined if p - str > PTRDIFF_MAX */
		result_len = strlen(original_str) + count * (new_strlen - old_strlen);
		
	} else
		result_len = strlen(original_str);

	result_str = (char *) secure_malloc(result_len + 1) ;
	
	r = result_str;
	for (p = original_str; (q = strstr(p, old_str)) != NULL; p = q + old_strlen) {
		/* this is undefined if q - p > PTRDIFF_MAX */
		ptr_difference = q - p;
		memcpy(r, p, ptr_difference);
		r += ptr_difference;
		memcpy(r, new_str, new_strlen);
		r += new_strlen;
	}
	
	strcpy(r, p);
	
	return result_str;
}

char *get_value(char *target_value,char *parse_value,int value_size)
{	
	if((target_value == NULL)||(parse_value ==  NULL) ||(value_size <= 0) )
	{
		printf("No DATA to get the value or negative size");
		exit(Exit_get_value);
		return NULL;

	}
	else
	{
   	char *value=(char *)secure_malloc(value_size+1);
	memcpy(value,parse_value,value_size);
	value[value_size]='\0';
	memcpy(target_value,value,value_size);
	target_value[value_size]='\0';
	
	return target_value;
	}
}

int get_size(char *source_temporary_data,char *target_value_name,char *balise,char *parse_pointer)
{   
	if((source_temporary_data == NULL)||(balise ==  NULL) ||(target_value_name == NULL) )
	{
		printf("No DATA to get its size");
		exit(Exit_get_size);
		return -1;
	}
	else
	{
		int value_size;
		int whileCounter=0;
		char *balise_value=strstr(source_temporary_data,balise);
		char *parse_value=strstr(balise_value,target_value_name);
		int length_parse_value=strlen(parse_value);
		while((parse_value[1]!='"')&&(whileCounter < length_parse_value))
		{
			parse_value=(char *)parse_value + sizeof(char);
			whileCounter++;
		}
		parse_value=(char *)parse_value + 2*sizeof(char);//to acces to the first char of the unit temporary_data
		value_size=(strstr(parse_value,"\"")-(char *)parse_value)/sizeof(char);
	
		memcpy(parse_pointer,parse_value,value_size);
		parse_pointer[value_size]='\0';
	
		return value_size;
	}
}


void print_temp(char *data){
	if(data == NULL) 
	{
		printf("No DATA to parse");
		exit(Exit_print_temp);
	}
	else 
	{
			char *temporary_data=(char *)secure_malloc(strlen(data)+1);
			int temp_value_size,min_temp_size,max_temp_size,unit_temp_size;
			char *temp_value;
			char *min_temp_value;
			char *max_temp_value;
			char *unit_temp_value;

			temp_value_size=get_size(data,"value=\"","temperature",temporary_data);
			temp_value = (char *)secure_malloc(temp_value_size+1);
			get_value(temp_value,temporary_data,temp_value_size);
	
			min_temp_size=get_size(data,"min=\"","temperature",temporary_data);
			min_temp_value = (char *)secure_malloc(min_temp_size+1);
			get_value(min_temp_value,temporary_data,min_temp_size);

			max_temp_size=get_size(data,"max=\"","temperature",temporary_data);
			max_temp_value = (char *)secure_malloc(min_temp_size+1);
			get_value(max_temp_value,temporary_data,max_temp_size);

			unit_temp_size=get_size(data,"unit=\"","temperature",temporary_data);
			unit_temp_value = (char *)secure_malloc(min_temp_size+1);
			get_value(unit_temp_value,temporary_data,unit_temp_size);    
    
			printf("la temperature:  %s ,minimale %s ,maximale %s %s",temp_value,min_temp_value,max_temp_value,unit_temp_value);
	
			free_dynamicVar(temp_value);
			free_dynamicVar(min_temp_value);
			free_dynamicVar(max_temp_value);
			free_dynamicVar(unit_temp_value);
	}
}
////////////end temp get value

void print_humidity(char *data){
	if(data == NULL) 
	{
		printf("No DATA to parse");
		exit(Exit_print_humidity);
	}
	else 
	{
		char *temporary_data=(char *)secure_malloc(strlen(data)+1);
		int humidity_value_size,unit_humidity_size;
		char *humidity_value;
		char *unit_humidity_value;

		humidity_value_size=get_size(data,"value=\"","humidity",temporary_data);
		humidity_value = (char *)secure_malloc(humidity_value_size+1);
		get_value(humidity_value,temporary_data,humidity_value_size);
	
		unit_humidity_size=get_size(data,"unit=\"","humidity",temporary_data);
		unit_humidity_value = (char *)secure_malloc(unit_humidity_size+1);
		get_value(unit_humidity_value,temporary_data,unit_humidity_size);
    
		printf("humidity est %s %s",humidity_value,unit_humidity_value);

		free_dynamicVar(humidity_value);
		free_dynamicVar(unit_humidity_value);
	}
}

void free_dynamicVar(void *var){
	if(var)
	{
		free(var);
		var=NULL;
	}
}

void* secure_malloc(size_t size){
	if(size == 0)
	{
		printf("ZERO can't size for Malloc");
		exit(Exit_secure_malloc);
		return NULL;
	}
	else 
	{
		void* ptr =(void *) malloc(size);
		int counter=0;
		while((ptr==NULL) && (counter < MAX_Malloc_Tries ))
		{
			ptr = malloc(size);
			counter++;
		}
 
		return ptr;
	}
}

void* secure_strcpy(char* firstStr,char* secondStr)
{
	if(firstStr && secondStr)
	{
		return strcpy(firstStr,secondStr);
	}
	
	else
	{
		
		return strcpy(firstStr,"");
		
	}


}