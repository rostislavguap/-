//---------------------------------------------------------------------------

#ifndef UnFoolH
#define UnFoolH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFmFool : public TForm
{
__published:	// IDE-managed Components
        TImage *UIM2;
        TImage *UIM3;
        TImage *UIM1;
        TImage *UIM4;
        TImage *UIM5;
        TImage *UIM6;
        TImage *CIM5;
        TImage *CIM4;
        TImage *CIM3;
        TImage *CIM2;
        TImage *CIM1;
        TImage *CIM6;
        TImage *ImCon;
        TImage *ImCol;
        TButton *Button1;
        TImage *ImConM1;
        TImage *ImConC1;
        TImage *ImConM2;
        TImage *ImConM3;
        TImage *ImConM4;
        TImage *ImConM5;
        TImage *ImConM6;
        TImage *ImConC2;
        TImage *ImConC3;
        TImage *ImConC4;
        TImage *ImConC5;
        TImage *ImConC6;
        TButton *ButOper;
        TButton *ButtonLeft;
        TButton *ButtonRight;
        TLabel *LQuan;
        TLabel *LPrompt;
        TLabel *LCQuan;
        TLabel *LUQuan;
        void __fastcall FormActivate(TObject *Sender); // метод,  который  вызывается  при  активации  формы.
        void __fastcall Button1Click(TObject *Sender); // метод,  который  вызывается  при  нажатии  кнопки Button1.
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, // метод,  который  вызывается  при  движении  мыши  над  формой.
          int X, int Y);
        void __fastcall UIM1MouseMove(TObject *Sender, TShiftState Shift, // метод,  который  вызывается  при  движении  мыши  над  компонентом  UIM1.
          int X, int Y);
        void __fastcall UIM2MouseMove(TObject *Sender, TShiftState Shift, // метод,  который  вызывается  при  движении  мыши  над  компонентом  UIM2.
          int X, int Y);
        void __fastcall UIM3MouseMove(TObject *Sender, TShiftState Shift, // метод,  который  вызывается  при  движении  мыши  над  компонентом  UIM3.
          int X, int Y);
        void __fastcall UIM4MouseMove(TObject *Sender, TShiftState Shift, // метод,  который  вызывается  при  движении  мыши  над  компонентом  UIM4.
          int X, int Y);
        void __fastcall UIM5MouseMove(TObject *Sender, TShiftState Shift, // метод,  который  вызывается  при  движении  мыши  над  компонентом  UIM5.
          int X, int Y);
        void __fastcall UIM6MouseMove(TObject *Sender, TShiftState Shift, // метод,  который  вызывается  при  движении  мыши  над  компонентом  UIM6.
          int X, int Y);
        void __fastcall UIM1Click(TObject *Sender); // метод,  который  вызывается  при  нажатии  компонента  UIM1.
        void __fastcall UIM2Click(TObject *Sender); // метод,  который  вызывается  при  нажатии  компонента  UIM2.
        void __fastcall UIM3Click(TObject *Sender); // метод,  который  вызывается  при  нажатии  компонента  UIM3.
        void __fastcall UIM4Click(TObject *Sender); // метод,  который  вызывается  при  нажатии  компонента  UIM4.
        void __fastcall UIM5Click(TObject *Sender); // метод,  который  вызывается  при  нажатии  компонента  UIM5.
        void __fastcall UIM6Click(TObject *Sender); // метод,  который  вызывается  при  нажатии  компонента  UIM6.
        void __fastcall ButOperClick(TObject *Sender); // метод,  который  вызывается  при  нажатии  кнопки  ButOper.
        void __fastcall FormCreate(TObject *Sender); // метод,  который  вызывается  при  создании  формы.
        void __fastcall ButtonRightClick(TObject *Sender); // метод,  который  вызывается  при  нажатии  кнопки  ButtonRight.
        void __fastcall ButtonLeftClick(TObject *Sender);
        void __fastcall CIM1Click(TObject *Sender); // метод,  который  вызывается  при  нажатии  кнопки  ButtonLeft.

private:	// User declarations
public:		// User declarations
        __fastcall TFmFool(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmFool *FmFool;
//---------------------------------------------------------------------------
#endif
