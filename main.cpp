#include <iostream>
#include <vector>
#include "Graf.h"

int main()
{
    Graf g;

    std::string c1 = "a";
    g.csucsHozzaAd(3,c1);
    std::string c2 = "b";
    g.csucsHozzaAd(4,c2);
    std::string c3 = "c";
    g.csucsHozzaAd(5,c3);
    g.elHozzaAd(c1,c2);
    g.elHozzaAd(c1,c3);
    g.elHozzaAd(c1,c1);

    /*std::cout << std::boolalpha << g.illeszkedikE(cs1,e1) << std::endl;
    std::cout << cs1.fokszam << std::endl;
    std::cout << g.szomszedosCsucsokE(cs1,cs2) << std::endl;
    std::cout << g.szomszedosCsucsokE(cs1,cs3) << std::endl;*/

    std::cout << g << std::endl;
    return 0;
}
