#include <random>
#include "Egg.h"
#include "Fly3D.h"

using namespace std;

Egg::Egg(Fly3D *mother, Fly3D *father) : mother(mother), father(father) {
    this->lr = (mother->GetLearningRate() + father->GetLearningRate()) / 2;
    this->max_ls = (mother->GetMaximumLearningStrength() + father->GetMaximumLearningStrength()) / 2;
    this->fecundity = (mother->GetFecundity() + father->GetFecundity()) / 2;
    this->speed = (mother->GetSpeed() + father->GetSpeed()) / 2;

}


Egg::Egg(const double &max_ls, const double &lr, const double &fecundity, const double &speed) : max_ls(max_ls), lr(lr),
                                                                                                 fecundity(fecundity),
                                                                                                 speed(speed) {
    this->mother = nullptr;
    this->father = nullptr;
}

double Egg::GetMaximumLearningStrength() const { return this->max_ls; }

double Egg::GetLearningRate() const { return this->lr; }

double Egg::GetFecundity() const { return this->fecundity; }

double Egg::GetSpeed() const { return this->speed; }

void Egg::SetMaximumLearningStrength(double &max_ls) { this->max_ls = max_ls; }

void Egg::SetLearningRate(const double &lr) { this->lr = lr; }

void Egg::SetFecundity(const double &fecundity) { this->fecundity = fecundity; }

void Egg::SetSpeed(const double &speed) { this->speed = speed; }

void SetGenotype(const std::vector<int> &genotype);

Fly3D *Egg::GetMother() { return this->mother; }