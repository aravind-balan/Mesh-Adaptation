#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

std::vector<std::string> su2_reader(std::ifstream &);
int find_nvariables(std::vector<std::string>, int, int[], int[], int[], int[], int *[], std::string *[]);

int main()
{
  int count_lines(std::ifstream &);

  int merge_count, ndime[2], npoin[2], nelem[2], nmark[2], number_of_lines, *marker_elems[2];
  std::string FName, *merge_names, *marker_tags[2];
  std::vector<std::string> line_data;
  std::cout << "Enter the grid filename: ";
  std::cin >> FName;

  std::ifstream input_mesh, marker_tag_details;

  // input_mesh.open(FName);
  // number_of_lines = count_lines(input_mesh);
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

  std::cout << "----------------|---------------|------------------\n";
  std::cout << "Variable    \t|\tValue\t|\tLine Number" << std::endl;
  std::cout << "----------------|---------------|------------------\n";
  std::cout << "Dimensions  \t|\t" << ndime[0] << "\t|\t" << ndime[1] << std::endl;
  std::cout << "Points      \t|\t" << npoin[0] << "\t|\t" << npoin[1] << std::endl;
  std::cout << "Elements    \t|\t" << nelem[0] << "\t|\t" << nelem[1] << std::endl;
  std::cout << "Markers     \t|\t" << nmark[0] << "\t|\t" << nmark[1] << std::endl;
  for (int i = 0; i < nmark[0]; i++)
  {
    std::cout << "Markers Tag \t|\t" << marker_tags[0][i] << "\t|\t" << marker_tags[1][i] << std::endl;
    std::cout << "Marker Elem \t|\t" << marker_elems[0][i] << "\t|\t" << marker_elems[1][i] << std::endl;
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
