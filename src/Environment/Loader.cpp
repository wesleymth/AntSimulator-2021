#include "Loader.hpp"
#include "Utility/Utility.hpp"
#include "Application.hpp"
#include <fstream>
#include <string>
#include "Environment.hpp"

Loader::Loader()
{

}

void loadMap(std::string const& filepath)
{
    ifstream file; // déclaration du flot en lecture
    file.open(filepath.c_str()); // le flot est lié au fichier "test"
    if (! file.fail()) {
        string line;
        string word;
        vector<string> words;
        while (!file.eof())
        {
            file >> ws
            getline(file, line);
            if (! file.fail()) // on a effectivement pu lire qqchose
            {
                if (line[0]!='#')
                {
                    for(size_t i(0); i<line.size(); ++i)
                    {
                        while(line[i]!=' ' and i<line.size())
                        {
                            word.pushback(line[i]);
                        }
                        words.pushback(word);
                    }
                    try
                    {
                        Switch(words[0])
                        {
                            case "anthill":
                                if(words.size=3)
                                {
                                    getAppEnv.addAnthill(Vec2d(std::stod(words[1]), std::stod(words[2])));
                                } else {
                                    throw "insufficient arguments";
                                }
                                break;
                            case "termite":
                                if(words.size=3)
                                {
                                    getAppEnv.addTermite(Vec2d(std::stod(words[1]), std::stod(words[2])));
                                } else {
                                    throw "insufficient arguments";
                                }
                                break;


                        }
                    }  catch ("insufficient arguments") {
                        cerr << "insufficient arguments provided for" << words << "construction" <<endl;
                    }


                }
            }
        }
        file.close (); // fermeture du flot
    } else {
    cerr << "Ouverture du fichier " << filepath << " impossible." << endl;
    }
}
