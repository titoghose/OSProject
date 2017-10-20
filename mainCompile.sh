# Shell scrip for final compilation with all modules 

fileName=$1
fName=${fileName%.*}
gcc $fileName compileCode.c uploadClientFile.c downloadClientFile.c uploadFile.c downloadFile.c writeLogs.c -o $fName -lpthread
