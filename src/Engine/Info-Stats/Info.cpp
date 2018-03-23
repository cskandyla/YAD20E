#include "Info.h"
#include <cstdlib>
#include <sstream>


Info::Info(string Name,string Class,string Race,string Gender):Name(Name),Class(Class),Race(Race),Gender(Gender)
{
    this->Name=Name;
    this->Class=Class;
    this->Race=Race;
    this->Gender=Gender;
}


string ItemInfo::InfoString()
{
    string toreturn="Name: "+name+"\nDescription: "+description;/*slot+" itemtype:"+type;*/
    return toreturn;
}


SpellInfo::SpellInfo(string Name,string Class,string School,string Description):Name(Name),Class(Class),School(School),Description(Description)
{

}


WeaponInfo::WeaponInfo(string name,string description,int range,int dmg,int tohitbonus,int dmgbonus,BASEDAMAGETYPE dmgt,WEAPONTYPE wpntype):ItemInfo(name,description,MainWeapon,WEAPON),range(range),dmg(dmg),tohitbonus(tohitbonus),dmgbonus(dmgbonus),dmgtype(dmgt),wpntype(wpntype)
{

}


string WeaponInfo::InfoString()
{

    stringstream ss;
    ss << "\nDamage: "<<dmg<<"\nRange: "<<range<<"\n Tohit: "<<tohitbonus<<"\nDamage Bonus: "<<dmgbonus;;

    string toreturn=ItemInfo::InfoString()+ss.str();

    return toreturn;
}

ArmorInfo::ArmorInfo(string name,string description,ITEMSLOT slot,ITEMTYPE it,int BaseDef,int BonusDef,int resistance,ARMORTYPE armtype):ItemInfo(name,description,slot,it),BaseDeff(BaseDef),BonusDeff(BonusDef),Armor(Armor),armtype(armtype)
{



}


string ArmorInfo::InfoString()
{

    stringstream ss;
    ss << "\nDeffence: "<<BaseDeff<<"\nBonus Deffence: "<<BonusDeff<<"\n Tohit: ";

    string toreturn=ItemInfo::InfoString()+ss.str();

    return toreturn;
}
