# Shell scrip for final compilation with all modules 

fileName=$1
fName=${fileName%.*}
gcc $fileName compileCode.c uploadClientFile.c uploadFile.c downloadFile.c -o $fName