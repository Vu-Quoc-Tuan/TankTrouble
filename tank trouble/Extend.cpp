#include "Extend.h"

bool detail::check_collision(const SDL_Rect &object1,
                             const SDL_Rect &object2)
{
    int left_a  =object1.x;
    int right_a =object1.x+object1.w;
    int top_a   =object1.y;
    int bottom_a=object1.y+object1.h;

    int left_b  =object2.x;
    int right_b =object2.x+object2.w;
    int top_b   =object2.y;
    int bottom_b=object2.y+object2.h;

    //case 1: size object1< size object 2
    if(left_a>left_b && left_a<right_b){
        if(top_a>top_b && top_a<bottom_b){
            return true;
        }
        if(bottom_a>top_b && bottom_a<bottom_b){
            return true;
        }
    }
    if(right_a>left_b && right_a<right_b){
        if(top_a>top_b && top_a<bottom_b){
            return true;
        }
        if(bottom_a>top_b && bottom_a<bottom_b){
            return true;
        }
    }

    //case 2: size object 1<size object 2
    if(left_b>left_a && left_b<right_a){
        if(top_b>top_a && top_b<bottom_a){
            return true;
        }
        if(bottom_b>top_a && bottom_b<bottom_a){
            return true;
        }
    }
    if(right_b>left_a && right_b<right_a){
        if(top_b>top_a && top_b<bottom_a){
            return true;
        }
        if(bottom_b>top_a && bottom_b<bottom_a){
            return true;
        }
    }

    // case 3: size object 1= size object 2
    if(top_a==top_b && right_a==right_b &&
       bottom_a==bottom_b && left_a==left_b)
       {
           return true;
       }

    return false;

}

bool detail::check_insize(const SDL_Rect &object1,
                          const SDL_Rect &object2)
{
    if(object1.x+object1.w>=object2.x && object1.x<=object2.x+object2.w){
        if(object1.y+object1.h>=object2.y && object1.y<=object2.y+object2.h){
            return true;
        }
    }
    return false;
}

int detail::get_distance(const SDL_Rect &object1,
                         const SDL_Rect &object2)
{
    return std::sqrt((object1.x-object2.x)*(object1.x-object2.x)+(object1.y-object2.y)*(object1.y-object2.y));
}

