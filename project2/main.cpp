// Project Identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
//  main.cpp
//  project2
//
//  Created by Kai Yamasaki on 2/8/23.
//
#include "P2random.h"
#include <iostream>
#include <getopt.h>
#include <queue>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

//ADDED THIS FROM xcode_redirect.hpp file on canvas
#include <cstdio>
// REQUIRES: argc & argv from main(), and optind from getopt.h
// MODIFIES: optind is incremented until it equals argc
// EFFECTS:
//     Looks for extra arguments after getopt() finishes reading options.
//     It replaces simple shell functionality by using freopen() to change
//     stdin (from < infilename) and stdout (from > outfilename).
inline void xcode_redirect(int argc, char **argv, int optind = 1) {
    while (optind < argc) {
        switch (*argv[optind]) {
            case '<':  // redirect input
                if (!freopen(argv[++optind], "r", stdin)) {
                    std::cerr << "Unable to open input file: " << argv[optind] <<
std::endl;
                    exit(1);
                }
                break;
            case '>':  // redirect output
                if (!freopen(argv[++optind], "w", stdout)) {
                    std::cerr << "Unable to open output file: " << argv[optind] <<
std::endl;
                    exit(1);
                }
                break;
        }  // switch
        ++optind;
    }  // while
}  // xcode_redirect()


//TODO: Need to change this to accept multiple command types, ex. can have v and m at the same time
void getMode(int argc, char * argv[], vector<char> &command) {
  // These are used with getopt_long()
  opterr = false; // Let us handle all error output for command line options
  int choice;
  int index = 0;
  option long_options[] = {
    // DONE: Fill in two lines, for the "mode" ('m') and
    // the "help" ('h') options.
    // ./project0 --mode nosize
    // ./project0 --help          //third argument always nullptr, cuz feature not used
      { "verbose", no_argument, nullptr, 'v' } ,
      { "median", no_argument, nullptr, 'm'} ,
      { "general-eval", no_argument, nullptr, 'g'} ,
      { "watcher", no_argument , nullptr, 'w'} ,
    { nullptr, 0, nullptr, '\0' },
  };  // long_options[]

  // TODO: Fill in the double quotes, to match the mode and help options.
  while ((choice = getopt_long(argc, argv, "vmgw", long_options, &index)) != -1) {
      // : means m is followed by an argument, while h has no argument
    switch (choice) {
        case 'v':
            command.push_back('v');
            break;

        case 'm': {  // Need a block here to declare a variable inside a case
            command.push_back('m');
            break;
        }
        case 'g': {  // Need a block here to declare a variable inside a case
            command.push_back('g');
            break;

          break;
        }  // case 'm'
        case 'w': {
            command.push_back('w');
            break;
        }
      //default:
        //cerr << "Error: invalid option" << endl;
        //exit(1);
    }  // switch ..choice
  }  // while
}









//START OF ACTUAL UNIQUE CODE
/*
class Fight{
public:
    Fight(): timestamp(0), troopsLost(0){}
    Fight(uint32_t time, uint32_t lost) : timestamp(time), troopsLost(lost) {}
    
    uint32_t getTime() const {
        return timestamp;
    }
    
private:
 
    uint32_t timestamp;
    
    
};
 */
 



class Battalion {
public:
    Battalion(uint32_t stamp, uint32_t gen, uint32_t plan, char t, uint32_t f, uint32_t num, uint32_t ID)
    : tstamp(stamp), genID(gen), planID(plan), team(t), force(f), numTroop(num), boo(ID) {}
    
    uint32_t getID() const {
        return boo;
    }
    
    uint32_t getGen() const {
        return genID;
    }
    uint32_t getPlan() const {
        return planID;
    }
    char getTeam() const {
        return team;
    }
    uint32_t getForce() const {
        return force;
    }
    uint32_t getStamp() const {
        return tstamp;
    }
    
    uint32_t getNum() const {
        return numTroop;
    }
    void lostTroop(const uint32_t x) {
        /*
        if (x > numTroop) {
            cerr << "tried to reduce by too much, bug" << endl;
            exit(1);
        }
         */
        
        numTroop = numTroop - x;
        return;
    }
    
   
private:
    uint32_t tstamp;
    uint32_t genID;
    uint32_t planID;
    char team;
    uint32_t force;
    uint32_t numTroop;
    uint32_t boo;
};

class Attack { //if bool is true, attack, if false its an ambush
public:
    Attack() : blank(true), type(false), time1(0), time2(0), difference(0) {}
    //Attack(uint32_t at, uint32_t t, bool here) : type(here), time(t), difference(at), time1(0), time2(0) {}
    
    void setAmbush(const uint32_t one, const uint32_t two, uint32_t diff) {
        blank = false;
        type = false;
        time1 = one;
        time2 = two;
        difference = diff; 
    }
    void setAttack(const uint32_t one, const uint32_t two, uint32_t diff) {
        blank = false;
        type = true;
        time1 = one;
        time2 = two;
        difference = diff;
    }
    
    uint32_t getDiff() const {
        return difference;
    }
    
