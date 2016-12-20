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
