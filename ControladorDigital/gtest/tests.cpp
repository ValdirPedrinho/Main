#include "Test_ControladorDigital.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//CtrPI ctrPI;

//const double CTR_K                  = 0.8;				// Ganho proporcional
//const double CTR_TAU                = 50*mili_const;	// Constante de tempo
//const double CTR_FREQ_SAMPLING  	= 15.0;				// Frequência de amostragem
//const double initialVoltage         = 1.0;
//
//TEST(Controlador, Regime_Permanente_FT_unitaria)
//{
//    double voltage = initialVoltage;
//    createPIHandler(&ctrPI, NULL, NULL, CTR_K, CTR_TAU, CTR_FREQ_SAMPLING, double (-100000*initialVoltage), double (100000*initialVoltage));
//    int i;
//    for(i=0; i<10000000; i++)
//    {
//        voltage = runPI(&ctrPI, initialVoltage, voltage);
//        if(_abs(ctrPI.e) < 1E-5)
//        {
//            break;
//        }
//        //cout << "input error:" << ctrPI.e << endl;
//    }
//    cout << "input error:" << ctrPI.e << " iteracao: " << i << endl;
//    EXPECT_LT(abs(_abs(ctrPI.e), 1E-5);
//}



