//
// Created by User on 15.11.2023.
//
#include <iostream>
#include <fstream>
#include <vector>

#include <TChain.h>
#include <TVector3.h>
#include <TMath.h>
#include <TH1F.h>
#include "TFile.h"
#include <TCanvas.h>
#include <TH2D.h>

template <typename T>
void print_vec(std::vector<T>& vec, std::string name = "vector") {
    std::cout << name << ": ";
    for (auto el : vec)
        std::cout << el << ", ";
    std::cout << std::endl;
}

template <typename T>
T vectorSum(std::vector<T>& vec) {
    T res;
    for (auto el : vec)
        res += el;
    return res;
}

/*void print_par(TF1* f, int n, std::string name = "function") {
    std::cout << name << ": ";
    for (int i = 0; i < n; i++) {
        std::cout << f->GetParameter(i) << ", ";
    }
    std::cout << std::endl;
}*/

template <typename T>
void draw_vec(std::vector<T>& vec, std::string name, std::string option="", int log=0) {
    auto c = new TCanvas("c", "c");
    c->SetLogy(log);
    for (int i = 0; i < vec.size(); i++) {
        vec[i]->Draw(option.c_str());
        c->SaveAs((name + std::to_string(i) + ".png").c_str());
    }
    delete c;
}

std::vector<TH1D*> YProjections(TH2D* histo2d, std::vector<int> range, int step) {
    std::vector<TH1D*> proj_histo;
    /*int step = (range.at(1) - range.at(0)) / n_pieces;*/
    while (range[0] < range[1]) {
        proj_histo.push_back(histo2d->ProjectionY( (std::to_string(range[0]) + "_" + std::to_string(range[0] + step)).c_str(), range[0], range[0] + step, "o"));
        range[0] += step;
    }
    return proj_histo;
}

std::vector<TH1D*> YProjections(TH2D* histo2d, std::vector<int> range, int n_pieces, double* x) {
    std::vector<TH1D*> proj_histo;
    int step = (range.at(1) - range.at(0)) / n_pieces;
    for (int i = 0; i < n_pieces; i++) {
        proj_histo.push_back(histo2d->ProjectionY((std::to_string(range[0]) + "_" + std::to_string(range[0] + step)).c_str(), range[0], range[0] + step, "o"));
        x[i] = histo2d->GetXaxis()->GetBinCenter(range[0] + step / 2);
        range[0] += step;
    }
    return proj_histo;
}