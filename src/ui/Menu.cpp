#include <iostream>
#include <string>
#include <limits>

#include "includes/ui/Menu.h"
#include "includes/ui/Option.h"

namespace ui {
    Menu::Menu(
        std::string menuTitle, 
        std::string lastOptionTitle, 
        std::string emptyMenuString
    ) : lastOption(Option(lastOptionTitle, [](void* args){static_cast<Menu*>(args)->isRunning = false;}, this))
    {
        setTitle(menuTitle);
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
            std::cout << "Select an Option From 1 to " + std::to_string(noOfOptions + 1) + ": ";
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input! Please enter a number." << std::endl;
                continue;
            }

            if(choice < 1 || choice > noOfOptions + 1){
                std::cout << "Invalid Option Selected!" << std::endl;
                continue;
            }
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

        std::cout << std::to_string(noOfOptions + 1) + ". " + lastOption.getTitle() << std::endl;

        return Menu::getChoice();
    }

    void Menu::callAction(int index){
        Menu::clearScreen();
        try
        {
            if(index == noOfOptions + 1){
                lastOption.callActionFunction();
            } else {
                options[index-1].callActionFunction();
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return;
    }

    void Menu::addOptions( Option* menuOptions, int optionCount){
        if(optionCount > 0 && menuOptions != nullptr){
            noOfOptions = optionCount;
            options = menuOptions;
        }
        
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