#include <cstdint>
#include "vector.h"
#include <fstream>


class Sandpile {
public:
    Sandpile(std::string& tsv, int iter, int freq) : tsv(tsv), height(0), width(0), iterations(iter), frequency(freq) {}
    ~Sandpile() = default;
    void CreateField();
    void Work(std::string& path);
    void OneIter();
    int GetWidth();
    int GetHidth();
    vector<vector<int>>& GetField();
    std::string& GetTsv();

private:
    std::string tsv;
    uint32_t width;
    uint32_t height;
    uint32_t iterations;
    uint32_t frequency;
    vector<vector<int>> coords;
    vector<vector<int>> field;
};