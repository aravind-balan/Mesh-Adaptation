#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

std::ofstream testreader(std::ifstream &);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Incorrect usage.\nUsage: " << argv[0] << " filename.vtu\n";
        exit(EXIT_FAILURE);
    }

    std::string filename;
    filename = argv[1];
    std::ifstream file;
    file.open(filename, std::ios_base::binary);
    if (!file)
    {
        std::cout << "File could not be open. Please check if the filename is correct or if the file exists\n";
        exit(EXIT_FAILURE);
    }

    std::ofstream outfile = testreader(file);
    outfile.close();
    file.close();
    return 0;
}

std::ofstream testreader(std::ifstream &infile)
{
    std::stringstream linestream;
    std::string line;
    char c[3];
    std::ofstream outfile;
    outfile.open("test.txt");
    linestream.clear();
    linestream.str("");
    do
    {
        infile.read(c, 1);
        linestream << c[0];
    } while (c[0] != '\n');
    line=linestream.str();
    std::cout << line;// << std::endl;
    int pos = infile.tellg();
    std::cout << "Length\tPosition\n" << line.length() << "\t" << pos << std::endl;
    return outfile;
}