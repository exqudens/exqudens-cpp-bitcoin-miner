#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <exqudens/Log.hpp>
#include <exqudens/log/api/Logging.hpp>

#include "TestUtils.hpp"
#include "exqudens/BitcoinMiner.hpp"

namespace exqudens {

    class BitcoinMinerUnitTests: public testing::Test {

        protected:

            inline static const char* LOGGER_ID = "BitcoinMinerUnitTests";

        protected:

            static void log(
                const std::string& file,
                const size_t& line,
                const std::string& function,
                const std::string& id,
                const unsigned short& level,
                const std::string& message
            ) {
                exqudens::log::api::Logging::Writer(file, line, function, id, level) << message;
            }

    };

    TEST_F(BitcoinMinerUnitTests, test1) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            EXQUDENS_LOG_INFO(LOGGER_ID) << "bgn";

            exqudens::BitcoinMiner object = {};
            std::filesystem::path projectSourceDir = {};
            std::string nameVersionContent = {};
            std::string expected = {};
            std::string actual = {};

            projectSourceDir = std::filesystem::path(TestUtils::getProjectSourceDir());
            nameVersionContent = TestUtils::readFileString((projectSourceDir / "name-version.txt").generic_string());

            expected = TestUtils::trim(TestUtils::split(TestUtils::trim(nameVersionContent), ":").at(1));
            EXQUDENS_LOG_INFO(LOGGER_ID) << "expected: '" << expected << "'";

            actual = object.getVersion();
            EXQUDENS_LOG_INFO(LOGGER_ID) << "actual: '" << actual << "'";

            ASSERT_EQ(expected, actual);

            EXQUDENS_LOG_INFO(LOGGER_ID) << "end";
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

    TEST_F(BitcoinMinerUnitTests, test2) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            EXQUDENS_LOG_INFO(LOGGER_ID) << "bgn";

            exqudens::BitcoinMiner object = {};
            std::string hexString = {};
            std::vector<unsigned char> bytes = {};
            std::string expected = {};
            std::string actual = {};

            hexString = "48656c6c6f20576f726c64";
            bytes = object.hexStringToBytes(hexString);

            expected = "Hello World";
            EXQUDENS_LOG_INFO(LOGGER_ID) << "expected: '" << expected << "'";

            actual = std::string(bytes.begin(), bytes.end());
            EXQUDENS_LOG_INFO(LOGGER_ID) << "actual: '" << actual << "'";

            ASSERT_EQ(expected, actual);

            expected = hexString;
            EXQUDENS_LOG_INFO(LOGGER_ID) << "expected: '" << expected << "'";

            actual = object.bytesToHexString(bytes);
            EXQUDENS_LOG_INFO(LOGGER_ID) << "actual: '" << actual << "'";

            ASSERT_EQ(expected, actual);

            EXQUDENS_LOG_INFO(LOGGER_ID) << "end";
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

    TEST_F(BitcoinMinerUnitTests, test3) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            EXQUDENS_LOG_INFO(LOGGER_ID) << "bgn";

            exqudens::BitcoinMiner object = {};
            std::string value = {};
            std::string expected = {};
            std::string actual = {};

            value = "test";
            EXQUDENS_LOG_INFO(LOGGER_ID) << "value: '" << value << "'";

            expected = "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08";
            EXQUDENS_LOG_INFO(LOGGER_ID) << "expected: '" << expected << "'";

            actual = object.sha256(value);
            EXQUDENS_LOG_INFO(LOGGER_ID) << "actual: '" << actual << "'";

            ASSERT_EQ(expected, actual);

            EXQUDENS_LOG_INFO(LOGGER_ID) << "end";
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

    TEST_F(BitcoinMinerUnitTests, test4) {
        try {
            std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
            std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
            EXQUDENS_LOG_INFO(LOGGER_ID) << "bgn";

            exqudens::BitcoinMiner object = {};
            std::string value = {};
            std::string expected = {};
            std::string actual = {};

            value = "Hello World";
            EXQUDENS_LOG_INFO(LOGGER_ID) << "value: '" << value << "'";

            expected = "a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e";
            EXQUDENS_LOG_INFO(LOGGER_ID) << "expected: '" << expected << "'";

            actual = object.sha256(value);
            EXQUDENS_LOG_INFO(LOGGER_ID) << "actual: '" << actual << "'";

            ASSERT_EQ(expected, actual);

            EXQUDENS_LOG_INFO(LOGGER_ID) << "end";
        } catch (const std::exception& e) {
            std::string errorMessage = TestUtils::toString(e);
            std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
            FAIL() << errorMessage;
        }
    }

}
