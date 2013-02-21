/*
 * gpio.h
 *
 *  Created on: Nov 24, 2012
 *      Author: jonathanhendrix
 */

#ifndef GPIO_H_
#define GPIO_H_


typedef enum  {
	PIN_00=0,
	PIN_01=1,
	PIN_02=2,
	PIN_03=3,
	PIN_04=4,
	PIN_05=5,
	PIN_06=6,
	PIN_07=7,
	PIN_08=8,
	PIN_09=9,
	PIN_10=10,
	PIN_11=11,
	PIN_12=12,
	PIN_13=13,
	PIN_14=14,
	PIN_15=15,
	PIN_16=16,
	PIN_17=17,
	PIN_18=18,
	PIN_19=19,
	PIN_20=20,
	PIN_21=21,
	PIN_22=22,
	PIN_23=23,
	PIN_24=24,
	PIN_25=25,
	PIN_26=26,
	PIN_27=27,
	PIN_28=28,
	PIN_29=29,
	PIN_30=30,
	PIN_31=31,
	PIN_32=32,
	PIN_33=33,
	PIN_34=34,
	PIN_35=35,
	PIN_36=36,
	PIN_37=37,
	PIN_38=38,
	PIN_39=39,
	PIN_40=40,
	PIN_41=41,
	PIN_42=42,
	PIN_43=43,
	PIN_44=44,
	PIN_45=45,
	PIN_46=46,
	PIN_47=47,
	PIN_48=48,
	PIN_49=49,
	PIN_50=50,
	PIN_51=51,
	PIN_52=52,
	PIN_53=53
} gpio_pin_t;

typedef enum  {
	INTPUT=0,
	OUTPUT=1,
	ALT0=4,
	ALT1=5,
	ALT2=6,
	ALT3=4,
	ALT4=3,
	ALT5=2,
	ALL_MASK=7
} gpio_function_t;

typedef enum {
	PIN_LOW = 0,
	PIN_HIGH = 1
} pin_level_t;


#ifdef __cplusplus
extern "C" {
#endif

void gpio_fsel(gpio_pin_t pin, gpio_function_t fun);

void gpio_set0(gpio_pin_t pin);

void gpio_clear0(gpio_pin_t pin);

void gpio_set1(gpio_pin_t pin);

void gpio_clear1(gpio_pin_t pin);

pin_level_t gpio_get_level(gpio_pin_t pin);

typedef enum {
	FALLING_EDGE_DETECT,
	RISING_EDGE_DETECT,
	TRANSITION_DETECT,
	HIGH_DETECT,
	LOW_DETECT,
	ASYNC_RISING_EDGE_DETECT,
	ASYNC_FALLING_EDGE_DETECT
} event_type_t;

void gpio_set_event_detect(gpio_pin_t pin, event_type_t event_type);

typedef enum {
	DISABLE_PULL_UP_DOWN_CTRL,
	ENABLE_PULL_DOWN_CTRL,
	ENABLE_PULL_UP_CNTRL,
	RESERVERVED_PULL_UP_DOWN_CTRL
} gppud_t;

void gpio_set_pud(gpio_pin_t pin, gppud_t);

#ifdef __cplusplus
}
#endif


#endif /* GPIO_H_ */
