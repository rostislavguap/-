//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnFool.h"
#include "UnitGameMode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

struct CSet    //Карты
 {
  AnsiString  pict; //1-черви,2-бубны,3-пики,4-трефы
  //int value; //2-2,3-3,
  int num;
  boolean  taken;
 }; //cards;


TFmFool *FmFool;
AnsiString fpath,InitDir;
CSet cards[37],PCards[3][37],temp,Coz;  //Все карты;
CSet PCardsCon[3][7]; //Карты на кону игрока и игрока/компьютера
int Pquan[3],quan; //Количество карт у игрока и игрока/компа
//у игрока и компьютера и в игре
int Mcard; //Масть козыря
int conQuan; //Карт на кону
boolean flag; //Была ли приподнята карта
boolean PlayerTake; //Берет ли комп или игрок
boolean UWin; //Кто победил в прошлом кону

int GameMode; //1-с компом, 2-друг с другом
int Player1 = 1; // игрок 1
int Player2 = 2; // комп или игрок 2
int PlayerHod;   // какой из игроков заходил
int PlayerActive;// игрой который в данный момент делает хож
String PlayerName[3];//имена игроков

//---------------------------------------------------------------------------

/**
1. int GetNoPlayerHod()
Функция определяет, кто должен делать ход следующим.
     Проверяет текущее значение переменной PlayerHod.
     Если `PlayerHod` равен Player1,
     то функция возвращает Player2 (ход переходит к другому игроку).
     Если `PlayerHod` равен Player2,
     то функция возвращает Player1 (ход переходит к первому игроку).
**/

int GetNoPlayerHod()
{
   if (PlayerHod == Player1) return Player2;
   if (PlayerHod == Player2) return Player1;
   return 0;
}

/**
2. int GetNoPlayerActive()
Функция определяет, кто из игроков является активным (играющим).
     Проверяет текущее значение переменной PlayerActive.
     Если PlayerActive равен Player1,
     то функция возвращает Player2 (активным становится второй игрок).
     Если PlayerActive равен Player2,
     то функция возвращает Player1 (активным становится первый игрок).

**/

int GetNoPlayerActive()
{
   if (PlayerActive == Player1) return Player2;
   if (PlayerActive == Player2) return Player1;
   return 0;
}

/**
1. Скрывает все карты:
     В начале функция скрывает все 6 компонент изображения, которые, вероятно,
     представляют собой 6 слотов для карт на игровом поле. Она делает это,
     устанавливая свойство Visible для каждого компонента в false.
2. Проходит по картам игрока:
     Цикл for  перебирает все 6 возможных слотов для карт (от 1 до 6).
      Внутри цикла, для каждого слота, функция проверяет,
      есть ли у игрока карта в этом слоте.  Она делает это,
      проверяя, не равно ли  PCardsCon[playerNum][i].num нулю.
3. Отрисовывает видимые карты:
      Если карта в слоте есть (ее num не равен нулю), функция:
          Отображает соответствующий компонент изображения (например, FmFool->ImConC1  для слота 1). 
          Загружает изображение карты в компонент с помощью метода LoadFromFile,
          используя PCardsCon[playerNum][i].pict для получения пути к файлу изображения карты.
4. Скрывает пустые слоты:
      Если в слоте нет карты (ее num равен нулю),
      функция скрывает соответствующий компонент изображения.
**/

