GCC = g++
OPS = -g
LINK_OPS = -lglut -lGL -lGLU -lX11  -lm -L/usr/X11R6/lib
OBJS = main.o Parser.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o ModeloDatos.o Elementos.o GLCamera.o ICP.o TriMesh_io.o KDtree.o TriMesh_normals.o TriMesh_bounding.o TriMesh_connectivity.o TriMesh_curvature.o TriMesh_grid.o TriMesh_pointareas.o TriMesh_stats.o TriMesh_tstrips.o remove.o reorder_verts.o
TEST_OBJS = 

all: $(OBJS) Makefile
	$(GCC) $(OPS) $(LINK_OPS) $(OBJS) -o tron

main.o : main.cpp
	$(GCC) $(OPS) -c main.cpp

Parser.o : Parser.cpp
	$(GCC) $(OPS) -c Parser.cpp

ModeloDatos.o : ModeloDatos.cpp
	$(GCC) $(OPS) -c ModeloDatos.cpp

tinystr.o : tinystr.cpp
	$(GCC) $(OPS) -c tinystr.cpp

tinyxml.o: tinyxml.cpp
	$(GCC) $(OPS) -c tinyxml.cpp

tinyxmlerror.o: tinyxmlerror.cpp
	$(GCC) $(OPS) -c tinyxmlerror.cpp

tinyxmlparser.o: tinyxmlparser.cpp
	$(GCC) $(OPS) -c tinyxmlparser.cpp

Elementos.o: Elementos.cpp
	$(GCC) $(OPS) -c Elementos.cpp

GLCamera.o: GLCamera.cc
	$(GCC) $(OPS) -c GLCamera.cc

ICP.o: ICP.cc
	$(GCC) $(OPS) -c ICP.cc

TriMesh_io.o: TriMesh_io.cc
	$(GCC) $(OPS) -c TriMesh_io.cc

KDtree.o: KDtree.cc
	$(GCC) $(OPS) -c KDtree.cc

TriMesh_normals.o: TriMesh_normals.cc
	$(GCC) $(OPS) -c TriMesh_normals.cc

TriMesh_bounding.o: TriMesh_bounding.cc
	$(GCC) $(OPS) -c TriMesh_bounding.cc

TriMesh_connectivity.o: TriMesh_connectivity.cc
	$(GCC) $(OPS) -c TriMesh_connectivity.cc

TriMesh_curvature.o: TriMesh_curvature.cc
	$(GCC) $(OPS) -c TriMesh_curvature.cc

TriMesh_grid.o: TriMesh_grid.cc
	$(GCC) $(OPS) -c TriMesh_grid.cc

TriMesh_pointareas.o: TriMesh_pointareas.cc
	$(GCC) $(OPS) -c TriMesh_pointareas.cc

TriMesh_stats.o: TriMesh_stats.cc
	$(GCC) $(OPS) -c TriMesh_stats.cc

TriMesh_tstrips.o: TriMesh_tstrips.cc
	$(GCC) $(OPS) -c TriMesh_tstrips.cc

remove.o: remove.cc
	$(GCC) $(OPS) -c remove.cc

reorder_verts.o: reorder_verts.cc
	$(GCC) $(OPS) -c reorder_verts.cc

clean:
	rm -rf tron test .\#* \#* *.o .*~ *~ *.gch semantic.cache
