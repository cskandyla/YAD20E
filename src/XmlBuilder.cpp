#include "XmlBuilder.h"
#include "miscellaneous.h"
#include "Team.h"
#include "KnowledgePool.h"
#include "Seeker.h"
#include "Zombie.h"
#include "Idle.h"
#include "Tokenizer.h"
#include "LuaObjective.h"
#include "BuiltinObjective.h"
#include "Quests.h"
#include <string>
using namespace std;

SDL_Renderer* XmlBuilder::renderer =NULL;
 
void XmlBuilder::ParseInit(string InitFile,string &map,string &mapsetting)
{
  xml_document doc;
  xml_parse_result result = doc.load_file(InitFile.c_str());
  pugi::xml_node mapnode=doc.select_nodes("//Map")[0].node();
  map=mapnode.child("mapfile").child_value();
  mapsetting=mapnode.child("setting").child_value();
  cout<<"map:"<<map<<" setting: "<<mapsetting<<endl;
}

void XmlBuilder::ParseMapSetting(string mapsetting,int &visibility)
{
  cout<<"Parsing the map setting"<<endl;
 xml_document doc;
 xml_parse_result result = doc.load_file(mapsetting.c_str());
 visibility=atoi(doc.select_nodes("//visibility")[0].node().child_value());
 string spawn=doc.select_nodes("//SpawnPoint")[0].node().child_value();
 Tokenizer t;
 t.setDelimeter(",");
 t.setInput(spawn);
 BaseCharacter *bchar=KnowledgePool::Instance()->getCharacter(1);
 vector<string> tokens=t.split();
 int xpos=atoi(tokens[0].c_str());
 int ypos=atoi(tokens[1].c_str());
 int tile_size=MapIndex::Instance()->getMap()->getTileSize();
 bchar->SetPosition(xpos*tile_size,ypos*tile_size);
 MapIndex::Instance()->CharIndexUpdate(bchar,0,0);
 LoadDoodads(mapsetting);
 LoadTeams(mapsetting);
 cout<<"Done Parsing Setting"<<endl;
}


AnimatedEntity* XmlBuilder::LoadEntity(string xmlfile,string entity_name="//Entity")
{
  cout<<"******BUILDING ENTITY FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node  enti=doc.select_nodes(entity_name.c_str())[0].node();
  string sprite=enti.child("Sprite").child_value();
  int width=atoi(enti.child("Width").child_value());
  int height=atoi(enti.child("Height").child_value());
  string animfile=enti.child("Animfile").child_value();
  cout<<"SpriteSheet Info:"<<sprite<<" "<<width<<" "<<height<<" "<<animfile<<endl;
  //SDL_Surface *basesurf=loadSurface(sprite.c_str());
  SDL_Texture *basetex=loadTexture(sprite.c_str(),XmlBuilder::renderer);
  /*  if(basesurf==NULL)
    {
      cout<<"Loading "<<" failed"<<endl;

    }
  Uint32 *pixels = (Uint32 *)basesurf->pixels;
  Uint8 r,g,b,a;
  SDL_GetRGB(pixels[0],basesurf->format,&r,&g,&b);
  SDL_SetColorKey(basesurf,SDL_TRUE ,SDL_MapRGB(basesurf->format,r,g,b));*/
  AnimatedEntity *ent=new AnimatedEntity(basetex,width,height);
  if(ent==NULL)
    {
      cout<<"Could Not Create Animated Entity"<<endl;
      return NULL;
    }
  if(!ent->LoadAnimations((char*)animfile.c_str()))
    return NULL;
  cout<<"Success"<<endl;
  return ent;

}

Info* XmlBuilder::LoadInfo(string xmlfile)
{
  cout<<"******BUILDING INFO FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node  info=doc.select_nodes("//Info")[0].node();
  string mname=info.child("Name").child_value();
  string mclass=info.child("Class").child_value();
  string mgender=info.child("Gender").child_value();
  string mrace=info.child("Race").child_value();
  Info *cinfo=new Info(mname,mclass,mrace,mgender);
  cout<<cinfo->getClass()<<" "<<cinfo->getGender()<<" "<<cinfo->getName()<<" "<<cinfo->getRace()<<endl;

  return cinfo;


}


