#ifndef _UTILS_H_
#define _UTILS_H_

#include <vcl.h>
#include <windows.h>
#include <Graphics.hpp>
#include "png.h"




typedef enum{FMT_UNKNOWN = 0, FMT_BMP, FMT_PNG, FMT_MYF}SUPPORTEDFORMATS;



void* Load(char* filename);
DWORD Save(char* filename, BYTE* pMemory, DWORD size);
DWORD GetFileSize(char* filename);
bool SelectDirDialog(HWND hwndOwner, char* dir, char* title);
SUPPORTEDFORMATS GetFileFormat(char* filename);
void LoadBitmapFromPNG(char* filename, Graphics::TBitmap* bm);
void FindFilesWithSubDirs(TStringList *sp, AnsiString DirName);
void FindFiles(TStringList *sp, AnsiString DirName);
AnsiString ExtractFileNameOnly(const AnsiString filepath);
BOOL CreateFullDirectory(LPCTSTR dirName, LPSECURITY_ATTRIBUTES lpSA);

CALLBACK BrowseCallbackProc(
   HWND   hwnd,
   UINT   uMsg,
   LPARAM lParam,
   LPARAM lpData
);

#endif /* _UTILS_H_ */
 