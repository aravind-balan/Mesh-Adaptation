#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void generateSolutionFiles(std::string, int);
void initializeFiles(std::ofstream&, int);

void writeSolFiles(double, double, double, double, double, double, double, double, double);
int main()
{
    std::string FName = "restart_flow.csv";
    int vertex_count;
    std::cout << "Enter Vertex Count: ";
    std::cin >> vertex_count;
    generateSolutionFiles(FName, vertex_count);
    return 0;
}

void initializeFiles(std::ofstream &File, int n)
{
    File.precision(20);
    File << "MeshVersionFormatted 1\n";
    File << "\nDimension 3\n"
         << "\nSolAtVertices\n"
         << n << std::endl << "1 1\n";
}
void generateSolutionFiles(std::string FileName, int n)
{
    std::ifstream DataFile(FileName);
    if (!DataFile)
    {
        std::cout << "Unable to open " << FileName;
        return;
    }
    std::ofstream DensityFile("./sol/density.sol");
    if (!DensityFile)
    {
        std::cout << "Unable to open ./sol/density.sol";
        return;
    }
    std::ofstream XmomFile("./sol/xmom.sol");
    if (!XmomFile)
    {
        std::cout << "Unable to open ./sol/xmom.sol";
        return;
    }
    std::ofstream YmomFile("./sol/ymom.sol");
    if (!YmomFile)
    {
        std::cout << "Unable to open ./sol/ymom.sol";
        return;
    }
    std::ofstream ZmomFile("./sol/zmom.sol");
    if (!ZmomFile)
    {
        std::cout << "Unable to open ./sol/zmom.sol";
        return;
    }
    std::ofstream EnergyFile("./sol/energy.sol");
    if (!EnergyFile)
    {
        std::cout << "Unable to open ./sol/energy.sol";
        return;
    }
    std::ofstream PressureFile("./sol/pressure.sol");
    if (!PressureFile)
    {
        std::cout << "Unable to open ./sol/pressure.sol";
        return;
    }
    std::ofstream TemperatureFile("./sol/temperature.sol");
    if (!TemperatureFile)
    {
        std::cout << "Unable to open ./sol/temperature.sol";
        return;
    }
    std::ofstream MachFile("./sol/mach.sol");
    if (!MachFile)
    {
        std::cout << "Unable to open ./sol/mach.sol";
        return;
    }
    std::ofstream CPFile("./sol/cp.sol");
    if (!CPFile)
    {
        std::cout << "Unable to open ./sol/cp.sol";
        return;
    }
    std::string dump;
    int flag = 0;
    int PointID;
    double x, y, z, density, x_mom, y_mom, z_mom, energy, pressure, temperature, mach, cp;
    getline(DataFile, dump);
    std::cout << dump << std::endl;

    initializeFiles(DensityFile, n);
    initializeFiles(XmomFile, n);
    initializeFiles(YmomFile, n);
    initializeFiles(ZmomFile, n);
    initializeFiles(EnergyFile, n);
    initializeFiles(PressureFile, n);
    initializeFiles(TemperatureFile, n);
    initializeFiles(MachFile, n);
    initializeFiles(CPFile, n);   

    for (int linecounter = 0; linecounter < n; linecounter++)
    {
        std::cout.precision(20);
        getline(DataFile, dump, ',');
        PointID = std::stoi(dump);

        getline(DataFile, dump, ',');
        x = std::stod(dump);

        getline(DataFile, dump, ',');
        y = std::stod(dump);

        getline(DataFile, dump, ',');
        z = std::stod(dump);

        getline(DataFile, dump, ',');
        density = std::stod(dump);
        DensityFile << std::endl << density;

        getline(DataFile, dump, ',');
        x_mom = std::stod(dump);
        XmomFile << std::endl << x_mom;

        getline(DataFile, dump, ',');
        y_mom = std::stod(dump);
        YmomFile << std::endl << y_mom;

        getline(DataFile, dump, ',');
        z_mom = std::stod(dump);
        ZmomFile << std::endl << z_mom;

        getline(DataFile, dump, ',');
        energy = std::stod(dump);
        EnergyFile << std::endl << energy;

        getline(DataFile, dump, ',');
        pressure = std::stod(dump);
        PressureFile << std::endl << pressure;

        getline(DataFile, dump, ',');
        temperature = std::stod(dump);
        TemperatureFile << std::endl << temperature;

        getline(DataFile, dump, ',');
        mach = std::stod(dump);
        MachFile << std::endl << mach;

        getline(DataFile, dump, '\n');
        cp = std::stod(dump);
        CPFile << std::endl << cp;
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