    bool getBlank() const {
        return blank;
    }
    
    uint32_t getT1() const {
        return time1;
    }
    uint32_t getT2() const {
        return time2;
    }
private:
    bool blank;
    bool type;
    uint32_t time1;
    uint32_t time2;
    uint32_t difference;
};

class State {
public:
    State() : nowT(0), nowM(0), TbestJedi(numeric_limits<uint32_t>::max()), TbestSith(0), MbestJedi(numeric_limits<uint32_t>::max()),
      TmaybeT(numeric_limits<uint32_t>::max()), MbestSith(0), MmaybeS(0) {}
    
    /*
    if (in.getTeam() == 'J' && in.getStamp() == 653 && in.getPlan() == 1 && in.getForce() < 5) {
        int x = 0;
    }
    if (in.getTeam() == 'S' && in.getStamp() == 3 && in.getPlan() == 4 && in.getForce() > 95) {
        int x = 0;
    }
    if (in.getTeam() == 'S' && in.getStamp() == 64 && in.getPlan() == 4 && in.getForce() > 95) {
        int x = 0;
    }
    
    
    if (in.getTeam() == 'S' && in.getStamp() == 0 && in.getPlan() == 8 && in.getForce() == 13) {
        int x = 0;
    }
    */
    
    /*
    if (in.getTeam() == 'J' && in.getStamp() == 3 && in.getPlan() == 0 && in.getForce() == 10) {
        int x = 0;
    }
     */
    /*
    void check(Battalion &in) {
        
        if (now == 0) {
                    if (in.getTeam() == 'J') {
                             //seenJedi(in.getForce());
                             now = 1;
                             TbestJedi = in.getForce();
                             MbestJedi = in.getForce();
                             TJediTime = in.getStamp();
                             MJediTime = in.getStamp();
                         }
                         else {
                             //bestSith = in.getForce();
                             //SithTime = in.getStamp();
                             MbestSith = in.getForce();
                             //TbestSith = in.getForce();  previously had these in, j took em out
                             //TSithTime = in.getStamp();
                             MSithTime = in.getStamp();
                             now = 2;
                             status = 'S';
                         }
                     }
        else if (now == 2) {
                         if (in.getTeam() == 'J') {
                             MJediTime = in.getStamp();
                             TJediTime = in.getStamp();
                             MbestJedi = in.getForce();
                             TbestJedi = in.getForce();
                             //bestJedi = in.getForce();
                             //JediTime = in.getStamp();
                             now = 3;
                             if (MbestJedi <= MbestSith) {
                                 bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                             }
                             
                         }
                         else {
                             if (in.getForce() > MbestSith)  {
                                 MbestSith = in.getForce();
                                 MSithTime = in.getStamp();
                             }
                         }
                     }
    else if (now == 1) {
                         if (in.getTeam() == 'J') {
                             if (in.getForce() < MbestJedi) {
                                 MJediTime = in.getStamp();
                                 MbestJedi = in.getForce();
                             }
                             if (in.getForce() < TbestJedi) {
                                 TJediTime = in.getStamp();
                                 TbestJedi = in.getForce();
                             }
                         }
                         else {
                             TSithTime = in.getStamp();
                             TbestSith = in.getForce();
                             if (TbestSith >= TbestJedi) {
                                
                                 MSithTime = in.getStamp();
                                 MbestSith = in.getForce();
                                 bestAttack.setAttack(TJediTime, TSithTime, (TbestSith - TbestJedi));
                             }
                             now = 3;
                         }
                     }
    else if (now == 3) {
                         if (in.getTeam() == 'S' && in.getForce() > TbestSith) {
                             TSithTime = in.getStamp();
                             TbestSith = in.getForce();
                             //TODO: MABE COMMENT THESE BACK IN
                             //MSithTime = in.getStamp();
                             //MbestSith = in.getForce();
                             MmaybeS = in.getForce();
                             MmaybeT = in.getStamp();
                             status = 's';
                             
                             
                             if (TbestJedi <= TbestSith) {
                                 if (bestAttack.getBlank()) {
                                     bestAttack.setAttack(TJediTime, TSithTime, (TbestSith -TbestJedi));
                                 }
                                 else if (TbestSith - TbestJedi > bestAttack.getDiff()) {
                                     bestAttack.setAttack(TJediTime, TSithTime, (TbestSith -TbestJedi));
                                 }
                             }
                             
                             
                         }
                         else if (in.getTeam() == 'J' && in.getForce() <= MbestJedi) {
                             uint32_t value = MbestSith - in.getForce();
                          
                             if (bestAmbush.getBlank() && MbestSith > in.getForce()) {
                                 MJediTime = in.getStamp();
                                 MbestJedi = in.getForce();
                                
                                 bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                             }
                             //added this bestAmbush.getBLank()
                             else if (!bestAmbush.getBlank() && (MbestSith > in.getForce() && bestAmbush.getDiff() < value)) {
                                 //TODO: THIS IS NEW CHANGE
                                 if (MbestJedi > in.getForce()) {
                                     MJediTime = in.getStamp();
                                     MbestJedi = in.getForce();
                                 }
                                 //MJediTime = in.getStamp();
                                 //MbestJedi = in.getForce();
                                 TbestJedi = in.getForce();
                                 TJediTime = in.getStamp();
                                 bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                                 //above was previous, now trying with TbestSith isntead?
                                 if (status == 'S') {
                                     //MbestSith = TbestSith;
                                     //MSithTime = TSithTime;
                                     //TODO: TEMPORARILY CHANGES THIS TO M FROM T, weird errors!
                                     bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                                 }
                             }
                             if (in.getForce() < TbestJedi) {
                                 TmaybeJ = in.getForce();
                                 TmaybeT = in.getStamp();
                                 now = 4;
                             }
                             
                         }
                         else if (in.getTeam() == 'S' && in.getForce() == TbestSith) {
                             TSithTime = in.getStamp();
                             TbestSith = in.getForce();
                             if (!bestAttack.getBlank() && (TbestSith - TbestJedi > bestAttack.getDiff() && TbestJedi <= TbestSith)) {
                                 bestAttack.setAttack(TJediTime, TSithTime, (TbestSith -TbestJedi));
                             }
                         }
                         //TODO: RELOCATED THIS HERE
                         if (now == 3 && status == 's') {
                             if (in.getTeam() == 'J' && in.getForce() < MmaybeS) {
                                 if (in.getForce() <= MmaybeS) { //just added this from piazza
                                     if (!bestAmbush.getBlank() && MmaybeS - in.getForce() > bestAmbush.getDiff()) {
                                         MSithTime = MmaybeT;
                                         MbestSith = MmaybeS;
                                         
        
                                         MbestJedi = in.getForce();
                                         MJediTime = in.getStamp();
                                         bestAmbush.setAmbush(MSithTime, MJediTime, MmaybeS - in.getForce());
                                         //now = "Seen Both";
                                         status = '0';
                                     }
                                 }
                             }
                             else if (in.getTeam() == 'S' && in.getForce() > MmaybeS) {
                                 MmaybeS = in.getForce();
                                 MmaybeT = in.getStamp();
                             }
                         }
                     }
    else if (now == 4) {
                         if (in.getTeam() == 'J' && in.getForce() < TmaybeJ){
                             TmaybeJ = in.getForce();
                             TmaybeT = in.getStamp();
                             if (!bestAmbush.getBlank() && TmaybeJ - MbestSith > bestAmbush.getDiff()) {
                                 MJediTime = TmaybeT;
                                 MbestJedi = TmaybeJ;
                                 bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                             }
                         }
                         else if (in.getTeam() == 'S') {
                             if (in.getForce() >= TbestSith) {
                                 if (in.getForce() >= TmaybeJ) { //just added this from piazza
                                     uint32_t newDiff = in.getForce() - TmaybeJ;
                                     if (bestAttack.getBlank()) {
                                         TbestJedi = TmaybeJ;
                                         TJediTime = TmaybeT;
                                         TbestSith = in.getForce();
                                         TSithTime = in.getStamp();
                                         //TODO: just added these, remove if no progress
                                         MbestSith = in.getForce();
                                         MSithTime = in.getStamp();
                                         now = 3;
                                         bestAttack.setAttack(TJediTime, TSithTime, (TbestSith - TbestJedi));
                                     }
                                     else if (!bestAttack.getBlank() && newDiff > bestAttack.getDiff()) {
                                         TbestJedi = TmaybeJ;
                                         TJediTime = TmaybeT;
                                         TbestSith = in.getForce();
                                         TSithTime = in.getStamp();
                                         //TODO: just added these, remove if no progress
                                         if (in.getForce() != MbestSith) {
                                             if (in.getForce() > MbestSith) {
                                                 MbestSith = in.getForce();
                                                 MSithTime = in.getStamp();
                                             }
                                         }
                                         
                                         now = 3;
                                         bestAttack.setAttack(TJediTime, TSithTime, (TbestSith - TbestJedi));
                                     }
                                 }
           
                             }
                         }
                     }

                 }
     */
    
    
    void tackCheck(Battalion &in) {
        char team = in.getTeam();
        uint32_t stamp = in.getStamp();
        uint32_t force = in.getForce();
    if (nowT == 0) {
                    if (team == 'J') {
                             //seenJedi(in.getForce());
                             nowT = 1;
                        TbestJedi = force;
                             
                        TJediTime = stamp;
                            
                         }
                     }
    else if (nowT == 1) {
                         if (team == 'J') {
                             if (force < TbestJedi) {
                                 TJediTime = stamp;
                                 TbestJedi = force;
                             }
                         }
                         else {
                             TSithTime = stamp;
                             TbestSith = force;
                             if (TbestSith >= TbestJedi) {
                                
                                 bestAttack.setAttack(TJediTime, TSithTime, (TbestSith - TbestJedi));
                             }
                             nowT = 3;
                         }
                     }
    
        
    else if (nowT == 3) {
                         if (team == 'S' && force > TbestSith) {
                             TSithTime = stamp;
                             TbestSith = force;
                             //TODO: MABE COMMENT THESE BACK IN
                             //MSithTime = in.getStamp();
                             //MbestSith = in.getForce();

                             //status = 's';
                             
                             
                             if (TbestJedi <= TbestSith) {
                                 if (bestAttack.getBlank()) {
                                     bestAttack.setAttack(TJediTime, TSithTime, (TbestSith -TbestJedi));
                                 }
                                 else if (TbestSith - TbestJedi > bestAttack.getDiff()) {
                                     bestAttack.setAttack(TJediTime, TSithTime, (TbestSith -TbestJedi));
                                 }
                             }
                             
                             
                         }
                         else if (team == 'J' && force <= TbestJedi) {
                             //unsure what to do with list, i think it should be no = ?
                             if (force < TbestJedi) {
                                 TmaybeJ = force;
                                 TmaybeT = stamp;
                                 nowT = 4;
                             }
                             
                         }
                         else if (team == 'S' && force == TbestSith) {
                             TSithTime = stamp;
                             TbestSith = force;
                             if (!bestAttack.getBlank() && (TbestSith - TbestJedi > bestAttack.getDiff() && TbestJedi <= TbestSith)) {
                                 bestAttack.setAttack(TJediTime, TSithTime, (TbestSith -TbestJedi));
                             }
                         }
                         
    }
    else if (nowT == 4) {
                         if (team == 'J' && force < TmaybeJ){
                             TmaybeJ = force;
                             TmaybeT = stamp;
                         }
                         else if (team == 'S') {
                             
                                 if (force >= TmaybeJ) { //just added this from piazza
                                     uint32_t newDiff = force - TmaybeJ;
                                     if (bestAttack.getBlank()) {
                                         TbestJedi = TmaybeJ;
                                         TJediTime = TmaybeT;
                                         TbestSith = force;
                                         TSithTime = stamp;
                                         //TODO: just added these, remove if no progress
                                         nowT = 3;
                                         bestAttack.setAttack(TJediTime, TSithTime, (TbestSith - TbestJedi));
                                     }
                                     else if (!bestAttack.getBlank() && newDiff > bestAttack.getDiff()) {
                                         TbestJedi = TmaybeJ;
                                         TJediTime = TmaybeT;
                                         TbestSith = force;
                                         TSithTime = stamp;
                                         //TODO: just added these, remove if no progress
                                         
                                         nowT = 3;
                                         bestAttack.setAttack(TJediTime, TSithTime, (TbestSith - TbestJedi));
                                     }
                                 }
           
                             }
                         }
    }
    
     
    
