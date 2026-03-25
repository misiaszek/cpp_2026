#include <iostream>
#include <fstream>
#include <array>
#include <string_view>
#include <iomanip>
#include <ctime>

/**
 * PROJEKT 1: TINY PACKER (v1.0)
 * ----------------------------
 * Cel: Stworzenie prostego archiwizatora plików binarnych.
 * Wykorzystane techniki:
 * - RAII (zarządzanie plikami i buforami)
 * - Singleton (logger zdarzeń)
 * - Deep Copy (bezpieczne kopiowanie danych plików)
 * - std::array (magiczne numery i stałe rozmiary)
 * - friend & operator<< (wizualizacja struktury archiwum)
 * - <iomanip> (formatowanie tabeli spisu treści)
 */

// --- 1. SINGLETON (Meyers' Singleton) ---
// Służy do centralnego logowania operacji w programie.
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
    Logger() {} // Prywatny konstruktor
    Logger(const Logger&) = delete; // Zakaz kopiowania
};

// --- 2. RAII: DataBuffer (Deep Copy Example) ---
// Zarządza surowymi danymi wczytanego pliku.
class DataBuffer {
    char* m_data;
    size_t m_size;

public:
    DataBuffer() : m_data{nullptr}, m_size{0} {}
    
    DataBuffer(size_t size) : m_size{size} {
        m_data = new char[m_size];
    }

    // KONSTRUKTOR KOPIUJĄCY (Głęboka Kopia)
    // Bez tego, skopiowanie obiektu spowodowałoby Double Free przy niszczeniu oryginału i kopii.
    DataBuffer(const DataBuffer& other) : m_size{other.m_size} {
        if (other.m_data) {
            m_data = new char[m_size];
            for (size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
        } else {
            m_data = nullptr;
        }
    }

    // Destruktor (Zwalnianie zasobów)
    ~DataBuffer() {
        delete[] m_data;
    }

    char* data() { return m_data; }
    size_t size() const { return m_size; }
};

// --- 3. STRUKTURY DANYCH ---
struct FileMetadata {
    char name[32];
    uint32_t size;
};

// --- 4. KLASA ARCHIWUM (TinyArchive) ---
class TinyArchive {
private:
    // Użycie std::array do "podpisu" formatu pliku (Lab 4)
    static constexpr std::array<char, 4> MAGIC = {'T', 'P', 'A', 'K'};
    
    static const size_t MAX_FILES = 5;
    std::array<FileMetadata, MAX_FILES> m_entries;
    std::array<DataBuffer, MAX_FILES> m_buffers;
    size_t m_fileCount = 0;

public:
    TinyArchive() = default;

    // Dodawanie pliku do struktury
    bool addFile(const std::string& filename) {
        if (m_fileCount >= MAX_FILES) {
            Logger::getInstance().error("Archive is full!");
            return false;
        }

        // Użycie klasycznego C-style file handlingu (jak prosiłeś) opakowanego w logikę C++
        FILE* f = fopen(filename.c_str(), "rb");
        if (!f) {
            Logger::getInstance().error("Could not open file: " + filename);
            return false;
        }

        // Sprawdzenie rozmiaru
        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);
        fseek(f, 0, SEEK_SET);

        // Alokacja bufora (RAII)
        DataBuffer buf(size);
        fread(buf.data(), 1, size, f);
        fclose(f);

        // Zapisanie metadanych
        FileMetadata& meta = m_entries[m_fileCount];
        for (size_t i = 0; i < 31 && i < filename.length(); ++i) meta.name[i] = filename[i];
        meta.name[31] = '\0';
        meta.size = static_cast<uint32_t>(size);

        m_buffers[m_fileCount] = buf; // Wywołuje operator przypisania (lub konstruktor kopiujący)
        m_fileCount++;

        Logger::getInstance().info("Added file: " + filename);
        return true;
    }

    // Zapisywanie wszystkiego do jednego pliku binarnego
    void save(const std::string& archiveName) {
        FILE* f = fopen(archiveName.c_str(), "wb");
        if (!f) return;

        // 1. Zapisz Magic Number (std::array)
        fwrite(MAGIC.data(), 1, MAGIC.size(), f);

        // 2. Zapisz liczbę plików
        uint32_t count = static_cast<uint32_t>(m_fileCount);
        fwrite(&count, sizeof(count), f);

        // 3. Zapisz metadane (Tablica struktur)
        for (size_t i = 0; i < m_fileCount; ++i) {
            fwrite(&m_entries[i], sizeof(FileMetadata), f);
        }

        // 4. Zapisz właściwe dane
        for (size_t i = 0; i < m_fileCount; ++i) {
            fwrite(m_buffers[i].data(), 1, m_buffers[i].size(), f);
        }

        fclose(f);
        Logger::getInstance().info("Archive saved to: " + archiveName);
    }

    // PRZYJACIEL: Do wypisywania spisu treści (Lab 3)
    friend std::ostream& operator<<(std::ostream& os, const TinyArchive& arc) {
        os << "\n--- TinyArchive Content Summary ---\n";
        os << std::left << std::setw(20) << "Filename" << "|" << std::right << std::setw(10) << "Size (B)" << "\n";
        os << std::string(32, '-') << "\n";
        
        // Pętla zakresowa (Lab 4)
        for (size_t i = 0; i < arc.m_fileCount; ++i) {
            os << std::left << std::setw(20) << arc.m_entries[i].name 
               << "|" << std::right << std::setw(10) << arc.m_entries[i].size << "\n";
        }
        return os;
    }
};

int main() {
    Logger::getInstance().info("Starting TinyPacker...");

    TinyArchive archive;

    // Pakujemy kilka plików, aby pokazać działanie archiwizatora
    // (Pliki te muszą istnieć w katalogu roboczym)
    archive.addFile("README.md");      
    archive.addFile("TinyPacker.cpp"); 

    // Wizualizacja spisu treści (operator<< + iomanip)
    // Tu zobaczymy kilka wpisów w ładnej tabeli
    std::cout << archive << std::endl;

    // Zapis do jednego pliku binarnego
    archive.save("test_archive.tpak");

    return 0;
}
