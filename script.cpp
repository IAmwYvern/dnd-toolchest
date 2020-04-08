#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

int strength = 0;
int dexterity = 1;
int constitution = 2;
int intelligence = 3;
int wisdom = 4;
int charisma = 5;

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
  std::cout << "2 - calculate armor class" << '\n';
  std::cout << "3 - get proficiency bonus" << '\n';
  std::cout << "4 - get ability modifier" << '\n';
}

int get_ability_mod() {
  int ability_score;
  std::cout << "\nWhat is your ability score?" << '\n';
  std::cin >> ability_score;
  ability_score = std::min(ability_score, 30);
  if (ability_score == 1) {
    return -5;
  }
  if (ability_score > 1 && ability_score < 4) {
    return -4;
  }
  if (ability_score > 3 && ability_score < 6) {
    return -3;
  }
  if (ability_score > 5 && ability_score < 8) {
    return -2;
  }
  if (ability_score > 7 && ability_score < 10) {
    return -1;
  }
  if (ability_score > 9 && ability_score < 12) {
    return 0;
  }
  if (ability_score > 11 && ability_score < 14) {
    return 1;
  }
  if (ability_score > 13 && ability_score < 16) {
    return 2;
  }
  if (ability_score > 15 && ability_score < 18) {
    return 3;
  }
  if (ability_score > 17 && ability_score < 20) {
    return 4;
  }
  if (ability_score > 19 && ability_score < 22) {
    return 5;
  }
  if (ability_score > 21 && ability_score < 24) {
    return 6;
  }
  if (ability_score > 23 && ability_score < 26) {
    return 7;
  }
  if (ability_score > 25 && ability_score < 28) {
    return 8;
  }
  if (ability_score > 27 && ability_score < 30) {
    return 9;
  }
  if (ability_score == 30) {
    return 10;
  }
  return 0;
}

int get_proficiency() {
  int proficiency_bonus;
  dnd_character character;
  std::cout << "\nWhat is your total character level?" << '\n';
  std::cin >> character.level;
  character.level = std::min(character.level, 20);

  if (character.level <= 20 && character.level >= 17) {
    return 6;
  }
  if (character.level <= 16 && character.level >= 13) {
    return 5;
  }
  if (character.level <= 12 && character.level >= 9) {
    return 4;
  }
  if (character.level <= 8 && character.level >= 5) {
    return 3;
  }
  if (character.level <= 4 && character.level >= 1) {
    return 2;
  }
  return 0;
}

int calc_ac() {
  int base_ac = 0;

  dnd_character character;

  std::cout << "\nWhat is your dexterity mod? (without the '+')" << '\n';
  std::cin >> character.ability_mods[dexterity];
  int bonus = character.ability_mods[dexterity];

  std::cout << "\nWhat armor does your character have? (all lowercase, see the armor table, type 'none' if they don't have any)" << '\n';
  std::string armor;
  std::cin >> armor;
  //light armor
  if (armor == "padded") {
    base_ac = 11;
  }
  if (armor == "leather") {
    base_ac = 11;
  }
  if (armor == "studded leather") {
    base_ac = 12;
  }
  //medium armor
  if (armor == "hide") {
    base_ac = 12;
    bonus = std::min(bonus, 2);
  }
  if (armor == "chain shirt") {
    base_ac = 13;
    bonus = std::min(bonus, 2);
  }
  if (armor == "scale mail") {
    base_ac = 13;
    bonus = std::min(bonus, 2);
  }
  if (armor == "breastplate") {
    base_ac = 14;
    bonus = std::min(bonus, 2);
  }
  if (armor == "half plate") {
    base_ac = 15;
    bonus = std::min(bonus, 2);
  }
  //heavy armor
  if (armor == "ring mail") {
    base_ac = 14;
    bonus = 0;
  }
  if (armor == "chain mail") {
    base_ac = 16;
    bonus = 0;
  }
  if (armor == "splint") {
    base_ac = 17;
    bonus = 0;
  }
  if (armor == "plate") {
    base_ac = 18;
    bonus = 0;
  }
  if (armor == "none") {
    base_ac = 10;
    bonus = character.ability_mods[dexterity];
  }
  if (base_ac == 0) {
    std::cout << "That is not a valid item!" << '\n';
    return 0;
  }

  int ac = 0;

  std::cout << "\nDoes your character have a shield? (y/n)" << '\n';
  std::string has_shield;
  std::cin >> has_shield;
  if (has_shield == "y") {
    ac += 2;
  }

  ac += base_ac + bonus;
  return ac;
}

int calc_hp() {
  int hp = 0;
  std::cout << '\n' << "What class is your character? (all lowercase!)" << '\n';
  std::string class_input;
  std::cin >> class_input;
  dnd_class character_class;
  character_class.name = "";

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
      character_class.hit_dice = 10;
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
  if (character_class.name == "") {
    std::cout << "that is not a valid class!" << '\n';
    return 0;
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

  std::cout << '\n' << "Is your character a hill dwarf? (y/n)" << '\n';
  std::string is_hill_dwarf;
  std::cin >> is_hill_dwarf;
  if (is_hill_dwarf == "y") {
    hp += character.level;
  }

  std::cout << '\n' << "Does your character have the tough feat? (y/n)" << '\n';
  std::string has_tough_feat;
  std::cin >> has_tough_feat;
  if (has_tough_feat == "y") {
    hp += character.level * 2;
  }

  std::cout << '\n' << "what is your CON mod? (without the '+')" << '\n';
  int CON_mod = 0;
  std::cin >> CON_mod;
  character.ability_mods[constitution] = CON_mod;

  hp += character_class.hit_dice + character.ability_mods[constitution];
  if (character.level == 1) {
    return hp;
  }

  std::cout << '\n' << "what method do you want to use to calculate the hp? (1-rolled, 2-average)" << '\n';
  int method = 1;
  std::cin >> method;

  if (method == 1) {
    for (size_t i = 2; i <= character.level; i++) {
      int rand_num = (std::rand() % character_class.hit_dice) + 1;
      hp += rand_num;
    }
  } else {
    for (size_t i = 2; i <= character.level; i++) {
      int add = 1 + (character_class.hit_dice / 2) + character.ability_mods[constitution];
      hp += add;
    }
  }

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
    if (hp == 0) {
      std::cout << "press enter to exit..." << '\n';
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.get();
      return 0;
    }
    std::cout << '\n' << "Your hp is " ;
    std::cout << hp << '\n';
    std::cout << "press enter to exit..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
  }
  if (opt == 2) {
    int ac;
    ac = calc_ac();
    if (ac == 0) {
      std::cout << "press enter to exit..." << '\n';
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.get();
      return 0;
    }
    std::cout << '\n' << "Your AC is " ;
    std::cout << ac << '\n';
    std::cout << "press enter to exit..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
  }
  if (opt == 3) {
    int prof;
    prof = get_proficiency();
    std::cout << "\nYour proficiency bonus is ";
    std::cout << "+" << prof << '\n';
    std::cout << "press enter to exit..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
  }
  if (opt == 4) {
    int mod;
    mod = get_ability_mod();
    std::cout << "\nYour ability modifier is " << '\n';
    std::cout << "+" << mod << '\n';
    std::cout << "press enter to exit..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
  }
  return 0;
}
