cmake -BImageCompressor -S. /y
xcopy /e /k /h /i include\ ImageCompressor\include\ /y
xcopy /e /k /h /i src\ ImageCompressor\src\ /y
xcopy D:\Qt\5.15.2\msvc2019_64\bin\Qt5Gui.dll ImageCompressor\Release\ /y
xcopy D:\Qt\5.15.2\msvc2019_64\bin\Qt5Core.dll ImageCompressor\Release\ /y
xcopy D:\Qt\5.15.2\msvc2019_64\bin\Qt5Widgets.dll ImageCompressor\Release\ /y
cmake --build ImageCompressor\ --config Release