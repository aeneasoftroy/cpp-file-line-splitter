/*
Program name: C++ file line splitter
Program date: 16-December-2017
Compiler: GNU GCC (Code::Blocks 13.12)
Coder: Stephan van de Kerkhof
Description: Little tool to process large data chunks fast, splits data until a delimiter has been found.
Usage: fls.exe -f <inputfile> -o <outputfile> -d <delimiter: tab, space, ',', ';', ':'>
Remarks: no additional libraries required
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;
// When we pass char arrays as parameters they must be pointers
int main(int argc, char* argv[]) {
    std::string theDelimiter, theFile, theOutfile;
    if (argc < 5) { // Check the value of argc. If not enough parameters have been passed, display a usage example and exit. It's set to 5 because we need 4 actual parameters, argv[0] is always the name of the program being ran, 1-4 being what we actually need, adds up to 5.
        std::cout << "Usage: "<< argv[0] << " " << "-f <infile> -d <delimiter> -o <outfile>" << endl; // usage example
        return(0);
    } else { // When there are enough parameters we proceed:
        //std::cout << argv[0];
        for (int i = 1; i < argc; i++) { // We scan / iterate over argv[] to get the parameters provided by the user.
            if (i + 1 != argc){
                // Use strcomp for comparing the values, remember that strcomp returns 0 when true.
                // We take the argv[i] value provided next (argv[i]+1) of the given switch as value of that switch.
                if(strcmp(argv[i], "-f") == 0 ){
                    theFile = argv[i + 1];
                }else if(strcmp(argv[i], "-d") == 0 ) {
                    theDelimiter = argv[i + 1];
                }else if(strcmp(argv[i], "-o") == 0 ) {
                    theOutfile = argv[i + 1];
                }
            }
            //Display the value of each switch:
            //std::cout << argv[i] << " ";
        }

        }
        // We open our output file outside of the loop where the data will be generated from
        ofstream outfile;
        outfile.open(theOutfile.c_str());
        // Start of the procedure
        // instead of file(theFile) we use file(theFile.c_str()) to fix the error: no matching function for call to 'std::basic_fstream<char>::basic_fstream(std::string&)'
        std::fstream file(theFile.c_str());
        std::string line;
        // Perform for every line inside the file of switch -s:
        while(std::getline(file, line))
        {
            std::stringstream   linestream(line);
            std::string         data;
            int                 val1;
            int                 val2;
            /* If the input file has tab delimited data, use getline() by changing the third parameter.
            If the input file is "white space" delimited, the operator ' ' can be used.
            */
            if(strcmp(theDelimiter.c_str(), "tab") == 0 ){
                    std::getline(linestream, data, '\t');
            } else if(strcmp(theDelimiter.c_str(), ";") == 0 ){
                    std::getline(linestream, data, ';');
            } else if(strcmp(theDelimiter.c_str(), ",") == 0 ){
                    std::getline(linestream, data, ',');
            } else if(strcmp(theDelimiter.c_str(), ":") == 0 ){
                    std::getline(linestream, data, ':');
            } else if(strcmp(theDelimiter.c_str(), "space") == 0 ){
                    std::getline(linestream, data, ' ');
            //now we run out of recognized user input, we can take whatever input as delimiter or error on the input
            } else {cout << "ERROR: " << theDelimiter << " " << "is a invalid delimiter parameter" << endl;
            return(0);
            }
            // Print the data that has been split
            cout << data << endl;
            // Save the data to the output file, which was previously, outside this loop, opened.
            outfile << data << std::endl;
            // Read the integers using the operator >>
            linestream >> val1 >> val2;
        }
        return 0;
    }
