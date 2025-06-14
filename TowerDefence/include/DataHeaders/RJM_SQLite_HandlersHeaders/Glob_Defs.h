/**
* This file is not written by me. I got the source file from article "Starting with SQLite in C++",
* on site code project. Here is a link to the article: https://www.codeproject.com/Articles/37614/Starting-with-SQLite-in-C-
*
* Files extracted from that project are:
*
    Glob_Defs.h
    RJMFTime.h
    RJMFTime.cpp
    RJM_SQLite_Resultset.h
    RJM_SQLite_Resultset.cpp

*/


//Glob_Defs.h

//Data types
#define DB_DT_LONG long
#define DB_DT_LONG_DEF 0
#define DB_DT_LONG_RET long
#define DB_DT_TIMESTAMP RJMF_TimeStamp
#define DB_DT_TIMESTAMP_DEF glob_RJMFTIMEDefault
#define DB_DT_TIMESTAMP_RET RJMF_TimeStamp*
#define DB_DT_TIMESTAMP_PASS RJMF_TimeStamp*
#define DB_DT_VARCHAR std::string
#define DB_DT_VARCHAR_DEF ""
#define DB_DT_VARCHAR_RET const char *

#define SAFE_DELETE(a) if (a) {delete a; a=NULL;}; 
#ifndef ASSERT
#if defined _DEBUG
#define ASSERT(a) if (!(a)) {exit(0);};
#else
#define ASSERT(a) 
#endif
#endif


//for testing
#define PQ printf("Query:\n%s\nEnd\n",strstrm.str().c_str());

//#define RAND_MAX 2147483647
#define GEN_ID ((rand()%999)*1000000000) + ((rand()%999)*1000000) + ((rand()%999)*1000) + (rand()%999)