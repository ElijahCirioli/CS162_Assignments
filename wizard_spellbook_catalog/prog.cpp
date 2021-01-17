#include <iostream>
#include <fstream>
#include "./wizard_catalog.h"

int main(int argc, char** argv) {
    //make sure enough arguments exist
    if (argc < 3) {
        cout << "Expected 2 arguments, received " << (argc - 1) << endl;
        return 1;
    }

    //make sure file 1 can be opened
    ifstream f(argv[1]);
    if (!f.is_open()) {
        cout << "Could not find file " << argv[1] << endl;
        return 1;
    }

    //create wizards array
    int num_wizards;
    f >> num_wizards;
    wizard* wizards = create_wizards(num_wizards);
    get_wizard_data(wizards, num_wizards, f);

    //make sure file 2 can be opened
    f.open(argv[2]);
    if (!f.is_open()) {
        cout << "Could not find file " << argv[2] << endl;
        return 1;
    }

    //create spellbooks
    int num_spellbooks;
    f >> num_spellbooks;
    spellbook* spellbooks = create_spellbooks(num_spellbooks);
    get_spellbook_data(spellbooks, num_spellbooks, f);

    //login and retrieve wizard index
    int wizard_index = login(wizards, num_wizards);
    if (wizard_index >= 0)
        menu(spellbooks, &wizards[wizard_index], num_spellbooks);

    //cleanup memory
    delete_info(&wizards, num_wizards, &spellbooks, num_spellbooks);
    return 0;
}