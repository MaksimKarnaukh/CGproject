#include "easy_image.h"
#include "ini_configuration.h"
#include "Lsysteem.h"
#include "L2Dsysteem.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

img::EasyImage generate_image(const ini::Configuration &configuration)
{
    string type = configuration["General"]["type"].as_string_or_die();
    string inputFile;
    vector<double> color;
    vector<double> backgroundColor;
    int size = 0;
    // parsen van .ini bestand
    if (type == "2DLSystem") {
        size = configuration["General"]["size"].as_int_or_die();
        backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
        inputFile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
        color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    }
    L2Dsysteem a = L2Dsysteem();
    std::list<Line2D> lines = a.parse(inputFile, color);
    return draw2DLines(lines, size, backgroundColor);

// oef 1 lijnen (gecentreerd)
//    std::list<Line2D> lines;
//    Point2D punt1;
//    punt1.x = 0;
//    punt1.y = 100;
//
//    Point2D punt2;
//    punt2.x = 100;
//    punt2.y = 0;
//
//    Color kleur;
//    kleur.red = 0.8;
//    kleur.blue = 0;
//    kleur.green = 0;
//    Line2D lijn1 = Line2D(punt1, punt2, kleur);
//    lines.push_back(lijn1);
//    return draw2DLines(lines, 200);
//    std::list<Line2D> lines;
//    for (auto i = 0; i < 5; i++) {
//        Point2D punt1;
//        punt1.x = i+1;
//        punt1.y = 10;
//
//        Point2D punt2;
//        punt2.x = 10*i+1;
//        punt2.y = 20+10*i;
//
//        Color kleur;
//        kleur.red = 0.8;
//        kleur.blue = 0;
//        kleur.green = 0;
//        Line2D lijn1 = Line2D(punt1, punt2, kleur);
//        lines.push_back(lijn1);
//    }
//    for (auto i = 0; i < 20; i++) {
//        Point2D punt1;
//        punt1.x = 100+10*i;
//        punt1.y = 10;
//
//        Point2D punt2;
//        punt2.x = 100+10*i;
//        punt2.y = 20+10*i;
//
//        Color kleur;
//        kleur.red = 1;
//        kleur.blue = 0;
//        kleur.green = 0;
//        Line2D lijn1 = Line2D(punt1, punt2, kleur);
//        lines.push_back(lijn1);
//    }

//    return draw2DLines(lines, 500);
}



int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                for(int i = 1; i < argc; ++i)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(argv[i]);
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string fileName(argv[i]);
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << argv[i] << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
