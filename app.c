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
#include <string.h>

#include "caplesense.h"
#include "caplesenseconfig.h"

#include "em_gpio.h"
#include "em_cmu.h"

#include <sl_udelay.h>

#define BUTTON_PORT gpioPortF
#define BUTTON_PIN  6

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

  CAPLESENSE_Init(false); //Initializes the capacative sense system without LESENSE. -- false

  //void CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable)
  CMU_ClockEnable(cmuClock_GPIO, true);

  // //void GPIO_PinModeSet(GPIO_Port_TypeDef port,unsigned int pin,GPIO_Mode_TypeDef mode,unsigned int out)
  GPIO_PinModeSet(gpioPortB, 9, gpioModeInput, 1); //gomb init
  GPIO_PinModeSet(gpioPortE, 2, gpioModePushPull, 0);  // LED kiindulási állapot: KI

}

/***************************************************************************//**
 * App ticking function. -- > T időnként meghívódik
 ******************************************************************************/


  //*****************************ANIMÁCIOHOZ*****************************************************-
  static const char *szoveg = "SET LEVEL";
  static char kijelzo[9] = "";
  static uint32_t start_index = 0;
  static int karakterdelaycounter =0;

  static bool animacio_aktiv = true;

  void app_process_action(void)
  {

    if(animacio_aktiv)
      {
          karakterdelaycounter++; //kesleltete4s miatt

   size_t szoveghossz = strlen(szoveg);
    if(karakterdelaycounter % 40 == 0)  //minden 40.lefutasra hajtodik vegre
    {

      for(uint8_t i = 0; i < 8; i++)
      {
        if((start_index + i) < szoveghossz)
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

    SegmentLCD_Write(kijelzo);

      }
  //************************************************************************************

  //**************A KAPACITIV ERZEKELO HELYZETE**************************************-*

    static int sliderPos = -1;
    static int elozo_leosztott = -1;
    static int utolso_ervenyes_pos = 0;  // Utolso érvényes pozicio megtarására

    // get slider position
    sliderPos = CAPLESENSE_getSliderPosition();

    // Ha van érvényes pozíció (érintés), frissítjük az utolsó érvényes értéket
    if (sliderPos > 0)
      {
        utolso_ervenyes_pos = sliderPos;
      }

    // Mindig az utolsó érvényes pozíciót használjuk

    static int leosztott;
    leosztott = (utolso_ervenyes_pos * 8) / 64 +1;

    // Korlátozás
    if (leosztott > 7) leosztott = 7;
    if (leosztott < 0) leosztott = 0;

    if (leosztott != elozo_leosztott)
    {
        if (leosztott > elozo_leosztott)
        {
            // Új gyűrűk bekapcsolása
            for(int i = elozo_leosztott; i < leosztott; i++)
            {
                SegmentLCD_ARing(i + 1, 1);
            }
        }
        else
        {
            // Extra gyűrűk kikapcsolása
            for(int i = leosztott; i < elozo_leosztott; i++)
            {
                SegmentLCD_ARing(i + 1, 0);
            }
        }
        elozo_leosztott = leosztott;
    }

    //*********************GOMB***************************************************-//
    //Erdemes lenne megszakítást (interruptot)!!!!!!!!!

    bool gomballapot = (GPIO_PinInGet(gpioPortB, 9) == 0); // gomb állapota aktiv low

    // Led lekezelésére
    if (gomballapot)
      {
        GPIO_PinOutSet(gpioPortE, 2);  // LED be ha gomb nyomva
        SegmentLCD_Number(leosztott +1); //0-48-ig
      }
    else
      {
        GPIO_PinOutClear(gpioPortE, 2); // LED ki ha gomb nincs nyomva
      }

    //*********************************************************************************//

    //**********Képernyő törlése- nehézségi szint kiiratása , felkészülni, rajt****************-//
    if (gomballapot)
    {
        sl_udelay_wait(10000000);
        animacio_aktiv = false;
        SegmentLCD_AllOff();
        SegmentLCD_AlphaNumberOff();

        SegmentLCD_Write("   3   ");
        sl_udelay_wait(100000000);

        SegmentLCD_AllOff();
        SegmentLCD_Write("   2   ");
        sl_udelay_wait(100000000);

        SegmentLCD_AllOff();
        SegmentLCD_Write("   1   ");
        sl_udelay_wait(100000000);

        SegmentLCD_AllOff();
        SegmentLCD_Write(" START ");
        sl_udelay_wait(100000000);
        SegmentLCD_AllOff();
        SegmentLCD_AlphaNumberOff();

    }
//*******************************************************************-//
//*******************-Jatek kezdete*********************************-*//

  }
