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

DWORD Save(char* filename, BYTE* pMemory, DWORD size)
{
  DWORD tmp;
  HANDLE hFile = CreateFile(filename,
                            GENERIC_WRITE,
                            0,             // No share
                            NULL,          // SecurityAttributes
                            CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);         // No Template

  if(hFile != INVALID_HANDLE_VALUE)
  {
    WriteFile(hFile, pMemory, size, &tmp, NULL);
    CloseHandle(hFile);
    return tmp;
  }
  else
    return 0;
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

bool SelectDirDialog(HWND hwndOwner, char* dir, char* title)
{
  static _ITEMIDLIST* pidl;
  _browseinfoA bi;

  bi.hwndOwner = hwndOwner;
  bi.pidlRoot = NULL;
  bi.pszDisplayName = dir;
  bi.lpszTitle = title;
  bi.ulFlags = BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
  bi.lpfn = BrowseCallbackProc;
  bi.lParam = (LONG)pidl;
  bi.iImage = 0;

  pidl =  SHBrowseForFolder(&bi);
  if(pidl == NULL) return false;
  SHGetPathFromIDList(pidl, dir);
  return true;
}

CALLBACK BrowseCallbackProc(
   HWND   hwnd,
   UINT   uMsg,
   LPARAM lParam,
   LPARAM lpData
)
{
  if(uMsg == BFFM_INITIALIZED)
  {
    SendMessage(hwnd,BFFM_SETSELECTION,false,lpData);
   // SendMessage(hwnd,BFFM_SETEXPANDED,falfe,lpData);
  }
  return 0;
}

void FindFilesWithSubDirs(TStringList *sp, AnsiString DirName)
{
TSearchRec sr;
if (DirName.Length())
{
  if (!FindFirst(DirName+"\\*.*",faAnyFile,sr))
 do
  {
  if (!(sr.Name=="." || sr.Name==".."))
   if (((sr.Attr & faDirectory) == faDirectory ) ||
   (sr.Attr == faDirectory))
   {
     FindFilesWithSubDirs(sp, DirName+"\\"+sr.Name);
   }
    else
    {
    sp->Add(DirName+"\\"+sr.Name);
    }
  }
 while (!FindNext(sr));
 FindClose(sr);
 }
}

void FindFiles(TStringList *sp, AnsiString DirName)
{
  TSearchRec sr;
  if (DirName.Length() == 0) return;

  int res = FindFirst(DirName+"\\*.*",faAnyFile,sr);
  if (res != 0) return;                            //found nothing
  do
  {
    if(!(sr.Attr & faDirectory) &&
       !(sr.Attr & FILE_ATTRIBUTE_REPARSE_POINT))  //found file
    {
      sp->Add(DirName+"\\"+sr.Name);
    }
  }
  while (!FindNext(sr));

  FindClose(sr);
}

//------------------------------------------------------------------------------
AnsiString ExtractFileNameOnly(const AnsiString filepath)
{
  AnsiString name, ext;
  name = ExtractFileName(filepath);
  ext = ExtractFileExt(filepath);
  name = name.Delete(name.Length() - ext.Length() + 1, ext.Length());
  return name;
}

BOOL CreateFullDirectory(LPCTSTR dirName, LPSECURITY_ATTRIBUTES lpSA)
{
    char tmpName[MAX_PATH];
    strcpy(tmpName, dirName);

    // Create parent directories
    for (LPTSTR p = strchr(tmpName, '\\'); p; p = strchr(p + 1, '\\'))
    {
        *p = 0;
        ::CreateDirectory(tmpName, lpSA);  // may or may not already exist
        *p = '\\';
    }

    return ::CreateDirectory(dirName, lpSA);
}






