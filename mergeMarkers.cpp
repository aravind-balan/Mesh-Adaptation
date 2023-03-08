#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

std::vector<std::string> su2_reader(std::ifstream &);
int find_nvariables(std::vector<std::string>, int, int[], int[], int[], int[], int *[], std::string *[]);
std::vector<std::string> *getNewMarkers(std::ifstream &, int &);
int search_index(std::string, std::string *[], int);
std::vector<std::string> *getMergedMarkerLines(std::vector<std::string>, std::vector<std::string> *, std::string *[], int *[], int[], int, int);
void putMergedMarkers(std::string, std::vector<std::string>, std::vector<std::string> *, int[], int);

int main()
{
  int merge_count, ndime[2], npoin[2], nelem[2], nmark[2], number_of_lines, *marker_elems[2], new_nmark, *new_marker_elems;
  std::string FName, *merge_names, *marker_tags[2];
  std::vector<std::string> line_data;
  std::vector<std::string> *new_markers, *new_marker_data;
  std::ifstream input_mesh, marker_tag_details;

  std::cout << "Enter the grid filename: ";
  std::cin >> FName;

  input_mesh.open(FName);
  if (!input_mesh)
  {
    std::cerr << "Mesh file not found. Exiting...\n";
    exit(EXIT_FAILURE);
  }

  line_data = su2_reader(input_mesh);
  number_of_lines = line_data.size();

  std::cout << "Number of lines: " << number_of_lines << std::endl;
  find_nvariables(line_data, number_of_lines, ndime, npoin, nelem, nmark, marker_elems, marker_tags);
  std::cout << "The line numbers are 1 less than the actual line numbers since indices start from zero and line numbers from one.\n\n";
  std::cout << "----------------|---------------|------------------\n";
  std::cout << "Variable    \t|Value\t\t|Line Number" << std::endl;
  std::cout << "----------------|---------------|------------------\n";
  std::cout << "Dimensions  \t|" << ndime[0] << "\t\t|" << ndime[1] << std::endl;
  std::cout << "Points      \t|" << npoin[0] << "\t\t|" << npoin[1] << std::endl;
  std::cout << "Elements    \t|" << nelem[0] << "\t\t|" << nelem[1] << std::endl;
  std::cout << "Markers     \t|" << nmark[0] << "\t\t|" << nmark[1] << std::endl;
  for (int i = 0; i < nmark[0]; i++)
  {
    std::cout << "Markers Tag \t|" << marker_tags[0][i] << "\t\t|" << marker_tags[1][i] << std::endl;
    std::cout << "Marker Elem \t|" << marker_elems[0][i] << "\t\t|" << marker_elems[1][i] << std::endl;
  }
  std::cout << "----------------|---------------|------------------\n\n";

  marker_tag_details.open(FName + ".fix");
  if (!marker_tag_details)
  {
    std::cerr << "File to fix either does not exist or has an incorrect name. Please create the filename with the name \"" << FName << ".fix\"\n"
              << "The format for the file is as follows\n\n"
              << "total_new_marker_count\n"
              << "new_marker_name1 old_marker_name1 old_marker_name2 ...\n"
              << "new_marker_name2 old_marker_name3 old_marker_name4 ...\n"
              << ".\n.\n.\n";
    exit(EXIT_FAILURE);
  }
  new_markers = getNewMarkers(marker_tag_details, new_nmark);
  new_marker_elems = new int[new_nmark];
  new_marker_data = getMergedMarkerLines(line_data, new_markers, marker_tags, marker_elems, new_marker_elems, new_nmark, nmark[0]);
  putMergedMarkers(FName, line_data, new_marker_data, nmark, new_nmark);

  std::cout << "----------------|---------------|------------------\n";
  std::cout << "Variable    \t|Value\t\t|Line Number" << std::endl;
  std::cout << "----------------|---------------|------------------\n";
  std::cout << "Dimensions  \t|" << ndime[0] << "\t\t|" << ndime[1] << std::endl;
  std::cout << "Points      \t|" << npoin[0] << "\t\t|" << npoin[1] << std::endl;
  std::cout << "Elements    \t|" << nelem[0] << "\t\t|" << nelem[1] << std::endl;
  std::cout << "Markers     \t|" << new_nmark << "\t\t|" << nmark[1] << std::endl;
  int line = nmark[1] + 1;
  for (int i = 0; i < new_nmark; i++)
  {
    std::cout << "Markers Tag \t|" << new_markers[i][0] << "\t\t|" << line << std::endl;
    std::cout << "Marker Elem \t|" << new_marker_elems[i] << "\t\t|" << line + 1 << std::endl;
    line = line + new_marker_data[i].size();
  }
  std::cout << "----------------|---------------|------------------\n\n";
  return 0;
}

