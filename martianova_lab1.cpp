#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Pipe.h"
#include "Station.h"
#include "Station.cpp"
#include <unordered_map>
#include "Pipe.h"
#include "Pipe.cpp"
#include "logging.h"
using namespace std;
typedef unordered_map<int, Station> MapStation;
typedef unordered_map<int, Pipe> MapPipe;

template <typename type>
bool CheckID(const unordered_map<int, type>& items, int id) {
	return (items.contains(id));
}

int CorrectIntID() {
	int id;
	while ((cin >> id).fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter an integer: ";
	}
	cerr << id << endl;
	return id;
}


// редактирование трубы
void EditPipe(MapPipe &AllPipe)
{
    int id;
    id=CorrectIntID();
    if (CheckID(AllPipe,id)){
        AllPipe[id].isRepair = !AllPipe[id].isRepair;
    }
};
//редактирование всех труб
void EditAllPipe(MapPipe &AllPipe)
{
    for (auto &i : AllPipe)
    {
        i.second.isRepair = !i.second.isRepair;
    }
    
};
// редактирование списка труб
void EditListPipes(MapPipe &AllPipe){
    string listId;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id через пробел: ";
        getline(cin, listId);

    } while (listId == "");
    // разбиение строки на пробелы
    stringstream ss(listId);
    string id;
    while (ss >> id)
    {
        if (CheckID(AllPipe, stoi(id)))
        {
            AllPipe[stoi(id)].isRepair = !AllPipe[stoi(id)].isRepair;
        }
    }
};
// редактирование станции
void EditStation(MapStation &AllStation)
{
    int id = 0;
    id=CorrectIntID();
    int countWork;
    if (CheckID(AllStation, id)){
        cout << "Number of workshops in operation: ";
        cin >> countWork;
        cerr << countWork;
        if(countWork <= AllStation[id].countAll){
            AllStation[id].countWork=countWork;
        }
    }
};

// удаление станции
void DeleteStation(MapStation &AllStation)
{
    int id;
    id=CorrectIntID();
    if (CheckID(AllStation, id)){
        AllStation.erase(id);
    }
    
};
// фильтрация станции по имени
unordered_map<int, Station> FindStationByName(MapStation AllStation, string name = "Unknow")
{
    MapStation res;
    for (auto &i : AllStation)
    {
        if (i.second.name == name)
        {
            res[i.first] = i.second;
        }
    }
    return res;
}
// фильтрация станции по цехам
unordered_map<int, Station> FindStationByWorkShop(MapStation AllStation, float per)
{
    MapStation res;
    float item;
    for (auto &i : AllStation)
    {
        item=((i.second.countAll)/100)*(i.second.countAll-i.second.countWork);
        if (item == per)
        {
            res[i.first] = i.second;
        }
    }
    return res;
}
// фильтрация трубы по признаку в ремонте
unordered_map<int, Pipe> FindPipeByIsRepair(MapPipe AllPipe, bool isRepair)
{
    MapPipe res;
    int i = 0;
    for (auto &i : AllPipe)
    {
        if (i.second.isRepair == isRepair)
        {
            res[i.first] = i.second;
        }
    }
    return res;
}

// фильтрация трубы по названию
unordered_map<int, Pipe> FindPipeByName(MapPipe AllPipe, string name)
{
    MapPipe res;
    int i = 0;
    for (auto &i : AllPipe)
    {
       if (i.second.name == name)
        {
            res[i.first] = i.second;
        }
    }
    return res;
}
// удаление трубы
void DeletePipe(MapPipe &AllPipe)
{
    int id;
    id=CorrectIntID();
    if (CheckID(AllPipe, id)){
        AllPipe.erase(id);
    }
};

// удаление списка труб
void DeleteListPipes(MapPipe &AllPipe)
{
    string listId;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите id через пробел: ";
        getline(cin, listId);
    } while (listId == "");
    // разбиение строки на пробелы
    stringstream ss(listId);
    string id;
    while (ss >> id)
    {
        if (CheckID(AllPipe, stoi(id)))
        {
            AllPipe.erase(stoi(id));
        }
    }
}



void PrintMenu()
{
    cout << "Add pipe: 1" << endl
         << "Add station: 2" << endl
         << "Viewing all objects: 3" << endl
         << "Edit pipe: 4" << endl
         << "Edit station: 5" << endl
         << "Save: 6" << endl
         << "Download: 7" << endl
         << "Delete station on id: 8" << endl
         << "Delete pipe on id: 9" << endl
         << "Filter stations on name: 10" << endl
         << "Filter pipes on sign in repair: 11" << endl
         << "Filter pipes on name: 12" << endl
         << "Filter stations of percentage non-operational workshops: 13" << endl
         << "Batch pipes delete: 14" << endl
         << "Batch pipes based on the need for repair: 15" << endl
         << "Exit: 0" << endl;
};

