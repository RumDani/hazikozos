
#include "setlevel.h"
#include <stdbool.h>
#include "caplesense.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "em_gpio.h"
#include "sl_udelay.h"

extern volatile bool gomballapot;   //gomb allapotára --> megszakításhoz

static int sliderPos;   //slider pozíciójához
static int elozo_leosztott;   //a törlés miatt, hogy az e
static int utolso_ervenyes_pos; // Utolso érvényes pozicio megtarására még leosztás előtt
static int leosztott;   //slider pozicio leosztás után
static int selectedLevel;   //kiiratáshoz a leosztottal lesz egyenlő

void setLevelInit(void) //Változók kezdeti értékbe állítása / inicializálása
{
  sliderPos = -1;
  utolso_ervenyes_pos = 0;
  leosztott = 1;
  selectedLevel = 0;
  elozo_leosztott = 0;
}

int setLevelUpdate(void)
{
  sliderPos = CAPLESENSE_getSliderPosition ();    //a slider értékét itt kapjuk meg

  if (sliderPos >= 0)   // Ha van érvényes pozíció (érintés), frissítjük az utolsó érvényes értéket
    {
      utolso_ervenyes_pos = sliderPos;
    }

  leosztott = (utolso_ervenyes_pos * 8) / 48;     // Mindig az utolsó érvényes pozíciót használjuk

  //korlátozás
  if (leosztott > 8)
    leosztott = 8;
  if (leosztott < 1)
    leosztott = 1;

  if (leosztott != elozo_leosztott)   //Új érvényes leosztás esetén érték frissítése
    {
      if (leosztott > elozo_leosztott)
        {
          for (int i = elozo_leosztott; i < leosztott; i++)    // Új gyűrűk bekapcsolása
            {
              SegmentLCD_ARing (i, 1);
            }
        }
      else
        {
          for (int i = leosztott; i < elozo_leosztott; i++)   // Extra gyűrűk kikapcsolása
            {
              SegmentLCD_ARing (i, 0);
            }
        }
      elozo_leosztott = leosztott;    //Ez azért hogy a leoszást vizsgálni tudjuk, hogy változott e
    }
  return leosztott;
}

bool setLevelOk(void)   //Itt történik meg a gombnyomásra a szint beállítása és kiírása
{
  if (gomballapot)
      {
          gomballapot = false;
          selectedLevel = leosztott;    //szint eltárolása későbbi felhasználásra

          SegmentLCD_Number(selectedLevel);   //kiírjuk a választott szintet
          GPIO_PinOutSet(gpioPortE, 2);   //Led bekapcsolása gomb nyomásának visszajelzésére
          sl_udelay_wait(300000);   //kis késleltetés
          GPIO_PinOutClear(gpioPortE, 2);   //led lekapcsolása

          return true;
      }
      return false;

}

int setLevelGetVal(void)
{

  return selectedLevel;
}
