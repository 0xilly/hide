NAME 	= hide
MAJOR 	= 0
MINOR 	= 0
VERSION = $(MAJOR).$(MINOR)
INCLUDE = include
LIBHIDE = -Ilibhide
SRC 	= $(shell find src/ -type f -name '*.cc')
LIBS 	= $(shell pkg-config --libs tree-sitter luajit vulkan shaderc xcb x11)
OUT=bin

build: compile

compile: prep
	$(CXX) -o ${OUT}/$(NAME) $(SRC) -I$(INCLUDE) $(LIBHIDE) $(LIBS) -g

prep:
	mkdir -p $(OUT)

clean:
	rm -rf $(OUT)
