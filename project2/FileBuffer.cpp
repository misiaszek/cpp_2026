#include "FileBuffer.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>

FileBuffer::FileBuffer(const std::string& filename) 
    : m_filename(filename), m_data(nullptr), m_size(0) {
    // Delegacja do metody load() mogłaby być tutaj (cw3)
}

FileBuffer::FileBuffer(const FileBuffer& other) 
    : m_filename(other.m_filename), m_size(other.m_size) {
    if (other.m_data) {
        m_data = new char[m_size];
        std::memcpy(m_data, other.m_data, m_size);
    } else {
        m_data = nullptr;
    }
}

FileBuffer& FileBuffer::operator=(const FileBuffer& other) {
    if (this != &other) { // check this (cw7)
        delete[] m_data;
        m_filename = other.m_filename;
        m_size = other.m_size;
        if (other.m_data) {
            m_data = new char[m_size];
            std::memcpy(m_data, other.m_data, m_size);
        } else {
            m_data = nullptr;
        }
    }
    return *this;
}

FileBuffer::~FileBuffer() {
    delete[] m_data;
}

void FileBuffer::load() {
    std::ifstream file(m_filename, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Nie mozna otworzyc pliku: " + m_filename); // (cw6)
    }

    m_size = file.tellg();
    file.seekg(0, std::ios::beg);

    delete[] m_data;
    m_data = new char[m_size];
    
    if (!file.read(m_data, m_size)) {
        throw std::runtime_error("Blad odczytu pliku: " + m_filename);
    }
}
