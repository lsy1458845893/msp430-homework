#pragma once
#include "msp430f5529.hpp"

namespace timer_A0 {

#include "hardware.hpp"
void(*timer_isr_handle)(void *) = 0;
void *timer_isr_data = 0;

// t = 1/freq = (count + 1) / 25MHz
// freq = 1 / ((count + 1) * 4e-8)
// count = 1e-8 s
void mode_interrupt(uint32_t count, void(*isr_handle)(void *),void *isr_data) {
  using namespace msp430f5529;
  TA0CCTL0 = CCIE;
  TA0CCR0  = (count / 40) + 1;
  TA0CTL   = TASSEL__SMCLK | MC__UP | ID__1;

  timer_isr_data = isr_data;
  timer_isr_handle = isr_handle;
}

void deinitial(void){
  TA0CTL = 0;
}

void mode_pwm(uint32_t count) {
  TA0CCR0 = (count / 40) + 1;
  TA0CTL = TASSEL__SMCLK | MC__UP | TACLR | ID__1;         // SMCLK, up mode, clear TAR
}

static volatile uint16_t* const TA0CCTLx[] = {
  &TA0CCTL0,
  &TA0CCTL1,
  &TA0CCTL2,
  &TA0CCTL3,
  &TA0CCTL4,
};

static volatile uint16_t* const TA0CCRx[] = {
  &TA0CCR0,
  &TA0CCR1,
  &TA0CCR2,
  &TA0CCR3,
  &TA0CCR4,
};

void pwm_duty(uint8_t channel, uint32_t duty) {
  if (duty) {
    *TA0CCRx[channel] = duty / 40;
    *TA0CCTLx[channel] = OUTMOD_7;
  } else *TA0CCTLx[channel] = 0;
}

void mode_capture(uint32_t count, void(*isr_handle)(void *),void *isr_data) {
  TA0CCR0 = (count / 40) + 1;
  TA0CCTL1 = CM_3 + CCIS_0 + CAP + SCS + CCIE;
  TA0CTL = TASSEL_2 + MC_2 + TAIE + ID__1; 
  timer_isr_data = isr_data;
  timer_isr_handle = isr_handle;
}

}

namespace timer_A1{
  
#include "hardware.hpp"
void(*timer_isr_handle)(void *) = 0;
void *timer_isr_data = 0;

// t = 1/freq = (count + 1) / 25MHz
// freq = 1 / ((count + 1) * 4e-8)
// count = 1e-8 s
void mode_interrupt(uint32_t count, void(*isr_handle)(void *),void *isr_data) {
  using namespace msp430f5529;
  TA1CCTL0 = CCIE;
  TA1CCR0  = (count / 40) + 1;
  TA1CTL   = TASSEL__SMCLK | MC__UP | ID__1;

  timer_isr_data = isr_data;
  timer_isr_handle = isr_handle;
}

void deinitial(void){
  TA1CTL = 0;
}

void mode_pwm(uint32_t count) {
  TA1CCR0 = (count / 40) + 1;
  TA1CTL = TASSEL__SMCLK | MC__UP | TACLR | ID__1;         // SMCLK, up mode, clear TAR
}

static volatile uint16_t* const TA1CCTLx[] = {
  &TA1CCTL0,
  &TA1CCTL1,
  &TA1CCTL2,
};

static volatile uint16_t* const TA1CCRx[] = {
  &TA1CCR0,
  &TA1CCR1,
  &TA1CCR2,
};

void pwm_duty(uint8_t channel, uint32_t duty) {
  if (duty) {
    *TA1CCRx[channel] = duty / 40;
    *TA1CCTLx[channel] = OUTMOD_7;
  } else *TA1CCTLx[channel] = 0;
}
}

extern "C" void interrupt_vector(TIMER0_A0_VECTOR) TIMER0_A0_ISR(void) {
  if (timer_A0::timer_isr_handle)timer_A0::timer_isr_handle(timer_A0::timer_isr_data);
}

extern "C" void interrupt_vector(TIMER1_A0_VECTOR) TIMER1_A0_ISR(void) {
  if (timer_A1::timer_isr_handle)timer_A1::timer_isr_handle(timer_A1::timer_isr_data);
}

