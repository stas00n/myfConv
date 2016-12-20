#include "utils.h"

DWORD GetFileSize(char* filename)
{
  DWORD size = 0, tmp;
  HANDLE hFile = CreateFile(filename,
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);

  if(hFile != INVALID_HANDLE_VALUE)
  {
    size = GetFileSize(hFile, &tmp);
    CloseHandle(hFile);
  }
  return size;
}

void* Load(char* filename)
{
  DWORD tmp;
  void* membuf;
  HANDLE hFile = CreateFile(filename,
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);

  if(hFile != INVALID_HANDLE_VALUE)
  {
    DWORD fsize = GetFileSize(hFile, &tmp);
    membuf = malloc(fsize);
    ReadFile(hFile, membuf, fsize, &tmp, NULL);
    CloseHandle(hFile);
    return membuf;
  }
  else
  {
    DWORD e = GetLastError();
    return NULL;
  }
}

SUPPORTEDFORMATS GetFileFormat(char* filename)
{
  DWORD tmp;
  char szFileId[5] = {0};
  HANDLE hFile = CreateFile(filename,
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);

  if(hFile != INVALID_HANDLE_VALUE)
  {
    ReadFile(hFile, szFileId, 4, &tmp, NULL);
    CloseHandle(hFile);
  }
  else
  {
    DWORD e = GetLastError();
    return FMT_UNKNOWN;
  }

  if(memcmp(szFileId, "BM", 2) == 0) return FMT_BMP;
  if(memcmp(szFileId, "‰PNG", 4) == 0) return FMT_PNG;
  if(memcmp(szFileId, "MYF", 3) == 0) return FMT_MYF;
  return FMT_UNKNOWN;
}

void LoadBitmapFromPNG(char* filename, Graphics::TBitmap* bm)
{
  png_image image;
  memset(&image, 0, (sizeof image));
  image.version = PNG_IMAGE_VERSION;
  image.format = PNG_FORMAT_RGB;
  image.opaque = NULL;

  png_bytep buffer;

  if(png_image_begin_read_from_file(&image, filename) == 0) return;

  size_t reqBufSize = (PNG_IMAGE_SIZE(image));
  buffer = (BYTE*) malloc(reqBufSize);
  if (buffer == NULL) return;

  int res = png_image_finish_read(&image,
                                  NULL/*background*/,
                                  buffer,
                                  0/*row_stride*/,
                                  NULL/*colormap*/);
  if(res == 0)
  {
    free(buffer);
    return;
  }

  bm->Width = image.width;
  bm->Height = image.height;

  TColor color;
  TColor* pColor = (TColor*)buffer;
  for(DWORD y = 0; y < image.height; y++)
  {
    for(DWORD x = 0; x < image.width; x++)
    {
      color = *(pColor++) & 0x00FFFFFF;
      bm->Canvas->Pixels[x][y] = color;
    }
  }
  free(buffer);
}


