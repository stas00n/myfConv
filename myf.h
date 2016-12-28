#ifndef _MYF_H_
#define _MYF_H_

#include <windows.h>
#include <Graphics.hpp>

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

int SaveBitmapToMYF(char* filename, MYFHEAD_T* head, WORD* clut, BYTE* sequence);
WORD RGB32To16(RGB32_T* src, WORD* dest);
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
void FindMinColDiff(DWORD pixelCount, WORD* bm16);

#endif /* _MYF_H_ */
 