#include <vector>
#include <iostream>

#include "Character.hpp"

//#define STAGE_1
//#define STAGE_2
//#define STAGE_3

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "--- Etap 1: Podstawowe Dziedziczenie i Polimorfizm ---" << std::endl;
    {
#ifdef STAGE_1
        Warrior* warrior = new Warrior("Aragorn");
        Mage* mage = new Mage("Gandalf");
        Warrior* monster = new Warrior("Goblin", 50, 5);

        std::cout << "\nDemonstrating polymorphism with base class pointers:" << std::endl;
        Character* polymorphChar = warrior;
        if (polymorphChar && polymorphChar->isAlive() && monster->isAlive()) {
            polymorphChar->attack(monster);
        }

        polymorphChar = mage;
        if (polymorphChar && polymorphChar->isAlive() && monster->isAlive()) {
            polymorphChar->attack(monster);
        }

        delete warrior;
        delete mage;
        delete monster;
#endif // STAGE_1
    }
    std::cout << "\n--- Koniec Etapu 1 ---\n" << std::endl;

    std::cout << "--- Etap 2: Wielodziedziczenie i Wyjatki ---" << std::endl;
    {
#ifdef STAGE_2
        BattleMage* battleMage = new BattleMage("Kaelthas", 100, 50);
        Warrior* target_warrior = new Warrior("Training Dummy", 200, 0);

        std::cout << "Attempting BattleMage attacks (will run out of mana):" << std::endl;
        for (int i = 0; i < 10; ++i) {
            if (battleMage && battleMage->isAlive() && target_warrior && target_warrior->isAlive()) {
                try {
                    battleMage->attack(target_warrior);
                }
                catch (const NoManaException& e) {
                    std::cerr << "Caught NoManaException in main: " << e.what() << std::endl;
                    battleMage->heal(5);
                }
                catch (const std::exception& e) {
                    std::cerr << "Caught general exception in main: " << e.what() << std::endl;
                }
                catch (...) {
                    std::cerr << "Caught unknown exception in main." << std::endl;
                }
            }
            else {
                break;
            }

        }

        std::cout << "\nAdding mana to BattleMage:" << std::endl;
        battleMage->addMana(100);
        if (battleMage && battleMage->isAlive() && target_warrior && target_warrior->isAlive()) {
            battleMage->attack(target_warrior);
        }

        delete battleMage;
        delete target_warrior;
#endif // STAGE_2
    }
    std::cout << "\n--- Koniec Etapu 2 ---\n" << std::endl;


    std::cout << "--- Etap 3: RTTI (typeid, dynamic_cast) ---" << std::endl;
    {
#ifdef STAGE_3
        Mage* powerfulMage = new Mage("Merlin", 100, 200, 30);
        Warrior* sturdyWarrior = new Warrior("Gimli", 150);
        Rogue* sneakyRogue = new Rogue("Ezreal", 80, 10, 40);

        Warrior* simpleTarget_warrior = new Warrior("Weak Creature", 30, 1); 
        BattleMage* mixyBattleMage = new BattleMage("Zilong", 100, 100, 12, 18);

        std::cout << "Mage attacking targets (demonstrating dynamic_cast for bonus):" << std::endl;
        if (powerfulMage && powerfulMage->isAlive()) powerfulMage->attack(sturdyWarrior); // Should get bonus damage (is CanUseMelee)
        if (powerfulMage && powerfulMage->isAlive()) powerfulMage->attack(simpleTarget_warrior);  // Should get bonus damage (is CanUseMelee)
        if (powerfulMage && powerfulMage->isAlive()) powerfulMage->attack(sneakyRogue); // Should get bonus damage (is CanUseMelee)
        if (powerfulMage && powerfulMage->isAlive()) powerfulMage->attack(mixyBattleMage); // Should get bonus damage (is CanUseMelee)


        std::cout << "\nRogue attempting backstab (demonstrating typeid):" << std::endl;
        if (sneakyRogue && sneakyRogue->isAlive()) sneakyRogue->backstab(powerfulMage); // Should fail (is Mage, is CanCastSpells)
        if (sneakyRogue && sneakyRogue->isAlive()) sneakyRogue->backstab(sturdyWarrior); // Should succeed (is Warrior, not CanCastSpells)
        if (sneakyRogue && sneakyRogue->isAlive()) sneakyRogue->backstab(simpleTarget_warrior); // Should succeed (is Warrior, not CanCastSpells)
        if (sneakyRogue && sneakyRogue->isAlive()) sneakyRogue->backstab(mixyBattleMage); // Should fail (is BattleMage, is CanCastSpells)

        delete powerfulMage;
        delete sturdyWarrior;
        delete sneakyRogue;
        delete simpleTarget_warrior;
        delete mixyBattleMage;
#endif // STAGE_3
    }
    std::cout << "\n--- Koniec Etapu 3 ---\n" << std::endl;

    return 0;
}