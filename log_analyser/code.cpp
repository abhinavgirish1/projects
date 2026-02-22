#include <bits/stdc++.h>
using namespace std;

struct entry{
    string timestamp;
    string level;
    string source;
    string message;
};
// standard log file format being ["timestamp (DD-MM-YY) level (Error/Warn/info/fatal/debug)
//  source (AuthService/DatabaseManager/PaymentModule) message (Database connection failed/Retry attempt initiated/Connection timeout)"]
vector<entry> log(vector<entry>& files,string ts,string lvl,string src,string msg){
    vector<entry> result;
    for(auto &e:files){
        if(!ts.empty() && e.timestamp!=ts) continue;
        if(!lvl.empty() && e.level!=lvl) continue;
        if(!src.empty() && e.source!=src) continue;
        if(!msg.empty() && e.message.find(msg)==string::npos) continue;
        result.push_back(e);
    }
    return result;
}

int main(){
    //Example log 
    vector<entry> files={
        {"2026-02-14 10:02:45","ERROR","AuthService","Invalid credentials provided"},
        {"2026-02-14 10:05:11","INFO","PaymentService","Payment processed successfully"},
        {"2026-02-14 10:06:29","ERROR","PaymentService","Payment gateway timeout"},
        {"2026-02-14 10:09:02","ERROR","DatabaseService","Database connection failed"},
        {"2026-02-14 10:11:37","WARN","DatabaseService","High query execution time detected"}
    };
    // Choice between specific keyword filtering and viewing general statistics of the levels in the log
    cout<<"Choose option:\n";
    cout<<"1. Filter Logs\n";
    cout<<"2. Show Statistics\n";

    int choice;
    cin>>choice;
    cin.ignore();

    if(choice==1){
        string ts,lvl,src,msg;
        cout<<"Enter timestamp filter (press Enter to skip): ";
        getline(cin,ts);
        cout<<"Enter level filter (press Enter to skip): ";
        getline(cin,lvl);
        cout<<"Enter source filter (press Enter to skip): ";
        getline(cin,src);
        cout<<"Enter message keyword (press Enter to skip): ";
        getline(cin,msg);

        vector<entry> result=log(files,ts,lvl,src,msg);

        cout<<"\nFiltered Results:\n\n";
        if(result.empty()){
            cout<<"No matching logs found.\n"; //for no such log found
        }
        else{
            for(auto &e:result)
                cout<<e.timestamp<<"|"<<e.level<<"|"<<e.source<<"|"<<e.message<<endl;
        }
    }
    else if(choice==2){
        unordered_map<string,int> levelCount; //using unordered hash map
        for(auto &e:files) levelCount[e.level]++;
        cout<<"\nLog Level Statistics:\n\n";
        for(auto &p:levelCount)
            cout<<p.first<<" : "<<p.second<<endl;
    }
    else{
        cout<<"Invalid choice.\n";
    }
}
