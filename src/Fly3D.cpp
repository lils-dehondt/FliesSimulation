#include <iostream>
#include <random>

#include "Fly3D.h"

using namespace std;

Fly3D::Fly3D(const Vector3d<double> &position, const int &index, Arena3D *arena) : female(false), r(position),
                                                                                   v(Vector3d<double>(0, 0, 0)),
                                                                                   v_pref(Vector3d<double>(0, 0, 0)),
                                                                                   a(Vector3d<double>(0, 0, 0)),
                                                                                   angle(0.0), index(index),
                                                                                   arena(arena),
                                                                                   room(arena->GetRoomFromPosition(
                                                                                           position)),
                                                                                   Fint(Vector3d<double>(0, 0, 0)),
                                                                                   Ffric(Vector3d<double>(0, 0, 0)),
                                                                                   Fres(Vector3d<double>(0, 0, 0)),
                                                                                   Fnoise(Vector3d<double>(0, 0, 0)),
                                                                                   rcog(100.0), timeonfood(0.0),
                                                                                   lr(0.2), ls(0.0), fecundity(5),
                                                                                   max_ls(0.8), aimTimer(0),
                                                                                   nb_successes(0), rep_timer(0),
                                                                                   speed(1.0) {

    this->GenerateNewAim();
}

Fly3D::Fly3D(const bool &female, const double &x, const double &y, const double &z, const int &index, Arena3D *arena)
        : female(female),
          r(Vector3d<double>(
                  x, y, z)),
          v(Vector3d<double>(
                  0, 0, 0)),
          v_pref(Vector3d<double>(
                  0, 0, 0)),
          a(Vector3d<double>(
                  0, 0, 0)),
          angle(0.0),
          index(index),
          arena(arena),
          room(arena->GetRoomFromPosition(
                  x, y, z)),
          Fint(Vector3d<double>(
                  0, 0, 0)),
          Ffric(Vector3d<double>(
                  0, 0, 0)),
          Fres(Vector3d<double>(
                  0, 0, 0)),
          Fnoise(Vector3d<double>(
                  0, 0, 0)),
          rcog(100.0),
          timeonfood(0.0),
          lr(0.2), ls(0.0),
          fecundity(5),
          max_ls(0.8),
          aimTimer(0),
          nb_successes(0),
          speed(1.0) {

    this->GenerateNewAim();
}


Fly3D::Fly3D(const bool &female, const int &room, const int &index, Arena3D *arena, const double &lr,
             const double &max_ls, const int &fecundity, const int &rep_time, const double &speed,
             const std::vector<int> &genotype) : female(female), v(Vector3d<double>(0, 0, 0)),
                                                 v_pref(Vector3d<double>(0, 0, 0)), a(Vector3d<double>(0, 0, 0)),
                                                 angle(0.0),
                                                 index(index), arena(arena), Fint(Vector3d<double>(0, 0, 0)),
                                                 Ffric(Vector3d<double>(0, 0, 0)), Fres(Vector3d<double>(0, 0, 0)),
                                                 Fnoise(Vector3d<double>(0, 0, 0)), rcog(100.0), timeonfood(0.0),
                                                 lr(lr),
                                                 ls(0.0), max_ls(max_ls), fecundity(fecundity), aimTimer(0),
                                                 nb_successes(0), nb_egg_layings(0), rep_time(rep_time), rep_timer(0),
                                                 speed(speed) {

    if (this->arena != nullptr && room < this->arena->GetNbWalls() && room >= 0) {
        r = this->arena->GetRoomCenter(room);
        this->room = room;
    }
    this->GenerateNewAim();


}

bool Fly3D::GetFemale() const { return this->female; }

int Fly3D::GetRoom() const { return this->room; }


double Fly3D::GetAngle() const { return this->angle; }

Vector3d<double> Fly3D::GetPosition() const { return this->r; }

double Fly3D::GetLearningStrength() const { return this->ls; }

double Fly3D::GetMaximumLearningStrength() const { return this->max_ls; }

double Fly3D::GetLearningRate() const { return this->lr; }

Vector3d<double> Fly3D::GetVelocity() const { return this->v; }

Vector3d<double> Fly3D::GetVelocitypref() const { return this->v_pref; }

Vector3d<double> Fly3D::GetFres() const { return this->Fres; }

Vector3d<double> Fly3D::GetAim() const { return this->aim; }

double Fly3D::GetSpeed() const { return this->speed; }

int Fly3D::GetNbSuccesses() { return this->nb_successes; }

int Fly3D::GetNbEggLayings() { return this->nb_egg_layings; }

int Fly3D::GetFecundity() { return this->fecundity; }

void Fly3D::SetAim(const Vector3d<double> &point) { this->aim = point; }

void Fly3D::SetAim(const double &x, const double &y, const double &z) { this->aim = Vector3d<double>(x, y, z); }


void Fly3D::GenerateNewAim() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::normal_distribution<double> Gauss(0.0, 50.0); //or rcog/2
    std::uniform_real_distribution<double> Uniform(-rcog, rcog);
    std::uniform_real_distribution<double> Unit(0, 1);
    Vector3d<double> dr;
    if (arena->OnFood(room)) { aim = arena->GetRoomCenter(room); }
    else {
        Vector3d<double> entrancePos =
                0.95 * arena->GetEntranceCenterFromPosition(r) + 0.05 * arena->GetRoomCenter(room);
        //-----------
        if (aim == entrancePos) {
            if (EuclideanNorm(r - aim) < 4) {
                aim = 0.9 * arena->GetEntranceCenterFromPosition(r) + 0.1 * arena->GetRoomCenter(room + 1);
            }
        }
            //------------
        else {
            do {
                double x(Uniform(gen));
                double y(Uniform(gen));
                double z(Uniform(gen));
                dr = Vector3d<double>(x, y, z);
            } while (EuclideanNorm((r + dr) - arena->GetCenter()) > arena->GetRadius() && EuclideanNorm(dr) < rcog);
            this->aim = r + dr;

        }
    }
    double distance = EuclideanNorm(r - aim);

    double velocity_norm = EuclideanNorm(v);

    aimTimer = (int) (2 * std::ceil(distance / (this->speed * velocity_norm)));
}

