#include "enum.h"

Enemies enemyConverter(int n) {
    if (n >= 0 && n <= 3) return Enemies::Human;
    if (n >= 4 && n <= 6) return Enemies::Dwarf;
    if (n >= 7 && n <= 11) return Enemies::Halfling;
    if (n >= 12 && n <= 13) return Enemies::Elf;
    if (n >= 14 && n <= 15) return Enemies::Orc;
    if (n >= 16 && n <= 17) return Enemies::Merchant;
}
