#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Entry{
    private:
        int amount;
        int month;
        int date;

    public:
        Entry(){
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

class Entry_Array{
private:
    Entry* operating_array;
    int array_size;
public:
    Entry_Array(){
        operating_array = new Entry[1000];
        array_size = 0;
    }
    int get_array_size(void){
        return array_size;
    }
    int get_amount(int id){
        return operating_array[id].get_amount();
    }
    int get_month(int id){
        return operating_array[id].get_month();
    }
    int get_date(int id){
        return operating_array[id].get_date();
    }
    void add_entry(void){
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
        //set up the correct entry data

        if (array_size == 0){
            array_size++;
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

};

/*Entry New_Entry(){
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
}*/
//function is been replaced by "add_entry()" in Entry_Array Class

/*void Add_Entry_To_Array(Entry* operating_array, int &array_size, Entry new_entry){
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

    
}*/
//function is been replaced by "add_entry()" in Entry_Array Class

void Print_All_Entry(Entry_Array input){
    for (int i = 0; i < input.get_array_size(); i++){
        cout<<"Entry no."<<i<<endl;
        cout<<"amount = "<<input.get_amount(i)<<endl;
        cout<<"month = "<<input.get_month(i)<<endl;
        cout<<"date = "<<input.get_date(i)<<endl;
    }
}

void Save_To_Text(Entry_Array input){
    std :: fstream ouput_text("result.txt", std :: fstream :: out);
    for (int i = 0; i < input.get_array_size(); i++){
        ouput_text<<i<<endl;
        ouput_text<<input.get_amount(i)<<endl;
        ouput_text<<input.get_month(i)<<endl;
        ouput_text<<input.get_date(i)<<endl;
    }
    ouput_text.close();
}



int main(void){
    Entry_Array data;
    //initialize the array
    //int array_size = 0;
    data.add_entry();
    data.add_entry();
    data.add_entry();
    data.add_entry();

    Print_All_Entry(data);
    Save_To_Text(data);
    char wait;
    cin>>wait;  
    return 0;
}
