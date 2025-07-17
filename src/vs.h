#pragma once
#define WINDOWS_64
#ifdef WINDOWS_64
#include <windows.h>
#endif
#include "config.h"
#include "nodes.h"
#include "variable.h"
#include "parser.h"
#include "node_connection.h"
#include "struct.h"
#include "libmatoya-main/src/matoya.h"
#include <filesystem>
#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>

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
    
        typedef enum Type {
            TYPE_PROJECT,
            TYPE_CLASS,
            TYPE_JSON,
        };

        typedef enum Platform {
            PLATFORM_ALL, // Portable code, non-platform dependent libraries
            PLATFORM_WINDOWS, 
        }; 

        typedef struct projectFile {
            Type type; 
            // std::filesystem::path file_path;
            std::string file_name;
            std::string file_extension;
        };

        typedef struct File { // : projectFile {
            uint32_t is_valid;
            Type type; 
            // std::filesystem::path file_path;
            std::string file_name;
            std::string file_extension;
            size_t data_size;
            // std::vector<int>vector_size_t;
            std::vector<std::string>file_data;
        };
        
        typedef struct Class {
            std::string class_name;
            std::vector<Vs_Node>vs_node;
            std::vector<Vs_Struct>vs_struct;
            std::vector<Variable>var;
            std::vector<Function>function;
        };

        typedef struct Project {
            std::string project_name;
            std::filesystem::path project_path;
            Language lang;
            Platform platform;
            std::vector<projectFile>files;
        };

        int init(Config config);
        void close();
        void wait_event(Config config, MTY_EventFunc event);
        void except(int error_code);
        bool is_running();
        
        File make_file(Type id, std::string file_name, std::string extension, char* data, size_t* size);
        File load_file(Type id, std::filesystem::path path, size_t* size);
        int save_file(File file, std::filesystem::path path);
        int make_project_files(std::string project_name, std::filesystem::path path);
        int load_project_files(std::filesystem::path path);

        std::string push_class_to_buf(Class *c);
        std::string push_project_to_buf(Project *p);
        Class pull_buf_to_class(std::string *buf);
        Project pull_buf_to_project(std::string *buf);

    private:
        void* opaque;
        MTY_App *app;
        MTY_App app_buf;
        MTY_AppFunc *app_fn;
        MTY_EventFunc *app_event;

        Language lang;
        Platform platform;
        std::vector<Class>vs_class;
        std::vector<Vs_Node>vs_node;
        std::vector<Connection>connection;
        std::vector<Struct>vs_struct;
        std::vector<Struct>instance;
        std::vector<Variable, std::vector<int>>int_var;
        std::vector<Variable, std::vector<float>>float_var;
        std::vector<Variable, std::vector<double>>double_var;
        std::vector<Function>function;
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
        int class_id;
        int project_id;
        
        std::filesystem::path current_file_path;
        // std::filesystem::path py_interpreter_path;
        std::filesystem::path default_project_path;
        std::filesystem::path config_path;
        std::error_code ec;

};  