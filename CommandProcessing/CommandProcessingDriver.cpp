//
// Created by Ricky Lam on 2021-11-03.
//

#include "CommandProcessingDriver.h"

Phases CheckCommandAndReturnPhase(string commander, CommandProcessor* comPro) {
    stringstream ss(commander);
    string comWord;
    ss >> comWord; //get first token of input string
    std::transform(comWord.begin(), comWord.end(), comWord.begin(),
                   [](unsigned char c){ return std::tolower(c); }); //convert input to lowercase

    if (comWord.compare("loadmap") == 0) {
        string secondWord;
        ss >> secondWord; //get second token of input string, which is the map file specified (e.g. canada.map)

        //does not check if map exists
        if (secondWord.compare("") != 0) {
            string header = "Loaded map ";
            string footer = " successfully and transitioned to the maploaded state.";
            string effect = header + secondWord + footer;
            cout << effect << endl;
            comPro->saveEffect(comPro->getLastCommandInList(), effect);
            return Phases::MAPLOADED;
        } else {
            string effect = "The command you entered was invalid. No file was specified for the map to be loaded. Please try again.";
            cout << effect << endl;
            comPro->saveEffect(comPro->getLastCommandInList(), effect);
            return Phases::START;
        }
    } else if (comWord.compare("validatemap") == 0) {

        // does not actually validate map

        string effect = "Validated the selected map successfully and transitioned to the mapvalidated state.";
        cout << effect << endl;
        comPro->saveEffect(comPro->getLastCommandInList(), effect);
        return Phases::MAPVALIDATED;
    } else if (comWord.compare("addplayer") == 0) {
        string secondWord;
        ss >> secondWord; //get second token of input string which is the name of the player to be added

        // does not actually add any player
        if (secondWord.compare("") != 0) {
            string header = "Added player ";
            string footer = " successfully and transitioned to the playersadded state.";
            string effect = header + secondWord + footer;
            cout << effect << endl;
            comPro->saveEffect(comPro->getLastCommandInList(), effect);
            return Phases::PLAYERSADDED;
        } else {
            string effect = "The command you entered was invalid. No name was provided for the player to be added. Please try again.";
            comPro->saveEffect(comPro->getLastCommandInList(), effect);
            cout << effect << endl;
            return Phases::MAPVALIDATED;
        }
    } else if (comWord.compare("gamestart") == 0) {
        string effect = "Started the game and transitioned to the assignreinforcement state.";
        cout << effect << endl;
        comPro->saveEffect(comPro->getLastCommandInList(), effect);
        return Phases::ASSIGNREINFORCEMENT;
    } else if (comWord.compare("replay") == 0) {
        string effect = "Replaying the game and transitioning to the start state.";
        cout << effect << endl;
        comPro->saveEffect(comPro->getLastCommandInList(), effect);
        return Phases::START;
    } else if (comWord.compare("quit") == 0) {
        string effect = "Quitting the game and exiting the program.";
        cout << effect << endl;
        comPro->saveEffect(comPro->getLastCommandInList(), effect);
        return Phases::WIN; //unsure about this part, there is no exit phase so I made it loop back into WIN
    } else {
        return Phases::START;
    }
}

void PhasesLoop(Phases* currentPhase, CommandProcessor* comPro) {
    string commander;
    while (*currentPhase != Phases::ASSIGNREINFORCEMENT) {
        switch (*currentPhase) {
            case Phases::START:
                cout << "Currently in START phase." << endl;
                commander = comPro->getCommand();
                while (!comPro->validate(commander, currentPhase)) {
                    cout << "The command you entered was invalid. Please try again." << endl;
                    commander = comPro->getCommand();
                }
                *currentPhase = CheckCommandAndReturnPhase(commander, comPro);
                break;
            case Phases::MAPLOADED:
                cout << "Currently in MAPLOADED phase." << endl;
                commander = comPro->getCommand();
                while (!comPro->validate(commander, currentPhase)) {
                    cout << "The command you entered was invalid. Please try again." << endl;
                    commander = comPro->getCommand();
                }
                *currentPhase = CheckCommandAndReturnPhase(commander, comPro);
                break;
            case Phases::MAPVALIDATED:
                cout << "Currently in MAPVALIDATED phase." << endl;
                commander = comPro->getCommand();
                while (!comPro->validate(commander, currentPhase)) {
                    cout << "The command you entered was invalid. Please try again." << endl;
                    commander = comPro->getCommand();
                }
                *currentPhase = CheckCommandAndReturnPhase(commander, comPro);
                break;
            case Phases::PLAYERSADDED:
                cout << "Currently in PLAYERSADDED phase." << endl;
                commander = comPro->getCommand();
                while (!comPro->validate(commander, currentPhase)) {
                    cout << "The command you entered was invalid. Please try again." << endl;
                    commander = comPro->getCommand();
                }
                *currentPhase = CheckCommandAndReturnPhase(commander, comPro);
                break;
            default:
                cout << "ERROR" << endl;
                break;
        }
    }
}

void CommandProcessingDriver(string filename) {
    CommandProcessor* comPro;
    Phases* currentPhase = new Phases(Phases::START);
    
    if (filename.compare("") != 0) {
        comPro = new FileCommandProcessorAdapter(filename);
    } else {
        comPro = new CommandProcessor();
    }

    while (*currentPhase == Phases::START) {
        PhasesLoop(currentPhase, comPro);

        delete currentPhase;

        cout << "Skipping gameplay loop... Currently in WIN phase." << endl;
        currentPhase = new Phases(Phases::WIN);
        string commander;
        commander = comPro->getCommand();
        while (!comPro->validate(commander, currentPhase)) {
            cout << "The command you entered was invalid. Please try again." << endl;
            commander = comPro->getCommand();
        }
        *currentPhase = CheckCommandAndReturnPhase(commander, comPro);
    }

    delete currentPhase;
    currentPhase = nullptr;
    delete comPro;
    comPro = nullptr;
}
