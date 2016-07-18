#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdint.h>
#include <stdbool.h>

struct stepper {
	uint32_t 			stepping_rate;	//steps per second

	uint32_t			t_val;
	int					dir;
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
};


void stepper_init(struct stepper *s);
void stepper_disable(struct stepper *s);
void stepper_enable(struct stepper *s);
void stepper_stop(struct stepper *s);
void stepper_start(struct stepper *s);
void stepper_set_stepping_rate(struct stepper *s, uint32_t stepping_rate);
void stepper_set_dir(struct stepper *s, int dir);
void stepper_move_steps(struct stepper *s, uint32_t steps);

#endif /* STEPPER_H_ */