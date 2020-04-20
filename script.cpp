#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>

int strength = 0;
int dexterity = 1;
int constitution = 2;
int intelligence = 3;
int wisdom = 4;
int charisma = 5;

std::vector<int> levels_exp_req =
{ 0, 300, 900, 2700, 6500, 14000,
  23000, 34000, 48000, 64000, 85000, 100000,
  120000, 140000, 165000, 195000, 225000, 265000,
  305000, 355000, 355000
};

class dnd_class {
  public:
    std::string name;
    int hit_dice;
};

class dnd_character {
  public:
    std::string name;
    dnd_class character_class;
    int ability_mods[5];
    int level;
    int proficiency_bonus;
    int init;
    int AC;
    int Max_HP;
    int HP;
};

bool cmp_init(dnd_character const & a, dnd_character const & b) {
  return a.init > b.init;
}

void print_welcome_message(std::string ver) {
  std::cout << "=================================================================" << '\n';
  std::cout << '\n';
  std::cout << "Welcome to the DnD Toolchest! ver " + ver << '\n';
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
  std::cout << "5 - get level based on exp" << '\n';
  std::cout << "6 - keep track of combat" << '\n';
}

void start_init() {
  dnd_character entities[99];
  std::cout << "\nPlease enter the number of players and creatures in the fight. (you can edit this later)" << '\n';
  int entity_count;
  std::cin >> entity_count;
  std::cout << "=== please enter all the creatures ===" << '\n';
  for (size_t i = 0; i < entity_count; i++) {
    std::cout << "=== creature " << i + 1 << '\n';
    std::cout << "name : ";
    std::cin.ignore();
    std::getline(std::cin, entities[i].name);
    std::cout << "init : ";
    std::cin >> entities[i].init;
    std::cout << "AC : ";
    std::cin >> entities[i].AC;
    std::cout << "HP : ";
    std::cin >> entities[i].HP;
    std::cout << '\n';
  }
  std::sort(entities, entities + entity_count, cmp_init);
  int iter = 0;
  int shown_iter = iter;
  std::cout << "====== INIT BEGIN ======" << '\n';
  std::cout << "Press '\\' and enter to stop. \nPress 'a' and enter to add another creature. \nPress 'h' and enter to change the HP value." << '\n';
  std::cout << '\n';
  while (true) {
    int c = getchar();
    if (c == 92) {
      break;
    } else if (c == 97) {
      ++entity_count;

      std::cout << '\n';
      std::cout << "name : ";
      std::cin.ignore();
      std::getline(std::cin, entities[entity_count - 1].name);
      std::cout << "init : ";
      std::cin >> entities[entity_count - 1].init;
      std::cout << "AC : ";
      std::cin >> entities[entity_count - 1].AC;
      std::cout << "HP : ";
      std::cin >> entities[entity_count - 1].HP;
      std::cout << '\n';

      std::sort(entities, entities + entity_count, cmp_init);

      continue;
    } else if (c == 104) {
      std::cout << "\nNew HP value : ";
      int new_hp;
      std::cin >> new_hp;
      entities[shown_iter].HP = new_hp;
      continue;
    }
    std::cout << "It's " << entities[iter].name << "'s " << "turn.";
    std::cout << "(";
    std::cout << "init " << entities[iter].init;
    std::cout << ", AP " << entities[iter].AC;
    std::cout << ", HP " << entities[iter].HP;
    std::cout << ")";
    shown_iter = iter;

    if (iter == entity_count - 1) {
      iter = 0;
      continue;
    }
    iter ++;
  }
  return;
}

int get_level() {
  int exp = 0;
  int level = 0;
  std::cout << "\nWhat is your exp value?" << '\n';\
  std::cin >> exp;
  for (size_t i = 0; i < levels_exp_req.size(); i++) {
    if(exp == 355000) {
      level = 20;
      break;
    }
    if (i == 0) {
      continue;
    }
    if (exp < levels_exp_req.at(i) && exp >= levels_exp_req.at(i - 1)) {
      level = i;
      break;
    }
  }
  int xp_left = levels_exp_req.at(level) - exp;
  std::cout << "\nYou need " << xp_left << " more exp to reach level " << std::min(level + 1, 20);
  return level;
}

int get_ability_mod() {
  int ability_score;
  std::cout << "\nWhat is your ability score?" << '\n';
  std::cin >> ability_score;
  ability_score = std::min(ability_score, 30);
  if (ability_score < 1) {
    ability_score = 1;
  }
  int ability_mod = (ability_score - 10) / 2;
  return ability_mod;
}

int get_proficiency() {
  int proficiency_bonus;
  dnd_character character;
  std::cout << "\nWhat is your total character level?" << '\n';
  std::cin >> character.level;
  character.level = std::min(character.level, 20);
  proficiency_bonus = 1 + (character.level / 4 + (character.level % 4 != 0));
  return proficiency_bonus;
}