    void BushCheck(Battalion &in) {
        char team = in.getTeam();
        uint32_t stamp = in.getStamp();
        uint32_t force = in.getForce();
        
        if (nowM == 0) {
                    if (team == 'S') {
                             //bestSith = in.getForce();
                             //SithTime = in.getStamp();
                        MbestSith = force;
                             //TbestSith = in.getForce();  previously had these in, j took em out
                             //TSithTime = in.getStamp();
                        MSithTime = stamp;
                             nowM = 2;
                             status = 'S';
                         }
                     }
        else if (nowM == 2) {
                         if (team == 'J') {
                             MJediTime = stamp;
                             //TJediTime = in.getStamp();
                             MbestJedi = force;
                             //TbestJedi = in.getForce();
                             //bestJedi = in.getForce();
                             //JediTime = in.getStamp();
                             nowM = 3;
                             if (MbestJedi <= MbestSith) {
                                 bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                             }
                             
                         }
                         else {
                             if (force > MbestSith)  {
                                 MbestSith = force;
                                 MSithTime = stamp;
                             }
                         }
                     }

    else if (nowM == 3) {
                         if (team == 'S' && force > MbestSith) {
                             
                            
                             MmaybeS = force;
                             MmaybeT = stamp;
                             //status = 's';
                             nowM = 4;
                             
                             
                         }
                         else if (team == 'J' && force <= MbestJedi) {
                             uint32_t value = MbestSith - force;
                          
                             if (bestAmbush.getBlank() && MbestSith >= force) {
                                 MJediTime = stamp;
                                 MbestJedi = force;
                                
                                 bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                             }
                             //added this bestAmbush.getBLank()
                             else if (!bestAmbush.getBlank() && (MbestSith > force && bestAmbush.getDiff() < value)) {
                                 //TODO: THIS IS NEW CHANGE
                                 if (MbestJedi > force) {
                                     MJediTime = stamp;
                                     MbestJedi = force;
                                 }
                                 //MJediTime = in.getStamp();
                                 //MbestJedi = in.getForce();
                                 
                                 bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                                 //above was previous, now trying with TbestSith isntead?
                             }
                             
                         }
                
                         //TODO: RELOCATED THIS HERE
                    
                     }
        else if (nowM == 4 /*&& status == 's'*/) {

            if (team == 'J' && force <= MmaybeS) {
                    
                    if (!bestAmbush.getBlank() && MmaybeS - force > bestAmbush.getDiff()) {
                        if (MbestSith < MmaybeS) {
                            MSithTime = MmaybeT;
                            MbestSith = MmaybeS;
                            
                            
                            
                            MbestJedi = force;
                            MJediTime = stamp;
                            bestAmbush.setAmbush(MmaybeT, MJediTime, MmaybeS - force);
                            //now = "Seen Both";
                            status = '0';
                            nowM = 3;
                             
                        }
                        else if (MbestSith > MmaybeS) {
                            
                            MbestJedi = force;
                            MJediTime = stamp;
                            bestAmbush.setAmbush(MmaybeT, MJediTime, MmaybeS - force);
                            //now = "Seen Both";
                            status = '0';
                            nowM = 3;
                        }
                        else {
                        //TODO: below was original, above is the "fix"
                        //MSithTime = MmaybeT;
                        //MbestSith = MmaybeS;
                        

                            
                            
                            
                            
                            MbestJedi = force;
                            MJediTime = stamp;
                            bestAmbush.setAmbush(MSithTime, MJediTime, MbestSith - force);
                            //now = "Seen Both";
                            status = '0';
                            nowM = 3;
                        }
                    
                }
                else if (bestAmbush.getBlank()) {
                    MbestSith = MmaybeS;
                    MSithTime = MmaybeT;
                    MbestJedi = force;
                    MJediTime = stamp;
                    
                    bestAmbush.setAmbush(MmaybeT, MJediTime, MmaybeS - force);
                    status = '0';
                    nowM = 3;
                }
            }
            else if (team == 'S' && force > MmaybeS) {
                MmaybeS = force;
                MmaybeT = stamp;
            }
        }
        
        
        
        
        
        
        /*
        
    else if (now == 4) {
                         if (in.getTeam() == 'J' && in.getForce() < TmaybeJ){
                             TmaybeJ = in.getForce();
                             TmaybeT = in.getStamp();
                             if (!bestAmbush.getBlank() && TmaybeJ - MbestSith > bestAmbush.getDiff()) {
                                 MJediTime = TmaybeT;
                                 MbestJedi = TmaybeJ;
                                 bestAmbush.setAmbush(MSithTime, MJediTime, (MbestSith - MbestJedi));
                             }
                         }
                         else if (in.getTeam() == 'S') {
                             if (in.getForce() >= TbestSith) {
                                 if (in.getForce() >= TmaybeJ) { //just added this from piazza
                                     uint32_t newDiff = in.getForce() - TmaybeJ;
                                     if (bestAttack.getBlank()) {
                                         TbestJedi = TmaybeJ;
                                         TJediTime = TmaybeT;
                                         TbestSith = in.getForce();
                                         TSithTime = in.getStamp();
                                         //TODO: just added these, remove if no progress
                                         MbestSith = in.getForce();
                                         MSithTime = in.getStamp();
                                         now = 3;
                                         bestAttack.setAttack(TJediTime, TSithTime, (TbestSith - TbestJedi));
                                     }
                                     else if (!bestAttack.getBlank() && newDiff > bestAttack.getDiff()) {
                                         TbestJedi = TmaybeJ;
                                         TJediTime = TmaybeT;
                                         TbestSith = in.getForce();
                                         TSithTime = in.getStamp();
                                         //TODO: just added these, remove if no progress
                                         if (in.getForce() != MbestSith) {
                                             if (in.getForce() > MbestSith) {
                                                 MbestSith = in.getForce();
                                                 MSithTime = in.getStamp();
                                             }
                                         }
                                         
                                         now = 3;
                                         bestAttack.setAttack(TJediTime, TSithTime, (TbestSith - TbestJedi));
                                     }
                                 }
           
                             }
                         }
                     }
         */
    }
    
         
    
    
           
            


   
    
