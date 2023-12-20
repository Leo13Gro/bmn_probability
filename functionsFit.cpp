//
// Created by User on 19.12.2023.
//
#include <iostream>
#include <vector>
#include <TStyle.h>
#include "src/PidFit.cpp"
void functionsFit(std::string in_file_name){
    gStyle->SetOptStat("n");
    std::vector<std::string> types = {"pionPos", "proton", "deuteron", "triton", "helion"};
    PidFit fit_400(types, in_file_name, "400");
    PidFit fit_700(types, in_file_name, "700");
    fit_400.drawPidFitRatio();
    fit_700.drawPidFitRatio();
}