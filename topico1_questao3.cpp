#include <iostream>
#include <vector>
#include <cmath>

using matriz = std::vector<std::vector<double>>;
char materiais[][16]{
    "areia",
    "cascalho fino",
    "cascalho grosso"
};

std::vector<double> add_mina() {
    static int num_mina(1);
    std::vector<double> mina(3);
    for (auto& material : mina) {
        std::cout << "\nInforme a proporcao de " << materiais[&material - &mina[0]] << " da mina " << num_mina << " (em porcentagem)\n";
        std::cin >> material;
        material /= 100;
    }
    num_mina++;
    return mina;
}

std::vector<double> add_materiais() {
    std::vector<double> materiais(3);
    for (auto& material : materiais) {
        std::cout << "\nInforme a quantidade necessaria de " << ::materiais[&material - &materiais[0]] << " para a construcao\n";
        std::cin >> material;
    }
    return materiais;
}

void print_sistema(matriz& sistema) {
    std::cout << "\n\n";
    for (auto& mina : sistema) {
        for (auto& material : mina) {
            if(&material != &mina.back()) {
                std::cout << material << char('x' + &material - &mina[0]) << ' ';
                continue;
            }
            std::cout << "= " << material << '\n';
        }
    }
}

void print_result(std::vector<double>& v) {
    std::cout << "\nA quantidade necessaria, em metros cubicos, a ser minerada em cada mina é:\n\n";
    for (auto& res : v) {
        auto i = &res - &v[0];
        std::cout << "Mina " << (i + 1) << " = " << res << " m3\n";
    }
}

void transposta(matriz& m) {
    matriz tmp;
    for (size_t x = 0; x < m[0].size(); x++) {
        std::vector<double> l;
        for (size_t y = 0; y < m.size(); y++) {
            l.push_back(m[y][x]);
        }
        tmp.push_back(l);
    }
    std::swap(m, tmp);
}



void gauss_pivot(matriz& m) {
    for (size_t y = 0; y < m.size() - 1; y++) {
        for (size_t x = y + 1; x < m.size(); x++) {
            if(std::abs(m[x][y]) > std::abs(m[y][y])) {
               std::swap(m[x], m[y]);
            }
        }
        for (size_t x = y + 1; x < m.size(); x++) {
            double razao(m[x][y] / m[y][y]);
            for (size_t yy = 0; yy < m[x].size(); yy++) {
                m[x][yy] -= (razao * m[y][yy]);
            }
        }
    }
}

std::vector<double> resolver_sistema(matriz m) {
    std::vector<double> result(m.size());
    for (int x = m.size() - 1; x >= 0; x--) {
        for (size_t y = x + 1; y < m[x].size() - 1; y++) {
            m[x].back() -= (m[x][y] * m[y].back());
        }
        result[x] = m[x].back() /= m[x][x];
    }
    return result;
}

int main() {
    matriz sistema{
        add_mina(),
        add_mina(),
        add_mina(),
        add_materiais()
    };
    transposta(sistema);
    std::cout << "\nSistema Linear:";
    print_sistema(sistema);
    gauss_pivot(sistema);
    std::cout << "\nSistema Linear Triangular:";
    print_sistema(sistema);
    auto result = resolver_sistema(sistema);
    print_result(result);
    return 0;
}
