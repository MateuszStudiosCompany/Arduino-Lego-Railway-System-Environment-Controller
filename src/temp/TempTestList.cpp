#include <iostream>
#include <string>

using namespace std;

class ListTest{
    public:
        int a;
        ListTest *next = NULL;
};

class List{
    public:
        ListTest *first = NULL;

        void add(int a){
            ListTest *new_obj = new ListTest;
            new_obj->a = a;

            if(first == NULL){
                first = new_obj;
                return;
            }
            ListTest *pointer = first;
            while(pointer->next){
                pointer = pointer->next;
            }
            pointer->next = new_obj;
        }

        void view(){
            ListTest *pointer = first;
            cout << pointer->a << endl;
            while(pointer->next){
                pointer = pointer->next;
                cout << pointer->a << endl;
            }
            cout << "end\n";
        }
};

int main(){

    List lista;

    cout << "a\n";

    for(int i = 0; i < 10; i++){
        lista.add(i);
    }

    lista.view();
    
    

    return 0;
}