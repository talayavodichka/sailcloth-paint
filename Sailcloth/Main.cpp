/*

 .oooooo..o            o8o  oooo            oooo                .   oooo
d8P'    `Y8            `"'  `888            `888              .o8   `888
Y88bo.       .oooo.   oooo   888   .ooooo.   888   .ooooo.  .o888oo  888 .oo.
 `"Y8888o.  `P  )88b  `888   888  d88' `"Y8  888  d88' `88b   888    888P"Y88b
     `"Y88b  .oP"888   888   888  888        888  888   888   888    888   888
oo     .d8P d8(  888   888   888  888   .o8  888  888   888   888 .  888   888
8""88888P'  `Y888""8o o888o o888o `Y8bod8P' o888o `Y8bod8P'   "888" o888o o888o

*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Process.h"

int main() {
    process_control::run(640, 480);

    return 0;
}