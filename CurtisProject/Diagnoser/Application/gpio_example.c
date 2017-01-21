/**
 * @file    gpio_example.c
 * @author  Curtis Team
 * @brief   GPIO API use case example
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "gpio.h"
#include "debug.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void systemReset(void);
void printResults(void);
void pinsVerification(void);
void pinsSet(void);
void pinsReset(void);
void pinsPreparation(void);
void pinsDiagnoserL(void);
void pinsDiagnoserH(void);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief 	Number of GPIO to test
*/
#define GPIO_NUMBER 13

/**
 * @brief 	String to print for KO pins 
*/
#define KO "--\t"

/**
 * @brief 	String to print for OK pins 
*/
#define OK "OK\t"

/**
 * @brief 	Mask for reception of '1' 
*/
#define MASK_1_RECEPTION 0x08 //1000

/**
 * @brief 	Mask for reception of '0' 
*/
#define MASK_0_RECEPTION 0x04 //0100

/**
 * @brief 	Mask for emmission of '1' 
*/
#define MASK_1_EMMISSION 0x02 //0010

/**
 * @brief 	Mask for emmission of '0' 
*/
#define MASK_0_EMMISSION 0x01 //0001

/**
 * @brief 	Name of the pins 
*/
static const char * pin_names[GPIO_NUMBER] =    {"PA0",         "PA1",          "PA2",          "PA3",          "PA4",          "PA5",          "PA6",          "PA7",          "PA8",          "PA9",          "PA10",          "PA11",        "PA12"};

/**
 * @brief 	GPIO associated to the pins
*/
GPIO_TypeDef* GPIO_List[GPIO_NUMBER] =          {GPIOA,         GPIOA,          GPIOA,          GPIOA,          GPIOA,          GPIOA,          GPIOA,          GPIOA,          GPIOA,          GPIOA,          GPIOA,           GPIOA,          GPIOA};

/**
 * @brief 	Number of the pins
*/
    uint16_t PIN_List[GPIO_NUMBER] =            {GPIO_Pin_0,    GPIO_Pin_1,     GPIO_Pin_2,     GPIO_Pin_3,     GPIO_Pin_4,     GPIO_Pin_5,     GPIO_Pin_6,     GPIO_Pin_7,     GPIO_Pin_8,     GPIO_Pin_9,     GPIO_Pin_10,    GPIO_Pin_11,    GPIO_Pin_12};

/**
 * @brief 	Condition of the pins. Condition is coded on 4 bits (the 4 others have no interest) 
 *              '1' reception   is OK : 0xxx    is KO : 1xxx
 *              '0' reception   is OK : x0xx    is KO : x1xx
 *              '1' emmission   is OK : xx0x    is KO : xx1x
 *              '0' emmission   is OK : xxx0    is KO : xxx1
*/
uint8_t PIN_Condion[GPIO_NUMBER];

    
/**
 * @brief 	Contains the value read on each pin.
*/    
uint8_t result[GPIO_NUMBER];

/**
 * @brief   Number of pins set to '1'
*/
uint16_t total = 0;

/**
 * @brief   Number of the iteration
*/
int i = 0;

