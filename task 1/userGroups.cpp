#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <sstream>
using namespace std;

class User{
    int id_ = 0;
    int inGroupId_ = 0;
public:
    User(int id) : id_(id){cout << "user " <<id_<< " constr" << endl;}
    User(int id, int grId) : id_(id), inGroupId_(grId){cout << "user " <<id_<< " constr" << endl;}
    int getId(){
        return id_;
    }
    int getGroupId(){
        return inGroupId_;
    }
    void addToGroup(int id){
        inGroupId_ = id;
    }
    ~User(){cout << "user " <<id_<< " destr" << endl;}
};

vector<shared_ptr<User>> allUsers;

class Group{
    int id_;
    vector<shared_ptr<User>> usersOfGroup;
public:
    int getId(){
        return id_;
    }
    Group(int gId) : id_(gId){cout << "group " << id_  << " constr" << endl;}
    void deleteUserFromGroup(int id){
        if(usersOfGroup.empty()){
            return;
        }
        for (int i = 0; i < usersOfGroup.size(); i++){
            if (usersOfGroup[i]->getId() == id){
                usersOfGroup.erase(usersOfGroup.begin()+i);
            }
        }
    }
    void addUserToGroup(shared_ptr<User>& us);
    vector<int> getIdsUsersOfGroup(){
        vector<int> vec;
        for (auto& elem: usersOfGroup){
            vec.push_back(elem->getId());
        }
        return vec;
    }
    void printUsersOfGroup(){
        cout << "Пользователи группы " << id_ << ": ";
        for (auto &elem: usersOfGroup){
            cout << elem->getId() << " ";
        }
        cout << endl;
    }
    ~Group(){
        cout <<"group " <<id_<< " destr" << endl;
    }
};


vector<shared_ptr<Group>> allGroups;

void printAllGroups(vector<shared_ptr<Group>> vec = allGroups){
    cout << "Вывод групп: ";
    for (auto &elem : vec){
        cout << "Группа " << elem->getId() << "; ";
        elem->printUsersOfGroup();
    }
    cout << endl;
}

void printAllUsers(vector<shared_ptr<User>> vec = allUsers){
    cout << "Вывод пользователей: ";
    for (auto &elem : vec){
        if (elem -> getGroupId() != 0){
            cout << "Пользователь " << elem->getId() << " в группе " << elem -> getGroupId() << "; ";
        }
        else{
            cout << "Пользователь " << elem->getId() << " не в группе" << "; ";
        }
    }
    cout << endl;
}


void Group::addUserToGroup(shared_ptr<User>& us){
    if (us->getGroupId() == 0){
        cout << "В группу " << id_ << " добавлен пользователь " << us->getId() << endl;
        usersOfGroup.push_back(us);
        us->addToGroup(id_);
    }
    else{
        throw logic_error("Пользователь уже состоит в группе");
    }
}

void createGroup(int id){
    for (int i = 0; i < allGroups.size(); i++){
        if (allGroups[i]->getId() == id){
            throw logic_error("Уже существует группа с таким ID");
            return;
        }
    }
    shared_ptr<Group> newGroup = make_shared<Group>(id);
    allGroups.push_back(newGroup);
    cout << "Создана группа с ID " << id << endl;
    return;
}

void createUser(int id){
    for (int i = 0; i < allUsers.size(); i++){
        if (allUsers[i]->getId() == id){
            throw logic_error("Уже существует пользователь с таким ID");
            return;
        } 
    }
    shared_ptr<User>&& newUs = make_shared<User>(id);
    // cout << "Shared_ptr.use_count1 = " << newUs.use_count() << endl;
    allUsers.push_back(move(newUs));
    cout << "Создан пользователь с ID " << id << endl;
    // cout << "Shared_ptr.use_count2 = " << newUs.use_count() << endl;

    return;
}

void createUser(int id, int grId){
    for (int i = 0; i < allUsers.size(); i++){
        if (allUsers[i]->getId() == id){
            throw exception();
            return;
        }
    }
    bool groupExists = false;
    int groupIndex;
    for (int i = 0; i < allGroups.size(); i++){
        if (allGroups[i]->getId() == grId){
            groupExists = true;
            groupIndex = i;
        }
    }
    if (!groupExists){
        throw logic_error("");
        return;
    }
    shared_ptr<User>&& newUs = make_shared<User>(id);
    allGroups[groupIndex]->addUserToGroup(newUs);
    allUsers.push_back(move(newUs));
    cout << "Создан пользователь с ID " << id << endl;
}

void getUser(int id){
    bool exists = false;
    for (auto& elem: allUsers){
        if (elem->getId() == id){
            exists = true;
            cout << "Пользователь " << elem -> getId();
            if (elem ->getGroupId() != 0){
                cout << " состоит в группе " << elem->getGroupId() << endl;
            }
            else{
                cout<< " не состоит в группе" << endl;
            }
            // cout << "Shared_ptr.use_count = " << elem.use_count() << endl;
        }
    }
    if (!exists){
        cout << "Пользователь с таким ID не найден" << endl;
    }
}

