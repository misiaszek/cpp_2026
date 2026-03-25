#include <iostream>
#include <fstream>
#include <array>
#include <string_view>
#include <iomanip>
#include <ctime>

/**
 * PROJEKT 1: TINY PACKER (v1.0)
 * ----------------------------
 * Przykład praktycznego zastosowania mechanizmów C++ (Lab 1-4).
 * 
 * Program demonstruje:
 * - RAII: Automatyczne zarządzanie cyklem życia zasobów (buforów danych).
 * - SINGLETON: Centralny punkt zarządzania logowaniem zdarzeń.
 * - GŁĘBOKA KOPIA: Poprawna obsługa zasobów dynamicznych w konstruktorze kopiującym.
 * - KONTENERY STL: Użycie std::array do definiowania stałych struktur binarnych.
 * - PRZYJAŹŃ I STRUMIENIE: Przeciążanie operatora << dla czytelnej wizualizacji danych.
 */

// Centralny system logowania zdarzeń (Wzorzec Singleton)
class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    void info(std::string_view msg) {
        std::cout << "[INFO]: " << msg << std::endl;
    }
    void error(std::string_view msg) {
        std::cerr << "[ERROR]: " << msg << std::endl;
    }
private:
    Logger() = default; 
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

// Klasa zarządzająca buforem pamięci dla danych pliku (Przykład RAII i Głębokiej Kopii)
class DataBuffer {
    char* m_data;
    size_t m_size;

public:
    DataBuffer() : m_data{nullptr}, m_size{0} {}
    
    DataBuffer(size_t size) : m_size{size} {
        m_data = new char[m_size];
    }

    // Konstruktor kopiujący realizujący głęboką kopię (Deep Copy)
    DataBuffer(const DataBuffer& other) : m_size{other.m_size} {
        if (other.m_data) {
            m_data = new char[m_size];
            for (size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
        } else {
            m_data = nullptr;
        }
    }

    // Operator przypisania (Zasada Trzech)
    DataBuffer& operator=(const DataBuffer& other) {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_data = new char[m_size];
            for (size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
        }
        return *this;
    }

    // Destruktor zwalniający pamięć
    ~DataBuffer() {
        delete[] m_data;
    }

    char* data() { return m_data; }
    size_t size() const { return m_size; }
};

// Struktura metadanych zapisywana bezpośrednio w nagłówku archiwum
struct FileMetadata {
    char name[32];
    uint32_t size;
};

// Klasa główna archiwizatora
class TinyArchive {
private:
    // Magic Number identyfikujący format pliku
    static constexpr std::array<char, 4> MAGIC = {'T', 'P', 'A', 'K'};
    
    static const size_t MAX_FILES = 5;
    std::array<FileMetadata, MAX_FILES> m_entries;
    std::array<DataBuffer, MAX_FILES> m_buffers;
    size_t m_fileCount = 0;

public:
    TinyArchive() = default;

    // Metoda dodająca plik do archiwum (wykorzystuje niskopoziomowe API C dla plików)
    bool addFile(const std::string& filename) {
        if (m_fileCount >= MAX_FILES) {
            Logger::getInstance().error("Archive capacity exceeded.");
            return false;
        }

        FILE* f = fopen(filename.c_str(), "rb");
        if (!f) {
            Logger::getInstance().error("Unable to open source file: " + filename);
            return false;
        }

        // Wyznaczenie rozmiaru pliku
        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);
        fseek(f, 0, SEEK_SET);

        // Alokacja bufora i odczyt danych
        DataBuffer buf(size);
        fread(buf.data(), 1, size, f);
        fclose(f);

        // Zapis metadanych pliku
        FileMetadata& meta = m_entries[m_fileCount];
        for (size_t i = 0; i < 31 && i < filename.length(); ++i) meta.name[i] = filename[i];
        meta.name[31] = '\0';
        meta.size = static_cast<uint32_t>(size);

        m_buffers[m_fileCount] = buf; 
        m_fileCount++;

        Logger::getInstance().info("File added to archive structure: " + filename);
        return true;
    }

    // Zapis struktury do pliku binarnego na dysku
    void save(const std::string& archiveName) {
        FILE* f = fopen(archiveName.c_str(), "wb");
        if (!f) return;

        // 1. Zapis sygnatury formatu
        fwrite(MAGIC.data(), 1, MAGIC.size(), f);

        // 2. Zapis liczby plików
        uint32_t count = static_cast<uint32_t>(m_fileCount);
        fwrite(&count, sizeof(count), f);

        // 3. Zapis tabeli metadanych
        for (size_t i = 0; i < m_fileCount; ++i) {
            fwrite(&m_entries[i], sizeof(FileMetadata), f);
        }

        // 4. Zapis surowych danych plików
        for (size_t i = 0; i < m_fileCount; ++i) {
            fwrite(m_buffers[i].data(), 1, m_buffers[i].size(), f);
        }

        fclose(f);
        Logger::getInstance().info("Archive successfully saved to disk: " + archiveName);
    }

    // Deklaracja przyjaciela umożliwiająca wizualizację stanu obiektu
    friend std::ostream& operator<<(std::ostream& os, const TinyArchive& arc) {
        os << "\n--- Memory State: Archive Entries ---\n";
        os << std::left << std::setw(20) << "Filename" << "|" << std::right << std::setw(10) << "Size (B)" << "\n";
        os << std::string(32, '-') << "\n";
        
        for (size_t i = 0; i < arc.m_fileCount; ++i) {
            os << std::left << std::setw(20) << arc.m_entries[i].name 
               << "|" << std::right << std::setw(10) << arc.m_entries[i].size << "\n";
        }
        return os;
    }

    // Weryfikacja zawartości pliku binarnego bezpośrednio z dysku
    static void listFileContents(const std::string& archiveName) {
        FILE* f = fopen(archiveName.c_str(), "rb");
        if (!f) {
            Logger::getInstance().error("Archive file not found.");
            return;
        }

        std::array<char, 4> diskMagic;
        fread(diskMagic.data(), 1, diskMagic.size(), f);
        if (diskMagic != MAGIC) {
            Logger::getInstance().error("Format mismatch (invalid Magic Number).");
            fclose(f);
            return;
        }

        uint32_t count;
        fread(&count, sizeof(count), f);

        std::cout << "\n[DISK VERIFICATION] Reading archive: " << archiveName << "\n";
        std::cout << std::left << std::setw(20) << "Filename" << "|" << std::right << std::setw(10) << "Size (B)" << "\n";
        std::cout << std::string(32, '=') << "\n";

        for (uint32_t i = 0; i < count; ++i) {
            FileMetadata meta;
            fread(&meta, sizeof(FileMetadata), f);
            std::cout << std::left << std::setw(20) << meta.name 
                      << "|" << std::right << std::setw(10) << meta.size << "\n";
        }

        fclose(f);
    }
};

int main() {
    Logger::getInstance().info("Starting TinyPacker utility...");

    TinyArchive archive;

    // Pakowanie wybranych plików
    archive.addFile("README.md");      
    archive.addFile("TinyPacker.cpp"); 

    // Wyświetlenie podsumowania z pamięci operacyjnej
    std::cout << archive << std::endl;

    // Persystencja danych
    archive.save("test_archive.tpak");

    // Weryfikacja poprawności zapisu binarnego
    TinyArchive::listFileContents("test_archive.tpak");

    return 0;
}
