source_dir = src
build_dir  = build

cc = g++

name = rpg

macflags = -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib 
flags = -lsfml-graphics -lsfml-window -lsfml-system

build_program:
	@mkdir -p $(build_dir) && $(cc) $(flags) $(source_dir)/*.cpp -o $(build_dir)/$(name)

mac:
	@mkdir -p $(build_dir) && $(cc) $(macflags) $(flags) $(source_dir)/*.cpp -o $(build_dir)/$(name)

run:
	@./$(build_dir)/$(name)

clean:
	rm -rf $(build_dir)
