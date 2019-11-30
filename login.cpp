#include <iostream>
#include <fstream>
#include <string>
using  namespace std;
bool usercheck=false;
int authenticate(const std::string &username, const std::string &password) {
    std::ifstream file("authdata.txt");
    std::string fusername, fpassword;

    while (file) {
        std::getline(file, fusername, ';'); // use ; as delimiter
        std::getline(file, fpassword); // use line end as delimiter
        // remember - delimiter readed from input but not added to output
        if ((fusername.compare(username)==0) && (fpassword.compare(password)==0))
            {
                cerr<<"login successful\n";
                return 1;

            }
    }

    cout<<"login unsuccessful\n";
    return 0;
}
string duplicateusercheck(){
    std::string username;
    std::string fusername, fpassword;
    std::cout<<"Enter username\n";
    std::cin >> username;
    std::ifstream file("authdata.txt");
    while (file) {
        std::getline(file, fusername, ';');
        std::getline(file, fpassword); // use line end as delimiter

       // cout<<"username from file" <<fusername <<"\n";
        if(fusername.compare(username)==0 || fusername.compare("error")==0) {
            file.close();
            username = duplicateusercheck();
            //std::cout<<"Enter username\n";
            //std::cin >> username;
        }
    }
    file.close();
    return username;
}
void signup(){
    std::string username, password;
    std::cout<<"Sign up now\n";
    username = duplicateusercheck();
    std::cout<<"Enter password\n";
    std::cin>>password;

    ofstream myfile;
    myfile.open ("authdata.txt",std::ios_base::app);
    myfile << username <<";"<<password<<"\n";
    myfile.close();
}

string userlogin(int buf) {
    std::string username, password;
    //std::cout<<"\t \t Enter your buf: \n"<<"\t \t \t 1 for sign in\n"<<"\t \t \t 2 for sign up\n";
    if(buf==2){
        signup();
        std::cout<<"Enter username and password to login: \n";
        std::cin >> username >> password;
        if(authenticate(username, password)) return username;
    }
    else if(buf==1){
        std::cout<<"Enter username and password to login: \n";
        std::cin >> username >> password;
        if(authenticate(username, password)) return username;
    }
    else {
        cout<<"try again and choose right option ";
        return "error";
    }
    return "error";
}
void display(string message){

}
