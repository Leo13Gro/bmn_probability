//
// Created by User on 15.11.2023.
//
#include <iostream>

#include "TFile.h"

#include "src/Pid.cpp"

using namespace ROOT;

void pidFunctions(std::string in_file_name, std::string out_file_name = "PidFunctions.root"){

    auto f_in = new TFile(in_file_name.c_str(), "READ");

    auto h2_pq_mass2_tof400 = (TH2D*) (f_in->Get("h2_pq_mass2_tof400"));
    auto h2_pq_mass2_tof700 = (TH2D*) (f_in->Get("h2_pq_mass2_tof700"));

    Pid pionPos_400("pionPos_400", "pol 4", "pol 4", "pol 3", h2_pq_mass2_tof400, { 35, 60 }, 5, {
            {-0.05, 0.05}, {-0.05, 0.05}, {-0.1, 0.1}, {-0.15, 0.1}, {-0.25, 0.1} });
    pionPos_400.f_m->SetParameter(0, 100);
    std::cout << "test: " << pionPos_400.f_m->Eval(1) << std::endl;
    Pid pionPos_700("pionPos_700", "pol 4", "pol 5", "pol 4", h2_pq_mass2_tof700, { 35, 70 }, 5, {
            {-0.02, 0.05}, {-0.02, 0.05}, {-0.05, 0.1}, {-0.05, 0.1}, {-0.1, 0.1}, {-0.2, 0.15}, {-0.2, 0.15} });
    std::cout << "test: " << pionPos_400.f_m->Eval(1) << std::endl;
    pionPos_400.fit_pid();
    pionPos_700.fit_pid();


    /*std::vector<Pid> particlesPid;

    particlesPid.push_back(Pid("pionPos_400", "pol 4", "pol 4", "pol 3", h2_pq_mass2_tof400, { 35, 60 }, 5, {
            {-0.05, 0.05}, {-0.05, 0.05}, {-0.1, 0.1}, {-0.15, 0.1}, {-0.25, 0.1} }));
    particlesPid.push_back(Pid("pionPos_700", "pol 4", "pol 5", "pol 4", h2_pq_mass2_tof700, { 35, 70 }, 5, {
            {-0.02, 0.05}, {-0.02, 0.05}, {-0.05, 0.1}, {-0.05, 0.1}, {-0.1, 0.1}, {-0.2, 0.15}, {-0.2, 0.15} }));

    particlesPid.push_back(Pid("proton_400", "pol 4", "pol 3", "pol 3", h2_pq_mass2_tof400, { 35, 70 }, 5, {
            {0.8, 1.1}, {0.8, 1.1}, {0.7, 1.1}, {0.7, 1.1}, {0.6, 1.0}, {0.6, 1.0}, {0.4, 0.9} }));
    particlesPid.push_back(Pid("proton_700", "pol 4", "pol 4", "pol 3", h2_pq_mass2_tof700, { 35, 75 }, 5, {
            {0.8, 1.1}, {0.8, 1.0}, {0.8, 1.0}, {0.8, 1.0}, {0.8, 1.0}, {0.7, 1.1}, {0.7, 1.1}, {0.7, 1.1} }));

    particlesPid.push_back(Pid("deuteron_400", "pol 4", "pol 3", "pol 4", h2_pq_mass2_tof400, { 40, 70 }, 5, {
            {3.5, 4.}, {3.5, 4.}, {3.25, 4.}, {3., 4.}, {3., 4.}, {3., 4.} }));
    particlesPid.push_back(Pid("deuteron_700", "pol 3", "pol 3", "pol 4", h2_pq_mass2_tof700, { 40, 70 }, 5, {3.25, 4.}));

    *//*particlesPid.push_back(new Pid("helion_400", "pol 2", "pol 3", "pol 3", h2_pq_mass2_tof400, { 40, 60 }, 5, {
            {1.85, 2.25}, {1.85, 2.25}, {1.85, 2.25}, {1.8, 2.1} }));
    *//**//*particlesPid.back()->f_m->SetParameters(1.911, -0.154, 0.424, -0.189);
    particlesPid.back()->f_s->SetParameters(1.448, -1.321, 0.208, 0.117);*//**//*
    particlesPid.push_back(new Pid("helion_700", "pol 4", "pol 5", "pol 4", h2_pq_mass2_tof700, { 40, 65 }, 5, {
            {1.95, 2.3}, {1.9, 2.2}, {1.85, 2.1}, {1.8, 2.1}, {1.75, 2.1} }));*//*

    particlesPid.push_back(Pid("triton_400", "pol 3", "pol 3", "pol 3", h2_pq_mass2_tof400, { 50, 70 }, 5, {
            {7.3, 9.}, {7.3, 9.}, {7.3, 8.5}, {7.3, 8.5} }));
    particlesPid.push_back(Pid("triton_700", "pol 4", "pol 5", "pol 5", h2_pq_mass2_tof700, { 40, 75 }, 5, {
            {7.5, 9.3}, {7.5, 9.}, {7.5, 9.}, {7.5, 8.5}, {7.5, 8.5}, {7.5, 8.5}, {7.5, 8.5} }));*/

    /*for (auto pid : particlesPid) {
        pid.fit_pid();
        *//*std::cout << pid->f_m->Eval(1) << std::endl;*//*
        pid.savePidFunctions();
    }*/
    //				================================Writing in file======================================
    auto f_out = new TFile(out_file_name.c_str(), "recreate");
    pionPos_400.savePidFunctions();
    pionPos_700.savePidFunctions();

    /*for (auto pid : particlesPid) {
        pid->savePidFunctions();
    }*/
}