#pragma once
#define WINDOWS_64
#ifdef WINDOWS_64
#include <windows.h>
#endif
#include "config.h"
#include "nodes.h"
#include "variable.h"
#include "parser.h"
#include "connection.h"
#include "libmatoya-main/src/matoya.h"
#include <filesystem>
#include <vector>
#include <cstring>
#include <fstream>

class Visual {

    public:
        Visual();
        ~Visual();

        typedef struct User {
            int debug;
        } User;

        typedef enum Language {
            LANG_PYTHON,
        };
    
        typedef enum File_Type {
            PROJECT_TYPE,
            CLASS_TYPE,
        }

        typedef enum Platform {
            PLATFORM_ALL, // Portable code, non-platform dependent libraries
            PLATFORM_WINDOWS, 
        }; 

        typedef struct File {
            std::filesystem::path file_path;
            char* file_name[64];
            char* file_extension[4];
            int file_size;
            std::vector<unsigned char>file_data;
            std::vector<Vs_Node>vs_node;
            std::vector<Vs_Struct>vs_struct;
            std::vector<Variable>var;
            std::vector<Function>function_ptr;
        };

        typedef struct Class {
            std::vector<Vs_Node>vs_node;
            std::vector<Vs_Struct>vs_struct;
            std::vector<Variable>var;
            std::vector<Function>function_ptr;
        };

        typedef struct Project {
            std::string project_name;
            std::filesystem::path project_path;
            Language lang;
            Platform platform;
            std::vector<File>files;
        };

        int init(Config config);
        void close();
        File make_file(int id, std::string file_name, std::string extension, std::string buffe);
        int save_file(std::string file_name, std::string extension, std::string buffer, std::filesystem::path path);
        void load_file(int id, std::filesystem::path path, size_t size);
        int make_project_files(std::string project_name, std::filesystem::path path);
        int load_project_files();
        bool is_running();
        void wait_event(Config config, MTY_EventFunc event);
        void except(int err_code);

    private:

        void* opaque;
        MTY_App* app;
        MTY_App* app_buf;
        MTY_AppFunc* app_fn;
        MTY_EventFunc* app_event;

        Language lang;
        Platform platform;
        // std::vector<Vs_Class>vs_class;
        std::vector<Vs_Node>vs_node;
        std::vector<Vs_Struct>vs_struct;
        std::vector<Variable>var;
        std::vector<Function>function_ptr;
        std::vector<Includes>include;
        std::vector<File>open_files;
        std::vector<Project>project;
        
        bool is_ctx_running;
        int current_file; 
        bool is_debugging;
        bool is_project_loaded;
        bool auto_save;
        float auto_save_period; 
        float time_debugging;
        
        std::filesystem::path current_file_path;
        std::filesystem::path py_interpreter_path;
        std::filesystem::path default_project_path;
        std::filesystem::path config_path;
        std::error_code ec;

};  