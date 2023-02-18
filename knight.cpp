#include "knight.h"

//Show Function ------------------------------------------------------------

void display(/*ofstream & outfile,*/ int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    
    /*outfile*/cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

//Process Function ------------------------------------------------------------

// Prime checking----------------------------------------------------------
void Eratosthenes(bool* & check){
    int N = 1000;
    check = new bool[N + 1];
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
    return;
}
// Hero checking ---------------------------------------------------
bool Arthur_check(int HP){
    if (HP == 999)
        return true;
    return false;

}

bool Lancelot_check(int HP, bool* Prime){
    if (Prime[HP])
        return true;
    return false;
}

//Anemies Checking-----------------------------------------------------
int levelO(int event){
    int b = event % 10;
    int level = event > 6 ? (b > 5 ? b : 5) : b;
    return level;
}

string anemy_name(int eventID){
    string name[100];

    name[1] = "MadBear";
    name[2] = "Bandit";
    name[3] = "LordLupin";
    name[4] = "Elf";
    name[5] = "Troll";
    name[6] = "Shaman";
    name[7] = "Siren Vajsh";
    name[11] = "MushMario";
    name[12] = "MushFibo";
    name[13] = "Remedy";
    name[14] = "Maidenkiss";
    name[15] = "PhoenixDown";
    name[18] = "Merlin";
    name[19] = "Asclepius";
    name[99] = "Bowser";
    
    if (eventID < 100)
        return name[eventID];
    else
        return  "MushGhost";  
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

//case 1->5 ---------------------------------------------------------------------
int Combat_check(int & HP, int level, int levelO){
    if (level > levelO) 
        return 1;
    if (level == levelO)
        return 0;
    
    return -1;
}

void CombatMode(int & HP,int eventID, int event){
    int damage = baseDamage(eventID) * levelO(event) * 10;
    HP -= damage;
}

//case 6 (Shaman)--------------------------------------------------------------------------------------------

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

int ShamanMode_check(int & smaller_mode, int & HP, int maxHP, int remedy){
    if (smaller_mode == 0) 
        return smaller_mode = 0;
    
    if (smaller_mode == 4 || remedy > 0) {
        HP = min(HP*5, maxHP);
        return smaller_mode = 0;
    }
    return smaller_mode += 1;
}

//case 7 (Siren Vajsh)--------------------------------------------------------------------------------------------

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

int VajshMode_check(int & frog_mode, int & level, int Prev_level, int maidenkiss){
   
   if (frog_mode == 0) 
        return frog_mode = 0;
    if (frog_mode == 4 || maidenkiss > 0) {
        level = Prev_level;
        return frog_mode = 0;
    }

    return frog_mode += 1;
}

//case 11 (Mush Mario)--------------------------------------------------------------------------------------------

int SumofOdd(int n){
    int odd = 99;
    int res = 0;
    
    for (int i = 0; i < n; ++i){
        res += (odd - 2*i);
    }
    
    return res;
}
void MushMario(int & HP, int level, int phoenixdown, bool* Prime){
    int n = (((level + phoenixdown) % 5) + 1) * 3;
    
    HP += (SumofOdd(n) % 100);
    while (Prime[HP] == false)
        HP++;
    
    return;
}

//case 12 (Mush Fibo)--------------------------------------------------------------------------------------------
int Fibonacci(int n){
    int fibo[15];
    
    fibo[13] = 610;
    fibo[14] = 987;
    
    int i = 14;
    
    for (; fibo[i] >= n; i--)
        fibo[i - 2] = fibo[i] - fibo[i - 1];
    
    return fibo[i];
}

void MushFibo(int & HP){
    
    if (HP > 1)
        HP = Fibonacci(HP);
    
    return;
}

//case 13 (Mush Ghost)--------------------------------------------------------------------------------------------

//read file function ---------
int* ReadMushGhostFile(string mushghost_input, int & length){
    ifstream mushghost_inp;
    string nln;
    int* mushghost_arr;
    
    mushghost_inp.open(mushghost_input);
    getline (mushghost_inp, nln);
    istringstream str(nln);
    
    str >> length;
    
    string line;
    
    getline (mushghost_inp, line);
    for (int i = 0; i < line.size(); ++i)
        if (line[i] == ',') 
            line[i] = ' ';
    
    istringstream str2(line);
    
    mushghost_arr = new int [length];
    int i = 0;
    int x;
    while (str2 >> x){
        mushghost_arr[i] = x;
        i++;
    }    
    mushghost_inp.close();
    return mushghost_arr;
}
//affectID = 1 -------
int affect1(int* array, int length){
    int index_max, index_min;
    int maxi = array[length - 1];
    int mini = array[length - 1];
    index_max = length - 1;
    index_min = length - 1;
    for (int i = length - 2; i >= 0 ; i--){
        if (maxi < array[i]){
            index_max = i;
            maxi = array[i];
        }
        if (mini > array[i]){
            index_min = i;
            mini = array[i];
        }
    }
    return index_max + index_min; 
}

//affectID = 2 -----------
int affect2(int* array, int length){
    int mtx;
    int mti; 
    for (int i = 1; i < length; i++){
        if (array[i] > array[i - 1]){
            mtx = array[i];
            mti = i;
        }
        else
            break;
    }
    for (int i = mti + 1; i < length; i++){
        if (array[i] < array[i - 1])
            continue;
        else
            return -5;
    }
    return mtx + mti;
}
//affectID = 3, 4----------------
int* Math_function(int* array, int length){
    int* tmp_array = new int[length];
    for (int i = 0; i < length; i++){
        if (array[i] < 0) 
            tmp_array[i] = array[i]* (-1);
        tmp_array[i] = (17 * array[i] + 9) % 257;
    
    }
    for (int i = 0; i < length; i++){
    }
    return tmp_array;
}

//affectID = 3 --------
int affect3(int* array, int length){
    int* tmp_array = Math_function(array, length);
    int index_max, index_min;
    int maxi = tmp_array[0];
    int mini = tmp_array[0];
    index_max = 0;
    index_min = 0;
    for (int i = 0; i < length ; i++){
        if (maxi < tmp_array[i]){
            index_max = i;
            maxi = tmp_array[i];
        }
        if (mini > tmp_array[i]){
            index_min = i;
            mini = tmp_array[i];
        }
    }
    return index_max + index_min;
}

//afectID = 4------------

int MiddleOfThree(int a, int b, int c){
    if(a == b && a == c)
        return -12;
    if ((b < a && a <= c) || (c < a && a <= b))
        return a;
    if ((a < b && b <= c) || (c < b && b < a))
        return b + 1;
    return c + 2;

}
int affect4(int* array, int length){
    int* tmp_array = Math_function(array, length);
    int res = MiddleOfThree(tmp_array[0], tmp_array[1], tmp_array[2]);
    return res;
}

//main case function --------
void mushghost_affect(int & HP, char affectID, int* array, int length){
    int HP_change;
    switch (affectID){
        case '1':
            HP_change = affect1(array, length);
            HP -= HP_change;
            break;
        case '2':
            HP_change = affect2(array, length);
            HP -= HP_change;
            break;
        case '3':
            HP_change = affect3(array, length);
            HP -= HP_change;
            break;
        case '4':
            HP_change = affect4(array, length);
            HP -= HP_change; 
            break;
    }
    
    return;
}


//case 18--------------------------------------------------------------------------------------------
int BonusHP_check(string name){
    if (name.find("Merlin") != string::npos || name.find("merlin") != string::npos)
        return 3;
    char merlin[6];
    merlin[0] = 'm';
    merlin[1] = 'e';
    merlin[2] = 'r';
    merlin[3] = 'l';
    merlin[4] = 'i';
    merlin[5] = 'n';
    
    char MERLIN[6];
    MERLIN[0] = 'M';
    MERLIN[1] = 'E';
    MERLIN[2] = 'R';
    MERLIN[3] = 'L';
    MERLIN[4] = 'I';
    MERLIN[5] = 'N';
    
    for (int i = 0 ; i < 6; ++i)
        if (name.find(merlin[i]) == string::npos && name.find(MERLIN[i]) == string::npos)
            return 0;
    return 2;
}
// read file function AND main case function ------------
void ReadMerlinFile(string merlin_input, int & HP){
    ifstream merlin_inp;
    merlin_inp.open(merlin_input);
    string nln;
    getline(merlin_inp, nln);
    istringstream nst(nln);
    int n ;
    nst >> n;
    string line;

    for (int i = 0; i < n; ++i){
        getline (merlin_inp, line);
        HP += BonusHP_check(line);
    }

    merlin_inp.close();
    return;
}
//case 19 (A)--------------------------------------------------------------------------------------------

// read file function -----------
int** ReadAsclepiusFile(string asclepius_input, int & rows, int & cols){
    int** matrix;
    ifstream asclepius_inp;
    string rowsline, colsline;
    
    asclepius_inp.open(asclepius_input);
    getline(asclepius_inp, rowsline);
    istringstream rowl(rowsline);
    rowl >> rows;
    getline(asclepius_inp, colsline);
    istringstream coll(colsline);
    coll >> cols;
    matrix = new int*[rows];
    for (int row = 0; row < rows; ++row){
        string line;
        getline(asclepius_inp, line);
        istringstream str(line);
        int x;
        int col = 0;
        matrix[row] = new int[cols];
        while(str >> x){
            matrix[row][col] = x;
            col += 1;
        }
    }
    asclepius_inp.close();
    return matrix;
}

// main case function ------------
void PickUp(int** matrix, int rows, int cols, int & remedy, int & maidenkiss, int & phoenixdown){
    for (int r = 0; r < rows; r++){
        int medicines_pickup = 0;
        for (int c = 0; c < cols; c++){
            switch (matrix[r][c]){
                case 15:
                    remedy++;
                    medicines_pickup++;
                    break;
                case 16:
                    maidenkiss++;
                    medicines_pickup++;
                    break;
                case 17:
                    phoenixdown++;
                    medicines_pickup++;
                    break;
            }
            if (medicines_pickup == 3) break;
        }
}

}
//Main Function ------------------------------------------------------------
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    //Input Section ------------------------------------------------------------
    ifstream infile;
    infile.open(file_input);
    //string file_output("tc1_output");
    //ofstream outfile;
    //outfile.open(file_output);
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
    infile.close();
    //Init Section ------------------------------------------------------------
    int maxHP = HP;
    int shaman_mode = 0;
    int vajsh_mode = 0;
    int Prev_level;
    bool lose_combat;
    bool Asclepius_meet_check = false;
    bool Merlin_meet_check = false;
    bool BowserCombat = true;
    bool* Prime_array;
    Eratosthenes(Prime_array);
    bool Lancelot = Lancelot_check(maxHP, Prime_array);
    bool Arthur = Arthur_check(maxHP);
    //Process Section ------------------------------------------------------------
    for (static int event = 1; event <= EventElement; ++event){
        if (EventID[event] == 0 || Arthur){
            rescue = 1;
            break;
        }
        //outfile << "during combat with anemy in event " << event << ": "<< anemy_name(EventID[event])<< " (level:" << levelO(event) << ")" << "\n";
        //outfile << "before combat: \n";
        //display(/*outfile,*/ HP, level, remedy, maidenkiss, phoenixdown, rescue);
        if (EventID[event] <= 7){
            if (Lancelot){
                level += 1;
                if (EventID[event] > 5)
                    level++;
                if (level > 10)
                    level = 10;
                lose_combat = false;
            }
            else
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
                        if (shaman_mode == 0 && vajsh_mode == 0)
                            ShamanMode(shaman_mode, HP, remedy);
                        break;
                    case 7:
                        if (shaman_mode == 0 && vajsh_mode == 0)
                            VajshMode(vajsh_mode, level, maidenkiss, Prev_level);
                        break;
                    default:
                        CombatMode(HP, EventID[event], event);
                }
            }
        }
        else
            switch(EventID[event]){
                case 11:
                    MushMario(HP, level, phoenixdown, Prime_array);
                    HP = min (maxHP, HP);
                    //outfile << "Mush Mario affected HP: " << HP << endl;
                    break;
                case 12:
                    MushFibo(HP);
                    //outfile << "Mush Fibo affected HP: " << HP << endl;
                    break;
                case 15:
                    remedy = min(remedy+1, 99);
                    break;
                case 16:
                    maidenkiss = min(maidenkiss + 1, 99);
                    break;
                case 17:
                    phoenixdown = min(phoenixdown + 1, 99);
                    break;
                case 18:
                    if (Merlin_meet_check)
                        break;
                    Merlin_meet_check = true;
                    ReadMerlinFile(merlin_pack, HP);
                    HP = min(HP, maxHP);
                    break;
                case 19:
                    if (Asclepius_meet_check) 
                        break;
                    int rows, cols;
                    Asclepius_meet_check = true;
                    int** matrix;
                    matrix = ReadAsclepiusFile(asclepius_pack, rows, cols);
                    PickUp(matrix, rows, cols, remedy, maidenkiss, phoenixdown);
                    break;
                case 99:
                    if ((Lancelot && level >= 8) || (level == 10)){
                        level = 10;
                        BowserCombat = true;
                    }
                    else {
                        rescue = 0;
                        BowserCombat = false;
                    }
                    break;
                default:
                    if (EventID[event] > 99){
                        stringstream ss;
                        ss << EventID[event];
                        string id_affect = ss.str();
                        int mushghost_length;
                        int* mushghost_array = new int[mushghost_length];
                        mushghost_array = ReadMushGhostFile(mush_ghost, mushghost_length);
                        for (int i = 2; i < id_affect.length(); ++i){
                            mushghost_affect(HP, id_affect[i], mushghost_array, mushghost_length);
                        }
                    }
            }
        if (BowserCombat == false) {
            rescue = 0;
            break;
        }
        if (HP <= 0){
            if (phoenixdown > 0){
                phoenixdown -= 1;
                HP = maxHP;
                shaman_mode = 0;
                vajsh_mode = 0;
            }
            else {
                rescue = 0;
                break;
            }
        }
        
        /*outfile << "after combat: \n";
        if (shaman_mode == 1)
            outfile << "shaman_mode enable\n";
        if (vajsh_mode == 1)
            outfile << "vajsh_mode enable\n";
        if (shaman_mode == 4)
            outfile << "shaman_mode disable\n";
        if (vajsh_mode == 4)
            outfile << "vajsh_mode disable\n";*/
        ShamanMode_check(shaman_mode, HP, maxHP, remedy);
        VajshMode_check(vajsh_mode, level, Prev_level, maidenkiss);
        display(/*outfile,*/ HP, level, remedy, maidenkiss, phoenixdown, rescue);
        //outfile << "\n";
        
        if (event == EventElement){
            rescue = 1;
        }
    }    
    /*if (rescue == 1)
        outfile << "Mission complete \n";
    else 
        outfile << "Mission Fail \n";*/
    
    //output Section ------------------------------------------------------------
    //display(/*outfile*/, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    //outfile.close();
}