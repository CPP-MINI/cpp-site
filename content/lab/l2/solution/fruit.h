#pragma once

namespace l2 {

    enum class Color{
        Red, Orange, Green, Violet
    };

    enum class FruitType {
        Apple, Orange, Plum
    };

    struct Fruit{
        Color color;
        FruitType type;
    };

    static constexpr Fruit RipeApple {.color = Color::Red, .type = FruitType::Apple };
    static constexpr Fruit UnripeApple {.color = Color::Green, .type = FruitType::Apple };
    static constexpr Fruit RipeOrange {.color = Color::Orange, .type = FruitType::Orange }; // C-style enums have problems here
    static constexpr Fruit UnripeOrange {.color = Color::Green, .type = FruitType::Orange }; 
    static constexpr Fruit RipePlum {.color = Color::Violet, .type = FruitType::Plum };
    static constexpr Fruit UnripePlum {.color = Color::Green, .type = FruitType::Plum };
}