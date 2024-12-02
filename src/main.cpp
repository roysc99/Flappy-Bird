#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"

#include "bn_regular_bg_items_background.h"
#include "bn_sprite_items_flappybird.h"
#include "bn_sprite_items_tuberoot.h"
#include "bn_sprite_items_tuberoot.h"


int main()
{
    bn::core::init();

    //load background
    bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(0, 0);

    //load bird sprite
    bn::sprite_ptr flappybird = bn::sprite_items::flappybird.create_sprite(0,0);

    //load bird sprite
    bn::sprite_ptr tube = bn::sprite_items::tuberoot.create_sprite(10,0);

    while(true)
    {
        bn::core::update();
    }
}
