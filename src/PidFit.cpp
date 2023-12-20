//
// Created by User on 19.12.2023.
//
#include <vector>
#include <TF1.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TFile.h>

#include "ParticleFitData.cpp"

class PidFit{
private:
    std::vector<ParticleParameters> particlesParameters; // 0 - Amplitude, 1 - Mean, 2 - Sigma

    double particlesIntegral = 0;

    std::vector<ParticleCurrParameters> particlesCurrParameters;

    std::vector<TF1 *> particlesFunction;

    std::vector<std::string> types;
    std::string optional_name;

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
    double findFitProbability(int type_number, double m2, double pq){
        calculateParticleFunctions(pq);
        double sum = 0;
        for (int i = 0; i < types.size(); ++i) {
            sum += particlesFunction.at(i)->Eval(m2);
        }
        return particlesFunction.at(type_number)->Eval(m2) / sum;
    }
    std::vector<double> findWeights(double m2, double pq){
        std::vector<double> res;
        double sum = 0;
        calculateParticleFunctions(pq);
        for (int i = 0; i < types.size(); ++i) {
            res.push_back(particlesFunction.at(i)->Eval(m2));
            sum += res.back();
        }
        for (double & w : res) {
            w /= sum;
        }
        return res;
    }
public:
    PidFit(std::vector<std::string>& types, const std::string& in_file_name, const std::string& optional_name = ""){
        auto* f = new TFile(in_file_name.c_str(), "READ");

        for (const auto& name : types) {
            particlesParameters.push_back({(TF1 *) f->Get((name + "_" + optional_name + "_amplitude").c_str()),
                                           (TF1 *) f->Get((name + "_" + optional_name + "_mean").c_str()),
                                           (TF1 *) f->Get((name + "_" + optional_name + "_sigma").c_str())});
            particlesCurrParameters.push_back({0, 0, 0});
            particlesFunction.push_back(new TF1((name + "F").c_str(), "gaus(0)", -1, 10));
        }
        this->types = types;
        this->optional_name = optional_name;
    }
    void drawPidFitRatio(){
        auto *c = new TCanvas();
        std::vector<TH2D*> h2_pq_m2_prob;
        for (int i = 0; i < types.size(); ++i) {
            h2_pq_m2_prob.push_back(new TH2D((types.at(i) + "_m2_pq_" + optional_name).c_str(),
                                                 ";p/q (GeV/c);m^{2} (GeV^{2}/c^{4})", 451, 0.5, 5., 1101, -1., 10.));
        }
        std::vector<double> weights;
        for (double p = 0.5; p < 5.; p += 0.01) {
            for (double m = -1.0; m < 10.; m += 0.01) {
                weights = findWeights(m, p);
                for (int i = 0; i < types.size(); ++i) {
                    h2_pq_m2_prob.at(i)->Fill(p, m, weights.at(i));
                }
            }
        }
        for (int i = 0; i < types.size(); ++i) {
            h2_pq_m2_prob.at(i)->SetAxisRange(0, 1, "Z");
            h2_pq_m2_prob.at(i)->Draw("colz");
            c->SaveAs(("bmn_hist/h2_fitRatio/" + types.at(i) + "_h2_pq_m2_prob_" + optional_name + ".png").c_str());
        }
    }
};