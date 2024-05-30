//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnFool.h"
#include "UnitGameMode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

struct CSet    //�����
 {
  AnsiString  pict; //1-�����,2-�����,3-����,4-�����
  //int value; //2-2,3-3,
  int num;
  boolean  taken;
 }; //cards;


TFmFool *FmFool;
AnsiString fpath,InitDir;
CSet cards[37],PCards[3][37],temp,Coz;  //��� �����;
CSet PCardsCon[3][7]; //����� �� ���� ������ � ������/����������
int Pquan[3],quan; //���������� ���� � ������ � ������/�����
//� ������ � ���������� � � ����
int Mcard; //����� ������
int conQuan; //���� �� ����
boolean flag; //���� �� ���������� �����
boolean PlayerTake; //����� �� ���� ��� �����
boolean UWin; //��� ������� � ������� ����

int GameMode; //1-� ������, 2-���� � ������
int Player1 = 1; // ����� 1
int Player2 = 2; // ���� ��� ����� 2
int PlayerHod;   // ����� �� ������� �������
int PlayerActive;// ����� ������� � ������ ������ ������ ���
String PlayerName[3];//����� �������

//---------------------------------------------------------------------------

/**
1. int GetNoPlayerHod()
������� ����������, ��� ������ ������ ��� ���������.
     ��������� ������� �������� ���������� PlayerHod.
     ���� `PlayerHod` ����� Player1,
     �� ������� ���������� Player2 (��� ��������� � ������� ������).
     ���� `PlayerHod` ����� Player2,
     �� ������� ���������� Player1 (��� ��������� � ������� ������).
**/

int GetNoPlayerHod()
{
   if (PlayerHod == Player1) return Player2;
   if (PlayerHod == Player2) return Player1;
   return 0;
}

/**
2. int GetNoPlayerActive()
������� ����������, ��� �� ������� �������� �������� (��������).
     ��������� ������� �������� ���������� PlayerActive.
     ���� PlayerActive ����� Player1,
     �� ������� ���������� Player2 (�������� ���������� ������ �����).
     ���� PlayerActive ����� Player2,
     �� ������� ���������� Player1 (�������� ���������� ������ �����).

**/

int GetNoPlayerActive()
{
   if (PlayerActive == Player1) return Player2;
   if (PlayerActive == Player2) return Player1;
   return 0;
}

/**
1. �������� ��� �����:
     � ������ ������� �������� ��� 6 ��������� �����������, �������, ��������,
     ������������ ����� 6 ������ ��� ���� �� ������� ����. ��� ������ ���,
     ������������ �������� Visible ��� ������� ���������� � false.
2. �������� �� ������ ������:
     ���� for  ���������� ��� 6 ��������� ������ ��� ���� (�� 1 �� 6).
      ������ �����, ��� ������� �����, ������� ���������,
      ���� �� � ������ ����� � ���� �����.  ��� ������ ���,
      ��������, �� ����� ��  PCardsCon[playerNum][i].num ����.
3. ������������ ������� �����:
      ���� ����� � ����� ���� (�� num �� ����� ����), �������:
          ���������� ��������������� ��������� ����������� (��������, FmFool->ImConC1  ��� ����� 1). 
          ��������� ����������� ����� � ��������� � ������� ������ LoadFromFile,
          ��������� PCardsCon[playerNum][i].pict ��� ��������� ���� � ����� ����������� �����.
4. �������� ������ �����:
      ���� � ����� ��� ����� (�� num ����� ����),
      ������� �������� ��������������� ��������� �����������.
**/

void drawupcards(int playerNum)
{
  //���������� ���� �� ������� �����
  FmFool->ImConC1->Visible = false;
  FmFool->ImConC2->Visible = false;
  FmFool->ImConC3->Visible = false;
  FmFool->ImConC4->Visible = false;
  FmFool->ImConC5->Visible = false;
  FmFool->ImConC6->Visible = false;

  for (int i=1;i<=6;i++) //���������� ���� �� ���� �� ������� �����
    {
      switch(i)
      {
      case 1 :
      if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConC1->Visible = true;
        FmFool->ImConC1->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConC1->Visible = false;

      break;
      case 2 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConC2->Visible = true;
        FmFool->ImConC2->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConC2->Visible = false;

      break;
      case 3 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConC3->Visible = true;
        FmFool->ImConC3->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConC3->Visible = false;

      break;
      case 4 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConC4->Visible = true;
        FmFool->ImConC4->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConC4->Visible = false;

      break;
      case 5 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConC5->Visible = true;
        FmFool->ImConC5->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConC5->Visible = false;

      break;
      case 6 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConC6->Visible = true;
        FmFool->ImConC6->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConC6->Visible = false;

      break;
      }
    }

    //���������� ���� ����������
  FmFool->CIM1->Visible = false;
  FmFool->CIM2->Visible = false;
  FmFool->CIM3->Visible = false;
  FmFool->CIM4->Visible = false;
  FmFool->CIM5->Visible = false;
  FmFool->CIM6->Visible = false;

  for (int i=1;i<=Pquan[playerNum];i++) //����������� ���� �����
  {
     if (i <= 6)//� ����� �� ������� 6 ����
       {
         switch(i)
      {
      case 1 : if (PCards[playerNum][1].num == 0) FmFool->CIM1->Visible = false;
      else
      {

        FmFool->CIM1->Visible = true;
        FmFool->CIM1->Picture->LoadFromFile(cards[0].pict);
      }
      break;
      case 2 : if (PCards[playerNum][2].num ==0) FmFool->CIM2->Visible = false;
      else
      {
        FmFool->CIM2->Picture->LoadFromFile(cards[0].pict);
        FmFool->CIM2->Visible = true;
      }
      break;
      case 3 : if (PCards[playerNum][3].num ==0) FmFool->CIM3->Visible = false;
      else
      {
        FmFool->CIM3->Picture->LoadFromFile(cards[0].pict);
        FmFool->CIM3->Visible = true;
      }
      break;
      case 4 : if (PCards[playerNum][4].num == 0) FmFool->CIM4->Visible = false;
      else
      {
        FmFool->CIM4->Visible = true;
        FmFool->CIM4->Picture->LoadFromFile(cards[0].pict);

      }
      break;
      case 5 : if (PCards[playerNum][5].num ==0) FmFool->CIM5->Visible = false;
      else
      {
        FmFool->CIM5->Picture->LoadFromFile(cards[0].pict);
        FmFool->CIM5->Visible = true;
      }
      break;
      case 6 : if (PCards[playerNum][6].num ==0) FmFool->CIM6->Visible = false;
      else
      {
        FmFool->CIM6->Picture->LoadFromFile(cards[0].pict);
        FmFool->CIM6->Visible = true;
      }
      break;
      }
       }  //end i<=6
  }
   FmFool->LCQuan->Caption = "���� �����: "+IntToStr(Pquan[playerNum]);
}

