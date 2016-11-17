@echo off
color 0A

set TemplateProjectName=Project_Template

set /P NewProjectName=Project name: 

mkdir "%NewProjectName%"
xcopy /E "%TemplateProjectName%" "%NewProjectName%"
ren "%NewProjectName%\%TemplateProjectName%".uvgui "%NewProjectName%".uvgui
ren "%NewProjectName%\%TemplateProjectName%".uvopt "%NewProjectName%".uvopt
ren "%NewProjectName%\%TemplateProjectName%".uvproj "%NewProjectName%".uvproj
