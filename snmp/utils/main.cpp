/*
    Function convert EngineID from std::string to the array of unsigned char.
*/

#include <vector>
#include <string>
#include <sstream>

#include <iostream>

std::vector<unsigned char> getBytesFromEngineIDString(const std::string& engineID)
{
    std::vector<unsigned char> result;
    std::istringstream id{ engineID };
    unsigned int byte;
    while (id >> std::hex >> byte)
    {
        result.push_back(byte);
    }
    return result;
}



int main()
{
    const std::vector<unsigned char> benchmark_engineID = {0x1, 0x2, 0x3, 0x4, 0x5};

    {
        const std::string test1 = "01 02 03 04 05";
        auto result = getBytesFromEngineIDString(test1);
        std::cout << (result == benchmark_engineID ? "Test1 OK\n" : "Test1 FAIL\n");
    }

    {
        const std::string test2 = "0102 03 04 05";
        auto result = getBytesFromEngineIDString(test2);
        std::cout << (result == benchmark_engineID ? "Test2 OK\n" : "Test2 FAIL\n");
    }
}