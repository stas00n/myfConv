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
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
