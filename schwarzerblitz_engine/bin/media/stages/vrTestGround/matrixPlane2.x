xof 0303txt 0032

template XSkinMeshHeader {
  <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
  WORD nMaxSkinWeightsPerVertex;
  WORD nMaxSkinWeightsPerFace;
  WORD nBones;
}

template SkinWeights {
  <6f0d123b-bad2-4167-a0d0-80224f25fabb>
  STRING transformNodeName;
  DWORD nWeights;
  array DWORD vertexIndices[nWeights];
  array float weights[nWeights];
  Matrix4x4 matrixOffset;
}

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000,-1.000000, 0.000000,
     0.000000, 1.000000,-0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Plane1 {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Frame Plane1_Bone {
      FrameTransformMatrix {
         1.000000, 0.000000, 0.000000, 0.000000,
         0.000000, 0.000000, 1.000000, 0.000000,
         0.000000,-1.000000, 0.000000, 0.000000,
         0.000000, 0.000000, 0.000000, 1.000000;;
      }
    } // End of Plane1_Bone
    Frame Plane {
      FrameTransformMatrix {
         8.200602, 0.000000, 0.000000, 0.000000,
         0.000000, 8.200602, 0.000000, 0.000000,
         0.000000, 0.000000, 8.200602, 0.000000,
         0.000000, 0.000000,-1.125329, 1.000000;;
      }
      Mesh { // Plane mesh
        20;
        -1.000000;-1.000000; 0.000000;,
         1.000000;-1.000000; 0.000000;,
         1.000000; 1.000000; 0.000000;,
        -1.000000; 1.000000; 0.000000;,
        -1.000000; 1.000000; 0.000000;,
        -1.015352; 1.015352; 0.021695;,
        -1.015352;-1.015352; 0.021695;,
        -1.000000;-1.000000; 0.000000;,
         1.000000; 1.000000; 0.000000;,
         1.015352; 1.015352; 0.021695;,
        -1.015352; 1.015352; 0.021695;,
        -1.000000; 1.000000; 0.000000;,
        -1.000000;-1.000000; 0.000000;,
        -1.015352;-1.015352; 0.021695;,
         1.015352;-1.015352; 0.021695;,
         1.000000;-1.000000; 0.000000;,
         1.000000;-1.000000; 0.000000;,
         1.015352;-1.015352; 0.021695;,
         1.015352; 1.015352; 0.021695;,
         1.000000; 1.000000; 0.000000;;
        5;
        4;0,1,2,3;,
        4;4,5,6,7;,
        4;8,9,10,11;,
        4;12,13,14,15;,
        4;16,17,18,19;;
        MeshNormals { // Plane normals
          5;
           0.000000; 0.000000; 1.000000;,
           0.816286; 0.000000; 0.577647;,
           0.000000;-0.816286; 0.577647;,
           0.000000; 0.816286; 0.577647;,
          -0.816286; 0.000000; 0.577647;;
          5;
          4;0,0,0,0;,
          4;1,1,1,1;,
          4;2,2,2,2;,
          4;3,3,3,3;,
          4;4,4,4,4;;
        } // End of Plane normals
        MeshTextureCoords { // Plane UV coordinates
          20;
           0.000000; 1.000000;,
           1.000000; 1.000000;,
           1.000000; 0.000000;,
           0.000000; 0.000000;,
           0.000000; 0.000000;,
           0.000000; 0.000000;,
           0.000000; 1.000000;,
           0.000000; 1.000000;,
           1.000000; 0.000000;,
           1.000000; 0.000000;,
           0.000000; 0.000000;,
           0.000000; 0.000000;,
           0.000000; 1.000000;,
           0.000000; 1.000000;,
           1.000000; 1.000000;,
           1.000000; 1.000000;,
           1.000000; 1.000000;,
           1.000000; 1.000000;,
           1.000000; 0.000000;,
           1.000000; 0.000000;;
        } // End of Plane UV coordinates
        MeshMaterialList { // Plane material list
          1;
          5;
          0,
          0,
          0,
          0,
          0;
          Material Plane1 {
             0.640000; 0.640000; 0.640000; 0.000000;;
             96.078431;
             0.500000; 0.500000; 0.500000;;
             0.000000; 0.000000; 0.000000;;
            TextureFilename {"texFixed.png";}
          }
        } // End of Plane material list
        XSkinMeshHeader {
          1;
          3;
          1;
        }
        SkinWeights {
          "Plane1_Bone";
          20;
          0,
          1,
          2,
          3,
          4,
          5,
          6,
          7,
          8,
          9,
          10,
          11,
          12,
          13,
          14,
          15,
          16,
          17,
          18,
          19;
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000,
           1.000000;
           8.200602, 0.000000, 0.000000, 0.000000,
           0.000000, 0.000000,-8.200602, 0.000000,
           0.000000, 8.200602, 0.000000, 0.000000,
           0.000000,-1.125329, 0.000000, 1.000000;;
        } // End of Plane1_Bone skin weights
      } // End of Plane mesh
    } // End of Plane
  } // End of Plane1
} // End of Root
