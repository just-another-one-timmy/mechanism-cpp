cd ../docs
rmdir html /s /q
rmdir latex /s /q
doxygen doxyfile
del "*.tmp"
start html/index.html
cd ..
exit
