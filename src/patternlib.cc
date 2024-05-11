#include <vector>   // std::vector
#include <string>   // std::string
#include <fstream>  // std::ofstream
#include <utility>  // std::pair
#include <unordered_map>  // std::unordered_map

#include "pattern/patternlib.hpp"

namespace pattern
{
    void ExportSolution(std::size_t hash, const std::vector<int>& vec, const std::string& filename, bool append)
    {
        // checks whether to append or rewrite the file
        std::ofstream outfile;
        if (append)
            outfile.open(filename, std::ios_base::app | std::ofstream::binary);
        else
            outfile.open(filename, std::ofstream::binary);

        // writes the hash of the state
        outfile.write(reinterpret_cast<const char*>(&hash), sizeof(std::size_t));

        // writes the ':' to seperate the hash of the state and its solution
        constexpr char sep (':');
        outfile.write((&sep), sizeof(char));

        // writes the solution of the state
        auto itr = vec.begin();
        while (itr != vec.end())
        {
            unsigned char data = 0x0;
            data <<= 4;
            data |= (*itr & 0xF);

            ++itr;
            data <<= 4;

            // pads 0xF if the number of solution is odd
            if (itr != vec.end())
            {
                
                data |= (*itr & 0xF);
                ++itr;
            }
            else
            {
                data |= (0xF);
            }

            outfile.write(reinterpret_cast<const char*>(&data), sizeof(char));
        }

        // writes the '\n' to seperate two entries
        constexpr char br ('\n');
        outfile.write((&br), sizeof(char));

        // closes the file
        outfile.close();
    }

    std::unordered_map<std::size_t, std::vector<int>> LoadSolution(const std::string& filename)
    {
        std::unordered_map<std::size_t, std::vector<int>> ret;

        std::ifstream infile(filename, std::ios::binary);

        // checks if the file can be open correctly
        if (infile.fail())
        {
            return { };
        }

        // 
        char buffer[128];
        int readPtr = 0;
        while (infile.read(&buffer[readPtr], sizeof(char)))
        {
            if (buffer[readPtr] == '\n')
            {
                int bufferPtr = 0;
                // get the hash
                std::size_t hash = *reinterpret_cast<std::size_t*>(buffer);
                bufferPtr += sizeof(std::size_t);

                // skip the ':'
                bufferPtr += sizeof(char);

                // get the solution
                std::vector<int> sol;
                while(buffer[bufferPtr] != '\n')
                {
                    unsigned char data = buffer[bufferPtr];
                    sol.emplace_back((data & 0xF0) >> 4);
                    sol.emplace_back(data & 0xF);

                    ++bufferPtr;
                }

                // checks the last step of the solution
                if (sol.back() == 0xF)
                {
                    sol.pop_back();
                }

                // inserts 
                ret.insert({hash, sol});

                readPtr = 0;
            }
            else
            {
                ++readPtr;
            }
        }

        // closes the file
        infile.close();

        return ret;
    }
}   // namespace pattern