    Attack getAttack() const {
        return bestAttack;
    }
    Attack getAmbush() const {
        return bestAmbush;
    }
    
private:
    Attack bestAmbush;
    Attack bestAttack;
    //uint32_t maybeTime;
    uint32_t TSithTime;
    uint32_t TJediTime;
    ///uint32_t now;
     uint32_t nowT;
    uint32_t nowM;
    
    
    
    
    uint32_t TbestJedi;
    //uint32_t TmaybeJ;
    uint32_t TbestSith;

    uint32_t MSithTime;
    uint32_t MJediTime;
    uint32_t MbestJedi;
    uint32_t TmaybeJ;
    uint32_t TmaybeT;
    uint32_t MbestSith;
        
    uint32_t MmaybeS;
    uint32_t MmaybeT;
        
        
    char status;
    
};

class General {
    //store troops lost
public:
    General() : JediDeployed(0), Survived(0), SithDeployed(0) {}
    void addDeployment(const uint32_t &x, char team) {
        if (team == 'J') {
            JediDeployed = JediDeployed + x;
        }
        else {
            SithDeployed = SithDeployed + x;
        }
        Survived = Survived + x;
    }
    void removeDeaths(const uint32_t &x) {
        Survived =  Survived -  x;
    }
    void print(uint32_t ID) {
        uint32_t totalDep = JediDeployed + SithDeployed;
        cout << "General " << ID << " deployed " << JediDeployed << " Jedi troops and "
        << SithDeployed << " Sith troops, and " << Survived << "/" << totalDep << " troops survived.\n";
    }
private:
    uint32_t JediDeployed;
    uint32_t Survived;
    uint32_t SithDeployed;

    
};

