#ifndef __DGOLD_H__
#define __DGOLD_H__

#include <string>
#include <memory>
#include "gold.h"

class WalkableTile;
class Dragon;

class Gold;

class DragonHoard: public Gold {
    private:
        std::shared_ptr<WalkableTile> dragonTile;
        std::shared_ptr<Dragon> dragon;


    public:
        DragonHoard();
        std::shared_ptr<Dragon> getDragon() const;
        std::shared_ptr<WalkableTile> getDragonTile() const;
        void setDragonTile(std::shared_ptr<WalkableTile> tile);


};

#endif
