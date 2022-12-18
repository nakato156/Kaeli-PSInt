if not %errorlevel%=0 goto :notfound

md build
cmake -B build
cmake --build build -v
goto :eof

:notfound
echo No se pudo encontrar cmake.