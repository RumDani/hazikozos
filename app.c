/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/


/* Header for the SegmentLCD driver extension*/
#include "segmentlcd_individual.h"
#include "segmentlcd.h"
 /* Header for device peripheral description*/
#include "em_device.h"
#include "em_cmu.h"

/*
 *      --- 0 (a) ---
 *   |              |
 *   |5 (f)         |1 (b)
 *   |              |
 *    --- 6 (g) ---
 *   |              |
 *   |4 (e)         |2 (c)
 *   |              |
 *    --- 3 (d) ---
 */
SegmentLCD_UpperCharSegments_TypeDef upperCharSegments[SEGMENT_LCD_NUM_OF_UPPER_CHARS]; //felső LCD-hez
/*
 *    --------- 0,a --------
 *
 *   |     \7,h  |8,j  /    |
 *   |5,f   \    |    /9,k  |1,b
 *   |       \   |   /      |
 *
 *    --- 6,g --   -- 10,m --
 *
 *   |      /    |    \11,n |
 *   |4,e  /13,q |12,p \    |2,c
 *   |    /      |      \   |
 *
 *    --------- 3,d --------*/

SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS]; //alsó LCD-hez

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  SegmentLCD_Init(false);  //segmentlcd.c-ből a függvény --> ne használjon boostot




}

/***************************************************************************//**
 * App ticking function. -- > T időnként meghívódik
 ******************************************************************************/
void app_process_action(void)
{
  //Le kell törölni először  szegmens-t
  for (uint8_t i = 0; i < SEGMENT_LCD_NUM_OF_LOWER_CHARS; i++)  //végigmegy az össezs szegmensen
    {
     for (uint8_t n = 0; n < 15; n++)   //ez megy végig egy szegmensen belül a-tól q-ig és raw-ra állítja -->
       {
        lowerCharSegments[i].raw = 1 << n;
     }
  }


  lowerCharSegments[/*slidernek a poziciója kell ide*/].d = 1;

    // rajzolja az alsó LCD - t
    SegmentLCD_LowerSegments(lowerCharSegments);
    //Késleltet(10);

}