Attributes*       XmlBuilder::LoadAttributes(string xmlfile)
{


  cout<<"******BUILDING ATTRIBUTES FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());

  pugi::xml_node  stats=doc.select_nodes("//Attributes")[0].node();
  int Int=atoi(stats.child("Int").child_value());
  int Str=atoi(stats.child("Str").child_value());
  int Dex=atoi(stats.child("Dex").child_value());
  int Con=atoi(stats.child("Con").child_value());
  int Spi=atoi(stats.child("Spi").child_value());
  Attributes *attribs=new Attributes(Str,Dex,Con,Int,Spi);
  cout<<"Attributes:"<<Int<<" "<<Str<<" "<<Dex<<" "<<Con<<" "<<Spi<<endl;

  return attribs;

}
GeneralStats*    XmlBuilder::LoadGeneralStats(string xmlfile)
{

  cout<<"******BUILDING GENERAL STATS FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());

  pugi::xml_node  stats=doc.select_nodes("//GeneralStats")[0].node();
  int hp=atoi(stats.child("Hp").child_value());
  int speed=atoi(stats.child("Sp").child_value());
  int xp=atoi(stats.child("Xp").child_value());
  GeneralStats *gstats=new GeneralStats(hp,speed,xp);
  return gstats;

}



Stats* XmlBuilder::LoadStats(string xmlfile)
{

  cout<<"******BUILDING STATS FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());

  pugi::xml_node  stats=doc.select_nodes("//Stats")[0].node();
  int Int=atoi(stats.child("Int").child_value());
  int Str=atoi(stats.child("Str").child_value());
  int Dex=atoi(stats.child("Dex").child_value());
  int Con=atoi(stats.child("Con").child_value());
  Stats *cstat=new Stats(Str,Dex,Int,Con);
  cout<<"Stats:"<<Int<<" "<<Str<<" "<<Dex<<" "<<Con<<endl;

  return cstat;
}


Projectile*       XmlBuilder::LoadProjectile(string xmlfile)
{
	cout<<"Not Implemented"<<endl;
	return NULL;
}

