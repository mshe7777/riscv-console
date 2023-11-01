#pragma once
#include <stdint.h>


void set_timer(uint64_t msec);
// millisecond


void handle_time_interrupt();


extern uint32_t video_flag;