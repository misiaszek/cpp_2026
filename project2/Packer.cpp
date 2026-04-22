#include "Packer.h"
#include <iostream>
#include <iomanip>

Packer::Packer(const std::string& archiveName) 
    : m_archiveName(archiveName) {
}

void Packer::addFile(const std::string& filename) {
    FileBuffer fb(filename);
    fb.load(); // Moze rzucic wyjatek (cw6)
    m_files.push_back(fb); // (cw5)
    std::cout << "[PACKER] Dodano plik: " << filename << " (" << fb.getSize() << " bajtow)\n";
}

void Packer::save() {
    std::cout << "[PACKER] Metoda save() klasy bazowej - nic nie robie.\n";
}

void Packer::printStats() const {
    size_t totalSize = 0;
    std::cout << "\n--- Statystyki Archiwum: " << m_archiveName << " ---\n";
    std::cout << std::left << std::setw(20) << "Plik" << " | " << std::right << std::setw(10) << "Rozmiar" << "\n";
    std::cout << std::string(35, '-') << "\n";
    
    for (const auto& f : m_files) { // (cw4)
        std::cout << std::left << std::setw(20) << f.getFilename() 
                  << " | " << std::right << std::setw(10) << f.getSize() << " B\n";
        totalSize += f.getSize();
    }
    std::cout << std::string(35, '-') << "\n";
    std::cout << "Razem: " << m_files.size() << " plik(ow), " << totalSize << " B\n\n";
}
