#include<iostream>
#include<string>
#include<fstream>

constexpr int MAX = 100;

using namespace std;

class Guest
{
public:
    int ID;
    string name;
    bool entered;
    bool inside;

    Guest(){
        ID = 0;
        name = "";
        entered = false;
        inside = false;
    }

    Guest(int id, string n){
        ID = id;
        name = n;
        entered = false;
        inside = false;
    }
};

Guest guest[MAX];
bool registered[MAX] = {false};
int guestCount = 0;
int nextTicketId = 1001;
int ticketCount = 0;
int guestInside = 0;


void saveGuests(){

    ofstream file("guests.txt");

    if (!file){
        cout << "===================" << endl;
        cout << "Error opening file!" << endl;
        cout << "===================" << endl;
        return;
    }

    for (int i = 0; i < MAX; i++){
        if (registered[i]){
            file << guest[i].ID << endl;
            file << guest[i].name << endl;
            file << guest[i].entered << endl;
            file << guest[i].inside << endl;
        }
    }

    file.close();
}


void loadGuests(){

    ifstream file("guests.txt");

    if (!file) return;

    int id;
    string name;
    bool entered;
    bool inside;

    while (file >> id){

        file >> ws;
        getline(file, name);

        if (!(file >> entered >> inside)) break;

        int index = -1;

        for (int i = 0; i < MAX; i++){
            if (!registered[i]){
                index = i;
                break;
            }
        }

        if (index == -1) break;

        guest[index] = Guest(id, name);
        guest[index].entered = entered;
        guest[index].inside = inside;

        registered[index] = true;

        ticketCount++;

        if (entered) guestCount++;

        if (inside) guestInside++;

        if (id >= nextTicketId) nextTicketId = id + 1;
    }

    file.close();
}


void registerGuest(){
    
    if(ticketCount >= MAX){

        cout << "=====================" << endl;
        cout << "No Available Tickets!" << endl;
        cout << "=====================" << endl;

        return;
    }

    for(int i = 0; i < MAX; i++){
        
        if(registered[i] == false){
            
            cout << "--------------------------" << endl;
            cout << "Ticket ID: " << nextTicketId << endl;
            string n;
            cout << "Enter Name: ";
            getline(cin >> ws, n);

            if(n.empty()){
                cout << "=====================" << endl;
                cout << "Name cannot be empty." << endl;
                cout << "=====================" << endl;

                return;
            }

            cout << "--------------------------" << endl;

            guest[i].ID = nextTicketId;
            guest[i].name = n;
            nextTicketId++;
            ticketCount++;
            registered[i] = true;

            cout << "==========================" << endl;
            cout << "Registration Successful!." << endl;
            cout << "==========================" << endl;

            saveGuests();

            return;
        }
    }
}

void displayGuestDetail(int i){

    if(i == -1){

        cout << "===============" << endl;
        cout << "Not Registered!" << endl;
        cout << "===============" << endl;

        return;
    }
    else{
        cout << "=====================" << endl;
        cout << "Guest ID: " << guest[i].ID << endl;
        cout << "Name: " << guest[i].name << endl;
        if(guest[i].entered) cout << "Entered." << endl;
        else cout << "Not Entered." << endl;
        if(guest[i].inside) cout << "Inside the Event." << endl;
        else cout << "Not inside the Event." << endl;
        cout << "=====================" << endl;

        return;
    }
}

int searchGuest(){

    int choose;

    while(true){
        
        cout << "---------------------" << endl;
        cout << "Search by- " << endl;
        cout << "1. ID." << endl;
        cout << "2. Name." << endl;

        if(!(cin >> choose)){

            cin.clear();
            cin.ignore(10000, '\n');

            cout << "==============================" << endl;
            cout << "Invalid input. Enter a number." << endl;
            cout << "==============================" << endl;
            continue;
        }

        if(choose == 1){

            int id;
            cout << "Enter Guest ID: ";

            if(!(cin >> id)){

                cin.clear();
                cin.ignore(10000, '\n');

                cout << "=================" << endl;
                cout << "Invalid Guest ID." << endl;
                cout << "=================" << endl;

                return -1;
            }

            cout << "---------------------" << endl;

            for(int i = 0; i < MAX; i++){

                if(registered[i] && guest[i].ID == id) return i;
            }

            return -1;
        }
        else if(choose == 2){

            string n;
            cout << "Enter guest Name: ";
            getline(cin >> ws, n);
            cout << "---------------------" << endl;

            for(int i = 0; i < MAX; i++){

                if(registered[i] && guest[i].name == n) return i;
            }

            return -1;
        }
        else{
            cout << "---------------------" << endl;
            cout << "Please choose 1 or 2." << endl;
            cout << "---------------------" << endl;
        }
    }
}

