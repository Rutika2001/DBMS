#include<iostream>
#include<conio.h>
#include <vector>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include<cstring>
#include<algorithm>
using namespace std;

fstream schemafile;
void fetchSchema(string tableName, vector<string>& schema);
void convertToVector(string input,  vector<string>& v);


vector<string> split(const char* str, char c )
{
    vector<string> result;

    do
    {
        const char* begin = str;

        while (*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    return result;
}

//create//checked_working
void createTable(vector<string> cmd) {
    if(cmd.size() == 2) {
        cout<<"Table name is not mentioned"<<endl;
        return;
    }
    string table_name = cmd[2];
    int start = -1, end = -1, start_new = -1 ;
    for (int i = 3; i < cmd.size(); i++)
    {
        if (cmd[i] == "(")
        {
            start = i;
            start_new = i;
        }
        if (cmd[i] == ");")
        {
            end = i;
        }
    }

    if (start == -1 || end == -1)
    {
        cout << "Error: Check bracket and semicolon" << endl;
        return;
    }
   // if (cmd[end-1] != "int" && cmd[end - 1] != "char" && cmd[end-1] != "pk")
   if (cmd[end-1] != "int" && cmd[end - 1] != "char")
    {
        cout <<"___---> "<< cmd[end - 1]<<" <---___";
        cout << "\tError: Invalid Datatypes"<<endl;
        return;
    }
    //int status = 0;
    while (start < end - 1)
        {
            start++;
            if (cmd[start] == "," )
            {

                if (cmd[start - 1] != "int" && cmd[start - 1] != "char" )
                {
                    cout <<"___---> "<< cmd[start - 1]<<" <---___";
                    cout << "\tError: Invalid Datatypes"<<endl;
                    return;
                }

            }
    }
    /*if(status == 1){
        cout<<"Please recheck"<<endl;
        return;
    }*/

    fstream dataFile(table_name + ".txt", ios::in);

    if(dataFile)
    {
        std::cout<<"Table Already Exists!!!!"<<std::endl;
    }
    else{

        dataFile.close();
        schemafile.open("Schema.txt", ios::app);
        schemafile << table_name;

        while (start_new < end - 1)
        {
            start_new++;
            if (cmd[start_new] == "," )
            {

               /* if (cmd[start - 1] != "int" && cmd[start - 1] != "char" )
                {
                    cout <<"___---> "<< cmd[start - 1]<<" <---___";
                    cout << "\tError: Invalid Datatypes"<<endl;
                    return;
                }*/

            }
            else if (cmd[start_new] != ",")
            {
                schemafile << "#" << cmd[start_new];
            }
        }
        schemafile << endl;

        dataFile.open(table_name + ".txt", ios::out);
        cout << "Table created successfully" << endl;

        schemafile.close();
    }
}

//Drop Table//checked_working
void dropTable(vector<string> cmd) {

    if(cmd.size() == 2) {
        cout<<"Table name is not mentioned"<<endl;
        return;
    }
    schemafile.open("Schema.txt", ios::in);

    string table_name = cmd[2];

        /*string line1;

        while (getline(schemafile, line1))
        {
            string l1 = line1.substr(0, line1.find('#'));
            if (table_name != l1)
            {
                cout<<"Table Not Found !!"<<endl;
                return;
            }
        }*/


        fstream temp;
        temp.open("temp.txt", ios::out);
        bool flag = false;
        string line;
        while (getline(schemafile, line))
            {
                string l1 = line.substr(0, line.find('#'));

                if (table_name == l1)
                    {
                        flag = true;
                    }
                 if (table_name != l1)
                    {
                        temp << line << endl;
                    }
            }

            schemafile.close();
            temp.close();
            if(flag){
            remove("Schema.txt");
            rename("temp.txt", "Schema.txt");

            //table_name = cmd[2];
            table_name += ".txt";
            const char *c = table_name.c_str();
            cout<<"File Name: ---> "<<c<<" <--- is deleted..."<<endl;
            remove(c);
            cout << "Table dropped successfully" << endl;
            }
            else{
                table_name += ".txt";
                const char *c = table_name.c_str();
                cout<<"File Name: ---> "<<c<<" <--- is not found..."<<endl;
                remove("temp.txt");
               rename("temp.txt", "Schema.txt");

            }


}


//Truncate Table//checked_working
void truncateTable(vector<string> cmd) {
    if(cmd.size() == 2) {
        cout<<"Table name is not mentioned"<<endl;
        return;
    }

    string table_name = cmd[2];

    fstream dataFile(table_name + ".txt", ios::in);

    if(!dataFile)
    {
        std::cout<<"No Table Found!!!!"<<std::endl;
    }
    /*
    string line1;

    while (getline(schemafile, line1))
    {
        string l1 = line1.substr(0, line1.find('#'));
        if (table_name != l1)
        {
            cout<<"Table Not Found !!"<<endl;
            return;
        }
     }*/

    else{

        dataFile.close();
        table_name += ".txt";
        const char *c = table_name.c_str();
        remove(c);

        fstream table;
        table.open(table_name, ios::app);

        cout << "Table trancate successfully" << endl;
    }

}

//Describe//checked_working
void describe(vector<string> cmd) {
    schemafile.open("Schema.txt", ios::in);

    if (cmd.size() > 1)
    {
        string table_name = cmd[1];
        fstream dataFile(table_name + ".txt", ios::in);

        if(!dataFile)
        {
            cout<<"No Table Found!!!!"<<endl;
        }
        else{
                string line;

                while (getline(schemafile, line))
                {
                    string l1 = line.substr(0, line.find('#'));

                    if (table_name == l1)
                    {
                        string l2 = line.substr(line.find('#') + 1, line.size());
                        int cnt = 1;

                        for (auto i : l2)
                        {
                            if (i == '#')
                            {
                                if (cnt % 2 != 0)
                                {
                                    cout << " --> ";
                                }
                                else
                                {
                                    cout << endl;
                                }
                                cnt++;
                            }
                            else
                            {
                                cout << i;
                            }
                        }
                    }
                }
            }
        }


    else
    {
        cout << "Mention Table Name:" << endl;
    }
    schemafile.close();
}

//Insert//checked_working
void insert_into(vector<string> cmd) {
    string table_name = cmd[2];


    fstream dataFile(table_name + ".txt", ios::in);

    if(!dataFile)
    {
        std::cout<<"No Table Found!!!!"<<std::endl;
    }
    else{
        fstream table;
        string line;
        table.open(table_name + ".txt", ios::app);
        stringstream fs;
        schemafile.open("Schema.txt", ios::in);
        vector<string> types;
            while (getline(schemafile, line))
            {
                string l1 = line.substr(0, line.find('#'));


                if (l1 == table_name)
                {
                    string l2 = line.substr(line.find('#')+1,line.size());
                    int cnt = 1;
                    stringstream ss;
                    ss << l2;
                    string s;
                    while (getline(ss, s, '#')) {
                        if (cnt % 2 == 0)
                        {
                            cout << s << endl;
                            types.push_back(s);
                        }
                        cnt++;
                    }
                }
            }
            schemafile.close();
            int start = -1, end = -1;
            for (int i = 3; i < cmd.size(); i++)
            {
                if (cmd[i] == "(")
                {
                    start = i;
                }
                if (cmd[i] == ");")
                {
                    end = i;
                }
            }
            if (start == -1 || end == -1)
            {
                cout << "Error: Check bracket and semicolon" << endl;
                return;
            }
            int cnt = 0;
            while (start < end - 1)
            {
                start++;

                if (cmd[start] != ",")
                {
                    cout << cmd[start] << endl;
                    if (types[cnt] == "char")
                    {

                        int len = cmd[start].length();

                        //cout <<"Index used by Input String: " <<cmd[start].find("'") << " ---> ";
                        //cout << cmd[start].find("'", 1) << endl;

                        if (cmd[start].find("'") != 0 || cmd[start].find("'", 1) != len-1)
                        {
                            cout << "ERROR:: Data_Type Mismatch --> Char must have quotes" << endl<<endl;
                            return;
                        }
                    }
                    if (types[cnt] == "int")
                    {
                        for (int j = 0; j < cmd[start].length(); j++)
                        {
                            if (!isdigit(cmd[start][j]))
                            {
                                cout << "ERROR:: Data_Type Mismatch --> int must have numerical values!" << endl<<endl;
                                return;
                            }
                        }
                    }

                    //PRIMARY KEY
                    /*if (types[cnt] == "pk")
                    {
                        string line;
                        while (getline(dataFile, line))
                        {
                            string l1 = line.substr(0, line.find('#'));

                            for (int j = 0; j < cmd[start].length(); j++)
                            {

                                if(cmd[start][j] = stoi(l1)){
                                    cout<<"Error:: Primary Key is already used... "<<endl<<endl;
                                    return;
                                }

                                if (!isdigit(cmd[start][j]))
                                {
                                    cout << "ERROR:: Data_Type Mismatch --> int must have numerical values!" << endl<<endl;
                                    return;
                            }
                        }
                    }

                    }*/
                    fs << cmd[start];
                    cnt++;
                    if (start != end - 1)
                    {
                        fs << "#";
                    }
                    else
                    {
                        fs << "\n";
                    }
                }
            }
            table <<fs.str();
            cout << "Row inserted successfully" << endl;
        }


}

//Update//checked_working
void update(vector<string> cmd) {
    vector<string> schema;
    fetchSchema(cmd[1], schema);
    int count = 0;
    string colname = cmd[3];
    string newval = cmd[5];
    if (!schema.empty())
    {
        int k = 0;
        if (cmd.size() == 3)
        {
            string table = cmd[1] + ".txt";
            char* c = new char[table.size() + 1];
            strcpy(c, table.c_str());
            remove(c);
        }
        else if (cmd[6] == "where")
        {
            string table_name = cmd[1];
            fstream table;
            fstream schem;
            schem.open("Schema.txt");
            string line2;

            vector<string> lineVec1;
            while (getline(schem, line2))
            {
                string l2 = line2.substr(0 , line2.find("#"));

                if (l2 == table_name)
                {
                    stringstream ss(line2);
                    while (ss.good())
                    {
                        string substr;
                        getline(ss, substr, '#');
                        lineVec1.push_back(substr);
                    }
                }
            }
            int index = -1;
            for (int i = 1; i < lineVec1.size(); i+=2)
            {
               // cout << lineVec[i]<<endl;
                index++;
                if (lineVec1[i] == colname)
                {
                    break;
                }
                   // break;
            }
            table.open(table_name + ".txt", ios::in);
            string line;

            int i, j;
            j = 0;
            int flag = 0;


            fstream temp;


            temp.open("temp.txt", ios::out);
            vector<string> lineVec;
            while (getline(table, line))
            {
                //  vector<int> flags = where_(cmd, 1, table_name);
                stringstream ss(line);
                while (ss.good())
                {
                    string substr;
                    getline(ss, substr, '#');
                    lineVec.push_back(substr);
                }

                for (i = 1; i < schema.size(); i += 2)
                {
                    if (cmd[7] == schema[i])
                    {
                        if (cmd[8] == "=")
                        {
                            if (cmd[9] == lineVec[j])
                            {
                                flag = 1;
                                count++;

                            }
                        }
                        if (cmd[8] == ">")
                        {
                            if (lineVec[j] > cmd[9])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[8] == "<")
                        {
                            if (lineVec[j] < cmd[9])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[8] == ">=")
                        {
                            if (lineVec[j] >= cmd[9])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[8] == "<=")
                        {
                            if (lineVec[j] <= cmd[9])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[8] == "!=")
                        {
                            if (cmd[9] != lineVec[j])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                    }
                    j++;
                }
                if (flag != 1)
                {
                    temp << line << endl;
                }
                else
                {
                    vector<string> l4;
                    stringstream ss(line);
                    while (ss.good())
                    {
                        string substr;
                        getline(ss, substr, '#');
                        l4.push_back(substr);
                    }

                    for (int i = 0; i < l4.size(); i++)
                    {
                        if (i != index)
                        {

                            if (i == l4.size() - 1)
                                temp << l4[i]<< endl;
                            else
                                temp << l4[i] << "#";
                        }
                        else
                        {
                            if (i == l4.size() - 1)
                                temp << newval << endl;
                            else
                                temp << newval << "#";
                        }
                    }

                }
                flag = 0;
            }
            table.close();
            temp.close();
            string table1 = table_name + ".txt";
            char* c = new char[table1.size() + 1];
            //char c[table1.size() + 1];
            strcpy(c, table1.c_str());
            remove(c);
            rename("temp.txt", c);
        }
        cout << "\n____ROWS UPDATED_____\n" << endl;
    }
}

// Delete//checked_working
void delete_(vector<string> cmd) {

    vector<string> schema;
    fetchSchema(cmd[2], schema);
    int count = 0;

    if (!schema.empty())
    {
        int k = 0;
        if (cmd.size() == 3)
        {
            string table = cmd[1] + ".txt";
            char* c = new char[table.size() + 1];
           // char c[];
            strcpy(c, table.c_str());
            remove(c);
        }
        else if (cmd[3] == "where")
        {
            string table_name = cmd[2];
            fstream table;
            table.open(table_name + ".txt", ios::in);
            string line;

            int i, j;
            j = 0;
            int flag = 0;
            vector<string> lineVec;

            fstream temp;
            temp.open("temp.txt", ios::out);

            while (getline(table, line))
            {
              //  vector<int> flags = where_(cmd, 1, table_name);
                stringstream ss(line);
                while (ss.good())
                {
                    string substr;
                    getline(ss, substr, '#');
                    lineVec.push_back(substr);
                }

                for (i = 1; i < schema.size(); i += 2)
                {
                    if (cmd[4] == schema[i])
                    {
                        if (cmd[5] == "=")
                        {
                            if (cmd[6] == lineVec[j])
                            {
                                flag = 1;
                                count++;

                            }
                        }
                        if (cmd[5] == ">")
                        {
                            if (lineVec[j] > cmd[6])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[5] == "<")
                        {
                            if (lineVec[j] < cmd[6])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[5] == ">=")
                        {
                            if (lineVec[j] >= cmd[6])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[5] == "<=")
                        {
                            if (lineVec[j] <= cmd[6])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[5] == "!=")
                        {
                            if (cmd[6] != lineVec[j])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                    }
                    j++;
                }
                if (flag != 1)
                {
                    temp << line << endl;
                }
                flag = 0;
            }
            table.close();
            temp.close();
            string table1 = table_name + ".txt";
            char* c = new char[table1.size() + 1];
            //char c[table1.size() + 1];
            strcpy(c, table1.c_str());
            remove(c);
            rename("temp.txt", c);
        }
        cout << "\n____ROWS DELETED____\n" << endl;
    }
}

// Select//checked_working
void select(vector<string> cmd) {

    fstream table;
    string line;
    string table_name;
    table_name = cmd[3];
    //cout << cmd.size() << endl;
    if (cmd[1] == "*")
    {
        if (cmd.size() == 5)
        {
            table.open(table_name + ".txt", ios::in);
            while (getline(table, line))
            {
                replace(line.begin(), line.end(), '#', ' ');
                cout << line << endl;
            }
        }

        else if (cmd[4] == "where")
        {
            int count = 0;
            vector<string> schema;
            fetchSchema(table_name, schema);
            table.open(table_name + ".txt", ios::in);
            string line;

            int i, j;
            j = 0;
            int flag = 0;
            vector<string> lineVec;

            fstream temp;
            temp.open("temp.txt", ios::out);

            while (getline(table, line))
            {
                //  vector<int> flags = where_(cmd, 1, table_name);
                stringstream ss(line);
                while (ss.good())
                {
                    string substr;
                    getline(ss, substr, '#');
                    lineVec.push_back(substr);
                }

                for (i = 1; i < schema.size(); i += 2)
                {
                    if (cmd[5] == schema[i])
                    {
                        if (cmd[6] == "=")
                        {
                            if (cmd[7] == lineVec[j])
                            {
                                flag = 1;
                                count++;

                            }
                        }
                        if (cmd[6] == ">")
                        {
                            if (lineVec[j] > cmd[7])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[6] == "<")
                        {
                            if (lineVec[j] < cmd[7])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[6] == ">=")
                        {
                            if (lineVec[j] >= cmd[7])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[6] == "<=")
                        {
                            if (lineVec[j] <= cmd[7])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[6] == "!=")
                        {
                            if (cmd[7] != lineVec[j])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                    }
                    j++;
                }
                if (flag == 1)
                {
                    cout << line << endl;
                }
                flag = 0;
            }
        }
    }

    else
    {
         string colname = cmd[1];
         fstream schem;
    //   fetchSchema(table_name, schem);
         vector<string> lineVec1;
             string line2;
             schem.open("Schema.txt");
         while (getline(schem, line2))
         {
             string l2 = line2.substr(0, line2.find("#"));

                 if (l2 == table_name)
                  {
              stringstream ss(line2);
              while (ss.good())
            {
                string substr;
                getline(ss, substr, '#');
                lineVec1.push_back(substr);
            }
        }
    }
    int index = -1;
    for (int i = 1; i < lineVec1.size(); i += 2)
    {
        index++;
        if (lineVec1[i] == colname)
            break;
    }
        if (cmd.size() == 4)
        {


            table.open(table_name + ".txt", ios::in);
            while (getline(table, line))
            {
                replace(line.begin(), line.end(), '#', ' ');
                vector<string> data;
                convertToVector(line, data);
                for (int i = 0; i < data.size(); i++)
                {
                    if (i == index)
                        cout << data[i]<<endl;
                }

            //    replace(line.begin(), line.end(), '#', ' ');
            //    cout << line << endl;
            }
        }

        else if (cmd[4] == "where")
        {
            int count = 0;
            vector<string> schema;
            fetchSchema(table_name, schema);
            table.open(table_name + ".txt", ios::in);
            string line;

            int i, j;
            j = 0;
            int flag = 0;
            vector<string> lineVec;

            fstream temp;
            temp.open("temp.txt", ios::out);

            while (getline(table, line))
            {
                //  vector<int> flags = where_(cmd, 1, table_name);
                stringstream ss(line);
                while (ss.good())
                {
                    string substr;
                    getline(ss, substr, '#');
                    lineVec.push_back(substr);
                }

                for (i = 1; i < schema.size(); i += 2)
                {
                    if (cmd[5] == schema[i])
                    {
                        if (cmd[6] == "=")
                        {
                            if (cmd[7] == lineVec[j])
                            {
                                flag = 1;
                                count++;

                            }
                        }
                        if (cmd[6] == ">")
                        {
                            if (lineVec[j] > cmd[7])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[6] == "<")
                        {
                            if (lineVec[j] < cmd[7])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[6] == ">=")
                        {
                            if (lineVec[j] >= cmd[7])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[6] == "<=")
                        {
                            if (lineVec[j] <= cmd[7])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                        if (cmd[6] == "!=")
                        {
                            if (cmd[7] != lineVec[j])
                            {
                                flag = 1;
                                count++;
                            }
                        }
                    }
                    j++;
                }
                if (flag == 1)
                {

                        replace(line.begin(), line.end(), '#', ' ');
                        vector<string> data;
                        convertToVector(line, data);
                        for (int i = 0; i < data.size(); i++)
                        {
                            if (i == index)
                                cout << data[i] << endl;
                        }

                        //    replace(line.begin(), line.end(), '#', ' ');
                        //    cout << line << endl;

                }
                flag = 0;
            }
        }
    }
}

// Help to know the tables
void helpTable() {
    string line;

    schemafile.open("Schema.txt");

    int count = 0;
    while (getline(schemafile, line))
    {
        string l1 = line.substr(0, line.find('#'));
        cout << l1 << endl;
        count++;
    }
    if (!count)
    {
        cout << "No tables found" << endl;
    }
}

// Help for Commands
void helpCmd(vector<string> cmd) {
    cout << "\n------------HELP----------------" << endl;
    int choice=0;

    cout<<"\t\t1. CREATE TABLE\n\t\t2. DROP TABLE\n\t\t3. SELECT\n\t\t4. INSERT\n\t\t5. DELETE\n\t\t6. UPDATE\n\t\t7. DESCRIBE\n\t\t8. HELP TABLES\n\t\t9. HELP CMD\n\t\t10. TRUNCATE\n\t\t11. QUIT"<<endl;
    cout<<"Enter your Choice: ";
    bool flag = true;
    while(flag){
    cout<<"\t\t1. CREATE TABLE\n\t\t2. DROP TABLE\n\t\t3. SELECT\n\t\t4. INSERT\n\t\t5. DELETE\n\t\t6. UPDATE\n\t\t7. DESCRIBE\n\t\t8. HELP TABLES\n\t\t9. HELP CMD\n\t\t10. TRUNCATE\n\t\t11. QUIT"<<endl;
    cout<<"Enter your Choice: ";
    cin>>choice;
    switch (choice)
    {
    case 1:

        cout << "\nCommand : CREATE TABLE" << endl;
        cout << "Info: Creates a new table" << endl;
        cout << "\nFormat: \nCREATE TABLE table_name ( attribute_1 attribute1_type CHECK (constraint1) , attribute_2 attribute2_type, …);" << endl;
        break;

    case 2:
        cout << "\nCommand : DROP TABLE" << endl;
        cout << "Info: Removes table defination" << endl;
        cout << "\nFormat: \nDROP TABLE table_name;" << endl;
        break;

    case 3:
        cout << "\nCommand : SELECT" << endl;
        cout << "Info: Extracts data from a database" << endl;
        cout << "\nFormat: \nSELECT attribute_list FROM table_list WHERE condition_list;" << endl;
        break;

    case 4:
        cout << "\nCommand : INSERT" << endl;
        cout << "Info: Inserts new data into a database" << endl;
        cout << "\nFormat: \nINSERT INTO table_name VALUES ( val1, val2, ... );" << endl;
        break;

    case 5:
        cout << "\nCommand : DELETE" << endl;
        cout << "Info: Deletes data from a database" << endl;
        cout << "\nFormat: \nDELETE FROM table_name WHERE condition_list;" << endl;
        break;

    case 6:
        cout << "\nCommand : UPDATE" << endl;
        cout << "Info: Updates data in a database" << endl;
        cout << "\nFormat: \nUPDATE table_name SET attr1 = val1, attr2 = val2… WHERE condition_list;" << endl;
        break;

    case 7:
        cout << "\nCommand : DESCRIBE" << endl;
        cout << "Info: DESCRIBE Describes the schema of table T_NAME" << endl;
        cout << "\nFormat: \nDESCRIBE table_name;" << endl;
        break;

    case 8:
        cout << "\nCommand : HELP_TABLE" << endl;
        cout << "Info: The output will be the list of tables in the database, with one row per table name." << endl;
        cout<<"\tIfthere are no tables in the database, you should print the message “No tables found”.\n";
        break;
    case 9:
        cout<<"The output will be a short description of the corresponding command and it's expected format."<<std::endl;
        break;
    case 10:
        cout << "Info: Removes all rows from table." << endl;
        cout << "Syntax: TRUNCATE table table_name ;" << endl;
        break;
    case 11:
        flag = false;
        break;
    default:
        cout << "Syntax Error";
        }
    }
}

void altertable(vector<string> cmd){
    string table_name = cmd[2];
    cout << table_name << endl;
    fstream dataFile(table_name + ".txt", ios::in);

    if(dataFile)
    {
        dataFile.close();
        dataFile.open(table_name, ios::in);
        cout << "went through this if" << endl;
    }
    else
    {
        std::cout<<"ERROR: NO SUCH TABLE!"<<std::endl<<std::endl;
        return;
    }

    cout << " out of it" << endl;
    string new_column = cmd[cmd.size() - 3];
    string new_datatype = cmd[cmd.size() - 2];
    cout << new_column << endl;
    cout << new_datatype << endl;
   // string::iterator itr = new_datatype.end();
    // new_datatype.erase(itr - 1, itr);

    schemafile.close();
    schemafile.open("Schema.txt", ios::in);
     cout << "before row vector" << endl;
    vector<string> row_vector;

    string line;

    while(!schemafile.eof())
    {
        getline(schemafile, line);

        if(line.substr(0, table_name.length()) == table_name)
            row_vector.push_back(line);
    }
    cout << "after while schema file" << endl;
    string new_record = table_name + "#" + new_column + "#" + new_datatype;

    row_vector.push_back(new_record);

    schemafile.close();

    schemafile.open("Schema.txt", ios::in);

    fstream schema_new("Schema_new.txt", ios::app);

    while(!schemafile.eof())
    {

        getline(schemafile, line);

        if(line.substr(0, table_name.length()) == table_name || line == "")
            continue;

        schema_new << line << std::endl;
    }
    cout << "after second schema file while" << endl;
    for(int i = 0; i < row_vector.size(); i++)
    {
        schema_new << row_vector[i] << std::endl;
    }

    schema_new.close();
    schemafile.close();

    remove("Schema.txt");
    rename("Schema_new.txt", "Schema.txt");


    fstream dataFile_new;

    dataFile.close();
    dataFile.open(table_name, std::ios::in);
    dataFile_new.open(table_name + "_new.txt", std::ios::out);

    getline(dataFile, line);
    line += new_column + "#";
    dataFile_new <<line<<std::endl;
    cout << "hmm iske bahar nikale dikhao" << endl;
//    while(!dataFile.eof())
//    {s
//        getline(dataFile, line);
//        if(line == "")
//            continue;
//        line += "null#";
//        dataFile_new << line <<std::endl;
//    }
    cout << "accha to yahi nahi aare kya aap" << endl;

    dataFile_new.close();
    dataFile.close();

    remove(table_name.c_str());
    rename((table_name + "_new").c_str(), table_name.c_str());
}


void convertToVector(string input, vector<string>& v) {
    string word = "";
    for (auto x : input)
    {
        if (x == ' ')
        {
            v.push_back(word);
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    v.push_back(word);
}

void fetchSchema(string tableName, vector<string>& schema) {
    schemafile.open("Schema.txt", ios::in);
    string line;
    int flag = 0;

    while (getline(schemafile, line))
    {
        string l1 = line.substr(0, line.find('#'));
        //cout << l1;
        if (tableName == l1)
        {
            flag = 1;
            stringstream ss(line);

            while (ss.good())
            {
                string substr;
                getline(ss, substr, '#');
                schema.push_back(substr);
            }
            break;
        }
    }

    if (flag == 0)
    {
        cout << "Table not found" << endl;
    }

    schemafile.close();
}

void handleCmd(vector<string> cmd) {
     //Create table
    if (cmd[0] == "create" && cmd[1] == "table")
    {
        createTable(cmd);
    }
    //Drop table
    else if (cmd[0] == "drop" && cmd[1] == "table")
    {
        dropTable(cmd);
    }
    // Help table
    else if (cmd[0] == "help" && cmd[1] == "table")
    {
        helpTable();
    }
    // Help command
    else if (cmd[0] == "help" && cmd[1] == "command")
    {
        helpCmd(cmd);
    }
    //Insert Into
    else if (cmd[0] == "insert" && cmd[1] == "into")
    {
        insert_into(cmd);
    }
    // Describe
    else if (cmd[0] == "describe")
    {
        describe(cmd);
    }
    // Select
    else if (cmd[0] == "select") {
        select(cmd);
    }
    // Delete
    else if (cmd[0] == "delete" && cmd[1] == "from")
    {
        delete_(cmd);
    }
    // Update
    else if (cmd[0] == "update" && cmd[2] == "set") {
        update(cmd);
    }
    // Trancate
    else if (cmd[0] == "truncate" && cmd[1] == "table") {
        truncateTable(cmd);
    }
    // alter
    else if (cmd[0] == "alter" && cmd[1] == "table") {
        altertable(cmd);
    }
    else
    {
        cout << "Syntax Error (Wrong command)";
    }
}

int main() {
 vector<string> cmd;
    string input;
    cout<<"_______________________________________________________!!!WELCOME!!!________________________________________________"<<endl<<endl;
    cout<<"_______________________________________________________TY-GROUP 47__________________________________________________"<<endl<<endl;
    //cout<<"____MENU___"<<endl;
    //cout<<"1. CREATE TABLE\n2. DROP TABLE\n3. DESCRIBE\n4. INSERT\n5. DELETE\n6. UPDATE\n7. SELECT\n8. HELP TABLES\n9. HELP CMD\n10. QUIT"<<endl;
    cout<<"\nEnter your Command: ";
    getline(cin, input);
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    //cout<<input;
    while (input != "Quit") {
        convertToVector(input, cmd);
        handleCmd(cmd);
        cmd.clear();
        cout<<endl;
        //cout<<"\t\t1. CREATE TABLE\n\t\t2. DROP TABLE\n\t\t3. DESCRIBE\n\t\t4. INSERT\n\t\t5. DELETE\n\t\t6. UPDATE\n\t\t7. SELECT\n\t\t8. HELP TABLES\n\t\t9. HELP CMD\n\t\t10. QUIT"<<endl;
        cout<<"\nEnter your Command: ";
        getline(cin, input);
    }
}
