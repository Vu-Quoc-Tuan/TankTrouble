#ifndef EXTEND_H_INCLUDED
#define EXTEND_H_INCLUDED

#include "Settings.h"

namespace detail
{
    bool check_collision (const SDL_Rect &object1,
                          const SDL_Rect &object2);
    bool check_insize(const SDL_Rect &object1,
                      const SDL_Rect &object2);
    int get_distance(const SDL_Rect &object1,
                      const SDL_Rect &object2 );
}

static  SDL_Event events;

enum type_item
{
    normal=-1,
    armor=0,
    rocket=1,
    laser=2
};

#endif // EXTEND_H_INCLUDED
