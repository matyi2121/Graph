#include "Graf.h"
#include <algorithm>
Graf::Graf()
{
    //ctor
}

Graf::~Graf()
{
    //dtor
}

void Graf::csucsHozzaAd(int adat, std::string cim)
{
    Csucs cs(adat,cim);
    m_csucsok.push_back(cs);
}

void Graf::elHozzaAd(std::string c1, std::string c2)
{
    /*e.elso->fokszam++;
    e.masodik->fokszam++;
    e.elso->elek.push_back(e);
    e.masodik->elek.push_back(e);*/
    Csucs* cs1 = nullptr;
    Csucs* cs2 = nullptr;
    if(c1 != c2)
    {
        for(size_t i = 0; i < m_csucsok.size(); i++)
        {
            if(m_csucsok[i].cim == c1)
            {
                cs1 = &m_csucsok[i];
            }
            else if(m_csucsok[i].cim == c2)
            {
                cs2 = &m_csucsok[i];
            }
        }
        El e(cs1,cs2);
        cs1->elek.push_back(e);
        cs1->fokszam++;
        cs2->elek.push_back(e);
        cs2->fokszam++;
    }
    else
    {
        for(size_t i = 0; i < m_csucsok.size(); i++)
        {
            if(m_csucsok[i].cim == c1)
            {
                cs1 = &m_csucsok[i];
            }
        }
        El e(cs1,cs1);
        cs1->elek.push_back(e);
        cs1->fokszam += 2;
    }
}

void Graf::elTorol(std::string c1, std::string c2)
{
    //Todo
    //e.elso->elek.erase(std::find(e.elso->elek.begin(),e.elso->elek.end(),e));
    //e.masodik->elek.erase(std::find(e.masodik->elek.begin(),e.masodik->elek.end(),e));
}
void Graf::csucsTorol(std::string c)
{
    //Todo
    //m_csucsok.erase(std::find(m_csucsok.begin(),m_csucsok.end(),cs));
}

bool Graf::illeszkedikE(const Csucs& cs, const El& e)
{
    for(auto& i : cs.elek)
    {
        if(e == i)
        {
            return true;
        }
    }
    return false;
}
std::vector<El> Graf::illeszkedik(const Csucs& cs)const
{
    std::vector<El> ret;
    for(auto& i : cs.elek)
    {
        ret.emplace_back(i.elso,i.masodik);
    }
    return ret;
}

bool Graf::szomszedosCsucsokE(const Csucs& cs1, const Csucs& cs2)const
{
    if(cs1.elek.size() <= cs2.elek.size())
    {
        for(auto& i : cs1.elek)
        {
            if(i.elso == &cs2 || i.masodik == &cs2)
            {
                return true;
            }
        }
    }
    else
    {
        for(auto& i : cs2.elek)
        {
            if(i.elso == &cs1 || i.masodik == &cs1)
            {
                return true;
            }
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Graf& g)
{
    for(size_t i = 0; i < g.m_csucsok.size(); i++)
    {
        std::vector<El> elek = g.illeszkedik(g.m_csucsok[i]);
        os << "Csucs: " << g.m_csucsok[i].cim << " adat: "<< g.m_csucsok[i].adat << " fokszama: " << g.m_csucsok[i].fokszam << "\n";
        for(size_t j = 0; j < elek.size(); j++)
        {
            os << elek[j].elso->cim << " - " << elek[j].masodik->cim << "\n";
        }
    }
    return os;
}
