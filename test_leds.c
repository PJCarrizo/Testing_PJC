/*** PRACTICO 3 - CARRIZO PABLO JESUS - CESE 15 COHORTE ***/



/*
    - Despues de reiniciar apagar todos los leds;
    - Prender un led cualquiera;
    - Apagar un led cualquiera;
    - Prender y apagar algunos leds;
    - Prender todos los leds juntos;
    - Apagar todos los leds juntos;
    - Consultar el estado de un led apagado;
    - Consultar el estado de un led encendido;
    - Revisar los valores limites de los parametros;
    - Probar valores invalidos para los parametros.
*/


#include <unity.h>
#include "leds.h"
#include "mock_errores.h" // buscar en project como se escribe los MOCK
#define LED 3
#define LED_BIT(x) (1 << (x - 1))
#define LED_LSB 1
#define LED_MSB 16



static uint16_t puerto_virtual; 
static uint16_t variable_aux;
void setUp(void){
    leds_create (&puerto_virtual);      // este llamado se ejecuta cada vez antes de cada prueba
}

/*
void teardown (){

}
*/

/*
 * Funcion inicial de Fallo de prueba *

void test_todos_los_leds_inician_apagados (void){
    TEST_FAIL_MESSAGE("Arrancamos");

}
*/

/* Despues de reiniciar apagar todos los leds */
void test_todos_los_leds_inician_apagados (void){
    uint16_t puerto_virtual = 0xFFFF;                       // se le da un valor distinto a 0x0000 para ver si existe el cmabio
    leds_create (&puerto_virtual);                          // simula la direccion del puerto led
    TEST_ASSERT_EQUAL_HEX16(0x0000,puerto_virtual);         // prueba verificando si el puerto reinicia apagado

}

/* Prender un led cualquiera */
 void test_prender_cualquier_led (void){
    // uint16_t puerto_virtual;
    // leds_create (&puerto_virtual);
    leds_on(LED);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED), puerto_virtual);
 }

 /* Apagar un led cualquiera */
 void test_apagar_cualquier_led(void){
    //uint16_t puerto_virtual; //= LED_BIT(LED);
    // leds_create (&puerto_virtual);
    leds_on(LED);
    leds_off(LED);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
 }

/* Prender y apagar algunos leds */
 void test_prender_apagar_algunos_led(void){
    leds_on(LED);
    leds_on(LED + 3);
    leds_off(LED);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED + 3), puerto_virtual);

 }
/* Prender todos los leds juntos */
void test_prender_todos_los_leds(void){
    // puerto_virtual = 0x0000; prueba en cero para ver falla
    leds_all_on(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF,puerto_virtual);    
}


/* Apagar todos los leds juntos */
void test_apagar_todos_los_leds(void){
    // puerto_virtual = 0x0000; prueba en cero para ver falla
    leds_all_off(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000,puerto_virtual);    
}


/* Consultar el estado de un led apagado */
void test_consultar_led_apagado(void){
    leds_on(LED);    
    leds_off(LED);                              // prueba con falla en caso de comentar esta linea
    variable_aux = LED;                         // variable auxiliar para enviar y trabajar con un registro
    leds_consult_off(&variable_aux);                //
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(~LED), puerto_virtual);
}


/* Consultar el estado de un led encendido */
void test_consultar_led_encendido(void){
    leds_on(LED);
    //leds_off(LED);                            // Con esta prueba falla en caso de comentar
    variable_aux = LED;                         // variable auxiliar para enviar y trabajar con un registro
    leds_consult_on(&variable_aux);                //
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED), puerto_virtual);
}

/* Revisar los valores limites de los parametros */
void test_consultar_limites_de_parametros(void){
    variable_aux = 0x8001;
    leds_on(LED_LSB);
    leds_on(LED_MSB);
    //leds_off(LED_LSB);                        // con esta linea consigo la falla
    TEST_ASSERT_EQUAL_HEX16(0x8001, puerto_virtual);
}

/* Probar valores invalidos para los parametros */
void test_error_enparametro(void){
    registrar_mensaje_Expect(0, "leds_on", 0,"Número de Led inválido");
    registrar_mensaje_IgnoreArg_linea();
    leds_on(17);
}