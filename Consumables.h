#ifndef CONSUMABLES_H
#define CONSUMABLES_H

#include <string>

class Item {
public:
    virtual std::string getType() const = 0;
    virtual ~Item() = default;
protected:
    std::string name;
};

class Weapon : public Item {
public:
    std::string getType() const override { return "Weapon"; }
    void use();
};

class Potion : public Item {
public:
    std::string getType() const override { return "Potion"; }
    void use();
};

class Armor : public Item {
public:
    std::string getType() const override { return "Armor"; }
    void use();
};
class Status {
public:
    Status(const std::string& name) : name(name) {}
    std::string getName() const { return name; }

private:
    std::string name;
};

class Buff : public Status {
public:
    Buff(const std::string& name) : Status(name) {}
};

class Debuff : public Status {
public:
    Debuff(const std::string& name) : Status(name) {}
};

#endif // CONSUMABLES_H