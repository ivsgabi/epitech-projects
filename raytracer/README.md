# Raytracer

## Create a scene

To create a scene, create a configuration file (file with the .cfg extension), following this template:

```
# Configuration of the camera
camera:
{
    resolution = { width = 1920; height = 1080; };
    position = { x = 0; y = 0; z = 0; };
    rotation = { x = 0; y = 0; z = 0; };
    fieldOfView = 72.0; # In degree
};

# Primitives in the scene
primitives:
{
    # List of spheres
    spheres = (
        { x = 0; y = 0; z = -1; r = 0.5; color = { r = 198; g = 233; b = 249 }; offset = { x = 0; y = 1; z = 0; };}
    );

    # List of planes
    planes = (
        { point = { x = 0; y = 0; z = 0; }; normal = { x = 0; y = 1; z = 1; }; color = { r = 64; g = 64; b = 255; }; }
    );
};

# Light configuration
lights:
{
    ambient = 0.4; # Multiplier of ambient light
    diffuse = 0.6; # Multiplier of diffuse light

    # List of point lights
    point = (
        { x = 400; y = 100; z = 500; },
        { x = -200; y = 300; z = -100; }
    );

    # List of directional lights
    directional = (
        { x = 1; y = 0; z = 0; },
        { x = 0; y = 1; z = 0; }
    );
};
```

You can add the offset field to primitives, point lights and directional lights.

## Contribute to the project

The project uses plugins which means that you can add new features, such as primitives or transformations, without completely rewriting the code.

Theses plugins are dynamic libraries (.so), that the program load at runtime.

Currently, the plugins systems is used for primitives and lights.

### Add new primitives

To add new primitives, first you will need to write your source code. Check out the include/Primitives/IPrimitive.hpp file to see how primitives are implemented.

Then you will need to compile your source code into a shared library (.so file).
Go to the PluginsMakefile (which is the Makefile that compiles the plugins), and add a new rule.

Example: you want to implement the torus primitive.

```
TORUS_SRC=src/Primitives/Torus.cpp \
			src/Math/Point3D.cpp \
			src/Math/Vector3D.cpp \
			src/RayTracer/Ray.cpp \
			src/RayTracer/HitRecord.cpp \
			src/VisualComp/Color.cpp \
			src/Primitives/APrimitive.cpp \
			src/Transformations/Translation.cpp

TORUS_OBJ=$(TORUS_SRC:.cpp=.o)
```

```
primitives: sphere
primitives: plane
primitives: torus

torus: $(TORUS_OBJ)
	$(CXX) $(LIB_FLAG) -o plugins/transformations/libtorus.so $(TORUS_OBJ)

```


#### Compilation

Then, you will need to add your new primitive into the include/Factories/PrimitiveFactory.hpp. Simple as that.