BaseCharacter* XmlBuilder::LoadCharacter(string xmlfile)
{
  
  cout<<"******BUILDING CHARACTER FORM XML:"<<xmlfile<<"******"<<endl;
  AnimatedEntity *ent=LoadEntity(xmlfile);
  Info* cinfo=LoadInfo(xmlfile);
  // Stats* cstats=LoadStats(xmlfile);
  Attributes* attribs=LoadAttributes(xmlfile);
  GeneralStats* gstats=LoadGeneralStats(xmlfile);
  gstats->SetHp(gstats->getHp()+(attribs->getCon()-10)/2);
  cout<<"BaseCharacterHp:"<<gstats->getHp()<<endl;


  int BaseAttackBonus=0;
  int ToHitBonus=(attribs->getStr()-10)/2;
  int Damage=(attribs->getStr()-10)/2;
  int ArmorClass=(attribs->getDex()-10)/2+10;
  int Sr=0;
  CombatStats* cstats=new CombatStats(BaseAttackBonus,ToHitBonus,Damage,ArmorClass,Sr);
  BaseCharacter *bchar=NULL;
  xml_document doc;    
  //Load The Xml
  xml_parse_result result = doc.load_file(xmlfile.c_str());

  if(cinfo->getClass().compare("Mage")==0)
    {
      int num_feats=doc.select_nodes("//Feats").size();
      cout<<"Num Feats"<<num_feats<<endl;
      if(num_feats==0)
	{
	  bchar=new Mage(ent,cinfo,attribs,gstats,cstats);
	}
      if(doc.select_nodes("//Feats/School").size() >0)
	{
	  pugi::xml_node  school_node=doc.select_nodes("//Feats/School")[0].node();
	  string school=school_node.child_value();
	  MAGE_MASTERY mm=M_NO_M;
	  if(doc.select_nodes("//Feats/Mastery").size()>0)
	    {
	      pugi::xml_node  mastery_node=doc.select_nodes("//Feats/Mastery")[0].node();
	      string mage_mastery=mastery_node.child_value();
	      
	      if(mage_mastery.compare("Arcane")==0)
		{
		  mm=M_ARCANE_M;
		}
	      else if(mage_mastery.compare("Spell")==0)
		{
		  mm=M_SPELL_M;;
		}
	    }
	  bchar=new Mage(ent,cinfo,attribs,gstats,cstats,school_string_to_enum(school),mm);
	}
      LoadSpells(xmlfile,dynamic_cast<Mage*>(bchar));
      
    }
  else if(cinfo->getClass().compare("Warrior")==0)
    {
      int num_feats=doc.select_nodes("//Feats").size();
      cout<<"Num Feats"<<num_feats<<endl;
      if(num_feats==0)
	{
	  bchar=new Warrior(ent,cinfo,attribs,gstats,cstats);
	}
      
      else if(doc.select_nodes("//Feats/Mastery").size()>0)
	{
	  WARRIOR_MASTERY wm=W_NO_M;
	  pugi::xml_node  mastery_node=doc.select_nodes("//Feats/Mastery")[0].node();
	  string warrior_mastery=mastery_node.child_value();
	  
	  if(warrior_mastery.compare("Arcane")==0)
	    {
	      wm=W_TWOHANDED_M;
	    }
	  else if(warrior_mastery.compare("Spell")==0)
	    {
	      wm=W_SHIELD_M;
	    }
	  bchar=new Warrior(ent,cinfo,attribs,gstats,cstats,wm); 
	}   
    }
  else
    bchar=new BaseCharacter(ent,cinfo,attribs,gstats,cstats);
  
  //Load The Character Portrait;
  if(doc.select_nodes("//Portrait").size()>0)
    {
      pugi::xml_node  portrait=doc.select_nodes("//Portrait")[0].node();
      if(strcmp(portrait.child_value(),"")!=0)
	{
	  cout<<"Loading Portrait:"<<portrait.child_value()<<endl;
	  SDL_Texture *portrait_tex=loadTexture(portrait.child_value(),XmlBuilder::renderer);
	  bchar->SetPortrait(portrait_tex);
	}
    }

  //Loading Items
  pugi::xml_node  head=doc.select_nodes("//Equiped/head")[0].node();
  cout<<head.child_value()<<endl;
  if(strcmp(head.child_value(),"")!=0)
    {
      Item *Head=LoadItem(head.child_value());
      bchar->Equip(Head);
    }
  pugi::xml_node  chest=doc.select_nodes("//Equiped/chest")[0].node();
  cout<<chest.child_value()<<endl;
  if(strcmp(chest.child_value(),"")!=0)
    {
      Item *Chest=LoadItem(chest.child_value());
      bchar->Equip(Chest);
    }
  pugi::xml_node  legs=doc.select_nodes("//Equiped/legs")[0].node();
  cout<<legs.child_value()<<endl;
  if(strcmp(legs.child_value(),"")!=0)
    {
      Item *Legs=LoadItem(legs.child_value());
      bchar->Equip(Legs);
    }
  pugi::xml_node  neck=doc.select_nodes("//Equiped/neck")[0].node();
  cout<<neck.child_value()<<endl;
  if(strcmp(neck.child_value(),"")!=0)
    {
      Item *Neck=LoadItem(neck.child_value());
      bchar->Equip(Neck);
    }
  pugi::xml_node  hand1=doc.select_nodes("//Equiped/hand1")[0].node();
  cout<<hand1.child_value()<<endl;
  if(strcmp(hand1.child_value(),"")!=0)
    {
      Item *Hand1=LoadItem(hand1.child_value());
      bchar->Equip(Hand1);
    }
  pugi::xml_node  hand2=doc.select_nodes("//Equiped/hand2")[0].node();
  cout<<hand2.child_value()<<endl;
  if(strcmp(hand2.child_value(),"")!=0)
    {
      Item *Hand2=LoadItem(hand2.child_value());
      bchar->Equip(Hand2);
    }
  pugi::xml_node  mainHand=doc.select_nodes("//Equiped/mainHand")[0].node();
  cout<<mainHand.child_value()<<endl;
  if(strcmp(mainHand.child_value(),"")!=0)
    {
      Item *Mainhand=LoadItem(mainHand.child_value());
      Mainhand->getInfo()->setItemSlot(MainWeapon);
      bchar->Equip(Mainhand);
    }
  pugi::xml_node  secondaryHand=doc.select_nodes("//Equiped/SecondWeapon")[0].node();
  if(strcmp(secondaryHand.child_value(),"")!=0)
    {
      Item *SecondaryHand=LoadItem(secondaryHand.child_value());
      SecondaryHand->getInfo()->setItemSlot(SecondWeapon);
      bchar->Equip(SecondaryHand);
    }
  cout<<secondaryHand.child_value()<<endl;
  pugi::xml_node  ammo=doc.select_nodes("//Equiped/ammo")[0].node();
  cout<<ammo.child_value()<<endl;
  if(strcmp(ammo.child_value(),"")!=0)
    {
      Item *Ammo=LoadItem(ammo.child_value());
      bchar->Equip(Ammo);
    }
  cout<<"Done Loading Items"<<endl;

  
  return bchar;

}

