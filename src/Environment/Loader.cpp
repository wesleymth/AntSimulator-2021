#include "Loader.hpp"
#include "Utility/Utility.hpp"
#include "Application.hpp"
#include "Environment.hpp"
#include <iostream>
#include "Termite.hpp"
#include "./Utility/Constants.hpp"

Loader::Loader()
{
    //done
}

void loadMap(std::string const& filepath)
{
    std::ifstream file; // déclaration du flot en lecture
    file.open(filepath.c_str()); // le flot est lié au fichier "test"
    if (! file.fail()) {
        std::string line;
        std::string word;
        std::vector<std::string> words;
        while (!file.eof())
        {
            getline(file, line);
            std::cout << line << std::endl; // test
            if (! file.fail()) // on a effectivement pu lire qqchose
            {
                if (line[0]!='#' and line.size()>1)
                {
                    for(size_t i(0); i<line.size()-1; ++i)
                    {
                        while(line[i]!=' ' and i<line.size())
                        {
                            word+=line[i];
                            ++i;
                        }
                        if(not word.empty())
                        {
                            words.push_back(word);
                        }
                        word.clear();
                    }
                    try
                    {
                        if (words[0]=="anthill")
                        {
                            if(words.size()==3)
                            {
                                getAppEnv().addAnthill(new Anthill(Vec2d(std::stod(words[1]), std::stod(words[2]))));// *** A decommenter
                            } else {
                                throw getAppConfig().ERROR_LOADER_INCORRECT_ARGUMENTS;
                            }
                        } else if (words[0]=="termite") {
                            if(words.size()==3)
                            {
                                getAppEnv().addAnimal(new Termite(Vec2d(std::stod(words[1]), std::stod(words[2]))));//  *** A decommenter
                            } else {
                                throw getAppConfig().ERROR_LOADER_INCORRECT_ARGUMENTS;
                            }
                        } else if (words[0]=="food") {
                            if(words.size()==4)
                            {
                                getAppEnv().addFood(new Food(Vec2d(std::stod(words[1]), std::stod(words[2])), std::stod(words[3])));  // *** A decommenter
                            } else {
                                throw getAppConfig().ERROR_LOADER_INCORRECT_ARGUMENTS;
                            }
                        } else {
                            std::cerr << "invalid argument provided for type"<< std::endl;
                        }
                    }
                    catch (int i) {
                        if (i==getAppConfig().ERROR_LOADER_INCORRECT_ARGUMENTS)
                        {
                            std::cerr << "incorrect number of arguments provided for " << words[0] << " construction" << std::endl;
                        }
                    }  catch (const std::invalid_argument&) {
                        std::cerr << "Argument is invalid -> no possible conversion to double";
                    }   catch (const std::out_of_range&) {
                                std::cerr << "Argument is out of range for a double";
                    }
                    words.clear();
                }
            }
        }
        file.close (); // fermeture du flot
    } else {
    std::cerr << "Ouverture du fichier " << filepath << " impossible." << std::endl;
    }
}