struct JediComp {
    template <typename T>
    bool operator()(const Battalion &lhs, const Battalion &rhs) const {
        uint32_t leftForce = lhs.getForce();
        uint32_t rightForce = rhs.getForce();
        if (leftForce > rightForce) {
            return true;
        }
        else if ((leftForce < rightForce)) {
            return false;
        }
        else {
            if (leftForce == rightForce) {
                //compare timestamps
                if (lhs.getStamp() > rhs.getStamp()) {
                    return true;
                }
                else if (lhs.getStamp() == rhs.getStamp()) {
                    if (lhs.getID() > rhs.getID()) {
                        return true;
                    }
                    return false;
                }
                else {
                    return false;
                }
            // if lhs timestamp > rhs timestamp
            // true
            }
            return false;
        }
        return (leftForce > rightForce);
    }
};

struct SithComp {
    bool operator()(const Battalion &lhs, const Battalion &rhs) const {
        uint32_t leftForce = lhs.getForce();
        uint32_t rightForce = rhs.getForce();
        if ((leftForce > rightForce)) {
            return false;
        }
        else if ((leftForce < rightForce)) {
            return true;
        }
        else {
            if (leftForce == rightForce) {
                //compare timestamps
                if (lhs.getStamp() > rhs.getStamp()) {
                    return true;
                }
                else if (lhs.getStamp() == rhs.getStamp()) {
                    if (lhs.getID() > rhs.getID()) {
                        return true;
                    }
                    return false;
                }
                else {
                    return false;
                }
            // if lhs timestamp > rhs timestamp
            // true
            }
            return true;
        }
        return (leftForce < rightForce);
    }
};

