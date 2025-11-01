#include <iostream>
#include <io.h>
#include <direct.h>

using namespace std;



void menu() {
    cout << "Chouse an option: " << endl;
    cout << "1 - Show disc content" << endl;
    cout << "2 - Create folder/file" << endl;
    cout << "3 - Delete folder/file" << endl;
    cout << "4 - Rename folder/file" << endl;
    cout << "5 - Copy/move folder/ file" << endl;
    cout << "6 - Calculate folder/file size" << endl;
    cout << "7 - Perform a mask search" << endl;
    cout << endl;
    cout << "0 - Exit" << endl;
}



void lookDiskContent() {
    struct _finddata_t myfileinfo;
    char path[] = "C:\\";

    long done = _findfirst("C:\\", &myfileinfo);

    
    cout << myfileinfo.name;
}



void createFolder() {
    char* dirname = new char[200];

    cout << "Enter the full path to your new folder: ";
    cin >> dirname;

    if (_mkdir(dirname) == 0) {
        cout << "\nFolder created succesfully" << endl;
    }
    else
    {
        cout << "\n Problem creating folder";
    }

    delete[] dirname;
}

void createFile() {
    FILE* newFile;
    char* fileName = new char[100];

    cout << "Enter the full path to your new file: ";
    cin >> fileName;

    if (fopen_s(&newFile, fileName, "r") != NULL) {
        if (fopen_s(&newFile, fileName, "w") != NULL) {
            cout << "\nThis file could not be created" << endl;
        }
        else
        {
            cout << "\nFile created succesfully" << endl;;
            fclose(newFile);
        }
    }
    else
    {
        fclose(newFile);

        cout << "\nFile with that name already exist. Do you want to rewrite it?" << endl;
        cout << "0 - No" << endl;
        cout << "1 - Yes" << endl;

        bool choice;
        cin >> choice;

        if (choice) {
            //fopen_s(&newFile, fileName, "w");
            //cout << "\nFile rewrited" << endl;
            if (fopen_s(&newFile, fileName, "w") != NULL) {
                cout << "\nThis file could not be created" << endl;
            }
            else
            {
                cout << "\nFile rewrited" << endl;;
                fclose(newFile);
            }
        }
        else
        {
            cout << "\nCanceled" << endl;
            fclose(newFile);
        }
    }

    delete[] fileName;
}



void deleteFolder() {
    char* dirname = new char[200];

    cout << "Enter the full path to the folder you want to delete: ";
    cin >> dirname;

    if (_rmdir(dirname) == 0) {
        cout << "\nFolder deleted succesfully" << endl;
    }
    else
    {
        cout << "\n Problem removing folder";
    }

    delete[] dirname;
}

void deleteFile() {
    FILE* newFile;
    char* fileName = new char[100];

    cout << "\nEnter the full path to file you want to delete: ";
    cin >> fileName;

    if (!(remove(fileName))) {
        cout << "\nDeleted succesfully" << endl;
    }
    else
    {
        cout << "\nCould not delete this file" << endl;
    }

    delete[] fileName;
}



void renameFolder(){
    char* oldDirName = new char[200];
    char* newDirName = new char[100];

    cout << "Enter the full path to this folder: ";
    cin >> oldDirName;

    cout << "\n\nEnter new name for this folder(be careful with the file type, if the type is specified incorrectly, all file data will be erased): ";
    cin >> newDirName;

    int result = rename(oldDirName, newDirName);

    if (result != 0) {
        cout << "\nCould not rename this folder" << endl;
    }
    else
    {
        cout << "Renamed succesfully" << endl;
    }

    delete[] oldDirName;
    delete[] newDirName;
}

void renameFile() {
    char* oldDirName = new char[200];
    char* newDirName = new char[100];

    cout << "Enter the full path to this file: ";
    cin >> oldDirName;

    cout << "\n\nEnter new name for this file: ";
    cin >> newDirName;

    int result = rename(oldDirName, newDirName);

    if (result != 0) {
        cout << "\nCould not rename this file" << endl;
    }
    else
    {
        cout << "Renamed succesfully" << endl;
    }

    delete[] oldDirName;
    delete[] newDirName;
}

int main()
{
        menu();

        createFile();
        renameFile();
        //deleteFile();
}