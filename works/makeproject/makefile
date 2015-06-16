../target/game: game.o debug.o decode.o estimate529.o sendmsg.o
	gcc -o ../target/game game.o debug.o decode.o estimate529.o sendmsg.o
game.o: ../source/game.c ../source/game.h ../source/debug.h ../source/decode.h ../source/estimate.h ../source/sendmsg.h
	gcc -c ../source/game.c
debug.o: ../source/debug.c ../source/game.h ../source/debug.h
	gcc -c ../source/debug.c
decode.o: ../source/decode.c ../source/game.h ../source/decode.h
	gcc -c ../source/decode.c
estimate529.o: ../source/estimate529.c ../source/game.h ../source/estimate.h
	gcc -c ../source/estimate529.c
sendmsg.o: ../source/sendmsg.c ../source/game.h ../source/sendmsg.h
	gcc -c ../source/sendmsg.c
clean:
	rm -f game.o debug.o decode.o estimate529.o sendmsg.o
