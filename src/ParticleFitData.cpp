//
// Created by User on 20.12.2023.
//

#include <TF1.h>

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

class ParticleFitData{
private:
    ParticleParameters particleParameters;
    ParticleCurrParameters particleCurrParameters;
    TF1 * particlesFunction;
    std::string name;
public:
    ParticleFitData(TF1* amplitude, TF1* mean, TF1* sigma){
        this->particleParameters.amplitude = amplitude;
        this->particleParameters.mean = mean;
        this->particleParameters.sigma = sigma;
    }
};