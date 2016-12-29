#ifndef _MYF_H_
#define _MYF_H_

#include <vcl.h>
#include <windows.h>


typedef struct
{
  BYTE id[4];
  WORD imgWidth;
  WORD imgHidth;
  WORD clutOffset;
  WORD clutUsed;
  WORD reserved;
  WORD sequenceOffset;
  DWORD sequenceSize;
}MYFHEAD_T;

typedef struct
{
 BYTE R;
 BYTE G;
 BYTE B;
 BYTE reserved;
}RGB32_T;

int SaveBitmapToMYF(char* filename, Graphics::TBitmap* bm);
int LoadBitmapFromMYF(char* filename, Graphics::TBitmap* bm);
void* BitmapToMYF(Graphics::TBitmap* bm, DWORD* size);

WORD RGB32To16(RGB32_T* src, WORD* dest);
DWORD RGB16To32(WORD* src, RGB32_T* dest);
void ConvertBitmap32To16(Graphics::TBitmap* bm, WORD* bm16);
WORD BuildCLUT(WORD* bitmap16, DWORD pixelCount, WORD* CLUT);
int BuildSequence(BYTE* buf,
                  DWORD bufSize,
                  WORD* bitmap16,
                  DWORD pixelCount,
                  WORD* clut,
                  WORD clutSize);
BYTE GetColorIndex(WORD* color, WORD* CLUT, WORD clutSize);

// Beta funcs
void ConvertBitmap32To16Gray(Graphics::TBitmap* bm, WORD* bm16);
WORD CountColors(WORD* bitmap16, DWORD pixelCount);


#endif /* _MYF_H_ */
 