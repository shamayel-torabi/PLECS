/*
 * Implementation file for: single_phase_pll_demo/Controller
 * Generated with         : PLECS 4.9.5
 *                          STM32G4x 1.4.3
 * Generated on           : 22 Nov 2025 19:39:07
 */
#include "Controller.h"
#ifndef PLECS_HEADER_Controller_h_
#error The wrong header file "Controller.h" was included. Please check your
#error include path to see whether this file name conflicts with the name
#error of another header file.
#endif /* PLECS_HEADER_Controller_h_ */
#if defined(__GNUC__) && (__GNUC__ > 4)
#   define _ALIGNMENT 16
#   define _RESTRICT __restrict
#   define _ALIGN __attribute__((aligned(_ALIGNMENT)))
#   if defined(__clang__)
#      if __has_builtin(__builtin_assume_aligned)
#         define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#      else
#         define _ASSUME_ALIGNED(a) a
#      endif
#   else
#      define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#   endif
#else
#   ifndef _RESTRICT
#      define _RESTRICT
#   endif
#   ifndef _ALIGN
#      define _ALIGN
#   endif
#   ifndef _ASSUME_ALIGNED
#      define _ASSUME_ALIGNED(a) a
#   endif
#endif
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "plx_hal.h"
#define PLECSRunTimeError(msg) Controller_errorStatus = msg
#define Controller_UNCONNECTED 0
static double Controller_deriv[3] _ALIGN;
static uint32_t Controller_tickLo;
static int32_t Controller_tickHi;
Controller_BlockOutputs Controller_B;
Controller_ModelStates Controller_X _ALIGN;
const char * Controller_errorStatus;
const double Controller_sampleTime = 0.00100000000000000002;
const char * const Controller_checksum =
   "28eb051a08b27bf4462b8c1fc2f3e55ae8f58b2b";
/* Target declarations */
extern void Controller_initHal();

void Controller_initialize(void)
{
   Controller_tickHi = 0;
   Controller_tickLo = 0;
   memset(&Controller_X, 0, sizeof(Controller_X));

   /* Target pre-initialization */
   Controller_initHal();


   /* Initialization for Integrator : 'Controller/Single-Phase PLL/Integrator' */
   Controller_X.Integrator_x = 0.;

   /* Initialization for Integrator : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Integrator' */
   Controller_X.Integrator_1_x = 1.;

   /* Initialization for Integrator : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1' */
   Controller_X.Integrator1_x = 0;
   Controller_X.Integrator1_i1_first = 1;
   Controller_X.Integrator1_i2_prevReset = 0.;
}

