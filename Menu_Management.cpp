#include <iostream>
#include <string>
using namespace std;

struct Menuitem 
{
    int Price;
    string Name; 
};

class Menu_Manager 
{
private: 
    int Size;
    int Length;
    Menuitem* Prt;

public: 
    Menu_Manager(int ArrSize)
    {
        Size = ArrSize;
        Length = 0; 
        Prt = new Menuitem[ArrSize];
    }

    void Append(Menuitem Newitem)
    {
        if (Length < Size)
        {
            Prt[Length] = Newitem;
            Length++;
            cout << "The Item Was Added Successfully\n"; 
        }
        else
        {
            cout << "The Menu Is full, We Can't Add New Items. \n";
            cout << "Please Release At Least one Item to add Another one\n";
        }
    }

    void Display()
    {
        cout << "=== Displaying Array Content ===\n";
        for (int i = 0; i < Length; i++)
        {
            cout << "Meal " << (i + 1) << ": ";
            cout << "Name: " << Prt[i].Name << " --- Price: " << Prt[i].Price << " EGP\n";
            cout << "-------------------------------------\n"; 
        }
    }

    int Search(string SearchName)
    {
        for (int i = 0; i < Length; i++)
        {
            if (Prt[i].Name == SearchName)
            {
                return i;
            }
        }
        return -1; 
    }

    void Update() 
    {
        string Exist_item;
        cout << "\nPlease Enter The Name Of Item To Update: ";
        cin >> Exist_item;

        int index = Search(Exist_item);

        if (index == -1) 
        {
            cout << "=== This Item Does Not Exist In Menu ===\n";
            return; 
        }

        int Action;
        cout << "\nWhat Do You Want To Update for " << Exist_item << "?\n";
        cout << "Press 1 : Update Price Only\n";
        cout << "Press 2 : Update Both Name And Price\n";
        cin >> Action;

        switch (Action) 
        {
            case 1: 
            {
                int NewPrice;
                cout << "Enter The New Price: ";
                cin >> NewPrice;
                
                Prt[index].Price = NewPrice;
                cout << "=== Price Updated Successfully ===\n";
                break; 
            } 

            case 2: 
            {
                string NewName;
                int NewPrice;
                
                cout << "Enter The New Name: ";
                cin >> NewName;
                
                while (NewName == Exist_item) 
                {
                    cout << "New name is identical to old name! Enter a different name: ";
                    cin >> NewName;
                }
                
                cout << "Enter The New Price: ";
                cin >> NewPrice;

                Prt[index].Name = NewName;
                Prt[index].Price = NewPrice;
                
                cout << "=== Full Item Updated Successfully ===\n";
                break;
            }
            default:
                cout << "Invalid Action!\n";
        }
    }
};  

int main()
{
    Menu_Manager menu(3);
    Menuitem item;

    cout << "Enter Meal Name: ";
    cin >> item.Name;
    cout << "Enter Meal Price: ";
    cin >> item.Price;
    menu.Append(item);

    cout << "Enter Meal Name: ";
    cin >> item.Name;
    cout << "Enter Meal Price: ";
    cin >> item.Price;
    menu.Append(item);

    menu.Display();

    menu.Update();

    menu.Display();

    return 0;
}
