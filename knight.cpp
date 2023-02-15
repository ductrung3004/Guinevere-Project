#include "knight.h"

//Show Function ------------------------------------------------------------

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

//Process Function ------------------------------------------------------------

string anemy_name(int eventID){
    string name[8];
    name[1] = "MadBear";
    name[2] = "Bandit";
    name[3] = "LordLupin";
    name[4] = "Elf";
    name[5] = "Troll";
    name[6] = "Shaman";
    name[7] = "Siren Vajsh";
    return name[eventID];
    
}
int Eratosthenes(){
    int N = 1000;
    bool check[N + 1];
    for (int i = 2; i <= N; i++) {
        check[i] = true;
    }
    for (int i = 2; i <= N; i++) {
        if (check[i] == true) {
            for (int j = 2 * i; j <= N; j += i) {
                check[j] = false;
            }
        }
    }
}

int levelO(int event){
    int b = event % 10;
    int level = event > 6 ? (b > 5 ? b : 5) : b;
    return level;
}

double baseDamage(int event){
    double basedamage[6];
    basedamage[1] = 1.0;
    basedamage[2] = 1.5;
    basedamage[3] = 4.5;
    basedamage[4] = 7.5;
    basedamage[5] = 9.5;
    return basedamage[event];
}

int Combat_check(int & HP, int level, int levelO){
    if (level > levelO) 
        return 1;
    if (level == levelO)
        return 0;
    return -1;

}
void CombatMode(int & HP, int event){
    int damage = baseDamage(event) * levelO(event) * 10;
    HP -= damage;

}

int ShamanMode(int & smaller_mode, int & HP, int & remedy){
    if (smaller_mode != 0) return smaller_mode;
    if (HP < 5)
        HP = 1;
    else
        HP /= 5;
    
    if (remedy > 0) {
        remedy -= 1;
        HP *= 5;
        return smaller_mode;
    }
    
    return smaller_mode = 1; 
}
int ShamanMode_check(int & smaller_mode, int & HP){
    if (smaller_mode == 0) 
        return smaller_mode = 0;
    
    if (smaller_mode == 4) {
        HP *= 5;
        return smaller_mode = 0;
    }
    return smaller_mode += 1;
}

int VajshMode(int & frog_mode, int & level, int & maidenkiss, int & Prev_level){
    if (frog_mode != 0) 
        return frog_mode;
    
    if (maidenkiss > 0){
        maidenkiss -= 1;
        return frog_mode = 0;
    }
    Prev_level = level;
    level = 1;
    return frog_mode = 1;
}
int VajshMode_check(int & frog_mode, int & level, int Prev_level){
    if (frog_mode == 0) 
        return frog_mode = 0;
    if (frog_mode == 4) {
        level = Prev_level;
        return frog_mode = 0;
    }
    return frog_mode += 1;

}


//Main Function ------------------------------------------------------------
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    //Input Section ------------------------------------------------------------
    ifstream infile;
    infile.open(file_input);
    string HeroInfo, EventPeriod, otherfiles;
    rescue = -1;
    getline(infile, HeroInfo);
    istringstream inputHeroInfo(HeroInfo);

    inputHeroInfo >> HP >> level >> remedy >> maidenkiss >> phoenixdown;
    getline(infile, EventPeriod);
    istringstream inputEventID(EventPeriod);
    int EventID[100];
    int i = 1;
    int x;
    while (inputEventID >> x){
        EventID[i] = x;
        i++;

    }
    int EventElement = i - 1;
    getline(infile, otherfiles);
    for (int i = 0; i < otherfiles.size(); i++)
        if (otherfiles[i] == ',') otherfiles[i] = ' ';
    string mush_ghost, asclepius_pack, merlin_pack;
    istringstream inputOtherfiles(otherfiles);
    inputOtherfiles >> mush_ghost >> asclepius_pack >> merlin_pack;

    //Init Section ------------------------------------------------------------
    int maxHP = HP;
    

    //Process Section ------------------------------------------------------------
    int shaman_mode = 0;
    int vajsh_mode = 0;
    int Prev_level = level;
    bool lose_combat;
    for (static int event = 1; event <= EventElement; ++event){
        ShamanMode_check(shaman_mode, HP);
        VajshMode_check(vajsh_mode, level, Prev_level);
        if (EventID[event] <= 7){
            switch (Combat_check(HP, level, levelO(event))){
                case 1: 
                    level += 1;
                    if (EventID[event] > 5)
                        level++;
                    if (level > 10)
                        level = 10;
                    lose_combat = false;
                    break;
                case -1:
                    lose_combat = true;
                    break;
                case 0:
                    lose_combat = false;
                    break;
                
            }
            if (lose_combat){
                switch(EventID[event]){    
                    case 0:
                        rescue = 1;
                        break;
                    case 6:
                        ShamanMode(shaman_mode, HP, remedy);
                        break;
                    case 7:
                        VajshMode(vajsh_mode, level, maidenkiss, Prev_level);
                        break;
                    default:
                        CombatMode(HP, event);
                }
            }
        }
        if (HP <= 0){
            if (phoenixdown > 0){
                phoenixdown -= 1;
                HP = maxHP;
            }
            else{ 
                cout << "Mission Fail \n";
                break;
            }
        }
        if (event == EventElement && HP > 0){
            rescue = 1;
        }
        cout << "after combat with anemy in event " << event << ": "<< anemy_name(EventID[event])<< " (level:" << levelO(event) << ")" << "\n";
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        if (rescue == 1) {
            cout << "Mission complete \n";
            break;
        }
    }    


    //output Section ------------------------------------------------------------
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
}