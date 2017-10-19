fileName=$1
outputFileName=${fileName%.*}
ext=${fileName##*\.}
case $ext in
	# To compile c source code 
	c)
		if gcc $fileName -o $outputFileName; then  
			echo "NO ERROR." > $outputFileName.txt
		else
			gcc $fileName -o $outputFileName 2> $outputFileName.txt
		fi
		;;

	# To compile c++ source code
	cpp)
		if g++ $fileName -o $outputFileName; then  
			echo "NO ERROR." > $outputFileName.txt
		else
			g++ $fileName -o $outputFileName 2> $outputFileName.txt
		fi
		;;
	
	# Unrecognised file type
	*)
		echo "INVALID FILETYPE." > $outputFileName.txt
		;;
esac