int calc_ac() {
  int base_ac = 0;
  int ac = 0;

  dnd_character character;

  std::cout << "\nWhat is your dexterity mod? (without the '+')" << '\n';
  std::cin >> character.ability_mods[dexterity];
  int bonus = character.ability_mods[dexterity];

  std::cout << "\nIs your character a draconic sorcerer? (y/n)" << '\n';
  std::string is_draconic_sorcerer;
  std::cin >> is_draconic_sorcerer;
  if (is_draconic_sorcerer == "y") {
    base_ac = 13;
    ac = base_ac + character.ability_mods[dexterity];
    return ac;
  }

  std::cout << "\nWhat armor does your character have? (all lowercase, see the armor table, type 'none' if they don't have any)" << '\n';
  std::string armor;
  std::cin.ignore();
  std::getline(std::cin, armor);
  //light armor
  if (armor == "padded") {
    base_ac = 11;
  } else if (armor == "leather") {
    base_ac = 11;
  } else if (armor == "studded leather") {
    base_ac = 12;
  } else if (armor == "hide") {
    base_ac = 12;
    bonus = std::min(bonus, 2);
  //medium armor
  } else if (armor == "chain shirt") {
    base_ac = 13;
    bonus = std::min(bonus, 2);
  } else if (armor == "scale mail") {
    base_ac = 13;
    bonus = std::min(bonus, 2);
  } else if (armor == "breastplate") {
    base_ac = 14;
    bonus = std::min(bonus, 2);
  } else if (armor == "half plate") {
    base_ac = 15;
    bonus = std::min(bonus, 2);
  //heavy armor
  } else if (armor == "ring mail") {
    base_ac = 14;
    bonus = 0;
  } else if (armor == "chain mail") {
    base_ac = 16;
    bonus = 0;
  } else if (armor == "splint") {
    base_ac = 17;
    bonus = 0;
  } else if (armor == "plate") {
    base_ac = 18;
    bonus = 0;
  } else if (armor == "none") {
    base_ac = 10;
    bonus = character.ability_mods[dexterity];
  }

  if (base_ac == 0) {
    std::cout << "That is not a valid item!" << '\n';
    return 0;
  }

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
  std::cin.ignore();
  std::getline (std::cin,class_input);
  dnd_class character_class;
  character_class.name = "";

  if(class_input != "") {
    if (class_input == "artificer") {
      character_class.name = "artificer";
      character_class.hit_dice = 8;
    } else if (class_input == "barbarian") {
      character_class.name = "barbarian";
      character_class.hit_dice = 12;
    } else if (class_input == "bard") {
      character_class.name = "bard";
      character_class.hit_dice = 8;
    } else if (class_input == "cleric") {
      character_class.name = "cleric";
      character_class.hit_dice = 8;
    } else if (class_input == "druid") {
      character_class.name = "druid";
      character_class.hit_dice = 8;
    } else if (class_input == "fighter") {
      character_class.name = "fighter";
      character_class.hit_dice = 10;
    } else if (class_input == "monk") {
      character_class.name = "monk";
      character_class.hit_dice = 8;
    } else if (class_input == "paladin") {
      character_class.name = "paladin";
      character_class.hit_dice = 10;
    } else if (class_input == "ranger") {
      character_class.name = "ranger";
      character_class.hit_dice = 10;
    } else if (class_input == "rogue") {
      character_class.name = "rogue";
      character_class.hit_dice = 8;
    } else if (class_input == "ranger") {
      character_class.name = "ranger";
      character_class.hit_dice = 10;
    } else if (class_input == "sorcerer") {
      character_class.name = "sorcerer";
      character_class.hit_dice = 6;
    } else if (class_input == "warlock") {
      character_class.name = "warlock";
      character_class.hit_dice = 8;
    } else if (class_input == "wizard") {
      character_class.name = "wizard";
      character_class.hit_dice = 6;
    } else if (class_input == "blood hunter") {
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
  } else if (character_class.name == "sorcerer") {
    std::cout << "\nIs your character a draconic sorcerer? (y/n)" << '\n';
    std::string is_draconic_sorcerer;
    std::cin >> is_draconic_sorcerer;
    if (is_draconic_sorcerer == "y") {
      hp += character.level;
    }
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
  std::string version =  "1.4.0";
  print_welcome_message(version);
  std::cout << "press enter to continue..." << '\n';
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
  } else if (opt == 3) {
    int prof;
    prof = get_proficiency();
    std::cout << "\nYour proficiency bonus is ";
    std::cout << "+" << prof << '\n';
    std::cout << "press enter to exit..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
  } else if (opt == 4) {
    int mod;
    mod = get_ability_mod();
    std::cout << "\nYour ability modifier is ";
    if (mod >= 0) {
      std::cout << "+" ;
    }
    std::cout << mod << '\n';
    std::cout << "press enter to exit..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
  } else if (opt == 5) {
    int level;
    level = get_level();
    std::cout << "\nYour level is " << level << '\n';
    std::cout << "press enter to exit..." << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
  } else if (opt == 6) {
    start_init();
    std::cout << "\ninit ended." << '\n';
  } else {
    std::cout << "error : invalid input." << '\n';
    std::cout << "Press enter to exit..." << '\n';
    std::cin.ignore();
    char c = getchar();
  }
  return 0;
}
