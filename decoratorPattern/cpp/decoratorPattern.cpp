#include<iostream>
using namespace std;

// character interface 
class ICharacter {
public:
    virtual string getAbility() const = 0;
    virtual ~ICharacter() = default;
};

// charcter class
class Maria : public ICharacter {
public:
    string getAbility() const override {
        return "Maria";
    }
};

class CharacterDecorator : public ICharacter {
protected:
    ICharacter* ch;
public:
    CharacterDecorator(ICharacter* ch) {
        this->ch = ch;
    }
};

class HeightUp : public CharacterDecorator {
public:
    HeightUp(ICharacter* ch) : CharacterDecorator(ch) {}

    string getAbility() const override {
        return ch->getAbility() + " With height up";
    }
};

class GunPower : public CharacterDecorator {
public:
    GunPower(ICharacter* ch): CharacterDecorator(ch) {}

    string getAbility() const override {
        return ch->getAbility() + " With gun power";
    }
};

class StarPower : public CharacterDecorator {
public:
    StarPower(ICharacter* ch) : CharacterDecorator(ch) {}

    string getAbility() const override {
        return ch->getAbility() + " With star power (limited time)";
    }

    ~StarPower() {
        cout << "Star power Destroyed" << endl;
    }
};

int main() {
    ICharacter* maria = new Maria();
    cout << "Base character: " << maria->getAbility() << endl;

    maria = new HeightUp(maria);
    cout << "After Heightup: " <<maria->getAbility() << endl;

    maria = new GunPower(maria);
    cout << "After Gunpower: " << maria->getAbility() << endl;

    maria = new StarPower(maria);
    cout << "After Startpower: " << maria->getAbility() << endl;

    delete maria;

    // ICharacter* maria = new StarPower(new GunPower(new HeightUp(new Maria())));
    // cout << "Ability: " << maria->getAbility() << endl; 

    // delete maria;

    return 0;
}