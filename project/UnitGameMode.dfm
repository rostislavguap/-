object FrmGameMode: TFrmGameMode
  Left = 412
  Top = 299
  BorderStyle = bsDialog
  Caption = #1056#1077#1078#1080#1084' '#1080#1075#1088#1099
  ClientHeight = 134
  ClientWidth = 244
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object rgGameMode: TRadioGroup
    Left = 16
    Top = 16
    Width = 217
    Height = 65
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1088#1077#1078#1080#1084' '#1080#1075#1088#1099
    ItemIndex = 0
    Items.Strings = (
      #1048#1075#1088#1086#1082' '#1089' '#1082#1086#1084#1087#1100#1102#1090#1077#1088#1086#1084
      #1048#1075#1088#1086#1082' '#1089' '#1080#1075#1088#1086#1082#1086#1084)
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 16
    Top = 96
    Width = 107
    Height = 25
    TabOrder = 1
    OnClick = BitBtn1Click
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 128
    Top = 96
    Width = 105
    Height = 25
    TabOrder = 2
    Kind = bkCancel
  end
end
