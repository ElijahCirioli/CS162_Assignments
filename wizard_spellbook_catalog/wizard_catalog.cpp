#include <iostream>
#include <fstream>
#include <string>
#include "./wizard_catalog.h" 

//create and return an array of wizzards
wizard* create_wizards(int size) {
    return new wizard[size];
}

//fill wizard array with data from txt file
void get_wizard_data(wizard* wizards, int size, ifstream& f) {
    for (int i = 0; i < size; i++) {
        wizard* w = &wizards[i];
        f >> w->name;
        f >> w->id;
        f >> w->password;
        f >> w->position_title;
        f >> w->beard_length;
    }
    f.close();
}

//create and return an array of spellbooks
spellbook* create_spellbooks(int size) {
    return new spellbook[size];
}

//fill spellbook array with data from txt file
void get_spellbook_data(spellbook* spellbooks, int size, ifstream& f) {
    for (int i = 0; i < size; i++) {
        spellbook* book = &spellbooks[i];
        f >> book->title;
        f >> book->author;
        f >> book->num_pages;
        f >> book->edition;
        f >> book->num_spells;
        book->s = create_spells(book->num_spells);
        get_spell_data(book->s, book->num_spells, f);
        float total_success_rate = 0;
        for (int j = 0; j < book->num_spells; j++)
            total_success_rate += book->s[j].success_rate;
        book->avg_success_rate = total_success_rate / book->num_spells;
    }
    f.close();
}

//create and return an array of spells
spell* create_spells(int size) {
    return new spell[size];
}

//fill spell data with data from txt file
void get_spell_data(spell* spells, int size, ifstream& f) {
    for (int i = 0; i < size; i++) {
        spell* s = &spells[i];
        f >> s->name;
        f >> s->success_rate;
        f >> s->effect;
    }
}

//give 3 attempts to give ID and password that exist in wizards array
int login(wizard* wizards, int size) {
    int remainingTries = 3;
    while (remainingTries > 0) {
        cout << "Please enter your ID: ";
        string id;
        cin >> id;
        cout << "Please enter your password: ";
        string password;
        cin >> password;

        for (int i = 0; i < size; i++) {
            wizard w = wizards[i];
            if (w.id == stoi(id) && w.password == password) {
                cout << endl << "Welcome, " << w.name << endl;
                cout << "ID: " << w.id << endl;
                cout << "Status: " << w.position_title << endl;
                cout << "Beard length: " << w.beard_length << endl;
                return i; //return wizard index
            }
        }
        remainingTries--;
        cout << "Incorrect ID or password, " << remainingTries << " attempts remaining." << endl;
    }
    cout << "No attempts remaining, shutting down." << endl;
    return -1;
}

//ask how the user wants to sort the spellbooks
void menu(spellbook* spellbooks, wizard* user, int num_spellbooks) {
    while (true) {
        cout << endl << "SELECT AN OPTION" << endl;
        cout << "Sort spellbooks by number of pages (Press 1)" << endl;
        cout << "Group spells by their effect (Press 2)" << endl;
        cout << "Sort spellbooks by average success rate (Press 3)" << endl;
        cout << "Quit (Press 4)" << endl;

        int selection;
        cin >> selection;
        if (selection == 4) //quit
            return;

        output* results;
        results = nullptr;
        string label;
        int result_size;
        int total_num_spells = 0;

        switch (selection) {
        case 1:
            results = sort_by_num_pages(spellbooks, user, num_spellbooks);
            result_size = num_spellbooks;
            label = "SORTED BY NUMBER OF PAGES";
            break;
        case 2:
            for (int i = 0; i < num_spellbooks; i++) {
                total_num_spells += spellbooks[i].num_spells;
            }
            results = sort_by_spell_effect(spellbooks, user, num_spellbooks, total_num_spells);
            result_size = total_num_spells;
            label = "SORTED BY SPELL EFFECT";
            break;
        case 3:
            results = sort_by_success_rate(spellbooks, user, num_spellbooks);
            result_size = num_spellbooks;
            label = "SORTED BY AVERAGE SUCCESS RATE";
            break;
        }
        //be sure the user entered 1, 2, 3, or 4
        if (results)
            output_results(results, label, result_size);
    }
}

///swap the position of two spellbooks
void swap(spellbook* ap, spellbook* bp) {
    spellbook temp = *ap;
    *ap = *bp;
    *bp = temp;
}

//sort spellbooks array based on given function
void bubble_sort(spellbook* spellbooks, int size, bool (*compare)(spellbook, spellbook)) {
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (compare(spellbooks[j], spellbooks[j + 1]))
                swap(&spellbooks[j], &spellbooks[j + 1]);
}

