cmake -BImageCompressor -S. /y
xcopy /e /k /h /i include\ ImageCompressor\include\ /y
xcopy /e /k /h /i src\ ImageCompressor\src\ /y
xcopy .\Qt\bin\Qt5Gui.dll .\ImageCompressor\Release\ /y
xcopy .\Qt\bin\Qt5Core.dll .\ImageCompressor\Release\ /y
::xcopy .\Qt\lib\Qt5Widgets.dll .\ImageCompressor\Release\ /y
cmake --build ImageCompressor\ --config Release