#!/bin/bash

# valid files

# for FILE in valid_asm/*.s; do
# 	./myasm $FILE
# 	#leaks -atExit -quiet -- "./myasm" "$FILE" >> "Leaks.txt"
# done

# for FILE in valid_asm/*.cor; do
# 	NAME=$(echo $FILE | awk '{split($0,a,"/"); print a[2]}')
# 	mv valid_asm/$NAME valid_asm/my_valid/
# done

# for FILE in valid_asm/*.s; do
# 	./ofasm $FILE
# done

# for FILE in valid_asm/*.cor; do
# 	NAME=$(echo $FILE | awk '{split($0,a,"/"); print a[2]}')
# 	mv valid_asm/$NAME valid_asm/of_valid/
# done

# for FILE in valid_asm/of_valid/*.cor; do
# 	NAME=$(echo $FILE | awk '{split($0,a,"/"); print a[3]}')
# 	echo "Comapre $FILE"
# 	diff -y $FILE valid_asm/my_valid/$NAME >> valid.txt
# done

# exit 0

# invalid files

for FILE in error_files/*.s; do
	./myasm $FILE
	leaks -atExit -quiet -- "./myasm" "$FILE" >> "Leaks.txt"
done

# find leaks

cat Leaks.txt | grep " leaks"

exit 0
# clean all .cor files

rm valid_asm/of_valid/*.cor
rm valid_asm/my_valid/*.cor
