all: data tree search
	
data: gen_data.c define.h
	gcc gen_data.c -O2 -o gen_data
tree: gen_tree.c define.h
	gcc gen_tree.c -O2 -o gen_tree
search: search.c define.h
	gcc search.c   -O2 -o search
clean:
	rm doc/*
	rm *.txt
