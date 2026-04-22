#include <iostream>
#include <stdexcept>
#include "TinyPacker.h"

/**
 * PROJECT 2: ADVANCED TINY PACKER (Multi-file)
 * ------------------------------------------
 * Wykorzystuje techniki z Laboratoriow 1 - 8.
 */
int main() {
    std::cout << "--- Advanced TinyPacker v2.0 ---\n\n";

    try {
        // 1. Tworzymy obiekt klasy pochodnej (cw8)
        TinyPacker myPacker("project2_archive.tpk");

        // 2. Dodajemy pliki (wykorzystuje FileBuffer i load())
        // Dodamy same siebie jako test
        myPacker.addFile("FileBuffer.h");
        myPacker.addFile("Packer.h");
        myPacker.addFile("TinyPacker.h");

        // 3. Wypisujemy statystyki (metoda klasy bazowej)
        myPacker.printStats();

        // 4. Zapisujemy (metoda nadpisana)
        myPacker.save();

        std::cout << "\nSukces! Archiwum zostalo utworzone.\n";

    } catch (const std::exception& e) {
        // Obsluga wyjatkow (cw6)
        std::cerr << "\n[KRYTYCZNY BLAD]: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
