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
 * software is distributed in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "segmentlcd_individual.h"
#include "segmentlcd.h"
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

//lefutott-e a startig
volatile bool starting = false;

//gomb interrupthoz
volatile bool gomballapot = false;

//lövés interrupthoz
volatile bool loves = false;

// ************************** INTERRUPT HANDLER *****************************

void GPIO_ODD_IRQHandler (void)
{
  uint32_t flags = GPIO_IntGet ();
  GPIO_IntClear (flags);

  if (flags & (1 << 9))  // PB0 gomb
    {
      loves = true;  // jelezzük a fő loop-nak
    }
}



void GPIO_EVEN_IRQHandler (void)
{
  uint32_t flags = GPIO_IntGet ();
  GPIO_IntClear (flags);

  if (flags & (1 << 10))  // PB1 gomb
    {

       gomballapot = true;  // jelezzük a fő loop-nak
    }
}

// *****************************************************************************

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void
app_init (void)
{
  SegmentLCD_Init (false); //segmentlcd.c-ből a függvény --> ne használjon boostot
  CAPLESENSE_Init (false); //Initializes the capacative sense system without LESENSE. -- false

  //void CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable)
  CMU_ClockEnable (cmuClock_GPIO, true);

  GPIO_PinModeSet (gpioPortE, 2, gpioModePushPull, 0); // LED kiindulási állapot: KI

  GPIO_PinModeSet (gpioPortE, 3, gpioModePushPull, 0);

  //*******************************gomb interrupt***************************

  //===========================================================================
  //// 1. PERIFÉRIA KONFIGURÁLÁSA (GPIO interrupt kérjen)
  // ===========================================================================
                  //void GPIO_PinModeSet(GPIO_Port_TypeDef port,unsigned int pin,GPIO_Mode_TypeDef mode,unsigned int out)
  GPIO_PinModeSet(gpioPortB, 10, gpioModeInputPull, 1);
                  //Interrupt konfigurálása (falling edge = gombnyomás)
                  /*
                   * void GPIO_ExtIntConfig(GPIO_Port_TypeDef port,
                   unsigned int pin,
                   unsigned int intNo,
                   bool risingEdge,
                   bool fallingEdge,
                   bool enable)
                   *///--> em_gpio.h
  GPIO_ExtIntConfig(gpioPortB, 10, 10, false, true, true);  // falling edge, enable

  // Tiszta állapot indításkor
  GPIO_IntClear(1 << 10);  //<-- maszkolás
  // ===========================================================================
  //// 2. NVIC ENGEDÉLYEZÉSE
  // ===========================================================================
  // NVIC engedélyezés NVIC_EnableIRQ --> core_cm3.h-ból
  //Az egyes NVIC IT vonalak elnevezése az efm32gg990f1024.h fájlban találhatók.
  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);

  GPIO_PinModeSet(gpioPortB , 9, gpioModeInputPull, 1);
  GPIO_ExtIntConfig(gpioPortB, 9, 9, false, true, true);

  NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
  NVIC_EnableIRQ(GPIO_ODD_IRQn);

  //*************************************************************************
}

/***************************************************************************//**
 * App ticking function. -- > T időnként meghívódik
 ******************************************************************************/

//*****************************ANIMÁCIOHOZ*****************************************************-
static const char *szoveg = "SET LEVEL";
static char kijelzo[9] = "";
static uint32_t start_index = 0;
static int karakterdelaycounter = 0;

static bool animacio_aktiv = true;

