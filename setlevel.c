
#include "setlevel.h"
#include <stdbool.h>
#include "caplesense.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "em_gpio.h"
#include "sl_udelay.h"

extern volatile bool gomballapot;

static int sliderPos;
static int elozo_leosztott;
static int utolso_ervenyes_pos; // Utolso érvényes pozicio megtarására
static int leosztott;
static int selectedLevel;
static bool ok;

void setLevelInit(void)
{
  sliderPos = -1;
  elozo_leosztott = -1;
  utolso_ervenyes_pos = 0;
  leosztott = 0;
  selectedLevel = 0;
  ok = false;
  SegmentLCD_AllOff();
}

int setLevelUpdate(void)
{
  sliderPos = CAPLESENSE_getSliderPosition ();

  // Ha van érvényes pozíció (érintés), frissítjük az utolsó érvényes értéket
  if (sliderPos >= 0)
    {
      utolso_ervenyes_pos = sliderPos;
    }

  // Mindig az utolsó érvényes pozíciót használjuk

  leosztott = (utolso_ervenyes_pos * 8) / 48;

  // Korlátozás
  if (leosztott > 8)
    leosztott = 8;
  if (leosztott < 1)
    leosztott = 1;

  if (leosztott != elozo_leosztott)
    {
      if (leosztott > elozo_leosztott)
        {
          // Új gyűrűk bekapcsolása
          for (int i = elozo_leosztott; i < leosztott; i++)
            {
              SegmentLCD_ARing (i, 1);
            }
        }
      else
        {
          // Extra gyűrűk kikapcsolása
          for (int i = leosztott; i < elozo_leosztott; i++)
            {
              SegmentLCD_ARing (i, 0);
            }
        }
      elozo_leosztott = leosztott;
    }
  return leosztott;
}
bool setLevelOk(void)
{
  if (gomballapot)
      {
          gomballapot = false;
          ok = true;
          selectedLevel = leosztott;
          /* LCD visszajelzés */
          SegmentLCD_Number(selectedLevel);
          GPIO_PinOutSet(gpioPortE, 2);
          sl_udelay_wait(300000);
          GPIO_PinOutClear(gpioPortE, 2);

          return true;
      }
      return false;

}
int setLevelGetVal(void)
{

  return selectedLevel;
}
