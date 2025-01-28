#pragma once
#include <string>
#include <vector>

// Funkcje do obs³ugi plików
std::vector<std::string> wczytDzial(const std::string& inputFilePath);
void zapisWyr(const std::string& outputFilePath, const std::vector<std::string>& expressions);
void zapisWart(const std::string& outputFilePath, const std::vector<double>& values);

// Funkcje do konwersji i obliczeñ
std::string wyrnaONP(const std::string& wyr);
double obliczONP(const std::string& onpWyr);
