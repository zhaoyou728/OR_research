@echo off

if "%1"== "" (
echo genpdf @@@.tex
) else (

platex %1||exit/B 0
platex %1
dvipdfmx %~n1
)
 
