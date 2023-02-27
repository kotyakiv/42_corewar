#!/bin/bash

neutre='\e[0;m'
green='\e[0;32m'
red='\e[0;31m'

rouge='\033[0;31m'

oldIFS=$IFS
IFS=$'\n'

declare -a players

vm_original=./resources/corewar
vm=./corewar

print_colone () {
	title=$1
	printf "| ${bold}${title}"
	size=${#title}
	while [ "$size" -lt "$2" ];
		do printf " "
		size=$(( $size + 1 ))
	done
}


print_name () {
	str=$1
	printf "| ${str}"
	size=${#str}
	while [ "$size" -lt "$2" ];
		do printf " "
		size=$(( $size + 1 ))
	done
}

print_status () {
	title=$1
	if [ "$title" == "OK" ];then
		printf "| ${green}${title}${neutre}"
	else
		printf "| ${red}${title}${neutre}"
	fi
	size=${#title}
	while [ "$size" -lt "$2" ];
		do printf " "
		size=$(( $size + 1 ))
	done	
}

print_line () {
	print_name $1 "30"
	print_status $2 "8"
	print_status $3 "8"
	print_status $4 "10"
	print_name $5 "45"
	printf "|\n"
}

dump_check () {
	our_dump=$(( $1 - 1 ))
	ori_dump=$(( $2 - 1 ))
}

report () {
	echo "************ SINGLE PLAYER *****************" >> temp/$player_name/report.txt
	echo "COMPILATION:" >> temp/$player_name/report.txt
	echo "YOU: 		./corewar -v 30 $2" >> temp/$player_name/report.txt
	echo "ORIGINE:	./resources/corewar -v 30 $2" >> temp/$player_name/report.txt
	echo -e "\n" >> temp/$player_name/report.txt
	echo "WINNER:" >> temp/$player_name/report.txt
	echo "YOU:		$3" >> temp/$player_name/report.txt
	echo "ORIGINE:	$4" >> temp/$player_name/report.txt
	echo -e "\n" >> temp/$player_name/report.txt
	echo "LAST CYCLE:" >>temp/$player_name/report.txt
	echo "YOU:		$5" >> temp/$player_name/report.txt
	echo "ORIGINE:	$6" >> temp/$player_name/report.txt
	echo -e "\n" >> temp/$player_name/report.txt
	echo -e "CHECKING LAST CYCLE BEFORE END GAME($8): \e[0m" >>temp/$player_name/report.txt
	echo "DIFF RET:		$7" >> temp/$player_name/report.txt

}


rm -rf temp

for player in $(find ./tests/vm/op_codes_champs/cor_files -type f -name "*.cor");
do
#	if grep -sq '.cor' <<< "$player"
	cor_player=$(grep ".cor" <<< "$player")
	if [ -n $"cor_player" ]; then 
		players=( "${players[@]}" $cor_player )
	fi
done

players_size=${#players[@]}
index=0
mkdir -p temp

print_colone "CHAMP_NAME" "30"
print_colone "SINGLE" "8"
print_colone "MULTI" "8"
print_colone "DUMP COMP" "10"
print_colone "COMMENT" "45"
printf "|\n"

while [[ "$index" -lt "$players_size" ]];
do
	player_name=$(echo ${players[$index]} | cut -d'/' -f 6)
	temp=$(( ${#player_name} - 4 ))
	player_name=$(echo $player_name | cut -c 1-$temp)

	single="OK"
	comment="-"
	d_status="OK"
	multi="OK"
	
#TEST SINGLE PLAYER
	mkdir -p temp/$player_name/single_player_test
	$vm_original -v 30 ${players[$index]} > temp/$player_name/single_player_test/$player_name.ori 
	$vm -v 30 ${players["$index"]} > temp/$player_name/single_player_test/$player_name.our

	our_winner=$(grep "has won"  temp/$player_name/single_player_test/$player_name.our | cut -d',' -f 1-2)
	ori_winner=$(grep "has won"  temp/$player_name/single_player_test/$player_name.ori | cut -d',' -f 1-2)
	
	our_last_cycle=$(grep "It is now cycle" temp/$player_name/single_player_test/$player_name.our | cut -d' ' -f 5 | tail -n 1)
	ori_last_cycle=$(grep "It is now cycle" temp/$player_name/single_player_test/$player_name.ori | cut -d' ' -f 5 | tail -n 1)

	dump_check $our_last_cycle $ori_last_cycle

	$vm -dump $our_dump -l ${players[$index]} > temp/$player_name/single_player_test/dump_test.our
	$vm_original -d $ori_dump ${players[$index]} > temp/$player_name/single_player_test/dump_test.ori

	ret_diff=$(diff -w temp/$player_name/single_player_test/dump_test.our temp/$player_name/single_player_test/dump_test.ori)
	if [ "$ret_diff" != "" ];then
		visu_diff=$(diff -w temp/$player_name/single_player_test/dump_test.our temp/$player_name/single_player_test/dump_test.ori)
		report "SINGLE PLAYER" ${players[$index]} $our_winner $ori_winner $our_last_cycle $ori_last_cycle $visu_diff $our_dump
		single="KO"
		comment="More_details_in_temp/$player_name/report.txt"
	else
		report "SINGLE PLAYER" ${players[$index]} $our_winner $ori_winner $our_last_cycle $ori_last_cycle "EMPTY" $our_dump
	fi

	diff_ret=$(diff temp/$player_name/single_player_test/$player_name.ori temp/$player_name/single_player_test/$player_name.our)
	if [ "$diff_ret" != "" ];then
		diff -w temp/$player_name/single_player_test/$player_name.ori temp/$player_name/single_player_yesy/$player_name.our > temp/$player_name/single_player_test/diff_ret.log
		single="KO"
		comment="More_details_in_temp/$player_name/report.txt"
	fi

#DUMP COMP
	j=0
	mkdir -p temp/$player_name/dump_test

	echo -e "\n" >> temp/$player_name/report.txt
	echo "**********************  DUMP TEST *************************" >> temp/$player_name/report.txt
	echo -e "\n" >> temp/$player_name_/report.txt
	echo "Player: ${player_name}" >> temp/$player_name/report.txt
	echo "COMPILATION:" >> temp/$player_name/report.txt
	echo "YOU: 		./corewar -v 30 -dump dump_number ${players[$index]}" >> temp/$player_name/report.txt
	echo -e "ORIGINE:	./resources/corewar -v 30 -d dump_number ${players[$index]}\n" >> temp/$player_name/report.txt

	while [ "$j" -lt "1" ];
	do
		dump="$(($RANDOM))"
		$vm_original -v 30 -d $dump ${players[$index]} > temp/$player_name/dump_test/$dump.ori
		$vm -dump $dump -l -v 30 ${players[$index]} > temp/$player_name/dump_test/$dump.our

		echo "Testing with -dump $dump ..." >> temp/$player_name/report.txt
#		our_last_cycle=$(grep "It is now cycle" temp/$player_name/dump_test/$dump.our | cut -d' ' -f 5 | tail -n 1)
#		ori_last_cycle=$(grep "It is now cycle" temp/$player_name/dump_test/$dump.ori | cut -d' ' -f 5 | tail -n 1)
		
		diff_ret=$(diff -w temp/$player_name/dump_test/$dump.ori temp/$player_name/dump_test/$dump.our)
		if [ "$diff_ret" != "" ];then
			diff -w temp/$player_name/dump_test/$dump.ori temp/$player_name/dump_test/$dump.our > temp/$player_name/dump_test/$dump.log
			d_status="KO"
			comment="More_details_in_temp/$player_name/report.txt"
			echo -e "TEST FAILED. Check temp/$player_name/dump_test/$dump.log for more details\n" >> temp/$player_name/report.txt
		else
			echo -e "TEST SUCCEED\n" >> temp/$player_name/report.txt
		fi

		j=$(( $j + 1 ))
	done

#MULTI
	j=1
	mkdir -p temp/$player_name/multi

	echo -e "\n" >> temp/$player_name/report.txt
	echo -e "**********************  MULTI *************************\n" >> temp/$player_name/report.txt
	
	while [ "$j" -lt "3" ];
	do
		echo -e "Match $j:\n" >> temp/$player_name/report.txt
		mkdir -p temp/$player_name/multi/match_$j
		tt_player=$(($RANDOM % 4 ))
		if [[ $tt_player == 1 ]];then
			echo "1 player"
		elif [[ $tt_player == 2 ]];then
			p1=$(($RANDOM % 16 ))
			$vm_original -v 30 ${players[$index]}  ${players[$p1]} > temp/$player_name/multi/match_$j/game.ori 
			$vm -v 30 ${players["$index"]} ${players[$p1]} > temp/$player_name/multi/match_$j/game.our
			echo -e "Players List: ${player_name}\n\t\t\t${players[$p1]}\n" >> temp/$player_name/report.txt
			echo "YOU: 		./corewar -v 30  ${players[$index]} ${players[$p1]}" >> temp/$player_name/report.txt
			echo -e "ORIGINE:	./resources/corewar -v 30 ${players[$index]} ${players[$p1]}\n" >> temp/$player_name/report.txt

		elif [[ $tt_player == 3 ]];then
			p1=$(($RANDOM % 16 ))
			p2=$(($RANDOM % 16 ))
			$vm_original -v 30 ${players[$p2]} ${players[$index]}  ${players[$p1]} > temp/$player_name/multi/match_$j/game.ori 
			$vm -v 30 ${players[$p2]} ${players["$index"]} ${players[$p1]} > temp/$player_name/multi/match_$j/game.our
			echo -e "Players List: ${player_name}\n\t\t\t${players[$p1]}\n\t\t\t${players[$p2]}\n" >> temp/$player_name/report.txt
			echo "YOU: 		./corewar -v 30  ${players[$p2]} ${players[$index]} ${players[$p1]}" >> temp/$player_name/report.txt
			echo -e "ORIGINE:	./resources/corewar -v 30 ${players[$p2]} ${players[$index]} ${players[$p1]}\n" >> temp/$player_name/report.txt
		else
			p1=$(($RANDOM % 16 ))
			p2=$(($RANDOM % 16 ))
			p3=$(($RANDOM % 16 ))
			$vm_original -v 30 ${players[$p3]} ${players[$p2]} ${players[$index]}  ${players[$p1]} > temp/$player_name/multi/match_$j/game.ori 
			$vm -v 30 ${players[$p3]} ${players[$p2]} ${players["$index"]} ${players[$p1]} > temp/$player_name/multi/match_$j/game.our
			echo -e "Players List: ${player_name}\n\t\t\t${players[$p1]}\n\t\t\t${players[$p2]}\n\t\t\t${players[$p3]}\n" >> temp/$player_name/report.txt
			echo "YOU: 		./corewar -v 30  ${players[$p3]} ${players[$p2]} ${players[$index]} ${players[$p1]}" >> temp/$player_name/report.txt
			echo -e "ORIGINE:	./resources/corewar -v 30 ${players[$p3]} ${players[$p2]} ${players[$index]} ${players[$p1]}\n" >> temp/$player_name/report.txt
			
		fi

		our_winner=$(grep "has won"  temp/$player_name/multi/match_$j/game.our | cut -d',' -f 1-2)
		ori_winner=$(grep "has won"  temp/$player_name/multi/match_$j/game.ori | cut -d',' -f 1-2)

		
		our_last_cycle=$(grep "It is now cycle" temp/$player_name/multi/match_$j/game.our | cut -d' ' -f 5 | tail -n 1)
		ori_last_cycle=$(grep "It is now cycle" temp/$player_name/multi/match_$j/game.ori | cut -d' ' -f 5 | tail -n 1)
		
		dump_check $our_last_cycle $ori_last_cycle
		
		k=0
		mkdir -p temp/$player_name/multi/match_$j/dump

		echo "WINNER:" >> temp/$player_name/report.txt
		echo "YOU:		$our_winner" >> temp/$player_name/report.txt
		echo "ORIGINE:	$ori_winner" >> temp/$player_name/report.txt
		echo -e "\n" >> temp/$player_name/report.txt
		echo "LAST CYCLE:" >>temp/$player_name/report.txt
		echo "YOU:		$our_last_cycle" >> temp/$player_name/report.txt
		echo "ORIGINE:	$ori_last_cycle" >> temp/$player_name/report.txt
		echo -e "\n" >> temp/$player_name/report.txt

	
		if [[ $tt_player == 1 ]];then
			echo "1 player"
		elif [[ $tt_player == 2 ]];then

			$vm -dump $our_dump -l ${players[$index]} ${players[p1]} > temp/$player_name/multi/match_$j/dump/dump_test.our
			$vm_original -d $ori_dump ${players[$index]} ${players[p1]} > temp/$player_name/multi/match_$j/dump/dump_test.ori
			echo "CHECKING LAST CYCLE BEFORE END GAME($our_dump):" >>temp/$player_name/report.txt
	
			ret_diff=$(diff -w temp/$player_name/multi/match_$j/dump/dump_test.our temp/$player_name/multi/match_$j/dump/dump_test.ori)
			if [ "$ret_diff" != "" ];then
				visu_diff=$(diff -w temp/$player_name/multi/match_$j/dump/dump_test.our temp/$player_name/multi/match_$j/dump/dump_test.ori)
				echo -e "DIFF RET:	$visu_diff\n" >> temp/$player_name/report.txt
				multi="KO"
				comment="More_details_in_temp/$player_name/report.txt"
			else
				echo -e "DIFF RET:	EMPTY\n" >> temp/$player_name/report.txt
			fi

			while [ "$k" -lt "2" ];
			do
				dump="$(($RANDOM))"
				echo "(MATCH $j)Testing with -dump $dump ..." >> temp/$player_name/report.txt

				$vm_original -v 30 ${players[$index]}  ${players[$p1]} > temp/$player_name/multi/match_$j/dump/$dump.ori 
				$vm -v 30 ${players["$index"]} ${players[$p1]} > temp/$player_name/multi/match_$j/dump/$dump.our
		
				diff_ret=$(diff -w temp/$player_name/multi/match_$j/dump/$dump.ori temp/$player_name/multi/match_$j/dump/$dump.our)
				if [ "$diff_ret" != "" ];then
					diff -w temp/$player_name/multi/match_$j/dump/$dump.ori temp/$player_name/multi/match_$j/dump/$dump.our > temp/$player_name/multi/match_$j/dump/$dump.log
					multi="KO"
					comment="More_details_in_temp/$player_name/report.txt"
					echo -e "TEST FAILED. Check temp/$player_name/multi/match_$j/dump/$dump.log for more details\n" >> temp/$player_name/report.txt
				else
					echo -e "TEST SUCCEED\n" >> temp/$player_name/report.txt
				fi
				k=$(( $k + 1 ))
			done
		elif [[ $tt_player == 3 ]];then

			$vm -dump $our_dump -l ${players[$p2]} ${players[$index]} ${players[p1]} > temp/$player_name/multi/match_$j/dump/dump_test.our
			$vm_original -d $ori_dump ${players[$p2]} ${players[$index]} ${players[p1]} > temp/$player_name/multi/match_$j/dump/dump_test.ori
			echo "CHECKING LAST CYCLE BEFORE END GAME($our_dump):" >>temp/$player_name/report.txt
			ret_diff=$(diff -w temp/$player_name/multi/match_$j/dump/dump_test.our temp/$player_name/multi/match_$j/dump/dump_test.ori)
			if [ "$ret_diff" != "" ];then
				visu_diff=$(diff -w temp/$player_name/multi/match_$j/dump/dump_test.our temp/$player_name/multi/match_$j/dump/dump_test.ori)
				echo -e "DIFF RET:	$visu_diff\n" >> temp/$player_name/report.txt
				multi="KO"
				comment="More_details_in_temp/$player_name/report.txt"
			else
				echo -e "DIFF RET:	EMPTY\n" >> temp/$player_name/report.txt
			fi

			while [ "$k" -lt "2" ];
			do
				dump="$(($RANDOM))"
				echo "(MATCH $j)Testing with -dump $dump ..." >> temp/$player_name/report.txt

				$vm_original -v 30 ${players[$p2]} ${players[$index]}  ${players[$p1]} > temp/$player_name/multi/match_$j/dump/$dump.ori 
				$vm -v 30 ${players[$p2]} ${players["$index"]} ${players[$p1]} > temp/$player_name/multi/match_$j/dump/$dump.our
		
				diff_ret=$(diff -w temp/$player_name/multi/match_$j/dump/$dump.ori temp/$player_name/multi/match_$j/dump/$dump.our)
				if [ "$diff_ret" != "" ];then
					diff -w temp/$player_name/multi/match_$j/dump/$dump.ori temp/$player_name/multi/match_$j/dump/$dump.our > temp/$player_name/multi/match_$j/dump/$dump.log
					multi="KO"
					comment="More_details_in_temp/$player_name/report.txt"
					echo -e "TEST FAILED. Check temp/$player_name/multi/match_$j/dump/$dump.log for more details\n" >> temp/$player_name/report.txt
				else
					echo -e "TEST SUCCEED\n" >> temp/$player_name/report.txt
				fi
				k=$(( $k + 1 ))
			done
		else

			$vm -dump $our_dump -l ${players[$p3]} ${players[$p2]} ${players[$index]} ${players[p1]} > temp/$player_name/multi/match_$j/dump/dump_test.our
			$vm_original -d $ori_dump ${players[$p3]} ${players[$p2]} ${players[$index]} ${players[p1]} > temp/$player_name/multi/match_$j/dump/dump_test.ori
			echo "CHECKING LAST CYCLE BEFORE END GAME($our_dump):" >>temp/$player_name/report.txt

			ret_diff=$(diff -w temp/$player_name/multi/match_$j/dump/dump_test.our temp/$player_name/multi/match_$j/dump/dump_test.ori)
			if [ "$ret_diff" != "" ];then
				visu_diff=$(diff -w temp/$player_name/multi/match_$j/dump/dump_test.our temp/$player_name/multi/match_$j/dump/dump_test.ori)
				echo -e "DIFF RET:	$visu_diff\n" >> temp/$player_name/report.txt
				multi="KO"
				comment="More_details_in_temp/$player_name/report.txt"
			else
				echo -e "DIFF RET:	EMPTY\n" >> temp/$player_name/report.txt
			fi

			while [ "$k" -lt "2" ];
			do
				dump="$(($RANDOM))"
				echo "(MATCH $j)Testing with -dump $dump ..." >> temp/$player_name/report.txt

				$vm_original -v 30 ${players[$p3]} ${players[$p2]} ${players[$index]}  ${players[$p1]} > temp/$player_name/multi/match_$j/dump/$dump.ori 
				$vm -v 30 ${players[$p3]} ${players[$p2]} ${players["$index"]} ${players[$p1]} > temp/$player_name/multi/match_$j/dump/$dump.our
		
				diff_ret=$(diff -w temp/$player_name/multi/match_$j/dump/$dump.ori temp/$player_name/multi/match_$j/dump/$dump.our)
				if [ "$diff_ret" != "" ];then
					diff -w temp/$player_name/multi/match_$j/dump/$dump.ori temp/$player_name/multi/match_$j/dump/$dump.our > temp/$player_name/multi/match_$j/dump/$dump.log
					multi="KO"
					comment="More_details_in_temp/$player_name/report.txt"
					echo -e "TEST FAILED. Check temp/$player_name/multi/match_$j/dump/$dump.log for more details\n" >> temp/$player_name/report.txt
				else
					echo -e "TEST SUCCEED\n" >> temp/$player_name/report.txt
				fi
				k=$(( $k + 1 ))
			done
		fi
		j=$(( $j + 1 ))
	done
	







#	$vm_original -v 30 ${players[$index]} ${players[$index_player]} > temp/$player_name/multi/one.ori
#	$vm -v 30 ${players[$index]} ${players[$index_player]} > temp/$player_name/multi/one.our


#	diff_ret=$(diff -w temp/$player_name/multi/one.ori temp/$player_name/multi/one.our)

#	if [ "$diff_ret" != "" ];then
#		diff -w temp/$player_name/multi/one.ori temp/$player_name/multi/one.our > temp/$player_name/multi/diff_one.log
#		multi="KO"
#		comment="More_details_in_temp/$player_name"
#	fi
	print_line $player_name $single $multi $d_status $comment
index=$(( $index + 1 ))
done