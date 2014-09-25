FLAGS := -lglut -lGL -lGLU -lGLEW -Wall -lIL -lILU -lILUT -L. -lm -lpthread -lassimp -lfreetype -lz -lpng12
CPP_FILES := $(wildcard *.cpp) 
OBJ_FILES := $(patsubst %.cpp,obj/%.o,$(CPP_FILES))
INC = -I../common -I/usr/include/freetype2 -I/usr/local/include/freetype2 -Idata

all: main.bin

release: FLAGS += -O2
release: main.bin

debug: FLAGS += -g -Wextra
debug: main.bin

main.bin: $(OBJ_FILES) obj/utils.o obj/VAO.o obj/ShaderProgram.o obj/Model.o obj/Example.o obj/Home.o obj/TextRenderer.o obj/SurfaceDistance.o obj/TerrainEdge.o obj/TerrainDistance.o obj/ModelPhong.o obj/ModelSilhouette.o obj/CurveCurvature.o obj/FieldDistance.o obj/TessDemo.o obj/SurfaceCurvature.o obj/ZFight.o
	g++ -o $@ $^ $(FLAGS) $(INC) 

obj/%.o: %.cpp
	g++ -c -o $@ $< $(FLAGS) $(INC) 

obj/utils.o: ../common/utils.cpp ../common/utils.h
	g++ -c ../common/utils.cpp -o $@ $(FLAGS) $(INC) 
obj/VAO.o: ../common/VAO.cpp ../common/VAO.h
	g++ -c ../common/VAO.cpp -o $@ $(FLAGS) $(INC) 
obj/ShaderProgram.o: ../common/ShaderProgram.cpp ../common/ShaderProgram.h
	g++ -c ../common/ShaderProgram.cpp -o $@ $(FLAGS) $(INC) 
obj/Model.o: ../common/Model.cpp ../common/Model.h
	g++ -c ../common/Model.cpp -o $@ $(FLAGS) $(INC) 
obj/Example.o: ../common/Example.cpp ../common/Example.h
	g++ -c ../common/Example.cpp -o $@ $(FLAGS) $(INC) 
obj/Home.o: Home.cpp Home.h
	g++ -c Home.cpp -o $@ $(FLAGS) $(INC) 
obj/TextRenderer.o: ../common/TextRenderer.cpp ../common/TextRenderer.h
	g++ -c ../common/TextRenderer.cpp -o $@ $(FLAGS) $(INC) 
obj/SurfaceDistance.o: SurfaceDistance.cpp SurfaceDistance.h
	g++ -c SurfaceDistance.cpp -o $@ $(FLAGS) $(INC) 
obj/TerrainEdge.o: TerrainEdge.cpp TerrainEdge.h
	g++ -c TerrainEdge.cpp -o $@ $(FLAGS) $(INC) 
obj/TerrainDistance.o: TerrainDistance.cpp TerrainDistance.h
	g++ -c TerrainDistance.cpp -o $@ $(FLAGS) $(INC) 
obj/ModelPhong.o: ModelPhong.cpp ModelPhong.h
	g++ -c ModelPhong.cpp -o $@ $(FLAGS) $(INC) 
obj/ModelSilhouette.o: ModelSilhouette.cpp ModelSilhouette.h
	g++ -c ModelSilhouette.cpp -o $@ $(FLAGS) $(INC) 
obj/CurveCurvature.o: CurveCurvature.cpp CurveCurvature.h
	g++ -c CurveCurvature.cpp -o $@ $(FLAGS) $(INC) 
obj/FieldDistance.o: FieldDistance.cpp FieldDistance.h
	g++ -c FieldDistance.cpp -o $@ $(FLAGS) $(INC) 
obj/TessDemo.o: TessDemo.cpp TessDemo.h
	g++ -c TessDemo.cpp -o $@ $(FLAGS) $(INC) 
obj/SurfaceCurvature.o: SurfaceCurvature.cpp SurfaceCurvature.h
	g++ -c SurfaceCurvature.cpp -o $@ $(FLAGS) $(INC) 
obj/ZFight.o: other/ZFight.cpp other/ZFight.h
	g++ -c other/ZFight.cpp -o $@ $(FLAGS) $(INC) 

clean:
	rm -rf obj/*.o main.bin 

