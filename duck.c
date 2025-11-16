
#include "duck.h"
#include "sl_sleeptimer.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include <stdlib.h>
#include <sl_udelay.h>

static bool kacsa_megjelenitve;   //első kacsa külön lekezelése, mert az időt innen kezdjük számolni
static int kacsa_pozicio;   //kacsa pozicio tárolása
static int kacsa_megjelenesi_ido;   //jelenlegi időből és az eltelt időt ebben tudjuk számolni (eltelt idő - jelenlegi idő = delta t)
static int kacsacounter;    //megjelenitett kacsák száma
static int idobeallitott;   //nehezsegi szint alapjan beallitott ido tárolása
static bool gameOver;   //játé végéhez állapot/flag
extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];    //LCD alsó szegmenseinek vezérlésére

void duckInit(int difficulty)   //alapértékek beállítása / inicializálás
{
        kacsa_megjelenitve = false;
        kacsa_pozicio = -1;
        kacsa_megjelenesi_ido = 0;
        kacsacounter = 0;
        idobeallitott = 0;
        gameOver = false;

        switch (difficulty)   //nehézségi szint szerinti kacsak megjelenések időítése
        {
            case 0: idobeallitott = 70000;  break;
            case 1: idobeallitott = 65000;  break;
            case 2: idobeallitott = 60000;  break;
            case 3: idobeallitott = 55000;  break;
            case 4: idobeallitott = 50000;  break;
            case 5: idobeallitott = 45000;  break;
            case 6: idobeallitott = 40000;  break;
            case 7: idobeallitott = 35000;  break;
            case 8: idobeallitott = 30000; break;
            default: idobeallitott = 70000; break;
        }

}

void duckUpdate()   //itt frissitjuk a kacsákat random
{

  int jelenlegiido = sl_sleeptimer_get_tick_count ();   // Jelenlegi idő lekérése
  if (!kacsa_megjelenitve)      // Csak egyszer fusson le, a "START" után -->// Ha még nincs kacsa megjelenítve, akkor jelenítsünk meg egy újat
    {
      kacsa_pozicio = (rand () % 7); //7-el vett maradék biztositja a szamokat a szegmensnek 0-6

      lowerCharSegments[kacsa_pozicio].a = 1;
      SegmentLCD_LowerSegments (lowerCharSegments);   // Kacsa megjelenítése az LCD-n (a szegmens bekapcsolása)

      kacsa_megjelenesi_ido = jelenlegiido;   // Idő és állapot frissítése
      kacsa_megjelenitve = true;  // többet ne fusson ha megjelenitbe van
      kacsacounter++;   //kacsaszám növelése
    }

  int eltelt = jelenlegiido - kacsa_megjelenesi_ido;    /// Eltelt idő számítása az utolsó megjelenés óta
  if (eltelt >= idobeallitott)    // Ha letelt az idő, akkor új kacsa vagy játék vége
    {

      lowerCharSegments[kacsa_pozicio].a = 0; //regi kacsa torlese
      SegmentLCD_LowerSegments (lowerCharSegments);

      if (kacsacounter < 25)    //ha nincs meg a 25 kacsa, új kacsa lekezelése és megjelítése, az előzőekhez hasonlóan
        {
          kacsa_pozicio = (rand () % 7);
          lowerCharSegments[kacsa_pozicio].a = 1;
          SegmentLCD_LowerSegments (lowerCharSegments);
          kacsa_megjelenesi_ido = jelenlegiido;

          kacsacounter++;
        }

      else
        {
          SegmentLCD_Write ("GAME");    //Game over megjelenitése és várakozás
          sl_udelay_wait (1000000);
          SegmentLCD_Write ("OVER");
          sl_udelay_wait (2000000);
          kacsa_megjelenitve = false;
          gameOver = true;


        }

    }
}

/**
 * @brief Ellenőrzi, hogy a vadász eltalálta-e a kacsát
 * @param hunterPos A vadász pozíciója
 * @return true ha eltalálta, false egyébként
 */
bool duckIsHit (int hunterPos)
{
    return kacsa_megjelenitve && (kacsa_pozicio == hunterPos);
}

/**
 * @brief Visszaadja, hogy véget ért-e a játék
 * @return true ha véget ért, false egyébként
 */

bool duckIsGameOver(void)
{
    return gameOver;
}

/**
 * @brief Találat animációját játssza le
 * @param hunterPos A vadász pozíciója ahol talált
 */
void duckHitAnimation(int hunterPos)
{
  //3x villan találat után
  for (int i = 0; i < 3; i++)
    {
      lowerCharSegments[hunterPos].a = 0;   //kikapcsolja a szegmenst
      SegmentLCD_LowerSegments (lowerCharSegments);
      sl_udelay_wait (100000);  // 100ms

      lowerCharSegments[hunterPos].a = 1;   //bekapcsolja a szegmenst
      SegmentLCD_LowerSegments (lowerCharSegments);
      sl_udelay_wait (100000);  // 100ms
    }

  lowerCharSegments[hunterPos].a = 0;   // Végül kikapcsoljuk a szegmenst
  SegmentLCD_LowerSegments (lowerCharSegments);
}


/**
 * @brief Megjeleníti a játék pontszámát
 * @param shotDownCount Lelőtt kacsák száma
 */
void duckCounter(int shotDownCount)
{
  int score = (kacsacounter*100) + (shotDownCount%100);
  SegmentLCD_Number(score);
  SegmentLCD_Symbol(LCD_SYMBOL_COL10, true);
}
