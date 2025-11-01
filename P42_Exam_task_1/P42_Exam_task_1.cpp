#include <iostream>
#include <io.h>
#include <direct.h>

using namespace std;

char* getName(char* path) {
    int count = 0;

    for (size_t i = 0; i < strlen(path); i++)
    {
        if (path[i] == '\\') {
            count++;
        }
    }

    if (count == 0) {
        char* name = new char[strlen(path) + 1];
        for (size_t i = 0; i < strlen(path); i++)
        {
            if (path[i] == '.') {
                name[i] = '\0';
                break;
            }
            name[i] = path[i];
        }
        return name;
    }
    else
    {
        int count2 = 0;
        char* name = new char[100];
        
        for (size_t i = 0; i < strlen(path); i++)
        {
            if(count2 == count) {
                if (path[i] == '.') {
                    name[i] = '\0';
                    break;
                }
                name[i] = path[i];
                continue;
            }

            if (path[i] == '\\') {
                count2++;
            }
        }

        return name;
    }
}


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



//void lookDiskContent() {
//    struct _finddata_t myfileinfo;
//    char path[] = "C:\\";
//
//    long done = _findfirst("C:\\", &myfileinfo);
//
//    
//    cout << myfileinfo.name;
//}



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



void copyFolder() {}

void copyFile() {
    char* fileName = new char[200];

    cout << "Enter the full path to the file: ";
    cin >> fileName;

    FILE* myfile;

    if (fopen_s(&myfile, fileName, "r") != NULL) {
        cout << "\nThis file could not be copied" << endl;
    }
    else
    {
        char* name = getName(fileName);
        char* copy = new char[strlen(name) + 7];
        strcpy_s(copy, strlen(name) + 1, name);
        strcat_s(copy, strlen(name) + 15, " - copy.txt");

        FILE* copyfile;

        if (fopen_s(&copyfile, copy, "r") != NULL) {
            if (fopen_s(&copyfile, copy, "w") != NULL) {
                cout << "\nThis file could not be copied" << endl;
            }
            else
            {
                char* buffer = new char[200];

                while (!feof(myfile)) {
                    fgets(buffer, 200, myfile);
                    fputs(buffer, copyfile);
                }


                fclose(myfile);
                fclose(copyfile);

                cout << "\nCopied succesfully" << endl;
            }
        }
        else
        {
            fclose(copyfile);

            cout << "Copy already exists. Do you want to rewrite it: " << endl;
            cout << "0 - No" << endl;
            cout << "1 - Yes" << endl;

            int choice;
            cin >> choice;

            if (choice) {
                if (fopen_s(&copyfile, copy, "w") != NULL) {
                    cout << "\nThis file could not be copied" << endl;
                }
                else
                {
                    char* buffer = new char[200];

                    while (!feof(myfile)) {
                        fgets(buffer, 200, myfile);
                        fputs(buffer, copyfile);
                    }


                    fclose(myfile);
                    fclose(copyfile);

                    cout << "\nCopied succesfully" << endl;
                }
            }
            else
            {
                cout << "\nCanceled" << endl;
            }
        }
    }
    


    delete[] fileName;
}


int main()
{
        menu();

        copyFile();
}