#pragma once

namespace l2
{

enum class Color
{
    Red,
    Orange,
    Green,
    Violet
};

enum class FruitType
{
    Apple,
    Orange,
    Plum
};

struct Fruit
{
    Color color;
    FruitType type;
};

static const Fruit RipeApple{.color = Color::Red, .type = FruitType::Apple};
static const Fruit UnripeApple{.color = Color::Green, .type = FruitType::Apple};
static const Fruit RipeOrange{.color = Color::Orange,
                                  .type = FruitType::Orange};  // C-style enums have problems here
static const Fruit UnripeOrange{.color = Color::Green, .type = FruitType::Orange};
static const Fruit RipePlum{.color = Color::Violet, .type = FruitType::Plum};
static const Fruit UnripePlum{.color = Color::Green, .type = FruitType::Plum};
}  // namespace l2