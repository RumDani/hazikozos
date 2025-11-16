#include "animation.h"
#include "segmentlcd_individual.h"
#include <string.h>
#include <stdbool.h>
#include <sl_udelay.h>
#include "segmentlcd.h"

static const char *szoveg = "SET LEVEL";
static char kijelzo[9] = "";
static uint32_t start_index = 0;
static int karakterdelaycounter = 0;


void animationShowSetLevel(void)  // set level szöveg futtatása
{
  karakterdelaycounter++; //kesleltetes miatt

  size_t szoveghossz = strlen (szoveg);
  if (karakterdelaycounter % 40 == 0) //minden 40.lefutasra hajtodik vegre
    {
      for (uint8_t i = 0; i < 8; i++)
        {
          if ((start_index + i) < szoveghossz)
            {
              kijelzo[i] = szoveg[start_index + i];
            }
          else
            {
              kijelzo[i] = ' ';
            }
        }
      kijelzo[8] = '\0';

      start_index++;
      if (start_index >= szoveghossz)
        {
          start_index = 0;
        }

      karakterdelaycounter = 0;
    }

  SegmentLCD_Write (kijelzo);

}

void animationShowCountDown(void)   // játék kezdése előtt visszaszámlálás
{
            SegmentLCD_AllOff ();
            SegmentLCD_AlphaNumberOff ();

            SegmentLCD_Write ("   3   ");
            sl_udelay_wait (1000000);

            SegmentLCD_AllOff ();
            SegmentLCD_Write ("   2   ");
            sl_udelay_wait (1000000);

            SegmentLCD_AllOff ();
            SegmentLCD_Write ("   1   ");
            sl_udelay_wait (1000000);

            SegmentLCD_AllOff ();
            SegmentLCD_Write (" START ");
            sl_udelay_wait (1000000);
            SegmentLCD_AllOff ();
            SegmentLCD_AlphaNumberOff ();

}

