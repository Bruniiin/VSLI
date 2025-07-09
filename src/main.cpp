#define WINDOWS_64
#ifdef WINDOWS_64
#include "windows.h"
#endif
#include "vs.h"
#include "config.h"
#include "string.h"
#include <filesystem>
#include <fstream>
#include <cstring>
#include "libmatoya-main/src/matoya.h"
#define init_error 0

int main(int argc, char* argv[]) {

    #ifdef is_instance_exclusive
    if(Visual::is_another_instance_running)
        return -1;
    #endif

    if(argc >= 1) {
        return -1;
    }

    #ifdef WINDOWS_64
    TCHAR* windows_user;
    DWORD size;

    if(!GetUserName(windows_user, &size)) {
        printf("debug error");
        return -1;
    }

    // should be its own function

    char user = *windows_user;

    Visual::User user_data;
    Config user_config;
    std::error_code ec;
    auto temp_folder = std::filesystem::temp_directory_path(ec);

    bool is_binary_file = false;
    char file_argv = *"user.txt";
    char file_argv_2 = *"saved.txt";
    char* path_user_folder = ("C:/Users/%s/AppData/Roaming/vs/", &user);
    char* path_saved_folder = ("C:/Users/%s/Documents/vs-saved/", &user);
    char* path_user_file_temp = ("C:/Users/%s/AppData/Roaming/Temp/%s", &user, &file_argv);
    char* path_user_file = ("C:/Users/%s/AppData/Roaming/vs/%s", &user, &file_argv); 
    char* path_saved_file = ("C:/Users/%s/Documents/vs-saved/%s", &user, &file_argv_2);
    char* path_saved_file_temp = ("C:/Users/%s/AppData/Roaming/Temp/%s", &user, &file_argv_2);
    bool does_file_exist = true;

    std::ofstream user_file(path_user_file_temp);
    std::ofstream saved_file(path_saved_file_temp);

    char* error_creating_folder = "error while creating directory or it already exists";

    if(!MTY_Mkdir(path_saved_folder)) {
        printf(error_creating_folder);
    }

    if(!MTY_Mkdir(path_user_folder))
        printf(error_creating_folder);

    char* buf[sizeof(user_data)];
        
    if(!MTY_FileExists(path_user_file)) {
        does_file_exist = false;
        // std::ofstream user_file(path_user_file);
        if(user_file.is_open()) {
            // user_file << "/0";
            char* buf_local = "bin/0";
            if (!MTY_WriteFile(path_user_file, buf, sizeof(buf_local)))
                printf("debug error");
            user_file.close();
            if (!MTY_MoveFile(path_user_file_temp, path_user_file))
                printf("debug error");
        }
    }

    void *file_data;

    if(does_file_exist) {
        if(user_file.is_open()) {
            if(is_binary_file) {
            // read_file_to_binary();
            std::memcpy(&user_data, &user_file, sizeof(user_data));
            // std::memcpy(&user_data, &buf, sizeof(user_data));
            user_file.close();
            // std::ofstream user_file(path_user_file);
            // std::memcpy((char*)&buf, &user_data, sizeof(user_data));
            // user_file << &buf;
            // user_file.close();
            }
            else {
                // read_file_to_string();
                file_data = MTY_ReadFile(path_user_file, (size_t*)1024);
                if(file_data == NULL)
                    printf("debug error");
                std::strcpy((char*)buf, (char*)file_data);
            }
        }
    }
    #endif

#ifndef FRONTEND
    if(!MTY_HasDialogs()) {
        return -1;
    }
    else {
        // MTY_OpenFile();
    }
#endif
    
    Visual vs;
    
    if(vs.init() == init_error) {
        return -1;
    }

    while(vs.is_running()) {
        // if(vs.is_project_loaded()) {
        //     if (!vs.check_project_folder())
        //         printf("debug error");
        //         if(!vs.make_project_folder(vs.project_path()), restore_missing_files) {
        //             printf("debug error");
        //         };
        // }
        vs.wait_event(user_config);
    }

    return 0;

}
