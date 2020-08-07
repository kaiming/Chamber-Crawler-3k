#ifndef __DGOLD_H__
#define __DGOLD_H__

#include <string>
#include <memory>
#include "gold.h"
#include "walkabletile.h"
#include "dragon.h"

class Gold;

class DragonHoard: public Gold {
    private:
        std::shared_ptr<WalkableTile> dragonTile;
        std::shared_ptr<Dragon> dragon;


    public:
        DragonHoard();
        std::shared_ptr<Dragon> getDragon();
        std::shared_ptr<WalkableTile> getDragonTile();
        void setDragonTile(std::shared_ptr<WalkableTile> tile);


};

#endif
