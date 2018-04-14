#!/bin/bash

TASKS=(
_list_1
_list_2
_list_3
_list_4
_list_5
_list_6
_list_7
_list_8
_list_9
_list_10
_list_11
_list_12
_list_13
_stack_1
_stack_2
_stack_3
_stack_4
_stack_5
_stack_6
_stack_7
_stack_8
_playlist_1
_playlist_2
_playlist_3
_playlist_4
_playlist_5
_playlist_6
_playlist_7
_playlist_8
_playlist_9
_playlist_10
_playlist_11
_playlist_12
_playlist_13
_playlist_14
_playlist_15
_playlist_16
_playlist_17
_playlist_18
)

TASK_INFO=(
"Tested methods: insertNode + print"
"Tested methods: insertNode + print"
"Tested methods: insertNode + copy constructor + print"
"Tested methods: insertNode + copy constructor + print"
"Tested methods: insertNode + assignment operator + print"
"Tested methods: insertNode + assignment operator + print"
"Tested methods: insertNode + getTail + getHead + findPrev + print"
"Tested methods: insertNode + getTail + getHead + findNode + print"
"Tested methods: insertNode + getTail + findNode + print"
"Tested methods: insertNode + getHead + print"
"Tested methods: insertNode + getHead + deleteNode"
"Tested methods: insertNode + getHead + deleteNode + print"
"Tested methods: insertNode + getHead + getSize + clear + isEmpty + print"
"Tested methods: push + print"
"Tested methods: push + print"
"Tested methods: push + copy constructor + print"
"Tested methods: push + copy constructor + print"
"Tested methods: push + assignment operator + print"
"Tested methods: push + assignment operator + print"
"Tested methods: push + pop + isEmpty +  print"
"Tested methods: push + pop + Top + print"
"Tested methods: load + print + printHistory"
"Tested methods: insertEntry + print + printHistory"
"Tested methods: insertEntry + deleteEntry + print + printHistory"
"Tested methods: insertEntry + deleteEntry + print + printHistory"
"Tested methods: deleteEntry + print + printHistory"
"Tested methods: insertEntry + moveLeft + print + printHistory"
"Tested methods: insertEntry + moveLeft + print + printHistory"
"Tested methods: insertEntry + moveRight + print + printHistory"
"Tested methods: insertEntry + moveRight + print + printHistory"
"Tested methods: load + +reverse + print + printHistory"
"Tested methods: sort + print + printHistory"
"Tested methods: load + sort + print + printHistory"
"Tested methods: load + sort + print + printHistory"
"Tested methods: load + sort + merge + print"
"Tested methods: load + shuffle + print"
"Tested methods: load + shuffle + print"
"Tested methods: load + reverse + undo +  print"
"Tested methods: load + deleteEntry + undo +  print"
)

TASK_FILES=(
"_list_1.cpp"
"_list_2.cpp"
"_list_3.cpp"
"_list_4.cpp"
"_list_5.cpp"
"_list_6.cpp"
"_list_7.cpp"
"_list_8.cpp"
"_list_9.cpp"
"_list_10.cpp"
"_list_11.cpp"
"_list_12.cpp"
"_list_13.cpp"
"_stack_1.cpp"
"_stack_2.cpp"
"_stack_3.cpp"
"_stack_4.cpp"
"_stack_5.cpp"
"_stack_6.cpp"
"_stack_7.cpp"
"_stack_8.cpp"
"_playlist_1.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_2.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_3.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_4.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_5.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_6.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_7.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_8.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_9.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_10.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_11.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_12.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_13.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_14.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_15.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_16.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_17.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
"_playlist_18.cpp Playlist.cpp HistoryRecord.cpp Entry.cpp"
)

PNTS=(
1
4
1
1
1
1
4
4
1
1
1
1
2
5
5
5
1
1
1
1
1
6
4
1
1
1
2
1
2
1
4
2
3
2
6
4
6
6
5
)

GRADE=0

FILES="
Entry.cpp
Entry.hpp
HistoryRecord.cpp
HistoryRecord.hpp
LinkedList.hpp
MyStack.hpp
Node.hpp
Playlist.cpp
Playlist.hpp
"



GRADE=0

FILES="
Entry.cpp
Entry.hpp
HistoryRecord.cpp
HistoryRecord.hpp
LinkedList.hpp
MyStack.hpp
Node.hpp
Playlist.cpp
Playlist.hpp
"


    for i in ${!TASKS[@]}; do

        printf "Testing ${TASKS[${i}]}:" >> grade.txt
        

        g++ ${TASK_FILES[${i}]} -o ${TASKS[${i}]} 2> ${TASKS[${i}]}_compile.err
        # if compiled, test
        if [ $? -eq 0 ]; then
                    
            # to capture segmentation fault
            { timeout 3 stdbuf -i0 -o0 -e0 ./${TASKS[${i}]} > ${TASKS[${i}]}.myout 2> ${TASKS[${i}]}.err ; TIMEOUT=$?; }  2> ${TASKS[${i}]}.sys.err

           if [ $TIMEOUT -eq 124 ]; then
                printf "<Time limit is exceeded>" >> grade.txt
            # valid signals between 1-64
            elif [ $TIMEOUT -ge 129 -a $TIMEOUT -le 192 ]; then
                sig=$(($TIMEOUT - 128))
                kill -l $sig | awk '$0=">"$0'
            # any other return code except 0
            elif [ $TIMEOUT -ne 0 ]; then
                if [ ${i} -eq 20 ] || [ ${i} -eq 21 ]; then
                    echo RETURNED:
                    echo $TIMEOUT | awk '$0=">"$0'
                    echo "Memory leak after clear"
                else
                    echo RETURNED:
                    echo $TIMEOUT | awk '$0=">"$0'
                fi
            fi 


            # if segfault show
            if [ -s ${TASKS[${i}]}.sys.err ]; then
                printf "<SEG. FAULT>" >> grade.txt
            fi

            diff ${TASKS[${i}]}.out ${TASKS[${i}]}.myout > ${TASKS[${i}]}.dif
            d=$?

            # if different display outputs
            if [ $d -eq 1 ]; then
                printf "<output is different>" >> grade.txt
            fi
            
            if [ $d -eq 0 ] && [ ! -s ${TASKS[${i}]}.sys.err ]; then
                printf "PASS\n" >> grade.txt
                GRADE=$(awk "BEGIN {print $GRADE+${PNTS[${i}]}; exit}")
            elif [ $d -eq 1 ]; then
                printf "FAIL\n" >> grade.txt
            elif [ -s ${TASKS[${i}]}.sys.err ]; then
                printf "ERROR\n" >> grade.txt
            else
                printf "ERROR\n" >> grade.txt
            fi            
        else
            printf "COMPILE ERROR\n" >> grade.txt
        fi
        echo
    done

echo

printf "Result: ${GRADE}\n" >> grade.txt

