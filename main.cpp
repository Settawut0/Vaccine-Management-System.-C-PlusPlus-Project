#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int ID;

struct patient_info{
    int id;
    string name;
    string surname;
    int age;
    string gender;
    string BG; //Blood Group
    int contact;
    string N;
}; //เก็บข้อมูลผู้ป่วย
int IDVACC;

struct Vaccine_info{
    int IDVAC;
    string Name_Vac;

}; //เก็บข้อมูลวัคซีน

struct Doctor{
    string id;
    string name;
    string surname;
    string position;
}; //เก็บข้อมูลหมอ

void ADD_Vaccine(){
    Vaccine_info vac;
    cout << "Enter Name : ";
    cin.get();
    getline(cin,vac.Name_Vac); //อ่านข้อมูลในสตริงหรือบรรทัดจากอินพุต

    IDVACC++;
    ofstream write; //เขียนข้อมูลลงไฟล์ Stream class
    write.open("InfoVACCINE.txt", ios::app); //เปิดไฟล์ ,ios::appเปิดไฟล์สำหรับเขียนข้อมูลลงไปต่อท้ายไฟล์
    write << "\n" << IDVACC; // เขียนข้อมูลลงไฟล์
    write << "\n" << vac.Name_Vac;
    write.close(); //ปิดไฟล์
    write.open("id2.txt");
    write << IDVACC;
    write.close();
    cout << "\n\tAdd Success....";
}

//แสดงวัคซีนในคลัง
void Show_Vacc_Data(Vaccine_info v){ //หนัาจอแสดงข้อมูล ไอดีกับ ชื่อแบบสตริง
    cout << "  \t **********************\n";
    cout << "\t|   ID" << "\t|   Name" << "   |\n";
    cout << "\t|   " <<  v.IDVAC << "\t|  " << v.Name_Vac << " |"  ;
    cout << endl;
}

//vaccine
void viewvaccine(){ //ดูวัคซีนในไฟล์ทั้งหมด
    Vaccine_info vac;
    ifstream read; //อ่านไฟล์
    read.open("InfoVACCINE.txt"); //เปิดไฟล์
    while (!read.eof()){ //ระบบจุดสิ้นสุดของไฟล์
        read >> vac.IDVAC;
        read.ignore();
        getline(read, vac.Name_Vac);
        Show_Vacc_Data(vac); //เรียกใช้ฟังก์ชัน
    }
    read.close();
}

int search22Data(){ //ค้นหาวัคซีนตามไอดี
    int IDVAC;
    cout << "\n\tEnter Patient id want to search : ";
    cin >> IDVAC;
    Vaccine_info vac;
    ifstream read; //อ่านข้อมูลในไฟล์ Stream class
    read.open("InfoVACCINE.txt");
    while(!read.eof()){ //ระบุจุดสิ้นสุดของไฟล์
        read >> vac.IDVAC;
        read.ignore();
        getline(read, vac.Name_Vac); //อ่านข้อมูลในสตริงหรือบรรทัดจากอินพุต

        if(vac.IDVAC == IDVAC){
            Show_Vacc_Data(vac);
            return IDVAC;
        }
    }
}

void updateData_Vac(){ //อัพเดตข้อมูล
    int IDVAC = search22Data();
    cout << "\n\tYou want to update record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y'){
        Vaccine_info NewDATA;
        cout << "\n\tEnter Vaccine name : ";
        cin.get();
        getline(cin , NewDATA.Name_Vac); //อ่านข้อมูลในสตริงหรือบรรทัดจากอินพุต

        Vaccine_info vac;
        ofstream TempFile;  //เขียนข้อมูลลงไฟล์ Stream class
        TempFile.open("Temp.txt");
        ifstream read; //อ่านข้อมูลในไฟล์ Stream class
        read.open("InfoVACCINE.txt");
        while(!read.eof()){ //ระบุจุดสิ้นสุดของไฟล์
            read >> vac.IDVAC;
            read.ignore(); //ข้ามไปบรรทัดถัดไป
            getline(read, vac.Name_Vac); //อ่านข้อมูลในสตริงหรือบรรทัดจากอินพุต

            if (vac.IDVAC != IDVAC){ //ข้อมูลในสตริงไม่เท่ากับ IDVAC
                TempFile << "\n" << vac.IDVAC; //เก็บข้อมูลในtemfile
                TempFile << "\n" << vac.Name_Vac;


            }else{//ถ้าไม่
                TempFile << "\n" << vac.IDVAC; //เก็บไอดีไว้และ
                TempFile << "\n" << NewDATA.Name_Vac; //เปลี่ยนข้อมูล แล้สไปเก็ฐใน temp

            }
        }
        read.close();
        TempFile.close();
        remove("InfoVACCINE.txt"); //คำสั่งลบไฟล์
        rename("Temp.txt", "InfoVACCINE.txt"); //เปลียนชื่อเก่าเป็นใหม่
        cout << "\n\tData Update success";
    }else {
        cout << "\n\tRecord not Update....";
    }
}

