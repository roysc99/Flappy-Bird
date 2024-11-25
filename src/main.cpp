#include "bn_core.h"
#include "bn_regular_bg_ptr.h"

#include "bn_regular_bg_items_background.h"


int main()
{
    bn::core::init();

    //load background
    bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(0, 0);

    while(true)
    {
        bn::core::update();
    }
}
