//---------------------------------------------------------------------------

#ifndef UnitGameModeH
#define UnitGameModeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmGameMode : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *rgGameMode;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFrmGameMode(TComponent* Owner);
        int GameMode;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmGameMode *FrmGameMode;
//---------------------------------------------------------------------------
#endif
