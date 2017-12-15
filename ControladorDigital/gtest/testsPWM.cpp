#include "Test_ControladorDigital.h"

Ctr2PWM ctr2PWM;
int_t max_pwm;
double min_output;
double max_output;

TEST(Controller_to_PWM, min_positivo_max_positivo)
{
    max_pwm = 10000;
    min_output = 0.0;
    max_output = 10.0;
    createCtr2PWMHandler(&ctr2PWM, max_pwm, min_output, max_output);
    EXPECT_EQ(10000, ctr2PWM.max_pwm);
    EXPECT_FLOAT_EQ(0.0, ctr2PWM.min_ctr_output);
    EXPECT_FLOAT_EQ(10.0, ctr2PWM.max_ctr_output);
    EXPECT_FLOAT_EQ(10.0, ctr2PWM.delta_ctr_output);
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, -1.0));
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, 0.0));
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, 0.00001));
    EXPECT_EQ(1, runCtr2PWM(ctr2PWM, 0.000505));
    EXPECT_EQ(5000, runCtr2PWM(ctr2PWM, 5.0));
    EXPECT_EQ(10000, runCtr2PWM(ctr2PWM, 10.0));
    EXPECT_EQ(10000, runCtr2PWM(ctr2PWM, 12.0));

    max_pwm = 255;
    min_output = 1.0;
    max_output = 3.3;
    createCtr2PWMHandler(&ctr2PWM, max_pwm, min_output, max_output);
    EXPECT_EQ(255, ctr2PWM.max_pwm);
    EXPECT_FLOAT_EQ(1.0, ctr2PWM.min_ctr_output);
    EXPECT_FLOAT_EQ(3.3, ctr2PWM.max_ctr_output);
    EXPECT_FLOAT_EQ(2.3, ctr2PWM.delta_ctr_output);
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, -1.0));
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, 1.0));
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, 1.00001));
    EXPECT_EQ(1, runCtr2PWM(ctr2PWM, 1.004509804));
    EXPECT_EQ(128, runCtr2PWM(ctr2PWM, 2.15));
    EXPECT_EQ(254, runCtr2PWM(ctr2PWM, 3.29549));
    EXPECT_EQ(255, runCtr2PWM(ctr2PWM, 3.3));
    EXPECT_EQ(255, runCtr2PWM(ctr2PWM, 3.4));
}

TEST(Controller_to_PWM, min_negativo_max_positivo)
{
    max_pwm = 1000;
    min_output = -5.0;
    max_output = 10.0;
    createCtr2PWMHandler(&ctr2PWM, max_pwm, min_output, max_output);
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, -6.0));
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, -5.0));
    EXPECT_EQ(500, runCtr2PWM(ctr2PWM, 2.5));
    EXPECT_EQ(1000, runCtr2PWM(ctr2PWM, 10.0));
    EXPECT_EQ(1000, runCtr2PWM(ctr2PWM, 12.0));
}

TEST(Controller_to_PWM, min_negativo_max_negativo)
{
    max_pwm = 200;
    min_output = -5.0;
    max_output = -1.0;
    createCtr2PWMHandler(&ctr2PWM, max_pwm, min_output, max_output);
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, -5.01));
    EXPECT_EQ(0, runCtr2PWM(ctr2PWM, -5.0));
    EXPECT_EQ(100, runCtr2PWM(ctr2PWM, -3.0));
    EXPECT_EQ(200, runCtr2PWM(ctr2PWM, -1.0));
    EXPECT_EQ(200, runCtr2PWM(ctr2PWM, -0.5));
}