void drawdowncards(int playerNum)
{
     //���������� ���� � ����� �������
  FmFool->ImConM1->Visible = false;
  FmFool->ImConM2->Visible = false;
  FmFool->ImConM3->Visible = false;
  FmFool->ImConM4->Visible = false;
  FmFool->ImConM5->Visible = false;
  FmFool->ImConM6->Visible = false;

  for (int i=1;i<=6;i++) //���������� ���� �� ���� � ����� �������
    {
      switch(i)
      {
      case 1 :
      if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConM1->Visible = true;
        FmFool->ImConM1->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConM1->Visible = false;

      break;
      case 2 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConM2->Visible = true;
        FmFool->ImConM2->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConM2->Visible = false;

      break;
      case 3 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConM3->Visible = true;
        FmFool->ImConM3->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConM3->Visible = false;

      break;
      case 4 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConM4->Visible = true;
        FmFool->ImConM4->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConM4->Visible = false;

      break;
      case 5 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConM5->Visible = true;
        FmFool->ImConM5->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConM5->Visible = false;

      break;
      case 6 :
       if (PCardsCon[playerNum][i].num != 0)
       {
        FmFool->ImConM6->Visible = true;
        FmFool->ImConM6->Picture->LoadFromFile(PCardsCon[playerNum][i].pict);
       }
       else FmFool->ImConM6->Visible = false;

      break;
      }
    }

    //���������� ����� ����
  FmFool->UIM1->Visible = false;
  FmFool->UIM2->Visible = false;
  FmFool->UIM3->Visible = false;
  FmFool->UIM4->Visible = false;
  FmFool->UIM5->Visible = false;
  FmFool->UIM6->Visible = false;
  //ShowMessage(Pquan[1]);

  for (int i=1;i<=Pquan[playerNum];i++) //����������� ����� ����
  {
     //ShowMessage("Moving "+IntToStr(i)+ "   "+PCards[2][i].pict);
     if (i <= 6)//� ��� �� ������� 6 ����
       {
         switch(i)
      {
      case 1 : if (PCards[playerNum][i].num == 0) FmFool->UIM1->Visible = false;
      else
      {

        FmFool->UIM1->Visible = true;
        FmFool->UIM1->Picture->LoadFromFile(PCards[playerNum][i].pict);
      }
      break;
      case 2 : if (PCards[playerNum][i].num ==0) FmFool->UIM2->Visible = false;
      else
      {
        FmFool->UIM2->Picture->LoadFromFile(PCards[playerNum][i].pict);
        FmFool->UIM2->Visible = true;
      }
      break;
      case 3 : if (PCards[playerNum][i].num ==0) FmFool->UIM3->Visible = false;
      else
      {
        FmFool->UIM3->Picture->LoadFromFile(PCards[playerNum][i].pict);
        FmFool->UIM3->Visible = true;
      }
      break;
      case 4 : if (PCards[playerNum][i].num == 0) FmFool->UIM4->Visible = false;
      else
      {
        FmFool->UIM4->Visible = true;
        FmFool->UIM4->Picture->LoadFromFile(PCards[playerNum][i].pict);

      }
      break;
      case 5 : if (PCards[playerNum][i].num ==0) FmFool->UIM5->Visible = false;
      else
      {
        FmFool->UIM5->Picture->LoadFromFile(PCards[playerNum][i].pict);
        FmFool->UIM5->Visible = true;
      }
      break;
      case 6 : if (PCards[playerNum][i].num ==0) FmFool->UIM6->Visible = false;
      else
      {
        FmFool->UIM6->Picture->LoadFromFile(PCards[playerNum][i].pict);
        FmFool->UIM6->Visible = true;
      }
      break;
      }
       }  //end i<=6
  }
   FmFool->LUQuan->Caption = "���� �����: "+IntToStr(Pquan[playerNum]);
}

void drawCards()
{
  //����� ���� ������������ � �����������
  if (GameMode == 1)
  {
     drawupcards(Player2);
     drawdowncards(Player1);
  }
  //����� ���� ������������ � �������������
  if (GameMode == 2)
  {
     drawupcards(GetNoPlayerActive());
     drawdowncards(PlayerActive);

     if (PlayerHod == PlayerActive)
     {
        FmFool->LPrompt->Caption = PlayerName[PlayerActive] + " ��� ���";
        if (PlayerTake)
           FmFool->ButOper->Caption = "������";
        else
           FmFool->ButOper->Caption = "����";
     }
     else
     {
        FmFool->LPrompt->Caption = PlayerName[PlayerActive] + " �����������";
        FmFool->ButOper->Caption = "�����";
     }

     //if (Pquan[PlayerActive] > 6)
     //{
     //   FmFool->ButtonRight->Enabled = true;
     //}
     //else
     //{
     //   FmFool->ButtonRight->Enabled = false;
     //   FmFool->ButtonLeft->Enabled = false;
     //}
  }
}
/**
������� ��������� ����������� ����� �� `cards[0].pict` �
6 ��������� ��������� ����������� �� ����� `FmFool`:
`UIM1`, `UIM2`, `UIM3`, `UIM4`, `UIM5`, `UIM6`.
**/
void drawendhod()
{
   FmFool->UIM1->Picture->LoadFromFile(cards[0].pict);
   FmFool->UIM2->Picture->LoadFromFile(cards[0].pict);
   FmFool->UIM3->Picture->LoadFromFile(cards[0].pict);
   FmFool->UIM4->Picture->LoadFromFile(cards[0].pict);
   FmFool->UIM5->Picture->LoadFromFile(cards[0].pict);
   FmFool->UIM6->Picture->LoadFromFile(cards[0].pict);

   ShowMessage("��� " + PlayerName[PlayerActive]);

   drawCards();
}
/**
1.  �������������:
    boolean fl = false; -  ���������� fl,  ��������,  ��������� �� ��,
      ��� �� ��� ����� � �������. ��� ���������������� � `false`.
      int n, i, m; -  ����������� ����� ���������� ��� ������������� � �������.
2.  �������� ���������� ����:
    if (quan==0) goto finish; -  ����  quan ����� 0,
      �� ���������� ������� � ����� finish (��������� � finish ����).
    if (quan == 36) //������ ������� ���� -  ����  quan ����� 36,  �� ���  ������ ������� ����.
       do n = random(36)+1; while (cards[n].taken == true); -
         �  �����  do while  ���������� ��������� �����  n  �� 1 �� 36,
         � ���� ����� �  ��������  n  � �������  cards  ���  "�����"  (cards[n].taken == true),
         ��  ����  ������������  � ���������� ����� �����.
       Coz.pict = cards[n].pict; -  �  ����������  Coz.pict  ����������� �����������  ������  ��  �������  cards.
       Coz.num = n; -  �  ����������  Coz.num  ����������� ����� ������ �� ������� cards.
       Mcard = n % 4; -  �����������  �����  ������  ���  �������  ��  �������  n  �� 4.
       cards[n].taken = true; -  �����  �  ��������  n  ����������  ���  "������".

3.  �������� ����:
    if (PlayerHod == Player2) -  ����  ���  ������ 2,  ��  �������  �  �����  l1.
    else -  ����  ���  ������ 1,  ��  �������  �  �����  l2.
4.  ������� ����:
    l1: -  ����� ���  ������,  �����  ���  ������ 2.
    if (Pquan[1] < 6) -  ����  �  ������ 1  ����� 6 ����,  ��:
       if (quan + Pquan[1] >= 6) Pquan[1] = 6;
       else Pquan[1] = Pquan[1] + quan; -  ���������������  ����������  ����  �  ������ 1  �  6,
         ����  ����������  ����  �  `quan`,  �����  �����������  ���  ����������  �����.
    l2: -  ����� ���  ������,  �����  ���  ������ 1.
    if (Pquan[2] < 6) Pquan[2] = 6; -  ����  �  ������ 2  ����� 6 ����,
      ��  ���������������  ����������  ���  ����  �  6.
    if (fl == true) goto finish; -  ����  fl  �����  true,
      ��  �������  �  �����  finish.
    for (i = 1; i <= Pquan[1]; i++) -  ����  ��  ������  ������ 1.
       if (PCards[1][i].num == 0) -  ����  �  ������ 1  �  i-��  �����  ���  �����  (num  �����  0),  ��:
          do { n = random(36) + 1; if (quan <= 2) break; } while (cards[n].taken == true); -
            �  �����  do while ���������� ��������� �����  n  �� 1 �� 36,
            � ���� ����� �  ��������  n  � �������  cards  ���  "�����",
            ��  ����  ������������  � ���������� ����� �����.
          if (quan == 1) { PCards[1][i].pict = Coz.pict; PCards[1][i].num = Coz.num; quan = 0; } -
            ����  quan  ����� 1,  ��  �  i-��  ����  ������ 1  ����������� ������.
          if (quan > 1) { cards[n].taken = true; PCards[1][i].pict = cards[n].pict; PCards[1][i].num = n; quan -= 1; } -
            ����  quan  ������ 1,  ��  �  i-��  ����  ������ 1  ����������� ��������� ����� ��  `cards`,
            �  `quan`  ����������� �� 1

**/
void givecards()
{
   boolean fl;
   int n,i,m;
   fl = false; //������� �� ����
   //ShowMessage("�����");
   if (quan==0) goto finish;
   if (quan == 36) //������ ������� ����
   {
     do
       n = random(36)+1;

     while (cards[n].taken == true);

     Coz.pict  = cards[n].pict; //������
     Coz.num = n;
     Mcard = n % 4; //���������� ����� ��� ������� �� ������� �� 4
     cards[n].taken = true;

     //ShowMessage("������ "+IntToStr(Mcard));
   };

   //if (Pquan[2] < 6) Pquan[2] = 6;

   if (PlayerHod == Player2)
   {
      //ShowMessage("� �������");
      goto l1;

    }
    else
    {
      //ShowMessage("�� �������");
      goto l2;//�� ������ ��� ������ ��� �����
     };
   l1:
   if (Pquan[1] < 6)
     if (quan +Pquan[1] >= 6) Pquan[1] = 6; else Pquan[1] = Pquan[1]+ quan;
   //ShowMessage("������� �");
   if (fl==true) goto finish;
   for(i=1;i<=Pquan[1];i++)
   {
     /* if (quan >= 50)
     {ShowMessage("����� �����������");
      return;
     }  */
     if (PCards[1][i].num == 0)
     {
      //ShowMessage("��������");
       do
       {
         n = random(36)+1;
         if (quan <= 2) break;
       }
       //if (cards[n].taken == false) cards[n].taken = true;
       while (cards[n].taken == true);
       if (quan == 1)
       {
        PCards[1][i].pict  = Coz.pict;
        PCards[1][i].num = Coz.num;
        quan = 0;
       }

       if (quan > 1)
       {
       cards[n].taken = true;
       PCards[1][i].pict  = cards[n].pict;
       PCards[1][i].num = n;
       quan -= 1;
       }

      }
   };

   fl = true;

   l2:
   if (Pquan[2] < 6)
   if (quan +Pquan[2] >= 6) Pquan[2] = 6; else Pquan[2] = Pquan[2]+ quan;
   //ShowMessage("�������� ����");
   for(i=1;i<=Pquan[2];i++)
   {
     if (PCards[2][i].num == 0)
     {
     do
       {
       n = random(36)+1;
       if (quan <= 2) break;
       }
     while (cards[n].taken == true);//   (quan >=1));

      if (quan == 1)
       {
        PCards[2][i].pict  = Coz.pict;
        PCards[2][i].num = Coz.num;
        //quan -= 1;
        quan = 0;
       };

     if (quan > 1)
     {
     cards[n].taken = true;
     PCards[2][i].pict  = cards[n].pict;
     //ShowMessage("Moo "+IntToStr(n));
     //ShowMessage("Moving "+IntToStr(i)+ "   "+PCards[2][i].pict);
     PCards[2][i].num = n;
     quan -= 1;
     }

     }
   };
   goto l1;
   finish:
   FmFool->ImCon->Picture->LoadFromFile(Coz.pict); //������
   FmFool->ImCol->Picture->LoadFromFile(cards[0].pict); //������
   // ShowMessage(cards[1].pict);

    //ShowMessage("Moving "+IntToStr(i)+ "   "+PCards[2][i].pict);
    if (quan == 1) FmFool->ImCol->Visible = false;
    if (quan == 0)
      {
        FmFool->ImCon->Visible = false;
        FmFool->ImCol->Visible = false;
      }
    if (quan > 2)
      {
         FmFool->ImCon->Visible = true;
         FmFool->ImCol->Visible = true;
      }
  FmFool->LQuan->Caption = "���� � ������: "+IntToStr(quan);
  drawCards();
 };

