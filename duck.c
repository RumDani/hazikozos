
#include "duck.h"
#include "sl_sleeptimer.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include <stdlib.h>
#include <sl_udelay.h>

static bool kacsa_megjelenitve;
static int kacsa_pozicio;
static int kacsa_megjelenesi_ido;
static int kacsacounter;
static int idobeallitott;
static bool gameOver;
extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

void duckInit(int difficulty)
{
        //int nehezsegiszint_ido;
        //nehezsegiszint_ido = global_leosztott;
        kacsa_megjelenitve = false;
        kacsa_pozicio = -1;
        kacsa_megjelenesi_ido = 0;
        kacsacounter = 0;
        idobeallitott = 0;
        gameOver = false;

        switch (difficulty)
        {
            case 0: idobeallitott = 60000;  break;
            case 1: idobeallitott = 50000;  break;
            case 2: idobeallitott = 40000;  break;
            case 3: idobeallitott = 30000;  break;
            case 4: idobeallitott = 25000;  break;
            case 5: idobeallitott = 20000;  break;
            case 6: idobeallitott = 15000;  break;
            case 7: idobeallitott = 10000;  break;
            case 8: idobeallitott = 8000; break;
            default: idobeallitott = 70000; break;
        }

}

void duckUpdate()
{

  int jelenlegiido = sl_sleeptimer_get_tick_count ();
  if (!kacsa_megjelenitve)      // Csak egyszer fusson le, a "START" után
    {
      kacsa_pozicio = (rand () % 7); //8-el vett maradék biztositja a szamokat a szegmensnek

      lowerCharSegments[kacsa_pozicio].a = 1;
      SegmentLCD_LowerSegments (lowerCharSegments);

      kacsa_megjelenesi_ido = jelenlegiido;
      kacsa_megjelenitve = true;  // többet ne fusson ha megjelenitbe van
      kacsacounter++;
    }

  int eltelt = jelenlegiido - kacsa_megjelenesi_ido;
  if (eltelt >= idobeallitott)
    {

      lowerCharSegments[kacsa_pozicio].a = 0; //kacsa torlese csak
      SegmentLCD_LowerSegments (lowerCharSegments);

      if (kacsacounter < 25)
        {
          kacsa_pozicio = (rand () % 7);
          lowerCharSegments[kacsa_pozicio].a = 1;
          SegmentLCD_LowerSegments (lowerCharSegments);
          kacsa_megjelenesi_ido = jelenlegiido;

          kacsacounter++;
        }

      else
        {
          SegmentLCD_Write ("GAME");
          sl_udelay_wait (1000000);
          SegmentLCD_Write ("OVER");
          sl_udelay_wait (2000000);
          kacsa_megjelenitve = false;
          gameOver = true;


        }

    }
}

bool duckIsHit (int hunterPos)
{
    return kacsa_megjelenitve && (kacsa_pozicio == hunterPos);
}

bool duckIsGameOver(void)
{
    return gameOver;
}

void duckHitAnimation(int hunterPos)
{
  //3x villan találat után
  for (int i = 0; i < 3; i++)
    {
      lowerCharSegments[hunterPos].a = 0;
      SegmentLCD_LowerSegments (lowerCharSegments);
      sl_udelay_wait (100000);  // 100ms

      lowerCharSegments[hunterPos].a = 1;
      SegmentLCD_LowerSegments (lowerCharSegments);
      sl_udelay_wait (100000);  // 100ms
    }

  lowerCharSegments[hunterPos].a = 0;
  SegmentLCD_LowerSegments (lowerCharSegments);
}

void duckCounter(int shotDownCount)
{
  int score = (kacsacounter*100) + (shotDownCount%100);
  SegmentLCD_Number(score);
  SegmentLCD_Symbol(LCD_SYMBOL_COL10, true);
}
