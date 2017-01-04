all: data tree search
	
data: gen_data.c
	gcc gen_data.c -o gen_data
tree: gen_tree.c
	gcc gen_tree.c -o gen_tree
search: search.c
	gcc search.c -o search
clean:
	