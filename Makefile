repl-build.out: property-tracker_template.c
	gcc -o $@ $^

.PHONY: run
run: repl-build.out input1.txt input2.txt
	./$^

.PHONY: clean

clean:
	rm -f repl-build.out