void getGroup(int id){
    bool exists = false;
    for (auto &elem: allGroups){
        if (elem -> getId() == id){
            exists = true;
            elem->printUsersOfGroup();
        }
    }
    if (!exists){
        cout << "Группа с таким ID не найдена" << endl;
    }
}

void deleteUserFromAllUsers(int id){
    bool exists = false;
    for (int i = 0; (i < allUsers.size()) && exists == false ; i++){
        if (allUsers[i]->getId() == id){
            exists = true;
            int groupId = allUsers[i]->getGroupId();
            for (auto &elem: allGroups){
                if (elem -> getId() == groupId){
                    elem->deleteUserFromGroup(id);
                }
            }
            allUsers.erase(allUsers.begin()+i);
            cout << "Пользователь " << id << " удалён" << endl;
        }
    }
    if (!exists){
        cout << "Пользователь с таким ID не найден" << endl;
    }
}


void deleteGroupFromAllGroups(int id){
    bool exists = false;
    for (int i = 0; (i < allGroups.size()) && exists == false ; i++){
        if (allGroups[i]->getId() == id){
            exists = true;
            auto usersOfGroup = allGroups[i]->getIdsUsersOfGroup();
            for (auto elem: usersOfGroup){
                deleteUserFromAllUsers(elem);
            }
            allGroups.erase(allGroups.begin()+i);
            cout << "Группа " << id << " удалена" << endl;
        }
    }
    if (!exists){
        cout << "Группа с таким ID не найдена" << endl;
    }
}

vector<string> splitBySpaces(string& line){
    istringstream iss(line);
    vector<string> words;
    string word;

    while(iss >> word){
        words.push_back(word);
    }
    return words;
}



int main(){
    string buffer;
    cout << "> ";
    while(getline(cin,buffer)){
        if (buffer.empty()){
            cout << "> ";
            continue;
        }
        vector<string> words = splitBySpaces(buffer);
        if (words.empty()){
            cout << "> ";
            continue;
        };
        if (words[0] == "man"){
            cout << "Commands: " << endl;
            cout << "createUser {userId} {groupId} \n" <<
            "deleteUser {userId} \n" <<
            "getUser {userId} \n"<<
            "allUsers \n" <<
            "createGroup {groupId}\n" <<
            "deleteGroup {groupId}\n" <<
            "allGroups\n"<<
            "getGroup {userId}" << endl;
        }
        else if (words[0] == "createUser"){
            if (words.size() == 1 || words.size() > 3){
                cout << "Use <man>" << endl;
                continue;
            }
            int userId = stoi(words[1]);
            try{
                if (words.size() == 3){
                    int groupId = stoi(words[2]);
                    try{createUser(userId, groupId);}
                    catch(logic_error){
                        cout << "Нет группы с таким ID" << endl;
                    }
                }
                else if( words.size() == 2){
                    createUser(userId);
                }
            }
            catch(exception){
                cout << "Уже существует пользователь с таким ID" << endl;
            }
            // cout << "Shared_ptr.use_count3 = " << allUsers.front().use_count() << endl;
        }
        else if (words[0] == "deleteUser"){
            if (words.size() > 2 || words.size() == 1){
                cout << "Use <man>" << endl;
                continue;
            }
            int userId = stoi(words[1]);
            deleteUserFromAllUsers(userId);
            // cout << allUsers[0].use_count() << endl;
        }
        else if (words[0] == "allUsers"){
            if (words.size() > 1){
                cout << "Use <man>" << endl;
                continue;
            }
            printAllUsers();
        }
        else if (words[0] == "getUser"){
            if (words.size() > 2 || words.size() == 1){
                cout << "<Use man>" << endl;
                continue;
            }
            int userId = stoi(words[1]);
            getUser(userId);
        }
        else if (words[0] == "createGroup"){
            if (words.size() > 2 || words.size() == 1){
                cout << "<Use man>" << endl;
                continue;
            }
            int groupId = stoi(words[1]);
            try{createGroup(groupId);}
            catch(logic_error){
                cout << "Уже существует группа с таким ID" << endl;
            }
        }
        else if (words[0] == "deleteGroup"){
            if (words.size() > 2 || words.size() == 1){
                cout << "<Use man>" << endl;
                continue;
            }
            int groupId = stoi(words[1]);
            deleteGroupFromAllGroups(groupId);
        }
        else if (words[0] == "allGroups"){
            if (words.size() > 1){
                cout << "<Use man>" << endl;
                continue;
            }
            printAllGroups();
        }
        else if (words[0] == "getGroup"){
            if (words.size() > 2 || words.size() == 1){
                cout << "<Use man>" << endl;
                continue;
            }
            int groupId = stoi(words[1]);
            getGroup(groupId);
        }
        else if (words[0] == "exit"){
            break;
        }
        else{
            cout << "Unknown command" << endl;
        }
        cout << "> ";
    }
}