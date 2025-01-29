#include "ONP.h"
#include <iostream>
#include <vector>
#include <string>

void instrukcja() {
    std::cout << "Użycie: ONP_calc.exe -i <plik_wejściowy> -o <plik_ONP> -w <plik_z_wynikami>\n";
}

int main(int argc, char* argv[]) {
    //Sprawdzamy czy 
    if (argc != 7) {
        instrukcja();
        return 1;
    }

    std::string inputFile, outputONPFile, outputValuesFile;

    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "-i") inputFile = argv[i + 1];
        else if (arg == "-o") outputONPFile = argv[i + 1];
        else if (arg == "-w") outputValuesFile = argv[i + 1];
        else {
            instrukcja();
            return 1;
        }
    }

    try {
        auto expressions = wczytDzial(inputFile);
        std::vector<std::string> rpnExpressions;
        std::vector<double> results;

        for (const auto& wyr : expressions) {
            std::string onp = wyrnaONP(wyr);
            double result = obliczONP(onp);
            rpnExpressions.push_back(rpn);
            results.push_back(result);
        }

        zapisWyr(outputONPFile, rpnExpressions);
        zapisWart(outputValuesFile, results);

    }
    catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
