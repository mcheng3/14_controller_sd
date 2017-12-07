control: control.c
	gcc control.c -o control

run: control
	./control