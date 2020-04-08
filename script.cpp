#include <iostream>
#include <string>

class abilities {
  public:
    int strength = 0;
    int dexterity = 1;
    int constitution = 2;
    int intelligence = 3;
    int wisdom = 4;
    int charisma = 5;
};

class dnd_class {
  public:
    std::string name;
    int hit_dice;
};

class dnd_character {
  public:
    dnd_class character_class;
    int ability_mods[5];
    int level;
    int proficiency_bonus;
};

void print_welcome_message(std::string ver) {
  std::cout << "=================================================================" << '\n';
  std::cout << '\n';
  std::cout << "Welcome to DnD utilities! ver " + ver << '\n';
  std::cout << "                 made by IAmwYvern " << '\n';
  std::cout << '\n';
  std::cout << "github repo : https://github.com/IAmwYvern/dnd-utilities" << '\n';
  std::cout << '\n';
  std::cout << "=================================================================" << '\n';
  std::cout << '\n';
}

void print_options() {
  std::cout << "what do you wish to do?" << '\n';
  std::cout << "1 - calculate hp" << '\n';
}

int calc_hp() {
  int hp = 0;
  std::cout << '\n' << "What class is your character?" << '\n';
  std::string class_input;
  std::cin >> class_input;
  dnd_class character_class;
  if(class_input != "") {
    if (class_input == "artificer") {
      character_class.name = "artificer";
      character_class.hit_dice = 8;
    }
    if (class_input == "barbarian"){
      character_class.name = "barbarian";
      character_class.hit_dice = 12;
    }
    if (class_input == "bard") {
      character_class.name = "bard";
      character_class.hit_dice = 8;
    }
    if (class_input == "cleric") {
      character_class.name = "cleric";
      character_class.hit_dice = 8;
    }
    if (class_input == "druid") {
      character_class.name = "druid";
      character_class.hit_dice = 8;
    }
    if (class_input == "fighter") {
      character_class.name = "fighter";
      character_class.hit_dice = 10;
    }
    if (class_input == "monk") {
      character_class.name = "monk";
      character_class.hit_dice = 8;
    }
    if (class_input == "paladin") {
      character_class.name = "paladin";
      character_class.hit_dice = 8;
    }
    if (class_input == "ranger") {
      character_class.name = "ranger";
      character_class.hit_dice = 10;
    }
    if (class_input == "rogue") {
      character_class.name = "rogue";
      character_class.hit_dice = 8;
    }
    if (class_input == "ranger") {
      character_class.name = "ranger";
      character_class.hit_dice = 10;
    }
    if (class_input == "sorcerer") {
      character_class.name = "sorcerer";
      character_class.hit_dice = 6;
    }
    if (class_input == "warlock") {
      character_class.name = "warlock";
      character_class.hit_dice = 8;
    }
    if (class_input == "wizard") {
      character_class.name = "wizard";
      character_class.hit_dice = 6;
    }
    if (class_input == "blood hunter") {
      character_class.name = "blood hunter";
      character_class.hit_dice = 10;
    }
  }
  dnd_character character;
  character.character_class = character_class;

  std::cout << '\n' << "what level is your character?" << '\n';
  int level = 1;
  std::cin >> level;
  if (level > 20) {
    level = 20;
  }
  character.level = level;

  std::cout << '\n' << "what is your CON mod? (without the '+')" << '\n';
  int CON_mod = 0;
  std::cin >> CON_mod;
  character.ability_mods[2] = CON_mod;

  hp = character_class.hit_dice + character.ability_mods[2];
  if (character.level == 1) {
    return hp;
  }

  std::cout << '\n' << "what method do you want to use to calculate the hp? (1-rolled, 2-average)" << '\n';
  int method = 1;
  std::cin >> method;

  return hp;
}

int main(int argc, char const *argv[]) {
  std::string version =  "1.0.0";
  print_welcome_message(version);
  std::cout << "press any key to continue..." << '\n';
  std::cin.get();
  print_options();


  int opt;
  std::cin >> opt;


  if(opt == 1) {

    int hp;
    hp = calc_hp();
    std::cout << '\n' << "Your hp is " ;
    std::cout << hp << '\n';
  }

  return 0;
}