void delete_Vac_Data(){
    int IDVAC = search22Data();
    cout << "\n\tYou want to delete record (y/n) : ";
    char choice;
    cin >> choice;
    if(choice == 'y'){
        Vaccine_info vac;
        ofstream TempFile; //เขียนข้อมูลลงไฟล์ Stream class
        TempFile.open("Temp.txt"); //เปิดไฟล์
        ifstream read; //อ่านข้อมูลในไฟล์ Stream class
        read.open("InfoVACCINE.txt"); //อ่านไฟล์
        while (!read.eof()) { //ระบุจุดสิ้นสุดของไฟล์
            read >> vac.IDVAC;
            read.ignore(); //ข้ามไปบรรทัดถัดไป
            getline(read, vac.Name_Vac); //อ่านข้อมูลในสตริงหรือบรรทัดจากอินพุต

            if(vac.IDVAC != IDVAC){ //ถ้าไม่ข้อมูลเดิม
                TempFile << "\n" << vac.IDVAC;  //ข้อมูลในสตริงไม่เท่ากับ IDVAC
                TempFile << "\n" << vac.Name_Vac;

            }
        }
        read.close();
        TempFile.close();
        remove("InfoVACCINE.txt"); //คำสั่งลบไฟล์
        rename("Temp.txt", "InfoVACCINE.txt"); //เปลียนชื่อเก่าเป็นใหม่
        cout << "\n\tData delete success";
    }
    else{
        cout << "\n\tRecord not deleted";
    }
}
//vaccine บน

void add_Patient(){
    patient_info Patient;
    cout << "\n\tEnter Patient name : ";
    cin.get();
    getline(cin,Patient.name);
    cout <<"\n\tEnter Patient Surname : ";
    cin >> Patient.surname;
    cout <<"\n\tEnter Patient age : ";
    cin >> Patient.age;
    cout <<"\n\tEnter Patient gender : ";
    cin >> Patient.gender;
    cout <<"\n\tEnter Patient Blood Group : ";
    cin >> Patient.BG;
    cout <<"\n\tEnter Patient Contact : ";
    cin >> Patient.contact;

    viewvaccine();
    cout << "Enter NameVaccine :";
    cin.get();
    getline(cin,Patient.N); //อ่านข้อมูลในสตริงหรือบรรทัดจากอินพุต
    ID++;

    ofstream write; //เขียนข้อมูลลงไฟล์ Stream class
    write.open("patient.txt", ios::app); //เปิดไฟล์ ,ios::appเปิดไฟล์สำหรับเขียนข้อมูลลงไปต่อท้ายไฟล์
    write << "\n" << ID ; // เขียนข้อมูลลงไฟล์
    write << "\n" << Patient.name; // เขียนข้อมูลลงไฟล์
    write << "\n" << Patient.surname; // เขียนข้อมูลลงไฟล์
    write << "\n" << Patient.age;
    write << "\n" << Patient.gender;
    write << "\n" << Patient.BG;
    write << "\n" << Patient.contact;
    write << "\n" << Patient.N;
    write.close();
    write.open("id.txt"); //เปิดไฟบ์.open
    write << ID;
    write.close();
    cout << "\n\t\t Data Save to file.....";
    cout << "\n\t\t" << " " << "         SUCCEED...\n";
}

void Show(patient_info p){ //เก็บข้อมูลลงในตัวแปร ที่มีสตริง ไว้เรียกดู
    cout << endl;
    cout << "\t\t<>============<>============<>Patient Data<>============<>============<>";
    cout << "\n  ID is : " << p.id;
    cout << " | Name is : " << p.name;
    cout << " | Surname is : " << p.surname;
    cout << " | Age is : " << p.age;
    cout << " | Gender is : " << p.gender;
    cout << " | Blood Group is : " << p.BG;
    cout << endl;

    cout << " | Contact is : " << p.contact;
    cout << " | Vaccine is : " << p.N;

    cout << endl;
}

