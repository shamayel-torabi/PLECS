/*
 * Implementation file for: 3-phase-invertor-svm-02/Controller
 * Generated with         : PLECS 4.9.5
 * Generated on           : 22 Apr 2026 10:50:46
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
#define PLECSRunTimeError(msg) Controller_errorStatus = msg
#define Controller_UNCONNECTED 0
static float Controller_deriv[6] _ALIGN;
static uint32_t Controller_tickLo;
static int32_t Controller_tickHi;
Controller_ExternalInputs Controller_U;
Controller_ExternalOutputs Controller_Y;
Controller_BlockOutputs Controller_B;
Controller_ModelStates Controller_X _ALIGN;
const char * Controller_errorStatus;
const float Controller_sampleTime = 0.0001f;
const char * const Controller_checksum =
   "96360f6d82e30ad814da3b60fa765f87f64f7956";
void Controller_initialize(float time)
{
   float remainder;
   Controller_errorStatus = NULL;
   Controller_tickHi = floor(time/(4294967296.0*Controller_sampleTime));
   remainder = time - Controller_tickHi*4294967296.0*Controller_sampleTime;
   Controller_tickLo = floor(remainder/Controller_sampleTime + .5);
   remainder -= Controller_tickLo*Controller_sampleTime;
   if (fabsf(remainder) > 1e-6*fabsf(time))
   {
      Controller_errorStatus =
         "Start time must be an integer multiple of the base sample time.";
   }
   memset(&Controller_X, 0, sizeof(Controller_X));

   /* Initialization for Integrator : 'Controller/Three-Phase PLL/Integrator' */
   Controller_X.Integrator_x = 0.f;

   /* Initialization for Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF2/Continuous/Transfer Fcn' */
   Controller_X.TransferFcn[0] = 0.f;
   Controller_X.TransferFcn[1] = 0.f;

   /* Initialization for Integrator : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1' */
   Controller_X.Integrator1_x = 0;
   Controller_X.Integrator1_i1_first = 1;
   Controller_X.Integrator1_i2_prevReset = 0.f;

   /* Initialization for Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF1/Continuous/Transfer Fcn' */
   Controller_X.TransferFcn_1 = 0.f;

   /* Initialization for Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF3/Continuous/Transfer Fcn' */
   Controller_X.TransferFcn_2 = -0.00450158158f;
}

void Controller_output(void)
{
   if (Controller_errorStatus)
   {
      return;
   }

   /* Integrator : 'Controller/Three-Phase PLL/Integrator' */
   if (Controller_X.Integrator_x > 6.28318531f || Controller_X.Integrator_x <
       0.f)
   {
      float span = 6.28318531f - (0.f);
      Controller_X.Integrator_x -= 0.f;
      Controller_X.Integrator_x = Controller_X.Integrator_x - span*floorf(
                                                                          Controller_X.Integrator_x/
                                                                          span)
                                  + (0.f);
   }
   Controller_B.Integrator = Controller_X.Integrator_x;

   /* Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/3ph->SRF/beta'
    * incorporates
    *  Analog In (Triggered) : 'Controller/Vabc'
    */
   Controller_B.beta = 0.577350259f *
                       (Controller_U.Vabc_Out1[1]-Controller_U.Vabc_Out1[2]);

   /* Trigonometric Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/sin\/cos/Trigonometric\nFunction1' */
   Controller_B.TrigonometricFunction1 = cosf(Controller_B.Integrator);

   /* Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/3ph->SRF/alpha'
    * incorporates
    *  Analog In (Triggered) : 'Controller/Vabc'
    */
   Controller_B.alpha = 0.333333343f *
                        (((2.f *
                           Controller_U.Vabc_Out1[0])-
                          Controller_U.Vabc_Out1[1])-
                         Controller_U.Vabc_Out1[2]);

   /* Trigonometric Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/sin\/cos/Trigonometric\nFunction' */
   Controller_B.TrigonometricFunction = sinf(Controller_B.Integrator);

   /* Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF2/Continuous/Transfer Fcn' */
   Controller_B.TransferFcn[0] = 222.144147f*Controller_X.TransferFcn[0];
   Controller_B.TransferFcn[1] = 222.144147f*Controller_X.TransferFcn[1];

   /* Gain : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/sin\/cos/Gain1'
    * incorporates
    *  Product : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/sin\/cos/Product'
    */
   Controller_B.Gain1 = 2.f*
                        (Controller_B.TrigonometricFunction *
                         Controller_B.TrigonometricFunction1);

   /* Sum : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/sin\/cos/Sum'
    * incorporates
    *  Constant : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/sin\/cos/Constant'
    *  Gain : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/sin\/cos/Gain'
    *  Math Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/sin\/cos/Math'
    */
   Controller_B.Sum = (-1.f) +
                      (2.f*
                       (Controller_B.TrigonometricFunction1 *
     Controller_B.TrigonometricFunction1));

   /* Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Decoupling\nnetwork+1/Fcn1'
    * incorporates
    *  Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Tdq+1/αβ->q'
    */
   Controller_B.Fcn1 =
      (((Controller_B.beta *
         Controller_B.TrigonometricFunction1)-
        (Controller_B.alpha *
         Controller_B.TrigonometricFunction)) +
       (Controller_B.TransferFcn[0] *
     Controller_B.Gain1))-(Controller_B.TransferFcn[1] * Controller_B.Sum);

   /* Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Decoupling\nnetwork+1/Fcn'
    * incorporates
    *  Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Tdq+1/αβ->d'
    */
   Controller_B.Fcn =
      (((Controller_B.alpha *
         Controller_B.TrigonometricFunction1) +
        (Controller_B.beta *
         Controller_B.TrigonometricFunction))-
       (Controller_B.TransferFcn[0] *
     Controller_B.Sum))-(Controller_B.TransferFcn[1] * Controller_B.Gain1);

   /* Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Normalize' */
   {
      float u, y;
      y = sqrtf(powf(Controller_B.Fcn,2.f) + powf(Controller_B.Fcn1,2.f));
      u = 0.0001f;
      if (u > y)
         y = u;
      Controller_B.Normalize = y;
   }

   /* Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Normalize' */
   Controller_B.Normalize_i1 = Controller_B.Fcn1 / Controller_B.Normalize;

   /* Integrator : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1' */
   if (Controller_X.Integrator1_i1_first ||
       (!Controller_X.Integrator1_i2_prevReset && 0.f))
   {
      Controller_X.Integrator1_x = 314.159265f;
   }
   Controller_B.Integrator1 = Controller_X.Integrator1_x;

   /* Saturation : 'Controller/Three-Phase PLL/Continuous PID\nController/Saturation/internal/Saturation Select/constant/Saturation'
    * incorporates
    *  Sum : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Sum'
    *  Product : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Product'
    *  Constant : 'Controller/Three-Phase PLL/Continuous PID\nController/Source Select/internal/Constant'
    *  Product : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Product3'
    *  Sum : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Sum1'
    *  Product : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Product2'
    *  Constant : 'Controller/Three-Phase PLL/Continuous PID\nController/Source Select/internal/Constant2'
    *  Constant : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Kd Integrator/Kd = 0/Constant'
    *  Constant : 'Controller/Three-Phase PLL/Continuous PID\nController/Source Select/internal/Constant3'
    */
   Controller_B.Saturation =
      (Controller_B.Normalize_i1 *
       314.159265f) +
      (((Controller_B.Normalize_i1 *
         0.f) - 0.f) * 0.f) + Controller_B.Integrator1;
   /* Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF1/Continuous/Transfer Fcn' */
   Controller_B.TransferFcn_1 = 222.144147f*Controller_X.TransferFcn_1;

   /* Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF3/Continuous/Transfer Fcn' */
   Controller_B.TransferFcn_2 = 222.144147f*Controller_X.TransferFcn_2;

   /* Global output signals */
   Controller_Y.DAC = Controller_B.Integrator;

}

