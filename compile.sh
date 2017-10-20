fileName=$1
outputFileName=${fileName%.*}
ext=${fileName##*\.}
case $ext in
	# To compile c source code 
	c)
		gcc $fileName -o $outputFileName 2> $outputFileName.txt
		if [ ! -s $outputFileName.txt ]; then  
			echo "NO ERROR." > $outputFileName.txt
		fi
		;;

	# To compile c++ source code
	cpp)
		g++ $fileName -o $outputFileName 2> $outputFileName.txt
		if [ ! -s $outputFileName.txt ]; then  
			echo "NO ERROR." > $outputFileName.txt
		fi
		;;
	
	# Unrecognised file type
	*)
		echo "INVALID FILETYPE." > $outputFileName.txt
		;;
esac