/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                              STM32L1XX
*
* Filename : bsp_int.h
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_INT_PRESENT
#define  BSP_INT_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     EXTERNAL C LANGUAGE LINKAGE
*
* Note(s) : (1) C++ compilers MUST 'extern'ally declare ALL C function prototypes & variable/object
*               declarations for correct C language linkage.
*********************************************************************************************************
*/

#ifdef __cplusplus
extern  "C" {                                                   /* See Note #1.                                         */
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*
* Note(s) : (1) The Cortex-M "Vector Table Offset Register" section states the following:
*
*               You must align the offset to the number of exception entries in the vector table. The
*               minimum alignment is 32 words, enough for up to 16 interrupts. For more interrupts,
*               adjust the alignment by rounding up to the next power of two. For example, if you require
*               21 interrupts, the alignment must be on a 64-word boundary because the required table
*               size is 37 words, and the next power of two is 64. SEE YOUR VENDOR DOCUMENTATION FOR THE
*               ALIGNMENT DETAILS FOR YOUR DEVICE.
*********************************************************************************************************
*/

#define  ARMV7M_CORE_EXCS             16u

#define  INT_ID_MAX_NBR               57u                       /* Max. number of ext. interrupt sources. (Check MCU RM)*/

                                                                /* 73 VTOR entries; next power of 2 is 128              */
#define  INT_VTOR_TBL_SIZE         (INT_ID_MAX_NBR + ARMV7M_CORE_EXCS)
#define  INT_VTOR_TBL_ALIGNMENT    (0x200uL)                    /* 128 * 4 = 512 words. See note 1                      */


/*
*********************************************************************************************************
*                                              DATA TYPES
*********************************************************************************************************
*/

                                                                /* --- STM32L1XX(CAT4, CAT5 & CAT6) Specific Intr. ---- */
typedef  enum  bsp_int_id {
    INT_ID_WWDG          = 0u,                                  /* Window WatchDog Interrupt                            */
    INT_ID_PVD           = 1u,                                  /* PVD through EXTI Line detection Interrupt            */
    INT_ID_TAMPER_STAMP  = 2u,                                  /* Tamper and TimeStamp interrupts through the EXTI line*/
    INT_ID_RTC_WKUP      = 3u,                                  /* RTC Wakeup Timer through EXTI Line Interrupt         */
    INT_ID_FLASH         = 4u,                                  /* FLASH global Interrupt                               */
    INT_ID_RCC           = 5u,                                  /* RCC global Interrupt                                 */
    INT_ID_EXTI0         = 6u,                                  /* EXTI Line0 Interrupt                                 */
    INT_ID_EXTI1         = 7u,                                  /* EXTI Line1 Interrupt                                 */
    INT_ID_EXTI2         = 8u,                                  /* EXTI Line2 Interrupt                                 */
    INT_ID_EXTI3         = 9u,                                  /* EXTI Line3 Interrupt                                 */
    INT_ID_EXTI4         = 10u,                                 /* EXTI Line4 Interrupt                                 */
    INT_ID_DMA1_Channel1 = 11u,                                 /* DMA1 Channel 1 global Interrupt                      */
    INT_ID_DMA1_Channel2 = 12u,                                 /* DMA1 Channel 2 global Interrupt                      */
    INT_ID_DMA1_Channel3 = 13u,                                 /* DMA1 Channel 3 global Interrupt                      */
    INT_ID_DMA1_Channel4 = 14u,                                 /* DMA1 Channel 4 global Interrupt                      */
    INT_ID_DMA1_Channel5 = 15u,                                 /* DMA1 Channel 5 global Interrupt                      */
    INT_ID_DMA1_Channel6 = 16u,                                 /* DMA1 Channel 6 global Interrupt                      */
    INT_ID_DMA1_Channel7 = 17u,                                 /* DMA1 Channel 7 global Interrupt                      */
    INT_ID_ADC1          = 18u,                                 /* ADC1 global Interrupt                                */
    INT_ID_USB_HP        = 19u,                                 /* USB High Priority Interrupt                          */
    INT_ID_USB_LP        = 20u,                                 /* USB Low Priority Interrupt                           */
    INT_ID_DAC           = 21u,                                 /* DAC Interrupt                                        */
    INT_ID_COMP          = 22u,                                 /* Comparator through EXTI Line Interrupt               */
    INT_ID_EXTI9_5       = 23u,                                 /* External Line[9:5] Interrupts                        */
    INT_ID_LCD           = 24u,                                 /* LCD Interrupt                                        */
    INT_ID_TIM9          = 25u,                                 /* TIM9 global Interrupt                                */
    INT_ID_TIM10         = 26u,                                 /* TIM10 global Interrupt                               */
    INT_ID_TIM11         = 27u,                                 /* TIM11 global Interrupt                               */
    INT_ID_TIM2          = 28u,                                 /* TIM2 global Interrupt                                */
    INT_ID_TIM3          = 29u,                                 /* TIM3 global Interrupt                                */
    INT_ID_TIM4          = 30u,                                 /* TIM4 global Interrupt                                */
    INT_ID_I2C1_EV       = 31u,                                 /* I2C1 Event Interrupt                                 */
    INT_ID_I2C1_ER       = 32u,                                 /* I2C1 Error Interrupt                                 */
    INT_ID_I2C2_EV       = 33u,                                 /* I2C2 Event Interrupt                                 */
    INT_ID_I2C2_ER       = 34u,                                 /* I2C2 Error Interrupt                                 */
    INT_ID_SPI1          = 35u,                                 /* SPI1 global Interrupt                                */
    INT_ID_SPI2          = 36u,                                 /* SPI2 global Interrupt                                */
    INT_ID_USART1        = 37u,                                 /* USART1 global Interrupt                              */
    INT_ID_USART2        = 38u,                                 /* USART2 global Interrupt                              */
    INT_ID_USART3        = 39u,                                 /* USART3 global Interrupt                              */
    INT_ID_EXTI15_10     = 40u,                                 /* External Line[15:10] Interrupts                      */
    INT_ID_RTC_Alarm     = 41u,                                 /* RTC Alarm through EXTI Line Interrupt                */
    INT_ID_USB_FS_WKUP   = 42u,                                 /* USB FS WakeUp from suspend through EXTI Line Intr    */
    INT_ID_TIM6          = 43u,                                 /* TIM6 global Interrupt                                */
    INT_ID_TIM7          = 44u,                                 /* TIM7 global Interrupt                                */
    INT_ID_SDIO          = 45u,                                 /* SDIO global Interrupt                                */
    INT_ID_TIM5          = 46u,                                 /* TIM5 global Interrupt                                */
    INT_ID_SPI3          = 47u,                                 /* SPI3 global Interrupt                                */
    INT_ID_UART4         = 48u,                                 /* UART4 global Interrupt                               */
    INT_ID_UART5         = 49u,                                 /* UART5 global Interrupt                               */
    INT_ID_DMA2_Channel1 = 50u,                                 /* DMA2 Channel 1 global Interrupt                      */
    INT_ID_DMA2_Channel2 = 51u,                                 /* DMA2 Channel 2 global Interrupt                      */
    INT_ID_DMA2_Channel3 = 52u,                                 /* DMA2 Channel 3 global Interrupt                      */
    INT_ID_DMA2_Channel4 = 53u,                                 /* DMA2 Channel 4 global Interrupt                      */
    INT_ID_DMA2_Channel5 = 54u,                                 /* DMA2 Channel 5 global Interrupt                      */
    INT_ID_AES           = 55u,                                 /* AES global Interrupt                                 */
    INT_ID_COMP_ACQ      = 56u                                  /* Comparator Channel Acquisition global Interrupt      */
} BSP_INT_ID;


typedef enum bsp_int_type {                                     /* Types of Interrupt.                                  */
    INT_IRQ,                                                    /* Normal interrupt request.                            */
} BSP_INT_TYPE;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  BSP_IntInit   (void);

void  BSP_IntEnable (BSP_INT_ID     int_id);

void  BSP_IntDisable(BSP_INT_ID     int_id);

void  BSP_IntClear  (BSP_INT_ID     int_id);

void  BSP_IntVectSet(BSP_INT_ID     int_id,
                     CPU_INT08U     int_prio,
                     BSP_INT_TYPE   int_type,
                     CPU_FNCT_VOID  isr_handler);


/*
*********************************************************************************************************
*                                   EXTERNAL C LANGUAGE LINKAGE END
*********************************************************************************************************
*/

#ifdef __cplusplus
}                                                               /* End of 'extern'al C lang linkage.                    */
#endif


/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
