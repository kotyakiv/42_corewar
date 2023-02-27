.name "tester"
.comment "simple test process behavior"

ld %1, r2
ld %180, r4
ld %20, r3
fork %80
ld %10, r5
live %1
fork %10
live %2
