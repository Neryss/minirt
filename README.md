# minirt
42minirt

## Scene

The scene must be declared in a special `.rt` file and must follow the following rules :

### Resoution

Resolution must me declared once, it will fit the maximum screen resolution if launched in a window.

Usage :
| "R" | x<0,16384> | y<0,16384> |
| --- | ---------- | ---------- |

Example :
```
R	1920	1080
```

### Ambiant light

Only one must be declared, if none is declared, a default black light will be used instead.

Usage :
| "A" | Intensity [-1,1] | RGB <r,g,b> [0,255] |
| --- | ---------------- | ------------------- |

Example :
```
A	0,2	255,255,255
```

### Cameras

As many cameras can be declared, at least one must exist. If used with the `--save` argument, the first camera will be used.

Usage :

| "C" | Position <x,y,z> | Rotation <x,y,z> [-1,1] | FOV [0,180] |
| --- | ---------------- | ----------------------- | ----------- |

Example :
```
C	-25,0.5,10.9	0,0,1	80
```

### Lights

As many lights can be declared.

Usage :

| "l" | Position <x,y,z> | Intenisity [0,1] | RGB <r,g,b> [0,255] |
| --- | ---------------- | ---------------  | ------------------- |

Example :
```
l	-30,10,2.5	0.8	100,255,0
```

### Spheres

Usage :

| "sp" | Position <x,y,z> | Diameter | RGB <r,g,b> [0,255] |
| ---- | ---------------- | -------- | ------------------- |

Example :
```
sp	0,4,10	2.5	255,0,255
```

### Planes

Usage :

| "pl" | Position <x,y,z> | Rotation <x,y,z> [-1,1] | RGB <r,g,b> [0,255] |
| ---- | ----------------- | ---------------------- | ------------------- |

Example :

```
pl	10,4,15	0,1,0	255,255,255
```
### Cylinders

Usage :

| "cy" | Position <x,y,z> | Rotation <x,y,z> [-1,1] | Diameter | Height | RGB <r,g,b> [0,255] |
| ---- | ---------------- | ----------------------- | -------- | ------ | ------------------- |

Example :
```
cy 10,0.5,15	1,0,0	2.6	7.9	255,255,255
```

### Squares

Usage :

| "sq" | Position <x,y,z> | Rotation <x,y,z> [-1,1] | Size | RGB <r,g,b> [0,255] |
| ---- | ---------------- | ----------------------- | ---- | ------------------- |

Example :
```
sq	5,0,4.5	0,0,1	5	100,100,100
```

### Triangles

| "tr" | P1 <x,y,z> | P2 <x,y,z> | P3 <x,y,z> | RGB <r,g,b> [0,255] |
| ---- | ---------- | -----------| ---------- | ------------------- |

Example :
```
tr	-15,4,0	-15,0,-4	0,2,-2	255,255,255
```