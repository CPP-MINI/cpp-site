#include <vector>
#include <iostream>
#include <memory>

#include "Character.hpp"

#define STAGE_1
#define STAGE_2
#define STAGE_3

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "--- Etap 1: Podstawowe Dziedziczenie i Polimorfizm ---" << std::endl;
    {
#ifdef STAGE_1
        std::unique_ptr<Character> warrior = std::make_unique<Warrior>("Aragorn");
        std::unique_ptr<Character> mage = std::make_unique<Mage>("Gandalf");
        std::unique_ptr<Character> monster = std::make_unique<Warrior>("Goblin", 50, 5);

        std::cout << "\nDemonstrating polymorphism with base class pointers:" << std::endl;
        if (warrior && warrior->isAlive() && monster->isAlive()) {
            warrior->attack(monster.get());
        }

        if (mage && mage->isAlive() && monster->isAlive()) {
            mage->attack(monster.get());
        }
#endif // STAGE_1
    }
    std::cout << "\n--- Koniec Etapu 1 ---\n" << std::endl;

    std::cout << "--- Etap 2: Wielodziedziczenie i Wyjatki ---" << std::endl;
    {
#ifdef STAGE_2
        std::unique_ptr<Character> battleMage = std::make_unique<BattleMage>("Kaelthas", 100, 50);
        std::unique_ptr<Character> target_warrior = std::make_unique<Warrior>("Training Dummy", 200, 0);

        std::cout << "Attempting BattleMage attacks (will run out of mana):" << std::endl;
        for (int i = 0; i < 10; ++i) {
            if (battleMage && battleMage->isAlive() && target_warrior && target_warrior->isAlive()) {
                try {
                    battleMage->attack(target_warrior.get());
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
        // Need to cast to BattleMage* to access addMana
        BattleMage* bmPtr = dynamic_cast<BattleMage*>(battleMage.get());
        if (bmPtr) {
            bmPtr->addMana(100);
        }
        if (battleMage && battleMage->isAlive() && target_warrior && target_warrior->isAlive()) {
            battleMage->attack(target_warrior.get());
        }
#endif // STAGE_2
    }
    std::cout << "\n--- Koniec Etapu 2 ---\n" << std::endl;


    std::cout << "--- Etap 3: RTTI (typeid, dynamic_cast) ---" << std::endl;
    {
#ifdef STAGE_3
        std::unique_ptr<Character> powerfulMage = std::make_unique<Mage>("Merlin", 100, 200, 30);
        std::unique_ptr<Character> sturdyWarrior = std::make_unique<Warrior>("Gimli", 150);
        std::unique_ptr<Character> sneakyRogue = std::make_unique<Rogue>("Ezreal", 80, 10, 40);

        std::unique_ptr<Character> simpleTarget_warrior = std::make_unique<Warrior>("Weak Creature", 30, 1); 
        std::unique_ptr<Character> mixyBattleMage = std::make_unique<BattleMage>("Zilong", 100, 100, 12, 18);

        std::cout << "Mage attacking targets (demonstrating dynamic_cast for bonus):" << std::endl;
        if (powerfulMage && powerfulMage->isAlive()) powerfulMage->attack(sturdyWarrior.get()); // Should get bonus damage (is CanUseMelee)
        if (powerfulMage && powerfulMage->isAlive()) powerfulMage->attack(simpleTarget_warrior.get());  // Should get bonus damage (is CanUseMelee)
        if (powerfulMage && powerfulMage->isAlive()) powerfulMage->attack(sneakyRogue.get()); // Should get bonus damage (is CanUseMelee)
        if (powerfulMage && powerfulMage->isAlive()) powerfulMage->attack(mixyBattleMage.get()); // Should get bonus damage (is CanUseMelee)


        std::cout << "\nRogue attempting backstab (demonstrating typeid):" << std::endl;
        // Need to cast to Rogue* to access backstab
        Rogue* roguePtr = dynamic_cast<Rogue*>(sneakyRogue.get());
        if (roguePtr && roguePtr->isAlive()) roguePtr->backstab(powerfulMage.get()); // Should fail (is Mage, is CanCastSpells)
        if (roguePtr && roguePtr->isAlive()) roguePtr->backstab(sturdyWarrior.get()); // Should succeed (is Warrior, not CanCastSpells)
        if (roguePtr && roguePtr->isAlive()) roguePtr->backstab(simpleTarget_warrior.get()); // Should succeed (is Warrior, not CanCastSpells)
        if (roguePtr && roguePtr->isAlive()) roguePtr->backstab(mixyBattleMage.get()); // Should fail (is BattleMage, is CanCastSpells)
#endif // STAGE_3
    }
    std::cout << "\n--- Koniec Etapu 3 ---\n" << std::endl;

    return 0;
}