#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Entry{
    private:
        int amount;
        int year;
        int month;
        int date;

    public:
        Entry(){
        }

        ~Entry(){} 

        int get_amount(void){
            return amount;
        } 

        int get_year(void){
            return year;
        }

        int get_month(void){
            return month;
        }
        
        int get_date(void){
            return date;
        }
        void Set_Entry(int a, int y, int m, int d){
            amount = a;
            year = y;
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
    int get_year(int id){
        return operating_array[id].get_year();
    }
    int get_month(int id){
        return operating_array[id].get_month();
    }
    int get_date(int id){
        return operating_array[id].get_date();
    }
    void add_entry(void){
        int amount;
        int year;
        int month;
        int date;
        
        cout<<"amount: ";
        cin>>amount;
        cout<<"year: ";
        cin>>year;
        cout<<"month: ";
        cin>>month;
        cout<<"date: ";
        cin>>date;
    
        Entry new_entry;
        new_entry.Set_Entry(amount, year, month, date);
        //set up the correct entry data

        if (array_size == 0){
            array_size++;
            operating_array[0] = new_entry;
        }
        else{
            int i;
            int new_entry_date_sum = new_entry.get_year()*366 + new_entry.get_month()*31 + new_entry.get_date();
            //find the approximate no. of day of the year

            for (i = 0; i < array_size; i++){
                int date_sum = operating_array[i].get_year()*366 + operating_array[i].get_month()*31+operating_array[i].get_date();
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

            cout<<"Successfully added and entry: "<<endl;
            cout<<year<<"/"<<month<<"/"<<date<<"      "<<amount<<endl;
        
        }
    }
    // for manual input new entries
    void replace_entry(Entry input, int id){
        operating_array[id] = input;
    }
    // to replace a specific entry
    void append_entry(Entry input){
        operating_array[array_size] = input;
        array_size++;
    }
    // to append an entry onto an existed Entry_Array
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

void Print_Entry(Entry_Array input, int id){
    cout<<"date: "<<input.get_year(id)<<"/"<<input.get_month(id)<<"/"<<input.get_date(id)<<endl;
    cout<<"amount: "<<input.get_amount(id)<<endl;
    cout<<endl;
}//print out the content of id

void Print_All_Entry(Entry_Array input){
    int i = 0;
    for (; i < input.get_array_size(); i++){
        Print_Entry(input, i);
    }
}

void Save_To_Text(Entry_Array input){
    std :: fstream ouput_text("result.txt", ios :: out);
    ouput_text<<input.get_array_size()<<endl;
    for (int i = 0; i < input.get_array_size(); i++){
        ouput_text<<i<<endl;
        ouput_text<<input.get_amount(i)<<endl;
        ouput_text<<input.get_year(i)<<endl;
        ouput_text<<input.get_month(i)<<endl;
        ouput_text<<input.get_date(i)<<endl;
    }
    ouput_text.close();
    cout<<"Succesfully saved to file as result.txt"<<endl;
}

Entry_Array Read_From_Text(void){
    Entry_Array input_result;//the final result of reading the file
    Entry temp;//the temptation Entry obj. for moving files
    int input_size; // the array_size of the input Entry_Array
    int a;//temp for amount
    int y;//temp for year
    int m;//temp for month
    int d;//temp for date
    int crap;

    std :: fstream input_text("result.txt", ios :: in);
    input_text>>input_size;

    for (int i = 0; i < input_size; i++){
        input_text>>crap;
        input_text>>a;
        input_text>>y;
        input_text>>m;
        input_text>>d;
        temp.Set_Entry(a, y, m, d);
        input_result.append_entry(temp);
    }
    input_text.close();

    return input_result;
}

void Report_Balance(Entry_Array input){
    int balance = -1;
    int initial_balance = -1;

    int year;//the year when the user asks for report
    int month;//the month when the user asks for report
    int date; // the date when the user asks for report

    char init = 'N';
    cout<<"initialize balance[Y/N]?(default = 0)"<<endl;
    cin>>init;
    if ((init == 'Y')||(init == 'y')){
        cout<<"Please enter current balance"<<endl;
        cin>>balance;
    }
    else{
        balance = 0;
    }//let the user to decide whether to initialize the balance
    initial_balance = balance;

    cout<<"Please enter the year"<<endl;
    cin>>year;
    cout<<"Please enter the month"<<endl;
    cin>>month;
    cout<<"Please enter the date"<<endl;
    cin>>date;
    //let the user set the month&date
    
    int current_date_sum = year*366 + month*31 + date;
    int i;

    for (i = 0; i < input.get_array_size(); i++){
        int entry_date_sum = input.get_year(i)*366 + input.get_month(i)*31+input.get_date(i);
        if(current_date_sum < entry_date_sum){
            break;
        }
        else if (current_date_sum == entry_date_sum){
            break;
        }
    }//find the correct id to start with the report

    int save_i = i; 

    for (; i < input.get_array_size(); i++){
        int balance_temp = balance + input.get_amount(i);
        Print_Entry(input, i);
        if (balance_temp<0){
            cout<<"======================"<<endl;
            cout<<"======================"<<endl;
            cout<<"        WARNING       "<<endl;
            cout<<"$"<<balance_temp<<"("<<balance<<"->"<<balance_temp<<")"<<endl<<endl;
            cout<<"======================"<<endl;
            cout<<"======================"<<endl;
        }
        else{
            cout<<"$"<<balance_temp<<"("<<balance<<"->"<<balance_temp<<")"<<endl<<endl;
        }
        balance = balance_temp;
    }
    cout<<"all data printed"<<endl;
    //print out the report

    char save = 'y';
    cout<<"Save to file?[Y/N]"<<endl;
    cin>>save;
    if((save == 'Y')||(save == 'y')){
        fstream output_report ("report.txt", ios :: out);
        output_report<<"initial balance: "<<initial_balance<<endl<<endl;
        //save the inital balance to file

        balance = initial_balance;
        i = save_i;

        for (; i < input.get_array_size(); i++){
            int balance_temp = balance + input.get_amount(i);
            
            output_report<<"date:"<<input.get_year(i) << "/" << input.get_month(i)<<"/"<<input.get_date(i)<<endl;
            output_report<<"$"<<input.get_amount(i)<<endl;

            if (balance_temp<0){
                output_report<<"======================"<<endl;
                output_report<<"======================"<<endl;
                output_report<<"        WARNING       "<<endl;
                output_report<<"$"<<balance_temp<<"("<<balance<<"->"<<balance_temp<<")"<<endl<<endl;
                output_report<<"======================"<<endl;
                output_report<<"======================"<<endl;
            }
            else{
                output_report<<"$"<<balance_temp<<"("<<balance<<"->"<<balance_temp<<")"<<endl<<endl;
            }
            output_report<<endl;

            balance = balance_temp;
        }
        output_report<<"all data printed"<<endl;
    }
}

int main(void){
    Entry_Array data;

    bool quit = false;
    char read = 'Y';
    int option = 0;
    cout<<"Read from file?[Y/N]"<<endl;
    cout<<"=============WARNING============"<<endl;
    cout<<"May overwrite existed files "<<endl;
    cout<<"=============WARNING============"<<endl;
    cin >> read;
    if ((read != 'N')&&(read != 'n')){
        data = Read_From_Text();
    }
    
    while(!quit){
        cout<<"Choose the operation 1: add entry 2:overview 3:report balance 4:save 5:save & quit 6: don't save & quit"<<endl;
        cin >> option;
        switch (option){
            case 1:
                data.add_entry();
                break;
            case 2:
                Print_All_Entry(data);
                break;
            case 3:
                Report_Balance(data);
                break;
            case 4:
                Save_To_Text(data);
                break;
            case 5:
                cout<<"Are you sure?[Y/N]"<<endl;
                char sure;
                cin>>sure;
                if((sure == 'Y')||(sure == 'y')){
                    Save_To_Text(data);
                    quit = true;
                }
                break;
            case 6:
                cout<<"Are you sure? Type 'sure' to quit"<<endl;
                string sure_drop;
                cin>>sure_drop;
                if(sure_drop=="sure"){
                    quit = true;
                }
                break;
        }

    }
    //data = Read_From_Text();
    Print_All_Entry(data);
    //Save_To_Text(data);
    char wait;
    cin>>wait;  
    return 0;
}
