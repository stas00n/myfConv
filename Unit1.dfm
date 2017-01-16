object Form1: TForm1
  Left = 399
  Top = 186
  Width = 488
  Height = 440
  Caption = 'MYF Image Converter v0.1'
  Color = clBtnFace
  Constraints.MinHeight = 440
  Constraints.MinWidth = 488
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 120
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 5
    Top = 0
    Width = 469
    Height = 375
    ActivePage = TabSheetSingle
    TabIndex = 0
    TabOrder = 0
    object TabSheetSingle: TTabSheet
      Caption = 'Single'
      object PaintBox1: TPaintBox
        Left = -20
        Top = -14
        Width = 315
        Height = 316
        OnPaint = PaintBox1Paint
      end
      object ButtonLoad: TButton
        Left = 362
        Top = 10
        Width = 92
        Height = 31
        Caption = 'Load'
        TabOrder = 0
        OnClick = ButtonLoadClick
      end
      object ButtonSaveAs: TButton
        Left = 362
        Top = 49
        Width = 92
        Height = 31
        Caption = 'Save As'
        TabOrder = 1
        OnClick = ButtonSaveAsClick
      end
      object ButtonSaveC: TButton
        Left = 361
        Top = 89
        Width = 92
        Height = 32
        Caption = 'Save .c'
        TabOrder = 2
        OnClick = ButtonSaveCClick
      end
      object Button1: TButton
        Left = 360
        Top = 136
        Width = 75
        Height = 25
        Caption = 'Bmp16.c'
        TabOrder = 3
        OnClick = Button1Click
      end
    end
    object TabSheetMulti: TTabSheet
      Caption = 'Batch'
      ImageIndex = 1
      object LabelFilter: TLabel
        Left = 39
        Top = 123
        Width = 29
        Height = 16
        Caption = 'Filter'
      end
      object EditSrcDir: TEdit
        Left = 30
        Top = 20
        Width = 316
        Height = 24
        ReadOnly = True
        TabOrder = 0
        Text = 'Select Source Directory...'
      end
      object EditDestDir: TEdit
        Left = 30
        Top = 59
        Width = 316
        Height = 24
        ReadOnly = True
        TabOrder = 1
        Text = 'Select Save Directory...'
      end
      object ButtonSelSrc: TButton
        Left = 354
        Top = 15
        Width = 31
        Height = 31
        Caption = '...'
        TabOrder = 2
        OnClick = ButtonSelSrcClick
      end
      object ButtonSelDestDir: TButton
        Left = 354
        Top = 54
        Width = 31
        Height = 31
        Caption = '...'
        TabOrder = 3
        OnClick = ButtonSelDestDirClick
      end
      object ButtonStart: TButton
        Left = 295
        Top = 167
        Width = 93
        Height = 31
        Caption = 'Start'
        TabOrder = 4
        OnClick = ButtonStartClick
      end
      object Memo1: TMemo
        Left = 39
        Top = 207
        Width = 376
        Height = 99
        Lines.Strings = (
          'Memo1')
        TabOrder = 5
      end
      object EditFilter: TEdit
        Left = 98
        Top = 118
        Width = 248
        Height = 24
        TabOrder = 6
        Text = '.png;'
      end
      object CheckBoxSubDirs: TCheckBox
        Left = 69
        Top = 167
        Width = 119
        Height = 21
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
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 320
    Top = 40
  end
end
