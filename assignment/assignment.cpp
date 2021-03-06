#include <iostream>
#include <cstring>

using namespace std;

class mystring
{
    char*  string;
    size_t length;
    int    id;
public:

    void setID (int id) { this->id = id; }
    int  getID ()       { return id; }

    mystring (const char* string){
        this->length = strlen(string) + 1;
        this->string = new char[length];
        strcpy (this->string, string);
    }

    const char* c_str (){
        return string;
    }

    void clear(){
        if(string != 0){
            cout << "deleting: " << id << endl;
            delete[] string;
            cout << "deleted: " << id << endl;
            string = 0;
        }
    }

    void swap(const mystring& right){
        this->string = right.string;
        this->length = right.length;
    }
    /** using strcpy:  
      * need an additional byte to store the \0, 
      * so always do something like new char[strlen(somestring)+1];. 
      * However, there is no need to manually add the \0; 
      * strcpy already does this.
      **/
    mystring (const mystring& right){
        length = right.length;
        char* temp = new char [length];        
        strcpy (temp, right.string);
        string = temp;
    }
    
    mystring& operator = (const mystring& right){
        // check self assignment
        if(this == &right)  
            return *this;    
        
        // make sure the state is not changed if exception occurs.
        // in this case exception can occur while new if memory is full
        
        char* temp = new char [strlen(right.string + 1)];       
        strcpy (temp,right.string);            
	 delete[] string;
        string = temp;

        // mystring tmp(right);
        // clear();
        // swap(right);

        return *this;
    }    

    virtual ~mystring(){
        cout << "~mystring()" << endl;
        //if(id != 1)
            clear();
    }
};

    // char* temp = new char [strlen(right.string + 1)];
        // delete[] string;
        // strcpy (temp,right.string);            
        // string = temp;

int main()
{
    // try{

        mystring str1 ("str1");
        str1.setID(1);
        mystring str2 ("str2");
        str2.setID(2);
        mystring str3 (str2);
        str3.setID(3);

        cout << "** before assignment **" << endl;
        cout << str1.c_str () << endl;
        cout << str2.c_str () << endl;    
        cout << str3.c_str () << endl;    
    
        mystring str = str1 = str2;
        str.setID(4);

        cout << "** after assignment **" << endl;
        cout << str1.c_str () << endl;
        cout << str2.c_str () << endl;
        cout << str.c_str  () << endl;
        
        cout << "done" << endl;
    // }catch(exception& ex){
    //     cout << "exception" << endl;
    //     cout << ex.what    () << endl;
    // }
    cout << "done final" << endl;
    return 1;
}
