
#include "hunter.h"
#include "segmentlcd_individual.h"
#include "caplesense.h"

static int hunterPos;
static int leosztott;
static int sliderPos;
extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];


void hunterUpdate(void)   // vadász folyamatos kijelzése a slider pozíciónak megfelelően
{
  sliderPos = CAPLESENSE_getSliderPosition ();

  // Csak akkor frissítjük, ha van aktív érintés
  if (sliderPos >= 0)
    {
      // slider pozíció számítása
      leosztott = ((sliderPos * 7) / 48);
      if (leosztott > 7)
        leosztott = 7;
      if (leosztott < 0)
        leosztott = 0;

      if (leosztott != hunterPos)
        {
          for (uint8_t p = 0; p < SEGMENT_LCD_NUM_OF_LOWER_CHARS; p++)
            {
              lowerCharSegments[p].d = 0;  // vadász szegmens törlése
            }

          lowerCharSegments[leosztott].d = 1; // új pozíció kijelzése
          hunterPos = leosztott;

          SegmentLCD_LowerSegments (lowerCharSegments);
        }
    }
}

int hunterGetPos(void)
{
  return hunterPos;
}
