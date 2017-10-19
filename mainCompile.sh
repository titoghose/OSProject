# Shell scrip for final compilation with all modules 

fileName=$1
fName=${fileName%.*}
gcc $fileName helperFunctions/compileCode.c helperFunctions/uploadClientFile.c helperFunctions/uploadFile.c helperFunctions/downloadFile.c helperFunctions/writeLogs.c -o $fName -lpthread 
