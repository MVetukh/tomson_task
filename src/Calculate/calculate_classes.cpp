//
// Created by Max on 10.09.2024.
//

#include "calculate_classes.h"

// Реализация конструктора класса Charge
Charge::Charge() {
    double x = random_double(-1.0, 1.0);
    double y = random_double(-1.0, 1.0);
    double z = random_double(-1.0, 1.0);
    double r = std::sqrt(x * x + y * y + z * z);
    position = { x / r * R, y / r * R, z / r * R };
}

// Реализация метода calculate_force класса Charge
std::array<double, 3> Charge::calculate_force(const Charge& other) const {
    double r = std::sqrt(
            std::pow(position[0] - other.position[0], 2) +
            std::pow(position[1] - other.position[1], 2) +
            std::pow(position[2] - other.position[2], 2)
    );

    double F = (k * e * e) / (r * r);

    std::array<double, 3> direction = {
            (other.position[0] - position[0]) * (-1),
            (other.position[1] - position[1]) * (-1),
            (other.position[2] - position[2]) * (-1)
    };

    return { direction[0] * F, direction[1] * F, direction[2] * F };
}

// Реализация метода random_double класса Charge
double Charge::random_double(double min, double max) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

// Реализация конструктора класса Simulation
Simulation::Simulation(int n) {
    charges.resize(n);
}

// Реализация метода calculate_energy класса Simulation
double Simulation::calculate_energy() const {
    double W = 0.0;
    for (size_t i = 0; i < charges.size() - 1; ++i) {
        for (size_t j = i + 1; j < charges.size(); ++j) {
            double r = std::sqrt(
                    std::pow(charges[i].position[0] - charges[j].position[0], 2) +
                    std::pow(charges[i].position[1] - charges[j].position[1], 2) +
                    std::pow(charges[i].position[2] - charges[j].position[2], 2)
            );
            W += k * e * e / r;
        }
    }
    return W;
}

// Реализация метода update_positions класса Simulation
void Simulation::update_positions() {
    double W = 1, W0 = 0;
    while (std::abs(W - W0) > 1e-6) {
        W0 = calculate_energy();
        for (size_t i = 0; i < charges.size(); ++i) {
            std::array<double, 3> resultant_force = { 0.0, 0.0, 0.0 };
            for (size_t j = 0; j < charges.size(); ++j) {
                if (i != j) {
                    auto force = charges[i].calculate_force(charges[j]);
                    resultant_force[0] += force[0];
                    resultant_force[1] += force[1];
                    resultant_force[2] += force[2];
                }
            }

            // Обновление позиции на основе силы
            for (int k = 0; k < 3; ++k) {
                charges[i].position[k] += resultant_force[k];
            }

            // Нормализация позиции
            double r = std::sqrt(
                    std::pow(charges[i].position[0], 2) +
                    std::pow(charges[i].position[1], 2) +
                    std::pow(charges[i].position[2], 2)
            );
            for (int k = 0; k < 3; ++k) {
                charges[i].position[k] = (charges[i].position[k] / r) * R;
            }
        }
        W = calculate_energy();
    }
}

// Реализация метода print_positions класса Simulation
void Simulation::print_positions() const {
    for (const auto& charge : charges) {
        std::cout << "Position: ("
                  << charge.position[0] << ", "
                  << charge.position[1] << ", "
                  << charge.position[2] << ")\n";
    }
}

