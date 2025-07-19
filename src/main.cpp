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
#include <iostream>
#include "libmatoya-main/src/matoya.h"
#define INIT_ERROR -2
#define FILESYSTEM_ERROR -3
#define MTY_ERROR -4

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

    char* drive = getenv("SystemDrive");
    
    if(drive == NULL) {
        return -1;
    }

    Visual::User user_data;
    Config user_config;
    std::error_code ec;
    auto temp_folder = std::filesystem::temp_directory_path(ec);
    
    if(ec) {
        return -1;
    }

    char file_argv = *"user.txt";
    char file_argv_2 = *"saved.txt";
    char* path_user_folder = ("%s:/Users/%s/AppData/Roaming/vs/", &drive, &user);
    char* path_saved_folder = ("%s:/Users/%s/Documents/vs-saved/", &drive, &user);
    char* path_config_file_temp = ("%s:/Users/%s/AppData/Roaming/Temp/%s", &drive, &user, &file_argv);
    char* path_config_file = ("%s:/Users/%s/AppData/Roaming/vs/%s", &drive, &user, &file_argv); 
    char* path_saved_file = ("%s:/Users/%s/Documents/vs-saved/%s", &drive, &user, &file_argv_2);
    char* path_saved_file_temp = ("%s:/Users/%s/AppData/Roaming/Temp/%s", &drive, &user, &file_argv_2);
    bool is_binary_file = false;
    bool does_file_exist = true;

    std::ofstream config_file(path_config_file_temp);
    std::ofstream saved_file(path_saved_file_temp);

    char* error_creating_folder = "error while creating directory or it already exists";

    if(!MTY_IsSupported()) {
        printf("MTY is not supported");
        return MTY_ERROR;
    }

    if(!MTY_Mkdir(path_saved_folder))
        printf(error_creating_folder);

    if(!MTY_Mkdir(path_user_folder))
        printf(error_creating_folder);

    char* buf[sizeof(config_file)];
        
    if(!MTY_FileExists(path_config_file)) {
        does_file_exist = false;
        // std::ofstream config_file(path_config_file);
        if(config_file.is_open()) {
            char* buf_local = "bin/0";
            if (!MTY_WriteFile(path_config_file_temp, buf_local, sizeof(buf_local)))
                return FILESYSTEM_ERROR;
            config_file.close();
            if (!MTY_MoveFile(path_config_file_temp, path_config_file))
                return FILESYSTEM_ERROR;
        }
    }

    void *file_data;

    if(does_file_exist) {
        if(config_file.is_open()) {
            if(is_binary_file) {
            // read_file_to_binary();
            memcpy(&user_config, &config_file, sizeof(user_data));
            config_file.close();
            // std::memcpy(&user_data, &buf, sizeof(user_data));
            // std::ofstream config_file(path_config_file);
            // std::memcpy((char*)&buf, &user_data, sizeof(user_data));
            // config_file << &buf;
            // config_file.close();
            }
            else {
                // read_file_to_string();
                file_data = MTY_ReadFile(path_config_file, (size_t*)1024);
                if(file_data == NULL)
                    return FILESYSTEM_ERROR;
                strcpy((char*)buf, (char*)file_data);
            }
        }
    }
    #endif

    #ifndef FRONTEND
        if(!MTY_HasDialogs())
            return MTY_ERROR;
    #endif
    
    Visual vs;
    MTY_EventFunc *app_event;

    if(vs.init(user_config) == INIT_ERROR)
        return INIT_ERROR;

    // app = vs.init(user_config, *app_fn, *app_event); 
    
    // if(app == NULL) {
    //     return -1;
    // }

    while(vs.is_running())
        vs.wait_event(user_config, *app_event);

    return 0;

}

    // if(vs.is_project_loaded()) {
    //     if (!vs.check_project_folder())
    //         printf("debug error");
    //         if(!vs.make_project_folder(vs.project_path()), restore_missing_files) {
    //             printf("debug error");
    //         };
    // }