void initcards()
{
 //�������
 cards[0].pict = InitDir+"\\images\\back.jpg"; //��������� ������� �����
 //��������
 cards[1].pict = InitDir+"\\images\\6ch.jpg"; //��������� ������� �����
 cards[2].pict = InitDir+"\\images\\6bub.jpg"; //��������� ������� �����
 cards[3].pict = InitDir+"\\images\\6vin.jpg"; //��������� ������� �����
 cards[4].pict = InitDir+"\\images\\6kr.jpg"; //��������� ������� �����
 //�������
 cards[5].pict = InitDir+"\\images\\7ch.jpg"; //��������� ������� �����
 cards[6].pict = InitDir+"\\images\\7bub.jpg"; //��������� ������� �����
 cards[7].pict = InitDir+"\\images\\7vin.jpg"; //��������� ������� �����
 cards[8].pict = InitDir+"\\images\\7kr.jpg"; //��������� ������� �����
 //���������
 cards[9].pict = InitDir+"\\images\\8ch.jpg"; //��������� ������� �����
 cards[10].pict = InitDir+"\\images\\8bub.jpg"; //��������� ������� �����
 cards[11].pict = InitDir+"\\images\\8vin.jpg"; //��������� ������� �����
 cards[12].pict = InitDir+"\\images\\8kr.jpg"; //��������� ������� �����
 //�������
 cards[13].pict = InitDir+"\\images\\9ch.jpg"; //��������� ������� �����
 cards[14].pict = InitDir+"\\images\\9bub.jpg"; //��������� ������� �����
 cards[15].pict = InitDir+"\\images\\9vin.jpg"; //��������� ������� �����
 cards[16].pict = InitDir+"\\images\\9kr.jpg"; //��������� ������� �����
 //�������
 cards[17].pict = InitDir+"\\images\\10ch.jpg"; //��������� ������� �����
 cards[18].pict = InitDir+"\\images\\10bub.jpg"; //��������� ������� �����
 cards[19].pict = InitDir+"\\images\\10vin.jpg"; //��������� ������� �����
 cards[20].pict = InitDir+"\\images\\10kr.jpg"; //��������� ������� �����
 //������
  cards[21].pict = InitDir+"\\images\\Jch.jpg"; //��������� ������� �����
  cards[22].pict = InitDir+"\\images\\Jbub.jpg"; //��������� ������� �����
  cards[23].pict = InitDir+"\\images\\Jvin.jpg"; //��������� ������� �����
  cards[24].pict = InitDir+"\\images\\Jkr.jpg"; //��������� ������� �����
 //����
  cards[25].pict = InitDir+"\\images\\Qch.jpg"; //��������� ������� �����
  cards[26].pict = InitDir+"\\images\\Qbub.jpg"; //��������� ������� �����
  cards[27].pict = InitDir+"\\images\\Qvin.jpg"; //��������� ������� �����
  cards[28].pict = InitDir+"\\images\\Qkr.jpg"; //��������� ������� �����
 //������
  cards[29].pict = InitDir+"\\images\\Kch.jpg"; //��������� ������� �����
  cards[30].pict = InitDir+"\\images\\Kbub.jpg"; //��������� ������� �����
  cards[31].pict = InitDir+"\\images\\Kvin.jpg"; //��������� ������� �����
  cards[32].pict = InitDir+"\\images\\Kkr.jpg"; //��������� ������� �����
 //����
  cards[33].pict = InitDir+"\\images\\Tch.jpg"; //��������� ������� �����
  cards[34].pict = InitDir+"\\images\\Tbub.jpg"; //��������� ������� �����
  cards[35].pict = InitDir+"\\images\\Tvin.jpg"; //��������� ������� �����
  cards[36].pict = InitDir+"\\images\\Tkr.jpg"; //��������� ������� �����
 }

