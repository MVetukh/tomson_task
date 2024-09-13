#include "Calculate/calculate_classes.h"
#include "Renderer/Renderer.h"
#include <iostream>



int main() {
    int n;
    std::cout << "Введите число точек на сфере: ";
    std::cin >> n;

    Simulation sim(n);
    sim.update_positions();

    

    Renderer renderer;
    if (!renderer.init(800, 600, "Charges Simulation")) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return -1;
    }

    // Получение позиций зарядов для отрисовки
    std::vector<std::array<double, 3>> points;
    for (const auto& charge : sim.charges) {
        points.push_back(charge.position);
    }

    // Запуск рендеринга
    renderer.render(points);

    return 0;
}