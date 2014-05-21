all: mainone maintwo mainthree mainfour mainfive mainsix mainseven maineight mainnine mainten maineleven maintwelve

mainone: mainone.c
	gcc -g mainone.c mymalloc.h mymalloc.c -o mainone

maintwo: maintwo.c
	gcc -g maintwo.c mymalloc.h mymalloc.c -o maintwo

mainthree: mainthree.c
	gcc -g mainthree.c mymalloc.h mymalloc.c -o mainthree

mainfour: mainfour.c
	gcc -g mainfour.c mymalloc.h mymalloc.c -o mainfour

mainfive: mainfive.c
	gcc -g mainfive.c mymalloc.h mymalloc.c -o mainfive
	
mainsix: mainsix.c
	gcc -g mainsix.c mymalloc.h mymalloc.c -o mainsix

mainseven: mainseven.c
	gcc -g mainseven.c mymalloc.h mymalloc.c -o mainseven

maineight: maineight.c
	gcc -g maineight.c mymalloc.h mymalloc.c -o maineight

mainnine: mainnine.c
	gcc -g mainnine.c mymalloc.h mymalloc.c -o mainnine

mainten: mainten.c
	gcc -g mainten.c mymalloc.h mymalloc.c -o mainten

maineleven: maineleven.c
	gcc -g maineleven.c mymalloc.h mymalloc.c -o maineleven

maintwelve: maintwelve.c
	gcc -g maintwelve.c mymalloc.h mymalloc.c -o maintwelve
	
clean:
	rm -rf *o mainone maintwo mainthree mainfour mainfive mainsix mainseven maineight mainnine mainten maineleven maintwelve