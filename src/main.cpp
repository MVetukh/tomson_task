#include "Calculate/calculate_classes.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <chrono>



int main() {
    int n;
    std::cout << "Enter number of points: ";
    std::cin >> n;

    auto start = std::chrono::high_resolution_clock::now();

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

    // Окончание измерения времени
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисление времени выполнения
    std::chrono::duration<double> duration = end - start;
    std::cout << "Runtime: " << duration.count() << " seconds\n";

    return 0;
}