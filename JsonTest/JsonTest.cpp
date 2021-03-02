// JsonTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "SettingReader.h"
#include <regex>

std::string filepathsufix = "\\Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\settings.json";
char* fileprefix = getenv("LOCALAPPDATA");
std::string filepath = fileprefix + filepathsufix;

//FOLDERID_AppDataDesktop
void printJson(json j, int l)
{
    std::cout << j.dump(4,' ');
}

void displayHelp()
{
    std::cout << "Usage: " << std::endl;
    std::cout << "\t --backgroundImage \t \t:\t Change the Background Image" << std::endl; 
    std::cout << "\t --bgImageOpacity \t \t:\t Change the Opacity of Background Image" << std::endl;
    std::cout << "\t --backgroundImageStretchMode \t:\t Change the strech mode of the background Image" << std::endl;
    std::cout << "\t --backgroundImageAlignment \t:\t Change Alignment Mode of the background Image" << std::endl;
    std::cout << "\t --useAcrylic \t \t \t:\t Change the background to use acrylic window managment" << std::endl;
    std::cout << "\t --acrylicOpacity \t \t:\t Change the opacity of the background" << std::endl;
    std::cout << "\t --padding \t \t \t:\t Change the padding of the text in the window" << std::endl;
    std::cout << "\t --tabColort \t \t:\t Change the color of the tab" << std::endl;
    std::cout << "\t --font \t \t \t:\t Change the font" << std::endl;
    std::cout << "\t --fontSize \t \t \t:\t Change the font size" << std::endl;
    std::cout << "\t --cursorShape \t \t \t:\t Change the shape of the cursor" << std::endl;
    std::cout << "\t --cursorSize \t \t \t:\t Change the size of the Vintage cursor" << std::endl;
    std::cout << "\t --phosphor \t \t \t:\t Use the built in Retro Display Shader Effect" << std::endl;
    std::cout << "\t --theme \t \t \t:\t set whether Windows Terminal uses the systemtheme, dark or light themes." << std::endl;
    std::cout << "\n";
    std::cout << "If you are unsure about the options or syntax of an option, type the option and -h" << std::endl;
}

