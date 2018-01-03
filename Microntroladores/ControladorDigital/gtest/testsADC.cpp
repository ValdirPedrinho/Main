#include "Test_ControladorDigital.h"

ADC2Ctr adc2ctr;
uint8_t bits_ADC;
double sensor_gain;
double min_input;
double max_input;

TEST(Conversao_AD, Ganho_1_Tensao_0_para_3V3)
{
    bits_ADC = 8;
    sensor_gain = 1.0;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(255, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.012941176));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 254) - 3.287058824));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 255) - 3.3));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 256) - 3.3));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 127) - 1.643529412));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 80) - 1.035294118));

    bits_ADC = 12;
    sensor_gain = 1.0;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(4095, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.000805861));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4094) - 3.299194139));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4095) - 3.3));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4096) - 3.3));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 333) - 0.268351648));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 2087) - 1.681831502));

    bits_ADC = 16;
    sensor_gain = 1.0;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(65535, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.000050355));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65534) - 3.299949645));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65535) - 3.3));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65536) - 3.3));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 333) - 0.016768139));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 20087) - 1.01147631));
}

TEST(Conversao_AD, Ganho_maior_que_1_Tensao_0_para_3V3)
{
    bits_ADC = 8;
    sensor_gain = 5.5;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(255, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3/5.5, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.012941176/5.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 254) - 3.287058824/5.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 255) - 3.3/5.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 256) - 3.3/5.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 127) - 1.643529412/5.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 80) - 1.035294118/5.5));

    bits_ADC = 12;
    sensor_gain = 2.1;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(4095, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3/2.1, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.000805861/2.1));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4094) - 3.299194139/2.1));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4095) - 3.3/2.1));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4096) - 3.3/2.1));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 333) - 0.268351648/2.1));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 2087) - 1.681831502/2.1));

    bits_ADC = 16;
    sensor_gain = 10.0;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(65535, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3/10.0, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.000050355/10.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65534) - 3.299949645/10.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65535) - 3.3/10.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65536) - 3.3/10.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 333) - 0.016768139/10.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 20087) - 1.01147631/10.0));
}

TEST(Conversao_AD, Ganho_menor_que_1_Tensao_0_para_3V3)
{
    bits_ADC = 8;
    sensor_gain = 0.5;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(255, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3/0.5, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.012941176/0.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 254) - 3.287058824/0.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 255) - 3.3/0.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 256) - 3.3/0.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 127) - 1.643529412/0.5));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 80) - 1.035294118/0.5));

    bits_ADC = 12;
    sensor_gain = 0.21;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(4095, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3/0.21, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.000805861/0.21));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4094) - 3.299194139/0.21));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4095) - 3.3/0.21));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4096) - 3.3/0.21));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 333) - 0.268351648/0.21));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 2087) - 1.681831502/0.21));

    bits_ADC = 16;
    sensor_gain = 0.10;
    min_input = 0.0;
    max_input = 3.3;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(65535, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(0.0, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(3.3/0.1, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 0.0));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 0.000050355/0.10));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65534) - 3.299949645/0.10));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65535) - 3.3/0.10));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65536) - 3.3/0.10));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 333) - 0.016768139/0.10));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 20087) - 1.01147631/0.10));
}

TEST(Conversao_AD, Ganho_variado_Tensao_negativa_para_positiva)
{
    bits_ADC = 8;
    sensor_gain = 1.0;
    min_input = -6.14;
    max_input = 6.14;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(255, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(-6.14, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(12.28, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - (-6.14)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - (-6.14)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - (-6.091843137)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 254) - 6.091843137));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 255) - 6.14));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 256) - 6.14));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 127) - (-0.024078431)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 80) - (-2.28745098)));

    bits_ADC = 12;
    sensor_gain = 0.5;
    min_input = -3.14;
    max_input = 5.14;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(4095, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(-3.14/0.5, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(8.28/0.5, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - (-6.28)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - (-6.28)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - (-6.275956044)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4094) - 10.275956044));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4095) - 10.28));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 4096) - 10.28));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 3054) - 6.070241758));

    bits_ADC = 16;
    sensor_gain = 2.5;
    min_input = -3.14;
    max_input = 3.14;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(65535, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(-3.14/2.5, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(6.28/2.5, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - (-1.256)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - (-1.256)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - (-1.255961669)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65534) - 1.255961669));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65535) - 1.256));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 65536) - 1.256));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 30054) - -0.104010254));
}

TEST(Conversao_AD, Ganho_variado_Tensao_negativa_para_negativa)
{
    bits_ADC = 24;
    sensor_gain = 1.0;
    min_input = -6.14;
    max_input = -0.14;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(16777215, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(-6.14, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(6.00, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - (-6.14)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - (-6.14)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - (-6.139999642)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 16777214) - (-0.140000358)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 16777215) - (-0.14)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 16777216) - (-0.14)));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 8388608) - (-3.139999821)));
}

TEST(Conversao_AD, Ganho_variado_Tensao_positiva_para_positiva)
{
    bits_ADC = 10;
    sensor_gain = 0.5;
    min_input = 3.14;
    max_input = 5.14;
    createADC2CtrHandler(&adc2ctr, bits_ADC, sensor_gain, min_input, max_input);
    EXPECT_EQ(1023, adc2ctr.max_adc);
    EXPECT_FLOAT_EQ(3.14/0.5, adc2ctr.min_analog_input);
    EXPECT_FLOAT_EQ(2.0/0.5, adc2ctr.delta_analog_input);
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, -1) - 6.28));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 0) - 6.28));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1) - 6.283910068));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1022) - 10.276089932));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1023) - 10.28));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 1024) - 10.28));
    EXPECT_GE(ERRO_MAX, abs(runADC2Ctr(adc2ctr, 512) - 8.281955034));
}
