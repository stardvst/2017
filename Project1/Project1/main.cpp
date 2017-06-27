#include <iostream>


// NOT GOOD DESIGN!!!

/* enum class Color { 
    Red, 
    Blue 
};

enum class Size { 
    Small, 
    Medium, 
    Large 
};


class WrongEnumValues : public std::exception {};

void NotGoodEnumDesign() {

    Color color;
    Size size;

    switch(color) {
        case Color::Red:
            switch(size) {
                case Size::Small:
                    // code
                    break;
                case Size::Medium:
                    // code
                    break;
                case Size::Large:
                    // code
                    break;
                default:
                    throw WrongEnumValues();
            }
        case Color::Blue:
            switch(size) {
                case Size::Small:
                    // code
                    break;
                case Size::Medium:
                    // code
                    break;
                case Size::Large:
                    // code
                    break;
                default:
                    throw WrongEnumValues();
            }
    }

}

*/



/*
enum class Color_Size {
    Red_Small,
    Red_Medium,
    Red_Large,
    Blue_Small,
    Blue_Medium,
    Blue_Large
};


constexpr Color_Size combineEnums(Color color, Size size) {
    switch(color) {
        case Color::Red:
            switch(size) {
                case Size::Small: return Color_Size::Blue_Small;
                case Size::Medium: return Color_Size::Blue_Medium;
                case Size::Large: return Color_Size::Blue_Large;
                default: throw WrongEnumValues();
            }
        case Color::Blue:
            switch(size) {
                case Size::Small: return Color_Size::Red_Small;
                case Size::Medium: return Color_Size::Red_Medium;
                case Size::Large: return Color_Size::Red_Large;
                default: throw WrongEnumValues();
            }
    }
}


void GoodEnumDesign(Color color, Size size) {
    switch(combineEnums(color, size)) {
        case combineEnums(Color::Red, Size::Small):
            // code
            break;
        case combineEnums(Color::Red, Size::Medium):
            // code
            break;
        case combineEnums(Color::Red, Size::Large):
            // code
            break;
        case combineEnums(Color::Blue, Size::Small):
            // code
            break;
        case combineEnums(Color::Blue, Size::Medium):
            // code
            break;
        case combineEnums(Color::Blue, Size::Large):
            // code
            break;
        default:
            throw WrongEnumValues();
    }
}

*/


enum class Color {
    Red,
    Blue,
    END
};

enum class Size {
    Small,
    Medium,
    Large,
    END
};

template<typename Enum>
constexpr std::size_t enumValue(Enum e) {
    return static_cast<std::size_t>(e);
}

template<typename Enum>
constexpr std::size_t enumSize() {
    return enumValue(Enum::END);
}

template<typename Enum1, typename Enum2>
constexpr std::size_t combineEnums(Enum1 enum1, Enum2 enum2) {
    return enumValue(e1) + enumSize<Enum1>() * enumValue(e2);
}


template<typename Enum1, typename Enum2>
struct CombineEnums {
    constexpr std::size_t operator()(Enum1 e1, Enum2 e2) {
        return enumValue(e1) + enumSize<Enum1>() * enumValue(e2);
    }
};


void real_switch(Color color, Size size) {
    CombineEnums<Color, Size> combineEnums;
    switch(combineEnums(color, size)) {
        case combineEnums(Color::Red, Size::Small) {

        }
    }
}