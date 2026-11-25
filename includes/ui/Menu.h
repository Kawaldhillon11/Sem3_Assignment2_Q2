#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "Option.h"

namespace ui
{
    class Menu
    {
        private:
            std::string title;
            Option* options;
            int noOfOptions;
            Option lastOption;
            std::string emptyMenu;

            bool isRunning = false;
            void setTitle(std::string menuTitle);
            
            int getChoice();
            int showOptions();
            void callAction(int index);  
            void clearScreen();

        public:
            Menu(
                std::string menuTitle, 
                std::string lastOptionTitle = "Go back", 
                std::string emptyMenuString = "***Empty Menu***"
            );

            void addOptions( Option* menuOptions, int optionCount);
            void run();
            void stop();
 
            ~Menu();
    };
    
} // namespace ui


#endif