void readDATA(){
    patient_info Patient;
    ifstream read; //อ่านแฟ้มข้อมูล
    read.open("patient.txt");
    while (!read.eof()){
        read >> Patient.id;
        read.ignore();
        getline(read, Patient.name);
        read >> Patient.surname;
        read >> Patient.age;
        read >> Patient.gender;
        read >> Patient.BG;
        read >> Patient.contact;
        read.ignore();
        getline(read, Patient.N);
        Show(Patient);
    }
    read.close();
}

int searchData(){
    int id;
    cout << "\n\tEnter Patient id want to search : ";
    cin >> id;
    patient_info Patient;
    ifstream read;
    read.open("patient.txt");
    while(!read.eof()){ //ตรวจสอบจุดสิ้นสุดของแฟ้มข้อมู,
        read >> Patient.id;
        read.ignore();
        getline(read, Patient.name);
        read >> Patient.surname;
        read >> Patient.age;
        read >> Patient.gender;
        read >> Patient.BG;
        read >> Patient.contact;
        read.ignore();
        getline(read, Patient.N);
        if(Patient.id == id){
            Show(Patient);
            return id;
        }
    }
}

void deleteData(){ //ลบข้อตามไอดี
    int id = searchData(); //ไอดีเหมือนกับฟังก์ชันเสริจ
    cout << "\n\tYou want to deleat record (y/n) : ";
    char choice;
    cin >> choice;
    if(choice == 'y'){
        patient_info Patient;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("patient.txt");
        while (!read.eof()) {
            read >> Patient.id;
            read.ignore();
            getline(read, Patient.name);
            read >> Patient.surname;
            read >> Patient.age;
            read >> Patient.gender;
            read >> Patient.BG;
            read >> Patient.contact;
            read.ignore();
            getline(read, Patient.N);
            if(Patient.id != id){
                tempFile << "\n" << Patient.id;
                tempFile << "\n" << Patient.name;
                tempFile << "\n" << Patient.surname;
                tempFile << "\n" << Patient.age;
                tempFile << "\n" << Patient.gender;
                tempFile << "\n" << Patient.BG;
                tempFile << "\n" << Patient.contact;
                tempFile << "\n" << Patient.N;

            }
        }
        read.close();
        tempFile.close();
        remove("patient.txt");
        rename("temp.txt", "patient.txt");
        cout << "\n\tData delete success";
    }
    else{
        cout << "\n\tRecord not deleted";
    }
}

void updateData(){ //อัพเดตข้อมูลผู้ป่วย
    int id = searchData();
    cout << "\n\tYou want to update record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y'){
        patient_info NEWdata;
        cout << "\n\tEnter Patient name : ";
        cin.get();
        getline(cin , NEWdata.name);
        cout << "\n\tEnter Patient Surname : ";
        cin >> NEWdata.surname;
        cout << "\n\tEnter Patient age : ";
        cin >> NEWdata.age;
        cout << "\n\tEnter Patient Gender : ";
        cin >> NEWdata.gender;
        cout << "\n\tEnter Patient Blood Group : ";
        cin >> NEWdata.BG;
        cout << "\n\tEnter Patient Contact : ";
        cin >> NEWdata.contact;
        viewvaccine();
        cout << "Enter NameVaccine :";
        cin.get();
        getline(cin,NEWdata.N);
        patient_info Patient;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("patient.txt");
        while(!read.eof()){
            read >> Patient.id;
            read.ignore();
            getline(read, Patient.name);
            read >> Patient.surname; //อ่านนข้อมูลใน
            read >> Patient.age;
            read >> Patient.gender;
            read >> Patient.BG;
            read >> Patient.contact;
            read.ignore();
            getline(read, Patient.N);
            if (Patient.id != id){
                tempFile << "\n" << Patient.id;
                tempFile << "\n" << Patient.name;
                tempFile << "\n" << Patient.surname;
                tempFile << "\n" << Patient.age;
                tempFile << "\n" << Patient.gender;
                tempFile << "\n" << Patient.BG;
                tempFile << "\n" << Patient.contact;
                tempFile << "\n" << Patient.N;
            }else{
                tempFile << "\n" << Patient.id;
                tempFile << "\n" << NEWdata.name; //เขียนมูลใหม่ลงใน tempfile
                tempFile << "\n" << NEWdata.surname;
                tempFile << "\n" << NEWdata.age;
                tempFile << "\n" << NEWdata.gender;
                tempFile << "\n" << NEWdata.BG;
                tempFile << "\n" << NEWdata.contact;
                tempFile << "\n" << NEWdata.N;
            }
        }
        read.close();
        tempFile.close();
        remove("patient.txt");
        rename("temp.txt", "patient.txt");
        cout << "\n\tData Update success";
    }else {
        cout << "\n\tRecord not Update....";
    }
}

