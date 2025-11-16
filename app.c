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
#include "hunter.h"
#include "duck.h"
#include "shooting.h"
#include "animation.h"
#include "setlevel.h"

#include "segmentlcd_individual.h"
#include "segmentlcd.h"
#include "em_device.h"
#include "em_cmu.h"
#include <string.h>

#include <stdlib.h>   //random miatt kell

#include "caplesense.h"
#include "caplesenseconfig.h"

#include "em_gpio.h"
#include "em_cmu.h"

#include <sl_udelay.h>

#include "sl_sleeptimer.h" //kacsa miatt

#define BUTTON_PORT gpioPortF
#define BUTTON_PIN  6

//SegmentLCD_UpperCharSegments_TypeDef upperCharSegments[SEGMENT_LCD_NUM_OF_UPPER_CHARS]; //felső LCD-hez
SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS]; //alsó LCD-hez


volatile bool starting = false;     //lefutott-e a startig
volatile bool gomballapot = false;  //gomb interrupthoz
volatile bool loves = false;        //lövés interrupthoz
static int global_leosztott = 0;    //globalis nehezsegi szint valtozo
static int shotDownCount = 0;
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

void app_init (void)
{
  SegmentLCD_Init (false); //segmentlcd.c-ből a függvény --> ne használjon boostot
  CAPLESENSE_Init (false); //Initializes the capacative sense system without LESENSE. -- false
  //void CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable)
  CMU_ClockEnable (cmuClock_GPIO, true);
  GPIO_PinModeSet (gpioPortE, 2, gpioModePushPull, 0); // LED kiindulási állapot: KI
  GPIO_PinModeSet (gpioPortE, 3, gpioModePushPull, 0);
  GPIO_PinModeSet (gpioPortF, 7, gpioModeInputPull, 1); //vadász lövéshez 1-es gomb
  srand(sl_sleeptimer_get_tick_count());
  //*******************************gomb interrupt***************************
  //===========================================================================
  //// 1. PERIFÉRIA KONFIGURÁLÁSA (GPIO interrupt kérjen)
  // ===========================================================================
  //void GPIO_PinModeSet(GPIO_Port_TypeDef port,unsigned int pin,GPIO_Mode_TypeDef mode,unsigned int out)
  GPIO_PinModeSet(gpioPortB, 10, gpioModeInputPull, 1);
  //Interrupt konfigurálása (falling edge = gombnyomás)
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
  NVIC_ClearPendingIRQ (GPIO_ODD_IRQn);
  NVIC_EnableIRQ (GPIO_ODD_IRQn);
  //*************************************************************************
}

/***************************************************************************//**
 * App ticking function. -- > T időnként meghívódik
 ******************************************************************************/
static bool levelInitialized = false;
void app_process_action(void)
{
  if (!starting)
    {
      if (!levelInitialized)
        {
              setLevelInit();        // Csak egyszer inicializáljuk
              levelInitialized = true;
         }
      //setLevelInit();
      animationShowSetLevel ();
      setLevelUpdate ();

      if (setLevelOk ())
        {
          global_leosztott = setLevelGetVal();
          animationShowCountDown ();
          duckInit (global_leosztott);
          starting = true;
          levelInitialized = false;
        }
    }

  if (starting)
    {
      hunterUpdate ();
      duckUpdate ();
      duckCounter (shotDownCount);
      if (!duckIsGameOver ())
        {
          if (loves)
            {
              loves = false;
              int hunterPos = hunterGetPos ();
              shootingUpdate (hunterPos);

              if (duckIsHit (hunterPos))
                {
                  shotDownCount++;
                  duckHitAnimation (hunterPos);   // eltalált kacsa villogása

                }
            }
        }
      else
        {
          SegmentLCD_AllOff();
          SegmentLCD_AlphaNumberOff();
          starting = false;
        }
    }
}

