//
// Created by User on 15.11.2023.
//
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLine.h>

#include "src/PidProbability.cpp"

using namespace ROOT;

void findProbabilities(std::string in_file_name){
    auto *c = new TCanvas();
    auto *l = new TLine(-2, 1, 11, 1);
    PidProbability prob_400("400", in_file_name);
    PidProbability prob_700("700", in_file_name);

    /*double res = prob_400.deuteronProbability(-0.9, 0.5);
    std::cout << "Probability = " << res << std::endl;

    std::cout << prob_400.pionProbability(1.0, 1.5) << std::endl;
    std::cout << prob_400.protonProbability(1.0, 1.5) << std::endl;
    std::cout << prob_400.deuteronProbability(1.0, 1.5) << std::endl;*/

    std::vector<double> m2;
    std::vector<double> probPion_400;
    std::vector<double> probPion_700;
    std::vector<double> probProton_400;
    std::vector<double> probProton_700;
    std::vector<double> probDeuteron_400;
    std::vector<double> probDeuteron_700;
    std::vector<double> probAll_400;
    std::vector<double> probAll_700;
    std::vector<TGraph*> graph;

    for (double i = 0.5; i < 5; i += 1.) {
        for (double m = -1.; m < 10.; m += 0.1) {
            m2.push_back(m);
            probPion_400.push_back(prob_400.pionProbability(m, i));
            probPion_700.push_back(prob_700.pionProbability(m, i));
            probProton_400.push_back(prob_400.protonProbability(m, i));
            probProton_700.push_back(prob_700.protonProbability(m, i));
            probDeuteron_400.push_back(prob_400.deuteronProbability(m, i));
            probDeuteron_700.push_back(prob_700.deuteronProbability(m, i));

            probAll_400.push_back(probPion_400.back() + probProton_400.back() + probDeuteron_400.back());
            probAll_700.push_back(probPion_700.back() + probProton_700.back() + probDeuteron_700.back());
        }
        graph.push_back(new TGraph(m2.size(), m2.data(), probPion_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probPion_700.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probProton_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probProton_700.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probDeuteron_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probDeuteron_700.data()));

        graph.push_back(new TGraph(m2.size(), m2.data(), probAll_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probAll_700.data()));

        graph.at(0)->SetTitle(("Pion probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(1)->SetTitle(("Pion probability 700, pq = " + std::to_string(i)).c_str());
        graph.at(2)->SetTitle(("Proton probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(3)->SetTitle(("Proton probability 700, pq = " + std::to_string(i)).c_str());
        graph.at(4)->SetTitle(("Deuteron probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(5)->SetTitle(("Deuteron probability 700, pq = " + std::to_string(i)).c_str());

        graph.at(6)->SetTitle(("Sum probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(7)->SetTitle(("Sum probability 700, pq = " + std::to_string(i)).c_str());
        for (int j = 0; j < graph.size(); ++j) {
            graph.at(j)->Draw("*ac");
            l->Draw("same");
            c->SaveAs(("bmn_hist/probabilities/" + std::to_string((int) (2 * i)) + "_" + std::to_string(j) + ".png").c_str());
        }
        graph.clear();
        m2.clear();
        probPion_400.clear();
        probPion_700.clear();
        probProton_400.clear();
        probProton_700.clear();
        probDeuteron_400.clear();
        probDeuteron_700.clear();

        probAll_400.clear();
        probAll_700.clear();
    }
    /*std::cout << "5 * sigma = " << sigma << std::endl;
    std::cout << "sigmaIntegral = " << sigmaIntegral << std::endl;
    std::cout << "pionProb_b = " << pionProb_b << std::endl;*/
}