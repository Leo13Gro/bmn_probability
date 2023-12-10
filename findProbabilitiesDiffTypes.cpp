//
// Created by User on 06.12.2023.
//
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLine.h>

#include "src/PidProbabilityDiffTypes.cpp"

using namespace ROOT;

void findProbabilitiesDiffTypes(std::string in_file_name){
    auto *c = new TCanvas();
    auto *l = new TLine(-2, 1, 11, 1);
    std::vector<std::string> types = {"pionPos", "proton", "deuteron", "triton", "helion"};
    PidProbabilityDiffTypes prob_400(types, in_file_name, "400");
    PidProbabilityDiffTypes prob_700(types, in_file_name, "700");

    /*const std::vector<double> &res = prob_400.findProbabilities(-1, 0.5);
    for (auto ans : res){
        std::cout << "Probability = " << ans << std::endl;
    }*/


    std::vector<double> m2;

    std::vector<double> probPion_400;
    std::vector<double> probPion_700;
    std::vector<double> probProton_400;
    std::vector<double> probProton_700;
    std::vector<double> probDeuteron_400;
    std::vector<double> probDeuteron_700;
    std::vector<double> probTriton_400;
    std::vector<double> probTriton_700;
    std::vector<double> probHelion_400;
    std::vector<double> probHelion_700;
    std::vector<double> probAll_400;
    std::vector<double> probAll_700;
    std::vector<TGraph*> graph;

    std::vector<double> temp;

    for (double i = 0.5; i < 5; i += 1.) {
        for (double m = -0.1; m < 10.; m += 0.1) {
            m2.push_back(m);
            temp = prob_400.findProbabilities(m, i);
            probPion_400.push_back(temp.at(0));
            probProton_400.push_back(temp.at(1));
            probDeuteron_400.push_back(temp.at(2));
            probTriton_400.push_back(temp.at(3));
            probHelion_400.push_back(temp.at(4));

            temp = prob_700.findProbabilities(m, i);
            probPion_700.push_back(temp.at(0));
            probProton_700.push_back(temp.at(1));
            probDeuteron_700.push_back(temp.at(2));
            probTriton_700.push_back(temp.at(3));
            probHelion_700.push_back(temp.at(4));

            probAll_400.push_back(probPion_400.back() + probProton_400.back() + probDeuteron_400.back() + probTriton_400.back() + probHelion_400.back());
            probAll_700.push_back(probPion_700.back() + probProton_700.back() + probDeuteron_700.back() + probTriton_700.back() + probHelion_700.back());
        }
        graph.push_back(new TGraph(m2.size(), m2.data(), probPion_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probPion_700.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probProton_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probProton_700.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probDeuteron_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probDeuteron_700.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probTriton_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probTriton_700.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probHelion_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probHelion_700.data()));

        graph.push_back(new TGraph(m2.size(), m2.data(), probAll_400.data()));
        graph.push_back(new TGraph(m2.size(), m2.data(), probAll_700.data()));

        graph.at(0)->SetTitle(("Pion probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(1)->SetTitle(("Pion probability 700, pq = " + std::to_string(i)).c_str());
        graph.at(2)->SetTitle(("Proton probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(3)->SetTitle(("Proton probability 700, pq = " + std::to_string(i)).c_str());
        graph.at(4)->SetTitle(("Deuteron probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(5)->SetTitle(("Deuteron probability 700, pq = " + std::to_string(i)).c_str());
        graph.at(6)->SetTitle(("Triton probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(7)->SetTitle(("Triton probability 700, pq = " + std::to_string(i)).c_str());
        graph.at(8)->SetTitle(("Helion probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(9)->SetTitle(("Helion probability 700, pq = " + std::to_string(i)).c_str());

        graph.at(10)->SetTitle(("Sum probability 400, pq = " + std::to_string(i)).c_str());
        graph.at(11)->SetTitle(("Sum probability 700, pq = " + std::to_string(i)).c_str());
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