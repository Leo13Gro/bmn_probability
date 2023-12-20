//
// Created by User on 15.11.2023.
//
#include <iostream>
#include <utility>
#include <vector>

#include <TH1F.h>
#include <TF1.h>
#include <TGraph.h>

#include "DrawingFunctions.cpp"

class Pid {
private:
    std::string name;
    TH2D* histo2d;
    std::vector<int> range;
    int step;
    std::vector<std::pair<double, double>> fit_ranges;
    std::pair<double, double> fit_range;
    bool are_different_ranges;
    void fit_pid_ranges() {
        int n = (range[1] - range[0]) / step;
        double amplitude[n];
        double mean[n];
        double sigma[n];
        double x[n];
        std::vector<TH1D*> proj_fit = YProjections(histo2d, range, n, x);

        auto f1 = new TF1("f1", "gaus");
        double par[3];
        for (int i = 0; i < n; i++) {
            proj_fit[i]->Fit("f1", "qL", "", fit_ranges[i].first, fit_ranges[i].second);
            f1->GetParameters(&par[0]);
            amplitude[i] = par[0];
            mean[i] = par[1];
            sigma[i] = par[2];
        }
        draw_vec(proj_fit, "bmn_hist/projections/" + name + "_", "E", 1);
        auto g_a = new TGraph(n, x, amplitude);
        g_a->Fit("f_a", "q", "");
        auto g_m = new TGraph(n, x, mean);
        g_m->Fit("f_m", "q", "");
        auto g_s = new TGraph(n, x, sigma);
        g_s->Fit("f_s", "q", "");
        auto c = new TCanvas("c", "c");
        g_a->Draw("ac*");
        c->SaveAs(("bmn_hist/parameters/amplitude_" + name + ".png").c_str());
        g_m->Draw("ac*");
        c->SaveAs(("bmn_hist/parameters/mean_" + name + ".png").c_str());
        g_s->Draw("ac*");
        c->SaveAs(("bmn_hist/parameters/sigma_" + name + ".png").c_str());
        delete c;
    }
    void selection_pid_ranges(const std::string& p_pol, const std::string& n_pol) {
        auto f_p = new TF1("f_p", p_pol.c_str());
        auto f_n = new TF1("f_n", n_pol.c_str());
        int n = (range[1] - range[0]) / step;
        double pos[n];
        double neg[n];
        double x[n];
        std::vector<TH1D*> proj_fit = YProjections(histo2d, range, n, x);
        auto f1 = new TF1("f1", "gaus");
        double par[3];
        for (int i = 0; i < n; i++) {
            proj_fit[i]->Fit("f1", "q", "", fit_ranges[i].first, fit_ranges[i].second);
            f1->GetParameters(&par[0]);
            pos[i] = par[1] + par[2];
            neg[i] = par[1] - par[2];
        }
        auto g_p = new TGraph(n, x, pos);
        g_p->Fit("f_p", "q", "");
        auto g_n = new TGraph(n, x, neg);
        g_n->Fit("f_n", "q", "");
        auto c = new TCanvas("c", "c");
        c->SetLogz(1);
        histo2d->Draw("colz");
        f_p->SetLineColor(kRed);
        f_n->SetLineColor(kBlue);
        f_p->DrawF1(0, 10, "same");
        f_n->DrawF1(0, 10, "same");
        c->SaveAs(("bmn_hist/selection/" + name + ".png").c_str());
        delete c;
    }
    void fit_pid_range() {
        int n = (range[1] - range[0]) / step;
        double amplitude[n];
        double mean[n];
        double sigma[n];
        double x[n];
        std::vector<TH1D*> proj_fit = YProjections(histo2d, range, n, x);

        auto f1 = new TF1("f1", "gaus");
        double par[3];
        for (int i = 0; i < n; i++) {
            proj_fit[i]->Fit("f1", "q", "", fit_range.first, fit_range.second);
            f1->GetParameters(&par[0]);
            amplitude[i] = par[0];
            mean[i] = par[1];
            sigma[i] = par[2];
        }
        draw_vec(proj_fit, "bmn_hist/projections/" + name + "_", "E", 1);
        auto g_a = new TGraph(n, x, amplitude);
        g_a->Fit("f_a", "q", "");
        auto g_m = new TGraph(n, x, mean);
        g_m->Fit("f_m", "q", "");
        auto g_s = new TGraph(n, x, sigma);
        g_s->Fit("f_s", "q", "");
        auto c = new TCanvas("c", "c");
        g_a->Draw("ac*");
        c->SaveAs(("bmn_hist/parameters/amplitude_" + name + ".png").c_str());
        g_m->Draw("ac*");
        c->SaveAs(("bmn_hist/parameters/mean_" + name + ".png").c_str());
        g_s->Draw("ac*");
        c->SaveAs(("bmn_hist/parameters/sigma_" + name + ".png").c_str());
        delete c;
    }
    void selection_pid_range(std::string p_pol, std::string n_pol) {
        auto f_p = new TF1("f_p", p_pol.c_str());
        auto f_n = new TF1("f_n", n_pol.c_str());
        int n = (range[1] - range[0]) / step;
        double pos[n];
        double neg[n];
        double x[n];
        std::vector<TH1D*> proj_fit = YProjections(histo2d, range, n, x);
        auto f1 = new TF1("f1", "gaus");
        double par[3];
        for (int i = 0; i < n; i++) {
            proj_fit[i]->Fit("f1", "q", "", fit_range.first, fit_range.second);
            f1->GetParameters(&par[0]);
            pos[i] = par[1] + par[2];
            neg[i] = par[1] - par[2];
        }
        auto g_p = new TGraph(n, x, pos);
        g_p->Fit("f_p", "q", "");
        auto g_n = new TGraph(n, x, neg);
        g_n->Fit("f_n", "q", "");
        auto c = new TCanvas("c", "c");
        c->SetLogz(1);
        histo2d->Draw("colz");
        f_p->SetLineColor(kRed);
        f_n->SetLineColor(kBlue);
        f_p->DrawF1(0, 10, "same");
        f_n->DrawF1(0, 10, "same");
        c->SaveAs(("bmn_hist/selection/" + name + ".png").c_str());
        delete c;
    }
    std::string m_pol;
public:
    TF1* f_a;
    TF1* f_m;
    TF1* f_s;