ItemInfo* XmlBuilder::LoadItemInfo(string xmlfile)
{

  cout<<"******BUILDING ITEMINFO FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node item = doc.child("Item");
  pugi::xml_node info=item.child("Info");
  string mname=info.child("Name").child_value();
  string description=info.child("Description").child_value();
  string slot=info.child("Slot").child_value();
  string type=info.child("Type").child_value();

  ITEMTYPE it;
  if(type.compare("Weapon")==0)
    {
      it=WEAPON;

      //LOAD ADDITIONAL WEAPONINFO
    }
  else if(type.compare("Armor")==0)
    {
      it=ARMOR;
    }
  else if(type.compare("Onhead")==0)
    {
      it=ONHEAD;
    }
  else if(type.compare("Other")==0)
    {
      it=OTHER;
    }
  


  ITEMSLOT sl;
  if(slot.compare("Head")==0)
    {
      sl=Head;

    }
  else if(slot.compare("Chest")==0)
    {
      sl=Chest;
    }
  else if(slot.compare("Legs")==0)
    {
      sl=Legs;
    }
  else if(slot.compare("Neck")==0)
    {
      sl=Legs;
    }
  else if(slot.compare("Hand1")==0)
    {
      sl=Hand1;
    }
  else if(slot.compare("Hand2")==0)
    {
      sl=Hand2;
    }
  else if(slot.compare("MainWeapon")==0)
    {
      sl=MainWeapon;
    }
  else if(slot.compare("SecondWeapon")==0)
    {
      sl=SecondWeapon;
    }
  else if(slot.compare("Ammo")==0)
    {
      sl=Ammo;
    }
  else 
    {
      sl=NONE;
    }



  ItemInfo *iinfo=new ItemInfo(mname,description,sl,it);
  cout<<iinfo->getName()<<" "<<iinfo->getDescription()<<" "<<iinfo->getItemSlot()<<" "<<iinfo->getItemType()<<endl;

  string itemtype=item.child("type").child_value();


  if(itemtype.compare("Weapon")==0)
    {

      cout<<"TYPE: WEAPON"<<endl;
      int range=atoi(info.child("Range").child_value());
      int dmg=atoi(info.child("Damage").child_value());
      int tohitbonus=atoi(info.child("ToHitBonus").child_value());
      int dmgbonus=atoi(info.child("DamageBonus").child_value());
      string  dmgtype=info.child("BaseDamageType").child_value();
      BASEDAMAGETYPE bdt;
      if(dmgtype.compare("Slashing")==0)
        {
	  bdt=SLASHING;
        }
      else if(dmgtype.compare("Bludgeoning")==0)
        {
	  bdt=BLUDGEONING;
        }
      else if(dmgtype.compare("Piercing")==0)
        {
	  bdt=PIERCING;
        }
      else if(dmgtype.compare("Force")==0)
        {
	  bdt=FORCE;
        }
      string wpntype=info.child("WeaponType").child_value();
      WEAPONTYPE wpt;
      if(wpntype.compare("Dagger")==0)
	{
	  wpt=DAGGER;
	}
      else if(wpntype.compare("Sword")==0)
	{
	  wpt=SWORD;
	}
      else if(wpntype.compare("Bow")==0)
	{
	  wpt=BOW;
	}
      else if(wpntype.compare("Spear")==0)
	{
	  wpt=SPEAR;
	}
      else if(wpntype.compare("Quarterstaff")==0)
	{
	  wpt=QUARTERSTAFF;
	}
      else if(wpntype.compare("Secondary")==0)
	{
	  wpt=WEAPON_SECONDARY;
	}
      else
	{
	  wpt=WEAPON_OTHER;
	}


      WeaponInfo *winfo=new WeaponInfo(mname,description,range,dmg,tohitbonus,dmgbonus,bdt,wpt);
      delete iinfo;
      return winfo;
    }
  else if(itemtype.compare("Armor")==0)
    {
      cout<<"TYPE: ARMOR"<<endl;
      int basedef=atoi(info.child("BaseDefense").child_value());
      int resistance=atoi(info.child("Resistance").child_value());
      int bonusdef=atoi(info.child("BonusDefense").child_value());
      string armtype=info.child("ArmorType").child_value();
      ARMORTYPE at;
      if(armtype.compare("Light")==0)
	{
	  at=ARMOR_LIGHT;
	}
      else if(armtype.compare("Medium")==0)
	{
	  at=ARMOR_MEDIUM;
	}
      else if(armtype.compare("Heavy")==0)
	{
	  at=ARMOR_HEAVY;
	}
      else if(armtype.compare("Other")==0)
	{
	  at=ARMOR_OTHER;
	}
      ArmorInfo *ainfo=new ArmorInfo(mname,description,sl,ARMOR,basedef,bonusdef,at);
      delete iinfo;
      return ainfo;
    }

  else
    {
      return iinfo;
    }


}