int main(int _argc, char** _argv)
{
    std::cout << fileprefix << std::endl;
    SettingReader r;
    json j = r.read(filepath);

    std::regex r_bg("(--backgroundImage)");
    std::regex r_bc("(--background)");
    json new_j = j["profiles"]["defaults"];

    for (int i = 0; i < _argc; i++) 
    {
        //std::cout << *(_argv);

        /*Background Settings*/
        if (std::regex_match(*(_argv), r_bg) && (i + 1 < _argc))
        {
            //std::cout << "found Background Image" << std::endl;
            new_j["backgroundImage"]= *(_argv + 1);
            //std::cout << new_j << std::endl; 
        }

        else if (std::regex_match(*(_argv), r_bc) && (i + 1 < _argc))
        {
            //std::cout << "found Background Color" << std::endl;
            std::regex r_hash("(#)[A-Fa-f0-9]{6}");
            //std::cout << regex_match(*(_argv + 1), r_hash);
            if (regex_match(*(_argv + 1), r_hash))
            {
                new_j["background"] = *(_argv + 1);
                //std::cout << new_j << std::endl;
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--bgImageOpacity)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("[+-]?([0-9]*[.])?[0-9]+")))
            {
                double a = std::stod(*(_argv + 1));
                //std::cout << a;
                if (0.0 <= a && a <= 1.0)
                {
                    new_j["backgroundImageOpacity"] = a;
                }
                else
                {
                    std::cout << "\"--bgImageOpacity\" requires a parameter within 0 and 1\n";
                }
            }
            else
            {
                std::cout << "\"--bgImageOpacity\" requires a parameter within 0 and 1\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--backgroundImageStretchMode)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(none)")))
            {
                new_j["backgroundImageStretchMode"] = "none";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(fill)")))
            {
                new_j["backgroundImageStretchMode"] = "fill";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(uniform)")))
            {
                new_j["backgroundImageStretchMode"] = "uniform";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(uniformToFill)")))
            {
                new_j["backgroundImageStretchMode"] = "uniformToFill";
            }
            else
            {
                std::cout << "Required options for \"--backgroundImageStretchMode\" are \"none,\" \"fill,\" \"uniform,\" or \"uniformToFill\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--backgroundImageAlignment)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(center)")))
            {
                new_j["backgroundImageAlignment"] = "center";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(left)")))
            {
                new_j["backgroundImageAlignment"] = "left";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(top)")))
            {
                new_j["backgroundImageAlignment"] = "top";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(right)")))
            {
                new_j["backgroundImageAlignment"] = "right";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(bottom)")))
            {
                new_j["backgroundImageAlignment"] = "bottom";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(topLeft)")))
            {
                new_j["backgroundImageAlignment"] = "topLeft";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(topRight)")))
            {
                new_j["backgroundImageAlignment"] = "topRight";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(bottomLeft)")))
            {
                new_j["backgroundImageAlignment"] = "bottomLeft";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(bottomRight)")))
            {
                new_j["backgroundImageAlignment"] = "bottomRight";
            }
            else
            {
                std::cout << "Required options for \"--backgroundImageAlignment\" are \"center,\" \"left,\" \"top,\" \"right,\" \"right,\" \"topLeft,\" \"topRight,\" \"bottomLeft,\" or \"bottomRight\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--useAcrylic)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(false)")))
            {
                new_j["useAcrylic"] = false;
            }

            else if (std::regex_match(*(_argv + 1), std::regex("(true)")))
            {
                new_j["useAcrylic"] = true;
            }
            else
            {
                std::cout << "Required options for \"--useAcrylic\" are \"true,\" or \"false,\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--acrylicOpacity)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("[+-]?([0-9]*[.])?[0-9]+")))
            {
                double a = std::stod(*(_argv + 1));

                if (0.0 <= a && a <= 1.0)
                {
                    new_j["acrylicOpacity"] = a;
                }
                else
                {
                    std::cout << "\"--acrylicOpacity\" requires a parameter within 0 and 1\n";
                }
            }
            else
            {
                std::cout << "\"--bgImageOpacity\" requires a parameter within 0 and 1\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--padding)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv+1), std::regex("[0-9]{1,2}(,)[0-9]{1,2}(,)[0-9]{1,2}(,)[0-9]{1,2}")))
            {
                new_j["padding"] = *(_argv + 1);
            }
            else
            {
                std::cout << "\"--padding\" requires a parameter in the format #,#,#,#\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--scrollbarState)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(visible)")))
            {
                new_j["scrollbarState"] = "visible";
            }

            else if (std::regex_match(*(_argv + 1), std::regex("(hidden)")))
            {
                new_j["scrollbarState"] = "hidden";
            }
            else
            {
                std::cout << "Required options for \"--scrollbarState\" are \"visible,\" or \"hidden,\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--tabColor)")) && (i + 1 < _argc))
        {
        //std::cout << "found Background Color" << std::endl;
            std::regex r_hash("(#)[A-Fa-f0-9]{6}");
        //std::cout << regex_match(*(_argv + 1), r_hash);
            if (regex_match(*(_argv + 1), r_hash))
            {
                new_j["tabColor"] = *(_argv + 1);
            }
            else
            {
                std::cout << "\"--tabColor\" requires a color formated as #ffffff\n";
            }
        }

        /*Font Settings*/
        else if (std::regex_match(*(_argv), std::regex("(--font)")))
        {
            new_j["fontFace"] = *(_argv + 1);
        }

        else if (std::regex_match(*(_argv), std::regex("(--fontSize)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("^[0-9]{1,2}$")))
            {
                int a = std::stoi(*(_argv + 1));
                new_j["fontSize"] = a;
            }
        }
        
        /*Display Aesthetic Settings*/
        else if (std::regex_match(*(_argv), std::regex("(--phosphor)")) && ((i + 1) < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(false)")))
            {
                new_j["experimental.retroTerminalEffect"] = false;
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(true)")))
            {
                new_j["experimental.retroTerminalEffect"] = true;
            }
            else
            {
                std::cout << "Required options for \"--phosphor\" are \"true,\" or \"false,\"\n";
            }

        }

        else if (std::regex_match(*(_argv), std::regex("(--cursorShape)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(bar)")))
            {
                new_j["cursorShape"] = "bar";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(vintage)")))
            {
                new_j["cursorShape"] = "vintage";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(underscore)")))
            {
                new_j["cursorShape"] = "underscore";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(filledBox)")))
            {
                new_j["cursorShape"] = "filledBox";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(emptyBox)")))
            {
                new_j["cursorShape"] = "emptyBox";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(doubleUnderscore)")))
            {
                new_j["cursorShape"] = "doubleUnderscore";
            }
            else
            {
                std::cout << "Required options for \"--cursorShape\" are \"bar,\" \"vintage,\" \"underscore,\" \"filledBox,\" \"emptyBox,\" or \"doubleUnderscore\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--cursorHeight)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("^[0-9]{1,3}$")))
            {
                std::cout << "\"--cursorHeight\" only works when \"--cursorShape\" is set to \"vintage.\"\n";
                int a = std::stoi(*(_argv + 1));
                if (25<=a && a <=100)
                {
                    new_j["cursorHeight"] = a;
                }
                else
                {
                    std::cout << "\"--cursorHeight\" must have parameters >25 but <100 \n";
                }
            }
            else
            {
                std::cout << "\"--cursorHeight\" must have parameters >=25 but <=100 \n";
            }
        }

        /*Window Settings*/
        else if (std::regex_match(*(_argv), std::regex("(--theme)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(system)")))
            {
                new_j["theme"] = "system";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(dark)")))
            {
                new_j["theme"] = "dark";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(light)")))
            {
                new_j["theme"] = "light";
            }
            else
            {
                std::cout << "Required options for \"--theme\" are \"system,\" \"dark,\" or \"light\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--alwaysShowTabs)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(false)")))
            {
                new_j["alwaysShowTabs"] = false;
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(true)")))
            {
                new_j["alwaysShowTabs"] = true;
            }
            else
            {
                std::cout << "Required options for \"--alwaysShowTabs\" are \"true,\" or \"false,\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--showTabsInTitlebar)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(false)")))
            {
                new_j["showTabsInTitlebar"] = false;
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(true)")))
            {
                new_j["showTabsInTitlebar"] = true;
            }
            else
            {
                std::cout << "Required options for \"--showTabsInTitlebar\" are \"true,\" or \"false,\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--showTerminalTitleInTitlebar)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(false)")))
            {
                new_j["showTerminalTitleInTitlebar"] = false;
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(true)")))
            {
                new_j["showTerminalTitleInTitlebar"] = true;
            }
            else
            {
                std::cout << "Required options for \"--showTerminalTitleInTitlebar\" are \"true,\" or \"false,\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--toggleAlwaysOnTop)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(false)")))
            {
                new_j["toggleAlwaysOnTop"] = false;
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(true)")))
            {
                new_j["toggleAlwaysOnTop"] = true;
            }
            else
            {
                std::cout << "Required options for \"--toggleAlwaysOnTop\" are \"true,\" or \"false,\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--tabWidthMode)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(equal)")))
            {
                new_j["tabWidthMode"] = "equal";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(titleLength)")))
            {
                new_j["tabWidthMode"] = "titleLength";
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(compact)")))
            {
                new_j["tabWidthMode"] = "compact";
            }
            else 
            {
                std::cout << "Required options for \"--tabWidthMode\" are \"equal,\" \"titleLength,\" or \"compact\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--disableAnimations)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(false)")))
            {
                new_j["disableAnimations"] = false;
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(true)")))
            {
                new_j["disableAnimations"] = true;
            }
            else
            {
                std::cout << "Required options for \"--disableAnimations\" are \"true,\" or \"false,\"\n";
            }
        }

        else if (std::regex_match(*(_argv), std::regex("(--confirmCloseAllTabs)")) && (i + 1 < _argc))
        {
            if (std::regex_match(*(_argv + 1), std::regex("(false)")))
            {
                new_j["confirmCloseAllTabs"] = false;
            }
            else if (std::regex_match(*(_argv + 1), std::regex("(true)")))
            {
                new_j["confirmCloseAllTabs"] = true;
            }
            else
            {
                std::cout << "Required options for \"--confirmCloseAllTabs\" are \"true,\" or \"false,\"\n";
            }
        }
        
        /*Information Commands*/
        else if (std::regex_match(*(_argv), std::regex("(-l)")) || std::regex_match(*(_argv), std::regex("(--list)")))
        {
            printJson(j, 0);
        }
        
        else if (std::regex_match(*(_argv), std::regex("(-h)")) || std::regex_match(*(_argv), std::regex("(--help)")))
        {
            displayHelp();
        }

        _argv++;

    }
    std::cout << new_j << std::endl;
    std::cout << std::endl;

    j["profiles"]["defaults"]=new_j;
    std::cout << j["profiles"]["defaults"] << std::endl;
    r.write(j, filepath);
    

    /*for (auto it : j)
    {
        std::cout << it;
    }*/
    /*std::cout << j << '\n';

    std::cout << j.at("$schema") << '\n';
    std::cout << j.at("profiles")<< '\n';
    std::cout << j.at("profiles").at("defaults") << '\n';

    j.at("profiles").at("defaults").emplace("backgroundImage", "desktopBackground");
    std::cout << j.at("profiles").at("defaults") << '\n';*/
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
