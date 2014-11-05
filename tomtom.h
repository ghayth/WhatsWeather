
#ifndef TOMTOM_H
#define TOMTOM_H
#define ASCII_Code_0 48
#define townName_Size 20

#define Exit_secure_malloc -11
#define Exit_get_value -21
#define Exit_get_size -31
#define Exit_print_temp -41
#define Exit_print_humidity -51
#define Exit_secure_strcpy -61

#define choice_first 1
#define choice_2 2
#define choice_3 3
#define choice_4 4
#define choice_last 5

#define MAX_Malloc_Tries 1000
#define default_townName "ABC" 
#define default_queryValue "http://api.openweathermap.org/data/2.5/weather?q=ABC&mode=xml"
#define ABOUT "About Embedded Weather Station \n\
It's an embedded application that consist of getting the weather's data through a web service.n\
I divided the application to 3 parts essentially: \n\
\
\1-The use of The api of openweathermap.org which with the free version that provide an XML file\n for the town's name,it represent\
\the Web service.\n \
2-The use of free library libcurl provided here: http:\/\/curl.haxx.se\/libcurl, to download the XML file result.\n\
3-Parsing the XML Result:I prefered to implement the parsing of the XML result file with basicly tow functions than using.\
already made librarys LibXML (xmlsoft.org) for learning purposes.\
4-The application : assembling all parts.\n\
The duration of the developping of this prototype is estimated to 24 hours during 12 days.\n\
Developper: Mkhinini Ghayth.\n"

char* substring(char*, int, int);
void insert_substring(char *a, char *b, int position);
char *get_value(char *target_value,char *parse_value,int value_size);
char *read_town_name();
void print_temp(char *data);
void print_humidity(char *data);
void printAbout();
void free_dynamicVar(void *var);
void* secure_malloc(int size);
void* secure_strcpy(char* firstStr,char* secondStr);
char *replace_str(const char *original_str, const char *old_str, const char *new_str);
struct MemoryStruct {
  char *memory;
  size_t size;
};
#endif // TOMTOM_H
