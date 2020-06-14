#include <iostream>
#include <string>

using namespace std;

class Entry{
    private:
        int amount;
        int month;
        int date;

    public:
        Enrty(){
        }

        ~Entry(){} 

        int get_amount(void){
            return amount;
        } 

        int get_month(void){
            return month;
        }
        
        int get_date(void){
            return date;
        }
        void Set_Entry(int a, int m, int d){
            amount = a;
            month = m;
            date = d;
        }
};

Entry New_Entry(){
    int amount;
    int month;
    int date;
    cout<<"amount: ";
    cin>>amount;
    cout<<"month: ";
    cin>>month;
    cout<<"date: ";
    cin>>date;
    
    Entry new_entry;
    new_entry.Set_Entry(amount, month, date);

    return new_entry;
}

void Add_Entry_To_Array(Entry* operating_array, int &array_size, Entry new_entry){
    if (operating_array == NULL){
        operating_array[0] = new_entry;
    }
    else{
        int i;
        int new_entry_date_sum = new_entry.get_month()*31+new_entry.get_date();
        //find the approximate no. of day of the year

        for (i = 0; i < array_size; i++){
            int date_sum = operating_array[i].get_month()*31+operating_array[i].get_date();
            //find the approximate no. of day of the year

            if (new_entry_date_sum == date_sum){
                i++;
                break;
            }
            else if (new_entry_date_sum < date_sum){
                break;
            }
        }
        // find the appropriate place to insert new entry

        array_size++;

        for (int k = array_size-1; k > i; k--){
            operating_array[k] = operating_array[k-1];
        }
        operating_array[i] = new_entry;
        
    }

    
}

void Print_All_Entry(Entry *operating_array, int array_size){
    for (int i = 0; i < array_size; i++){
        cout<<"Entry no."<<i<<endl;
        cout<<"amount = "<<operating_array[i].get_amount()<<endl;
        cout<<"month = "<<operating_array[i].get_month()<<endl;
        cout<<"date = "<<operating_array[i].get_date()<<endl;
    }
}

int main(void){
    Entry operating_array[1000];
    operating_array[0] = New_Entry();
    operating_array[1] = New_Entry();
    operating_array[2] = New_Entry();

    int array_size = 3;
    Add_Entry_To_Array(operating_array, array_size, New_Entry());
    Print_All_Entry(operating_array, 4);
    char wait;
    cin>>wait;
    return 0;
}
