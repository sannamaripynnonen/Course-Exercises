/* Tramway
 *
 * Desc:
 * Program reads a file and generates a data structure with tram lines and
 * stations. User can enter the following commands:
 * QUIT - Ends program
 * LINES - Lists all lines in alphabetical order
 * LINE <route> - Lists all the stations on the line
 * STATIONS - Lists all stations in alphabetical order
 * STATION <stop> - Lists all the lines that include the station
 * ADDLINE <route> - Adds a new line
 * ADDSTATION <route> <new stop> <next stop> - Adds a new station
 * REMOVE <stop> - Removes the station from all lines
 *
 * Program author
 * Name: Sannamari Pynnönen
 *
 * Notes about the program and it's implementation:
 * */

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

using Tramlines = std::map<std::string, std::vector<std::string>>;
const std::string ERROR = "Error: Station/line already exists.";

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

// Copied from network.
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// Done during weekly exercise.
bool read_data(Tramlines& tramlines){
    std::string input = "";
    std::cout << "Give a name for input file: ";
    std::getline(std::cin, input);

    std::ifstream file(input);

    if(!file){
        std::cout << "Error: File could not be read." << std::endl;
        return false;
    }

    std::vector<std::string> line_parts = {};
    std::string line = "";

    while(std::getline(file, line)){
        line_parts = split(line, ';');

        // Checks that format is correct.
        if(line_parts.size() != 2 || line_parts.at(0).size() == 0
                                  || line_parts.at(1).size() == 0){
            std::cout << "Error: Invalid format in file." << std::endl;
            return false;
        }

        std::string tram_line = line_parts.at(0);
        std::string new_stop = line_parts.at(1);

        if(tramlines.find(tram_line) == tramlines.end()){
            tramlines.insert({tram_line, {} } );
        }

        for(std::string station : tramlines.at(tram_line)){
            if(station == new_stop){
                std::cout << "Error: Station/line already exists." << std::endl;
                return false;
            }

        }
        // Add stop to existing tramline.
        tramlines.at(tram_line).push_back(new_stop);

    }
    file.close();
    return true;
    
}

// Adds a new line to the data structure.
void command_add_line(Tramlines& tramlines, std::string new_line){
    if (tramlines.find(new_line) != tramlines.end()){
        std::cout << ERROR << std::endl;
    }

    else{
        tramlines[new_line]={};
        std::cout << "Line was added." << std::endl;
    }

}

// Adds a new station to the line.
void command_add_station(Tramlines& tramlines, std::string line,
                         std::string new_station, std::string next_station){
    if (tramlines.find(line) != tramlines.end()){
        //Checks if new station is already added.
        std::vector<std::string>::iterator iter
                = std::find(tramlines[line].begin(), tramlines[line].end(), new_station);
        if(iter != tramlines[line].end()){
            std::cout << ERROR << std::endl;
        }
        else{
            // If there is no next station.
            if(next_station == ""){
                tramlines[line].push_back(new_station);
                std::cout << "Station was added." << std::endl;
            }
            // If the next station is given.
            else{
                std::vector<std::string>::iterator iter
                        = std::find(tramlines[line].begin(), tramlines[line].end(), next_station);
                if(iter != tramlines[line].end()){
                    iter = tramlines[line].insert(iter, new_station);
                    std::cout << "Station was added." << std::endl;
                }
                else{
                    tramlines[line].push_back(new_station);
                    std::cout << "Station was added." << std::endl;
                }
            }
        }
    }
    else {
        std::cout << ERROR << std::endl;
    }
}

// Prints all tramlines in alphabetical order.
void command_all_lines(Tramlines& tramlines){
    std::set<std::string> all_lines;

    for(std::pair<std::string, std::vector<std::string>> line : tramlines){
        all_lines.insert(line.first);
        }

    std::cout << "All tramlines in alphabetical order:" << std::endl;

    for(std::string line : all_lines){
        std::cout << line << std::endl;
    }
}

