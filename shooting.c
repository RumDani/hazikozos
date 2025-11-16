
#include "shooting.h"
#include "segmentlcd_individual.h"
#include <sl_udelay.h>

extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

void shootingInit(void)
{
  for (int i = 0; i < SEGMENT_LCD_NUM_OF_LOWER_CHARS; i++) {
          lowerCharSegments[i].p = 0;
          lowerCharSegments[i].j = 0;
      }
}


void shootingUpdate(int hunterPos)
{
  lowerCharSegments[hunterPos].p = 1;
  lowerCharSegments[hunterPos].j = 1;
  SegmentLCD_LowerSegments (lowerCharSegments);

  sl_udelay_wait (100000);   //100ms ideig látszik a töltény

  lowerCharSegments[hunterPos].p = 0;
  lowerCharSegments[hunterPos].j = 0;
  SegmentLCD_LowerSegments (lowerCharSegments);

}
