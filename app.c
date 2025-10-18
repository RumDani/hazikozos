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

// ************************** INTERRUPT HANDLER *****************************
void GPIO_ODD_IRQHandler(void)
{
    uint32_t flags = GPIO_IntGet();
    GPIO_IntClear(flags);

    if (flags & (1 << 9))  // PB9
    {
        gomballapot = true;  // jelezzük a fő loop-nak
    }
}

// *****************************************************************************



/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
    SegmentLCD_Init(false);  //segmentlcd.c-ből a függvény --> ne használjon boostot
    CAPLESENSE_Init(false);  //Initializes the capacative sense system without LESENSE. -- false

    //void CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable)
    CMU_ClockEnable(cmuClock_GPIO, true);

    // //void GPIO_PinModeSet(GPIO_Port_TypeDef port,unsigned int pin,GPIO_Mode_TypeDef mode,unsigned int out)
    GPIO_PinModeSet(gpioPortB, 9, gpioModeInputPull, 1); //gomb init
    GPIO_PinModeSet(gpioPortE, 2, gpioModePushPull, 0);  // LED kiindulási állapot: KI

    GPIO_PinModeSet(gpioPortE, 3, gpioModePushPull, 0);

    //*******************************gomb interrupt***************************
    /*1. Fel kell konfigurálni a kérdéses perifériát, hogy kérjen megszakítást egy adott esemény bekövetkeztekor*/

    // NVIC engedélyezés NVIC_EnableIRQ --> core_cm3.h-ból
    //Az egyes NVIC IT vonalak elnevezése az efm32gg990f1024.h fájlban találhatók.
    NVIC_EnableIRQ(GPIO_ODD_IRQn); // javítva: PB9 páratlan pin, ODD IRQ

    // 3. Interrupt konfigurálása (falling edge = gombnyomás)
    /*
     * void GPIO_ExtIntConfig(GPIO_Port_TypeDef port,
                  unsigned int pin,
                  unsigned int intNo,
                  bool risingEdge,
                  bool fallingEdge,
                  bool enable)
     */ //--> em_gpio.h
    GPIO_ExtIntConfig(gpioPortB, 9, 9, false, true, true);  // PB9, falling edge, enabled

    //*************************************************************************
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
  static int sliderPos;
  static int elozo_leosztott;
  static int utolso_ervenyes_pos;
  int leosztott;

  if(starting == false){
    if(animacio_aktiv)
    {
        karakterdelaycounter++; //kesleltetes miatt

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

    //**************A KAPACITIV ERZEKELO HELYZETE***************************************
    sliderPos = -1;
    elozo_leosztott = -1;
    utolso_ervenyes_pos = 0;  // Utolso érvényes pozicio megtarására

    // get slider position
    sliderPos = CAPLESENSE_getSliderPosition();

    // Ha van érvényes pozíció (érintés), frissítjük az utolsó érvényes értéket
    if (sliderPos >= 0)
    {
        utolso_ervenyes_pos = sliderPos;
    }

    // Mindig az utolsó érvényes pozíciót használjuk

    leosztott = (utolso_ervenyes_pos * 8) / 48;

    // Korlátozás
    if (leosztott > 7) leosztott = 0;
    if (leosztott < 0) leosztott = 0;

    if (leosztott != elozo_leosztott)
    {
        if (leosztott > elozo_leosztott)
        {
            // Új gyűrűk bekapcsolása
            for(int i = elozo_leosztott+1; i <= leosztott; i++)
            {
                SegmentLCD_ARing(i, 1);
            }
        }
        else
        {
            // Extra gyűrűk kikapcsolása
            for(int i = leosztott+1; i <= elozo_leosztott; i++)
            {
                SegmentLCD_ARing(i, 0);
            }
        }
        elozo_leosztott = leosztott;
    }

    //*********************GOMB***************************************************
    //Erdemes lenne megszakítást (interruptot)!!!!!!!!!
    /*
    if (gomballapot)
    {
        gomballapot = false;  // reset flag
        GPIO_PinOutSet(gpioPortE, 2);  // LED
        SegmentLCD_Number(leosztott + 1);
    }
    */

    //**********Képernyő törlése- nehézségi szint kiiratása , felkészülni, rajt****************-//
    // Ezt az animáció résznél már nem blokkolva kellene, de megtartottam a kommenteket
    if (gomballapot)
    {
        gomballapot = false;

        SegmentLCD_Number(leosztott);
        GPIO_PinOutSet(gpioPortE, 2); // LED0 bekapcsolása

        sl_udelay_wait(1000000); // rövid vizuális jelzés

        animacio_aktiv = false;
        SegmentLCD_AllOff();
        SegmentLCD_AlphaNumberOff();

        SegmentLCD_Write("   3   ");
        sl_udelay_wait(1000000);

        SegmentLCD_AllOff();
        SegmentLCD_Write("   2   ");
        sl_udelay_wait(1000000);

        SegmentLCD_AllOff();
        SegmentLCD_Write("   1   ");
        sl_udelay_wait(1000000);

        SegmentLCD_AllOff();
        SegmentLCD_Write(" START ");
        sl_udelay_wait(1000000);
        SegmentLCD_AllOff();
        SegmentLCD_AlphaNumberOff();

        starting = true;

        GPIO_PinOutClear(gpioPortE, 2); // LED0 kikapcsolása, hogy ne maradjon bekapcsolva
    }
  }
  else if(starting)
    {

      GPIO_PinModeSet(gpioPortF, 7, gpioModeInputPull, 1);  //vadász lövéshez 1-es gomb

      //tesztelés képpen a másik led világit
      GPIO_PinOutSet(gpioPortE, 3);  // LED
      //void GPIO_PortOutClear(GPIO_Port_TypeDef port, uint32_t pins)
      //--> The LEDs are connected to pins PE2 and PE3 in an activehigh configuration. -->efm32gg-stk3700.pdf ből


      //********************************************************************//
      //*******************-Csúszka->Vadász*********************************//


      sliderPos = CAPLESENSE_getSliderPosition(); //csúszka pozíció bekérése

      leosztott = (sliderPos * 7) / 48;   // 7 alsó szegmens van ahol a vadász megjelenhet
      if (leosztott > 6) leosztott = 6;
      if (leosztott < 0) leosztott = 0;

      lowerCharSegments[leosztott].d = 1; // vadász megjelenítése

      if(GPIO_PinInGet(gpioPortF, 7) == 0)
        {
            lowerCharSegments[leosztott].p = 1;   // ha pb1 lenyomva,
            lowerCharSegments[leosztott].j = 1;   //
            SegmentLCD_LowerSegments(lowerCharSegments);
            sl_udelay_wait(100000);   //100ms ideig látszik a töltény
        }

      SegmentLCD_LowerSegments(lowerCharSegments);
      //*******************************************************************//
    }
    //*******************************************************************-//
    //*******************-Jatek kezdete*********************************-*//





  }