__fastcall TFmFool::TFmFool(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

/**
1. ��������  ��  ������  ������:
     if (conQuan == 0) return true;  -  ����  ����������  ����  ��  ������  �����  0,
       ��  �������  ����������  true (�.�.  �����  �����  ��������).
2. ��������  ����  ������,  �������  �����:
     for (i = 1; i <= conQuan; i++)  -  ����  ����������  �����  ��  ������.
       k = PCardsCon[PlayerHod][i].num; -  �  ����������  k  �����������  �����
         �����  ��  ������  (PCardsCon  -  ������,  ��������  ����������  �  ������  �������).
       t = k;  -  �  ����������  t  �����������  ��������  �����  �����.
       while (k % 4 != 0)  -  ����  �����������,  ����  k  ��  �����  ��������
         ��  4  ���  �������  (�.�.  ����  ��  �����  ����������  �����  "�����").
         k -= 1; -  k  �����������  ��  1.
       if (t % 4 != 0) k += 1; -  ����  ��������  �����  �����  ��  "�����",
         ��  k  �������������  ��  1 (�����  �������  ���  �  �����  �����).
       if ((num >= k) && (num <= k + 3) && ((t % 4 != 0))) - �����������,
         �������������  ��  �����  ������������  �����  (num) ���������  ����
         ��  ������  (�  ������,  ��������  ��  "������"). ���� ��,
         ��  �������  ����������  true.
       if ((num >= k - 3) && (num <= k) && ((t % 4 == 0))) - �����������,
         �������������  ��  �����  ������������  �����  (num)  ���������  ����
         ��  ������  (�  ������  "�����"). ����  ��, �� �������  ����������  true.
3. ��������  ����  �������  ������:
     int noPlayerHod = GetNoPlayerHod();  -  ����������  �������  GetNoPlayerHod
       ���  ����������  �����  ������,  �������  ��  �����).
     for (i = 1; i <= conQuan; i++)  -  ����  ����������  �����  ��  ������.
       ������  �����  ����������  ������  �����������  �����,
       ������  �����������  �����  �������  ������  (noPlayerHod).
4. �����������  false:
     return false;  -  ����  ��������  �����  ������
     (��  ��  ��������  ������  ����,  ��  ��  �������  ���������������  ����  �  �������),
     ��  �������  ����������  false.
**/

boolean CanGiveMy(int num) //�������� ����� �� ���� ��� ����� �����
{
 int i,k,t;
 //return true;
 if (conQuan == 0) return true;
 for(i=1;i<=conQuan;i++)
  {
    k = PCardsCon[PlayerHod][i].num; //������� �� ������ ����� ������� ��������
    t = k;
    while (k % 4 != 0)
      {
        k -= 1;
      }
     if (t % 4 != 0) k += 1; //�� ������;
     if ((num >= k) && (num <= k+3) && ((t % 4 != 0)))
     {

     return true;
     }
     if ((num >= k-3) && (num <= k) && ((t % 4 == 0)))
     {

      return true;
     }
  }     //�������� ������� �� ����� ����� � ����

  int noPlayerHod = GetNoPlayerHod();
  for(i=1;i<=conQuan;i++)
  {
    k = PCardsCon[noPlayerHod][i].num; //������� �� ������ ����� ������� ��������
    t = k;
    while (k % 4 != 0)
      {
        k -= 1;
      }
      if (t % 4 != 0) k += 1; //�� ������;
     if ((num >= k) && (num <= k+3) && ((t % 4 != 0)))
     {
     return true;
     };

     if ((num >= k-3) && (num <= k) && ((t % 4 == 0)))
     {
     return true;
     }
  }     //�������� ������� �� ����� ����� � ����
 return false;
}

/**
1. ��������  ��  ������:
     if (Pquan[playerNum] == 0)  -  ����  �  ������  �  �������
       playerNum  ���  ����  (Pquan[playerNum] == 0),
       ��  ���������  ���������  �  ������  �  �������  �����������.

2. �����  ����:
     for (j = 1; j <= Pquan[playerNum]; j++)  -
       �������  ����  ����������  ���  �����  �  �������  ������.
     for (i = 1; i <= Pquan[playerNum]; i++)  -
       ����������  ����  �����  ����������  ���  �����  �  �������  ������.
       if ((PCards[playerNum][i].num == 0) && (PCards[playerNum][i + 1].num != 0))  -
         �����������,  ����  �  �������  �����  i  ���  �����  (PCards[playerNum][i].num == 0),
         �  �  ���������  �����  i + 1  ����  �����  (`PCards[playerNum][i + 1].num != 0`).
          PCards[playerNum][i].num = PCards[playerNum][i + 1].num;  -
            �  �������  ����  i  ������������  �����  �����  ��  ����������  �����  i + 1.
          PCards[playerNum][i + 1].num = 0;  -  �����  �����  �  ���������  �����  i + 1  ����������.
          PCards[playerNum][i].pict = PCards[playerNum][i + 1].pict;  -
            �  �������  ����  i  ������������  �����������  �����  ��  ����������  �����  `i + 1`.
          PCards[playerNum][i + 1].pict = "";  -  �����������  �����
            �  ���������  �����  i + 1  ����������.

**/

void moving(int playerNum) //��������� ������ ����
{
  int i,j;
  if (Pquan[playerNum] == 0)
  {
      ShowMessage("������� " + PlayerName[playerNum]);
      return;
  }
  for(j=1;j<=Pquan[playerNum];j++)
    for(i=1;i<=Pquan[playerNum];i++)
    {
      if ((PCards[playerNum][i].num == 0) && (PCards[playerNum][i+1].num != 0))
      {
        //ShowMessage("Moving "+IntToStr(i));
        PCards[playerNum][i].num  = PCards[playerNum][i+1].num;
        PCards[playerNum][i+1].num  = 0;
        PCards[playerNum][i].pict = PCards[playerNum][i+1].pict;
        PCards[playerNum][i+1].pict = "";

      }
    }
}

void downMoving(int playerNum) //��������� ������ ���� ������� �������� ����
{
    moving(playerNum);

    if (Pquan[playerNum] > 6)
    {
      FmFool->ButtonRight->Enabled = true;
    }
    else

    {
      FmFool->ButtonRight->Enabled = false;
      FmFool->ButtonLeft->Enabled = false;
    }
}

boolean CheckComp() //�������� ����� �� ���� ��������
{int i,j;
  if (PlayerTake == true) return false;
  for(i=1;i<=conQuan;i++) //���� �� ������ �� ����
    {
      if (PCardsCon[1][i].taken == false) //���� ������� ����� �� ���� ��� ������
      {
        for(j=1;j<=Pquan[2];j++) //���� �� ������ ����������
         {
           if((PCardsCon[1][i].num%4 == PCards[2][j].num%4) && (PCardsCon[1][i].num < PCards[2][j].num))
             //����� �� �������� ��� �������
             {
               PCardsCon[2][i].num = PCards[2][j].num;//��� ����� �� ���
               PCardsCon[2][i].pict = PCards[2][j].pict;
               PCards[2][j].num = 0;
               PCardsCon[1][i].taken = true;
               moving(Player2);
               Pquan[2] -= 1; //���������� ���� ����� ����������� �� �������
               if ((Pquan[2]==0) && (quan==0))
                 {
                   FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("������� ���������");
                    UWin = false;
                 }
               //���� ��������� ��������� ������ ����
               return true;
             }

         } //End ����� �� ��� �������


        //�������� ����� �� �������� ��������

        for(j=1;j<=Pquan[2];j++) //���� �� ������ �����
         {
           //����� ������� ���� ������ - �� ������
           if((PCardsCon[1][i].num%4 != Mcard) && (PCards[2][j].num%4==Mcard))
             //����� �������� �������
             {
               PCardsCon[2][i].num = PCards[2][j].num;//��� ����� �� ���
               PCardsCon[1][i].taken = true; //������� ����� ������
               PCardsCon[2][i].pict = PCards[2][j].pict;
               PCards[2][j].num = 0;
               moving(Player2);
               Pquan[2] -= 1; //���������� ���� ����� ����������� �� �������
               if ((Pquan[2]==0) && (quan==0))
                 {
                   FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("������� ���������");
                    UWin = false;
                    //return;
                 }
               return true;
             }
           //����� ������� ���� ������ ������
           if((PCardsCon[1][i].num%4 == Mcard) && (PCards[2][j].num%4==Mcard) && (PCardsCon[1][i].num<PCards[2][j].num))
             //����� �������� �������
             {
               PCardsCon[2][i].num = PCards[2][j].num;//��� ����� �� ���
               PCardsCon[1][i].taken = true;
               PCardsCon[2][i].pict = PCards[2][j].pict;
               PCards[2][j].num = 0;
               moving(Player2);

               Pquan[2] -= 1; //���������� ���� ����� ����������� �� �������
               if ((Pquan[2]==0) && (quan==0))
                 {
                   FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("������� ���������");
                    UWin = false;
                    //return;
                 }
               return true;
             }
         }

         //ShowMessage("����� ��!");
         PlayerTake = true; //���� �����

         return false;

      }  //End ���� ������� ����� �� ������

    }
   // ShowMessage("�� ���� ��� �������");
    PlayerTake = false; //����
    moving(Player2);
    return true;


 //���������� ��������
};


boolean CheckMy(int num) //�������� ����� �� �� ��������
{
int i,j;

  int noPlayerHod = GetNoPlayerHod();
  for(i=1;i<=conQuan;i++) //���� �� ������ �� ����
    {
      if (PCardsCon[PlayerHod][i].taken == false) //���� ������� ����� �� ���� ��� ������ � ����� �������
      {
         {
           if((PCardsCon[PlayerHod][i].num % 4 == PCards[noPlayerHod][num].num % 4) && (PCardsCon[PlayerHod][i].num < PCards[noPlayerHod][num].num))
             //����� �� �������� ��� �������
             {
               PCardsCon[noPlayerHod][i].num = PCards[noPlayerHod][num].num;//��� ����� �� ���
               PCardsCon[noPlayerHod][i].pict = PCards[noPlayerHod][num].pict;
               PCards[noPlayerHod][num].num = 0;
               PCards[noPlayerHod][num].pict = "";
               PCardsCon[PlayerHod][i].taken = true;
               downMoving(PlayerActive);
               Pquan[noPlayerHod] -= 1; //���������� ���� ����������� �� �������
               if ((Pquan[noPlayerHod]==0) && (quan==0))
                 {
                    UWin = true;
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("���� ������������ - �� ��������");
                 }
               return true;
             }

         } //End ����� �� ��� �������


        //�������� ����� �� �������� ��������

         {
           //����� ������� ���� ������ - �� ������
           if((PCardsCon[PlayerHod][i].num % 4 != Mcard) && (PCards[noPlayerHod][num].num%4==Mcard))
             //����� �������� �������
             {
               //ShowMessage("����� �������� �������!!! "+IntToStr(Mcard)+ "    "+PCards[GetNoPlayerActive][num].num);
               PCardsCon[noPlayerHod][i].num = PCards[noPlayerHod][num].num;//��� ����� �� ���
               PCardsCon[PlayerHod][i].taken = true; //������� ����� ������
               PCardsCon[noPlayerHod][i].pict = PCards[noPlayerHod][num].pict;
               PCards[noPlayerHod][num].num = 0;
               PCards[noPlayerHod][num].pict = "";
               downMoving(PlayerActive);
               Pquan[noPlayerHod] -= 1; //���������� ���� ����� ����������� �� �������
                if ((Pquan[noPlayerHod]==0) && (quan==0))
                 {
                    UWin = true;
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("���� ������������ - �� ��������");
                 }
               return true;
             };
           //����� ������� ���� ������ ������
           if((PCardsCon[PlayerHod][i].num % 4 == Mcard) && (PCards[noPlayerHod][num].num % 4==Mcard) && (PCardsCon[PlayerHod][i].num < PCards[noPlayerHod][num].num))
             //����� �������� �������
             {
               PCardsCon[noPlayerHod][i].num = PCards[noPlayerHod][j].num;//��� ����� �� ���
               PCardsCon[PlayerHod][i].taken = true;
               PCardsCon[noPlayerHod][i].pict = PCards[noPlayerHod][j].pict;
               PCards[noPlayerHod][num].num = 0;
               PCards[noPlayerHod][num].pict = "";
               downMoving(PlayerActive); //��������� ������ ����

               Pquan[noPlayerHod] -= 1; //���������� ���� ����� ����������� �� �������
                if ((Pquan[noPlayerHod]==0) && (quan==0))
                 {
                    UWin = true;
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("���� ������������ - �� ��������");
                 }
               return true;
             }
         }

      }  //End ���� ������� ����� �� ������

    }

    return false;



}



boolean CheckKoz() //�������� ��� �� ����� � ����� ������
{int i;
 for(i=1;i<=Pquan[2];i++)
   {
     if (PCards[2][i].num % 4 != Mcard) return false; //���� ���������� �����
   }
 return true; //��� ������
}


boolean CanGive(int num) //�������� ����� �� ���� ���� ������ ����� (�������)
{
 int i,k,t;
 if (conQuan == 0) return true;
 for(i=1;i<=conQuan;i++)
  {
    k = PCardsCon[1][i].num; //������� �� ������ ����� ������� ��������
    t = k;
    while (k % 4 != 0)
      {
        k -= 1;
      }
      if (t % 4 != 0) k += 1; //�� ������;
     if ((num >= k) && (num <= k+3) && ((t % 4 != 0))) return true;
     if ((num >= k-3) && (num <= k) && ((t % 4 == 0))) return true;

  }     //�������� ������� �� ����� ����� ��� �� ���� � ���


  for(i=1;i<=conQuan;i++)
  {
    k = PCardsCon[2][i].num; //������� �� ������ ����� ������� ��������
    t = k;
    while (k % 4 != 0)
      {
        k -= 1;
      }
     if (t % 4 != 0) k += 1; //�� ������;
     if ((num >= k) && (num <= k+3) && ((t % 4 != 0))) return true;
     if ((num >= k-3) && (num <= k) && ((t % 4 == 0))) return true;

  }     //�������� ������� �� ����� ����� ��� �� ���� � �����
 return false;
}


void HodComp()
{int i;
  if (PlayerHod == Player1)  //��������� ����������
    {
      if ((Pquan[1] == 0)  && (quan == 0))
       {
         ShowMessage("���� ������������ - �� ��������");
         UWin = true;
         return;

       }
      if (CheckComp() == true)
        {
          drawCards();//���������� ����
          FmFool->ButOper->Caption = "����";

        }
      else //���� �� ����������
      {

         FmFool->ButOper->Caption = "������";
         drawCards();//���������� ����
      }
    }
  else   //��������� �����
  {

      //ShowMessage("�� �����");
      FmFool->ButOper->Caption = "�����";
      boolean hod;
      hod = false; //������ ����
      if (conQuan < 6)
      {
      //int min,num,i;
      AnsiString pict;
      if (CheckKoz() == false)//���� ���� ���������� �����, �� � ��� �����
        {

          for(i=1;i<=Pquan[2];i++) //����� �����, ���. ���� ����� ������
            {
              if ((CanGive(PCards[2][i].num)== true) && (PCards[2][i].num % 4 != Mcard)) //����� �� �� ���� ������� �����
                {
                  conQuan += 1;
                  //ShowMessage("bla bla "+IntToStr(conQuan));
                  PCardsCon[2][conQuan].num = PCards[2][i].num;
                  PCardsCon[2][conQuan].pict = PCards[2][i].pict;
                  //ShowMessage(IntToStr(conQuan)+"  "+ PCardsCon[2][conQuan].pict);
                  PCards[2][i].num = 0;
                  PCards[2][i].pict = "";
                  moving(Player2); //����� ����
                  drawCards(); //����������� ����
                  hod = true;
                  Pquan[2] -= 1;
                  if ((Pquan[2] ==0) && (quan == 0))
                  {
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("������� ���������");
                    UWin = false;
                    return;
                  }
                  return;
                }
            }


        }
     if (CheckKoz() == true)//���� ��� �������� �����
        {
          for(i=1;i<=Pquan[2];i++) //����� �����, ��� ���� ����� ������
            {
              if (CanGive(PCards[2][i].num)==true ) //��� ����� ����� ��������
                {
                  conQuan += 1;

                  PCardsCon[2][conQuan].num = PCards[2][i].num;
                  PCardsCon[2][conQuan].pict = PCards[2][i].pict;
                  PCards[2][i].num = 0;
                  PCards[2][i].pict = "";
                  moving(Player2); //����� ����
                  drawCards(); //����������� ����
                  hod = true;
                  Pquan[2] -= 1;
                   if ((Pquan[2] <=0) && (quan == 0))
                  {
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("������� ���������");
                    UWin = false;
                    return;
                  }
                  return;
              
                }
            }


        } //End ���� ��� ������

         //for(i=1;i<=Pquan[2];i++)
         if (hod == false) //���� ���� ������ ����, ���. ����� ����
         {
           //ShowMessage("���� �� ����� 1");
           FmFool->LPrompt->Caption = "��� ���";
           for(i=1;i<=6;i++)
             {
                PCardsCon[1][i].taken = false;
                PCardsCon[2][i].taken = false;
                PCardsCon[1][i].num = 0;
                PCardsCon[2][i].num = 0;
                PCardsCon[1][i].pict = "";
                PCardsCon[2][i].pict = "";
             };
          conQuan = 0;
          FmFool->ButOper->Caption = "����";
          PlayerHod = Player1;
          givecards();
             //��� ��� ������
         } //End ���� ���� ������ ����, ���. ����� ���� � �����
      } //End ���� ���� �� ���� ������ 6
     else //��� 6 ���� ������
     {
      //����

           for(i=1;i<=6;i++)
             {
                PCardsCon[1][i].taken = false;
                PCardsCon[2][i].taken = false;
                PCardsCon[1][i].num = 0;
                PCardsCon[2][i].num = 0;
                PCardsCon[1][i].pict = "";
                PCardsCon[2][i].pict = "";
             };
       conQuan = 0;
       givecards();
       PlayerHod = Player1;
     }
  } //End ��������� �����
}

void __fastcall TFmFool::FormActivate(TObject *Sender)
{int i;
 randomize();
  for (i =0;i<=36;i++)
    cards[i].taken  = FALSE;
  quan = 36; //��������� ����� ����
  Pquan[Player1] = 0;
  Pquan[Player2] = 0;
  PlayerHod = Player1;
}
//---------------------------------------------------------------------------

void __fastcall TFmFool::Button1Click(TObject *Sender)
{
  int i;

  if (FrmGameMode->ShowModal() == mrCancel) return;
  GameMode = FrmGameMode->GameMode;
  //����� ���� ������������ � �����������
  if (GameMode == 1)
  {
     Button1->Enabled = false;
     ButOper->Enabled = true;
     ButtonLeft->Enabled = false;
     ButtonRight->Enabled = false;
     PlayerTake = false; //�� ��������� ���� �� �����

     PlayerActive = Player1;
     PlayerName[Player1] = "�����";
     PlayerName[Player2] = "���������";

     Pquan[Player1] = 6;
     Pquan[Player2] = 6;//!!! ����� ���� ��� ����� ���������!!!
     conQuan = 0;
     quan = 36;
     for (i =0;i<=36;i++)
     {
        cards[i].taken  = FALSE;
        PCards[Player1][i].num = 0;
        PCards[Player2][i].num = 0;
        PCards[Player1][i].pict = "";
        PCards[Player2][i].pict = "";
     }
     for (i =0;i<=6;i++)
     {
        PCardsCon[Player2][i].taken = false;
        PCardsCon[Player1][i].taken = false;
        PCardsCon[Player1][i].num = 0;
        PCardsCon[Player2][i].num = 0;
        PCardsCon[Player1][i].pict = "";
        PCardsCon[Player2][i].pict = "";
     }
     //FmFool->UIM1->Picture->Free();
     givecards();
     drawCards();
     if (UWin == false)
     {
        PlayerHod = Player2;
        LPrompt->Caption = "�����������";
        HodComp();
     }
     else
     {
        LPrompt->Caption = "��� ���";
        PlayerHod = Player1;
     }
  }
  //����� ���� ������������ � �������������
  if (GameMode == 2)
  {
     Button1->Enabled = false;
     ButOper->Enabled = true;
     ButtonLeft->Enabled = false;
     ButtonRight->Enabled = false;

     PlayerName[Player1] = "����� 1";
     PlayerName[Player2] = "����� 2";

     Pquan[Player1] = 6;
     Pquan[Player2] = 6;
     conQuan = 0;
     quan = 36;
     for (i =0;i<=36;i++)
     {
        cards[i].taken  = FALSE;
        PCards[Player1][i].num = 0;
        PCards[Player2][i].num = 0;
        PCards[Player1][i].pict = "";
        PCards[Player2][i].pict = "";
     }
     for (i =0;i<=6;i++)
     {
        PCardsCon[Player2][i].taken = false;
        PCardsCon[Player1][i].taken = false;
        PCardsCon[Player1][i].num = 0;
        PCardsCon[Player2][i].num = 0;
        PCardsCon[Player1][i].pict = "";
        PCardsCon[Player2][i].pict = "";
     }

     givecards();

     if (UWin == false)
     {
        PlayerHod = Player2;
        PlayerActive = Player2;
     }
     else
     {
        PlayerHod = Player1;
        PlayerActive = Player1;
     }

     drawCards();
     drawendhod();
     LPrompt->Caption = PlayerName[PlayerHod] + " ��� ���";
  }

}
//---------------------------------------------------------------------------


void __fastcall TFmFool::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  if (flag == TRUE)
    {
      UIM1->Top = 366;
      UIM2->Top = 366;
      UIM3->Top = 366;
      UIM4->Top = 366;
      UIM5->Top = 366;
      UIM6->Top = 366;
    }
  flag = FALSE;
}
//---------------------------------------------------------------------------
void __fastcall TFmFool::UIM1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  if (flag == FALSE)
    {
      UIM1->Top = UIM1->Top-5;
    }
  flag = TRUE;



}
//---------------------------------------------------------------------------
void __fastcall TFmFool::UIM2MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
   if (flag == FALSE)
    {
      UIM2->Top = UIM2->Top-5;
    }
  flag = TRUE;

}
//---------------------------------------------------------------------------
void __fastcall TFmFool::UIM3MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
   if (flag == FALSE)
    {
      UIM3->Top = UIM3->Top-5;
    }
  flag = TRUE;

}
//---------------------------------------------------------------------------
void __fastcall TFmFool::UIM4MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
   if (flag == FALSE)
    {
      UIM4->Top = UIM4->Top-5;
    }
  flag = TRUE;

}
//---------------------------------------------------------------------------
void __fastcall TFmFool::UIM5MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
   if (flag == FALSE)
    {
      UIM5->Top = UIM5->Top-5;
    }
  flag = TRUE;

}
//---------------------------------------------------------------------------
void __fastcall TFmFool::UIM6MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
   if (flag == FALSE)
    {
      UIM6->Top = UIM6->Top-5;
    }
  flag = TRUE;

}
//---------------------------------------------------------------------------
void HodMy(int cquan,int num)
{
   switch (cquan)
            {
            case 1: FmFool->ImConM1->Visible = true; FmFool->ImConM1 ->Picture->LoadFromFile(PCards[PlayerActive][num].pict); break;
            case 2: FmFool->ImConM2->Visible = true; FmFool->ImConM2 ->Picture->LoadFromFile(PCards[PlayerActive][num].pict); break;
            case 3: FmFool->ImConM3->Visible = true; FmFool->ImConM3 ->Picture->LoadFromFile(PCards[PlayerActive][num].pict); break;
            case 4: FmFool->ImConM4->Visible = true; FmFool->ImConM4 ->Picture->LoadFromFile(PCards[PlayerActive][num].pict); break;
            case 5: FmFool->ImConM5->Visible = true; FmFool->ImConM5 ->Picture->LoadFromFile(PCards[PlayerActive][num].pict); break;
            case 6: FmFool->ImConM6->Visible = true; FmFool->ImConM6 ->Picture->LoadFromFile(PCards[PlayerActive][num].pict); break;
            }

}