Item* XmlBuilder::LoadItem(string xmlfile)
{

  cout<<"******BUILDING ITEM FORM XML:"<<xmlfile<<"******"<<endl;
  ItemInfo* info=LoadItemInfo(xmlfile);
  Stats* stats=LoadStats(xmlfile);

  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node item = doc.child("Item");
  string itemtype=item.child("type").child_value();
  pugi::xml_node image=item.child("Image");

  string itemimage=image.child_value();
  SDL_Texture *itemtex=loadTexture(itemimage,XmlBuilder::renderer);
  if(itemtype.compare("Visible")==0)
    {
      cout<<"VISIBLEITEM CREATION"<<endl;
      AnimatedEntity* aent=LoadEntity(xmlfile);
      VisibleItem* vitem=new VisibleItem(info,stats,itemtex,aent);
      return vitem;

    }
  else if(itemtype.compare("Weapon")==0)
    {
      AnimatedEntity* aent=LoadEntity(xmlfile);

      WeaponInfo *winfo=dynamic_cast<WeaponInfo*>(info);
      Weapon *wep=new Weapon(winfo,stats,itemtex,aent);
      return wep;

    }
  else if(itemtype.compare("Armor")==0)
    {
      AnimatedEntity* aent=LoadEntity(xmlfile);
      ArmorInfo *ainfo=dynamic_cast<ArmorInfo*>(info);
      Armor *armor=new Armor(ainfo,stats,itemtex,aent);
      return armor;

    }
  else if(itemtype.compare("Usable")==0)
    {
      SpellStats* sp_stats=LoadSpellStats(xmlfile,"//SpellStats");
      xml_document doc;
      xml_parse_result result = doc.load_file(xmlfile.c_str());
      pugi::xml_node  effect=doc.select_nodes("//EffectName")[0].node();
      Spell_Effect_t the_effect=NULL;
      if(LookUpSpell(effect.child_value())!=-1)
	{
	  the_effect=spellarchives[LookUpSpell(effect.child_value())].spell_effect; 
	  UsableItem *usable=new UsableItem(info,stats,itemtex,the_effect,sp_stats);
	  return usable;
	}
      
      return NULL;
    }
  else
    {

      Item* it=new Item(info,stats,itemtex);
      return it;

    }


}


