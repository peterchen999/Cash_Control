#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

using namespace std;

class Entry{
    private:
        int amount;
        int year;
        int month;
        int date;
        string comment;

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

        string get_comment(void){
            return comment;
        }
        void Set_Entry(int a, int y, int m, int d, string c = ""){
            amount = a;
            year = y;
            month = m;
            date = d;
            comment = c;
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
    string get_comment(int id){
        return operating_array[id].get_comment();
    }

    void add_entry(void){
        int amount;
        int year;
        int month;
        int date;
        string comment;
        
        cout<<"amount: ";
        cin>>amount;
        cout<<"year: ";
        cin>>year;
        cout<<"month: ";
        cin>>month;
        cout<<"date: ";
        cin>>date;
        cout<<"comment: ";
        cin.ignore();
        getline(cin, comment);
    
        Entry new_entry;
        new_entry.Set_Entry(amount, year, month, date, comment);
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

            
        
        }
        cout<<"Successfully added an entry: "<<endl;
        cout<<year<<"/"<<month<<"/"<<date<<"      $"<<amount<<" comment: "<<comment<<endl;
    }

    void add_entry(int input_amount, int input_year, int input_month, int input_date, string input_comment){
        //adds entries with known input
        int amount = input_amount;
        int year = input_year;
        int month = input_month;
        int date = input_date;
        string comment = input_comment;
    
        Entry new_entry;
        new_entry.Set_Entry(amount, year, month, date, comment);
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

            
        
        }
        cout<<"Successfully added an entry: "<<endl;
        cout<<year<<"/"<<month<<"/"<<date<<"      $"<<amount<<" comment: "<<comment<<endl;
    }
    void add_monthly_entries(void){
        int starting_month; //the first month to start monthly entries
        int total_months; // the total months to repeat the entry
        int year;
        int date;
        int amount;
        string original_comment;
        
        cout<<"warning!! date should be less than 28"<<endl;
        cout<<"amount: ";
        cin>>amount;
        cout<<"starting year: ";
        cin>>year;
        cout<<"starting month: ";
        cin>>starting_month;
        cout<<"date: ";
        cin>>date;
        cout<<"total months: ";
        cin>>total_months;
        cout<<"comment: ";
        cin.ignore();
        getline(cin, original_comment);

        int current_month = starting_month;
        // the month to add entry

        for (int i = 0; i < total_months; i++){
            if (current_month > 12){
                //resolve current_month > 12
                year++;
                current_month = 1;
            }
            string comment = patch::to_string(year)+"/"+patch::to_string(current_month)+" "+original_comment;
            //to show the month and year corresponding to the entry
            add_entry(amount, year, current_month, date, comment);
            current_month++;
        }

    }

    // for manual input new entries
    void replace_entry(Entry input, int id){
        operating_array[id] = input;    
    }
    // to replace a specific entry
    void replace_entry(int id){
        //this function first deletes the replaced entry, then adds a new entry
        delete_entry(id);
        //deletes the replaced entry
        add_entry();
        
        cout<<"successfully modified"<<endl;
    }
    void append_entry(Entry input){
        operating_array[array_size] = input;
        array_size++;
    }
    // to append an entry onto an existed Entry_Array

    void delete_entry(int id){
        if (id >= array_size){
            cout << "invalid id"<<endl;
            return;
        }
        for (int i = id; i < array_size-1; i++){
            operating_array[i] = operating_array[i+1];
        }
        array_size--;
    }
    //to delete the specific entry
};



void Print_Entry(Entry_Array input, int id){
    cout<<"id: "<<id<<endl;
    cout<<"date: "<<input.get_year(id)<<"/"<<input.get_month(id)<<"/"<<input.get_date(id)<<endl;
    cout<<"amount: "<<input.get_amount(id)<<endl;
    cout<<"comment: "<<input.get_comment(id)<<endl;
    cout<<endl;
}//print out the content of id

void Print_All_Entry(Entry_Array input){
    int i = 0;
    for (; i < input.get_array_size(); i++){
        Print_Entry(input, i);
    }
}