class Planet {
public:
    Planet() : lastT(0), numBatts(0) {
        vector<uint32_t> nextTime = { lastT };
    }
    
    void addBattalion(Battalion &in, vector<General> &genie, bool &verbose, bool &median, bool &watcher, uint32_t &counter, bool &generals) {
        if (watcher) {
           
            //movie.check(in);
            movie.BushCheck(in);
            movie.tackCheck(in);

        }
        
        if (in.getTeam() ==  'J') {
                Jedi.push(in);
            //}
            if (!Sith.empty()) {
                
                
                fightCheck(verbose, genie, median, in.getStamp(), counter, generals);
            }
        }
        else if (in.getTeam() ==  'S') {
                Sith.push(in);
            //}
            if (!Jedi.empty()) {
                fightCheck(verbose, genie, median, in.getStamp(), counter, generals);
            }
        }
        else {
            cerr << "ERROR: TEAM NOT PROPERLY STORED\n";
            exit(0);
        }
    }
    
    void movieCheck(uint32_t &i) {
        if (movie.getAmbush().getBlank()) {
            cout << "A movie watcher would not see an interesting ambush on planet " << i << ".\n";
        }
        else {
            cout << "A movie watcher would enjoy an ambush on planet " << i << " with Sith at time " <<
             movie.getAmbush().getT1() << " and Jedi at time " << movie.getAmbush().getT2()
            << " with a force difference of " << movie.getAmbush().getDiff() << ".\n";
        }
        
        if (movie.getAttack().getBlank()) {
            cout << "A movie watcher would not see an interesting attack on planet " << i << ".\n";
        }
        else {
            cout << "A movie watcher would enjoy an attack on planet " << i << " with Jedi at time " << movie.getAttack().getT1() << " and Sith at time " << movie.getAttack().getT2() <<
             " with a force difference of " << movie.getAttack().getDiff() << ".\n";
        }
    }
    

