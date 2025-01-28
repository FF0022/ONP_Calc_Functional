#include "ONP.h"
#include <stack>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <fstream>

// Wczytuje wyra¿enia z pliku
std::vector<std::string> wczytDzial(const std::string& inputFilePath) {
    std::ifstream inputFile(inputFilePath);
    if (!inputFile) throw std::runtime_error("Nie mo¿na otworzyæ pliku wejœciowego.");

    std::vector<std::string> expressions;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (!line.empty()) expressions.push_back(line);
    }

    return expressions;
}

// Zapisuje wyra¿enia do pliku
void zapisWyr(const std::string& outputFilePath, const std::vector<std::string>& expressions) {
    std::ofstream outputFile(outputFilePath);
    if (!outputFile) throw std::runtime_error("Nie mo¿na otworzyæ pliku wyjœciowego.");

    for (const auto& expr : expressions) {
        outputFile << expr << "\n";
    }
}

// Zapisuje wartoœci do pliku
void zapisWart(const std::string& outputFilePath, const std::vector<double>& values) {
    std::ofstream outputFile(outputFilePath);
    if (!outputFile) throw std::runtime_error("Nie mo¿na otworzyæ pliku wyjœciowego.");

    for (const auto& value : values) {
        outputFile << value << "\n";
    }
}

// Funkcja sprawdzaj¹ca, czy ci¹g znaków to liczba
bool isDigit(const std::string& znak) {
    for (char c : znak) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

// Sprawdza, czy znak jest operatorem
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Porównuje priorytety operatorów ze sob¹ 
bool porownaniePriorytetu(char op1, char op2) {
    auto priorytet = [](char op) -> int {
        if (op == '^') return 3;
        if (op == '*' || op == '/') return 2;
        if (op == '+' || op == '-') return 1;
        return 0;
        };

    // Zwraca priorytet operatora wzglêdem innego z nim porównywanego
    return priorytet(op1) > priorytet(op2) ||
        (priorytet(op1) == priorytet(op2) && op1 != '^');
        // Wyj¹tkiem jest Potêgowanie, symbolizowane znakiem ^
}

// Konwersja wyra¿enia infiksowego na ONP
std::string infixToRPN(const std::string& expression) {
    std::stack<char> operators;
    std::ostringstream output;
    std::istringstream input(expression);
    std::string znak;

    while (input >> znak) {
        if (isDigit(znak)) { // Liczba
            output << znak << " ";
        }
        else if (isOperator(znak[0])) { // Operator
            while (!operators.empty() && porownaniePriorytetu(operators.top(), znak[0])) {
                output << operators.top() << " ";
                operators.pop();
            }
            operators.push(znak[0]);
        }
        else if (znak[0] == '(') { // Lewy nawias
            operators.push(znak[0]);
        }
        else if (znak[0] == ')') { // Prawy nawias
            while (!operators.empty() && operators.top() != '(') {
                output << operators.top() << " ";
                operators.pop();
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        output << operators.top() << " ";
        operators.pop();
    }

    return output.str();
}

// Oblicza wartoœæ wyra¿enia w ONP
double evaluateRPN(const std::string& onpWyr) {
    std::stack<double> values;
    std::istringstream input(onpWyr);
    std::string znak;

    // Sprawdzamy wyra¿enie, znak po znaku
    while (input >> znak) {
        if (isDigit(znak)) { // Liczba, wrzucamy na stos liczb
            values.push(std::stod(znak));
        }
        else if (isOperator(znak[0])) { // Operator
            if (values.size() < 2) {
                throw std::runtime_error("Z³e wyra¿enie. Za ma³a iloœæ wartoœci w stsunku do operatorów");
            }
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();

            switch (znak[0]) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/':
                if (b == 0) throw std::runtime_error("Dzielenie przez zero");
                values.push(a / b);
                break;
            case '^': values.push(std::pow(a, b)); break;
            }
        }
    }

    return values.top();
}