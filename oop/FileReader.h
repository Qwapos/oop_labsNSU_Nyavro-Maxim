#ifndef OOP_LABSNSU_NYAVRO_MAXIM_FILEREADER_H
#define OOP_LABSNSU_NYAVRO_MAXIM_FILEREADER_H
#include <string>
#include <fstream>

class FileReader
{
public:
        explicit FileReader(const std::string& sourceFileName);
        bool readWord(std::string& word);
private:
        std::ifstream fin;
};


#endif //OOP_LABSNSU_NYAVRO_MAXIM_FILEREADER_H