// Prints the stations on the tramline.
void command_line(Tramlines& tramlines, std::string line){
    std::vector<std::string> all_lines;

    // Checks if line is found.
    if(tramlines.find(line) != tramlines.end()){
        std::cout << "Line " << line <<
                     " goes through these stations in the order they are listed:" << std::endl;
    }
    else{
        std::cout << "Error: Line could not be found." << std::endl;
        return;
    }

    // Makes a vector of all stations on the line.
    for(std::pair<std::string, std::vector<std::string>> tram_line : tramlines){
        if (tram_line.first == line){
            for (std::string stop_name : tram_line.second){
                all_lines.push_back(stop_name);
            }
        }
    }

    for(std::string line : all_lines){
        std::cout << " - " << line << std::endl;
    }
}

// Removes the station from all lines.
void command_remove(Tramlines& tramlines, std::string station){

    bool b = false;

    for(std::pair<std::string, std::vector<std::string>> line : tramlines){
        for (std::string stop_name : line.second){
            if(station == stop_name){
                b = true;
                tramlines[line.first].erase(std::remove(tramlines[line.first].begin(),
                                            tramlines[line.first].end(), station),
                                            tramlines[line.first].end());
            }
        }
    }
    if ((b == true)){
        std::cout << "Station was removed from all lines." << std::endl;
    }
    else{
        std::cout << "Error: Station could not be found." << std::endl;
    }
}

// Done during weekly exercise. Prints the lines where the station is found.
void command_station(Tramlines tramlines, std::string station){
    std::set<std::string> all_lines;

    for(std::pair<std::string, std::vector<std::string>> line : tramlines){
        for(std::string stop_name : line.second){
            if(station == stop_name){
                all_lines.insert(line.first);
            }
        }
    }

    if(all_lines.empty()){
        std::cout << "Error: Station could not be found." << std::endl;
        return;
    }
    std::cout << "Station " << station << " can be found on the following lines:" << std::endl;
    for (std::string line : all_lines){
        std::cout << " - " << line << std::endl;
    }

}

// Prints all the stations in alphabetical order.
void command_all_stations(Tramlines& tramlines){
    std::set<std::string> all_stations;

    for(std::pair<std::string, std::vector<std::string>> line : tramlines){
        for (std::string stop_name : line.second){
            all_stations.insert(stop_name);
        }
    }

    std::cout << "All stations in alphabetical order:" << std::endl;

    for(std::string station : all_stations){
        std::cout << station << std::endl;
    }
}

void user_input(Tramlines lines){

    std::string input = "";
    std::cout << "tramway> ";

    std::vector<std::string> parts = {};

    while(std::getline(std::cin, input)){
        parts = split(input, ' ');

        std::string cmd = parts.at(0);
        std::transform(cmd.begin(), cmd.end(), cmd.begin(),::toupper);

        if (cmd == "QUIT" || cmd == "Q"){
            return;
        }
        else if (cmd == "ADDLINE" && parts.size() == 2){
            command_add_line(lines, parts.at(1));
        }
        else if (cmd == "ADDSTATION" && parts.size() == 3){
            command_add_station(lines, parts.at(1), parts.at(2), "");
        }
        else if (cmd == "ADDSTATION" && parts.size() == 4){
            command_add_station(lines, parts.at(1), parts.at(2), parts.at(3));
        }
        else if (cmd == "LINES" && parts.size() == 1){
            command_all_lines(lines);
        }
        else if (cmd == "LINE" && parts.size() == 2){
            command_line(lines, parts.at(1));
        }
        else if (cmd == "STATION" && parts.size() == 2){
            command_station(lines, parts.at(1));
        }
        else if (cmd == "STATIONS" && parts.size() == 1){
            command_all_stations(lines);
        }
        else if (cmd == "REMOVE" && parts.size() == 2){
            command_remove(lines, parts.at(1));
        }
        else {
            std::cout << "Error: Invalid input." << std::endl;
        }
        std::cout << "tramway> ";
    }
}

// Short and sweet main.
int main()
{
    print_rasse();

    Tramlines tramlines;


    if(!read_data(tramlines)){
        return EXIT_FAILURE;
    }

    user_input(tramlines);

    return EXIT_SUCCESS;
}
