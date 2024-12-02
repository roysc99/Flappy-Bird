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
#include "bn_sprite_items_tuberoot.h"


int main()
{
    bn::core::init();

    //load background
    bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(0, 0);

    //load bird sprite
    bn::sprite_ptr flappybird = bn::sprite_items::flappybird.create_sprite(0,0);

    //object to generate text
    bn::sprite_text_generator text_generator(common::variable_8x8_sprite_font);
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    //printing default text
    text_generator.generate(-60, -68, "(Press up key to start)", text_sprites);

   bool game_started = false; //flag to check if the game has started

    while (true)
    {
        if (bn::keypad::up_pressed())
        {
            if (!game_started)
            {
                // Clear the text sprites when the game starts
                text_sprites.clear();
                game_started = true; // Mark the game as started
            }

            flappybird.set_y(flappybird.y() - 20); // Move the bird up
        }
        else if (game_started)
        {
            flappybird.set_y(flappybird.y() + 1); // Apply gravity only if the game has started
        }

        bn::core::update();
    }
}
