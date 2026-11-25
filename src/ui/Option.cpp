#include <stdexcept>
#include <string>

#include "includes/ui/Option.h"

namespace ui
{
    Option::Option(std::string optionTitle, void (*actionFunc)(void* args), void* funcArgs)
    {
        setTitle(optionTitle);
        action = actionFunc;
        args = funcArgs;
    }

    void Option::setTitle(std::string optionTitle){
        if(optionTitle.empty())
            throw std::invalid_argument("Option Title cannot be empty");
        
        title = optionTitle;
    }

    std::string Option::getTitle(){
        return title;
    }


    void Option::callActionFunction(){
        if(action != nullptr)
            action(args);
    }

    
    Option::~Option()
    {
    }
} // namespace ui
