#include<iostream>
#include<string>

#define MAX 100

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

void registerGuest(){
    
    if(ticketCount >= 100){

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
            cin >> n;
            cout << "--------------------------" << endl;

            guest[i].ID = nextTicketId;
            guest[i].name = n;
            nextTicketId++;
            ticketCount++;
            registered[i] = true;

            cout << "==========================" << endl;
            cout << "Registration Successfull!." << endl;
            cout << "==========================" << endl;

            return;
        }
    }
}

void displayGuestDetail(int i){

    cout << "=====================" << endl;
    cout << "Guest ID: " << guest[i].ID << endl;
    cout << "Name: " << guest[i].name << endl;
    if(guest[i].entered) cout << "Entered." << endl;
    else cout << "Not Entered." << endl;
    if(guest[i].inside) cout << "Inside the Event." << endl;
    else cout << "Not inside the Event." << endl;
    cout << "=====================" << endl;
}

void searchGuest(){

    int choose;
    cout << "---------------------" << endl;
    cout << "Search by- " << endl;
    cout << "1. ID." << endl;
    cout << "2. Name." << endl;
    cin >> choose;

    if(choose == 1){

        int id;
        cout << "Enter Guest ID: ";
        cin >> id;
        cout << "---------------------" << endl;

        for(int i = 0; i < MAX; i++){

            if(guest[i].ID == id){
                displayGuestDetail(i);
                return;
            }
        }

        cout << "===============" << endl;
        cout << "Not Registered!" << endl;
        cout << "===============" << endl;
        return;
    }
    else if(choose == 2){

        string n;
        cout << "Enter guest Name: ";
        cin >> n;
        cout << "---------------------" << endl;

        for(int i = 0; i < MAX; i++){

            if(guest[i].name == n){
                displayGuestDetail(i);
                return;
            }
        }

        cout << "===============" << endl;
        cout << "Not Registered!" << endl;
        cout << "===============" << endl;
        return;
    }
    else{
        cout << "---------------------" << endl;
        cout << "Please choose 1 or 2." << endl;
        cout << "---------------------" << endl;

        searchGuest();
    }
}

int main(){

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
        cout << "7. Display Attendes." << endl;
        cout << "8. Sort Attendees." << endl;
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
                searchGuest();
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                break;

            case 8:
                break;

            case 9:
                cout << "==============" << endl;
                cout << "Sysyem Closed." << endl;
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