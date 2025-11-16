
#include "shooting.h"
#include "segmentlcd_individual.h"
#include <sl_udelay.h>

extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

void shootingUpdate(int hunterPos)  // töltény kijelzése a vadász pozíciójának megfelelően
{
  lowerCharSegments[hunterPos].p = 1;
  lowerCharSegments[hunterPos].j = 1;
  SegmentLCD_LowerSegments (lowerCharSegments);

  sl_udelay_wait (100000);   //100ms ideig látszik a töltény

  lowerCharSegments[hunterPos].p = 0;
  lowerCharSegments[hunterPos].j = 0;
  SegmentLCD_LowerSegments (lowerCharSegments);

}
