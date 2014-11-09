#ifndef STRINGSDEF_H
#define STRINGSDEF_H

#define initValue_queryValue "http://api.openweathermap.org/data/2.5/weather?q="
#define	lastPart_queryValue "&mode=xml"
#define ABOUT "About Embedded Weather Station \n\
It's an embedded application that consist of getting the weather's data through a web service.n\
I divided the application to 3 parts essentially: \n\
\
\1-The use of The api of openweathermap.org which with the free version that provide an XML file\n for the town's name,it represent\
\the Web service.\n \
2-The use of free library libcurl provided here: http:\\curl.haxx.se/libcurl, to download the XML file result.\n\
3-Parsing the XML Result:I prefered to implement the parsing of the XML result file with basicly tow functions than using.\
already made librarys LibXML (xmlsoft.org) for learning purposes.\
4-The application : assembling all parts.\n\
The duration of the developping of this prototype is estimated to 24 hours during 12 days.\n\
Developper: Mkhinini Ghayth.\n"

#endif // STRINGSDEF_H