    void fightCheck(bool verbose, vector<General> &genie, bool median, uint32_t time, uint32_t &counter, bool generals) {  //when Jedi shows up
        //if hetski is true, Jedi, if false, Sith
        //need to make this track states
        while (Sith.top().getForce() >= Jedi.top().getForce() && !Sith.empty() && !Jedi.empty()) {
            uint32_t troopsLost = 0;
            ++numBatts;
            
            auto &topJedi = const_cast<Battalion &>(Jedi.top());
            auto &topSith = const_cast<Battalion &>(Sith.top());
            
            uint32_t Gen1;
            uint32_t Gen2;
            Gen1 = topJedi.getGen();
            Gen2 = topSith.getGen();
            uint32_t realPlan = topSith.getPlan();
            
            
            uint32_t jCount = Jedi.top().getNum();
            uint32_t sCount = Sith.top().getNum();
            if (jCount > sCount) {
                if (generals) {
                    genie[topJedi.getGen()].removeDeaths(sCount);
                    genie[topSith.getGen()].removeDeaths(sCount);
                }
                
                
                topJedi.lostTroop(sCount);
                
                troopsLost = 2 * sCount;
                Sith.pop();
            }
            else if (jCount < sCount) {
                if (generals) {
                    genie[topJedi.getGen()].removeDeaths(jCount);
                    genie[topSith.getGen()].removeDeaths(jCount);
                }
                
                
            
                topSith.lostTroop(jCount);
                troopsLost = 2 * jCount;
                Jedi.pop();
            }
            else {
               
                if (generals) {
                    genie[topJedi.getGen()].removeDeaths(jCount);
                    genie[topSith.getGen()].removeDeaths(sCount);
                }
                
                troopsLost = 2 * sCount;
                Jedi.pop();
                Sith.pop();
            }
            
            if (verbose) {
                ++counter;
                cout << "General " << Gen2 << "'s battalion attacked General " << Gen1 << "'s battalion on planet " << realPlan << ". " << troopsLost << " troops were lost.\n";
            }
            if (median) {
                
                if (time > lastT) {
        
                    lastT = time;
    
                    
                }
                    
                    if (pqMax.empty() || troopsLost < pqMax.top()) {
                        pqMax.push(troopsLost);
                    } else {
                        pqMin.push(troopsLost);
                    }
                        
                    if (pqMax.size() > pqMin.size() + 1) {
                        pqMin.push(pqMax.top());
                        pqMax.pop();
                    }
                    else if (pqMin.size() > pqMax.size() + 1) {
                        pqMax.push(pqMin.top());
                        pqMin.pop();
                    
                    //reblance ^
                }
                 
                
                
           
              
            }
        }
    }
    
    void medPrint(uint32_t currentTime, uint32_t planNum) {

        uint32_t med;
        
        
        
        
        if (pqMax.empty() && pqMin.empty()) {
            return;
        }
        else if (pqMax.size() > pqMin.size()) {
            med = pqMax.top();
            //pqMax.pop();
        }
        else if (pqMin.size() > pqMax.size()) {
            med = pqMin.top();
            //pqMin.pop();
        }
        else {
            med = (pqMax.top() + pqMin.top()) / 2;
            //pqMax.pop();
            //pqMin.pop();
        }
        cout << "Median troops lost on planet " << planNum << " at time " << currentTime << " is " << med << ".\n";
    }

   
    
    
    priority_queue<Battalion, vector<Battalion>, JediComp>& getJedi() {
        return Jedi;
    }
    priority_queue<Battalion, vector<Battalion>, SithComp>& getSith() {
        return Sith;
    }
    
    uint32_t getNumBatts() const {
        return numBatts;
    }
    
    
private:
    State movie;
    uint32_t lastT;
    uint32_t numBatts;
    //vector<Fight> log;
    
    
    priority_queue<uint32_t, vector<uint32_t>> pqMax;
    priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t>> pqMin;
    
    priority_queue<Battalion, vector<Battalion>, JediComp> Jedi;
    priority_queue<Battalion, vector<Battalion>, SithComp> Sith;
};


class Game {
public:
    Game(uint32_t gen, uint32_t plan) : ctime(0), numGen(gen), numPlan(plan) {
        plans.resize(numPlan);
        genies.resize(numGen);
        verbose = false;
        median = false;
        genEval = false;
        watcher = false;
        counter = 0;
    }
    
    void order(Battalion in) {
        
        genies[in.getGen()].addDeployment(in.getNum(), in.getTeam());
        if (in.getStamp() > ctime) {
            if (isMedian()) {
                medianPrint(ctime);
            }
            ctime = in.getStamp();
            
        }
        plans[in.getPlan()].addBattalion(in, genies, verbose, median, watcher, counter, genEval);
        
    }
    
    uint32_t findNumFights() {
        uint32_t count = 0;
        for (uint32_t i = 0; i < numPlan; ++i) {
            count = count + plans[i].getNumBatts();
        }
        return count;
    }
    void medianPrint(uint32_t ctime) {
        
        uint32_t count = 0;
        for (auto &p : plans) {

                p.medPrint(ctime, count);
                ++count;
            
        }
    }
    
    void moviePrint() {
        if (watcher) {
            cout << "---Movie Watcher---\n";
            for (uint32_t i = 0; i < numPlan; ++i) {
                plans[i].movieCheck(i);
            }
        }
    }
    vector<Planet>& getPlans() {
        return plans;
    }
    
    

    uint32_t getnumGen() const {
        return numGen;
    }
    uint32_t getnumPlan() const {
        return numPlan;
    }
    
    bool isMedian() {
        return median;
    }
    
    void printGeneral() {
        if (genEval) {
            cout << "---General Evaluation---\n";
            for (uint32_t i = 0; i < numGen; ++i) {
                genies[i].print(i);
            }
        }
    }
    
    void vTrue() {
        verbose = true;
    }
    void mTrue() {
        median = true;
    }
    void genTrue() {
        genEval = true;
    }
    void watchTrue() {
        watcher = true;
    }
    uint32_t getTime() const {
        return ctime;
    }
    
private:
    
    uint32_t ctime;
    bool verbose;
    bool median;
    bool genEval;
    bool watcher;
    uint32_t numGen;
    uint32_t numPlan;
    vector<Planet> plans;
    vector<General> genies;
    uint32_t counter;
};

