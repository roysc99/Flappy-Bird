#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_vector.h"
#include "common_info.h"
#include "common_variable_8x8_sprite_font.h"

#include "bn_regular_bg_items_background.h"
#include "bn_sprite_items_flappybird.h"
#include "bn_sprite_items_tuberoot.h"
#include "bn_sprite_items_floor.h"

int main()
{
    bn::core::init();

    //load background
    bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(0, 0);

    //load bird sprite
    bn::sprite_ptr flappybird = bn::sprite_items::flappybird.create_sprite(0, 0);

    //object to generate text
    bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.generate(-60, -68, "(Press up key to start)", text_sprites);

    //generate floor
    bn::vector<bn::sprite_ptr, 9> floor_sprites; //240/32 = 7.5, so 9 sprites for full coverage
    for(int i = 0; i < 9; i++)
    {
        int x = -104 + (i * 32); 
        int y = 64;
        bn::sprite_ptr floor = bn::sprite_items::floor.create_sprite(x, y);
        floor_sprites.push_back(floor);
    }

    bool game_started = false; //flag to check if the game has started
    bn::fixed floor_offset = 0; //floor offset to keep track of floor sprite positions
    bool bird_alive = true;

    while (true)
    {
        if (bn::keypad::up_pressed())
        {
            if (!game_started)
            {
                //clear the text sprites when the game starts or restarts
                text_sprites.clear();
                //remark game state
                game_started = true; 
                bird_alive = true;
                //reset bird position
                flappybird.set_position(0,0);
                //reset floor offset
                floor_offset = 0;
            }

            flappybird.set_y(flappybird.y() - 20); //move bird up
        }
        else if (game_started)
        {
            flappybird.set_y(flappybird.y() + .75); //apply gravity only if the game has started
        }

        if (bird_alive){
            //update the floor offset
            floor_offset -= bn::fixed(0.5); //0.5 is the speed the floor moves

            //reset the offset if it exceeds the width of a sprite
            if(floor_offset <= -bn::fixed(32))
            {
                floor_offset += bn::fixed(32);
            }

            //move our sprites left based on the offset
            for(int i = 0; i < floor_sprites.size(); ++i)
            {
                bn::fixed x_position = bn::fixed(-104) + bn::fixed(i * 32) + floor_offset;
                floor_sprites[i].set_x(x_position);
            }
        }

        //collision with floor
        if(flappybird.y() + 8 > 48)
        {
            flappybird.set_position(flappybird.x(), flappybird.y());
            text_sprites.clear();
            text_generator.generate(-93, -68, "Game over (Press up key to restart)", text_sprites);
            bird_alive = false;
            game_started = false;
        }

        bn::core::update();
    }
}
