#ifndef _UTILS_H_
#define _UTILS_H_

#include <windows.h>
#include <Graphics.hpp>
#include "png.h"
#include "zlib.h"



typedef enum{FMT_UNKNOWN = 0, FMT_BMP, FMT_PNG, FMT_MYF}SUPPORTEDFORMATS;

void* Load(char* filename);
DWORD GetFileSize(char* filename);
SUPPORTEDFORMATS GetFileFormat(char* filename);
void LoadBitmapFromPNG(char* filename, Graphics::TBitmap* bm);

#endif /* _UTILS_H_ */
 