void CardClick(TObject *Sender, int cardNum)
{
  //����� ���� ������������ � �����������
  if (GameMode == 1)
  {
     if (PlayerHod == Player1)
     {
        if (conQuan < 6)
        {
           if (CanGiveMy(PCards[1][cardNum].num) == true)
           {
              conQuan += 1;
              ((TImage*)Sender)->Visible = false;
              HodMy(conQuan,cardNum);

              PCardsCon[1][conQuan].num = PCards[1][cardNum].num;
              PCardsCon[1][conQuan].pict = PCards[1][cardNum].pict;
              PCards[1][cardNum].pict = "";
              PCards[1][cardNum].num = 0;
              downMoving(Player1);
              Pquan[1] -= 1;
              if ((Pquan[1] == 0 ) && (quan == 0))
              {
                 UWin = true;
                 FmFool->ButOper ->Enabled = false;
                 FmFool->Button1 ->Enabled = true;
                 ShowMessage("���� ������������ - �� ��������");
              }
              HodComp();
           }
        }
     }
     else //�� ����������
     {
        if (CheckMy(cardNum)== true)
        {
           HodComp();
           drawCards();
        }
     }
  }
  //����� ���� ������������ � �������������
  if (GameMode == 2)
  {
     if (PlayerHod == PlayerActive)
     {
        if (conQuan < 6)
        {
           if (CanGiveMy(PCards[PlayerHod][cardNum].num) == true)
           {
              conQuan += 1;
              ((TImage*)Sender)->Visible = false;
              HodMy(conQuan,cardNum);

              PCardsCon[PlayerHod][conQuan].num = PCards[PlayerHod][cardNum].num;
              PCardsCon[PlayerHod][conQuan].pict = PCards[PlayerHod][cardNum].pict;
              PCards[PlayerHod][cardNum].pict = "";
              PCards[PlayerHod][cardNum].num = 0;
              downMoving(PlayerHod);
              Pquan[PlayerHod] -= 1;
              if ((Pquan[1] == 0 ) && (quan == 0))
              {
                 UWin = true;
                 FmFool->ButOper ->Enabled = false;
                 FmFool->Button1 ->Enabled = true;
                 ShowMessage(PlayerName[PlayerHod] + " ���� ������������ - �� ��������");
              }
              else
              {
                 if (PlayerTake == false)
                    PlayerActive = GetNoPlayerActive();

                 drawCards();

                 if (PlayerTake == false)
                 {
                    drawendhod();

                    if (Pquan[PlayerActive] > 6)
                    {
                       FmFool->ButtonRight->Enabled = true;
                    }
                    else
                    {
                       FmFool->ButtonRight->Enabled = false;
                       FmFool->ButtonLeft->Enabled = false;
                    }
                 }
              }

           }
        }
     }
     else //�� ����������
     {
        if (CheckMy(cardNum)== true)
        {
           PlayerActive = GetNoPlayerActive();
           drawCards();

           drawendhod();

           if (Pquan[PlayerActive] > 6)
           {
              FmFool->ButtonRight->Enabled = true;
           }
           else
           {
              FmFool->ButtonRight->Enabled = false;
              FmFool->ButtonLeft->Enabled = false;
           }
        }
     }

  }
}

