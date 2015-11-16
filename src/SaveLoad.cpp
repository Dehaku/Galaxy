
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
               << "[zpos:" << critter.zpos << "]"
               << "[strength:" << critter.attributes.strength << "]"
               << "[perception:" << critter.attributes.perception << "]"
               << "[intelligence:" << critter.attributes.intelligence << "]"
               << "[charisma:" << critter.attributes.charisma << "]"
               << "[endurance:" << critter.attributes.endurance << "]"
               << "[dexterity:" << critter.attributes.dexterity << "]"
               << "[agility:" << critter.attributes.agility << "]"
               << "[health:" << critter.health << "]"
               << "[angle:" << critter.angle << "]"
               << "[cbaseid:" << critter.cbaseid << "]"
               << "[maxhealth:" << critter.maxhealth << "]"
               << "[skillpoints:" << critter.skillpoints << "]"
               << "{Tags:" << critter.tags << "}";

               for(auto skill : critter.skills.list)
               {
                    if(skill.ranks == 0)
                        continue;
                    outputFile << "[Skill:" << skill.name << ":" << skill.ranks << "]";
               }

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
                for(auto invItem : item.internalitems)
                {
                    file << "[InternalItem]"
                    "[name:" << invItem.name << "]"
                    "[amount:" << invItem.amount << "]";
                    for(auto status : invItem.statusEffects)
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
                    for(auto status : invItem.statusEffectsInflict)
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
        }
    }
}

