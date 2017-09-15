@echo off

"C:\Program Files\Doxygen\bin\doxygen.exe" doxyfile
copy .\CodeProject\TabViewCtrl.jpg .\Docs\html\TabViewCtrl.jpg

"C:\Program Files\HTML Help Workshop\hhc.exe" .\Docs\html\index.hhp

copy .\Docs\html\index.chm .\Docs\CWTLTabViewCtrl.chm
rd /s /q .\Docs\html\