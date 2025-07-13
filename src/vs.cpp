#include "vs.h"
// #define DEBUG
#define APP_ERROR -1
#define FILESYSTEM_ERROR -2

int Visual::init(Config config)
{
    project.clear();
    open_files.clear();

    auto temp_folder = std::filesystem::temp_directory_path(ec);
    if(ec)
        return FILESYSTEM_ERROR;

    char* default_project_name = "untitled-project";
    char* default_project_extension = ".vsproj";

    project.push_back({
        default_project_name,
        temp_folder,
        LANG_PYTHON, // default lang
        PLATFORM_ALL, // default platform
    });

    project.front().files.push_back({
        TYPE_CLASS,
        default_project_name,
        default_project_extension,
        temp_folder,
    });

    char* default_file_name = "untitled-file";
    char* default_extension = ".vs";

    char* data[sizeof(Class)];
    File file;
    file = make_file(TYPE_CLASS, default_file_name, default_extension, *data);
    if(!save_file(file, temp_folder))
        return FILESYSTEM_ERROR;

    current_file = 0;

    // open_files.push_back({file});

    // temp
    // for(auto f : open_files) {
    //     vs_node = f.vs_node;
    //     vs_struct = f.vs_struct;
    //     var = f.var;
    // }

    // for(auto p : project) { 
    //     p.files.push_back(open_files.front());
    // }

    app = MTY_AppCreate((MTY_AppFlag)NULL, *app_fn, *app_event, opaque);
    if(app == NULL) {
        except(APP_ERROR);
    }
    app_buf = app;
    
    MTY_AppRun(app);

    is_ctx_running = true;

    return 1;
}

int Visual::save_file(File file, std::filesystem::path path)
{   
    // int path_size = file_name.size() + extension.size() + path.size();
    #ifdef DEBUG
    std::string file_path = ("%s/%s.%s", path, file_name, extension);
    std::ofstream file(file_path);
    if(!MTY_WriteFile((char*)&file_path, (char*)&buffer, buffer.size()))
        return FILESYSTEM_ERROR;
    file.close();
    #else
    #endif

    return 1;
}

Visual::File Visual::load_file(int id, std::filesystem::path path, size_t size)
{

}

Visual::File Visual::make_file(int id, std::string file_name, std::string extension, char* data, size_t size, std::vector<int>vector_size_t)
{
    File file{};
    file.file_name = file_name;
    file.file_extension = extension; 
    file.data_size = size;
    file.vector_size_t = vector_size_t;
    file.file_data.push_back({*data});

    return file;
}

int Visual::make_project_files(std::string project_name, std::filesystem::path path)
{
    // Project project{
    //     project_name,
    //     path,
    //     LANG_PYTHON, // default lang
    //     PLATFORM_ALL, // default platform
    // };

    project.push_back({
        project_name,
        path,
        LANG_PYTHON,
        PLATFORM_ALL,
    });

    char* data[sizeof(project)];

    char* file_name = "untitled-project";
    char* extension = ".vsproj";

    File file{};

    file = make_file(TYPE_PROJECT, file_name, extension, *data);
    if(!save_file(file, path))
        return FILESYSTEM_ERROR;

    char* file_name = "untitled-file";
    char* extension = ".vs";

    File file{};

    char* data[sizeof(file)];

    file = make_file(TYPE_CLASS, file_name, extension, *data);
    if(!save_file(file, path))
        return FILESYSTEM_ERROR;

    open_files.push_back({file}); 

    return 1;
}

bool Visual::load_project_files(std::filesystem::path path)
{
    return false;
}

bool Visual::is_running()
{
    if(app == NULL) {
        return false;
    }

    if(is_ctx_running)
        return true;
    else
        return false;
}

void Visual::wait_event(Config config, MTY_EventFunc event)
{
    
}

void Visual::except(int error_code)
{
    std::cout << "error: " << error_code << std::endl;
}
