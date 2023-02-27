.name "Alexander the great and Solomon the wise"
.comment "Ekin says xywuywdyu 	qq7yst   t7qy"

# init r10
ld	%0, r3
add r1, r3, r10

# init reg with loop values
ld %57674240, r4
ld %100728832, r5
ld %32768880, r6
ld %184548359, r7
ld %1409483523, r8
ld %167768320, r9

# prepare a trap:
ld %251658242, r11
ld %2415919104, r12
ld %66644, r13
ld %16843017, r14
ld %4293984256, r15

# set a trap at our start
st r11, -89
st r12, -90
st r13, -91
st r14, -92
st r15, -93

# set a trap before first loop
st r11, 500
st r12, 499
st r13, 498
st r14, 497
st r15, 496

# copy first loop
st r4, 497
st r5, 496
st r6, 495
st r7, 494
st r8, 493
st r9, 492

# live at least once
or r3, r3, r3
st 	r10, 6
live %500
lfork %460

# set a trap before second loop
st r11, 500
st r12, 499
st r13, 498
st r14, 497
st r15, 496

# copy second loop
st r4, 497
st r5, 496
st r6, 495
st r7, 494
st r8, 493
st r9, 492

# live at least once
or r3, r3, r3
st 	r10, 6
live %500
lfork %460

# set a trap before third loop
st r11, 500
st r12, 499
st r13, 498
st r14, 497
st r15, 496

# copy third loop
st r4, 497
st r5, 496
st r6, 495
st r7, 494
st r8, 493
st r9, 492

# live at least once
or r3, r3, r3
st 	r10, 6
live %500
lfork %460

# set a trap before 4 loop
st r11, 500
st r12, 499
st r13, 498
st r14, 497
st r15, 496

# copy 4 loop
st r4, 497
st r5, 496
st r6, 495
st r7, 494
st r8, 493
st r9, 492

# live at least once
or r3, r3, r3
st 	r10, 6
live %500
lfork %460

# set a trap before 5 loop
st r11, 500
st r12, 499
st r13, 498
st r14, 497
st r15, 496

# copy 5 loop
st r4, 497
st r5, 496
st r6, 495
st r7, 494
st r8, 493
st r9, 492

# live at least once
or r3, r3, r3
st 	r10, 6
live %500
lfork %460

# set a random trap1  in our used ocets
st r11, -404
st r12, -405
st r13, -406
st r14, -407
st r15, -408

# set a random trap2  in our used ocets
st r11, -304
st r12, -305
st r13, -306
st r14, -307
st r15, -308

# set a random trap3  in our used ocets
st r11, -204
st r12, -205
st r13, -206
st r14, -207
st r15, -208

# set a random trap4  in our used ocets
st r11, -104
st r12, -105
st r13, -106
st r14, -107
st r15, -108

# live at least once
or r3, r3, r3
st 	r10, 6
live %500
zjmp %40


# our loop code
# our trap code I suddenly erased ;(

#st 	r10, 6
#run1:
#	live %500
#st r10, -4
#or r3, r3, r3
#zjmp %:run1

