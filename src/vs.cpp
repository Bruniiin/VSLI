#include "vs.h"
// #define DEBUG
#define APP_ERROR -1
#define FILESYSTEM_ERROR -2

int Visual::init(Config config)
{
    project.clear();
    vs_class.clear();
    vs_node.clear();
    vs_struct.clear();

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
    });

    char* default_file_name = "untitled-file";
    char* default_extension = ".vs";

    auto temp_folder = std::filesystem::temp_directory_path(ec);
    if(ec)
        return FILESYSTEM_ERROR;
    char* data[sizeof(Class)];
    File file{};
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
    std::string data;
    std::string file_path = ("%s/%s.%s", path, file.file_name, file.file_extension);
    
    data.append((char*)file.vector_size_t.size());
    data.append((char*)file.vector_size_t.data()); // uh
    data.append((char*)file.file_data.size());
    data.append((char*)file.file_data.data());
    
    if(MTY_WriteFile((char*)&file_path, (char*)&data, file.data_size))
        return FILESYSTEM_ERROR;
    #endif

    return 1;
}

Visual::File Visual::load_file(int id, std::filesystem::path path, size_t size)
{
    File file{};

    return file; 
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

    int id = project.size();

    char* file_name = "untitled-project";
    char* extension = ".vsproj";

    std::string data = push_project_to_buf(project.front());
    File file{};

    file = make_file(TYPE_PROJECT, file_name, extension, (char*)&data);
    if(!save_file(file, path))
        return FILESYSTEM_ERROR;

    char* file_name = "untitled-file";
    char* extension = ".vs";
    
    std::string data = push_class_to_buf(vs_class.front());
    File file{};
    
    file = make_file(TYPE_CLASS, file_name, extension, (char*)&data);
    if(!save_file(file, path))
        return FILESYSTEM_ERROR;

    open_files.push_back({file}); 

    return 1;
}

int Visual::load_project_files(std::filesystem::path path)
{
    if(!MTY_FileExists((char*)&path))
        return FILESYSTEM_ERROR;
    size_t file_size = std::filesystem::file_size(path);
    File file = load_file(TYPE_PROJECT, path, file_size);
    std::string file_data = *file.file_data.data();
    Project project_buf = push_buf_to_project(file_data);
    project.push_back({project_buf});
    
    return 1;
}

bool Visual::is_running()
{
    if(app == NULL || is_ctx_running == false)
        return false;
    else
        return true;
}

void Visual::wait_event(Config config, MTY_EventFunc event)
{
    
}

void Visual::except(int error_code)
{
    std::cout << "error: " << error_code << std::endl;
}
