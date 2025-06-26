#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <vector>

#include "exqudens/bitcoin/miner/export.hpp"

namespace exqudens {

    class EXQUDENS_BITCOIN_MINER_EXPORT BitcoinMiner {

        public:

            BitcoinMiner();

            std::string getVersion();

            unsigned char hexCharToByte(char value);

            std::vector<unsigned char> hexStringToBytes(const std::string& value);

            std::string bytesToHexString(const std::vector<unsigned char>& value);

            std::vector<uint32_t> bytesToUnsignedIntegers(const std::vector<unsigned char>& value);

            std::vector<unsigned char> unsignedIntegersToBytes(const std::vector<uint32_t>& value);

            std::string sha256(const std::string& value);

            ~BitcoinMiner();

    };

}
