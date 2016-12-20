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
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  delete bm;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
  ButtonLoad->Left = Form1->Width - 96;
  ButtonSaveAs->Left = Form1->Width - 96;
  PaintBox1->Width = Form1->Width - 112;
  PaintBox1->Height = Form1->Height - 74;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{
  PaintBox1->Canvas->Draw(0,0,bm);
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
      return;

    default:
      return;
  }

  PaintBox1->Canvas->Draw(0,0,bm);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Open1Click(TObject *Sender)
{
  ButtonLoadClick(NULL);
}
//---------------------------------------------------------------------------



