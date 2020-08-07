#ifndef __GOLD_H__
#define __GOLD_H__

#include <string>

class Gold {
    private:
        std::string type;
        int size;

    public:
        Gold(std::string type, int size);
        int getSize();
        std::string getType();
};

#endif
