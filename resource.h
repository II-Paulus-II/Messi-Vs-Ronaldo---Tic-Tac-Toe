#ifndef RESOURCES
#define RESOURCES
#endif // RESOURCES

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <wingdi.h>

#define IDC_STATIC -1
#define IDR_MYMENU          101
#define IDI_MYICON          102
#define IDD_ABOUT           103
#define IDI_MYICON_BS       104

#define ID_FILE_EXIT        40001
#define ID_STUFF_DCFIVE     40002
#define ID_STUFF_ABOUT      40003
#define ID_FILE_NEWGAME     40005
