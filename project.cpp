#include <iostream>
#include <iomanip>
using namespace std;
FILE* f;

struct to_do_list
{
    int id = 1;
    char comment[100];
};

int idFun();

int main(){
    char choice;
    bool loop = true;
    system("clear");
    do
    {
        cout << "----------To Do List---------\n";
        cout << "1.create list\n";
        cout << "2.show list\n";
        cout << "3.delete list\n";
        cout << "0.exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == '1')
        {
            system("clear");
            to_do_list tdl;
            int create_id = idFun();
            f = fopen("./to_do_list_data.txt", "a");
            tdl.id = create_id;
            cout << "----------Creat List---------\n";
            cout << "Write here: ";
            fflush(stdin);
            gets(tdl.comment);
            fwrite(&tdl, sizeof(to_do_list), 1, f);
            fclose(f);
            system("clear");
            cout << "### a task List added. ###\n";
        }
        else if (choice == '2')
        {
            system("clear");
            f = fopen("./to_do_list_data.txt", "r");
            fseek(f, 0, 2);  
            int total = ftell(f);
            int n = total/sizeof(to_do_list);
            fseek(f, 0, 0); 
            to_do_list tdl[n];
            fread(&tdl, sizeof(tdl), n, f);
            cout << "----------Show List----------\n";
            cout << setw(15) << " ID| Lists\n";
            for (int i = 0; i < n; i++)
            {
                cout << setw(7) << tdl[i].id << "| "<< tdl[i].comment << endl;
            }
            fclose(f);
            cout << "-----------------------------\n";
        }
        else if (choice == '3')
        {
            system("clear");
            int searchid;
            cout << "----------Delete List--------\n";
            cout << "Enter List ID: ";
            cin >> searchid;
            f = fopen("./to_do_list_data.txt", "r+");
            fseek(f, 0, 2);
            int n = ftell(f)/sizeof(to_do_list);
            to_do_list tdl[n];
            fseek(f, 0, 0);
            fread(tdl, sizeof(tdl),1,f);
            fclose(f);
            f = fopen("./to_do_list_data.txt", "w");
            int found = 0;
            for(int i = 0; i < n; i++)
            {
                if(tdl[i].id != searchid)
                fwrite(&tdl[i], sizeof(to_do_list),1,f);
                else
                found = 1;
            }
            fclose(f);
            system("clear");
            if(found == 0)
            cout<<"### ID not found ###\n";
            else
            cout<<"### a list deleted ###\n";
            
        }
        else if (choice == '0')
        {
            loop = false;
            system("clear");
            cout << "### bye bye ###\n";
        }
        else
        {
            system("clear");
            cout << "Choice Error\n";
        }
    } while (loop);
}

int idFun(){
    f = fopen("./to_do_list_data.txt", "a");
    fseek(f, 0, 2);
	int total = ftell(f);
	int n = total/sizeof(to_do_list);
	fseek(f, 0, 0);
    fclose(f);
    return n+1;
}
