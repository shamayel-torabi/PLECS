/*
 * Header file for: single_phase_pll_demo/Controller
 * Generated with : PLECS 4.9.5
 *                  STM32G4x 1.4.3
 * Generated on   : 22 Nov 2025 19:39:07
 */
#ifndef PLECS_HEADER_Controller_h_
#define PLECS_HEADER_Controller_h_

#include <stdbool.h>
#include <stdint.h>

/* Model floating point type */
typedef double Controller_FloatType;

/* Model checksum */
extern const char * const Controller_checksum;

/* Model error status */
extern const char * Controller_errorStatus;


/* Model sample time */
extern const double Controller_sampleTime;


/*
 * Model states */
typedef struct
{
   double Integrator_x;             /* Controller/Single-Phase PLL/Integrator */
   double Integrator_1_x;           /* Controller/Single-Phase PLL/Phase detector/Enhanced PLL/Integrator */
   double Integrator1_x;            /* Controller/Single-Phase PLL/Continuous PID Controller/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1 */
   bool Integrator1_i1_first;       /* Controller/Single-Phase PLL/Continuous PID Controller/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1 */
   bool Integrator1_i2_prevReset;   /* Controller/Single-Phase PLL/Continuous PID Controller/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1 */
} Controller_ModelStates;
extern Controller_ModelStates Controller_X;


/* Block outputs */
typedef struct
{
   double Fcn;                      /* Controller/Single-Phase PLL/Phase detector/Enhanced PLL/Fcn */
   double Saturation;               /* Controller/Single-Phase PLL/Continuous PID Controller/Saturation/internal/Saturation Select/constant/Saturation */
   double Integrator;               /* Controller/Single-Phase PLL/Integrator */
   double Integrator_1;             /* Controller/Single-Phase PLL/Phase detector/Enhanced PLL/Integrator */
   double TrigonometricFunction1;   /* Controller/Single-Phase PLL/Phase detector/Enhanced PLL/Trigonometric Function1 */
   double Sum;                      /* Controller/Single-Phase PLL/Phase detector/Enhanced PLL/Sum */
   double Product;                  /* Controller/Single-Phase PLL/Phase detector/Enhanced PLL/Product */
   double Integrator1;              /* Controller/Single-Phase PLL/Continuous PID Controller/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1 */
   double Sum_1;                    /* Controller/Single-Phase PLL/Continuous PID Controller/Continous Time/Sum */
} Controller_BlockOutputs;
extern Controller_BlockOutputs Controller_B;

/* Entry point functions */
void Controller_initialize(void);
void Controller_step(void);
void Controller_terminate(void);

#endif /* PLECS_HEADER_Controller_h_ */
