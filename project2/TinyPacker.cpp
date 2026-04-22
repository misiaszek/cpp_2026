#include "TinyPacker.h"
#include <iostream>
#include <fstream>
#include <cstdint>

TinyPacker::TinyPacker(const std::string& archiveName) 
    : Packer(archiveName) { // Wywolanie konstruktora bazy (cw8)
}

void TinyPacker::save() {
    std::ofstream arc(this->m_archiveName, std::ios::binary); // uzycie this (cw7)
    if (!arc) {
        throw std::runtime_error("Nie mozna utworzyc archiwum: " + m_archiveName);
    }

    // Zapisz MAGIC (cw4/5)
    arc.write(MAGIC.data(), MAGIC.size());

    // Zapisz liczbe plikow (cw5)
    uint32_t count = static_cast<uint32_t>(m_files.size());
    arc.write(reinterpret_cast<char*>(&count), sizeof(count));

    // Zapisz naglowki (cw4/5)
    for (const auto& f : m_files) {
        char nameBuf[32] = {0};
        std::strncpy(nameBuf, f.getFilename().c_str(), 31);
        uint32_t size = static_cast<uint32_t>(f.getSize());
        
        arc.write(nameBuf, 32);
        arc.write(reinterpret_cast<char*>(&size), sizeof(size));
    }

    // Zapisz dane (RAII)
    for (const auto& f : m_files) {
        arc.write(f.getData(), f.getSize());
    }

    std::cout << "[TINYPACKER] Zapisano archiwum: " << m_archiveName << std::endl;
}