void loadGame(std::string profileName)
{
    for(auto squaddie : Squaddies)
        squaddie->toDelete = true;

    Squaddies.clear();

    std::cout << "Loading Game Profile: " + profileName + "!\n";
    std::ifstream input("data/saves/" + profileName + "/save.crit");
    if (!input.is_open())
        return;

    con("Critter File is open.");

    while (input.good())
    {
        std::string line;
        getline(input, line);
        Npc critter;

        critter.name = "Debuggery";
        std::string critterName = stringFindString(line, "[name:");
        if(critterName == "")
        { // This is an invalid line, Next!
            std::cout << "This line doesn't have a name! Invalid. \n";
            continue;
        }
        critter.race = stringFindString(line, "[race:");

        // This should save some manual work.
        critter = *getGlobalCritter(critter.race);
        critter.name = critterName;
        critter.skillpoints = stringFindNumber(line, "[skillpoints:");
        critter.xpos = stringFindNumber(line, "[xpos:");
        critter.ypos = stringFindNumber(line, "[ypos:");
        critter.zpos = stringFindNumber(line, "[zpos:");
        critter.attributes.strength = stringFindNumber(line, "[strength:");
        critter.attributes.perception = stringFindNumber(line, "[perception:");
        critter.attributes.intelligence = stringFindNumber(line, "[intelligence:");
        critter.attributes.charisma = stringFindNumber(line, "[charisma:");
        critter.attributes.endurance = stringFindNumber(line, "[endurance:");
        critter.attributes.dexterity = stringFindNumber(line, "[dexterity:");
        critter.cbaseid = stringFindNumber(line, "[cbaseid:");
        critter.tags = stringFindChaos(line,"{Tags:","}");
        std::cout << "Tags: " << critter.tags << std::endl;
        critter.health = critter.getMaxHealth();
        //status.auraAffectsAllies = booleanize(stringFindNumber(line, "[AuraAllies:"));

        con("Loading Skills");
        std::vector<std::string> skills = stringFindVectorChaos(line,"[Skill:","]");
        for(auto &skillLine : skills)
        {
            std::vector<std::string> skillBits = stringFindElements(skillLine);
            for(auto &skill : critter.skills.list)
                if(skillBits[0] == skill.name)
                    skill.ranks = std::stoi(skillBits[1]);
        }

        critter.isSquaddie = true;
        critter.faction = conFact->name;
        critter.factionPtr = conFact;
        critter.chasePriority = "Hold Position";
        std::cout << "Loaded " << critter.name << " the " << critter.race << std::endl;
        npclist.push_back(critter);
    }

    AnyDeletes(npclist);
    Squaddies.clear();
    for(auto &npc : npclist)
        if(npc.faction == "The Titanium Grip" && npc.isSquaddie)
            Squaddies.push_back(&npc);

    std::ifstream itemInput("data/saves/" + profileName + "/save.inv");
    if (!itemInput.is_open())
        return;

    Item * lastItem;
    while (itemInput.good())
    {
        std::string line;
        getline(itemInput, line);

        Item item;

        item.name = "Debuggery";
        std::string itemName = stringFindString(line, "[name:");
        if(itemName == "")
        { // This is an invalid line, Next!
            std::cout << "This line doesn't have a name! Invalid. \n";
            continue;
        }
        con("Getting item: " + itemName);
        item = *getGlobalItem(itemName);
        item.amount = stringFindNumber(line, "[amount:");

        std::vector<std::string> statusEffects = stringFindVectorChaos(line,"{StatusEffect:","}");
        std::vector<std::string> statusEffectInflicts = stringFindVectorChaos(line,"{StatusEffectInflict:","}");

        con("Status Effects");
        for(auto &statusString : statusEffects)
        {
            StatusEffect status;
            status.name = stringFindString(statusString, "[Name:");
            status.duration = stringFindNumber(statusString, "[Duration:");
            status.auraAffectsAllies = booleanize(stringFindNumber(statusString, "[AuraAllies:"));
            status.auraAffectsEnemies = booleanize(stringFindNumber(statusString, "[AuraEnemies:"));
            status.auraAffectsNeutrals = booleanize(stringFindNumber(statusString, "[AuraNeutrals:"));

            std::vector<std::string> aspectStrings = stringFindVectorChaos(statusString, "[Aspect:","]");
            for(auto &aspectString : aspectStrings)
            {
                StatusAspect aspect;

                std::vector<std::string> aspectBits = stringFindElements(aspectString);
                for(int i = 0; i != 3; i++)
                {
                    if(i == 0)
                        aspect.name = std::stoi(aspectBits[i]);
                    if(i == 1)
                        aspect.potency = std::stoi(aspectBits[i]);
                    if(i == 2)
                        aspect.type = aspectBits[i];
                }
                status.aspects.push_back(aspect);
            }
            con(item.name + " is infused with " + status.name + "!");
            item.statusEffects.push_back(status);
        }

        con("Status Effect Inflicting");
        for(auto &statusString : statusEffectInflicts)
        {
            StatusEffect status;
            status.name = stringFindString(statusString, "[Name:");
            status.duration = stringFindNumber(statusString, "[Duration:");
            status.auraAffectsAllies = booleanize(stringFindNumber(statusString, "[AuraAllies:"));
            status.auraAffectsEnemies = booleanize(stringFindNumber(statusString, "[AuraEnemies:"));
            status.auraAffectsNeutrals = booleanize(stringFindNumber(statusString, "[AuraNeutrals:"));

            std::vector<std::string> aspectStrings = stringFindVectorChaos(statusString, "[Aspect:","]");
            for(auto &aspectString : aspectStrings)
            {
                StatusAspect aspect;

                std::vector<std::string> aspectBits = stringFindElements(aspectString);
                for(int i = 0; i != 3; i++)
                {
                    if(i == 0)
                        aspect.name = std::stoi(aspectBits[i]);
                    if(i == 1)
                        aspect.potency = std::stoi(aspectBits[i]);
                    if(i == 2)
                        aspect.type = aspectBits[i];
                }
                status.aspects.push_back(aspect);
            }
            con(item.name + " is infused with inflicting " + status.name + "!");
            item.statusEffectsInflict.push_back(status);
        }




        std::string itemOwner = stringFindString(line, "[owner:");
        if(itemOwner != "")
        {
            con("Looking for " + itemOwner);
            for(auto &squaddie : Squaddies)
            {
                if(squaddie->name == itemOwner)
                {
                    con(itemOwner + " found, adding " + item.name);
                    squaddie->inventory.push_back(item);
                    lastItem = &squaddie->inventory.back();
                }
            }
        }

        if(line.find("[InternalItem]") != std::string::npos)
        {
            con("Internal Item, Shoving into " + lastItem->name);
            lastItem->internalitems.push_back(item);
        }
    }

    con("Game's loaded, You're good to go recollect some bounties!");
}