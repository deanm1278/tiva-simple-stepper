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
    
}
void stepper_disable(struct stepper *s);
void stepper_enable(struct stepper *s);
void stepper_stop(struct stepper *s);
void stepper_start(struct stepper *s);

void stepper_set_stepping_rate(struct stepper *s, uint32_t stepping_rate){
	TimerLoadSet(s->TIMER_BASE, s->TIMER, SysCtlClockGet()/stepping_rate);
	s->stepping_rate = stepping_rate;
}

void stepper_set_dir(struct stepper *s, int dir){
	s->dir = dir;
}
void stepper_move_steps(struct stepper *s, uint32_t steps);