#include "sandpile.h"
#include "bmp.h"
#include <iostream>
#include <fstream>
#include <string>


int ToInt(const vector<char>& s) {
    int t = s.size();
    int st = 1;
    int res = 0;
    for (int i = t - 1; i >= 0; i--) {
        res += (s[i] - '0') * st;
        st *= 10;
    }
    return res;
}


void Sandpile::CreateField() {
    std::ifstream file(tsv);
    char ch[256];
    if (!file.is_open()) {
        std::cerr << "WRONG" << '\n';
        exit(EXIT_FAILURE);
    }
    int maxx = 0;
    int maxy = 0;
    std::ifstream map(tsv);
    char s[256];

    while (map.getline(s, 256,  '\n')) {
        vector<char> buf;
        vector<int> vec;
        for (char a : s) {
            if (a == '\0') {
                vec.pushback(ToInt(buf));
                buf.clear();
                coords.pushback(vec);
                if (vec[0] > maxx) {
                    maxx = vec[0];
                }
                if (vec[1] > maxy) {
                    maxy = vec[1];
                }
                vec.clear();
                break;
            }
            if (a != '\t') {
                buf.pushback(a);
            } else {
                vec.pushback(ToInt(buf));
                buf.clear();
            }
        }
    }

    height = (maxy + 1);
    width = (maxx + 1);

    for (int i = 0; i < height; i++) {
        field.pushback(vector<int>(width));
    }

    for (int i = 0; i < coords.size(); i++) {
        field[coords[i][1]][coords[i][0]] = coords[i][2];
    }
}

vector<vector<int>> &Sandpile::GetField() {
    return field;
}

std::string &Sandpile::GetTsv() {
    return tsv;
}

void Sandpile::Work(std::string& path) {
    for (int i = 1; i <= iterations; i++) {
        OneIter();
        if (i % frequency == 0) {
            BMP bmp(width, height, field);
            std::string name = path + std::to_string(i) + ".bmp"; // the name of the file is the number of iterations
            bmp.MakeFile(name);
        }
    }
}

void Sandpile::OneIter() {
    height = field.size();
    width = field[0].size();

    vector<std::pair<int, int>> help;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (field[y][x] > 3) {

                if (y - 1 < 0) { // upper overflow
                    field.insert(vector<int>(width));
                    height++;
                    y++;
                    for (int i = 0; i < help.size(); i++) {
                        help[i].first++;
                    }
                }
                if (y + 1 == height) { // lower overflow
                    field.pushback(vector<int>(width));
                    height++;
                }
                if (x - 1 < 0) { // left overflow
                    for (int i = 0; i < height; i++) {
                        field[i].insert(0);
                    }
                    width++;
                    x++;
                    for (int i = 0; i < help.size(); i++) {
                        help[i].second++;
                    }
                }
                if (x + 1 == width) { // right overflow
                    for (int i = 0; i < height; i++) {
                        field[i].pushback(0);
                    }
                    width++;
                }
                help.pushback({y, x});
            }
        }
    }

    for (int i = 0; i < help.size(); i++) {
        std::pair<int, int> cur = help[i];
        field[cur.first][cur.second] -= 4;
        field[cur.first - 1][cur.second]++;
        field[cur.first + 1][cur.second]++;
        field[cur.first][cur.second - 1]++;
        field[cur.first][cur.second + 1]++;
    }

    help.clear();

}

int Sandpile::GetWidth() {
    return width;
}

int Sandpile::GetHidth() {
    return height;
}