void __fastcall TFmFool::UIM1Click(TObject *Sender)
{
   CardClick(Sender, 1);
}
//---------------------------------------------------------------------------

void __fastcall TFmFool::UIM2Click(TObject *Sender)
{
   CardClick(Sender, 2);
}
//---------------------------------------------------------------------------

void __fastcall TFmFool::UIM3Click(TObject *Sender)
{
   CardClick(Sender, 3);
}
//---------------------------------------------------------------------------

void __fastcall TFmFool::UIM4Click(TObject *Sender)
{
   CardClick(Sender, 4);
}
//---------------------------------------------------------------------------

void __fastcall TFmFool::UIM5Click(TObject *Sender)
{
   CardClick(Sender, 5);
}
//---------------------------------------------------------------------------

void __fastcall TFmFool::UIM6Click(TObject *Sender)
{
   CardClick(Sender, 6);
}
//---------------------------------------------------------------------------

void __fastcall TFmFool::ButOperClick(TObject *Sender)
{
  int i,cur;//cur - ������� ����� �� ����
  //����� ���� ������������ � �����������
  if(GameMode == 1)
  {
     if (PlayerHod == Player1)
     {
        LPrompt->Caption = " ��� ���";
        //ShowMessage(IntToStr(conQuan));

        if (CheckComp() == false)  //���� ����� �����, ���. �� ��� ����.
        {
           if (conQuan != 0)
           {
              //ShowMessage("���� ����� �����!!!");
              cur = 1;
              for(i=1;i<=36;i++) //������� ���� �������� ���� �����
              {
                 if (PCards[2][i].num ==0)//����� ���� �����
                 {

                    if (PCardsCon[2][cur].num != 0) //���� �� ����
                    {
                       PCards[2][i].num = PCardsCon[2][cur].num;
                       PCards[2][i].pict = PCardsCon[2][cur].pict;
                       PCardsCon[2][cur].pict = "";
                       PCardsCon[2][cur].num = 0;
                       Pquan[2] += 1;  //���������� ����� ���� �����

                       cur += 1; //���� �������� ������� �����
                    }
                 }
              }

              cur = 1;
              for(i=1;i<=36;i++) //����� ���� �������� ���� �����
              {
                 if (PCards[2][i].num ==0)//����� ���� �����
                 {

                    if (PCardsCon[1][cur].num != 0) //���� �� ����
                    {
                       PCards[2][i].num = PCardsCon[1][cur].num;
                       PCardsCon[1][cur].num = 0;
                       PCards[2][i].pict = PCardsCon[1][cur].pict;
                       PCardsCon[1][cur].pict = "";
                       Pquan[2] += 1; //���������� ����� ���� �����
                       cur += 1; //���� �������� ������� �����
                    }
                 }
              }

              drawCards();
              conQuan = 0; //���� �� ���� �� ��������

              for(i=1;i<=6;i++)
                 PCardsCon[1][i].taken = false;

              PlayerHod = Player1;
              givecards();

              PlayerTake = false;
           }// End If conquan <> 0
        }//END ���� ���� �����
        else
        {
           if (conQuan != 0)
           {
              PlayerHod = Player2;   //��� ��� ��������
              LPrompt->Caption = "�����������";

              for(i=1;i<=6;i++)
              {
                 PCardsCon[1][i].taken = false;
                 PCardsCon[2][i].taken = false;
                 PCardsCon[1][i].num = 0;
                 PCardsCon[2][i].num = 0;
                 PCardsCon[1][i].pict = "";
                 PCardsCon[2][i].pict = "";
              };

              //ShowMessage("����!!!");
              //Pquan[1]
              conQuan = 0; //���� �� ���� �� ��������
              givecards(); //������� ����
              drawCards(); //����������� ����
              HodComp();
           }//End if conQuan != 0
        }

     } //End ���� �� �����
     else //�� �����
     {
        //�������� �����
        if (conQuan != 0)
        {
           //ShowMessage("� ����!!!");
           cur = 1;
           for(i=1;i<=36;i++) //������� � ������� ��� �����
           {
              if (PCards[1][i].num ==0)//����� ����
              {

                 if (PCardsCon[2][cur].num != 0) //���� �� ����
                 {
                    PCards[1][i].num = PCardsCon[2][cur].num;
                    PCards[1][i].pict = PCardsCon[2][cur].pict;
                    PCardsCon[2][cur].num = 0;
                    PCardsCon[2][cur].pict = "";
                    Pquan[1] += 1;  //���������� ����� ���� ����

                    cur += 1; //� ������� ������� �����
                 }
              }
           }

           cur = 1;
           for(i=1;i<=36;i++) //�����  �������� ���� �����
           {
              if (PCards[1][i].num ==0)//����� ����
              {

                 if (PCardsCon[1][cur].num != 0) //���� �� ����
                 {
                    PCards[1][i].num = PCardsCon[1][cur].num;
                    PCardsCon[1][cur].num = 0;
                    PCards[1][i].pict = PCardsCon[1][cur].pict;
                    PCardsCon[1][cur].pict = "";
                    Pquan[1] += 1; //���������� ����� ���� �����
                    cur += 1; //���� �������� ������� �����
                 }
              }
           }

           drawCards();
           conQuan = 0; //���� �� ���� �� ��������
           for(i=1;i<=6;i++)
              PCardsCon[2][i].taken = false;

           PlayerHod = Player2;
           givecards();

           if (Pquan[1] > 6)
           {
              FmFool->ButtonRight->Enabled = true;
           }
           else
           {
              FmFool->ButtonRight->Enabled = false;
              FmFool->ButtonLeft->Enabled = false;
           }

           HodComp();


        }
     }

  }

  //����� ���� ������������ � �������������
  if(GameMode == 2)
  {
     if (PlayerHod == PlayerActive)
     {
        LPrompt->Caption = PlayerName[PlayerActive] + " ��� ���";
        //ShowMessage(IntToStr(conQuan));

           if (conQuan != 0)
           {
              //������ �����
              if (PlayerTake)
              {
                 int noPlayerHod = GetNoPlayerHod();

                 //ShowMessage("������ �����!!!");
                 cur = 1;
                 for(i=1;i<=36;i++) //������� � ������� ��� �����
                 {
                    if (PCards[noPlayerHod][i].num ==0)//����� ����
                    {

                        if (PCardsCon[PlayerHod][cur].num != 0) //���� �� ����
                        {
                           PCards[noPlayerHod][i].num = PCardsCon[PlayerHod][cur].num;
                           PCards[noPlayerHod][i].pict = PCardsCon[PlayerHod][cur].pict;
                           PCardsCon[PlayerHod][cur].num = 0;
                           PCardsCon[PlayerHod][cur].pict = "";
                           Pquan[noPlayerHod] += 1;  //���������� ����� ���� ����

                           cur += 1; //� ������� ������� �����
                        }
                    }
                 }

                 cur = 1;
                 for(i=1;i<=36;i++) //�����  �������� ���� �����
                 {
                    if (PCards[noPlayerHod][i].num ==0)//����� ����
                    {

                        if (PCardsCon[noPlayerHod][cur].num != 0) //���� �� ����
                        {
                           PCards[noPlayerHod][i].num = PCardsCon[noPlayerHod][cur].num;
                           PCardsCon[noPlayerHod][cur].num = 0;
                           PCards[noPlayerHod][i].pict = PCardsCon[noPlayerHod][cur].pict;
                           PCardsCon[noPlayerHod][cur].pict = "";
                           Pquan[noPlayerHod] += 1; //���������� ����� ���� �����
                           cur += 1; //���� �������� ������� �����
                        }
                    }
                 }

                 conQuan = 0; //���� �� ���� �� ��������
                 for(i=1;i<=6;i++)
                    PCardsCon[PlayerHod][i].taken = false;

                 PlayerTake = false;
                 givecards();
                 drawCards();
              }
              else
              {

                 PlayerHod = GetNoPlayerHod();   //��� ��� ��������
                 PlayerActive = GetNoPlayerActive();

                 LPrompt->Caption = PlayerName[PlayerActive] + " �����������";

                 for(i=1;i<=6;i++)
                 {
                    PCardsCon[Player1][i].taken = false;
                    PCardsCon[Player2][i].taken = false;
                    PCardsCon[Player1][i].num = 0;
                    PCardsCon[Player2][i].num = 0;
                    PCardsCon[Player1][i].pict = "";
                    PCardsCon[Player2][i].pict = "";
                 };

                 conQuan = 0; //���� �� ���� �� ��������
                 givecards(); //������� ����
                 drawCards(); //����������� ����

                 drawendhod();//���������� ��������� ���� ������

                 if (Pquan[PlayerActive] > 6)
                 {
                    FmFool->ButtonRight->Enabled = true;
                 }
                 else
                 {
                    FmFool->ButtonRight->Enabled = false;
                    FmFool->ButtonLeft->Enabled = false;
                 }
              }

           }//End if conQuan != 0

     } //End ���� �� �����
     else //�� �����
     {
        int noPlayerActive = GetNoPlayerActive();

        //�������� �����
        if (conQuan != 0)
        {
           PlayerTake = true;
           PlayerActive = noPlayerActive;
           drawCards();

           drawendhod(); //���������� ��������� ���� ������

           if (Pquan[PlayerActive] > 6)
           {
              FmFool->ButtonRight->Enabled = true;
           }
           else
           {
              FmFool->ButtonRight->Enabled = false;
              FmFool->ButtonLeft->Enabled = false;
           }


        }
     }

  }


}
//---------------------------------------------------------------------------

