#include <iostream>
#include <string>

void print_welcome_message(std::string ver) {
  std::cout << "=================================================================" << '\n';
  std::cout << '\n';
  std::cout << "Welcome to DnD utilities! ver " + ver << '\n';
  std::cout << "                 made by IAmwYvern " << '\n';
  std::cout << '\n';
  std::cout << "github repo : https://github.com/IAmwYvern/dnd-utilities" << '\n';
  std::cout << '\n';
  std::cout << "=================================================================" << '\n';
}

void print_options() {
  std::cout << "what do you wish to do?" << '\n';
  std::std::cout << "1 - calculate hp" << '\n';
}

int main(int argc, char const *argv[]) {
  std::string version =  "1.0.0";
  print_welcome_message(version);
  print_options();

  

  return 0;
}