void Fly3D::UpdateAim(const double &dt) {
    if (EuclideanNorm(r - aim) <= EuclideanNorm(v) * dt * 2.5 || EuclideanNorm(r - aim) > rcog || this->aimTimer < 0) {
        this->GenerateNewAim();
        this->aimTimer = (int) (std::ceil(this->aimTimer / dt));
    }
}

void Fly3D::Update(const double &dt) {
    // Update reponse to environment
    this->UpdateFres();
    // Update preferred velocity
    this->UpdateVpref(dt);
    // Update velocity
    this->UpdateV(dt);
    // Update angle
    this->UpdateAngle();
    // Update position
    this->UpdatePosition(dt);
    // Update aim
    this->UpdateAim(dt);

    this->UpdateAimTimer();

    this->UpdateNbSuccesses();




    // This line has to be before updating the room, else it won't work!
    this->UpdateLearningStrength();

    //-----------------

    // Update room of fly
    this->UpdateRoom();
    // Update time of food
    this->UpdateTimeOmFood(dt);

    this->UpdateRepTimer();
}

void Fly3D::UpdateAimTimer() {
    this->aimTimer -= 1;
}

void Fly3D::UpdateLearningStrength() {
    bool success = this->Success();
    if (success) {
        int newroom = arena->GetRoomFromPosition(r);
        if (arena->OnFood(newroom)) {
            this->ls = this->ls + this->lr * (this->max_ls - this->ls);
            if (female && rep_timer == 0) {
                nb_egg_layings += 1;
                rep_timer = rep_time;
            }

        }
    }
}

void Fly3D::UpdateAngle() {
    if (this->v != Vector3d<double>(0.0, 0.0, 0.0)) {
        Vector3d<double> orient(this->r + this->v);
        Vector3d<double> uvec(1.0, 0.0, 0.0);
        uvec += this->r;
        this->angle = atan2(this->v.y, this->v.x);
    }

}

void Fly3D::UpdateFres() {
    Vector3d<double> rie(aim - r);
    // Fres = Xres * H(rcog - |rie|) * (se * rie/|rie| * R(n, theta) - (1 - se) * rie / |rie|)
    if (arena->OnFood(room)) {
        double rcog_ = 1000.0;
        Fres = 10.0 * std::max(0.0, (rcog_ - EuclideanNorm(rie)) / fabs(rcog_ - EuclideanNorm(rie))) *
               (rie / EuclideanNorm(rie));

    } else {

        Vector3d<double> entrancePos =
                0.95 * arena->GetEntranceCenterFromPosition(r) + 0.05 * arena->GetRoomCenter(room);
        Vector3d<double> rie_entrance(entrancePos - r);


        Vector3d<double> Fres_entrance = (female && !(arena->GetWallFromPosition(r)->PointIsInside(r))) ? 100 *
                                                                                                          std::max(0.0,
                                                                                                                   (rcog -
                                                                                                                    EuclideanNorm(
                                                                                                                            rie_entrance)) /
                                                                                                                   fabs(rcog -
                                                                                                                        EuclideanNorm(
                                                                                                                                rie_entrance))) *
                                                                                                          (rie_entrance /
                                                                                                           EuclideanNorm(
                                                                                                                   rie_entrance))
                                                                                                        : Vector3d<double>(
                        0.0, 0.0, 0.0);
        Fres = 100 * std::max(0.0, (rcog - EuclideanNorm(rie)) / fabs(rcog - EuclideanNorm(rie))) *
               (rie / EuclideanNorm(rie)) + Fres_entrance;
        if (Fres == Vector3d<double>(0.0, 0.0, 0.0)) {
        }
    }
}

void Fly3D::UpdateVpref(const double &dt) {
    v_pref = v + Fres * dt;
    // If v_pref norm exceeds max observed fly speed
    // if(EuclideanNorm(v_pref) > 25) v_pref *= 25 / EuclideanNorm(v_pref);
}

void Fly3D::UpdateV(const double &dt) {
    v = v_pref;
    // If v_pref norm exceeds max observed fly speed
    if (EuclideanNorm(v) > 25) v *= 25 / EuclideanNorm(v);
}

void Fly3D::UpdatePosition(const double &dt) {
    Vector3d<double> new_r(r + v * dt * this->speed);
    if (arena->AllowMove(r, new_r)) { r = new_r; }
    else if (arena->OnFood(room)) { GenerateNewAim(); }
    else { GenerateNewAim(); }
}

void Fly3D::UpdateRoom() { room = arena->GetRoomFromPosition(r); }

void Fly3D::UpdateNbSuccesses() {
    if (this->Success()) {
        nb_successes += 1;
    }
}

bool Fly3D::Success() {
    int newroom = arena->GetRoomFromPosition(r);
    if (room != newroom) {
        return true;

    } else { return false; }
}

double Fly3D::GetTimeOnFood() const { return timeonfood; }

void Fly3D::UpdateTimeOmFood(const double &dt) {
    if (arena->OnFood(room)) { timeonfood += dt; }
}

void Fly3D::UpdateRepTimer() {
    if (rep_timer != 0) {
        rep_timer -= 1;
    }
}
