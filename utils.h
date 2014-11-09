#ifndef TOMTOM_H
#define TOMTOM_H

char* substring(char*, int, int);
void insert_substring(char *a, char *b, int position);
char *get_value(char *target_value,char *parse_value,int value_size);
char *read_town_name();
void print_temp(char *data);
void print_humidity(char *data);
void printAbout();
void free_dynamicVar(void *var);
void* secure_malloc(size_t size);
void* secure_strcpy(char* firstStr,char* secondStr);


#endif // TOMTOM_H
