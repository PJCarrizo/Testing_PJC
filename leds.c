#include "leds.h"
#include "errores.h"
#include <stdio.h>
#define LEDS_ALL_OFF    0x0000
#define LEDS_ALL_ON     0xFFFF
#define LEDS_OFFSET     1
#define LED_ON_STATE    1
#define TRUE            1
static uint16_t *puerto;                    // declaracion de variable global
//static uint16_t puerto_aux[];                    // declaracion de variable global
uint16_t led_to_mask (int led){
    return (LED_ON_STATE <<(led - LEDS_OFFSET));
}

void leds_create (uint16_t *direccion){
    puerto = direccion;
    *puerto = LEDS_ALL_OFF;
}

void leds_on (uint8_t led){
    //*puerto = 0x0004; //Falla
    //*puerto = 0x0024; //Falla
    //*puerto = 0x0020; //Falla
    if ((led >= 1) && (led <= 16)){
        *puerto |= led_to_mask(led);    //(1 << (led - 1));
    }else {
        registrar_mensaje(0, __FUNCTION__, __LINE__, "Número de Led inválido");
    }
    
}

void leds_off(uint8_t led){
    *puerto &= ~led_to_mask(led);//~(1 << (led - 1)); 
}

void leds_all_on(uint16_t *direccion){
    puerto = direccion;
    *puerto = LEDS_ALL_ON;      // *puerto = LEDS_ALL_OFF; con esta prueba falla
}

void leds_all_off(uint16_t *direccion){
    puerto = direccion;
    *puerto = LEDS_ALL_OFF;      // *puerto = LEDS_ALL_ON; con esta prueba falla
}

void leds_consult_on(uint16_t *led){
    uint8_t led_1 = led;
    if (*puerto == *led){//puerto_aux[led] == TRUE ){
        *puerto |= led_to_mask(led_1);
    }else{
        *puerto &= ~led_to_mask(led_1);
    }
}

void leds_consult_off(uint16_t *led){
    uint8_t led_1 = led;
    if (*puerto == *led){//puerto_aux[led] == TRUE ){
        *puerto |= led_to_mask(led_1);
    }else{
        *puerto &= ~led_to_mask(led_1);
    }
}