void
app_process_action (void)
{
  // static int sliderPos;
  //static int elozo_leosztott;
  //static int utolso_ervenyes_pos;
  //int leosztott;

  if (starting == false)
    {
      if (animacio_aktiv)
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
      //************************************************************************************

      //**************A KAPACITIV ERZEKELO HELYZETE***************************************
      static int sliderPos = -1;
      static int elozo_leosztott = -1;
      static int utolso_ervenyes_pos = 0; // Utolso érvényes pozicio megtarására
      static int leosztott;

      // get slider position
      sliderPos = CAPLESENSE_getSliderPosition ();

      // Ha van érvényes pozíció (érintés), frissítjük az utolsó érvényes értéket
      if (sliderPos >= 0)
        {
          utolso_ervenyes_pos = sliderPos;
        }

      // Mindig az utolsó érvényes pozíciót használjuk

      leosztott = (utolso_ervenyes_pos * 8) / 48;

      // Korlátozás
      if (leosztott > 7)
        leosztott = 0;
      if (leosztott < 0)
        leosztott = 0;

      if (leosztott != elozo_leosztott)
        {
          if (leosztott > elozo_leosztott)
            {
              // Új gyűrűk bekapcsolása
              for (int i = elozo_leosztott + 1; i <= leosztott; i++)
                {
                  SegmentLCD_ARing (i, 1);
                }
            }
          else
            {
              // Extra gyűrűk kikapcsolása
              for (int i = leosztott + 1; i <= elozo_leosztott; i++)
                {
                  SegmentLCD_ARing (i, 0);
                }
            }
          elozo_leosztott = leosztott;
        }


      //**********Képernyő törlése- nehézségi szint kiiratása , felkészülni, rajt****************-//
      // Ezt az animáció résznél már nem blokkolva kellene, de megtartottam a kommenteket
      if (gomballapot)
        {
          gomballapot = false;

          SegmentLCD_Number (leosztott);
          GPIO_PinOutSet (gpioPortE, 2); // LED0 bekapcsolása

          sl_udelay_wait (1000000); // rövid vizuális jelzés

          animacio_aktiv = false;
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

          starting = true;

          GPIO_PinOutClear (gpioPortE, 2); // LED0 kikapcsolása, hogy ne maradjon bekapcsolva
        }
    }
  else if (starting)
    {

      //GPIO_PinModeSet (gpioPortF, 7, gpioModeInputPull, 1); //vadász lövéshez 1-es gomb

      //tesztelés képpen a másik led világit
      GPIO_PinOutSet (gpioPortE, 3);  // LED
      //void GPIO_PortOutClear(GPIO_Port_TypeDef port, uint32_t pins)
      //--> The LEDs are connected to pins PE2 and PE3 in an activehigh configuration. -->efm32gg-stk3700.pdf ből

      //********************************************************************//
      //*******************-Csúszka->Vadász*********************************//

      static int sliderPos2 = -1;
      static int leosztott2 = -1;
      static int elozoleosztott2 = -1;

      // get slider position
      sliderPos2 = CAPLESENSE_getSliderPosition ();

      // Csak akkor frissítjük, ha van aktív érintés
      if (sliderPos2 >= 0)
        {
          // calculate position
          leosztott2 = ((sliderPos2 * 7) / 48);
          if (leosztott2 > 7)
            leosztott2 = 7;
          if (leosztott2 < 0)
            leosztott2 = 0;

          if (leosztott2 != elozoleosztott2)
            {
              // delete segments
              for (uint8_t p = 0; p < SEGMENT_LCD_NUM_OF_LOWER_CHARS; p++)
                {
                  lowerCharSegments[p].raw = 0;
                }
              // set segment lines belonging to slider
              lowerCharSegments[leosztott2].d = 1;
              elozoleosztott2 = leosztott2;
              // draw LCD
              SegmentLCD_LowerSegments (lowerCharSegments);


            }



        }

      /*if(GPIO_PinInGet(gpioPortF, 7) == 0)
       {
       lowerCharSegments[leosztott2].p = 1;   // ha pb1 lenyomva,
       lowerCharSegments[leosztott2].j = 1;   //
       SegmentLCD_LowerSegments(lowerCharSegments);
       sl_udelay_wait(100000);   //100ms ideig látszik a töltény
       }*/

      if(loves)
       {
          loves=false;

          lowerCharSegments[leosztott2].p = 1;
          lowerCharSegments[leosztott2].j = 1;
          SegmentLCD_LowerSegments(lowerCharSegments);
          sl_udelay_wait(100000);   //100ms ideig látszik a töltény

          lowerCharSegments[leosztott2].p = 0;
          lowerCharSegments[leosztott2].j = 0;
          SegmentLCD_LowerSegments(lowerCharSegments);
       }

      //*******************************************************************//
    }

}
