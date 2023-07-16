//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
#define CZAS 30
int a=1;              //indykator koloru ( do migania)
int czas;          // czas na zegarze do odliczania, w sekundach
int licznik=0;        //sprawdza ile kabli jest pzreciêtych prawid³owo
int godz, min, sek;    //przeliczanie czasu ze zmiennej czas
AnsiString godzin, minut, sekund;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void wybuch()
{                                         // przy wybuchu
     Form1->TimerZegar->Enabled=false;
     Form1->TimerWybuch->Enabled=true;
     Form1->Blue->Enabled=false;
     Form1->Red->Enabled=false;
     Form1->Green->Enabled=false;
     Form1->Napis->Caption="Oh nooo...........";
}
//---------------------------------------------------------------------------

void win()       // Przy wygranej
{
  Form1->TimerZegar->Enabled=false;
  Form1->Napis->Caption="YEA!!!!! You saved us!";
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   Zegar->Visible=false;        //znika plansza
   Bomba->Visible=false;
   Blue->Visible=false;
   Red->Visible=false;
   Green->Visible=false;
   Napis->Visible=false;

   Button1->Visible=true;       //pojawia siê strona tytu³owa
   Logo->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BlueClick(TObject *Sender)
{
     if(random(2)||licznik==2)  //przy klikniêciu 50% szans na trafienie
     {                          // je¿eli licznik 2 to 3 kabel ju¿ na pewno trafiony
        Blue->Visible=false;
        CBlue->Visible=true;  //rozciêcie
        licznik++;
        if(licznik>=3)win();
     }
     else
     {
       wybuch();
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GreenClick(TObject *Sender)
{
   if(random(2)||licznik==2)
     {
        Green->Visible=false;
        CGreen->Visible=true;
        licznik++;
        if(licznik>=3)win();
     }
     else
     {
       wybuch();
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RedClick(TObject *Sender)
{
   if(random(2)||licznik==2)
     {
        Red->Visible=false;
        CRed->Visible=true;
        licznik++;
        if(licznik>=3)win();
     }
     else
     {
       wybuch();
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerZegarTimer(TObject *Sender)
{
   godz=czas/3600;                         //rozpisanie czasu na zegarek
   godzin=IntToStr(godz);
   if(godz<10)godzin= "0" +IntToStr(godz);    //z doklejonymi z przodu nieznacz¹cymi zerami
   min=(czas-godz*3600)/60;
   minut=IntToStr(min);
   if(min<10)minut= "0" +IntToStr(min);
   sek=(czas-godz*3600-min*60);
   sekund=IntToStr(sek);
   if(sek<10)sekund= "0" +IntToStr(sek);

   Zegar->Caption=godzin+":"+minut+":"+sekund;
   czas--;             //up³yw czasu
   if(czas<0)
   {                                    //je¿eli czas ubiegnie, koniec gry
     TimerZegar->Enabled=false;
     wybuch();
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerWybuchTimer(TObject *Sender)
{
     if(a==1)
     {
    Form1->Color=clRed;          //mruganie wybuchowe
    }
     else
    Form1->Color=clBtnFace;
    a*=-1;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   Button1->Visible=false;           //usuwanie strony tytu³owej
   Logo->Visible=false;

   Zegar->Visible=true;
   Bomba->Visible=true;             // ³adowanie planszy
   Blue->Visible=true;
   Red->Visible=true;
   Green->Visible=true;
   Napis->Visible=true;
   czas=CZAS-1;
   licznik=0;                      //zegar od nowa
   randomize();
   Zegar->Caption="00:00:30";
   TimerZegar->Enabled=true;
}
//---------------------------------------------------------------------------

