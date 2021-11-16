call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsMSBuildCmd.bat"

msbuild BoardTest.vcxproj /p:Configuration=Release /p:Platform=Win32 /t:Clean;Rebuild
msbuild BoardTest.vcxproj /p:Configuration=Release /p:Platform=x64 /t:Clean;Rebuild