/**
 * @brief 	Print a diagnotic of the GPIO pins. The only thing you have to do is to connect together all the pins to test. 
 * @retval  None
*/
void GPIO_Diagnoser(void) {

    systemReset();

    for(i=0; i<GPIO_NUMBER; i++) {
        pinsPreparation();

        pinsReset();
        pinsVerification();
        pinsDiagnoserL();
        
        pinsSet();
        pinsVerification();
        pinsDiagnoserH();
    }

    printResults();
    
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief 	Resets the variables.  
 * @retval  None
*/
void systemReset(void) {
    int j = 0;
    for(j=0; j<GPIO_NUMBER; j++) {
        PIN_Condion[j] = 0x00;
    }
}

/**
 * @brief 	Displays yhe results in a cool format. 
 * @retval  None
*/
void printResults(void) {
    int j = 0;
    printf("PIN \tIN '1'\tIN'0'\tOUT'1'\tOUT'0'\n");
    for(j=0; j<GPIO_NUMBER; j++) {
        printf("%s\t", pin_names[j]); 
        if (PIN_Condion[j] & MASK_1_RECEPTION) printf(KO); else printf(OK);
        if (PIN_Condion[j] & MASK_0_RECEPTION) printf(KO); else printf(OK);
        if (PIN_Condion[j] & MASK_1_EMMISSION) printf(KO); else printf(OK);
        if (PIN_Condion[j] & MASK_0_EMMISSION) printf(KO); else printf(OK);
        printf("\n");
    }    
}

/**
 * @brief 	Counts the pins set to '1'
 * @retval  None
*/
void pinsVerification(void) {
    int j = 0;
    total = 0;
    for(j=0; j<GPIO_NUMBER; j++) {
        total = total + result[j];
    }
}

/**
 * @brief 	Sets one pin to '1' and reads the value on the others.
 * @retval  None
*/
void pinsSet(void) {
    int j = 0;
    GPIO_SetBits(GPIO_List[i], PIN_List[i]);
    for(j=0; j<GPIO_NUMBER; j++) {
        if (j != i) result[j] = GPIO_ReadInputDataBit(GPIO_List[j], PIN_List[j]);
        else        result[j] = 0x01;
    }
}

/**
 * @brief 	Sets one pin to '0' and reads the value on the others.
 * @retval  None
*/
void pinsReset(void) {
    int j = 0;
    GPIO_ResetBits(GPIO_List[i], PIN_List[i]);
    for(j=0; j<GPIO_NUMBER; j++) {
        if (j != i) result[j] = GPIO_ReadInputDataBit(GPIO_List[j], PIN_List[j]);
        else        result[j] = 0x00;
    }
}

/**
 * @brief 	Configures the pins as input or output.
 * @retval  None
*/
void pinsPreparation(void) {
    int j = 0;
    for(j=0; j<GPIO_NUMBER; j++) {
        if (j != i) GPIO_QuickInit(GPIO_List[j], PIN_List[j], GPIO_Mode_IN_FLOATING);
        else        GPIO_QuickInit(GPIO_List[j], PIN_List[j], GPIO_Mode_Out_PP); 
    }
}

/**
 * @brief 	Diagnoses the pins for level low ('0')
 * @retval  None
*/
void pinsDiagnoserL(void) {
    int j = 0;
    if (total < 3) {
        // Output is ok
        for(j=0; j<GPIO_NUMBER; j++) { 
            if (j != i) {
                if (result[j] == 0x00)  {/*Input is ok*/    PIN_Condion[j] = PIN_Condion[j] & (0xFF - MASK_0_RECEPTION);}
                else                    {/*Input is KO*/    PIN_Condion[j] = PIN_Condion[j] | MASK_0_RECEPTION;}
            }
            else {
                /*Output is ok*/ PIN_Condion[j] = PIN_Condion[j] & (0xFF - MASK_0_EMMISSION);
            }
        } 
    }    
    else {
        
        /*Output is KO*/ PIN_Condion[i] = PIN_Condion[i] | MASK_0_EMMISSION;
        /*Nothing can be conclued on inputs*/
    }
}

/**
 * @brief 	Diagnoses the pins for level high ('1')
 * @retval  None
*/
void pinsDiagnoserH(void) {
    int j = 0;
    if (total > GPIO_NUMBER - 3) {
    // Output is ok
        for(j=0; j<GPIO_NUMBER; j++) { 
            if (j != i) {
                if (result[j] == 0x01)  {/*Input is ok*/    PIN_Condion[j] = PIN_Condion[j] & (0xFF - MASK_1_RECEPTION);}
                else                    {/*Input is KO*/    PIN_Condion[j] = PIN_Condion[j] | MASK_1_RECEPTION;}
            }
            else {
                /*Output is ok*/ PIN_Condion[j] = PIN_Condion[j] & (0xFF - MASK_1_EMMISSION);
            }
        } 
    }    
    else {
        /*Output is KO*/ PIN_Condion[i] = PIN_Condion[i] | MASK_1_EMMISSION;
        /*Nothing can be conclued on inputs*/
    }
}
