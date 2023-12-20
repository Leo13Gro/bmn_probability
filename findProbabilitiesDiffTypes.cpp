//
// Created by User on 06.12.2023.
//
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLine.h>
#include <TH2D.h>
#include <TStyle.h>

#include "src/PidProbabilityDiffTypes.cpp"

using namespace ROOT;

void findProbabilitiesDiffTypes(std::string in_file_name){
    auto *c = new TCanvas();
    auto *l = new TLine(-2, 1, 11, 1);
    std::vector<std::string> types = {"pionPos", "proton", "deuteron", "triton", "helion"};
    PidProbabilityDiffTypes prob_400(types, in_file_name, "400");
    PidProbabilityDiffTypes prob_700(types, in_file_name, "700");
    double p;
    std::cin >> p;
    while(p != 100){
        prob_400.printProbabilities(0.3, p);
        std::cin >> p;
    }

    /*prob_400.printProbabilities(0.4, 2.09);*/

    std::vector<double> m2;
    std::vector<double> pq;
    std::vector<std::vector<double>> probabilities_400(types.size());
    std::vector<std::vector<double>> probabilities_700(types.size());

    std::vector<TGraph*> graph;

    std::vector<double> temp_4;
    std::vector<double> temp_7;

    /*for (double p = 0.5; p < 5; p += 1.) {
        for (double m = -0.1; m < 10.; m += 0.1) {
            m2.push_back(m);
            temp_4 = prob_400.findProbabilities(m, p);
            temp_7 = prob_700.findProbabilities(m, p);
            for (int j = 0; j < types.size(); ++j) {
                probabilities_400.at(j).push_back(temp_4.at(j));
                probabilities_700.at(j).push_back(temp_7.at(j));
            }
        }
        for (int j = 0; j < types.size(); ++j) {
            graph.push_back(new TGraph(m2.size(), m2.data(), probabilities_400.at(j).data()));
            graph.back()->SetTitle((types.at(j) + " probability 400, pq = " + std::to_string(p)).c_str());
            graph.push_back(new TGraph(m2.size(), m2.data(), probabilities_700.at(j).data()));
            graph.back()->SetTitle((types.at(j) + " probability 700, pq = " + std::to_string(p)).c_str());
        }
        for (int j = 0; j < graph.size(); ++j) {
            graph.at(j)->Draw("*ac");
            l->Draw("same");
            c->SaveAs(("bmn_hist/probabilities/" + std::to_string((int) (2 * p)) + "_" + std::to_string(j) + ".png").c_str());
        }
        graph.clear();
        m2.clear();
        for (int j = 0; j < probabilities_400.size(); ++j) {
            probabilities_400.at(j).clear();
            probabilities_700.at(j).clear();
        }
    }*/
    /*gStyle->SetOptStat("n");
    std::vector<TH2D*> h2_pq_m2_prob_400;
    std::vector<TH2D*> h2_pq_m2_prob_700;
    for (int i = 0; i < types.size(); ++i) {
        h2_pq_m2_prob_400.push_back(new TH2D((types.at(i) + "_m2_pq_400").c_str(),
                                             ";p/q (GeV/c);m^{2}_{TOF-400} (GeV^{2}/c^{4})", 451, 0.5, 5., 1101, -1., 10.));
        h2_pq_m2_prob_700.push_back(new TH2D((types.at(i) + "_m2_pq_700").c_str(),
                                             ";p/q (GeV/c);m^{2}_{TOF-400} (GeV^{2}/c^{4})", 451, 0.5, 5., 1101, -1., 10.));
    }
    for (double p = 0.5; p < 5.; p += 0.01) {
        for (double m = -1.0; m < 10.; m += 0.01) {
            temp_4 = prob_400.findProbabilities(m, p);
            temp_7 = prob_700.findProbabilities(m, p);
            for (int i = 0; i < types.size(); ++i) {
                h2_pq_m2_prob_400.at(i)->Fill(p, m, temp_4.at(i));
                h2_pq_m2_prob_700.at(i)->Fill(p, m, temp_7.at(i));
            }
        }
    }
    for (int i = 0; i < types.size(); ++i) {
        h2_pq_m2_prob_400.at(i)->Draw("colz");
        c->SaveAs(("bmn_hist/h2_probabilities/" + types.at(i) + "_h2_pq_m2_prob_400.png").c_str());
        h2_pq_m2_prob_700.at(i)->Draw("colz");
        c->SaveAs(("bmn_hist/h2_probabilities/" + types.at(i) + "_h2_pq_m2_prob_700.png").c_str());
    }*/

    /*std::cout << "5 * sigma = " << sigma << std::endl;
    std::cout << "sigmaIntegral = " << sigmaIntegral << std::endl;
    std::cout << "pionProb_b = " << pionProb_b << std::endl;*/
}