void Menu(){
    cout << "\n\t\t+<><><><><><><><><><>=========================================================<><><><><><><><><><>+";
    cout << "\n\t\t +                     MM                MM  EEEEEEEE  NN      NN  UU      UU                    +";
    cout << "\n\t\t   +                   MM MM          MM MM  EEE       NN NN   NN  UU      UU                 +";
    cout << "\n\t\t     +                 MM   MM      MM   MM  EEEEEEEE  NN  NN  NN  UU      UU               +";
    cout << "\n\t\t   +                   MM     MM  MM     MM  EEE       NN   NN NN  UU      UU                 +";
    cout << "\n\t\t +                     MM       MM       MM  EEEEEEEE  NN      NN    UUUUUU                      +";
    cout << "\n\t\t+<><><><><><><><><><>==========================================================<><><><><><><><><><>+";
    cout << endl;
    cout << "\n\t\t                        >>>>>>        PATIENT MANAGEMENT SYSTEM       <<<<<<                           ";
    cout << "\n\t\t                                     ___________________________                                      ";
    cout << endl;
    cout << "\n\t\t                                        1.Add Patient data";
    cout << "\n\t\t                                        2.See Patient data";
    cout << "\n\t\t                                        3.Search Patient data";
    cout << "\n\t\t                                        4.Delete Patient data";
    cout << "\n\t\t                                        5.Update Patient data";
    cout << "\n\t\t                                        6.Back";
}

void M(){
    cout << "\n\t\t+<><><><><><><><><><>=========================================================<><><><><><><><><><>+";
    cout << "\n\t\t +                     MM                MM  EEEEEEEE  NN      NN  UU      UU                    +";
    cout << "\n\t\t   +                   MM MM          MM MM  EEE       NN NN   NN  UU      UU                 +";
    cout << "\n\t\t     +                 MM   MM      MM   MM  EEEEEEEE  NN  NN  NN  UU      UU               +";
    cout << "\n\t\t   +                   MM     MM  MM     MM  EEE       NN   NN NN  UU      UU                 +";
    cout << "\n\t\t +                     MM       MM       MM  EEEEEEEE  NN      NN    UUUUUU                      +";
    cout << "\n\t\t+<><><><><><><><><><>==========================================================<><><><><><><><><><>+";
    cout << endl;
    cout << "\n\t\t                        >>>>>>                 SYSTEM                 <<<<<<                        ";
    cout << "\n\t\t                                     ___________________________                                      ";
    cout << endl;
    cout << "\n\t\t                                     1.Patient Management System";
    cout << "\n\t\t                                     2.Vaccine Management System";
    cout << "\n\t\t                                     3.List of doctor";
    cout << "\n\t\t                                     4.Back Log-in System";
    cout << endl;
}

void MenuVac(){
    cout << "\n\t\t+<><><><><><><><><><>=========================================================<><><><><><><><><><>+";
    cout << "\n\t\t +                     MM                MM  EEEEEEEE  NN      NN  UU      UU                    +";
    cout << "\n\t\t   +                   MM MM          MM MM  EEE       NN NN   NN  UU      UU                 +";
    cout << "\n\t\t     +                 MM   MM      MM   MM  EEEEEEEE  NN  NN  NN  UU      UU               +";
    cout << "\n\t\t   +                   MM     MM  MM     MM  EEE       NN   NN NN  UU      UU                 +";
    cout << "\n\t\t +                     MM       MM       MM  EEEEEEEE  NN      NN    UUUUUU                      +";
    cout << "\n\t\t+<><><><><><><><><><>==========================================================<><><><><><><><><><>+";
    cout << endl;
    cout << "\n\t\t                        >>>>>>        Vaccine MANAGEMENT SYSTEM       <<<<<<                           ";
    cout << "\n\t\t                                     ___________________________                                      ";
    cout << endl;
    cout << "\n\t\t                                        1.Add Vaccine data";
    cout << "\n\t\t                                        2.See Vaccine data";
    cout << "\n\t\t                                        3.Search Vaccine data";
    cout << "\n\t\t                                        4.Update Vaccine data";
    cout << "\n\t\t                                        5.Delete Vaccine data";
    cout << "\n\t\t                                        6.Back";
}

