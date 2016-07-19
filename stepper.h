#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdint.h>
#include <stdbool.h>

#define AIN1_BIT 0x08
#define AIN2_BIT 0x04
#define BIN1_BIT 0x02
#define BIN2_BIT 0x01

 #define STEPPER_MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

struct stepper {
//set these when you create the struct before calling stepper_init
        uint32_t                        AIN1_BASE;
        uint32_t                        AIN2_BASE;
        uint32_t                        BIN1_BASE;
        uint32_t                        BIN2_BASE;
        uint32_t                        AIN1_PIN;
        uint32_t                        AIN2_PIN;
        uint32_t                        BIN1_PIN;
        uint32_t                        BIN2_PIN;
	uint32_t			TIMER_BASE;
	uint32_t			TIMER;
        
//no need to mess with these, use setters and getters
        int     			stepping_rate;	//current steps per second
        int                             stepping_rate_target; //target stepping rate
        int                             dir;
        uint32_t                        pos;
	uint32_t			t_val;
        uint32_t                        acc_max;
};


void stepper_init(struct stepper *s);
void stepper_disable(struct stepper *s);
void stepper_enable(struct stepper *s);
void stepper_tick(struct stepper *s);

//set target speed in steps per second
void stepper_set_stepping_rate(struct stepper *s, int stepping_rate);
void stepper_move_steps(struct stepper *s, uint32_t steps);

//set max acceleration rate in steps per second per second
void stepper_set_acc_max(struct stepper *s, uint32_t acc);

#endif /* STEPPER_H_ */