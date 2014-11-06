#ifndef ERRORCODES_H
#define ERRORCODES_H



#define ASCII_Code_0 48
#define ASCII_Code_ENTER 13
#define MAX_Malloc_Tries 1000
#define SECOND 1000
#define MAX_ERRORS -999
enum eCodeErrors
{
Exit_secure_malloc = MAX_ERRORS,
Exit_get_value ,
Exit_get_size ,
Exit_print_temp ,
Exit_print_humidity ,
Exit_secure_strcpy 

};
enum eMenuSelection
{
    DEFAULT,
    PRINT_TEMPERATURE,
    PRINT_HUMIDITY,
	TOWN_NAME,
	ABOUT_APPLICATION,
	EXIT
    
};
#endif // ERRORCODES_H