    Pid(std::string name, std::string a_pol, std::string m_pol, std::string s_pol, TH2D* histo2d, std::vector<int> range, int step, std::vector<std::pair<double, double>> fit_ranges) {
        this->m_pol = m_pol;
        this->name = std::move(name);
        f_a = new TF1("f_a", a_pol.c_str());
        f_m = new TF1("f_m", m_pol.c_str());
        f_s = new TF1("f_s", s_pol.c_str());
        this->histo2d = histo2d;
        this->range = range;
        this->step = step;
        this->fit_ranges = fit_ranges;
        are_different_ranges = true;
        fit_pid();
    };
    Pid(std::string name, std::string a_pol, std::string m_pol, std::string s_pol, TH2D* histo2d, std::vector<int> range, int step, std::pair<double, double> fit_range) {
        this->m_pol = m_pol;
        this->name = std::move(name);
        f_a = new TF1("f_a", a_pol.c_str());
        f_m = new TF1("f_m", m_pol.c_str());
        f_s = new TF1("f_s", s_pol.c_str());
        this->histo2d = histo2d;
        this->range = range;
        this->step = step;
        this->fit_range = fit_range;
        are_different_ranges = false;
        fit_pid();
    };
    void fit_pid(){
        if (are_different_ranges)
            fit_pid_ranges();
        else fit_pid_range();
    }
    // Mean + Sigma: Red Graph, Mean - Sigma: Blue graph
    void selection_pid(std::string p_pol, std::string n_pol){
        if (are_different_ranges)
            selection_pid_ranges(p_pol, n_pol);
        else selection_pid_range(p_pol, n_pol);
    }
    void selection_pid(){ selection_pid(m_pol, m_pol); }
    void savePidFunctions(){
        f_a->Write((name + "_amplitude").c_str());
        f_m->Write((name + "_mean").c_str());
        f_s->Write((name + "_sigma").c_str());
    }
};