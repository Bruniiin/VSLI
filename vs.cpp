#include "vs.h"
#define APP_ERROR -1
#define FILESYSTEM_ERROR -2

int Visual::init(Config config)
{

    project.clear();
    open_files.clear();

    auto temp_folder = std::filesystem::temp_directory_path(ec);
    if(ec) {
        except(FILESYSTEM_ERROR);
        return -1;
    }

    char* default_project_name = "untitled-project";

    project.push_back({
        default_project_name,
        temp_folder,
        LANG_PYTHON, // default lang
        PLATFORM_ALL, // default platform
    });

    char* default_file_name = "untitled-file";
    char* default_extension = ".vs";

    current_file = 0;

    open_files.push_back({
            temp_folder,
            default_file_name,
            default_extension, 
    });

    // temp

    for(auto f : open_files) {
        vs_node = f.vs_node;
        vs_struct = f.vs_struct;
        var = f.var;
    }

    for(auto p : project) { 
        p.files.push_back(open_files.front());
    }

    app = MTY_AppCreate((MTY_AppFlag)NULL, *app_fn, *app_event, opaque);
    if(app == NULL) {
        except(APP_ERROR);
    }
    app_buf = app;
    
    MTY_AppRun(app);

    is_ctx_running = true;

    return 1;
}

Visual::File Visual::make_file(File file, std::filesystem::path path)
{
    
}

Visual::Project Visual::make_project_files(std::string project_name, std::filesystem::path path)
{
    Project project{
        project_name,
        path,
        LANG_PYTHON, // default lang
        PLATFORM_ALL, // default platform
    };

    //char* buf[sizeof(file)];
    
    File file{};

    file = make_file(project_name, ".vsproj", buf, path);

    char* file_name = "untitled-file";
    char* extension = ".vs";

    File file{};

    //char* buf[sizeof(file)];

    file = make_file(file_name, extension, buf, path);

    open_files.push_back({file}); 

    return project;
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