void Controller_step(void)
{
   if (Controller_errorStatus)
   {
      return;
   }

   /* Integrator : 'Controller/Single-Phase PLL/Integrator' */
   if (Controller_X.Integrator_x > 6.28318530717958623 ||
       Controller_X.Integrator_x < 0.)
   {
      double span = 6.28318530717958623 - (0.);
      Controller_X.Integrator_x -= 0.;
      Controller_X.Integrator_x = Controller_X.Integrator_x - span*floor(
                                                                         Controller_X.Integrator_x/
                                                                         span)
                                  + (0.);
   }
   Controller_B.Integrator = Controller_X.Integrator_x;
   /* DAC : 'Controller/DAC' */
   PLXHAL_DAC_setChannelOut(0, 0, Controller_B.Integrator, 0.000000,
                            6.600000);

   /* Integrator : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Integrator' */
   Controller_B.Integrator_1 = Controller_X.Integrator_1_x;

   /* Trigonometric Function : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Trigonometric\nFunction1' */
   Controller_B.TrigonometricFunction1 = sin(Controller_B.Integrator);

   /* Sum : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Sum'
    * incorporates
    *  Analog In : 'Controller/Analog In'
    *  Product : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Product2'
    */
   Controller_B.Sum =
      (PLXHAL_ADC_getRegIn(0,
                           0)) -
      (Controller_B.Integrator_1 * Controller_B.TrigonometricFunction1);

   /* Function : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Fcn' */
   {
      double u, y;
      y = Controller_B.Integrator_1;
      u = 0.000100000000000000005;
      if (u > y)
         y = u;
      Controller_B.Fcn = y;
   }

   /* Product : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Product'
    * incorporates
    *  Function : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Fcn'
    *  Trigonometric Function : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Trigonometric\nFunction'
    */
   Controller_B.Product = (Controller_B.Sum / Controller_B.Fcn) * cos(
                                                                      Controller_B.Integrator);

   /* Integrator : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1' */
   if (Controller_X.Integrator1_i1_first ||
       (!Controller_X.Integrator1_i2_prevReset && 0.))
   {
      Controller_X.Integrator1_x = 314.159265358979326;
   }
   Controller_B.Integrator1 = Controller_X.Integrator1_x;

   /* Sum : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Sum'
    * incorporates
    *  Product : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Product'
    *  Constant : 'Controller/Single-Phase PLL/Continuous PID\nController/Source Select/internal/Constant'
    *  Product : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Product3'
    *  Sum : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Sum1'
    *  Product : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Product2'
    *  Constant : 'Controller/Single-Phase PLL/Continuous PID\nController/Source Select/internal/Constant2'
    *  Constant : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Kd Integrator/Kd = 0/Constant'
    *  Constant : 'Controller/Single-Phase PLL/Continuous PID\nController/Source Select/internal/Constant3'
    */
   Controller_B.Sum_1 =
      (Controller_B.Product *
       153.333333333333314) +
      (((Controller_B.Product * 0.) - 0.) * 0.) + Controller_B.Integrator1;

   /* Saturation : 'Controller/Single-Phase PLL/Continuous PID\nController/Saturation/internal/Saturation Select/constant/Saturation' */
   Controller_B.Saturation = Controller_B.Sum_1;
   if (Controller_B.Saturation < 125.663706143591739)
   {
      Controller_B.Saturation = 125.663706143591739;
   }
   if (Controller_errorStatus)
   {
      return;
   }

   /* Update for Integrator : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1'
    * incorporates
    *  Constant : 'Controller/Single-Phase PLL/Continuous PID\nController/Reset select/None/Constant'
    */
   Controller_X.Integrator1_i1_first = 0;
   Controller_X.Integrator1_i2_prevReset = !!(0.);

   /* Derivatives for Integrator : 'Controller/Single-Phase PLL/Integrator' */
   Controller_deriv[2] = Controller_B.Saturation;

   /* Derivatives for Integrator : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Integrator'
    * incorporates
    *  Gain : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Gain'
    *  Product : 'Controller/Single-Phase PLL/Phase\ndetector/Enhanced PLL/Product1'
    */
   Controller_deriv[0] = 153.333333333333314*
                         (Controller_B.Sum *
                          Controller_B.TrigonometricFunction1);

   /* Derivatives for Integrator : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1'
    * incorporates
    *  Sum : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Sum3'
    *  Product : 'Controller/Single-Phase PLL/Continuous PID\nController/Continous Time/Product1'
    *  Constant : 'Controller/Single-Phase PLL/Continuous PID\nController/Source Select/internal/Constant1'
    *  Constant : 'Controller/Single-Phase PLL/Continuous PID\nController/Anti-windup\nmethod/Back-Calculation/Constant'
    *  Product : 'Controller/Single-Phase PLL/Continuous PID\nController/Anti-windup\nmethod/Back-Calculation/Product'
    *  Sum : 'Controller/Single-Phase PLL/Continuous PID\nController/Anti-windup\nmethod/Back-Calculation/Sum'
    *  Constant : 'Controller/Single-Phase PLL/Continuous PID\nController/Source Select/internal/Anti-windup\nmethod/Back-Calculation/Constant'
    */
   Controller_deriv[1] =
      (Controller_B.Product * 11755.5555555555566 *
       1.) +
      ((-Controller_B.Sum_1 + Controller_B.Saturation) * 76.6666666666666856);

   /* Update continuous states */
   Controller_X.Integrator_x += 0.00100000000000000002*Controller_deriv[2];
   Controller_X.Integrator_1_x += 0.00100000000000000002*Controller_deriv[0];
   Controller_X.Integrator1_x += 0.00100000000000000002*Controller_deriv[1];
}

void Controller_terminate(void)
{
}