void Controller_update(void)
{
   if (Controller_errorStatus)
   {
      return;
   }

   /* Update for Integrator : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1'
    * incorporates
    *  Constant : 'Controller/Three-Phase PLL/Continuous PID\nController/Reset select/None/Constant'
    */
   Controller_X.Integrator1_i1_first = 0;
   Controller_X.Integrator1_i2_prevReset = !!(0.f);

   /* Derivatives for Integrator : 'Controller/Three-Phase PLL/Integrator' */
   Controller_deriv[5] = Controller_B.Saturation;

   /* Derivatives for Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF2/Continuous/Transfer Fcn'
    * incorporates
    *  Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Decoupling\nnetwork-1/Fcn'
    *  Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Tdq-1/αβ->d'
    *  Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Decoupling\nnetwork-1/Fcn1'
    *  Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/Tdq-1/αβ->q'
    */
   Controller_deriv[2] =
      ((((Controller_B.alpha *
          Controller_B.TrigonometricFunction1)-
         (Controller_B.beta *
          Controller_B.TrigonometricFunction))-
        (Controller_B.TransferFcn_1 *
         Controller_B.Sum)) +
       (Controller_B.TransferFcn_2 *
     Controller_B.Gain1))-222.144147f*Controller_X.TransferFcn[0];
   Controller_deriv[3] =
      ((((Controller_B.beta *
          Controller_B.TrigonometricFunction1) +
         (Controller_B.alpha *
          Controller_B.TrigonometricFunction))-
        (Controller_B.TransferFcn_1 *
         Controller_B.Gain1))-
       (Controller_B.TransferFcn_2 *
     Controller_B.Sum))-222.144147f*Controller_X.TransferFcn[1];

   /* Derivatives for Integrator : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1'
    * incorporates
    *  Sum : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Sum3'
    *  Product : 'Controller/Three-Phase PLL/Continuous PID\nController/Continous Time/Product1'
    *  Constant : 'Controller/Three-Phase PLL/Continuous PID\nController/Source Select/internal/Constant1'
    *  Constant : 'Controller/Three-Phase PLL/Continuous PID\nController/Anti-windup\nmethod/None/Constant'
    *  Constant : 'Controller/Three-Phase PLL/Continuous PID\nController/Anti-windup\nmethod/None/Constant1'
    */
   Controller_deriv[0] =
      (Controller_B.Normalize_i1 * 56982.1876f * 1.f) + 0.f;

   /* Derivatives for Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF1/Continuous/Transfer Fcn' */
   Controller_deriv[1] = (Controller_B.Fcn)-222.144147f*
                         Controller_X.TransferFcn_1;

   /* Derivatives for Transfer Function : 'Controller/Three-Phase PLL/Phase\ndetector/DSRF/LPF3/Continuous/Transfer Fcn' */
   Controller_deriv[4] = (Controller_B.Fcn1)-222.144147f*
                         Controller_X.TransferFcn_2;

   /* Update continuous states */
   Controller_X.Integrator_x += 0.0001f*Controller_deriv[5];
   Controller_X.TransferFcn[0] += 0.0001f*Controller_deriv[2];
   Controller_X.TransferFcn[1] += 0.0001f*Controller_deriv[3];
   Controller_X.Integrator1_x += 0.0001f*Controller_deriv[0];
   Controller_X.TransferFcn_1 += 0.0001f*Controller_deriv[1];
   Controller_X.TransferFcn_2 += 0.0001f*Controller_deriv[4];
}

void Controller_terminate(void)
{
}
