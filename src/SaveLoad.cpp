
#include "SaveLoad.h"

void saveGame(std::string profileName)
{

    std::string line("data/saves/" + profileName);

    galaxy_mkdir(line);
    line.append("/save");
    line.append(".crit");

    std::string invLine("data/saves/" + profileName);
    invLine.append("/save");
    invLine.append(".inv");
    std::ofstream outputFileItems(invLine.c_str());

    std::ofstream outputFile(line.c_str());
    for(auto squaddie : Squaddies)
    {
        Npc critter = *squaddie;

        outputFile << "[name:" << critter.name << "]"
               << "[race:" << critter.race << "]"
               << "[xpos:" << critter.xpos << "]"
               << "[ypos:" << critter.ypos << "]"
               << "[strength:" << critter.attributes.strength << "]"
               << "[perception:" << critter.attributes.perception << "]"
               << "[intelligence:" << critter.attributes.intelligence << "]"
               << "[charisma:" << critter.attributes.charisma << "]"
               << "[endurance:" << critter.attributes.endurance << "]"
               << "[dexterity:" << critter.attributes.dexterity << "]"
               << "[agility:" << critter.attributes.agility << "]"
               << "[health:" << critter.health << "]"
               //<< "[action:" << critter.action << "]"
               << "[angle:" << critter.angle << "]"
               << "[thirst:" << critter.thirst << "]"
               << "[hunger:" << critter.hunger << "]"
               << "[strengthxp:" << critter.attributes.strengthxp << "]"
               << "[perceptionxp:" << critter.attributes.perceptionxp << "]"
               << "[intelligencexp:" << critter.attributes.intelligencexp << "]"
               << "[charismaxp:" << critter.attributes.charismaxp << "]"
               << "[endurancexp:" << critter.attributes.endurancexp << "]"
               << "[dexterityxp:" << critter.attributes.dexterityxp << "]"
               << "[agilityxp:" << critter.attributes.agilityxp << "]"
               << "[cbaseid:" << critter.cbaseid << "]"
               << "[maxhealth:" << critter.maxhealth << "]"
               << "{Tags:" << critter.tags << "}";
               outputFile << std::endl;

        if(critter.inventory.empty())
            continue;

        std::ofstream file;
        file.open(invLine.c_str(), std::fstream::in | std::fstream::ate);
        if(file.is_open())
        {
            for(auto item : critter.inventory)
            {
                file << "[owner:" << critter.name << "]"
                "[name:" << item.name << "]"
                "[amount:" << item.amount << "]";
                for(auto status : item.statusEffects)
                {
                    file << "{StatusEffect:"
                    << "[Name:" << status.name << "]"
                    << "[Duration:" << status.duration << "]"
                    << "[AuraRadius:" << status.auraRadius << "]"

                    << "[AuraAllies:" << status.auraAffectsAllies << "]"
                    << "[AuraEnemies:" << status.auraAffectsEnemies << "]"
                    << "[AuraNeutrals:" << status.auraAffectsNeutrals << "]";
                    for(auto aspect : status.aspects)
                        file << "[Aspect:" << aspect.name << ":" << aspect.potency << ":" << aspect.type << "]" ;
                    file << "}";
                }
                for(auto status : item.statusEffectsInflict)
                {
                    file << "{StatusEffectInflict:"
                    << "[Name:" << status.name << "]"
                    << "[Duration:" << status.duration << "]"
                    << "[AuraRadius:" << status.auraRadius << "]"

                    << "[AuraAllies:" << status.auraAffectsAllies << "]"
                    << "[AuraEnemies:" << status.auraAffectsEnemies << "]"
                    << "[AuraNeutrals:" << status.auraAffectsNeutrals << "]";
                    for(auto aspect : status.aspects)
                        file << "[Aspect:" << aspect.name << ":" << aspect.potency << ":" << aspect.type << "]" ;
                    file << "}";
                }
                file << std::endl;
            }
        }








        /*
        std::ofstream outputFileItems(invLine.c_str());

        for (auto i = critter.inventory.begin(); i != critter.inventory.end();
             i++)
        {
            outputFile << "[" << (*i).name << "]";
        }
        outputFile << "";

        */

    }





    /*

    std::ofstream file;
    con("looking for file...");
    file.open(line.c_str(), std::fstream::in | std::fstream::ate);
    if (file.is_open())
    {
        con("Problem? 3");
        file << "[name:" << critter.name << "]"
             << "[race:" << critter.race << "]"
             << "[xpos:" << critter.xpos << "]"
             << "[ypos:" << critter.ypos << "]"
             << "[strength:" << critter.attributes.strength << "]"
             << "[perception:" << critter.attributes.perception << "]"
             << "[intelligence:" << critter.attributes.intelligence << "]"
             << "[charisma:" << critter.attributes.charisma << "]"
             << "[endurance:" << critter.attributes.endurance << "]"
             << "[dexterity:" << critter.attributes.dexterity << "]"
             << "[agility:" << critter.attributes.agility << "]"
             << "[health:" << critter.health << "]"
             //<< "[action:" << critter.action << "]"
             << "[angle:" << critter.angle << "]"
             << "[thirst:" << critter.thirst << "]"
             << "[hunger:" << critter.hunger << "]"
             << "[strengthxp:" << critter.attributes.strengthxp << "]"
             << "[perceptionxp:" << critter.attributes.perceptionxp << "]"
             << "[intelligencexp:" << critter.attributes.intelligencexp << "]"
             << "[charismaxp:" << critter.attributes.charismaxp << "]"
             << "[endurancexp:" << critter.attributes.endurancexp << "]"
             << "[dexterityxp:" << critter.attributes.dexterityxp << "]"
             << "[agilityxp:" << critter.attributes.agilityxp << "]"
             << "[cbaseid:" << critter.cbaseid << "]"
             << "[maxhealth:" << critter.maxhealth << "]"
             << "{Tags:" << critter.tags << "}"
             << "{Blood:" << critter.bloodcontent << "}"
             << "{Items:";
        con("Problem? 4");

        //for(int i = 0; i != Critter.inventory.size(); i++)
        for (auto i = critter.inventory.begin(); i != critter.inventory.begin();
             i++)
        {
            file << "[" << (*i).name << "]";
        }
        file << "}";
        file << std::endl;
        con("Problem? 5");
        //Con("Added", false);
        //Con(object.name);
        file.close();
    } // End to Load Map

    */
    /*debug("v-Adding Tags-v");
                debug(StringFindChaos(line,"{Tags:","}"));
                debug("^-Added Tags-^");
                Critter.tags.append(StringFindChaos(line,"{Tags:","}"));
                std::set<std::string> Items;
                std::string List;
                List.append(StringFindChaos(line,"{Items:","}"));
                Items = StringFindSetChaos(List,"[","]");
                for(std::set<std::string>::iterator i = Items.begin(); i != Items.end(); i++)
                {
                    std::string OogaBooga = *i;
                    char *a=new char[OogaBooga.size()+1];a[OogaBooga.size()]=0;memcpy(a,OogaBooga.c_str(),OogaBooga.size());
                    if(Debug){ std::cout << "Pre Critter.AddItem \n";}
                    Critter.AddItem(a,1);
                    if(Debug){ std::cout << "*Post Critter.AddItem* \n";}
                }*/

}

void loadGame(std::string profileName)
{

}
