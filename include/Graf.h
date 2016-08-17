#ifndef GRAF_H
#define GRAF_H
#include <vector>
#include <iostream>
struct El;
struct Csucs
{
    int adat;
    std::string cim;
    //sulyozas
    int fokszam;
    Csucs(int a, std::string Cim)
    :adat(a),cim(Cim),fokszam(0){}
    bool operator==(const Csucs& cs)const
    {
        return (adat == cs.adat && fokszam == cs.fokszam);
    }
    std::vector<El> elek;
};

struct El
{
    Csucs* elso;
    Csucs* masodik;
    El(Csucs* cs1, Csucs* cs2)
    :elso(cs1),masodik(cs2){}
    bool operator==(const El& e)const
    {
        return (elso == e.elso && masodik == e.masodik);
    }
};

class Graf
{
    public:
        Graf();
        ~Graf();
        friend std::ostream& operator<<(std::ostream& os, const Graf& g);
        void csucsHozzaAd(int adat, std::string);
        void elHozzaAd(std::string, std::string);
        void elTorol(std::string, std::string);
        void csucsTorol(std::string, std::string);
        bool illeszkedikE(const Csucs& cs, const El& e);
        std::vector<El> illeszkedik(const Csucs& cs)const;
        bool szomszedosCsucsokE(const Csucs& cs1, const Csucs& cs2)const;
    private:
        std::vector<Csucs> m_csucsok;
};

#endif // GRAF_H