SpellInfo*        XmlBuilder::LoadSpellInfo(string xmlfile)
{
  cout<<"******BUILDING SPELLINFO FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node  info=doc.select_nodes("//Info")[0].node();
  string sname=info.child("Name").child_value();
  string sclass=info.child("Class").child_value();
  string sschool=info.child("School").child_value();
  string sdescription=info.child("Description").child_value();
  SpellInfo *sinfo=new SpellInfo(sname,sclass,sschool,sdescription);
  cout<<sinfo->getClass()<<" "<<sinfo->getSchool()<<" "<<sinfo->getName()<<" "<<sinfo->getDescription()<<endl;

  return sinfo;


}
SpellStats*       XmlBuilder:: LoadSpellStats(string xmlfile,string stats_name="//Stats")
{
  cout<<"******BUILDING SPELLSTATS FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node  stats=doc.select_nodes(stats_name.c_str())[0].node();
    
  int Range=atoi(stats.child("Range").child_value());
  int Radius=atoi(stats.child("Radius").child_value());
  int Rank=atoi(stats.child("Rank").child_value());
  int Level=atoi(stats.child("Level").child_value());
  string AoeType=stats.child("AOE").child_value();
  string ReqTarget=stats.child("ReqTarget").child_value();

  AOE aoe_t;
  if(AoeType.compare("SINGLE")==0)
    {
      aoe_t=SINGLE;

    }
  else if(AoeType.compare("DISK")==0)
    {
      aoe_t=DISK;
    }
  else if(AoeType.compare("CONE")==0)
    {
      aoe_t=CONE;
    }
  else if(AoeType.compare("CLOUD")==0)
    {
      aoe_t=CLOUD;
    }
  else if(AoeType.compare("LINE")==0)
    {
      aoe_t=LINE;
    }
  else if(AoeType.compare("WALL")==0)
    {
      aoe_t=WALL;
    }
  
  //assume we require a target by default
  bool req_t=true;
  if(ReqTarget.compare("NO")==0)
    {
      req_t=false;
    }
  if(ReqTarget.compare("YES")==0)
    {
      req_t=true;
    }

  SpellStats *sstat=new SpellStats(Range,Radius,Rank,Level,aoe_t,req_t);
  cout<<"Stats:"<<Range<<" "<<Radius<<" "<<Rank<<" "<<Level<<endl;
  return sstat;

}

Spell*           XmlBuilder::LoadSpell(string xmlfile)
{
  Spell *the_spell=NULL;;
  cout<<"******BUILDING SPELL FORM XML:"<<xmlfile<<"******"<<endl;
  SpellInfo* info=LoadSpellInfo(xmlfile);
  SpellStats* sp_stats=LoadSpellStats(xmlfile);
  AnimatedEntity* projectile_entity=LoadEntity(xmlfile);
  
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node  effect=doc.select_nodes("//EffectName")[0].node();
  Spell_Effect_t the_effect=NULL;
  if(LookUpSpell(effect.child_value())!=-1)
    {
      cout<<"Effect Found in the Archive"<<endl;
      the_effect=spellarchives[LookUpSpell(effect.child_value())].spell_effect;
	
    }
  
  if(sp_stats->GetAoeType()==SINGLE)
    {
      cout<<"TargetSpell Type"<<endl;
      the_spell=new TargetSpell(info,NULL,the_effect,projectile_entity);
    }
  else if(sp_stats->GetAoeType()==DISK)
    {
      AnimatedEntity* blast_entity=LoadEntity(xmlfile,"//Blast");
      cout<<"SpellBlast type"<<endl;
      the_spell=new SpellBlast(info,NULL,the_effect,projectile_entity,blast_entity);
	
    }
  else if(sp_stats->GetAoeType()==CLOUD)
    {
      int duration=4;
      cout<<"Cloud Time type"<<endl;
      the_spell=new CloudSpell(info,NULL,the_effect,projectile_entity,duration);
	
    }
  else if(sp_stats->GetAoeType()==WALL)
    {
      int duration=4;
      
      pugi::xml_node  built_effect=doc.select_nodes("//OnBuilt")[0].node();
      Spell_Effect_t the_built_effect=NULL;
      if(LookUpSpell(built_effect.child_value())!=-1)
	{
	  cout<<"Built Effect Found in the Archive"<<endl;
	  the_built_effect=spellarchives[LookUpSpell(built_effect.child_value())].spell_effect;
	  
	}

      pugi::xml_node expired_effect=doc.select_nodes("//OnExpired")[0].node();
      Spell_Effect_t the_expired_effect=NULL;
      if(LookUpSpell(expired_effect.child_value())!=-1)
	{
	  cout<<"Expired Effect Found in the Archive"<<endl;
	  the_expired_effect=spellarchives[LookUpSpell(expired_effect.child_value())].spell_effect;
	  
	}
      else
	{
	  cout<<"No Expired Effect"<<endl;
	  exit(-1);
	}
      
      the_spell=new WallSpell(info,NULL,the_effect,projectile_entity,duration,the_built_effect,the_expired_effect);
      sp_stats->SetDirection(S_LEFT);
    }
  else if(sp_stats->GetAoeType()==LINE)
    {
      int duration=4;
      the_spell=new LineSpell(info,NULL,the_effect,projectile_entity);
      sp_stats->SetDirection(S_LEFT);
    }
  else if(sp_stats->GetAoeType()==CONE)
    {
      the_spell=new ConeSpell(info,NULL,the_effect,projectile_entity);
      sp_stats->SetDirection(S_RIGHT);
    }
  else
    {
      cout<<"SPELL NOT SUPPORTED/IMPLEMENTED YET"<<endl;
    }
  the_spell->SetSpellStats(sp_stats);
  pugi::xml_node  IconNode=doc.select_nodes("//Icon")[0].node();
  string Icon=IconNode.child_value();
  SDL_Texture *icontex=loadTexture(Icon,XmlBuilder::renderer);
  the_spell->LoadIcon(icontex);
    
  return the_spell;
}


void XmlBuilder::LoadSpells(string xmlfile,Mage *the_mage)
{
  cout<<"******LOADING SPELLS FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node  spells=doc.select_nodes("//SpellBook")[0].node();
  for(pugi::xml_node node=spells.first_child();node;node=node.next_sibling())
    {
      Spell* the_spell=LoadSpell(node.child_value());
      if(the_spell)
	the_mage->LearnSpell(the_spell);
    }

}

Effect* LoadEffect(string xmlfile)
{
	cout<<" Not Implemented"<<endl;
	return NULL;

}

void XmlBuilder::LoadTeams(string xmlfile)
{

  
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node teamsnode=doc.select_nodes("//Teams")[0].node();
  for(pugi::xml_node teamnode=teamsnode.child("Team");teamnode;teamnode=teamnode.next_sibling("Team"))
    {  Team *team=NULL;
      string name=teamnode.child("Name").child_value();
      cout<<"Team Name:"<<name<<endl;
      if(name!="")
	{
      
	  set<unsigned int> members;
	  for(pugi::xml_node member=teamnode.child("Member");member;member=member.next_sibling("Member"))
	    {
	      BaseCharacter *bchar=LoadCharacter(member.child("character").child_value());
	      cout<<"Character "<<bchar->getInfo()->getName()<<" loaded"<<endl;
	      KnowledgePool::Instance()->AddCharacter(bchar);
	      cout<<"Added "<<bchar->getInfo()->getName()<<endl;
	      string AI=member.child("AI").child_value();
	      if(AI!="NO")
		{
		  if(AI=="Zombie")
		    {
		      Zombie_AI* aie=new Zombie_AI(bchar);
		      aie->setTarget(KnowledgePool::Instance()->getCharacter(1));
		      KnowledgePool::Instance()->AddAIEntity(bchar->getID(),aie);
		    }
		  else if(AI=="Seeker")
		    {
		      Seeker_AI*  aie=new Seeker_AI(bchar);
		      aie->setTarget(KnowledgePool::Instance()->getCharacter(1));
		      KnowledgePool::Instance()->AddAIEntity(bchar->getID(),aie);
		    }
		  else if(AI=="Idle")
		  {
			  Idle_AI *aie=new Idle_AI(bchar);
			  KnowledgePool::Instance()->AddAIEntity(bchar->getID(),aie);
		  }
		}
	      string position=member.child("Location").child_value();
	      cout<<"position"<<position<<endl;
	      if(position!="")
		{
		  Tokenizer t;
		  t.setDelimeter(",");
		  t.setInput(position);
		  vector<string> tokens=t.split();
		  int xpos=atoi(tokens[0].c_str());
		  int ypos=atoi(tokens[1].c_str());
		  int tile_size=MapIndex::Instance()->getMap()->getTileSize();
		  MapIndex::Instance()->AddCharacter(bchar);
		  cout<<"Setting position to"<<xpos<<','<<ypos<<endl;
		  bchar->SetPosition(xpos*tile_size,ypos*tile_size);
		  cout<<"Adding character"<<endl;
		  
		  cout<<"Character Added"<<endl;
		  members.insert(bchar->getID());
		  MapIndex::Instance()->CharIndexUpdate(bchar,0,0);
		  cout<<"Index Updated"<<endl;
		}
	    }
	  cout<<"Creating new team"<<endl;
	  team=new Team(name,members);
	  KnowledgePool::Instance()->AddTeam(team);
	}
    }
  cout<<"Done Loading Teams"<<endl;
}