int main()
{
    
    MapStation AllStation;
    MapPipe AllPipe;
    Station station;
    Pipe pipe;
    bool isStation = false;
    bool isPipe = false;
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("log.txt");
	if (logfile)
		cerr_out.redirect(logfile);
    while (1)
    {
        PrintMenu();
        int i = 0;
        do
        {
            if (cin.fail() || i > 8)
            {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin>>i;
            cerr << i<<endl;
        } while (cin.fail() || i > 15);
        switch (i)
        {
        case 1:
        {
            cin >> pipe;
            int id = pipe.GetChangeId();
            AllPipe[id] = pipe;
            isPipe = true;
            break;
        }
        case 2:
        {
            cin >> station;
            
            int id = station.GetChangeId();
            AllStation[id] = station;
            isStation = true;
            break;
        }
        case 3:
        {
            if (AllStation.size() > 0)
            {
                for (auto &i : AllStation)
                {
                    cout << i.second;
                }
            }
            if (AllPipe.size() > 0)
            {
                for (auto &i : AllPipe)
                {
                    cout << i.second;
                }
            }
            break;
        }
        case 4:
        {
            if (AllPipe.size() > 0)
            {
                EditPipe(AllPipe);
            }
            else
            {
                cout << "Трубы не существует" << endl;
            }
            break;
        }
        case 5:
        {
            if (AllStation.size() > 0)
            {
                EditStation(AllStation);
            }
            else
            {
                cout << "Станции не существует" << endl;
            }
            break;
        }
        case 6:
        {
            string nameFile;
                cout << "Введите название файла: ";
                cin>>nameFile;
                cerr<<nameFile;
            
			ofstream out(nameFile);
			for (auto const& p : AllPipe) {
				if (!p.second.name.empty()) {
					AllPipe[p.first].SavePipe(out);
				}
			}
			for (auto const& k : AllStation) {
				if (!k.second.name.empty()) {
					AllStation[k.first].SaveStation(out);
				}
			}
			break;
        }
        case 7:
        {
            cout << "Введите название файла: ";
			string read_file;
            cin>>read_file;
            ifstream read(read_file+".txt");
			if (read.peek() == std::ifstream::traits_type::eof()) {
				cout << "Ошибка\n";
			}
			else {
				string Name;
				while (getline(read, Name)) {
					if (Name == "pipe") {
						Pipe read_pipe;
						read_pipe.download(read);
						AllPipe.insert({ read_pipe.GetId(), read_pipe });				
					}
					if (Name == "station") {
						Station read_ks;
						read_ks.download(read);
						AllStation.insert({ read_ks.GetId(), read_ks });
					}
				}
			}
			break;
        }
        case 8:
        {
            DeleteStation(AllStation);
            break;
        }
        case 9:
        {
            DeletePipe(AllPipe);
            break;
        }
        case 10:
        {
            MapStation FilterNameStation;
            string name;

            cout << "Type name: ";
            READ_LINE(cin, name);

            FilterNameStation = FindStationByName(AllStation, name);
            if (FilterNameStation.size() == 0)
            {
                cout << "Такой станции не существует" << endl;
            }
            else
            {
                for (auto &i : FilterNameStation)
                {
                    cout << i.second;
                }
            }

            break;
        }
        case 11:
        {
            MapPipe FilterIsRepairPipe;
            bool isRepair;
            cout << "Type in repair (1=in repair, 0=not in repair): ";
            cin >> isRepair;

            FilterIsRepairPipe = FindPipeByIsRepair(AllPipe, isRepair);
            if (FilterIsRepairPipe.size() == 0)
            {
                cout << "Такой трубы не существует" << endl;
            }
            else
            {
                for (auto &i : FilterIsRepairPipe)
                {
                    cout << i.second;
                }
            }

            break;
        }
        case 12:
        {
            MapPipe FilterNamePipe;
            string name;

            cout << "Type name: ";
            READ_LINE(cin, name);

            FilterNamePipe = FindPipeByName(AllPipe, name);
            if (FilterNamePipe.size() == 0)
            {
                cout << "Такой трубы не существует" << endl;
            }
            else
            {
                for (auto &i : FilterNamePipe)
                {
                    cout << i.second;
                }
            }

            break;
        }
        case 13:
        {
            MapStation FilterWorkShopStation;
            float percent;
        do
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Введите процент незадействованных цехов: ";
                cin>>percent;
            } while (cin.fail());
            FilterWorkShopStation=FindStationByWorkShop(AllStation,percent);
            if (FilterWorkShopStation.size() == 0)
            {
                cout << "Такой станции не существует" << endl;
            }
            else
            {
                for (auto &i : FilterWorkShopStation)
                {
                    cout << i.second;
                }
            }
            break;
        }
        case 14:
        {
            int num;
            
                cout << "Введите 1 или 2 (1 - удаление всех труб; 2 - удаление труб по id): ";
                cin >> num;
            if (num == 1)
            {
                AllPipe.clear();
                cout << "Все трубы удалены" << endl;
            }
            else if(num == 2)
            {
                DeleteListPipes(AllPipe);
                cout << "Оставшиеся трубы" << endl;
                if (AllPipe.size() > 0)
                {
                    for (auto &i : AllPipe)
                    {
                        cout << i.second;
                    }
                }
            }
            break;
        }
        case 15:
        {
            int num;
                cout << "Введите 1 или 2 (1 - редактирование всех труб; 2 - редактирование труб по id): ";
                cin >> num;
            if (num == 1)
            {
                EditAllPipe(AllPipe);
                cout << "Все трубы отредактированы" << endl;
            }
            else if(num==2)
            {
                EditListPipes(AllPipe);
                if (AllPipe.size() > 0)
                {
                    for (auto &i : AllPipe)
                    {
                        cout << i.second;
                    }
                }
            }
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Произошла ошибка" << endl;
        }
        }
    }
    return 0;
}

// https://iq.opengenus.org/istringstream-in-cpp/
// https://stackoverflow.com/questions/5781597/incomplete-type-is-not-allowed-stringstream
// https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
// https://favtutor.com/blogs/split-string-cpp
// https://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c

//https://stackoverflow.com/questions/42230318/how-to-remove-an-entry-from-a-stdmap-using-key
//https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
//https://metanit.com/cpp/tutorial/8.3.php
//http://cppstudio.com/post/816/