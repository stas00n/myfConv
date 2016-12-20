object Form1: TForm1
  Left = 454
  Top = 311
  Width = 368
  Height = 330
  Caption = 'MYF Image Converter v0.1'
  Color = clBtnFace
  Constraints.MinHeight = 330
  Constraints.MinWidth = 368
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 8
    Top = 8
    Width = 256
    Height = 256
    OnPaint = PaintBox1Paint
  end
  object ButtonLoad: TButton
    Left = 272
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Load'
    TabOrder = 0
    OnClick = ButtonLoadClick
  end
  object ButtonSaveAs: TButton
    Left = 272
    Top = 40
    Width = 75
    Height = 25
    Caption = 'Save As'
    TabOrder = 1
  end
  object MainMenu: TMainMenu
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open...'
        OnClick = Open1Click
      end
      object SaveAs1: TMenuItem
        Caption = 'Save &As...'
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object About1: TMenuItem
        Caption = '&About...'
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 320
    Top = 8
  end
end