Doodad* XmlBuilder::LoadDoodad(string xmlfile)
{
cout<<"******BUILDING DOODAD FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  AnimatedEntity* aent=LoadEntity(xmlfile);
  Doodad *doodad=new Doodad(aent);
  pugi::xml_node  doodadfuncs=doc.select_nodes("//States")[0].node();
  for(pugi::xml_node node=doodadfuncs.first_child();node;node=node.next_sibling())
    {
      int func_id=LookUpDoodadFunction(node.child_value());
    if(func_id!=-1)
    {
      cout<<"Doodad Found in the Archive"<<endl;
      //the_effect=spellarchives[LookUpSpell(effect.child_value())].spell_effect;
      doodad->AddState(DoodadFunctions[func_id].Doodadfunc);
	
    }  
    
    }

  pugi::xml_node  visibilitynode=doc.select_nodes("//Visibility")[0].node();
  int visibility=atoi(visibilitynode.child_value());
  cout<<"Visibility:"<<visibility<<endl;
  doodad->setVisibility(visibility);
  
  return doodad;
}

void XmlBuilder::LoadDoodads(string xmlfile)
{
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node doodadsnode=doc.select_nodes("//Doodads")[0].node();
  for(pugi::xml_node node=doodadsnode.child("Doodad");node;node=node.next_sibling("Doodad"))
    {
      Doodad *doodad=LoadDoodad(node.child("DoodadFile").child_value());
       string position=node.child("Location").child_value();
       if(position!="")
	 {
	   Tokenizer t;
	   t.setDelimeter(",");
	   t.setInput(position);
	   vector<string> tokens=t.split();
	   int xpos=atoi(tokens[0].c_str());
	   int ypos=atoi(tokens[1].c_str());
	   int tile_size=MapIndex::Instance()->getMap()->getTileSize();
	   
	   doodad->GetEntity()->setPosition(xpos*tile_size,ypos*tile_size);	   
	   MapIndex::Instance()->AddDoodad(doodad);
	   MapIndex::Instance()->DoodadIndexUpdate(doodad,0,0,doodad->getVisibility());

	 }
    }

}

Quest* XmlBuilder::LoadQuest(string xmlfile, lua_State *l)
{
cout<<"******BUILDING QUEST FORM XML:"<<xmlfile<<"******"<<endl;
  xml_document doc;
  xml_parse_result result = doc.load_file(xmlfile.c_str());
  pugi::xml_node  questnode=doc.select_nodes("//Quest")[0].node();
  string questname=questnode.child("Name").child_value();

  Quest *quest=new Quest(questname);
  cout<<"Quest Name:"<<questname<<endl;
  for(pugi::xml_node node=questnode.child("Objective");node;node=node.next_sibling("Objective"))
  {
	  string objective_name=node.child("Name").child_value();
	  cout<<"Name:"<<objective_name<<endl;
	  pugi::xml_node magic;
	  Objective *objective=NULL;;
	  if(magic=node.child("Script"))
	  {
		  
		  string lua_func=magic.child_value();
		  cout<<"Script:"<<lua_func<<endl;
		  objective=new LuaObjective(objective_name,lua_func,l);
	  }
	  else if(magic=node.child("Builtin"))
	  {
		  string builtin=magic.child_value();
		  int builtin_func=LookUpObjective(builtin.c_str());
		  if(builtin_func!=-1)
		  {
			  objective=new BuiltinObjective(objective_name,BuiltinObjectives[builtin_func].objective_func);
		  }
		  else
		  {
			  cout<<"Could not find builtin"<<builtin<<endl;
			  exit(-1);
		  }
		  
		  
	  }
	  if(objective)
		  quest->addObjective(objective);
  }
  return quest;
}
