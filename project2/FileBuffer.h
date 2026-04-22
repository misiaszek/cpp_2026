#pragma once

#include <string>
#include <vector>

/**
 * Klasa FileBuffer (Kompozycja i RAII)
 * Zarządza danymi pojedynczego pliku.
 * Pokazuje: Konstruktory, Destruktor, Kopiowanie (cw3, cw7).
 */
class FileBuffer {
private:
    std::string m_filename;
    char* m_data;
    size_t m_size;

public:
    FileBuffer(const std::string& filename);
    
    // Rule of Three (cw3)
    FileBuffer(const FileBuffer& other);
    FileBuffer& operator=(const FileBuffer& other);
    ~FileBuffer();

    // Gettery (const - cw7)
    const std::string& getFilename() const { return m_filename; }
    size_t getSize() const { return m_size; }
    const char* getData() const { return m_data; }

    void load(); // Wczytuje dane z dysku
};
