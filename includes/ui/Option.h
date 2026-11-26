#ifndef OPTION_H
#define OPTION_H

#include <string>

namespace ui
{
    class Option
    {
        private:
            std::string title;
            void (*action)(void* args);
            void* args;

            void setTitle(std::string optionTitle);

        public:
            Option();
            Option(std::string optionTitle, void (*action)(void* args), void* args);
            std::string getTitle();
            void callActionFunction();

            ~Option();
    };
    
} // namespace ui


#endif