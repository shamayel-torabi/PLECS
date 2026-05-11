/*
 * Header file for: 3-phase-invertor-svm-02/Controller
 * Generated with : PLECS 4.9.5
 * Generated on   : 22 Apr 2026 10:50:46
 */
#ifndef PLECS_HEADER_Controller_h_
#define PLECS_HEADER_Controller_h_

#include <stdbool.h>
#include <stdint.h>

/* Model floating point type */
typedef float Controller_FloatType;

/* Model checksum */
extern const char * const Controller_checksum;

/* Model error status */
extern const char * Controller_errorStatus;


/* Model sample time */
extern const float Controller_sampleTime;


/*
 * Model states */
typedef struct
{
   float Integrator_x;              /* Controller/Three-Phase PLL/Integrator */
   float TransferFcn[2];            /* Controller/Three-Phase PLL/Phase detector/DSRF/LPF2/Continuous/Transfer Fcn */
   float Integrator1_x;             /* Controller/Three-Phase PLL/Continuous PID Controller/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1 */
   bool Integrator1_i1_first;       /* Controller/Three-Phase PLL/Continuous PID Controller/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1 */
   bool Integrator1_i2_prevReset;   /* Controller/Three-Phase PLL/Continuous PID Controller/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1 */
   float TransferFcn_1;             /* Controller/Three-Phase PLL/Phase detector/DSRF/LPF1/Continuous/Transfer Fcn */
   float TransferFcn_2;             /* Controller/Three-Phase PLL/Phase detector/DSRF/LPF3/Continuous/Transfer Fcn */
} Controller_ModelStates;
extern Controller_ModelStates Controller_X;


/* External inputs */
typedef struct
{
   float Vabc_Out1[3];              /* Out1 */
} Controller_ExternalInputs;
extern Controller_ExternalInputs Controller_U;


/* External outputs */
typedef struct
{
   float DAC;                       /* DAC */
} Controller_ExternalOutputs;
extern Controller_ExternalOutputs Controller_Y;


/* Block outputs */
typedef struct
{
   float Normalize;                 /* Controller/Three-Phase PLL/Phase detector/DSRF/Normalize */
   float Saturation;                /* Controller/Three-Phase PLL/Continuous PID Controller/Saturation/internal/Saturation Select/constant/Saturation */
   float Integrator;                /* Controller/Three-Phase PLL/Integrator */
   float beta;                      /* Controller/Three-Phase PLL/Phase detector/DSRF/3ph->SRF/beta */
   float TrigonometricFunction1;    /* Controller/Three-Phase PLL/Phase detector/DSRF/sin/cos/Trigonometric Function1 */
   float alpha;                     /* Controller/Three-Phase PLL/Phase detector/DSRF/3ph->SRF/alpha */
   float TrigonometricFunction;     /* Controller/Three-Phase PLL/Phase detector/DSRF/sin/cos/Trigonometric Function */
   float TransferFcn[2];            /* Controller/Three-Phase PLL/Phase detector/DSRF/LPF2/Continuous/Transfer Fcn */
   float Gain1;                     /* Controller/Three-Phase PLL/Phase detector/DSRF/sin/cos/Gain1 */
   float Sum;                       /* Controller/Three-Phase PLL/Phase detector/DSRF/sin/cos/Sum */
   float Fcn1;                      /* Controller/Three-Phase PLL/Phase detector/DSRF/Decoupling network+1/Fcn1 */
   float Fcn;                       /* Controller/Three-Phase PLL/Phase detector/DSRF/Decoupling network+1/Fcn */
   float Normalize_i1;              /* Controller/Three-Phase PLL/Phase detector/DSRF/Normalize */
   float Integrator1;               /* Controller/Three-Phase PLL/Continuous PID Controller/Continous Time/Ki Integrator/Ki ~= 0/Integrator/edge_triggered/Integrator1 */
   float TransferFcn_1;             /* Controller/Three-Phase PLL/Phase detector/DSRF/LPF1/Continuous/Transfer Fcn */
   float TransferFcn_2;             /* Controller/Three-Phase PLL/Phase detector/DSRF/LPF3/Continuous/Transfer Fcn */
} Controller_BlockOutputs;
extern Controller_BlockOutputs Controller_B;

/* Entry point functions */
void Controller_initialize(float time);
void Controller_output(void);
void Controller_update(void);
void Controller_terminate(void);

#endif /* PLECS_HEADER_Controller_h_ */
