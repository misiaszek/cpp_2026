#include <iostream>
#include <fstream>
#include <array>
#include <string_view>
#include <iomanip>
#include <ctime>
#include <cstdint>
#include <cstring> // Dla memset

/**
 * PROJEKT 1: TINY PACKER (v1.0)
 * ----------------------------
 * Przykład praktycznego zastosowania mechanizmów C++ (Lab 1-4).
 */

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    void info(std::string_view msg) { std::cout << "[INFO]: " << msg << std::endl; }
    void error(std::string_view msg) { std::cerr << "[ERROR]: " << msg << std::endl; }
private:
    Logger() = default; 
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

class DataBuffer {
    char* m_data;
    size_t m_size;
public:
    DataBuffer() : m_data{nullptr}, m_size{0} {}
    DataBuffer(size_t size) : m_size{size} { m_data = new char[m_size]; }
    DataBuffer(const DataBuffer& other) : m_size{other.m_size} {
        if (other.m_data) {
            m_data = new char[m_size];
            std::memcpy(m_data, other.m_data, m_size);
        } else m_data = nullptr;
    }
    DataBuffer& operator=(const DataBuffer& other) {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            if (other.m_data) {
                m_data = new char[m_size];
                std::memcpy(m_data, other.m_data, m_size);
            } else m_data = nullptr;
        }
        return *this;
    }
    ~DataBuffer() { delete[] m_data; }
    char* data() { return m_data; }
    size_t size() const { return m_size; }
};

struct FileMetadata {
    char name[32];
    uint32_t size;
};

class TinyArchive {
private:
    static constexpr std::array<char, 4> MAGIC = {'T', 'P', 'A', 'K'};
    static const size_t MAX_FILES = 5;
    
    // Inicjalizacja listowa {} gwarantuje wyzerowanie tablic (C++11)
    std::array<FileMetadata, MAX_FILES> m_entries{}; 
    std::array<DataBuffer, MAX_FILES> m_buffers{};
    size_t m_fileCount = 0;

public:
    TinyArchive() = default;

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

        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);
        fseek(f, 0, SEEK_SET);

        DataBuffer buf(size);
        fread(buf.data(), 1, size, f);
        fclose(f);

        // BEZPIECZNE KOPIOWANIE NAZWY
        FileMetadata& meta = m_entries[m_fileCount];
        std::memset(meta.name, 0, sizeof(meta.name)); // Zerujemy cały bufor nazwy
        std::strncpy(meta.name, filename.c_str(), sizeof(meta.name) - 1); // Kopiujemy bezpiecznie
        meta.size = static_cast<uint32_t>(size);

        m_buffers[m_fileCount] = buf; 
        m_fileCount++;

        Logger::getInstance().info("File added: " + filename);
        return true;
    }

    void save(const std::string& archiveName) {
        FILE* f = fopen(archiveName.c_str(), "wb");
        if (!f) return;

        fwrite(MAGIC.data(), 1, MAGIC.size(), f);
        uint32_t count = static_cast<uint32_t>(m_fileCount);
        fwrite(&count, sizeof(count), 1, f);

        for (size_t i = 0; i < m_fileCount; ++i) {
            fwrite(&m_entries[i], sizeof(FileMetadata), 1, f);
        }

        for (size_t i = 0; i < m_fileCount; ++i) {
            fwrite(m_buffers[i].data(), 1, m_buffers[i].size(), f);
        }

        fclose(f);
        Logger::getInstance().info("Archive saved: " + archiveName);
    }

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

    static void listFileContents(const std::string& archiveName) {
        FILE* f = fopen(archiveName.c_str(), "rb");
        if (!f) return;

        std::array<char, 4> diskMagic;
        fread(diskMagic.data(), 1, diskMagic.size(), f);
        if (std::memcmp(diskMagic.data(), MAGIC.data(), 4) != 0) {
            fclose(f);
            return;
        }

        uint32_t count;
        fread(&count, sizeof(count), 1, f);

        std::cout << "\n[DISK VERIFICATION] Reading archive: " << archiveName << "\n";
        std::cout << std::left << std::setw(20) << "Filename" << "|" << std::right << std::setw(10) << "Size (B)" << "\n";
        std::cout << std::string(32, '=') << "\n";

        for (uint32_t i = 0; i < count; ++i) {
            FileMetadata meta{}; // Inicjalizacja zerami
            fread(&meta, sizeof(FileMetadata), 1, f);
            std::cout << std::left << std::setw(20) << meta.name 
                      << "|" << std::right << std::setw(10) << meta.size << "\n";
        }
        fclose(f);
    }
};

int main() {
    Logger::getInstance().info("Starting TinyPacker utility...");
    TinyArchive archive;
    archive.addFile("README.md");      
    archive.addFile("TinyPacker.cpp"); 
    std::cout << archive << std::endl;
    archive.save("test_archive.tpak");
    TinyArchive::listFileContents("test_archive.tpak");
    return 0;
}