void Save_To_Text(Entry_Array input){
    string file_name_temp = "-1";//the file name temp
    char file_name_default[10] = {'r', 'e', 's', 'u', 'l', 't', '.', 't', 'x', 't'};
    //rile_name_dafualt = result.txt
    char* file_name_temp2;

    cout<<"please enter the file name to be saved(for default, please enter -1)"<<endl;
    cin >> file_name_temp; //input the file name

    if (file_name_temp == "-1"){//test for default setting
        file_name_temp2 = file_name_default;
    }
    else{
        file_name_temp2 = &file_name_temp[0];
    }

    const char* file_name = file_name_temp2;//to copy the string into file_name

    std :: fstream ouput_text(file_name, ios :: out);
    ouput_text<<input.get_array_size()<<endl;
    for (int i = 0; i < input.get_array_size(); i++){
        ouput_text<<i<<endl;
        ouput_text<<input.get_amount(i)<<endl;
        ouput_text<<input.get_year(i)<<endl;
        ouput_text<<input.get_month(i)<<endl;
        ouput_text<<input.get_date(i)<<endl;
        ouput_text<<input.get_comment(i)<<endl;
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
    string c;//temp for comment;
    int crap;
    std :: fstream input_text("result.txt", ios :: in);

    string file_name_temp = "-1";//the file name temp
    char file_name_default[10] = {'r', 'e', 's', 'u', 'l', 't', '.', 't', 'x', 't'};
    //rile_name_dafualt = result.txt
    char* file_name_temp2;

    cout<< "name of file to be opened?(for default please type -1 to ignore)"<<endl;
    cin >> file_name_temp; //input the file name

    if (file_name_temp == "-1"){
        file_name_temp2 = file_name_default;
    }
    else{
        file_name_temp2 = &file_name_temp[0];
    }

    const char* file_name = file_name_temp2;//to copy the string into file_name

    std :: fstream input_text_customization(file_name, ios :: in);
    
    input_text>>input_size;

    for (int i = 0; i < input_size; i++){
        input_text>>crap;
        input_text>>a;
        input_text>>y;
        input_text>>m;
        input_text>>d;
        input_text>>c;
        temp.Set_Entry(a, y, m, d, c);
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
        string report_name;
        cout<<"Name of the report?"<<endl;
        cin>>report_name;
        report_name += ".txt";
        fstream output_report (report_name.c_str(), ios :: out);
        output_report<<"reported at: "<<year<<"/"<<month<<"/"<<date<<endl;
        output_report<<"initial balance: "<<initial_balance<<endl<<endl;
        //save the inital balance to file

        balance = initial_balance;
        i = save_i;

        for (; i < input.get_array_size(); i++){
            int balance_temp = balance + input.get_amount(i);
            
            output_report<<"date:"<<input.get_year(i) << "/" << input.get_month(i)<<"/"<<input.get_date(i)<<endl;
            output_report<<"comment: "<<input.get_comment(i)<<endl;
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
        output_report.close();
        cout<<"succesfully saved as "<<report_name<<endl;
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
        cout<<"Choose the operation 1: add entry 11: add monthly entry 2:modify entry 3: delete entry 4:overview 5:report balance 6:save 7:save & quit 8: don't save & quit"<<endl;
        cin >> option;
        switch (option){
            case 1:
                data.add_entry();
                break;
            case 11:
                data.add_monthly_entries();
                break;
            case 2:
                Print_All_Entry(data);
                int id;
                cout<<"the id of entry to be modified?"<<endl;
                cin>>id;
                data.replace_entry(id);
                break;
            case 3:
                Print_All_Entry(data);
                cout<<"the id of entry to be deleted?"<<endl;
                cout<<"(to cancel, please enter -1 )"<<endl;
                cin>>id;
                if (id == -1){
                    break;
                }
                data.delete_entry(id);
                break;
            case 4:
                Print_All_Entry(data);
                break;
            case 5:
                Report_Balance(data);
                break;
            case 6:
                Save_To_Text(data);
                break;
            case 7:
                cout<<"Are you sure?[Y/N]"<<endl;
                char sure;
                cin>>sure;
                if((sure == 'Y')||(sure == 'y')){
                    Save_To_Text(data);
                    quit = true;
                }
                break;
            case 8:
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
    //Print_All_Entry(data);
    //Save_To_Text(data);
    //char wait;
    //cin>>wait;  
    return 0;
}
