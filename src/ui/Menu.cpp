#include <iostream>
#include <string>

#include "includes/ui/Menu.h"
#include "includes/ui/Option.h"

namespace ui {
    Menu::Menu(
        std::string menuTitle, 
        Option* menuOptions,
        int optionsCount,
        std::string lastOptionTitle = "Go back", 
        std::string emptyMenuString = "***Empty Menu***"
    )
    {
        setTitle(menuTitle);
        options = menuOptions;
        noOfOptions = optionsCount;
        lastOption = lastOptionTitle;
        emptyMenu = emptyMenuString;

    }

    void Menu::setTitle(std::string menuTitle){
        if(menuTitle.empty())
            throw std::invalid_argument("Option Title cannot be empty");
        
        title = menuTitle;
    }

    int Menu::getChoice(){
        bool choice_valid = false;
        while (!choice_valid)
        {
            int choice; 
            std::cout << "Select an Option From 1 to " + std::to_string(noOfOptions);
            std::cin >> choice;
            if(choice < 1 || choice > noOfOptions)
                std::cout << "Invalid Option Selected!" << std::endl;
            
            return choice;
        }
        
    }

    int Menu::showOptions(){
        Menu::clearScreen();
        std::cout << "---- " + title + " -----" << std::endl;

        if(noOfOptions < 2)
            std::cout << emptyMenu << std::endl;
        
        for (int i = 0; i < noOfOptions; i++)
        {
            std::cout << std::to_string(i+1) + ". " + options[i].getTitle() << std::endl;
        }

        return Menu::getChoice();
    }

    void Menu::callAction(int index){
        Menu::clearScreen();
        try
        {
            options[index].callActionFunction();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return;
    }

    void Menu::run(){
        if(!isRunning){
            isRunning = true;
        }

        while (isRunning)
        {
            callAction(showOptions());
        }
    }

    void Menu::stop(){
        isRunning = false;
    }

    void Menu::clearScreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    
    Menu::~Menu()
    {
    }
    
}