int find_nvariables(std::vector<std::string> line_data, int line_count, int dimension[], int points[], int elements[], int markers[], int *marker_elems[], std::string *marker_tags[])
{
  int i, marker_counter = 0;
  char first_char;
  std::stringstream dump;
  std::string variable_name, variable_value;
  for (i = 0; i < line_count; i++)
  {
    first_char = line_data[i].at(0);
    dump << line_data[i];
    if (first_char == '%')
    {
      dump.clear();
      dump.str("");
      continue;
    }
    else if (isalpha(first_char))
    {
      if (first_char == 'N')
      {
        getline(dump, variable_name, '=');
        boost::trim(variable_name);
        getline(dump, variable_value);
        boost::trim(variable_value);
        std::cout << "Found " << variable_name << std::endl;

        if (variable_name == "NDIME")
        {
          dimension[0] = std::stoi(variable_value);
          dimension[1] = i;
          if (dimension[0] > 3)
          {
            std::cout << "Incorrect dimension. Exiting...\n";
            exit(EXIT_FAILURE);
          }
        }
        else if (variable_name == "NPOIN")
        {
          points[0] = std::stoi(variable_value);
          points[1] = i;
        }
        else if (variable_name == "NELEM")
        {
          elements[0] = std::stoi(variable_value);
          elements[1] = i;
        }
        else if (variable_name == "NMARK")
        {
          markers[0] = std::stoi(variable_value);
          markers[1] = i;
          marker_tags[0] = new std::string[markers[0]];
          marker_tags[1] = new std::string[markers[0]];

          marker_elems[0] = new int[markers[0]];
          marker_elems[1] = new int[markers[0]];
        }
      }
      else if (first_char == 'M')
      {
        getline(dump, variable_name, '=');
        boost::trim(variable_name);
        getline(dump, variable_value);
        boost::trim(variable_value);
        if (variable_name == "MARKER_TAG")
        {
          marker_tags[0][marker_counter] = variable_value;
          marker_tags[1][marker_counter] = std::to_string(i);
        }
        else if (variable_name == "MARKER_ELEMS")
        {
          marker_elems[0][marker_counter] = std::stoi(variable_value);
          marker_elems[1][marker_counter] = i;
          i += marker_elems[0][marker_counter++];
        }
      }
    }
    dump.clear();
    dump.str("");
  }
  return EXIT_SUCCESS;
}

std::vector<std::string> su2_reader(std::ifstream &input_mesh)
{

  std::vector<std::string> line_dump;
  std::string line;
  std::cout << "Reading the mesh\n";

  while (getline(input_mesh, line))
  {
    boost::trim(line);
    line_dump.push_back(line);
  }
  input_mesh.close();
  return line_dump;
}

std::vector<std::string> *getNewMarkers(std::ifstream &marker_details, int &new_markers)
{
  std::vector<std::string> *marker_dump;
  std::string line, marker_name;
  std::stringstream dump;
  // int new_markers;
  getline(marker_details, line);
  new_markers = std::stoi(line);
  marker_dump = new std::vector<std::string>[new_markers];
  for (int i = 0; i < new_markers; i++)
  {
    getline(marker_details, line);
    dump.str(line);

    while (getline(dump, marker_name, ' '))
    {
      marker_dump[i].push_back(marker_name);
    }
    dump.clear();
    dump.str("");
  }
  return marker_dump;
}

int search_index(std::string marker, std::string *marker_tags[], int nmark)
{
  int index = -1;
  for (int i = 0; i < nmark; i++)
  {
    if (marker == marker_tags[0][i])
    {
      index = i;
    }
  }
  return index;
}

std::vector<std::string> *getMergedMarkerLines(std::vector<std::string> linedata, std::vector<std::string> *marker_dump, std::string *marker_tags[], int *marker_elems[], int new_marker_elems[], int new_nmark, int nmark)
{
  std::vector<std::string> *new_marker_lines;
  new_marker_lines = new std::vector<std::string>[new_nmark];
  int index, elements;
  for (int i = 0; i < new_nmark; i++)
  {
    elements = 0;
    new_marker_lines[i].push_back("MARKER_TAG= " + marker_dump[i][0]);
    new_marker_lines[i].push_back("MARKER_ELEMS= ");
    for (int j = 1; j < marker_dump[i].size(); j++)
    {
      index = search_index(marker_dump[i][j], marker_tags, nmark);
      if (index == -1)
      {
        std::cout << "Marker name \"" << marker_dump[i][j] << "\" not found in existing markers.\nPlease fix the file.\n";
        exit(EXIT_SUCCESS);
      }
      elements += marker_elems[0][index];

      for (int k = 1; k <= marker_elems[0][index]; k++)
      {
        new_marker_lines[i].push_back(linedata[marker_elems[1][index] + k]);
      }
    }
    new_marker_elems[i] = elements;
    new_marker_lines[i].at(1) = "MARKER_ELEMS= " + std::to_string(elements);
  }

  return new_marker_lines;
}

void putMergedMarkers(std::string Filename, std::vector<std::string> line_data, std::vector<std::string> *marker_dump, int nmark[], int new_nmark)
{
  std::ofstream MergedMesh;
  MergedMesh.open("fixed_" + Filename);
  for (int linenumber = 0; linenumber < nmark[1]; linenumber++)
  {
    MergedMesh << line_data[linenumber] << std::endl;
  }
  MergedMesh << "NMARK= " + std::to_string(new_nmark) + "\n";

  for (int i = 0; i < new_nmark; i++)
  {
    for (int j = 0; j < marker_dump[i].size(); j++)
    {
      MergedMesh << marker_dump[i][j] << std::endl;
    }
  }
  MergedMesh.close();
}