//return whether there are more pages in book a or b
bool compare_pages(spellbook a, spellbook b) {
    return a.num_pages > b.num_pages;
}

//return whether average spell success rate for book a or b is higher
bool compare_success_rate(spellbook a, spellbook b) {
    return a.avg_success_rate > b.avg_success_rate;
}

//return whether a user is allowed to look at a given spellbook
bool allowed_access(wizard* user, spellbook* book) {
    if (user->position_title == "Student")
        for (int j = 0; j < book->num_spells; j++) {
            spell* s = &(book->s[j]);
            if (s->effect == "death" || s->effect == "poison")
                return false;
        }
    return true;
}

//return an array of spellbooks sorted by number of pages
output* sort_by_num_pages(spellbook* spellbooks, wizard* user, int size) {
    output* results = new output[size];
    bubble_sort(spellbooks, size, &compare_pages);
    for (int i = 0; i < size; i++) {
        spellbook* book = &spellbooks[i];
        if (allowed_access(user, book)) {
            results[i].name = book->title;
            results[i].data = to_string(book->num_pages);
        }
        else
            results[i].name = "HIDE";
    }
    return results;
}

//push a spell to the results array based on a given effect
void push_by_effect(spellbook* spellbooks, wizard* user, int size, string effect, output** results, int* index) {
    for (int i = 0; i < size; i++) {
        spellbook* book = &spellbooks[i];
        for (int j = 0; j < book->num_spells; j++) {
            spell* s = &(book->s[j]);
            if (s->effect == effect) {
                if (user->position_title == "Student" && (effect == "poison" || effect == "death"))
                    (*results)[*index].name = "HIDE";
                else {
                    (*results)[*index].name = s->name;
                    (*results)[*index].data = s->effect;
                }
                (*index)++;
            }
        }
    }
}

//return an array of spells sorted by effect
output* sort_by_spell_effect(spellbook* spellbooks, wizard* user, int size, int num_spells) {
    output* results = new output[num_spells];
    int index = 0;

    push_by_effect(spellbooks, user, size, "bubble", &results, &index);
    push_by_effect(spellbooks, user, size, "memory_loss", &results, &index);
    push_by_effect(spellbooks, user, size, "fire", &results, &index);
    push_by_effect(spellbooks, user, size, "poison", &results, &index);
    push_by_effect(spellbooks, user, size, "death", &results, &index);

    return results;
}

//return an array of spellbooks based on average success rate
output* sort_by_success_rate(spellbook* spellbooks, wizard* user, int size) {
    output* results = new output[size];
    bubble_sort(spellbooks, size, &compare_success_rate);
    for (int i = 0; i < size; i++) {
        spellbook* book = &spellbooks[i];
        if (allowed_access(user, book)) {
            results[i].name = book->title;
            string data = to_string(book->avg_success_rate);
            results[i].data = data.substr(0, data.find(".") + 3);
        }
        else
            results[i].name = "HIDE";
    }
    return results;
}

//print out array of results to terminal
void write_output_to_terminal(output* results, string label, int size) {
    cout << endl << label << endl;
    for (int i = 0; i < size; i++)
        if (results[i].name != "HIDE")
            cout << results[i].name << "    " << results[i].data << endl;
}

//print out array of results to file
void write_output_to_file(output* results, string label, string file_name, int size) {
    ofstream f(file_name, ios::app);
    if (f.is_open())
        cout << "Written to file " << file_name << endl;
    f << label << endl;
    for (int i = 0; i < size; i++)
        if (results[i].name != "HIDE")
            f << results[i].name << "    " << results[i].data << endl;
    f << endl;
}

//print results to either terminal or file
void output_results(output* results, string label, int result_size) {
    cout << "How would you like the information displayed?" << endl;
    cout << "Print to screen (Press 1)" << endl;
    cout << "Write to file (Press 2)" << endl;
    int selection;
    cin >> selection;

    if (selection == 1)
        write_output_to_terminal(results, label, result_size);
    else if (selection == 2) {
        cout << "Please provide desired filename: ";
        string file_name;
        cin >> file_name;
        write_output_to_file(results, label, file_name, result_size);
    }
    delete[] results;
}

//delete pointers from memory.
void delete_info(wizard** wizards, int w_size, spellbook** spellbooks, int s_size) {
    delete[] * wizards;
    for (int i = 0; i < s_size; i++)
        delete[](*spellbooks)[i].s;
    delete[] * spellbooks;
}