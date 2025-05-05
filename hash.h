#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::vector<unsigned long long> w(5, 0); // holds up to 5 chunks
        int len = k.length();
        int chunkIndex = 4; // start from end, w[4] is last chunk

        for (int i = len - 1; i >= 0 && chunkIndex >= 0; ) {
            unsigned long long chunkValue = 0;
            unsigned long long power = 1;

            // up to 6 characters in one chunk
            for (int j = 0; j < 6 && i >= 0; ++j, --i) {
                char c = std::tolower(k[i]);
                int val = letterDigitToNumber(c);
                chunkValue += val * power;
                power *= 36;
            }

            w[chunkIndex] = chunkValue;
            --chunkIndex;
        }

        // Step 2: Compute final hash value
        unsigned long long hash = 0;
        for (int i = 0; i < 5; ++i) {
            hash += rValues[i] * w[i];
        }

        return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (std::isalpha(letter)) {
            return std::tolower(letter) - 'a';
        }
        else if (std::isdigit(letter)) {
            return 26 + (letter - '0');
        }
        return 0; // fallback, shouldn't happen with valid input   
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
