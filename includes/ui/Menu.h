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
            std::string lastOption;
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
                Option* menuOptions,
                int optionsCount,
                std::string lastOptionTitle = "Go back", 
                std::string emptyMenuString = "***Empty Menu***"
            );

            void run();
            void stop();
 
            ~Menu();
    };
    
} // namespace ui


#endif