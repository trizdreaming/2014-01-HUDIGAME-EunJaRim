xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


Frame Box001 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh {
  45;
  5.000000;5.000000;0.000000;,
  -15.000000;-5.000000;0.000000;,
  15.000000;-5.000000;0.000000;,
  -5.000000;5.000000;0.000000;,
  5.000000;5.000000;-10.000000;,
  -15.000000;-5.000000;-10.000000;,
  -5.000000;5.000000;-10.000000;,
  15.000000;-5.000000;-10.000000;,
  15.000000;-5.000000;-10.000000;,
  -15.000000;-5.000000;0.000000;,
  -15.000000;-5.000000;-10.000000;,
  15.000000;-5.000000;0.000000;,
  15.000000;5.000000;-10.000000;,
  15.000000;-5.000000;-10.000000;,
  15.000000;5.000000;0.000000;,
  -15.000000;-5.000000;-10.000000;,
  -15.000000;5.000000;0.000000;,
  -15.000000;5.000000;-10.000000;,
  -15.000000;-5.000000;0.000000;,
  15.000000;5.000000;0.000000;,
  15.000000;5.000000;-10.000000;,
  5.000000;5.000000;0.000000;,
  15.000000;5.000000;0.000000;,
  -15.000000;5.000000;0.000000;,
  -5.000000;5.000000;0.000000;,
  -15.000000;5.000000;-10.000000;,
  -15.000000;5.000000;0.000000;,
  -5.000000;5.000000;-10.000000;,
  5.000000;5.000000;-10.000000;,
  15.000000;5.000000;-10.000000;,
  5.000000;15.000000;0.000000;,
  -5.000000;5.000000;0.000000;,
  5.000000;5.000000;0.000000;,
  -5.000000;15.000000;0.000000;,
  5.000000;15.000000;-10.000000;,
  -5.000000;5.000000;-10.000000;,
  -5.000000;15.000000;-10.000000;,
  5.000000;5.000000;-10.000000;,
  5.000000;5.000000;-10.000000;,
  5.000000;15.000000;0.000000;,
  -5.000000;15.000000;-10.000000;,
  5.000000;15.000000;0.000000;,
  5.000000;15.000000;-10.000000;,
  -5.000000;15.000000;0.000000;,
  -5.000000;15.000000;0.000000;;
  28;
  3;0,1,2;,
  3;1,0,3;,
  3;4,5,6;,
  3;5,4,7;,
  3;8,9,10;,
  3;9,8,11;,
  3;12,2,13;,
  3;2,12,14;,
  3;15,16,17;,
  3;16,15,18;,
  3;19,20,21;,
  3;22,0,2;,
  3;23,24,25;,
  3;26,1,3;,
  3;25,24,27;,
  3;17,6,5;,
  3;20,28,21;,
  3;29,7,4;,
  3;30,31,32;,
  3;31,30,33;,
  3;34,35,36;,
  3;35,34,37;,
  3;34,32,38;,
  3;32,34,39;,
  3;40,41,42;,
  3;41,40,43;,
  3;6,44,36;,
  3;44,6,31;;

  MeshNormals {
   14;
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;-1.000000;,
   0.000000;-1.000000;0.000000;,
   1.000000;0.000000;0.000000;,
   -1.000000;0.000000;0.000000;,
   0.000000;1.000000;0.000000;,
   1.000000;-0.000000;0.000000;,
   1.000000;0.000000;0.000000;,
   1.000000;-0.000000;0.000000;,
   1.000000;-0.000000;0.000000;,
   -1.000000;-0.000000;-0.000000;,
   -1.000000;-0.000000;0.000000;,
   -1.000000;-0.000000;-0.000000;,
   -1.000000;0.000000;-0.000000;;
   28;
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;2,2,2;,
   3;2,2,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;4,4,4;,
   3;4,4,4;,
   3;5,5,5;,
   3;0,0,0;,
   3;5,5,5;,
   3;0,0,0;,
   3;5,5,5;,
   3;1,1,1;,
   3;5,5,5;,
   3;1,1,1;,
   3;0,0,0;,
   3;0,0,0;,
   3;1,1,1;,
   3;1,1,1;,
   3;6,8,7;,
   3;8,6,9;,
   3;5,5,5;,
   3;5,5,5;,
   3;10,12,11;,
   3;12,10,13;;
  }

  MeshTextureCoords {
   45;
   10.000000;-9.000000;,
   30.000000;1.000000;,
   0.000000;1.000000;,
   20.000000;-9.000000;,
   20.000000;-9.000000;,
   0.000000;1.000000;,
   10.000000;-9.000000;,
   30.000000;1.000000;,
   30.000000;-9.000000;,
   0.000000;1.000000;,
   0.000000;-9.000000;,
   30.000000;1.000000;,
   10.000000;-9.000000;,
   0.000000;-9.000000;,
   10.000000;1.000000;,
   10.000000;-9.000000;,
   0.000000;1.000000;,
   0.000000;-9.000000;,
   10.000000;1.000000;,
   0.000000;1.000000;,
   0.000000;-9.000000;,
   10.000000;1.000000;,
   0.000000;-9.000000;,
   30.000000;1.000000;,
   20.000000;1.000000;,
   30.000000;-9.000000;,
   30.000000;-9.000000;,
   19.999998;-9.000000;,
   9.999999;-9.000000;,
   30.000000;-9.000000;,
   0.000000;-9.000000;,
   10.000000;1.000000;,
   0.000000;1.000000;,
   10.000000;-9.000000;,
   10.000000;-9.000000;,
   0.000000;1.000000;,
   0.000000;-9.000000;,
   10.000000;1.000000;,
   0.000000;-9.000000;,
   10.000000;1.000000;,
   10.000000;-9.000000;,
   0.000000;1.000000;,
   0.000000;-9.000000;,
   10.000000;1.000000;,
   0.000000;1.000000;;
  }

  MeshMaterialList {
   1;
   28;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;

   Material {
    0.588000;0.588000;0.588000;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "Corps_Color.dds";
    }
   }
  }
 }
}