void searchGuest2(){

    int i = searchGuest();
    displayGuestDetail(i);
}

void updateGuest(){

    int i = searchGuest();
    displayGuestDetail(i);

    if(i == -1) return;

    string n;
    cout << "--------------------------------------------------" << endl;
    cout << "Enter the name that you want to change into: ";
    getline(cin >> ws, n);

    if(n.empty()){

        cout << "=====================" << endl;
        cout << "Name cannot be empty." << endl;
        cout << "=====================" << endl;

        return;
    }

    cout << "--------------------------------------------------" << endl;

    guest[i].name = n;

    cout << "===================================" << endl;
    cout << "Name has been changed successfully." << endl;
    cout << "===================================" << endl;

    displayGuestDetail(i);

    saveGuests();
}

void deleteGuest(){

    int i = searchGuest();
    displayGuestDetail(i);

    if(i == -1) return;

    int d;

    while(true){

        cout << "-------------------" << endl;
        cout << "Confirm to delete: " << endl;
        cout << "1. Delete." << endl;
        cout << "2. Cancel." << endl;

        if(!(cin >> d)){

            cin.clear();
            cin.ignore(10000, '\n');

            cout << "==============================" << endl;
            cout << "Invalid input. Enter a number." << endl;
            cout << "==============================" << endl;

            continue;
        }

        cout << "-------------------" << endl;

        if(d == 1){

            if(guest[i].entered) guestCount--;
            if(guest[i].inside) guestInside--;
            ticketCount--;

            guest[i].ID = 0;
            guest[i].name = "";
            guest[i].entered = false;
            guest[i].inside = false;

            registered[i] = false;
        
            cout << "==============" << endl;
            cout << "Guest removed." << endl;
            cout << "==============" << endl;

            saveGuests();

            return;
        }
        else if(d == 2){

            cout << "=========" << endl;
            cout << "Canceled." << endl;
            cout << "=========" << endl;

            return;
        }
        else{

            cout << "---------------------" << endl;
            cout << "Please choose 1 or 2." << endl;
            cout << "---------------------" << endl;
        }
    }
    
}

void manageEntry(){

    int i = searchGuest();
    displayGuestDetail(i);
    if(i == -1) return;

    if (guestInside >= MAX && !guest[i].inside){

        cout << "============================" << endl;
        cout << "Venue is full! Entry denied." << endl;
        cout << "============================" << endl;

        return;
    }

    if(!guest[i].entered || !guest[i].inside){

        int c;
        while(true){

            cout << "--------------" << endl;
            cout << "Confirm Entry-" << endl;
            cout << "1. Confirm." << endl;
            cout << "2. Cancel." << endl;
            
            if(!(cin >> c)){

                cin.clear();
                cin.ignore(10000, '\n');

                cout << "==============================" << endl;
                cout << "Invalid input. Enter a number." << endl;
                cout << "==============================" << endl;

                continue;
            }

            if(c == 1 || c == 2) break;

            cout << "=====================" << endl;
            cout << "Please choose 1 or 2." << endl;
            cout << "=====================" << endl;
        }
        
        cout << "--------------" << endl;

        if(c == 1){

            if(!guest[i].entered){

                guest[i].entered = true;
                guestCount++;
            }
            
            if(!guest[i].inside){

                guest[i].inside = true;
                guestInside++;
            }
            
            cout << "=================" << endl;
            cout << "Entry successful." << endl;
            cout << "=================" << endl;

            saveGuests();
        
            return;
        }
        else{

            cout << "---------------" << endl;
            cout << "Entry Canceled." << endl;
            cout << "---------------" << endl;
            return;
        }
    }
    
    cout << "=============================" << endl;
    cout << "The guest is already Entered!" << endl;
    cout << "=============================" << endl;
}

