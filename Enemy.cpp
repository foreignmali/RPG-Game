#include "Entity.h"

Slime::Slime(Room* location){
    string names[]={"Blobous","Slip","Sopp","Sliem","David"};
    Entity::Entity(names[rand()%5],location,5,1);
}
Goblin::Goblin(Room* location){
    string names[]={"Deez","Globn","Alexander","Corpus","Nubs"};
    Entity::Entity(names[rand()%5],location,10,1);
}
Bird::Bird(Room* location){
    string names[]={"Pidgee","Fletcher","Sanders","Flyer","Bord"};
    Entity::Entity(names[rand()%5],location,7,1);
}
class Goblin : public Entity {
    
public:
    const string names[5]={"Blobous","Slip","Sopp","Sliem","David"};
    Goblin(Room* location): Entity(names[rand()%5], location, 80, 1) {}

    void dirtyStrike(Entity* target) {
        // Code for Dirty Strike
    }

    void goblinRush() {
        // Code for Goblin Rush
    }
};

// Giant Spider class, inherits from Entity
class GiantSpider : public Entity {
public:
    GiantSpider(Room* location)
        : Entity("Giant Spider", location, 120, 1) {}

    void webTrap(Entity* target) {
        // Code for Web Trap
    }

    void venomSpray() {
        // Code for Venom Spray
    }
};

// Skeleton Warrior class, inherits from Entity
class SkeletonWarrior : public Entity {
public:
    SkeletonWarrior(Room* location)
        : Entity("Skeleton Warrior", location, 90, 1) {}

    void boneShield() {
        // Code for Bone Shield
    }

    void revenantStrike(Entity* target) {
        // Code for Revenant Strike
    }
};

// Orc Brute class, inherits from Entity
class OrcBrute : public Entity {
public:
    OrcBrute(Room* location)
        : Entity("Orc Brute", location, 200, 1) {}

    void berserkSmash(Entity* target) {
        // Code for Berserk Smash
    }

    void warCry() {
        // Code for War Cry
    }
};

// Fire Drake class, inherits from Entity
class FireDrake : public Entity {
public:
    FireDrake(Room* location)
        : Entity("Fire Drake", location, 300, 1) {}

    void fireBreath(Entity* target) {
        // Code for Fire Breath
    }

    void scorchingAura() {
        // Code for Scorching Aura
    }
};

// Dark Sorcerer class, inherits from Entity
class DarkSorcerer : public Entity {
public:
    DarkSorcerer(Room* location)
        : Entity("Dark Sorcerer", location, 250, 1) {}

    void darkGrasp(Entity* target) {
        // Code for Dark Grasp
    }

    void summonSkeletons() {
        // Code for Summon Skeletons
    }

    void drainLife(Entity* target) {
        // Code for Drain Life
    }
};

// Troll class, inherits from Entity
class Troll : public Entity {
public:
    Troll(Room* location)
        : Entity("Troll", location, 350, 1) {}

    void regeneration() {
        // Code for Regeneration
    }

    void crushingBlow(Entity* target) {
        // Code for Crushing Blow
    }

    void trollRoar() {
        // Code for Troll Roar
    }
};

// Lich King class, inherits from Entity
class LichKing : public Entity {
public:
    LichKing(Room* location)
        : Entity("Lich King", location, 500, 1) {}

    void iceStorm() {
        // Code for Ice Storm
    }

    void raiseDead() {
        // Code for Raise Dead
    }

    void soulDrain(Entity* target) {
        // Code for Soul Drain
    }

    void deathTouch(Entity* target) {
        // Code for Death's Touch
    }
};

// Wyvern class, inherits from Entity
class Wyvern : public Entity {
public:
    Wyvern(Room* location)
        : Entity("Wyvern", location, 400, 1) {}

    void wingFlap() {
        // Code for Wing Flap
    }

    void poisonousBite(Entity* target) {
        // Code for Poisonous Bite
    }

    void diveBomb(Entity* target) {
        // Code for Dive Bomb
    }
};

// Demon Lord class, inherits from Entity
class DemonLord : public Entity {
public:
    DemonLord(Room* location)
        : Entity("Demon Lord", location, 1000, 1) {}

    void inferno() {
        // Code for Inferno
    }

    void darkPact() {
        // Code for Dark Pact
    }

    void summonDemons() {
        // Code for Summon Demons
    }

    void eternalTorment() {
        // Code for Eternal Torment
    }

    void hellsGate(Entity* target) {
        // Code for Hell's Gate
    }
};