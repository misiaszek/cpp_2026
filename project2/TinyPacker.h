#pragma once

#include "Packer.h"
#include <array>

/**
 * Klasa TinyPacker (cw8)
 * Dziedziczy po Packer i implementuje specyficzny format zapisu.
 * Pokazuje: Nadpisywanie metod wirtualnych.
 */
class TinyPacker : public Packer {
private:
    static constexpr std::array<char, 4> MAGIC = {'T', 'P', 'K', '2'};

public:
    // Wywolanie konstruktora klasy bazowej (cw8)
    TinyPacker(const std::string& archiveName);

    // Przesloniecie metody klasy bazowej (cw8)
    void save(); 
};
