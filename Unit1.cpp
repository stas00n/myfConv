//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

  bm = new Graphics::TBitmap;
  bm->Width = PaintBox1->Width;
  bm->Height = PaintBox1->Height;
  bm->PixelFormat = pf24bit;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  delete bm;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
  PageControl1->Width = Form1->ClientWidth - 10;
  PageControl1->Height = Form1->ClientHeight - 10;
  ButtonLoad->Left = PageControl1->ClientWidth - 110;
  ButtonSaveAs->Left = PageControl1->ClientWidth - 110;
  ButtonSaveC->Left = PageControl1->ClientWidth - 110;
  PaintBox1->Width = Form1->ClientWidth - 112;
  PaintBox1->Height = Form1->ClientHeight - 24;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{

  int x = (PaintBox1->Width - bm->Width) / 2;
  int y = (PaintBox1->Height - bm->Height) / 2;
  PaintBox1->Canvas->Draw(x,y,bm);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonLoadClick(TObject *Sender)
{
  if(!OpenDialog1->Execute()) return;
  SUPPORTEDFORMATS fmt = GetFileFormat(OpenDialog1->FileName.c_str());
  switch(fmt)
  {
    case FMT_BMP:
      bm->LoadFromFile(OpenDialog1->FileName);
      break;

    case FMT_PNG:
      LoadBitmapFromPNG(OpenDialog1->FileName.c_str(), bm);
      break;

    case FMT_MYF:
      LoadBitmapFromMYF(OpenDialog1->FileName.c_str(), bm);
      break;

    default:
      return;
  }
  PaintBox1->Hide();
  PaintBox1->Canvas->Draw(0,0,bm);
  PaintBox1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Open1Click(TObject *Sender)
{
  ButtonLoadClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonSaveAsClick(TObject *Sender)
{
  if(!SaveDialog1->Execute())
    return;

  DWORD fileSize;

  void* pFile = BitmapToMYF(bm, &fileSize);
  Save(SaveDialog1->FileName.c_str(), (BYTE*)pFile, fileSize);
  free(pFile);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSaveCClick(TObject *Sender)
{
  if(!SaveDialog1->Execute())
    return;
  // Convert in memory
  DWORD fileSize;
  void* myf = (BYTE*)BitmapToMYF(bm, &fileSize);

  AnsiString s,fn;
  TStringList* cfile = new TStringList;

  fn = ExtractFileNameOnly(SaveDialog1->FileName);
  cfile->Add("extern const unsigned char " + fn +"[] = {");

  BYTE* p = (BYTE*)myf;
  for(DWORD i = 0; i < fileSize; i)
  {
    s = "  ";
    for(DWORD j = 0; j < 16; j++)
    {
      s += ("0x" + IntToHex(*(p++), 2) + ", ");
      if(++i >= fileSize) break;
    }
    cfile->Add(s);
  }

  int end = cfile->Strings[cfile->Count - 1].Length();
  cfile->Strings[cfile->Count - 1] = cfile->Strings[cfile->Count - 1].Delete(end-1,2);
  cfile->Add("};");
  cfile->SaveToFile(SaveDialog1->FileName);
  
  delete cfile;
  free(myf);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
  Form1->Close();        
}

//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonSelSrcClick(TObject *Sender)
{
  char dir[MAX_PATH];
  int res = SelectDirDialog(Form1->WindowHandle, dir, "Select source image directory");
  if(res) EditSrcDir->Text = dir;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonSelDestDirClick(TObject *Sender)
{
  char dir[MAX_PATH];
  int res = SelectDirDialog(Form1->WindowHandle, dir, "Select save image directory");
  if(res) EditDestDir->Text = dir;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonStartClick(TObject *Sender)
{
 Memo1->Clear();

  AnsiString path = EditSrcDir->Text+"*";
  HANDLE h;
  bool result;
  WIN32_FIND_DATA fd;
  h = FindFirstFile(path.c_str(), &fd);
  if(h != INVALID_HANDLE_VALUE)
     Memo1->Lines->Add(fd.cFileName);
  result = true;
  while(result)
  {
  result = FindNextFile(h, &fd);
  if(result)
    Memo1->Lines->Add(fd.cFileName);
  }
  FindClose(h);

  TStringList* sl = new TStringList;
  if(CheckBoxSubDirs->Checked)
    FindFilesWithSubDirs(sl,EditSrcDir->Text);
  else
    FindFiles(sl,EditSrcDir->Text);

  //Filter by extension
  TStringList* extFilter = new TStringList;
  int start = 0, end=0,len;
  char c;
  int i = 0;
  while(i < EditFilter->Text.Length())
  {
    for(i = start; i < EditFilter->Text.Length(); i++)
    {
      c = EditFilter->Text.c_str()[i];
      if(c == ' ' || c == ';')
      {
        end = i;
        break;
      }
    }

  extFilter->Add(EditFilter->Text.SubString(start,end-start));
  start = end+2;
  }

  int indx = 0;
  AnsiString ext;

  bool extMatch;
  AnsiString extf;
  while(indx < sl->Count)
  {
    extMatch = false;
    ext = ExtractFileExt(sl->Strings[indx]);
    for (i = 0; i < extFilter->Count; i++)
    {
      extf = extFilter->Strings[i];
      if(extf == ext)
      {
        extMatch = true;
        break;
      }
    }
    if (!extMatch)
    {
      sl->Delete(indx);
      continue;
    }
    indx++;
  }
  Memo1->Text = sl->Text;
  Memo1->Lines->Add("Total "+IntToStr(sl->Count)+ " .bmp Files Found");
  delete sl;
}
//---------------------------------------------------------------------------



