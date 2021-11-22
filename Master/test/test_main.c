#include "main.h"
#include <unity.h>

void setUp(void) {
    //LED_GPIO_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}

void tearDown(void) {
    HAL_GPIO_DeInit(LD2_GPIO_Port, LD2_Pin);
}

void test_LD2_builtin_pin_number(void) {
    TEST_ASSERT_EQUAL(GPIO_PIN_5, LD2_Pin);
}

void test_LD2_state_high(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    TEST_ASSERT_EQUAL(GPIO_PIN_SET, HAL_GPIO_ReadPin(LD2_GPIO_Port, LD2_Pin));
}

void test_LD2_state_low(void) {
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
    TEST_ASSERT_EQUAL(GPIO_PIN_RESET, HAL_GPIO_ReadPin(LD2_GPIO_Port, LD2_Pin));
}

int main() {
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay
    UNITY_BEGIN();
    RUN_TEST(test_LD2_builtin_pin_number);

    for (unsigned int i = 0; i < 5; i++)
    {
        RUN_TEST(test_LD2_state_high);
        HAL_Delay(500);
        RUN_TEST(test_LD2_state_low);
        HAL_Delay(500);
    }

    UNITY_END(); // stop unit testing

    while(1){}
}

void SysTick_Handler(void) {
    HAL_IncTick();
}