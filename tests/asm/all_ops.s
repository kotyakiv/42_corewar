.name "zork"
.comment "I'M ALIIIIVE"

l2:		liv %1

live:	live %1
		zjmp %:live

dead:
