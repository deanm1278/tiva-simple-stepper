#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#include "stepper.h"

static const uint8_t step_table[] = {
  0x0A,
  0x09,
  0x05,
  0x06
};

void stepper_init(struct stepper *s){
    GPIOPinTypeOutput(s->AIN1_BASE, s->AIN1_PIN);
    GPIOPinTypeOutput(s->AIN2_BASE, s->AIN2_PIN);
    GPIOPinTypeOutput(s->BIN1_BASE, s->AIN1_PIN);
    GPIOPinTypeOutput(s->BIN2_BASE, s->AIN2_PIN);
    
    s->stepping_rate = 0;
    s->stepping_rate_target = 0;
    
    s->dir = 1;
    
    s->max_start_speed = 1000;
    s->acc_max = 10000;
    
}
void stepper_disable(struct stepper *s){
    GPIOPinWrite(s->AIN1_BASE, s->AIN1_PIN, 0x00);
    GPIOPinWrite(s->AIN2_BASE, s->AIN2_PIN, 0x00);
    GPIOPinWrite(s->BIN1_BASE, s->BIN1_PIN, 0x00);
    GPIOPinWrite(s->BIN2_BASE, s->BIN2_PIN, 0x00);
}

void stepper_enable(struct stepper *s);

void stepper_tick(struct stepper *s){
    if(step_table[s->t_val] & AIN1_BIT){ GPIOPinWrite(s->AIN1_BASE, s->AIN1_PIN, s->AIN1_PIN); }
    else{ GPIOPinWrite(s->AIN1_BASE, s->AIN1_PIN, 0x00); }
    
    if(step_table[s->t_val] & AIN2_BIT){ GPIOPinWrite(s->AIN2_BASE, s->AIN2_PIN, s->AIN2_PIN); }
    else{ GPIOPinWrite(s->AIN2_BASE, s->AIN2_PIN, 0x00); }
    
    if(step_table[s->t_val] & BIN1_BIT){ GPIOPinWrite(s->BIN1_BASE, s->BIN1_PIN, s->BIN1_PIN); }
    else{ GPIOPinWrite(s->BIN1_BASE, s->BIN1_PIN, 0x00); }
    
    if(step_table[s->t_val] & BIN2_BIT){ GPIOPinWrite(s->BIN2_BASE, s->BIN2_PIN, s->BIN2_PIN); }
    else{ GPIOPinWrite(s->BIN2_BASE, s->BIN2_PIN, 0x00); }
    
    s->t_val = s->t_val + s->dir;
    if(s->t_val > 3 || s->t_val < -3)
        s->t_val = 0;
    
    stepper_set_stepping_rate(s, s->target_stepping_rate);
}

void stepper_set_stepping_rate(struct stepper *s, int target) {
    uint32_t max_delta, delta;

    if (s->stepping_rate != stepping_rate) {
        s->target_stepping_rate = stepping_rate;
        delta = abs(s->target_stepping_rate - s->stepping_rate);

        //set actual rate to the max allowed by acc rate
        max_delta = acc_max / (1 << abs(s->stepping_rate));

        delta = STEPPER_MIN(delta, max_delta);
        if (s->target_stepping_rate < s->stepping_rate)
            s->stepping_rate = s->stepping_rate - delta;
        else
            s->stepping_rate = s->stepping_rate + delta;
        
        s->dir = (s->stepping_rate < 0 ? -1 : 1);
        TimerLoadSet(s->TIMER_BASE, s->TIMER, SysCtlClockGet() / (1 << abs(s->stepping_rate)));
    }
}


void stepper_move_steps(struct stepper *s, uint32_t steps);

void stepper_set_acc_max(struct stepper *s, uint32_t acc){
    s->acc_max = acc;
}