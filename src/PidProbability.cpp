//
// Created by User on 15.11.2023.
//
#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TFile.h>

class PidProbability{
private:
    TF1* pionParameters[3]; // 0 - Amplitude, 1 - Mean, 2 - Sigma
    TF1* protonParameters[3];
    TF1* deuteronParameters[3];

    double protonIntegral;
    double pionIntegral;
    double deuteronIntegral;

    double protonCurrParameters[3];
    double pionCurrParameters[3];
    double deuteronCurrParameters[3];

    void calculateParticleFunctions(double pq){
        for (int i = 0; i < 3; ++i) {
            protonCurrParameters[i] = (*protonParameters[i])(pq);
        }
        for (int i = 0; i < 3; ++i) {
            pionCurrParameters[i] = (*pionParameters[i])(pq);
        }
        for (int i = 0; i < 3; ++i) {
            deuteronCurrParameters[i] = (*deuteronParameters[i])(pq);
        }
        protonF->SetParameters(protonCurrParameters[0], protonCurrParameters[1], protonCurrParameters[2]);
        pionF->SetParameters(pionCurrParameters[0], pionCurrParameters[1], pionCurrParameters[2]);
        deuteronF->SetParameters(deuteronCurrParameters[0], deuteronCurrParameters[1], deuteronCurrParameters[2]);

        protonIntegral = protonF->Integral(-1, 10);
        pionIntegral = pionF->Integral(-1, 10);
        deuteronIntegral = deuteronF->Integral(-1, 10);
    }

public:
    TF1* protonF = new TF1("protonF", "gaus(0)", -1, 10);
    TF1* pionF = new TF1("pionF", "gaus(0)", -1, 10);
    TF1* deuteronF = new TF1("deuteronF", "gaus(0)", -1, 10);

    PidProbability(const std::string& name, const std::string& in_file_name){
        auto* f = new TFile(in_file_name.c_str(), "READ");

        pionParameters[0] = (TF1*) (f->Get(("pionPos_" + name + "_amplitude").c_str()));
        pionParameters[1] = (TF1*) f->Get(("pionPos_" + name + "_mean").c_str());
        pionParameters[2] = (TF1*) f->Get(("pionPos_" + name + "_sigma").c_str());

        protonParameters[0] = (TF1*) f->Get(("proton_" + name + "_amplitude").c_str());
        protonParameters[1] = (TF1*) f->Get(("proton_" + name + "_mean").c_str());
        protonParameters[2] = (TF1*) f->Get(("proton_" + name + "_sigma").c_str());

        deuteronParameters[0] = (TF1*) f->Get(("deuteron_" + name + "_amplitude").c_str());
        deuteronParameters[1] = (TF1*) f->Get(("deuteron_" + name + "_mean").c_str());
        deuteronParameters[2] = (TF1*) f->Get(("deuteron_" + name + "_sigma").c_str());
    }
    double pionProbability(double m2, double pq){
        calculateParticleFunctions(pq);
        double sigma = m2 > pionCurrParameters[1] ? 10.0 : -1.0;

        double sigmaIntegral = abs(pionF->Integral(m2, sigma));
        double pionProb_b = sigmaIntegral == 0 ? 1 : (abs(protonF->Integral(m2, sigma)) + sigmaIntegral + abs(deuteronF->Integral(m2, sigma)))
                                                     / (protonIntegral + pionIntegral + deuteronIntegral);
        return sigmaIntegral / pionProb_b / (protonIntegral + pionIntegral + deuteronIntegral);
    }
    // protonProb_a - particle is proton
    // prob_b - particle: |m2 - <m2>| >= m2_{measured} (m2 in 5sigma range)

    double protonProbability(double m2, double pq){
        calculateParticleFunctions(pq);
        double sigma = m2 > protonCurrParameters[1] ? 10.0 : -1.0;

        double sigmaIntegral = abs(protonF->Integral(m2, sigma));
        double protonProb_b = sigmaIntegral == 0 ? 1 : (sigmaIntegral + abs(pionF->Integral(m2, sigma)) + abs(deuteronF->Integral(m2, sigma)))
                                                       / (protonIntegral + pionIntegral + deuteronIntegral);
        return sigmaIntegral / protonProb_b / (protonIntegral + pionIntegral + deuteronIntegral);
    }

    double deuteronProbability(double m2, double pq){
        calculateParticleFunctions(pq);
        double sigma = m2 > deuteronCurrParameters[1] ? 10.0 : -1.0;

        double sigmaIntegral = abs(deuteronF->Integral(m2, sigma));
        double deuteronProb_b = sigmaIntegral == 0 ? 1 : (sigmaIntegral + abs(protonF->Integral(m2, sigma)) + abs(pionF->Integral(m2, sigma)))
                                                         / (protonIntegral + pionIntegral + deuteronIntegral);
        /*std::cout << "5 * sigma = " << sigma << std::endl;
        std::cout << "sigmaIntegral = " << sigmaIntegral << std::endl;
        std::cout << "deuteronProb_b = " << deuteronProb_b << std::endl;
        std::cout << "sum of Integrals = " << protonIntegral + pionIntegral + deuteronIntegral << std::endl;*/
        return sigmaIntegral / deuteronProb_b / (protonIntegral + pionIntegral + deuteronIntegral);
    }
};