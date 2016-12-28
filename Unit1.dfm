object Form1: TForm1
  Left = 399
  Top = 186
  Width = 488
  Height = 439
  Caption = 'MYF Image Converter v0.1'
  Color = clBtnFace
  Constraints.MinHeight = 368
  Constraints.MinWidth = 420
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
  object PageControl1: TPageControl
    Left = 4
    Top = 0
    Width = 381
    Height = 305
    ActivePage = TabSheetSingle
    TabIndex = 0
    TabOrder = 0
    object TabSheetSingle: TTabSheet
      Caption = 'Single'
      object PaintBox1: TPaintBox
        Left = -16
        Top = -11
        Width = 256
        Height = 256
        OnPaint = PaintBox1Paint
      end
      object ButtonLoad: TButton
        Left = 294
        Top = 8
        Width = 75
        Height = 25
        Caption = 'Load'
        TabOrder = 0
        OnClick = ButtonLoadClick
      end
      object ButtonSaveAs: TButton
        Left = 294
        Top = 40
        Width = 75
        Height = 25
        Caption = 'Save As'
        TabOrder = 1
        OnClick = ButtonSaveAsClick
      end
      object ButtonSaveC: TButton
        Left = 293
        Top = 72
        Width = 75
        Height = 26
        Caption = 'Save .c'
        TabOrder = 2
        OnClick = ButtonSaveCClick
      end
    end
    object TabSheetMulti: TTabSheet
      Caption = 'Batch'
      ImageIndex = 1
      object LabelFilter: TLabel
        Left = 32
        Top = 100
        Width = 22
        Height = 13
        Caption = 'Filter'
      end
      object EditSrcDir: TEdit
        Left = 24
        Top = 16
        Width = 257
        Height = 24
        ReadOnly = True
        TabOrder = 0
        Text = 'Select Source Directory...'
      end
      object EditDestDir: TEdit
        Left = 24
        Top = 48
        Width = 257
        Height = 24
        ReadOnly = True
        TabOrder = 1
        Text = 'Select Save Directory...'
      end
      object ButtonSelSrc: TButton
        Left = 288
        Top = 12
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 2
        OnClick = ButtonSelSrcClick
      end
      object ButtonSelDestDir: TButton
        Left = 288
        Top = 44
        Width = 25
        Height = 25
        Caption = '...'
        TabOrder = 3
        OnClick = ButtonSelDestDirClick
      end
      object ButtonStart: TButton
        Left = 240
        Top = 136
        Width = 75
        Height = 25
        Caption = 'Start'
        TabOrder = 4
        OnClick = ButtonStartClick
      end
      object Memo1: TMemo
        Left = 32
        Top = 168
        Width = 305
        Height = 81
        Lines.Strings = (
          'Memo1')
        TabOrder = 5
      end
      object EditFilter: TEdit
        Left = 80
        Top = 96
        Width = 201
        Height = 24
        ReadOnly = True
        TabOrder = 6
        Text = '*.png; *.bmp'
      end
      object CheckBoxSubDirs: TCheckBox
        Left = 56
        Top = 136
        Width = 97
        Height = 17
        Caption = 'Include Sub Dirs'
        TabOrder = 7
      end
    end
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
        OnClick = SaveAs1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
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
  object SaveDialog1: TSaveDialog
    Left = 320
    Top = 40
  end
end
