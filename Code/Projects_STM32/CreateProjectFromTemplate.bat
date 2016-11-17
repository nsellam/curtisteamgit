@echo off
color 0A

set TemplateProjectName=Project_Template
set IDE=MDK-ARM

set /P NewProjectName=Project name: 

mkdir "%NewProjectName%"
xcopy /E "%TemplateProjectName%" "%NewProjectName%"
ren "%NewProjectName%\%IDE%\%TemplateProjectName%".uvgui "%NewProjectName%".uvgui
ren "%NewProjectName%\%IDE%\%TemplateProjectName%".uvopt "%NewProjectName%".uvopt
ren "%NewProjectName%\%IDE%\%TemplateProjectName%".uvproj "%NewProjectName%".uvproj
