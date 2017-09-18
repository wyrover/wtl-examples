BOOK_CODE_PATH = "E:/book-code"
THIRD_PARTY = "E:/book-code/3rdparty"
WORK_PATH = os.getcwd()
includeexternal (BOOK_CODE_PATH .. "/premake-vs-include.lua")




workspace(path.getname(os.realpath(".")))
    language "C++"
    location "build/%{_ACTION}/%{wks.name}"    
    if _ACTION == "vs2015" then
        toolset "v140_xp"
    elseif _ACTION == "vs2013" then
        toolset "v120_xp"
    end

    --include (BOOK_CODE_PATH .. "/common.lua")    
    

    group "test"       
        

--        create_mfc_console_project("test_filesystem", "src")
--            includedirs
--            {
--                "%{THIRD_PARTY}/googletest/googletest/include",
--                "%{THIRD_PARTY}/googletest/googletest",
--                "%{THIRD_PARTY}/googletest/googlemock/include",
--                "%{THIRD_PARTY}/googletest/googlemock"
--            }
--            links
--            {
--                "gtest",
----                "crypt32.lib",
----                "winhttp.lib"
--            }

        create_dll_project("wtl_windows_dll", "src")
            includedirs
            {
                "src",
                "3rdparty/wtl"
            }

        create_wtl_project("wtl_dialog_template", "src")
            includedirs
            {
                "src",
                "3rdparty/wtl"
            }

        create_wtl_project("wtl_dialog_template_2", "src")
            includedirs
            {
                "src",
                "src/wtl_dialog_template_2",
                "3rdparty/wtl",
                "%{THIRD_PARTY}"
            }

        create_wtl_project("wtl_windows_template", "src")
            includedirs
            {
                "src",
                "3rdparty/wtl"
            }

        

        create_wtl_project("wtl_listview", "src")
            includedirs
            {
                "src",
                "src/wtl_listview",
                "src/wtl_listview/source",
                "3rdparty/wtl"
            }

        create_wtl_project("leafanalysis", "src")
            includedirs
            {
                "src",
                "src/leafanalysis",                
                "3rdparty/wtl"
            }
            
        create_wtl_project("wtl_layered_window", "src")
            includedirs
            {
                "src",
                "3rdparty/wtl"
            }
            
            
        create_console_project("worker_thread_client", "src")


    group "wtl_draw_examples"
        matches = os.matchdirs("src/wtl_draw_examples/wtl_draw_*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_wtl_project(project_name, "src/wtl_draw_examples")
            
            
        end

    group "wtl_gdiplus_examples"
        matches = os.matchdirs("src/wtl_gdiplus_examples/*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_wtl_project(project_name, "src/wtl_gdiplus_examples")
            
            
        end


    group "wtl_control_examples"
        matches = os.matchdirs("src/wtl_control_examples/*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_wtl_project(project_name, "src/wtl_control_examples")
            
            
        end

    group "wtl_directx_examples"
        matches = os.matchdirs("src/wtl_directx_examples/*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_wtl_project(project_name, "src/wtl_directx_examples")
            
            
        end

    
    group "mfc_draw_examples"
        matches = os.matchdirs("src/mfc_draw_examples/*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_mfc_project(project_name, "src/mfc_draw_examples")
            
            
        end
     
    
    group "wtl_encrypt_decrypt"
        matches = os.matchdirs("src/wtl_encrypt_decrypt/*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_wtl_project(project_name, "src/wtl_encrypt_decrypt")
            
            
        end
        

    group "tetris_examples"
        matches = os.matchdirs("src/tetris_examples/*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_wtl_project(project_name, "src/tetris_examples")
            
            
        end



    group "alphablending_examples"
        matches = os.matchdirs("src/alphablending_examples/*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_wtl_project(project_name, "src/alphablending_examples")
            
            
        end

    group "game_examples"
        matches = os.matchdirs("src/game_examples/*")
        for i = #matches, 1, -1 do
            --p.w(path.getname(matches[i]))  
            local project_name = path.getname(matches[i])
            
            create_wtl_project(project_name, "src/game_examples")
            
            
        end

        