void drawupcards(int playerNum)
{
  //Прорисовка кона со стороны компа
  FmFool->ImConC1->Visible = false;
  FmFool->ImConC2->Visible = false;
  FmFool->ImConC3->Visible = false;
  FmFool->ImConC4->Visible = false;
  FmFool->ImConC5->Visible = false;
  FmFool->ImConC6->Visible = false;

  for (int i=1;i<=6;i++) //Прорисовка карт на кону со стороны компа
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

    //Прорисовка карт компьютера
  FmFool->CIM1->Visible = false;
  FmFool->CIM2->Visible = false;
  FmFool->CIM3->Visible = false;
  FmFool->CIM4->Visible = false;
  FmFool->CIM5->Visible = false;
  FmFool->CIM6->Visible = false;

  for (int i=1;i<=Pquan[playerNum];i++) //Перерисовка карт компа
  {
     if (i <= 6)//У компа не больнше 6 карт
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
   FmFool->LCQuan->Caption = "Карт всего: "+IntToStr(Pquan[playerNum]);
}

void drawdowncards(int playerNum)
{
     //Прорисовка кона с нашей стороны
  FmFool->ImConM1->Visible = false;
  FmFool->ImConM2->Visible = false;
  FmFool->ImConM3->Visible = false;
  FmFool->ImConM4->Visible = false;
  FmFool->ImConM5->Visible = false;
  FmFool->ImConM6->Visible = false;

  for (int i=1;i<=6;i++) //Прорисовка карт на кону с нашей стороны
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

    //Прорисовка наших карт
  FmFool->UIM1->Visible = false;
  FmFool->UIM2->Visible = false;
  FmFool->UIM3->Visible = false;
  FmFool->UIM4->Visible = false;
  FmFool->UIM5->Visible = false;
  FmFool->UIM6->Visible = false;
  //ShowMessage(Pquan[1]);

  for (int i=1;i<=Pquan[playerNum];i++) //Перерисовка наших карт
  {
     //ShowMessage("Moving "+IntToStr(i)+ "   "+PCards[2][i].pict);
     if (i <= 6)//У нас не больнше 6 карт
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
   FmFool->LUQuan->Caption = "Карт всего: "+IntToStr(Pquan[playerNum]);
}

void drawCards()
{
  //Режим игры Пользователь с компьютером
  if (GameMode == 1)
  {
     drawupcards(Player2);
     drawdowncards(Player1);
  }
  //Режим игры Пользователь с пользователем
  if (GameMode == 2)
  {
     drawupcards(GetNoPlayerActive());
     drawdowncards(PlayerActive);

     if (PlayerHod == PlayerActive)
     {
        FmFool->LPrompt->Caption = PlayerName[PlayerActive] + " Ваш ход";
        if (PlayerTake)
           FmFool->ButOper->Caption = "Отдать";
        else
           FmFool->ButOper->Caption = "Бито";
     }
     else
     {
        FmFool->LPrompt->Caption = PlayerName[PlayerActive] + " Отбивайтесь";
        FmFool->ButOper->Caption = "Взять";
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
Функция загружает изображение карты из `cards[0].pict` в
6 различных компонент изображения на форме `FmFool`:
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

   ShowMessage("Ход " + PlayerName[PlayerActive]);

   drawCards();
}
/**
1.  Инициализация:
    boolean fl = false; -  переменная fl,  вероятно,  указывает на то,
      был ли уже заход в функцию. Она инициализируется в `false`.
      int n, i, m; -  объявляются целые переменные для использования в функции.
2.  Проверка количества карт:
    if (quan==0) goto finish; -  если  quan равно 0,
      то происходит переход к метке finish (подробнее о finish ниже).
    if (quan == 36) //Первая раздача карт -  если  quan равно 36,  то это  первая раздача карт.
       do n = random(36)+1; while (cards[n].taken == true); -
         в  цикле  do while  выбирается случайное число  n  от 1 до 36,
         и если карта с  индексом  n  в массиве  cards  уже  "взята"  (cards[n].taken == true),
         то  цикл  продолжается  и выбирается новое число.
       Coz.pict = cards[n].pict; -  в  переменную  Coz.pict  загружается изображение  козыря  из  массива  cards.
       Coz.num = n; -  в  переменную  Coz.num  загружается номер козыря из массива cards.
       Mcard = n % 4; -  вычисляется  масть  козыря  как  остаток  от  деления  n  на 4.
       cards[n].taken = true; -  карта  с  индексом  n  помечается  как  "взятая".

3.  Проверка хода:
    if (PlayerHod == Player2) -  если  ход  игрока 2,  то  переход  к  метке  l1.
    else -  если  ход  игрока 1,  то  переход  к  метке  l2.
4.  Раздача карт:
    l1: -  метка для  случая,  когда  ход  игрока 2.
    if (Pquan[1] < 6) -  если  у  игрока 1  менее 6 карт,  то:
       if (quan + Pquan[1] >= 6) Pquan[1] = 6;
       else Pquan[1] = Pquan[1] + quan; -  устанавливается  количество  карт  у  игрока 1  в  6,
         если  достаточно  карт  в  `quan`,  иначе  добавляются  все  оставшиеся  карты.
    l2: -  метка для  случая,  когда  ход  игрока 1.
    if (Pquan[2] < 6) Pquan[2] = 6; -  если  у  игрока 2  менее 6 карт,
      то  устанавливается  количество  его  карт  в  6.
    if (fl == true) goto finish; -  если  fl  равно  true,
      то  переход  к  метке  finish.
    for (i = 1; i <= Pquan[1]; i++) -  цикл  по  картам  игрока 1.
       if (PCards[1][i].num == 0) -  если  у  игрока 1  в  i-ом  слоте  нет  карты  (num  равно  0),  то:
          do { n = random(36) + 1; if (quan <= 2) break; } while (cards[n].taken == true); -
            в  цикле  do while выбирается случайное число  n  от 1 до 36,
            и если карта с  индексом  n  в массиве  cards  уже  "взята",
            то  цикл  продолжается  и выбирается новое число.
          if (quan == 1) { PCards[1][i].pict = Coz.pict; PCards[1][i].num = Coz.num; quan = 0; } -
            если  quan  равно 1,  то  в  i-ый  слот  игрока 1  загружается козырь.
          if (quan > 1) { cards[n].taken = true; PCards[1][i].pict = cards[n].pict; PCards[1][i].num = n; quan -= 1; } -
            если  quan  больше 1,  то  в  i-ый  слот  игрока 1  загружается случайная карта из  `cards`,
            и  `quan`  уменьшается на 1

**/
void givecards()
{
   boolean fl;
   int n,i,m;
   fl = false; //Заходов не было
   //ShowMessage("Набор");
   if (quan==0) goto finish;
   if (quan == 36) //Первая раздача карт
   {
     do
       n = random(36)+1;

     while (cards[n].taken == true);

     Coz.pict  = cards[n].pict; //Козырь
     Coz.num = n;
     Mcard = n % 4; //Определяем масть как остаток от деления на 4
     cards[n].taken = true;

     //ShowMessage("Козырь "+IntToStr(Mcard));
   };

   //if (Pquan[2] < 6) Pquan[2] = 6;

   if (PlayerHod == Player2)
   {
      //ShowMessage("Я набтраю");
      goto l1;

    }
    else
    {
      //ShowMessage("Он набтраю");
      goto l2;//Мы только что ходили или взяли
     };
   l1:
   if (Pquan[1] < 6)
     if (quan +Pquan[1] >= 6) Pquan[1] = 6; else Pquan[1] = Pquan[1]+ quan;
   //ShowMessage("Набираю я");
   if (fl==true) goto finish;
   for(i=1;i<=Pquan[1];i++)
   {
     /* if (quan >= 50)
     {ShowMessage("Карты закончились");
      return;
     }  */
     if (PCards[1][i].num == 0)
     {
      //ShowMessage("Загрузка");
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
   //ShowMessage("Набирает комп");
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
   FmFool->ImCon->Picture->LoadFromFile(Coz.pict); //Козырь
   FmFool->ImCol->Picture->LoadFromFile(cards[0].pict); //Колода
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
  FmFool->LQuan->Caption = "Карт в колоде: "+IntToStr(quan);
  drawCards();
 };

void initcards()
{
 //Рубашка
 cards[0].pict = InitDir+"\\images\\back.jpg"; //Оборотная сторона карты
 //Шестерки
 cards[1].pict = InitDir+"\\images\\6ch.jpg"; //Оборотная сторона карты
 cards[2].pict = InitDir+"\\images\\6bub.jpg"; //Оборотная сторона карты
 cards[3].pict = InitDir+"\\images\\6vin.jpg"; //Оборотная сторона карты
 cards[4].pict = InitDir+"\\images\\6kr.jpg"; //Оборотная сторона карты
 //семерки
 cards[5].pict = InitDir+"\\images\\7ch.jpg"; //Оборотная сторона карты
 cards[6].pict = InitDir+"\\images\\7bub.jpg"; //Оборотная сторона карты
 cards[7].pict = InitDir+"\\images\\7vin.jpg"; //Оборотная сторона карты
 cards[8].pict = InitDir+"\\images\\7kr.jpg"; //Оборотная сторона карты
 //Восьмерки
 cards[9].pict = InitDir+"\\images\\8ch.jpg"; //Оборотная сторона карты
 cards[10].pict = InitDir+"\\images\\8bub.jpg"; //Оборотная сторона карты
 cards[11].pict = InitDir+"\\images\\8vin.jpg"; //Оборотная сторона карты
 cards[12].pict = InitDir+"\\images\\8kr.jpg"; //Оборотная сторона карты
 //Девятки
 cards[13].pict = InitDir+"\\images\\9ch.jpg"; //Оборотная сторона карты
 cards[14].pict = InitDir+"\\images\\9bub.jpg"; //Оборотная сторона карты
 cards[15].pict = InitDir+"\\images\\9vin.jpg"; //Оборотная сторона карты
 cards[16].pict = InitDir+"\\images\\9kr.jpg"; //Оборотная сторона карты
 //Десятки
 cards[17].pict = InitDir+"\\images\\10ch.jpg"; //Оборотная сторона карты
 cards[18].pict = InitDir+"\\images\\10bub.jpg"; //Оборотная сторона карты
 cards[19].pict = InitDir+"\\images\\10vin.jpg"; //Оборотная сторона карты
 cards[20].pict = InitDir+"\\images\\10kr.jpg"; //Оборотная сторона карты
 //Вальты
  cards[21].pict = InitDir+"\\images\\Jch.jpg"; //Оборотная сторона карты
  cards[22].pict = InitDir+"\\images\\Jbub.jpg"; //Оборотная сторона карты
  cards[23].pict = InitDir+"\\images\\Jvin.jpg"; //Оборотная сторона карты
  cards[24].pict = InitDir+"\\images\\Jkr.jpg"; //Оборотная сторона карты
 //Дамы
  cards[25].pict = InitDir+"\\images\\Qch.jpg"; //Оборотная сторона карты
  cards[26].pict = InitDir+"\\images\\Qbub.jpg"; //Оборотная сторона карты
  cards[27].pict = InitDir+"\\images\\Qvin.jpg"; //Оборотная сторона карты
  cards[28].pict = InitDir+"\\images\\Qkr.jpg"; //Оборотная сторона карты
 //Короли
  cards[29].pict = InitDir+"\\images\\Kch.jpg"; //Оборотная сторона карты
  cards[30].pict = InitDir+"\\images\\Kbub.jpg"; //Оборотная сторона карты
  cards[31].pict = InitDir+"\\images\\Kvin.jpg"; //Оборотная сторона карты
  cards[32].pict = InitDir+"\\images\\Kkr.jpg"; //Оборотная сторона карты
 //Тузы
  cards[33].pict = InitDir+"\\images\\Tch.jpg"; //Оборотная сторона карты
  cards[34].pict = InitDir+"\\images\\Tbub.jpg"; //Оборотная сторона карты
  cards[35].pict = InitDir+"\\images\\Tvin.jpg"; //Оборотная сторона карты
  cards[36].pict = InitDir+"\\images\\Tkr.jpg"; //Оборотная сторона карты
 }

__fastcall TFmFool::TFmFool(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

/**
1. Проверка  на  пустую  стопку:
     if (conQuan == 0) return true;  -  если  количество  карт  на  стопке  равно  0,
       то  функция  возвращает  true (т.е.  карту  можно  сбросить).
2. Проверка  карт  игрока,  который  ходит:
     for (i = 1; i <= conQuan; i++)  -  цикл  перебирает  карты  на  стопке.
       k = PCardsCon[PlayerHod][i].num; -  в  переменную  k  загружается  номер
         карты  на  стопке  (PCardsCon  -  массив,  хранящий  информацию  о  картах  игроков).
       t = k;  -  в  переменную  t  сохраняется  исходный  номер  карты.
       while (k % 4 != 0)  -  цикл  повторяется,  пока  k  не  будет  делиться
         на  4  без  остатка  (т.е.  пока  не  будет  достигнута  масть  "черви").
         k -= 1; -  k  уменьшается  на  1.
       if (t % 4 != 0) k += 1; -  если  исходная  масть  карты  не  "черви",
         то  k  увеличивается  на  1 (чтобы  вернуть  его  к  масти  карты).
       if ((num >= k) && (num <= k + 3) && ((t % 4 != 0))) - проверяется,
         соответствует  ли  номер  сбрасываемой  карты  (num) диапазону  карт
         на  стопке  (с  мастью,  отличной  от  "червей"). Если да,
         то  функция  возвращает  true.
       if ((num >= k - 3) && (num <= k) && ((t % 4 == 0))) - проверяется,
         соответствует  ли  номер  сбрасываемой  карты  (num)  диапазону  карт
         на  стопке  (с  мастью  "черви"). Если  да, то функция  возвращает  true.
3. Проверка  карт  другого  игрока:
     int noPlayerHod = GetNoPlayerHod();  -  вызывается  функция  GetNoPlayerHod
       она  возвращает  номер  игрока,  который  не  ходит).
     for (i = 1; i <= conQuan; i++)  -  цикл  перебирает  карты  на  стопке.
       Логика  цикла  аналогична  логике  предыдущего  цикла,
       только  проверяются  карты  другого  игрока  (noPlayerHod).
4. Возвращение  false:
     return false;  -  если  сбросить  карту  нельзя
     (ни  по  правилам  сброса  карт,  ни  по  наличию  соответствующих  карт  у  игроков),
     то  функция  возвращает  false.
**/

boolean CanGiveMy(int num) //Проверка можно ли дать эту карту компу
{
 int i,k,t;
 //return true;
 if (conQuan == 0) return true;
 for(i=1;i<=conQuan;i++)
  {
    k = PCardsCon[PlayerHod][i].num; //Доходим до червей карты данного номинала
    t = k;
    while (k % 4 != 0)
      {
        k -= 1;
      }
     if (t % 4 != 0) k += 1; //На червях;
     if ((num >= k) && (num <= k+3) && ((t % 4 != 0)))
     {

     return true;
     }
     if ((num >= k-3) && (num <= k) && ((t % 4 == 0)))
     {

      return true;
     }
  }     //Проверка имеются ли такие карты у меня

  int noPlayerHod = GetNoPlayerHod();
  for(i=1;i<=conQuan;i++)
  {
    k = PCardsCon[noPlayerHod][i].num; //Доходим до червей карты данного номинала
    t = k;
    while (k % 4 != 0)
      {
        k -= 1;
      }
      if (t % 4 != 0) k += 1; //На червях;
     if ((num >= k) && (num <= k+3) && ((t % 4 != 0)))
     {
     return true;
     };

     if ((num >= k-3) && (num <= k) && ((t % 4 == 0)))
     {
     return true;
     }
  }     //Проверка имеются ли такие карты у меня
 return false;
}

/**
1. Проверка  на  победу:
     if (Pquan[playerNum] == 0)  -  если  у  игрока  с  номером
       playerNum  нет  карт  (Pquan[playerNum] == 0),
       то  выводится  сообщение  о  победе  и  функция  завершается.

2. Сдвиг  карт:
     for (j = 1; j <= Pquan[playerNum]; j++)  -
       внешний  цикл  перебирает  все  слоты  с  картами  игрока.
     for (i = 1; i <= Pquan[playerNum]; i++)  -
       внутренний  цикл  также  перебирает  все  слоты  с  картами  игрока.
       if ((PCards[playerNum][i].num == 0) && (PCards[playerNum][i + 1].num != 0))  -
         проверяется,  если  в  текущем  слоте  i  нет  карты  (PCards[playerNum][i].num == 0),
         а  в  следующем  слоте  i + 1  есть  карта  (`PCards[playerNum][i + 1].num != 0`).
          PCards[playerNum][i].num = PCards[playerNum][i + 1].num;  -
            в  текущий  слот  i  перемещается  номер  карты  из  следующего  слота  i + 1.
          PCards[playerNum][i + 1].num = 0;  -  номер  карты  в  следующем  слоте  i + 1  обнуляется.
          PCards[playerNum][i].pict = PCards[playerNum][i + 1].pict;  -
            в  текущий  слот  i  перемещается  изображение  карты  из  следующего  слота  `i + 1`.
          PCards[playerNum][i + 1].pict = "";  -  изображение  карты
            в  следующем  слоте  i + 1  обнуляется.

**/

void moving(int playerNum) //Порцедура сдвига карт
{
  int i,j;
  if (Pquan[playerNum] == 0)
  {
      ShowMessage("Победил " + PlayerName[playerNum]);
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

void downMoving(int playerNum) //Порцедура сдвига карт нижнего игрового поля
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

boolean CheckComp() //Проверка может ли комп отбиться
{int i,j;
  if (PlayerTake == true) return false;
  for(i=1;i<=conQuan;i++) //Цикл по картам на кону
    {
      if (PCardsCon[1][i].taken == false) //Если текущая карта не была уже побита
      {
        for(j=1;j<=Pquan[2];j++) //Цикл по картам компьютера
         {
           if((PCardsCon[1][i].num%4 == PCards[2][j].num%4) && (PCardsCon[1][i].num < PCards[2][j].num))
             //Можно ли отбиться без козырей
             {
               PCardsCon[2][i].num = PCards[2][j].num;//Эту карту на кон
               PCardsCon[2][i].pict = PCards[2][j].pict;
               PCards[2][j].num = 0;
               PCardsCon[1][i].taken = true;
               moving(Player2);
               Pquan[2] -= 1; //Количество карт компа уменьшается на кдиницу
               if ((Pquan[2]==0) && (quan==0))
                 {
                   FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("Победил компьютер");
                    UWin = false;
                 }
               //Надо поставить процедуру сдвига карт
               return true;
             }

         } //End Можно ли без козырей


        //Проверка можно ли отбиться козырями

        for(j=1;j<=Pquan[2];j++) //Цикл по картам компа
         {
           //Карта которую надо побить - не козырь
           if((PCardsCon[1][i].num%4 != Mcard) && (PCards[2][j].num%4==Mcard))
             //Можно отбиться козырем
             {
               PCardsCon[2][i].num = PCards[2][j].num;//Эту карту на кон
               PCardsCon[1][i].taken = true; //Текущая карта побита
               PCardsCon[2][i].pict = PCards[2][j].pict;
               PCards[2][j].num = 0;
               moving(Player2);
               Pquan[2] -= 1; //Количество карт компа уменьшается на кдиницу
               if ((Pquan[2]==0) && (quan==0))
                 {
                   FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("Победил компьютер");
                    UWin = false;
                    //return;
                 }
               return true;
             }
           //Карта которую надо побить козырь
           if((PCardsCon[1][i].num%4 == Mcard) && (PCards[2][j].num%4==Mcard) && (PCardsCon[1][i].num<PCards[2][j].num))
             //Можно отбиться козырем
             {
               PCardsCon[2][i].num = PCards[2][j].num;//Эту карту на кон
               PCardsCon[1][i].taken = true;
               PCardsCon[2][i].pict = PCards[2][j].pict;
               PCards[2][j].num = 0;
               moving(Player2);

               Pquan[2] -= 1; //Количество карт компа уменьшается на единицу
               if ((Pquan[2]==0) && (quan==0))
                 {
                   FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("Победил компьютер");
                    UWin = false;
                    //return;
                 }
               return true;
             }
         }

         //ShowMessage("Берет он!");
         PlayerTake = true; //Комп берет

         return false;

      }  //End Если текущая карта не побита

    }
   // ShowMessage("На кону все покрыто");
    PlayerTake = false; //Бито
    moving(Player2);
    return true;


 //Невозможно отбиться
};


boolean CheckMy(int num) //Проверка можем ли мы отбиться
{
int i,j;

  int noPlayerHod = GetNoPlayerHod();
  for(i=1;i<=conQuan;i++) //Цикл по картам на кону
    {
      if (PCardsCon[PlayerHod][i].taken == false) //Если текущая карта не была уже побита к этому времени
      {
         {
           if((PCardsCon[PlayerHod][i].num % 4 == PCards[noPlayerHod][num].num % 4) && (PCardsCon[PlayerHod][i].num < PCards[noPlayerHod][num].num))
             //Можно ли отбиться без козырей
             {
               PCardsCon[noPlayerHod][i].num = PCards[noPlayerHod][num].num;//Эту карту на кон
               PCardsCon[noPlayerHod][i].pict = PCards[noPlayerHod][num].pict;
               PCards[noPlayerHod][num].num = 0;
               PCards[noPlayerHod][num].pict = "";
               PCardsCon[PlayerHod][i].taken = true;
               downMoving(PlayerActive);
               Pquan[noPlayerHod] -= 1; //Количество карт уменьшается на кдиницу
               if ((Pquan[noPlayerHod]==0) && (quan==0))
                 {
                    UWin = true;
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("Наши поздравления - Вы победили");
                 }
               return true;
             }

         } //End Можно ли без козырей


        //Проверка можно ли отбиться козырями

         {
           //Карта которую надо побить - не козырь
           if((PCardsCon[PlayerHod][i].num % 4 != Mcard) && (PCards[noPlayerHod][num].num%4==Mcard))
             //Можно отбиться козырем
             {
               //ShowMessage("Можно отбиться козырем!!! "+IntToStr(Mcard)+ "    "+PCards[GetNoPlayerActive][num].num);
               PCardsCon[noPlayerHod][i].num = PCards[noPlayerHod][num].num;//Эту карту на кон
               PCardsCon[PlayerHod][i].taken = true; //Текущая карта побита
               PCardsCon[noPlayerHod][i].pict = PCards[noPlayerHod][num].pict;
               PCards[noPlayerHod][num].num = 0;
               PCards[noPlayerHod][num].pict = "";
               downMoving(PlayerActive);
               Pquan[noPlayerHod] -= 1; //Количество карт компа уменьшается на кдиницу
                if ((Pquan[noPlayerHod]==0) && (quan==0))
                 {
                    UWin = true;
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("Наши поздравления - Вы победили");
                 }
               return true;
             };
           //Карта которую надо побить козырь
           if((PCardsCon[PlayerHod][i].num % 4 == Mcard) && (PCards[noPlayerHod][num].num % 4==Mcard) && (PCardsCon[PlayerHod][i].num < PCards[noPlayerHod][num].num))
             //Можно отбиться козырем
             {
               PCardsCon[noPlayerHod][i].num = PCards[noPlayerHod][j].num;//Эту карту на кон
               PCardsCon[PlayerHod][i].taken = true;
               PCardsCon[noPlayerHod][i].pict = PCards[noPlayerHod][j].pict;
               PCards[noPlayerHod][num].num = 0;
               PCards[noPlayerHod][num].pict = "";
               downMoving(PlayerActive); //Процедура сдвига карт

               Pquan[noPlayerHod] -= 1; //Количество карт компа уменьшается на единицу
                if ((Pquan[noPlayerHod]==0) && (quan==0))
                 {
                    UWin = true;
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("Наши поздравления - Вы победили");
                 }
               return true;
             }
         }

      }  //End Если текущая карта не побита

    }

    return false;



}



boolean CheckKoz() //Проверка все ли карты у компа козыри
{int i;
 for(i=1;i<=Pquan[2];i++)
   {
     if (PCards[2][i].num % 4 != Mcard) return false; //Есть некозырные карты
   }
 return true; //Все козыри
}


boolean CanGive(int num) //Проверка может ли комп дать данную карту (текущую)
{
 int i,k,t;
 if (conQuan == 0) return true;
 for(i=1;i<=conQuan;i++)
  {
    k = PCardsCon[1][i].num; //Доходим до червей карты данного номинала
    t = k;
    while (k % 4 != 0)
      {
        k -= 1;
      }
      if (t % 4 != 0) k += 1; //На червях;
     if ((num >= k) && (num <= k+3) && ((t % 4 != 0))) return true;
     if ((num >= k-3) && (num <= k) && ((t % 4 == 0))) return true;

  }     //Проверка имеются ли такие карты как на кону у нас


  for(i=1;i<=conQuan;i++)
  {
    k = PCardsCon[2][i].num; //Доходим до червей карты данного номинала
    t = k;
    while (k % 4 != 0)
      {
        k -= 1;
      }
     if (t % 4 != 0) k += 1; //На червях;
     if ((num >= k) && (num <= k+3) && ((t % 4 != 0))) return true;
     if ((num >= k-3) && (num <= k) && ((t % 4 == 0))) return true;

  }     //Проверка имеются ли такие карты как на кону у компа
 return false;
}


void HodComp()
{int i;
  if (PlayerHod == Player1)  //Компьютер отбивается
    {
      if ((Pquan[1] == 0)  && (quan == 0))
       {
         ShowMessage("Наши поздравления - вы победили");
         UWin = true;
         return;

       }
      if (CheckComp() == true)
        {
          drawCards();//Прорисовка кона
          FmFool->ButOper->Caption = "Бито";

        }
      else //Комп не отбивается
      {

         FmFool->ButOper->Caption = "Отдать";
         drawCards();//Прорисовка кона
      }
    }
  else   //Компьютер ходит
  {

      //ShowMessage("Он ходит");
      FmFool->ButOper->Caption = "Взять";
      boolean hod;
      hod = false; //Нечего дать
      if (conQuan < 6)
      {
      //int min,num,i;
      AnsiString pict;
      if (CheckKoz() == false)//Если есть некозырные карты, то с них заход
        {

          for(i=1;i<=Pquan[2];i++) //выбор карты, кот. комп будет ложить
            {
              if ((CanGive(PCards[2][i].num)== true) && (PCards[2][i].num % 4 != Mcard)) //Может ли он дать текущую карту
                {
                  conQuan += 1;
                  //ShowMessage("bla bla "+IntToStr(conQuan));
                  PCardsCon[2][conQuan].num = PCards[2][i].num;
                  PCardsCon[2][conQuan].pict = PCards[2][i].pict;
                  //ShowMessage(IntToStr(conQuan)+"  "+ PCardsCon[2][conQuan].pict);
                  PCards[2][i].num = 0;
                  PCards[2][i].pict = "";
                  moving(Player2); //Сдвиг карт
                  drawCards(); //Перерисовка поля
                  hod = true;
                  Pquan[2] -= 1;
                  if ((Pquan[2] ==0) && (quan == 0))
                  {
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("Победил компьютер");
                    UWin = false;
                    return;
                  }
                  return;
                }
            }


        }
     if (CheckKoz() == true)//Если все козырные карты
        {
          for(i=1;i<=Pquan[2];i++) //выбор карты, кот комп будет ложить
            {
              if (CanGive(PCards[2][i].num)==true ) //Эту карту можно положить
                {
                  conQuan += 1;

                  PCardsCon[2][conQuan].num = PCards[2][i].num;
                  PCardsCon[2][conQuan].pict = PCards[2][i].pict;
                  PCards[2][i].num = 0;
                  PCards[2][i].pict = "";
                  moving(Player2); //Сдвиг карт
                  drawCards(); //Перерисовка поля
                  hod = true;
                  Pquan[2] -= 1;
                   if ((Pquan[2] <=0) && (quan == 0))
                  {
                    FmFool->ButOper ->Enabled = false;
                    FmFool->Button1 ->Enabled = true;
                    ShowMessage("Победил компьютер");
                    UWin = false;
                    return;
                  }
                  return;
              
                }
            }


        } //End Если все козыри

         //for(i=1;i<=Pquan[2];i++)
         if (hod == false) //Если нету больше карт, кот. можно дать
         {
           //ShowMessage("Бито от компа 1");
           FmFool->LPrompt->Caption = "Ваш ход";
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
          FmFool->ButOper->Caption = "Бито";
          PlayerHod = Player1;
          givecards();
             //Наш ход теперь
         } //End Если нету больше карт, кот. можно дать у компа
      } //End Если карт на кону меньше 6
     else //Все 6 карт побиты
     {
      //Бито

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
  } //End Компьютер ходит
}

void __fastcall TFmFool::FormActivate(TObject *Sender)
{int i;
 randomize();
  for (i =0;i<=36;i++)
    cards[i].taken  = FALSE;
  quan = 36; //Начальное число карт
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
  //режим игры Пользователь с Компьютером
  if (GameMode == 1)
  {
     Button1->Enabled = false;
     ButOper->Enabled = true;
     ButtonLeft->Enabled = false;
     ButtonRight->Enabled = false;
     PlayerTake = false; //По умолчанию комп не берет

     PlayerActive = Player1;
     PlayerName[Player1] = "Игрок";
     PlayerName[Player2] = "Компьютер";

     Pquan[Player1] = 6;
     Pquan[Player2] = 6;//!!! Сброс карт для компа ОСТОРОЖНО!!!
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
        LPrompt->Caption = "Отбивайтесь";
        HodComp();
     }
     else
     {
        LPrompt->Caption = "Ваш ход";
        PlayerHod = Player1;
     }
  }
  //режим игры Пользователь с Пользователем
  if (GameMode == 2)
  {
     Button1->Enabled = false;
     ButOper->Enabled = true;
     ButtonLeft->Enabled = false;
     ButtonRight->Enabled = false;

     PlayerName[Player1] = "Игрок 1";
     PlayerName[Player2] = "Игрок 2";

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
     LPrompt->Caption = PlayerName[PlayerHod] + " Ваш ход";
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
  //режим игры Пользователь с Компьютером
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
                 ShowMessage("Наши поздравления - Вы победили");
              }
              HodComp();
           }
        }
     }
     else //Мы отбиваемся
     {
        if (CheckMy(cardNum)== true)
        {
           HodComp();
           drawCards();
        }
     }
  }
  //режим игры Пользователь с Пользователем
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
                 ShowMessage(PlayerName[PlayerHod] + " Наши поздравления - Вы победили");
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
     else //Мы отбиваемся
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
  int i,cur;//cur - текущая карта на кону
  //режим игры Пользователь с Компьютером
  if(GameMode == 1)
  {
     if (PlayerHod == Player1)
     {
        LPrompt->Caption = " Ваш ход";
        //ShowMessage(IntToStr(conQuan));

        if (CheckComp() == false)  //Комп берет карты, кот. мы ему дали.
        {
           if (conQuan != 0)
           {
              //ShowMessage("Комп берет тварь!!!");
              cur = 1;
              for(i=1;i<=36;i++) //Сначала комп забирает свои карты
              {
                 if (PCards[2][i].num ==0)//Конец карт компа
                 {

                    if (PCardsCon[2][cur].num != 0) //Если на кону
                    {
                       PCards[2][i].num = PCardsCon[2][cur].num;
                       PCards[2][i].pict = PCardsCon[2][cur].pict;
                       PCardsCon[2][cur].pict = "";
                       PCardsCon[2][cur].num = 0;
                       Pquan[2] += 1;  //Увеличение числа карт компа

                       cur += 1; //Комп забирает текущую карту
                    }
                 }
              }

              cur = 1;
              for(i=1;i<=36;i++) //Потом комп забирает наши карты
              {
                 if (PCards[2][i].num ==0)//Конец карт компа
                 {

                    if (PCardsCon[1][cur].num != 0) //Если на кону
                    {
                       PCards[2][i].num = PCardsCon[1][cur].num;
                       PCardsCon[1][cur].num = 0;
                       PCards[2][i].pict = PCardsCon[1][cur].pict;
                       PCardsCon[1][cur].pict = "";
                       Pquan[2] += 1; //Увеличение числа карт компа
                       cur += 1; //Комп забирает текущую карту
                    }
                 }
              }

              drawCards();
              conQuan = 0; //Карт на кону не остается

              for(i=1;i<=6;i++)
                 PCardsCon[1][i].taken = false;

              PlayerHod = Player1;
              givecards();

              PlayerTake = false;
           }// End If conquan <> 0
        }//END Если комп берет
        else
        {
           if (conQuan != 0)
           {
              PlayerHod = Player2;   //Наш код закончен
              LPrompt->Caption = "Отбивайтесь";

              for(i=1;i<=6;i++)
              {
                 PCardsCon[1][i].taken = false;
                 PCardsCon[2][i].taken = false;
                 PCardsCon[1][i].num = 0;
                 PCardsCon[2][i].num = 0;
                 PCardsCon[1][i].pict = "";
                 PCardsCon[2][i].pict = "";
              };

              //ShowMessage("БИТО!!!");
              //Pquan[1]
              conQuan = 0; //Карт на кону не остается
              givecards(); //Раздача карт
              drawCards(); //Перерисовка поля
              HodComp();
           }//End if conQuan != 0
        }

     } //End Если мы ходим
     else //Мы берем
     {
        //Забираем карты
        if (conQuan != 0)
        {
           //ShowMessage("Я беру!!!");
           cur = 1;
           for(i=1;i<=36;i++) //Сначала я забираю его карты
           {
              if (PCards[1][i].num ==0)//Конец карт
              {

                 if (PCardsCon[2][cur].num != 0) //Если на кону
                 {
                    PCards[1][i].num = PCardsCon[2][cur].num;
                    PCards[1][i].pict = PCardsCon[2][cur].pict;
                    PCardsCon[2][cur].num = 0;
                    PCardsCon[2][cur].pict = "";
                    Pquan[1] += 1;  //Увеличение числа карт мщих

                    cur += 1; //я забираю текущую карту
                 }
              }
           }

           cur = 1;
           for(i=1;i<=36;i++) //Потом  забираем наши карты
           {
              if (PCards[1][i].num ==0)//Конец карт
              {

                 if (PCardsCon[1][cur].num != 0) //Если на кону
                 {
                    PCards[1][i].num = PCardsCon[1][cur].num;
                    PCardsCon[1][cur].num = 0;
                    PCards[1][i].pict = PCardsCon[1][cur].pict;
                    PCardsCon[1][cur].pict = "";
                    Pquan[1] += 1; //Увеличение числа карт компа
                    cur += 1; //Комп забирает текущую карту
                 }
              }
           }

           drawCards();
           conQuan = 0; //Карт на кону не остается
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

  //режим игры Пользователь с Пользователем
  if(GameMode == 2)
  {
     if (PlayerHod == PlayerActive)
     {
        LPrompt->Caption = PlayerName[PlayerActive] + " Ваш ход";
        //ShowMessage(IntToStr(conQuan));

           if (conQuan != 0)
           {
              //Отдаем карты
              if (PlayerTake)
              {
                 int noPlayerHod = GetNoPlayerHod();

                 //ShowMessage("Отдаем карты!!!");
                 cur = 1;
                 for(i=1;i<=36;i++) //Сначала я забираю его карты
                 {
                    if (PCards[noPlayerHod][i].num ==0)//Конец карт
                    {

                        if (PCardsCon[PlayerHod][cur].num != 0) //Если на кону
                        {
                           PCards[noPlayerHod][i].num = PCardsCon[PlayerHod][cur].num;
                           PCards[noPlayerHod][i].pict = PCardsCon[PlayerHod][cur].pict;
                           PCardsCon[PlayerHod][cur].num = 0;
                           PCardsCon[PlayerHod][cur].pict = "";
                           Pquan[noPlayerHod] += 1;  //Увеличение числа карт мщих

                           cur += 1; //я забираю текущую карту
                        }
                    }
                 }

                 cur = 1;
                 for(i=1;i<=36;i++) //Потом  забираем наши карты
                 {
                    if (PCards[noPlayerHod][i].num ==0)//Конец карт
                    {

                        if (PCardsCon[noPlayerHod][cur].num != 0) //Если на кону
                        {
                           PCards[noPlayerHod][i].num = PCardsCon[noPlayerHod][cur].num;
                           PCardsCon[noPlayerHod][cur].num = 0;
                           PCards[noPlayerHod][i].pict = PCardsCon[noPlayerHod][cur].pict;
                           PCardsCon[noPlayerHod][cur].pict = "";
                           Pquan[noPlayerHod] += 1; //Увеличение числа карт компа
                           cur += 1; //Комп забирает текущую карту
                        }
                    }
                 }

                 conQuan = 0; //Карт на кону не остается
                 for(i=1;i<=6;i++)
                    PCardsCon[PlayerHod][i].taken = false;

                 PlayerTake = false;
                 givecards();
                 drawCards();
              }
              else
              {

                 PlayerHod = GetNoPlayerHod();   //Наш код закончен
                 PlayerActive = GetNoPlayerActive();

                 LPrompt->Caption = PlayerName[PlayerActive] + " Отбивайтесь";

                 for(i=1;i<=6;i++)
                 {
                    PCardsCon[Player1][i].taken = false;
                    PCardsCon[Player2][i].taken = false;
                    PCardsCon[Player1][i].num = 0;
                    PCardsCon[Player2][i].num = 0;
                    PCardsCon[Player1][i].pict = "";
                    PCardsCon[Player2][i].pict = "";
                 };

                 conQuan = 0; //Карт на кону не остается
                 givecards(); //Раздача карт
                 drawCards(); //Перерисовка поля

                 drawendhod();//Прорисовка окончания хода игрока

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

     } //End Если мы ходим
     else //Мы берем
     {
        int noPlayerActive = GetNoPlayerActive();

        //Забираем карты
        if (conQuan != 0)
        {
           PlayerTake = true;
           PlayerActive = noPlayerActive;
           drawCards();

           drawendhod(); //Прорисовка окончания хода игрока

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
 UWin = true; //По умолчанию ходит пользователь
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
      q = Pquan[PlayerActive] - 6; //Число не умещающихся карт
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
      q = Pquan[PlayerActive] - 6; //Число не умещающихся карт
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

