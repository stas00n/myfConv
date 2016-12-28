#include "myf.h"
#include <math.h>


WORD BuildCLUT(WORD* bitmap16, DWORD pixelCount, WORD* CLUT)
{
  WORD indx = 0;
  WORD tmp;
  bool exists;

  for(DWORD i = 0; i < pixelCount; i++)
  {
    tmp = *(bitmap16++);
    exists = false;
    // Check color already exist in table
    for(WORD j = 0; j < indx; j++)
    {
      if(CLUT[j] == tmp) exists = true;
    }
    if(!exists)
    {
      CLUT[indx] = tmp;
      indx++;
    }
    if(indx > 253)
    {
      MessageBox(NULL, "Palette has more than 254 colors", "Warning", MB_OK);
      break;
    }
  }
  return indx;//CLUT used size;
}

int BuildSequence(BYTE* buf,
                  DWORD bufSize,
                  WORD* bitmap16,
                  DWORD pixelCount,
                  WORD* clut,
                  WORD clutSize)
{
  DWORD cnt = 0;
  WORD repeatCnt = 0;
  WORD colindx, colindxprev = 0xFFFF;
  for(DWORD i = 0; i < pixelCount; i++)
  {
    if(cnt > bufSize) return -1;
     colindx = GetColorIndex((bitmap16 + i), clut, (BYTE)clutSize);
     if(colindx != colindxprev)
     {
       if(repeatCnt != 0)
       {
         if(repeatCnt < 256)
         {
           buf[cnt - 1] = 0xFF;
           buf[cnt++] = (BYTE)repeatCnt;
         }
         else
         {
           buf[cnt - 1] = 0xFE;
           buf[cnt++] = (BYTE)(repeatCnt & 0xFF);
           buf[cnt++] = (BYTE)(repeatCnt >> 8);
         }
         repeatCnt = 0;
       }
       buf[cnt++] = colindx;
       colindxprev = colindx;
     }
     else if(repeatCnt == 0)
     {
       buf[cnt++] = 0xFF;
       repeatCnt++;
     }
     else
     {
       repeatCnt++;
     }

     if(repeatCnt == 65535)//Max repetitions reached
     {
       buf[cnt - 1] = 0xFE;
       buf[cnt++] = 0xFF;
       buf[cnt++] = 0xFF;
       repeatCnt = 0;
       colindxprev = 0xFFFF;
     }
  }
  if(repeatCnt != 0)
  {
    buf[cnt++] = (BYTE)(repeatCnt & 0xFF);
    if(repeatCnt > 255)
    {
      buf[cnt - 2] = 0xFE;
      buf[cnt++] = (BYTE)(repeatCnt >> 8);
    }
  }

  return cnt;
}

BYTE GetColorIndex(WORD* color, WORD* CLUT, WORD clutSize)
{
  WORD indx = 0xFD;//index doesn't exists, return max possible index
  for(BYTE i = 0; i < clutSize; i++)
  {
    if(*color == CLUT[i])
    {
      indx = i;
      break;
    }
  }
  return indx;
}

int SaveBitmapToMYF(char* filename, MYFHEAD_T* head, WORD* clut, BYTE* sequence)
{
  return 0;
}

WORD RGB32To16(RGB32_T* src, WORD* dest)
{
  *dest = (src->R >> 3);
  *dest <<= 6;
  *dest |= (src->G >> 2);
  *dest <<= 5;
  *dest |= (src->B >> 3);
  return *dest;
}

void ConvertBitmap32To16(Graphics::TBitmap* bm, WORD* bm16)
{
  TColor color;
  RGB32_T* pColor = (RGB32_T*)&color;
  for(int y = 0; y < bm->Height; y++)
  {
    for(int x = 0; x < bm->Width; x++)
    {
      color = bm->Canvas->Pixels[x][y];
      RGB32To16(pColor, bm16++);
    }
  }
}







 // Beta funcs
void ConvertBitmap32To16Gray(Graphics::TBitmap* bm, WORD* bm16)
{
  TColor color;
  RGB32_T* pColor = (RGB32_T*)&color;
  float fGray;
  BYTE bGray;
  for(int y = 0; y < bm->Height; y++)
  {
    for(int x = 0; x < bm->Width; x++)
    {
      color = bm->Canvas->Pixels[x][y];
      fGray = 0.3 * pColor->R + 0.59 * pColor->G + 0.11 * pColor->B;
      bGray = (BYTE)(fGray + 0.5);
      *bm16 = bGray >> 3;
      *bm16 <<= 6;
      *bm16 |= bGray >> 2;
      *bm16 <<= 5;
      *(bm16++) |= bGray >> 3;
    }
  }
}

WORD CountColors(WORD* bitmap16, DWORD pixelCount)
{
  WORD indx = 0;
  WORD tmp;
  bool exists;
  WORD CLUT[65536];
  for(DWORD i = 0; i < pixelCount; i++)
  {
    tmp = *(bitmap16++);
    exists = false;
    // Check color already exist in table
    for(WORD j = 0; j < indx; j++)
    {
      if(CLUT[j] == tmp) exists = true;
    }
    if(!exists)
    {
      CLUT[indx] = tmp;
      indx++;
    }
  }
  return indx;//CLUT used size;
}
void FindMinColDiff(DWORD pixelCount, WORD* bm16)
{
// Count colors
  WORD indx = 0;
  WORD tmp;
  bool exists;
  WORD CLUT[65536];
  for(DWORD i = 0; i < pixelCount; i++)
  {
    tmp = *(bm16++);
    exists = false;
    // Check color already exist in table
    for(WORD j = 0; j < indx; j++)
    {
      if(CLUT[j] == tmp) exists = true;
    }
    if(!exists)
    {
      CLUT[indx] = tmp;
      indx++;
    }
  }


  WORD ncol = indx;

WORD c1,c2;
typedef struct
{
 BYTE R;
 BYTE G;
 BYTE B;
}nrgb_t;
nrgb_t nrgb1, nrgb2;

float* diff = new float[ncol];
for (WORD i = 0; i < ncol; i++)
{
  
}



nrgb1.B = (c1 & 0x1F) << 1;
c1 >>= 5;
nrgb1.G = (c1 & 0x3F);
c1 >>= 6;
nrgb1.R = (c1 & 0x1F) << 1;

nrgb2.B = (c2 & 0x1F) << 1;
c2 >>= 5;
nrgb2.G = (c2 & 0x3F);
c2 >>= 6;
nrgb2.R = (c2 & 0x1F) << 1;

//diff = pow((nrgb1.R - nrgb2.R), 2);
//diff += pow((nrgb1.G - nrgb2.G), 2);
//diff += pow((nrgb1.B - nrgb2.B), 2);
//diff = pow(diff, 0.5);
}
