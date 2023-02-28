#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>

std::string *su2_reader(std::ifstream &, int);
int find_nvariables(std::string *, int, int[], int[], int[], int[], int *[], std::string *[]);
int main()
{
  int count_lines(std::ifstream &);

  int merge_count, ndime[2], npoin[2], nelem[2], nmark[2], number_of_lines, *marker_elems[2];
  std::string FName, *line_data, *merge_names, *marker_tags[2];
  std::cout << "Enter the grid filename: ";
  std::cin >> FName;

  std::ifstream input_mesh;

  input_mesh.open(FName);
  number_of_lines = count_lines(input_mesh);
  input_mesh.open(FName);
  line_data = su2_reader(input_mesh, number_of_lines);
  find_nvariables(line_data, number_of_lines, ndime, npoin, nelem, nmark, marker_elems, marker_tags);

  std::cout << "Variable    \t\tValue\t\tLine Number" << std::endl;
  std::cout << "Dimensions: \t\t" << ndime[0] << "\t\t" << ndime[1] << std::endl;
  std::cout << "Points:     \t\t" << npoin[0] << "\t\t" << npoin[1] << std::endl;
  std::cout << "Elements:   \t\t" << nelem[0] << "\t\t" << nelem[1] << std::endl;
  std::cout << "Markers:    \t\t" << nmark[0] << "\t\t" << nmark[1] << std::endl;
  for (int i = 0; i < nmark[0]; i++)
  {
    std::cout << "Markers Tag:\t\t" << marker_tags[0][i] << "\t\t" << marker_tags[1][i] << std::endl;
    std::cout << "Marker Elem:\t\t" << marker_elems[0][i] << "\t\t" << marker_elems[1][i] << std::endl;
  }

  std::cout << "Enter the number of markers you want to merge: ";
  std::cin >> merge_count;
  if (merge_count == nmark[0])
  {
    char ch = 'n';
    std::cout << "This will merge all the markers into one. Are you sure?(y/N)\n";
  }
  merge_names = new std::string[merge_count];

  std::cout << "Enter the names of the markers you want to merge (case sensitive):\n";
  for (int i = 0; i < merge_count; i++)
  {
    std::cout << i + 1 << ". : ";
    std::cin >> merge_names[i];
  }

  return 0;
}

int find_nvariables(std::string *line_data, int line_count, int dimension[], int points[], int elements[], int markers[], int *marker_elems[], std::string *marker_tags[])
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

        if (variable_name == "NDIME")
        {
          std::cout << "Found NDIME\n";
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
          std::cout << "Found NPOIN\n";
          points[0] = std::stoi(variable_value);
          points[1] = i;
        }
        else if (variable_name == "NELEM")
        {
          std::cout << "Found NELEM\n";
          elements[0] = std::stoi(variable_value);
          elements[1] = i;
        }
        else if (variable_name == "NMARK")
        {
          std::cout << "Found NMARK\n";
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

std::string *su2_reader(std::ifstream &input_mesh, int number_of_lines)
{

  std::string *line_dump;
  std::cout << "Reading the mesh\n";
  line_dump = new std::string[number_of_lines];

  for (int i = 0; i < number_of_lines; i++)
  {
    getline(input_mesh, line_dump[i]);
    boost::trim(line_dump[i]);
  }
  input_mesh.close();
  return line_dump;
}

int count_lines(std::ifstream &input_mesh)
{
  std::string dump;
  int counter = 0;
  std::cout << "Counting lines\n";

  while (std::getline(input_mesh, dump))
  {
    counter++;
  }
  input_mesh.close();
  return counter;
}