void __fastcall TFmFool::FormCreate(TObject *Sender)
{
 UWin = true; //�� ��������� ����� ������������
 InitDir = GetCurrentDir();
 ButOper->Enabled = false;
 initcards();

}
//---------------------------------------------------------------------------

void __fastcall TFmFool::ButtonRightClick(TObject *Sender)
{
   CSet temp;
   int i,q,j;
   if (Pquan[PlayerActive] > 6)
   {
      ButtonLeft->Enabled = true;
      q = Pquan[PlayerActive] - 6; //����� �� ����������� ����
      if (q <= 6)ButtonRight->Enabled = false;
      if (q > 6) q = 6;
      for(j=1;j<=q;j++)
      {
         temp = PCards[PlayerActive][1]; //
         for(i=1;i<=Pquan[PlayerActive]-1;i++)
         {
            PCards[PlayerActive][i]=PCards[PlayerActive][i+1];
         } //i
         PCards[PlayerActive][Pquan[PlayerActive]] = temp;
      } // j
      drawCards();
   }

}
//---------------------------------------------------------------------------

void __fastcall TFmFool::ButtonLeftClick(TObject *Sender)
{
   CSet temp;
   int i,q,j;
   if (Pquan[PlayerActive] > 6)
   {
      ButtonRight->Enabled = true;
      q = Pquan[PlayerActive] - 6; //����� �� ����������� ����
      //j = 1;
      if (q <= 6)ButtonLeft->Enabled = false;
      if (q > 6) q = 6;
      for(j=1;j<=q;j++)
      {
         temp = PCards[PlayerActive][Pquan[PlayerActive]]; //
         for(i=Pquan[PlayerActive];i>=2;i--)
         {
            PCards[PlayerActive][i]=PCards[PlayerActive][i-1];
         } //i
         PCards[PlayerActive][1] = temp;
      } // j
      drawCards();
   }
}
//---------------------------------------------------------------------------






void __fastcall TFmFool::CIM1Click(TObject *Sender)
{
        
}
//---------------------------------------------------------------------------

