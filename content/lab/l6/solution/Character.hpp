#pragma once

#include <iostream>
#include <string>

class NoManaException : public std::exception
{
   public:
    const char* what() const noexcept override { return "Not enough mana to perform this action."; }
};

class Character;

class CanCastSpells
{
   protected:
    int mana;
    int maxMana;

   public:
    CanCastSpells(int initialMana = 100) : mana(initialMana), maxMana(initialMana) {}
    virtual ~CanCastSpells() = default;

    int getMana() const { return mana; }
    void addMana(int amount)
    {
        mana = std::min(mana + amount, maxMana);
        std::cout << "Mana increased by " << amount << ". Current mana: " << mana << std::endl;
    }

    virtual void useMana(int amount)
    {
        if (mana < amount)
        {
            throw NoManaException();
        }
        mana -= amount;
        std::cout << "Used " << amount << " mana. Remaining mana: " << mana << std::endl;
    }

    virtual void castSpell(Character* target) = 0;
};

class CanUseMelee
{
   public:
    CanUseMelee() = default;
    virtual ~CanUseMelee() = default;

    virtual void performMeleeAttack(Character* target) = 0;
};

class Character
{
   protected:
    std::string name;
    int health;
    int maxHealth;

   public:
    Character(const std::string& name, int health = 100) : name(name), health(health), maxHealth(health) {}
    virtual ~Character() = default;

    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    bool isAlive() const { return health > 0; }

    virtual void takeDamage(int damage)
    {
        health -= damage;
        if (health < 0)
            health = 0;
        std::cout << name << " took " << damage << " damage. Remaining health: " << health << std::endl;
        if (!isAlive())
        {
            std::cout << name << " has been defeated!" << std::endl;
        }
    }

    virtual void heal(int amount)
    {
        health += amount;
        if (health > maxHealth)
            health = maxHealth;
        std::cout << name << " healed " << amount << " health. Remaining health: " << health << std::endl;
    }

    virtual void attack(Character* target) = 0;
};

class Warrior : public Character, public CanUseMelee
{
   private:
    int meleeDamage;

   public:
    Warrior(const std::string& name, int health = 120, int damage = 15)
        : Character(name, health), CanUseMelee(), meleeDamage(damage)
    {
    }

    void attack(Character* target) override;
    void performMeleeAttack(Character* target) override;
};

class Mage : public Character, public CanCastSpells
{
   private:
    int spellDamage;

   public:
    Mage(const std::string& name, int health = 80, int mana = 150, int damage = 20)
        : Character(name, health), CanCastSpells(mana), spellDamage(damage)
    {
    }

    void attack(Character* target) override;
    void castSpell(Character* target) override;
};

class BattleMage : public Character, public CanCastSpells, public CanUseMelee
{
   private:
    int baseMeleeDamage;
    int baseSpellDamage;

   public:
    BattleMage(const std::string& name, int health = 100, int mana = 100, int meleeDmg = 10, int spellDmg = 15)
        : Character(name, health),
          CanCastSpells(mana),
          CanUseMelee(),
          baseMeleeDamage(meleeDmg),
          baseSpellDamage(spellDmg)
    {
    }

    void attack(Character* target) override;

    void castSpell(Character* target) override;
    void performMeleeAttack(Character* target) override;
};

class Rogue : public Character, public CanUseMelee
{
   private:
    int basicAttackDamage;
    int backstabDamage;

   public:
    Rogue(const std::string& name, int health = 90, int basicDmg = 12, int backstabDmg = 30)
        : Character(name, health), CanUseMelee(), basicAttackDamage(basicDmg), backstabDamage(backstabDmg)
    {
    }

    void attack(Character* target) override;

    void backstab(Character* target);
    void performMeleeAttack(Character* target) override;
};
