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

#ifndef BIT_STREAM_HPP
#define BIT_STREAM_HPP

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <fstream>

/**
 * @class BitStream
 * @brief Space-efficient bit container with windowed access and file I/O
 * 
 * Features:
 * - Compact storage (8 bits/byte)
 * - Random access via operator[]
 * - Sequential window management
 * - Cross-platform file I/O
 * - Exception-safe operations
 * 
 * @invariant 0 ≤ start_pos ≤ end_pos ≤ (data.size() * 8)
 */
class BitStream {
public:
    // ==================== Construction/Cleanup ====================
    
    /// Creates an empty bit stream
    BitStream() = default;

    /**
     * @brief Clear all bits and reset state
     * @post size() == 0, start_pos == 0, end_pos == 0
     */
    void clear() noexcept;

    // ==================== Bit Modification ====================
    
    /**
     * @brief Append a bit to the stream
     * @param bit Integer value (0 = false, non-zero = true)
     * @post size() increases by 1
     */
    void append(int bit);

    /**
     * @brief Append a boolean bit
     * @param bit Value to append
     */
    void append(bool bit);

    // ==================== Bit Access ====================
    
    /**
     * @brief Read bit at position
     * @param index Relative position in current window [0, size())
     * @return Bit value as bool
     * @throws std::out_of_range if index >= size()
     */
    bool operator[](size_t index) const;

    /**
     * @brief Mutable bit access via proxy
     * @param index Relative position in current window [0, size())
     * @return BitProxy for assignment operations
     * @throws std::out_of_range if index >= size()
     */
    class BitProxy;
    BitProxy operator[](size_t index);

    // ==================== Window Management ====================
    
    /**
     * @brief Remove bits from start of window
     * @param n Number of bits to remove (default=1)
     * @throws std::out_of_range if n > size()
     * @post start_pos += n (if valid)
     */
    void pop_front(size_t n = 1);

    /**
     * @brief Get number of valid bits in window
     * @return end_pos - start_pos
     */
    size_t size() const noexcept;

    // ==================== File I/O ====================
    
    /**
     * @brief Write current window to file
     * @param filename Output file path
     * @throws std::runtime_error On file errors
     * 
     * @note File format:
     * - Bits packed MSB-first
     * - Final byte padded with 0s
     */
    void write_to_file(const std::string& filename) const;

    /**
     * @brief Append bits from file to stream
     * @param filename Input file path
     * @throws std::runtime_error On file errors
     * @throws std::bad_alloc On memory failure
     */
    void read_from_file(const std::string& filename);

private:
    // ==================== Implementation Details ====================
    std::vector<uint8_t> data;      ///< Byte storage (MSB-first)
    size_t start_pos = 0;           ///< First valid bit (inclusive)
    size_t end_pos = 0;             ///< End of valid bits (exclusive)

    void append_internal(bool bit);
    bool get_bit(size_t absolute_pos) const;
    void set_bit(size_t absolute_pos, bool value);
    
    void validate_index(size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Bit index " + std::to_string(index) 
                + " out of range [0, " + std::to_string(size()) + ")");
        }
    }

public:
    // ==================== Bit Proxy ====================
    /**
     * @class BitStream::BitProxy
     * @brief Enables mutable bit assignments through operator[]
     */
    class BitProxy {
        BitStream& stream;  ///< Reference to parent BitStream
        size_t pos;         ///< Absolute bit position
        
    public:
        BitProxy(BitStream& s, size_t p) : stream(s), pos(p) {}
        
        /// Convert to bool (read operation)
        operator bool() const { return stream.get_bit(pos); }
        
        /// Assign boolean value (write operation)
        BitProxy& operator=(bool value) {
            stream.set_bit(pos, value);
            return *this;
        }
        
        /// Assign integer value (0 = false, non-zero = true)
        BitProxy& operator=(int value) {
            /* On Mac: Apple clang version 17.0.0 (clang-1700.0.13.3)
            note: candidate function (the implicit copy assignment operator) not viable: no known conversion from 'bool' to 'const BitProxy' for 1st argument
            */
            // return operator=(value != 0);

            return (*this) = (value != 0) ; 
            // avoid calling operator= directly, which may have some name resolution problem by some compiler 
        }
    };
};

#endif // BIT_STREAM_HPP