#pragma once

#include <vector>
#include <string>
#include "FileBuffer.h"

/**
 * Klasa bazowa Packer (cw8)
 * Definiuje ogolna logike archiwizacji.
 */
class Packer {
protected:
    std::vector<FileBuffer> m_files; // Kompozycja (cw6)
    std::string m_archiveName;

public:
    Packer(const std::string& archiveName);
    ~Packer() = default; // zwykly destruktor (cw7/8)

    void addFile(const std::string& filename);
    
    // Metoda do zdefiniowania w klasach pochodnych (cw8)
    void save(); 

    // Metoda pomocnicza wypisujaca statystyki
    void printStats() const;
};
