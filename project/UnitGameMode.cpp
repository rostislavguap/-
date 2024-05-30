//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitGameMode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmGameMode *FrmGameMode;
//---------------------------------------------------------------------------
__fastcall TFrmGameMode::TFrmGameMode(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmGameMode::BitBtn1Click(TObject *Sender)
{
   if (rgGameMode->ItemIndex == 0) GameMode = 1;
   if (rgGameMode->ItemIndex == 1) GameMode = 2;
}
//---------------------------------------------------------------------------
