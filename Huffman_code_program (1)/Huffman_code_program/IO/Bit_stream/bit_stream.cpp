/*********************************************************** 
 * CS111 OOP 2025 Homework 2 
 * Program designed and implemented by the instructor
 * Zhiyao Liang  ( zyliang@must.edu.mo )                                
 * Date: 2025-May                                       
 ***********************************************************/

  /*******************************************
  * If you changed the file, write your names
  * Student names: 
  ********************************************/

#include "bit_stream.hpp"
#include <fstream>
#include <stdexcept>
#include <cstdio>
#include <limits> // for std::numeric_limits

// ==================== Core Operations ====================

void BitStream::clear() noexcept {
    data.clear();
    start_pos = 0;
    end_pos = 0;
}

void BitStream::append(int bit) {
    append_internal(bit != 0);
}

void BitStream::append(bool bit) {
    append_internal(bit);
}

void BitStream::append_internal(bool bit) {
    const size_t absolute_pos = end_pos++;
    const size_t byte_index = absolute_pos / 8;
    const uint8_t bit_mask = 1 << (7 - (absolute_pos % 8));

    if (byte_index >= data.size()) {
        data.push_back(0);
    }

    if (bit) {
        // !!!!!!!!!!!! <Task 9.a>, provide the missing code
        
    } else {
        
        // <Task 9.a>, provide the missing code
    }
}

// ==================== Bit Access ====================

bool BitStream::operator[](size_t index) const {
    validate_index(index);
    return get_bit(start_pos + index);
}

BitStream::BitProxy BitStream::operator[](size_t index) {
    validate_index(index);
    return BitProxy(*this, start_pos + index);
}

// ==================== Window Management ====================

void BitStream::pop_front(size_t n) {
    if (n > size()) {
        throw std::out_of_range("pop_front: Cannot remove " + 
                              std::to_string(n) + " from " + 
                              std::to_string(size()) + " bits");
    }
    start_pos += n;
}

size_t BitStream::size() const noexcept {
    return end_pos - start_pos;
}

// ==================== File I/O ====================

void BitStream::write_to_file(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("write_to_file: Failed to open " + filename);
    }

    try {
        // Write header: 64-bit bit count
        const uint64_t bit_count = end_pos - start_pos;
        file.write(reinterpret_cast<const char*>(&bit_count), sizeof(bit_count));

        // Write actual bits
        size_t current_pos = start_pos;
        while (current_pos < end_pos) {
            uint8_t byte = 0;
            for (int bit_pos = 7; bit_pos >= 0 && current_pos < end_pos; --bit_pos) {
                if (get_bit(current_pos++)) {
                    byte |= (1 << bit_pos);
                }
            }
            file.write(reinterpret_cast<const char*>(&byte), 1);
        }
    }
    catch (const std::ios_base::failure& e) {
        throw std::runtime_error("write_to_file: I/O error - " + std::string(e.what()));
    }
}

void BitStream::read_from_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("read_from_file: Failed to open " + filename);
    }

    try {
        // Read header: 64-bit bit count
        // uint64_t bit_count = 0;
        uint64_t bit_count_u64 = 0;
        file.read(reinterpret_cast<char*>(&bit_count_u64), sizeof(bit_count_u64));

        if (bit_count_u64> static_cast<uint64_t>(std::numeric_limits<size_t>::max()))
        {
            throw std::runtime_error("File too large for system limits");
        }

        // Calculate needed bytes
        // warning of information loss 
        //  const size_t byte_count = (bit_count + 7) / 8;

        const size_t bit_count = static_cast<size_t>(bit_count_u64);
        const size_t byte_count = (bit_count + 7) / 8;

        std::vector<uint8_t> buffer(byte_count);
        
        if (!file.read(reinterpret_cast<char*>(buffer.data()), byte_count)) {
            throw std::runtime_error("read_from_file: Failed to read contents");
        }

        // Append exact number of bits
        size_t bits_added = 0;
        for (uint8_t byte : buffer) {
            for (int bit_pos = 7; bit_pos >= 0 && bits_added < bit_count; --bit_pos) {
                append_internal((byte >> bit_pos) & 1);
                bits_added++;
            }
        }
    }
    catch (const std::ios_base::failure& e) {
        throw std::runtime_error("read_from_file: I/O error - " + std::string(e.what()));
    }
    catch (const std::bad_alloc&) {
        throw std::runtime_error("read_from_file: Memory allocation failed");
    }
}

// ==================== Private Helpers ====================

bool BitStream::get_bit(size_t absolute_pos) const {
    const size_t byte_index = absolute_pos / 8;
    const uint8_t bit_mask = 1 << (7 - (absolute_pos % 8));
    return (data[byte_index] & bit_mask) != 0;
}

void BitStream::set_bit(size_t absolute_pos, bool value) {
    const size_t byte_index = absolute_pos / 8;
    const uint8_t bit_mask = 1 << (7 - (absolute_pos % 8));

    if (value) {
        data[byte_index] |= bit_mask;
    } else {
        data[byte_index] &= ~bit_mask;
    }
}


