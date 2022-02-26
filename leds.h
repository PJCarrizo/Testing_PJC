#include <stdint.h>

void leds_create (uint16_t *puerto);

void leds_on (uint8_t led);

void leds_off(uint8_t led);

void leds_all_on(uint16_t *puerto);

void leds_all_off(uint16_t *puerto);

void leds_consult_on(uint16_t *puerto);

void leds_consult_off(uint16_t *puerto);