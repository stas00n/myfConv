//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
// User includes:
#include <windows.h>
#include <Dialogs.hpp>
#include "utils.h"
#include "myf.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPaintBox *PaintBox1;
        TMainMenu *MainMenu;
        TMenuItem *File1;
        TMenuItem *Exit1;
        TMenuItem *N2;
        TMenuItem *SaveAs1;
        TMenuItem *Open1;
        TMenuItem *Help1;
        TMenuItem *About1;
        TButton *ButtonLoad;
        TButton *ButtonSaveAs;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TPageControl *PageControl1;
        TTabSheet *TabSheetSingle;
        TTabSheet *TabSheetMulti;
        TEdit *EditSrcDir;
        TEdit *EditDestDir;
        TButton *ButtonSelSrc;
        TButton *ButtonSelDestDir;
        TButton *ButtonStart;
        TMemo *Memo1;
        TEdit *EditFilter;
        TLabel *LabelFilter;
        TCheckBox *CheckBoxSubDirs;
        TButton *ButtonSaveC;
        TButton *Button1;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall PaintBox1Paint(TObject *Sender);
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall ButtonSaveAsClick(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall ButtonSelSrcClick(TObject *Sender);
        void __fastcall ButtonSelDestDirClick(TObject *Sender);
        void __fastcall ButtonStartClick(TObject *Sender);
        void __fastcall ButtonSaveCClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
        Graphics::TBitmap* bm;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
