//
// Created by User on 06.12.2023.
//
#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TFile.h>

struct ParticleParameters{
    TF1* amplitude;
    TF1* mean;
    TF1* sigma;
};

struct ParticleCurrParameters{
    double amplitude;
    double mean;
    double sigma;
};

class PidProbabilityDiffTypes{
private:
    std::vector<ParticleParameters> particlesParameters; // 0 - Amplitude, 1 - Mean, 2 - Sigma

    double particlesIntegral = 0;

    std::vector<ParticleCurrParameters> particlesCurrParameters;

    std::vector<TF1 *> particlesFunction;

    void calculateParticleFunctions(double pq){
        particlesIntegral = 0;
        for (int i = 0; i < particlesParameters.size(); ++i) {
            particlesCurrParameters.at(i).amplitude = particlesParameters.at(i).amplitude->Eval(pq);
            particlesCurrParameters.at(i).mean = particlesParameters.at(i).mean->Eval(pq);
            particlesCurrParameters.at(i).sigma = particlesParameters.at(i).sigma->Eval(pq);
            particlesFunction.at(i)->SetParameters(particlesCurrParameters.at(i).amplitude,
                                                   particlesCurrParameters.at(i).mean,
                                                   particlesCurrParameters.at(i).sigma);
            particlesIntegral += particlesFunction.at(i)->Integral(-1, 10);
        }
    }

public:
    PidProbabilityDiffTypes(std::vector<std::string>& types, const std::string& in_file_name, const std::string& optional_name = ""){
        auto* f = new TFile(in_file_name.c_str(), "READ");

        for (const auto& name : types) {
            particlesParameters.push_back({(TF1 *) f->Get((name + "_" + optional_name + "_amplitude").c_str()),
                                           (TF1 *) f->Get((name + "_" + optional_name + "_mean").c_str()),
                                           (TF1 *) f->Get((name + "_" + optional_name + "_sigma").c_str())});
            particlesCurrParameters.push_back({0, 0, 0});
            particlesFunction.push_back(new TF1((name + "F").c_str(), "gaus(0)", -1, 10));
        }
    }
    // protonProb_a - particle is proton
    // prob_b - particle: |m2 - <m2>| >= m2_{measured} (m2 in 5sigma range)
    std::vector<double> findProbabilities(double m2, double pq){
        std::vector<double> probabilities;
        calculateParticleFunctions(pq);
        for (int i = 0; i < particlesCurrParameters.size(); ++i) {
            double sigma = m2 > particlesCurrParameters.at(i).mean ? 10.0 : -1.0;
            double currParticleSigmaIntegral = abs(particlesFunction.at(i)->Integral(m2, sigma));
            if (currParticleSigmaIntegral == 0){
                probabilities.push_back(0);
                continue;
            }
            double sigmaIntegral = 0;
            for (int j = 0; j < particlesCurrParameters.size(); ++j) {
                sigmaIntegral += abs(particlesFunction.at(j)->Integral(m2, sigma));
            }
            double particleProb_b = sigmaIntegral / particlesIntegral;
            probabilities.push_back(currParticleSigmaIntegral / particleProb_b / particlesIntegral);
        }
        return probabilities;
    }
    void printProbabilities(double m2, double pq){
        const std::vector<double> &res = findProbabilities(m2, pq);
        for (auto ans : res){
            std::cout << "Probability = " << ans << std::endl;
        }
    }
};