//
// Created by nyamax on 03.10.2026.
//

#ifndef OOP_LABSNSU_NYAVRO_MAXIM_CSVWRITER_H
#define OOP_LABSNSU_NYAVRO_MAXIM_CSVWRITER_H
#include <string>
#include <fstream>
#include <vector>
#include <utility>

class CSVWriter
{
public:
    explicit CSVWriter(const std::string& filename);
    void writeCSV(const std::vector<std::pair<std::string, long long>>& data, long long totalWords);
private:
    std::ofstream fout;
};


#endif //OOP_LABSNSU_NYAVRO_MAXIM_CSVWRITER_H