void Menu_login(){
    cout << "\t\t\t<><><><><><><><><><><><><>" << endl;
    cout << "\t\t\t  ||<><><><><><><><><>||" << endl;
    cout << "\t\t\t     ====Welcome==== " << endl;
    cout << "\t\t\t     >>>>>LOGIN<<<<<< " << endl;
    cout << "\t\t\t  ||<><><><><><><><><>||" << endl;
    cout << "\t\t\t<><><><><><><><><><><><><>" << endl;
}

void Read_Data(Doctor arr[],int *Num_Doctor){ //อ่านข้อมูล
    ifstream myFile("..\\Doctor.txt",ios::in);
    int index = 0; //กำหนด ขนาด
    if (myFile.is_open()){
        while(myFile >> arr[index].id >> arr[index].name >> arr[index].surname >> arr[index].position ){
            index++;
            *Num_Doctor = index;
        }
    }
    else{
        cout << "Unable to OPEN.TXT" << endl;
    }
}



//เพิ่มวัคซีน
//เอาออกราคาออก
//โปรแกรมหลัก
int main() {
    Doctor stu;
    Doctor arr[100];
    int Num_Doctor; //วนเรียกช้อมูลในไฟล์หมอ
    string username = "";
    string password = "";
    bool loginSuccess = false; //เพื่อเก็บแค่ 2 ค่าคือจริงและเท็จ
    Menulog: Menu_login();
    do {
        cout << " Username(login) : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;

        if (username == "Pluem" && password == "1234PP") {
            cout << "\t\tSuccessful Login...\n";
            loginSuccess = true; //ถ้าเป็นเป็นจริงหรือรหหัสถูก

            ifstream read; //เปิดไฟล์ไอดีก่อน
            read.open("id.txt");
            if (!read.fail()) { //ไม่ล้มเหลวก็อ่านไอดี
                read >> ID;
            } else {
                ID = 0;
            }
            read.close();

            Menu: M();
            int Selec;
            cout << "\n\t\t                             Enter choice : ";
            cin >> Selec;
            if (Selec == 1) {
                Menu1: Menu();
                int choice;
                cout << "\n\t\t                             Enter choice : ";
                cin >> choice;
                switch (choice) {
                    case 1:
                        add_Patient();
                        goto Menu1;
                    case 2:
                        readDATA();
                        goto Menu1;
                    case 3:
                        searchData();
                        goto Menu1;
                    case 4:
                        deleteData();
                        goto Menu1;
                    case 5:
                        updateData();
                        goto Menu1;
                    case 6:
                        goto Menu;
                }
            } else if (Selec == 2) {
                Menu2: MenuVac();
                int choice2;
                cout << "\n\t\t                             Enter choice : ";
                cin >> choice2;
                switch (choice2){
                    case 1:
                        ADD_Vaccine();
                        goto Menu2;
                    case 2:
                        viewvaccine();
                        goto Menu2;
                    case 3:
                        search22Data();
                        goto Menu2;
                    case 4:
                        updateData_Vac();
                        goto Menu2;
                    case 5:
                        delete_Vac_Data();
                        goto Menu2;
                    case 6:
                        goto Menu;
                }
            }else if(Selec == 3){
                Read_Data(arr, &Num_Doctor);
                for (int i = 0; i < Num_Doctor; i++) {
                    cout << arr[i].id << "\t" << arr[i].name << "\t" << arr[i].surname << "\t" << arr[i].position <<endl;
                }
                goto Menu;
            }else if (Selec == 4){
                goto Menulog;
            }
        } else {
            cout << "\t\tIncorrect username password combo \n";
            cout << "\t\tPlease try to login again....\n";
        }
    }while (true);
}