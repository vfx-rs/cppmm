#pragma once 

namespace mimpl {

class Number {
    int _number;

public:
    Number() : _number(42) {}

    int get_number() const { return _number; }
};

}
