#include "Proc_imagenes.h"
#include "Tracking_object.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define SENSOR_ATRIBUTE_ON      0xFFFF
#define SENSOR_ATRIBUTE_OFF     0x0000
#define SW_R                    1
#define SW_L                    2
//#define MOVE_RIGHT_ON           0xFFFF  
//#define MOVE_LEFT_ON            0xFFFF
//#define ERROR                   0x0000


//static uint16_t *variable_motor;
static uint16_t *sensor_atribute;
static int i = 0;
static uint16_t port;

static uint16_t vector_move[8] = {      // variable usada para el firo de ambos Motores PAP
    0b10001000,
    0b11001100,
    0b01000100,
    0b01100110,
    0b00100010,
    0b00110011,
    0b00010001,
    0b10011001,
};

static uint16_t vector_move_x[8] = {        // variable usada para mover PAP en eje X
    0b00001000,
    0b00001100,
    0b00000100,
    0b00000110,
    0b00000010,
    0b00000011,
    0b00000001,
    0b00001001,
};

static uint16_t vector_move_y[8] = {        // variable usada para mover PAP en eje Y
    0b10000000,
    0b11000000,
    0b01000000,
    0b01100000,
    0b00100000,
    0b00110000,
    0b00010000,
    0b10010000,
};


void init_sensor(uint16_t *variable_atribute){
    sensor_atribute = variable_atribute;    // cargo los atributos de la variable
    /*
    -----------------------------------------------------------------------------------
    ---- Parte del programa en micropython en donde seteo los atributos del sensor ----
    -----------------------------------------------------------------------------------

    import sensor, image, time

    sensor.reset()                      # Reset and initialize the sensor.
    sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
    sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
    sensor.skip_frames(time = 2000)     # Wait for settings take effect.
    clock = time.clock()                # Create a clock object to track the FPS.

    */
    *sensor_atribute = SENSOR_ATRIBUTE_ON;
}

void move_pap(uint16_t sw){
    if (sw == SW_R){
        i = 0;
        while(i < 8){
            port = vector_move[i];
            sleep (0.2);
            i ++;
        }
        *sensor_atribute = SENSOR_ATRIBUTE_ON;
    }else if (sw == SW_L){
        i = 7;
        while (i >= 0)
        {
            port = vector_move[i];
            sleep (0.2);
            i --;
        }
        *sensor_atribute = SENSOR_ATRIBUTE_ON;
    }
    else{
        *sensor_atribute = SENSOR_ATRIBUTE_OFF;
    }
}

void move_pap_coordenate (uint16_t variable_x, uint16_t coordenate_x, uint16_t variable_y, uint16_t coordenate_y){
    if (variable_x == SW_R){
        i = 0;
        while (coordenate_x != 0)
        {
            port = vector_move_x [i];
            i++;
            if (i == 8)
                i = 0;
            coordenate_x --;
        }
    }
    if (variable_x == SW_L){
        i = 7;
        while (coordenate_x != 0)
        {
            port = vector_move_x [i];
            i--;
            if (i == 0)
                i = 7;
            coordenate_x --;
        }
    }
    if (variable_y == SW_R){
        i = 0;
        while (coordenate_y != 0)
        {
            port = vector_move_y [i];
            i++;
            if (i == 8)
                i = 0;
            coordenate_y --;
        }    
    }
    if (variable_y == SW_L){
        i = 7;
        while (coordenate_y != 0)
        {
            port = vector_move_y [i];
            i--;
            if (i == 0)
                i = 7;
            coordenate_y --;
        }
    }
    *sensor_atribute = SENSOR_ATRIBUTE_ON;
}
/*
void take_img(void){
    inicia
}
*/