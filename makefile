source_dir = src
build_dir  = build

cc = g++

name = rpg

flags = -lsfml-graphics -lsfml-window -lsfml-system

build_program:
	@mkdir -p $(build_dir) && $(cc) $(flags) $(source_dir)/*.cpp -o $(build_dir)/$(name)

run:
	@./$(build_dir)/$(name)

clean:
	rm -rf $(build_dir)
