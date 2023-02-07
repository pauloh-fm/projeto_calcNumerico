#include <iostream>
#include <vector>

struct Coordenadas {
    std::vector<double> x, y1, y2;
    double limiteInf, limiteSup;
};

double regra_trapezios_composta(std::vector<double> y, double h) {
    double area(0);
    size_t i;
    for (i = 1; i < y.size() - 1; i++) {
        area += 2 * y[i];
    }
    area += y[0] + y[i];
    area *= (h / 2);
    return area;
}

double regra_simpson_repetida(std::vector<double> y, double h) {
    double area(0);
    size_t i;
    for (i = 1; i < y.size() - 1; i++) {
        if(i & 1) {
            area += 4 * y[i];
        } else {
            area += 2 * y[i];
        }
    }
    area += y[0] + y[i];
    area *= (h / 3);
    return area;
}

double h_rio(Coordenadas rio) {
    int subIntervalos(0);
    for (auto x : rio.x) {
        if(x == rio.limiteInf || (subIntervalos && x != rio.limiteSup)) {
            subIntervalos++;
        } else if(x == rio.limiteSup) {
            break;
        }
    }
    if(!subIntervalos) {
        std::cout << "Erro - Intervalo Invalido\n";
        std::exit(1);
    }
    return (rio.limiteSup - rio. limiteInf) / subIntervalos;
}

std::vector<double> pontos_origem(unsigned int n_medidas) {
    std::vector<double> o(n_medidas);
    for (auto& x : o) {
        std::cout << "\nInforme a distancia da origem do rio ao ponto " << (&x - &o[0] + 1) << "\n";
        std::cin >> x;
    }
    return o;
}

std::vector<double> margem(unsigned int n_medidas) {
    static bool sup(false);
    std::vector<double> m(n_medidas);
    for (auto& y : m) {
        std::cout << "\nInforme a distancia da margem " << (sup ? "superior" : "inferior") << " do ponto " << (&y - &m[0] + 1) << " para o ponto de referencia\n";
        std::cin >> y;
    }
    sup = !sup;
    return m;
}

double limite() {
    static bool sup(false);
    double l;
    std::cout << "\nInforme o limite " << (sup ? "superior" : "inferior") << " do intervalo de integracao\n";
    std::cin >> l;
    sup = !sup;
    return l;
}

int main() {
    unsigned int n_medidas;
    std::cout << "\nInforme o numero de medidas coletada no rio\n";
    std::cin >> n_medidas;
    Coordenadas rio{
        .x = pontos_origem(n_medidas),
        .y1 = margem(n_medidas),
        .y2 = margem(n_medidas),
        .limiteInf = limite(),
        .limiteSup = limite()
    };
    double h = h_rio(rio);
    double area_por_trapezios = regra_trapezios_composta(rio.y2, h) - regra_trapezios_composta(rio.y1, h);
    double area_por_simpson = regra_simpson_repetida(rio.y2, h) - regra_simpson_repetida(rio.y1, h);
    std::cout << 
        "\nArea aproximada 1 = " << area_por_trapezios << " m2 (Regra dos Trapezios Composta)\n" << 
        "Area aproximada 2 = " << area_por_simpson << " m2 (Regra de 1/3 de Simpson Repetida)\n";
    return 0;
}
