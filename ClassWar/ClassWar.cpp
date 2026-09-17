#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class Weapon {
protected:
    string requiredOwner;

public:
    Weapon(string owner) : requiredOwner(owner) {}

    virtual void useWeapon() const = 0;
    virtual string getName() const = 0;

    string getRequiredOwner() const {
        return requiredOwner;
    }
    virtual ~Weapon() = default;
};
class WizardStaff : public Weapon {
public:
    WizardStaff() : Weapon("Чарівник") {}
    void useWeapon() const override { cout << "випускає магічну вогняну кулю!" << endl; }
    string getName() const override { return "Магічний посох"; }
};
class WizardGrimoire : public Weapon {
public:
    WizardGrimoire() : Weapon("Чарівник") {}
    void useWeapon() const override { cout << "читає заборонене заклинання з прадавньої книги!" << endl; }
    string getName() const override { return "Гримуар Таємниць"; }
};

class KnightSword : public Weapon {
public:
    KnightSword() : Weapon("Лицар") {}
    void useWeapon() const override { cout << "здійснює потужний випад гострим королівським мечем!" << endl; }
    string getName() const override { return "Королівський меч"; }
};
class KnightHammer : public Weapon {
public:
    KnightHammer() : Weapon("Лицар") {}
    void useWeapon() const override { cout << "трощить ворога важким бойовим молотом!" << endl; }
    string getName() const override { return "Важкий молот"; }
};

class ElfBow : public Weapon {
public:
    ElfBow() : Weapon("Ельф") {}
    void useWeapon() const override { cout << "пускає влучну стрілу з гнучкого ельфійського лука!" << endl; }
    string getName() const override { return "Ельфійський лук"; }
};
class ElfDaggers : public Weapon {
public:
    ElfDaggers() : Weapon("Ельф") {}
    void useWeapon() const override { cout << "наносить серію блискавичних ударів парними кинджалами!" << endl; }
    string getName() const override { return "Парні кинджали"; }
};

class TrollClub : public Weapon {
public:
    TrollClub() : Weapon("Троль") {}
    void useWeapon() const override { cout << "б'є величезною грубою дубиною з розмаху!" << endl; }
    string getName() const override { return "Величезна дубина"; }
};
class TrollBoulder : public Weapon {
public:
    TrollBoulder() : Weapon("Троль") {}
    void useWeapon() const override { cout << "кидає важкий каміннюк у ворогів!" << endl; }
    string getName() const override { return "Важкий валун"; }
};

class Character {
protected:
    string name;
    string description;
    string typeName;
    Weapon* weapon;
public:
    Character(string n, string desc, string t)
        : name(n), description(desc), typeName(t), weapon(nullptr) {
    }
    void display() const {
        cout << "Герой: " << name << " (" << description << ")" << endl;
    }
    bool equipWeapon(Weapon* newWeapon) {
        if (newWeapon->getRequiredOwner() == this->typeName) {
            if (weapon != nullptr) {
                delete weapon;
            }
            weapon = newWeapon;
            cout << "Успішно озброєно: " << weapon->getName() << "!" << endl;
            return true;
        }
        else {
            cout << "Ця зброя не підходить цьому персонажу!" << endl;
            return false;
        }
    }
    void fight() const {
        if (weapon) {
            cout << name << " ";
            weapon->useWeapon();
        }
        else {
            cout << name << " б'ється голими руками (немає зброї)!" << endl;
        }
    }
    virtual ~Character() {
        if (weapon) delete weapon;
    }
};

class Wizard : public Character {
public:
    Wizard() : Character("Чарівник", "Мудрий майстер магії", "Чарівник") {}
};
class Knight : public Character {
public:
    Knight() : Character("Лицар", "Відважний воїн у броні", "Лицар") {}
};
class Elf : public Character {
public:
    Elf() : Character("Ельф", "Влучний лісовий стрілець", "Ельф") {}
};
class Troll : public Character {
public:
    Troll() : Character("Троль", "Дика і страшна сила", "Троль") {}
};
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Character* player = nullptr;
    bool running = true;
    while (running) {
        cout << " === ГОЛОВНЕ МЕНЮ === " << endl;
        cout << "1. Вибрати персонажа" << endl;
        cout << "2. Вибрати зброю" << endl;
        cout << "3. Атакувати" << endl;
        cout << "4. Вийти з гри" << endl;
        cout << "Ваш вибір (1-4): ";
        int mainChoice;
        cin >> mainChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\nВведіть цифру від 1 до 4." << endl;
            continue;
        }
        switch (mainChoice) {
        case 1: {
            int charChoice;
            cout << "\n === ВИБІР ПЕРСОНАЖА === " << endl;
            cout << "1. Чарівник\n2. Лицар\n3. Ельф\n4. Троль\nВаш вибір: ";
            cin >> charChoice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << "Невірне введення!" << endl;
                break;
            }
            if (player != nullptr) {
                delete player;
                player = nullptr;
            }
            switch (charChoice) {
            case 1: player = new Wizard(); break;
            case 2: player = new Knight(); break;
            case 3: player = new Elf(); break;
            case 4: player = new Troll(); break;
            default:
                cout << "Ви стали Тролем." << endl;
                player = new Troll();
                break;
            }
            cout << "\n";
            player->display();
            break;
        }
        case 2: {
            if (player == nullptr) {
                cout << "\nСпочатку виберіть персонажа!" << endl;
                break;
            }
            int weaponChoice;
            cout << "\n === ВИБІР ЗБРОЇ === " << endl;
            cout << "1. Магічний посох (Чарівник) 2. Гримуар Таємниць (Чарівник)\n";
            cout << "3. Королівський меч (Лицар) 4. Важкий молот (Лицар)\n";
            cout << "5. Ельфійський лук (Ельф) 6. Парні кинджали (Ельф)\n";
            cout << "7. Величезна дубина (Троль) 8. Важкий валун (Троль)\n";
            cout << "Ваш вибір (1-8): ";
            cin >> weaponChoice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << "Невірне введення!" << endl;
                break;
            }
            Weapon* selectedWeapon = nullptr;
            switch (weaponChoice) {
            case 1: selectedWeapon = new WizardStaff(); break;
            case 2: selectedWeapon = new WizardGrimoire(); break;
            case 3: selectedWeapon = new KnightSword(); break;
            case 4: selectedWeapon = new KnightHammer(); break;
            case 5: selectedWeapon = new ElfBow(); break;
            case 6: selectedWeapon = new ElfDaggers(); break;
            case 7: selectedWeapon = new TrollClub(); break;
            case 8: selectedWeapon = new TrollBoulder(); break;
            default: break;
            }
            if (selectedWeapon != nullptr) {
                cout << "\n";
                if (!player->equipWeapon(selectedWeapon)) {
                    delete selectedWeapon;
                }
            }
            else {
                cout << "Невірний вибір зброї." << endl;
            }
            break;
        }
        case 3: {
            if (player == nullptr) {
                cout << "\nСпочатку виберіть персонажа!" << endl;
            }
            else {
                cout << "\n === АТАКА === " << endl;
                player->fight();
            }
            break;
        }
        case 4: {
            cout << "\nВихід з гри. До зустрічі!" << endl;
            running = false;
            break;
        }
        default:
            cout << "\nНевідома команда!" << endl;
            break;
        }
    }
    if (player != nullptr) {
        delete player;
    }
    return 0;
}