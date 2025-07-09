#pragma once
#define WINDOWS_64
#ifdef WINDOWS_64
#include <windows.h>
#endif
#include "config.h"
#include "nodes.h"
#include "parser.h"
#include "connection.h"
#include "libmatoya-main/src/matoya.h"
#include <filesystem>
#include <vector>
#include <cstring>

class Visual {

    public:
        Visual();
        ~Visual();

        typedef struct User {
            int debug;
        } User;

        int init();
        void close();
        bool make_project_files();
        bool load_project_files();
        bool is_running();
        void wait_event(Config config);
        void except(int err_code);

    private:

        typedef enum Language {
            PYTHON,
        };
    
        typedef enum Platform {
            ALL, // Portable code, non-platform dependent libraries
            WINDOWS, 
        }; 

        Language lang;
        Platform platform;
        // std::vector<Vs_Class>vs_class;
        std::vector<Vs_Node>vs_node;
        std::vector<Vs_Struct>vs_struct;
        std::vector<Variable>var;
        std::vector<Function>function_ptr;
        std::vector<Includes>include;
        
        bool is_debugging;
        bool is_project_loaded;
        bool auto_save;
        float auto_save_period; 
        float time_debugging;
        
        std::filesystem::path open_file_path;
        std::filesystem::path py_interpreter_path;
        std::filesystem::path default_project_path;
        std::filesystem::path config_path;
        std::error_code ec;

};  