#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <filesystem>
#include <sstream>
#include <iomanip>

#include "exqudens/BitcoinMiner.hpp"
#include "exqudens/bitcoin/miner/versions.hpp"
#include "exqudens/bitcoin/miner/Sha256.hpp"

#define CALL_INFO std::string(__FUNCTION__) + "(" + std::filesystem::path(__FILE__).filename().string() + ":" + std::to_string(__LINE__) + ")"
#define LOGGER_ID "exqudens.BitcoinMiner"

namespace exqudens {

    BitcoinMiner::BitcoinMiner() = default;

    std::string BitcoinMiner::getVersion() {
        return std::to_string(PROJECT_VERSION_MAJOR) + "." + std::to_string(PROJECT_VERSION_MINOR) + "." + std::to_string(PROJECT_VERSION_PATCH);
    }

    unsigned char BitcoinMiner::hexCharToByte(char value) {
        if (value >= '0' && value <= '9') {
            return value - '0';
        } else if (value >= 'a' && value <= 'f') {
            return 10 + (value - 'a');
        } else if (value >= 'A' && value <= 'F') {
            return 10 + (value - 'A');
        } else {
            throw std::runtime_error(CALL_INFO + ": Invalid hex character");
        }
    }

    std::vector<unsigned char> BitcoinMiner::hexStringToBytes(const std::string& value) {
        if (value.length() % 2 != 0) {
            throw std::runtime_error(CALL_INFO + ": Hex string length must be even.");
        }

        std::vector<unsigned char> bytes = {};
        bytes.reserve(value.length() / 2);

        for (size_t i = 0; i < value.length(); i += 2) {
            unsigned char highNibble = hexCharToByte(value[i]);
            unsigned char lowNibble = hexCharToByte(value[i + 1]);
            bytes.push_back((highNibble << 4) | lowNibble);
        }

        return bytes;
    }

    std::string BitcoinMiner::bytesToHexString(const std::vector<unsigned char>& value) {
        std::ostringstream stream;
        stream << std::hex << std::setfill('0');
        for (unsigned char byte : value) {
            stream << std::setw(2) << static_cast<int>(byte);
        }
        return stream.str();
    }

    std::vector<uint32_t> BitcoinMiner::bytesToUnsignedIntegers(const std::vector<unsigned char>& value) {
        size_t size = sizeof(uint32_t);

        if (value.size() % size != 0) {
            throw std::runtime_error(CALL_INFO + ": Byte array size does not match unsigned int size.");
        }

        std::vector<uint32_t> result = {};

        for (size_t i = 0; i < value.size(); i += size) {
            unsigned int v = 0;

            /* std::vector<unsigned char> subValue(value.begin() + i, value.begin() + i + size);
            std::memcpy(&v, subValue.data(), size); */

            /* v |= static_cast<unsigned int>(value.at(i));
            v |= static_cast<unsigned int>(value.at(i + 1)) << 8;
            v |= static_cast<unsigned int>(value.at(i + 2)) << 16;
            v |= static_cast<unsigned int>(value.at(i + 3)) << 24; */

            v |= static_cast<unsigned int>(value.at(i + 3)) << 24;
            v |= static_cast<unsigned int>(value.at(i + 2)) << 16;
            v |= static_cast<unsigned int>(value.at(i + 1)) << 8;
            v |= static_cast<unsigned int>(value.at(i));

            result.emplace_back(v);
        }

        return result;
    }

    std::vector<unsigned char> BitcoinMiner::unsignedIntegersToBytes(const std::vector<uint32_t>& value) {
        std::vector<uint8_t> result = {};

        if (value.empty()) {
            return result;
        }

        /* size_t size = sizeof(unsigned int);
        result.resize(value.size() * size);

        std::memcpy(result.data(), value.data(), value.size() * size); */

        /* for (uint32_t val : value) {
            result.emplace_back(static_cast<uint8_t>(val & 0xFF));
            result.emplace_back(static_cast<uint8_t>((val >> 8) & 0xFF));
            result.emplace_back(static_cast<uint8_t>((val >> 16) & 0xFF));
            result.emplace_back(static_cast<uint8_t>((val >> 24) & 0xFF));
        } */

        for (uint32_t val : value) {
            result.emplace_back(static_cast<uint8_t>((val >> 24) & 0xFF));
            result.emplace_back(static_cast<uint8_t>((val >> 16) & 0xFF));
            result.emplace_back(static_cast<uint8_t>((val >> 8) & 0xFF));
            result.emplace_back(static_cast<uint8_t>(val & 0xFF));
        }

        return result;
    }

    std::string BitcoinMiner::sha256(const std::string& value) {
        exqudens::bitcoin::miner::Sha256 object = {};
        std::vector<uint8_t> tmp(value.begin(), value.end());
        std::array<uint8_t, 32> result = object.convert(tmp.data(), tmp.size());
        return exqudens::bitcoin::miner::Sha256::toString(result);
    }

    BitcoinMiner::~BitcoinMiner() = default;

}

#undef LOGGER_ID
#undef CALL_INFO
