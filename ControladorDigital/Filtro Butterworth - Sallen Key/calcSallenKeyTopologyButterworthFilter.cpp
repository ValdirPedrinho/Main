#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdlib.h>

using namespace std;

#define PI 			3.14159265359

#define ARQ_RESISTORES      "Resistores.txt"
#define ARQ_CAPACITORES     "Capacitores.txt"
#define CHAMADA_PLOT        system("python ./stepPlotBodePlot.py &");
#define ARQ_FUNC_TRANSF     "FuncaoTransferencia.txt"
#define CHAMADA_TABELA      system("libreoffice ./PassivosDoFiltro.csv &");
#define ARQ_FUNC_TABELA     "PassivosDoFiltro.csv"

typedef class Passivos
{
public:

    Passivos(double r1, double r2, double c1, double c2, double ne)
        : C1(c1), C2(c2), R1(r1), R2(r2), NE(ne) {}

public:
    double C1;
    double C2;
    double R1;
    double R2;
    double NE;
} passivos_t;

void insereOrdenado(vector<passivos_t *> & ptrVet, passivos_t * passivos);
double erro(double constante, double calc);
double norma2(double ea, double eb, double ec);
string imprimeResistor(double res);
string imprimeCapacitor(double cap);
vector<double> leValoresComerciais(const char * nome_arq);

int main(int argc, char *argv[])
{
    istringstream ss(argv[1]);
    double fc;
    ss >> fc;

    istringstream ss2(argv[2]);
    double erroMax;
    ss2 >> erroMax;

    vector<passivos_t *> vetorPossibilidades;
    passivos_t * novosPassivos = NULL;

    double alpha = 1.0/(4*pow(PI,2)*pow(fc,2));
    double beta = 1.0/(2*PI*fc*(sqrt(2)/2));
    double gama = (2*PI*fc)/(sqrt(2)/2);
    double erroAlpha, erroBeta, erroGama, erroNorma;

    vector<double> resistores = leValoresComerciais(ARQ_RESISTORES);
    int qtde_res = resistores.size();
    vector<double> capacitores = leValoresComerciais(ARQ_CAPACITORES);
    int qtde_cap = capacitores.size();

    for(int i=0; i<qtde_res; i++)
    {
        for(int j=i; j<qtde_res; j++)
        {
            for(int k=0; k<qtde_cap; k++)
            {
                for(int l=0; l<qtde_cap; l++)
                {
                    if((erroAlpha = erro(alpha, resistores[i]*resistores[j]*capacitores[k]*capacitores[l]) ) < erroMax)
                    {
                        if((erroBeta = erro(beta, capacitores[l]*(resistores[i]+resistores[j])) ) < erroMax)
                        {
                            if((erroGama = erro(gama, (resistores[i]+resistores[j])/(resistores[i]*resistores[j]*capacitores[k])) ) < erroMax)
                            {
                                if((erroNorma = norma2(erroAlpha, erroBeta, erroGama) ) < erroMax)
                                {
                                    novosPassivos = new Passivos(resistores[i], resistores[j], capacitores[k], capacitores[l], erroNorma);
                                    insereOrdenado(vetorPossibilidades, novosPassivos);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (vetorPossibilidades.size() > 0)
    {
        double w2_n = 1/((vetorPossibilidades[0]->R1)*(vetorPossibilidades[0]->R2)*(vetorPossibilidades[0]->C1)*(vetorPossibilidades[0]->C2));
        double w_n2csi = ((vetorPossibilidades[0]->R1)+(vetorPossibilidades[0]->R2))/((vetorPossibilidades[0]->R1)*(vetorPossibilidades[0]->R2)*(vetorPossibilidades[0]->C1));
        ofstream tffile;
        tffile.open(ARQ_FUNC_TRANSF);
        tffile << "# (omega_n)^2:" << endl << w2_n << endl;
        tffile << "# 2*omega_n*Csi:" << endl << w_n2csi << endl;
        tffile << "# Constante de tempo:" << endl << 2/w_n2csi << " s"<< endl;
        tffile.close();
        char e;
        do
        {
            cout << "Plot? (y/n)" << endl;
            cin >> e;
            if(e == 'y')
            {
                CHAMADA_PLOT
            }
        }while((e != 'n') && (e != 'y'));
    }

    ofstream logfile;
    logfile.open(ARQ_FUNC_TABELA);

    logfile << "fc =\t" << fc << " Hz" << endl;
    logfile << "R Vin\tR V(+)\tC feedback\tC V(+)\tErro(%)" << endl;
    for(int i=0; i < vetorPossibilidades.size(); i++)
    {
        logfile << imprimeResistor(vetorPossibilidades[i]->R1);
        logfile << imprimeResistor(vetorPossibilidades[i]->R2);
        logfile << imprimeCapacitor(vetorPossibilidades[i]->C1);
        logfile << imprimeCapacitor(vetorPossibilidades[i]->C2);
        logfile << fixed << setprecision(2) << vetorPossibilidades[i]->NE*100 << endl;
        delete vetorPossibilidades[i];
    }

    logfile.close();
//    CHAMADA_TABELA
    return 0;
}

void insereOrdenado(vector<passivos_t *> & ptrVet, passivos_t * passivos)
{
    for(int i=0; i<ptrVet.size(); i++)
    {
        if(((ptrVet[i])->NE) > (passivos->NE))
        {
            ptrVet.insert(ptrVet.begin()+i, passivos);
            return;
        }
    }
    ptrVet.push_back(passivos);
}

double erro(double constante, double calc)
{
    return abs(calc - constante)/constante;
}

double norma2(double ea, double eb, double ec)
{
    return sqrt(pow(ea,2)+pow(eb,2)+pow(ec,2));
}

string imprimeResistor(double res)
{
    ostringstream strs;
    if(res > 1000000.00)
    {
        strs << res/1000000.00 << " MOhm\t";
    }
    else if(res > 1000.00)
    {
        strs << res/1000.00 << " kOhm\t";
    }
    else
    {
        strs << res << " Ohm\t";
    }
    return strs.str();
}

string imprimeCapacitor(double cap)
{
    ostringstream strs;
    if(cap < 0.000000001)
    {
        strs << cap*1000000000000 << " pF\t";
    }
    else if(cap < 0.000001)
    {
        strs << cap*1000000000 << " nF\t";
    }
    else if(cap < 0.001)
    {
        strs << cap*1000000 << " uF\t";
    }
    else
    {
        strs << cap*1000 << " mF\t";
    }
    return strs.str();
}

vector<double> leValoresComerciais(const char * nome_arq)
{
    double aux;
    vector<double> valoresComerciais;
    ifstream infile(nome_arq);
    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        double aux;
        if (!(iss >> aux))
        {
            break;    // error
        }

        valoresComerciais.push_back(aux);
    }
    return valoresComerciais;
}
