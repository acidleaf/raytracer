-- A premake4 build script used to compile a basic SDL application using OpenGL for rendering

solution "raytracer"
	configurations { "Debug", "Release" }
	
	project "raytracer"
		targetname = project
		kind "ConsoleApp"
		language "C++"
		
		pchheader "include/pch.hpp"
		
		
		files { "include/**.h", "src/**.cc" }
		includedirs { "include", "include/**" }
		links { "SDL2", "glew" }
		
		buildoptions { "--std=c++11" }
		
		if os.is("windows") then
			includedirs { "D:/Lib/SDL/i686-w64-mingw32/include" }
			libdirs { "D:/Lib/SDL/i686-w64-mingw32/lib"}
			links { "mingw32", "opengl32", "SDL2main" }
			
		elseif os.is("macosx") then
			includedirs { "/usr/local/include" }
			libdirs { "/usr/local/lib"}
			linkoptions { "-framework OpenGL" }
		end
		
		
		
		
		configuration "Debug"
			targetdir "bin/Debug"
			objdir "obj/Debug"
			flags { "Symbols" }
			
			buildoptions { "-Wall" }
			
			if os.is("windows") then
				buildoptions { "-mconsole" }		-- Console for logging debug output (Windows)
			end
			
		configuration "Release"
			targetdir "bin/Release"
			objdir "obj/Release"
			flags { "Optimize" }