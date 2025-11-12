
#include "hunter.h"
#include "segmentlcd_individual.h"
#include "caplesense.h"

static int hunterPos;
static int leosztott;
static int sliderPos;
extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

void hunterInit(void)
{
  hunterPos = -1;
  leosztott = -1;
  sliderPos = -1;
  for (int i = 0; i < SEGMENT_LCD_NUM_OF_LOWER_CHARS; i++) {
          lowerCharSegments[i].d = 0;
      }
}

void hunterUpdate(void)
{
  sliderPos = CAPLESENSE_getSliderPosition ();

  // Csak akkor frissítjük, ha van aktív érintés
  if (sliderPos >= 0)
    {
      // calculate position
      leosztott = ((sliderPos * 7) / 48);
      if (leosztott > 7)
        leosztott = 7;
      if (leosztott < 0)
        leosztott = 0;

      if (leosztott != hunterPos)
        {
          // delete segments
          for (uint8_t p = 0; p < SEGMENT_LCD_NUM_OF_LOWER_CHARS; p++)
            {
              lowerCharSegments[p].d = 0;  // vadasz torlese  csak
            }

          lowerCharSegments[leosztott].d = 1; // set segment lines belonging to slider
          hunterPos = leosztott;

          SegmentLCD_LowerSegments (lowerCharSegments);    // draw LCD
        }
    }
}

int hunterGetPos(void)
{
  return hunterPos;
}
