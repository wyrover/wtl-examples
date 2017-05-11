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

    include ("common.lua")   
    

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

        create_dll_project("wtl_dialog_template", "src")
            includedirs
            {
                "src",
                "3rdparty/wtl"
            }

        create_dll_project("wtl_windows_template", "src")
            includedirs
            {
                "src",
                "3rdparty/wtl"
            }
            
            