void manageExit(){

    int exit;
    while(true){

        cout << "-------------------" << endl;
        cout << "Which type of exit?" << endl;
        cout << "1. Leave." << endl;
        cout << "2. Temporary exit." << endl;

        if(!(cin >> exit)){

            cin.clear();
            cin.ignore(10000, '\n');

            cout << "==============================" << endl;
            cout << "Invalid input. Enter a number." << endl;
            cout << "==============================" << endl;

            continue;
        }

        if(exit == 1 || exit == 2) break;
        else{

            cout << "---------------------" << endl;
            cout << "Please choose 1 or 2." << endl;
            cout << "---------------------" << endl;
        }
    }

    cout << "-------------------" << endl;

    if(exit == 1){
        deleteGuest();
        return;
    }
    else if(exit == 2){

        int i = searchGuest();
        displayGuestDetail(i);

        if(i == -1) return;

        if(!guest[i].inside){

            cout << "========================================" << endl;
            cout << "Guest is not currently inside the event." << endl;
            cout << "========================================" << endl;
            return;
        }

        int c;
        while(true){
            cout << "-------------" <<endl;
            cout << "Confirm Exit-" << endl;
            cout << "1. Confirm." << endl;
            cout << "2. Cancel." << endl;
        
            if(!(cin >> c)){

                cin.clear();
                cin.ignore(10000, '\n');

                cout << "==============================" << endl;
                cout << "Invalid input. Enter a number." << endl;
                cout << "==============================" << endl;

                continue;
            }

            if(c == 1 || c == 2) break;

            cout << "=====================" << endl;
            cout << "Please choose 1 or 2." << endl;
            cout << "=====================" << endl;
        }

        cout << "-------------" <<endl;

        if(c == 1){

            guest[i].inside = false;
            guestInside--;
            cout << "========" << endl;
            cout << "Outside." << endl;
            cout << "========" << endl;

            saveGuests();

            return;
        }
        else{

            cout << "--------------" << endl;
            cout << "Exit Canceled." << endl;
            cout << "--------------" << endl;
            return;
        }
    }
    
}

void displayGuests(){

    if(ticketCount == 0){

        cout << "=============================" << endl;
        cout << "No guests are Registered yet." << endl;
        cout << "=============================" << endl;

        return;
    }
    
    for(int i = 0; i < MAX; i++){

        if(registered[i]) displayGuestDetail(i);
    }
}

void stats(){

    double crowdPercentage = (guestInside / MAX) * 100;

    cout << "==============================" << endl;
    cout << "Total Space: " << MAX << endl;
    cout << "Total Registered: " << ticketCount << endl;
    cout << "Total Entered: " << guestCount << endl;
    cout << "Available Registration: " << MAX - ticketCount << endl;
    cout << "Guest Inside: " << guestInside << endl;
    cout << "Guest Outside: " << guestCount - guestInside << endl;
    cout << "Crowd: " << crowdPercentage << "%" << endl;
    cout << "==============================" << endl;

}

int main(){

    loadGuests();

    int choose = 0;
    do{
        cout << "--------------------------------------------" << endl;
        cout << "   Crowd Density and Event Entry Manager.   " << endl;
        cout << "--------------------------------------------" << endl;

        cout << "1. Register Attendee." << endl;
        cout << "2. Search Attendee." << endl;
        cout << "3. Update Attendee." << endl;
        cout << "4. Delete Attendee." << endl;
        cout << "5. Manage Entry." << endl;
        cout << "6. Manage Exit." << endl;
        cout << "7. Display Attendees." << endl;
        cout << "8. Display Stats." << endl;
        cout << "9. EXIT." << endl;

        if(!(cin >> choose)){

            cin.clear();
            cin.ignore(10000, '\n');

            choose = 0;
            cout << "=====================" << endl;
            cout << "Invalid input Option.";
            cout << "=====================" << endl;
            continue;
        }

        switch(choose){

            case 1:
                registerGuest();
                break;

            case 2:
                searchGuest2();
                break;

            case 3:
                updateGuest();
                break;

            case 4:
                deleteGuest();
                break;

            case 5:
                manageEntry();
                break;

            case 6:
                manageExit();
                break;

            case 7:
                displayGuests();
                break;

            case 8:
                stats();
                break;

            case 9:
                cout << "==============" << endl;
                cout << "System Closed." << endl;
                cout << "==============" << endl;
                break;

            default:
                cout << "======================================" << endl;
                cout << "INVALID! Please choose between 1 to 9." << endl;
                cout << "======================================" << endl;
                break;
        }
    }while(choose != 9);
}