void readIn(istream &inputStream, Game &Starwars, uint32_t lastT) {
    /*
    uint32_t time;
    string team;
    int inputs[4];
    uint32_t boo = 0;
   
    while (inputStream >> time >> team)  {
     
        string splice;
        
        
        int count = 0;
        while (count < 4) {
            if (lastT > time) {
                cerr << "ERROR: INVALID TIMESTAMP\n";
                exit(1);
            }
            lastT = time;
            inputStream >> splice;
            stringstream(splice.substr(1)) >> inputs[count];
            count++;
        }
        if (inputs[0] >= static_cast<int>(Starwars.getnumGen()) || inputs[1] < 0) {
            cerr << "ERROR: INVALID GENERAL INPUT\n";
            exit(1);
        }
        if (inputs[1] >= static_cast<int>(Starwars.getnumPlan()) || inputs[1] < 0) {
            cerr << "ERROR: INVALID PLANET INPUT\n";
            exit(1);
        }
        if (inputs[2] <= 0) {
            cerr << "ERROR: INVALID FORCE INPUT\n";
            exit(1);
        }
        if (inputs[3] <= 0) {
            cerr << "ERROR: INVALID FORCE INPUT\n";
            exit(1);
        }
        
        char t;
        if (team == "JEDI") {
            t = 'J';
        }
        else {
            t = 'S';
        }
        
        Battalion in(time, static_cast<uint32_t>(inputs[0]), static_cast<uint32_t>(inputs[1]), t, static_cast<uint32_t>(inputs[2]), static_cast<uint32_t>(inputs[3]), boo);
        Starwars.order(in);
        ++boo;
    
        
    }
    */
    uint32_t maxGENERAL = Starwars.getnumGen() - 1;
    uint32_t maxPLANET = Starwars.getnumPlan() - 1;
    
    uint32_t time;
    string team;
    uint32_t boo = 0;
    uint32_t genIds;
    uint32_t planetIds;
    uint32_t forceLevels;
    uint32_t troopsLevels;
    
    char temp;
    
    while (inputStream >> time >> team)  {
     
        if (lastT > time) {
            cerr << "ERROR: INVALID TIMESTAMP\n";
            exit(1);
        }
        lastT = time;
        //3 JEDI G0 P1 F70 #70
        
        inputStream >> temp >> genIds >> temp >> planetIds >> temp >> forceLevels >> temp >> troopsLevels;
        
        if (genIds > maxGENERAL) {
            cerr << "ERROR: INVALID GENERAL INPUT\n";
            exit(1);
        }
        if (planetIds > maxPLANET) {
            cerr << "ERROR: INVALID PLANET INPUT\n";
            exit(1);
        }
        int forceChecker = static_cast<int>(forceLevels);
        if (forceChecker <= 0) {
            cerr << "ERROR: INVALID FORCE INPUT\n";
            exit(1);
        }
        int troopChecker = static_cast<int>(troopsLevels);
        if (troopChecker <= 0) {
            cerr << "ERROR: INVALID # INPUT\n";
            exit(1);
        }
        
        
        

        
        char t;
        if (team == "JEDI") {
            t = 'J';
        }
        else {
            t = 'S';
        }
        
        Battalion in(time, genIds, planetIds, t, forceLevels, troopsLevels, boo);
        Starwars.order(in);
        ++boo;
        
    }
    
    
}


int main(int argc, char * argv[]) {
    std::ios::sync_with_stdio(false);
    // insert code here...
    //TODO: change command so it can hold multiple commands
    vector<char> command;
    getMode(argc, argv, command);
    xcode_redirect(argc, argv);
    string comment;
    getline(cin, comment);
    
    string mode;
    uint32_t numGen;
    uint32_t numPlan;
    
    cin >> comment;
    cin >> mode;
    
    cin >> comment;
    cin >> numGen;
    
    cin >> comment;
    cin >> numPlan;
    
    Game Starwars(numGen, numPlan);
    for (uint32_t i = 0; i < command.size(); ++i) {
        if (command[i] == 'v') {
            Starwars.vTrue();
        }
        else if (command[i] == 'm') {
            Starwars.mTrue();
        }
        else if (command[i] == 'g') {
            Starwars.genTrue();
        }
        else if (command[i] == 'w') {
            Starwars.watchTrue();
        }
    }
    stringstream ss;
    if (mode == "PR") {
        uint32_t seed;
        uint32_t numDep;
        uint32_t arrRate;
        cin >> comment >> seed >> comment >> numDep >> comment >> arrRate;
        P2random::PR_init(ss, seed, Starwars.getnumGen(), Starwars.getnumPlan(), numDep, arrRate);
        
        
    }
    istream &inputStream = mode == "PR" ? ss : cin;
    
    
    cout << "Deploying troops...\n";
    readIn(inputStream, Starwars, 0);
    Starwars.medianPrint(Starwars.getTime());
    cout << "---End of Day---\n" << "Battles: " << Starwars.findNumFights() << endl;
    Starwars.printGeneral();
    
    Starwars.moviePrint();
    return 0;
}
