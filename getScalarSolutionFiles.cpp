#include <iostream>
#include <fstream>
#include <string>

void generateSolutionFiles(std::string, int);
std::ofstream initializeFiles(std::string, int);

// void writeSolFiles(double, double, double, double, double, double, double, double, double);
int main()
{
    std::string FName = "restart_flow.csv";
    int vertex_count;
    std::cout << "Enter Vertex Count: ";
    std::cin >> vertex_count;
    generateSolutionFiles(FName, vertex_count);
    std::cout << "\n--------EXIT SUCCESS--------\n";
    return 0;
}

std::ofstream initializeFiles(std::string Filename, int n)
{
    std::ofstream File;
    std::cout << "Initializing " << Filename << std::endl;
    int dimension = 3;

#ifdef TWOD
    dimension = 2;
#endif

    File.open(Filename);
    if (!File)
    {
        std::cout << "Could not create " << Filename << std::endl;
        return File;
    }
    File.precision(20);
    File << "MeshVersionFormatted 1\n";
    File << "\nDimension " << dimension << "\n"
         << "\nSolAtVertices\n"
         << n << std::endl
         << "1 1\n";

    return File;
}
void generateSolutionFiles(std::string FileName, int n)
{
    std::ifstream DataFile(FileName);
    std::ofstream DensityFile, XmomFile, YmomFile, ZmomFile, EnergyFile, PressureFile, TemperatureFile, MachFile, CPFile;
    if (!DataFile)
    {
        std::cout << "Unable to open " << FileName;
        return;
    }

    std::string dump;
    int PointID;
    double x, y, z, density, x_mom, y_mom, z_mom, energy, pressure, temperature, mach, cp;
    getline(DataFile, dump);

    DensityFile = initializeFiles("./sol/density.sol", n);
    XmomFile = initializeFiles("./sol/xmom.sol", n);
    YmomFile = initializeFiles("./sol/ymom.sol", n);
#ifndef TWOD
    ZmomFile = initializeFiles("./sol/zmom.sol", n);
#endif
    EnergyFile = initializeFiles("./sol/energy.sol", n);
    PressureFile = initializeFiles("./sol/pressure.sol", n);
    TemperatureFile = initializeFiles("./sol/temperature.sol", n);
    MachFile = initializeFiles("./sol/mach.sol", n);
    CPFile = initializeFiles("./sol/cp.sol", n);

    for (int linecounter = 0; linecounter < n; linecounter++)
    {

        getline(DataFile, dump, ',');
        PointID = std::stoi(dump);

        getline(DataFile, dump, ',');
        x = std::stod(dump);

        getline(DataFile, dump, ',');
        y = std::stod(dump);
#ifndef TWOD
        getline(DataFile, dump, ',');
        z = std::stod(dump);
#endif
        getline(DataFile, dump, ',');
        if (DensityFile)
        {
            density = std::stod(dump);
            DensityFile << std::endl
                        << density;
        }

        getline(DataFile, dump, ',');
        if (XmomFile)
        {
            x_mom = std::stod(dump);
            XmomFile << std::endl
                     << x_mom;
        }

        getline(DataFile, dump, ',');
        if (YmomFile)
        {
            y_mom = std::stod(dump);
            YmomFile << std::endl
                     << y_mom;
        }
#ifndef TWOD
        getline(DataFile, dump, ',');
        if (ZmomFile)
        {
            z_mom = std::stod(dump);
            ZmomFile << std::endl
                     << z_mom;
        }
#endif
        getline(DataFile, dump, ',');
        if (EnergyFile)
        {
            energy = std::stod(dump);
            EnergyFile << std::endl
                       << energy;
        }
#ifdef VISCOUS
        getline(DataFile, dump, ','); // get Nu_Tilde and ignores the input
#endif
        getline(DataFile, dump, ',');

        if (PressureFile)
        {
            pressure = std::stod(dump);
            PressureFile << std::endl
                         << pressure;
        }

        getline(DataFile, dump, ',');
        if (TemperatureFile)
        {
            temperature = std::stod(dump);
            TemperatureFile << std::endl
                            << temperature;
        }

        getline(DataFile, dump, ',');
        if (MachFile)
        {
            mach = std::stod(dump);
            MachFile << std::endl
                     << mach;
        }
#ifdef VISCOUS
        getline(DataFile, dump, ',');
#endif
#ifndef VISCOUS
        getline(DataFile, dump, '\n');
#endif
        if (CPFile)
        {
            cp = std::stod(dump);
            CPFile << std::endl
                   << cp;
        }
#ifdef VISCOUS
        getline(DataFile, dump, '\n'); // Gets all the viscous flow variables after CP and ignores the input
#endif
    }

    DensityFile << "\n\nEND";
    XmomFile << "\n\nEND";
    YmomFile << "\n\nEND";
    ZmomFile << "\n\nEND";
    EnergyFile << "\n\nEND";
    PressureFile << "\n\nEND";
    TemperatureFile << "\n\nEND";
    MachFile << "\n\nEND";
    CPFile << "\n\nEND";

    DataFile.close();
    DensityFile.close();
    XmomFile.close();
    YmomFile.close();
    ZmomFile.close();
    EnergyFile.close();
    PressureFile.close();
    TemperatureFile.close();
    MachFile.close();
    CPFile.close();
}
