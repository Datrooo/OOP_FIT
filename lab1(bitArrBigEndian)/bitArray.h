#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <vector>
#include <string>

#define BYTE 8
/**
 * @class BitArray
 * @brief a dynamic bit array for useful storage.
 * 
 * The BitArray class supports bitwise operations,
 * dynamic resizing, and other useful methods for
 * working with binary data. The class works with
 * unsigned long sized memory blocks.
 */

class BitArray{
    private:
        std::vector<unsigned long> bits;    ///Storage for bits in blocks of unsigned long
        int sizeOfBuf;  ///Number of used bits in array
        static const int bitsPerBlock;  /// Size of block in bits.
        /**
         * @brief Find block of vector.
         * @return num of block
         */
        int findBlock(int numBits);

    public:
        /**
         * @brief Default constructor. Initializes an empty 
         * bit array.
         */
        BitArray();

        /**
         * @brief Default destructor.
         */
        ~BitArray();
        
         /**
         * @brief Constructor to initialize the bit array with a specific number of bits.
         * 
         * @param numBits The number of bits to initialize the array with.
         * @param value The initial value to set the bits to (default is 0).
         * @throws std::invalid_argument if numBits is negative.
         */
        explicit BitArray(int numBits, unsigned long value = 0);

        /**
         * @brief Copy constructor.
         * 
         * @param b The BitArray to copy from.
         */
        BitArray(const BitArray& b);

        /**
         * @brief Swaps the contents of this BitArray with another.
         * 
         * @param b The BitArray to swap with.
         */
        void swap(BitArray& b);

        /**
         * @brief Assignment operator.
         * 
         * @param b The BitArray to assign from.
         * @return Reference to this BitArray.
         */
        BitArray& operator=(const BitArray& b);

        /**
         * @brief Resizes the BitArray to a new size.
         * 
         * @param numBits The new size of the BitArray.
         * @param value The value to set new bits to (default is false).
         * @throws std::invalid_argument if numBits is negative.
         */
        void resize(int numBits, bool value = false);

        /**
         * @brief Clears the BitArray, resetting its size to zero.
        */  
        void clear();

        /**
         * @brief Adds a bit to the end of the BitArray.
         * 
         * @param bit The bit to add (true for 1, false for 0).
         */    
        void pushBack(bool bit);

        /**
         * @brief Bitwise AND assignment operator.
         * 
         * @param b The BitArray to AND with.
         * @return Reference to this BitArray.
         * @throws std::invalid_argument if sizes do not match.
         */
        BitArray& operator&=(const BitArray& b);

        /**
         * @brief Bitwise OR assignment operator.
         * 
         * @param b The BitArray to OR with.
         * @return Reference to this BitArray.
         * @throws std::invalid_argument if sizes do not match.
         */
        BitArray& operator|=(const BitArray& b);

        /**
         * @brief Bitwise XOR assignment operator.
         * 
         * @param b The BitArray to XOR with.
         * @return Reference to this BitArray.
         * @throws std::invalid_argument if sizes do not match.
         */
        BitArray& operator^=(const BitArray& b);
        
        /**
         * @brief Bitwise left shift assignment operator.
         * 
         * @param n The number of positions to shift left.
         * @return Reference to this BitArray.
         * @throws std::invalid_argument if n is negative.
         */
        BitArray& operator<<=(int n);

        /**
         * @brief Bitwise right shift assignment operator.
         * 
         * @param n The number of positions to shift right.
         * @return Reference to this BitArray.
         * @throws std::invalid_argument if n is negative.
         */
        BitArray& operator>>=(int n);

        /**
         * @brief Bitwise left shift operator.
         * 
         * @param n The number of positions to shift left.
         * @return A new BitArray that is the result of the shift.
         */
        BitArray operator<<(int n) const;

        /**
         * @brief Bitwise right shift operator.
         * 
         * @param n The number of positions to shift right.
         * @return A new BitArray that is the result of the shift.
         */        
        BitArray operator>>(int n) const;

        /**
         * @brief Sets the bit at a specified index.
         * 
         * @param n The index of the bit to set.
         * @param val The value to set the bit to (default is true).
         * 
         * @return Reference to this BitArray.
         * 
         * @throws std::invalid_argument if index is out of range.
         */
        BitArray& set(int n, bool val = true);

        /**
         * @brief Sets all bits in the BitArray to true (1).
         * 
         * @return Reference to this BitArray.
         */
        BitArray& set();

        /**
         * @brief Resets the bit at a specified index to false (0).
         * 
         * @param n The index of the bit to reset.
         * @return Reference to this BitArray.
         */
        BitArray& reset(int n);

        /**
         * @brief Resets all bits in the BitArray to false (0).
         * 
         * @return Reference to this BitArray.
         */
        BitArray& reset();

        /**
         * @brief Checks if any bits are set to true (1).
         * 
         * @return True if at least one bit is set, otherwise false.
         */
        bool any() const;

        /**
         * @brief Checks if all bits are set to false (0).
         * 
         * @return True if all bits are false, otherwise false.
         */
        bool none() const;

        /**
         * @brief Bitwise NOT operator.
         * 
         * @return A new BitArray that is the negation of this BitArray.
         */
        BitArray operator~() const;

        /**
         * @brief Counts the number of bits set to true (1).
         * 
         * @return The count of bits set to true.
         */
        int count() const;

        /**
         * @brief Index operator to access bits.
         * 
         * @param i The index of the bit to access.
         * @return True if the bit at index i is set, otherwise false.
         * @throws std::invalid_argument if index is out of range.
         */
        bool operator[](int i) const;

        /**
        * @brief Returns the number of bits in the array.
         *
         * @return The size of the BitArray.
         */
        int size() const;

        /**
         * @brief Checks if the BitArray hasnt got bits.
         *
         * @return True if empty, otherwise false.
         */
        bool empty() const;

    /**
     * @brief Convert the BitArray to a string representation.
     *
     * @return A string representation of an array of bits.
     */
        
        std::string toString() const;

        /**
         * @brief Compare two BitArrays for equality.
         *
         * @param a The first bit array.
         * @param b The second bit array.
         * @return True if the two arrays are equivalent, otherwise false.
         */
        friend bool operator==(const BitArray & a, const BitArray & b);

        /**
         * @brief Compare two BitArrays for inequality.
         *
         * @param a The first bit array.
         * @param b The second bit array.
         * @return True if the two arrays arenot  equivalent, otherwise false.
         */
        friend bool operator!=(const BitArray & a, const BitArray & b);

};

/**
 * @brief Bitwise AND operation betweeen btt arrays
 * 
 * @param b1 The first BitArray operand;
 * @param b2 The second BitArray operand;
 * 
 * @return  A new BitArray is the result it the AND operrration.
 * @throws std::invalid_argument if the two BitArrays have different sizes.
 */
BitArray operator&(const BitArray& b1, const BitArray& b2);

/**
 * @brief Bitwise OR operation betweeen btt arrays
 * 
 * @param b1 The first BitArray operand;
 * @param b2 The second BitArray operand;
 * 
 * @return  A new BitArray is the result it the OR operrration.
 * @throws std::invalid_argument if the two BitArrays have different sizes.
 */
BitArray operator|(const BitArray& b1, const BitArray& b2);

/**
 * @brief Bitwise XOR operation between bit arrays.
 *
 * @param b1 The first BitArray operand.
 * @param b2 The second BitArray operand.

 * @return A new BitArray is the result of the XOR operation.

 * @throws std::invalid_argument if the two BitArrays have different sizes.
 */
BitArray operator^(const BitArray& b1, const BitArray& b2);



#endif