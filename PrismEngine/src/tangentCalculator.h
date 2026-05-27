#pragma once
#include "utils.h"
#include "layersMacroses.h"
#include "pgcLayersObjsTemplate.h"
#include "mesh.h"
#include <mikktspace.h>

DECLARE_PGC_LAYER_INSTANCE(L3)

class TangentCalculator {
public:
    static void generateTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

private:
    struct MikkTSpaceData {
        std::vector<Vertex>& vertices;
        std::vector<uint32_t>& indices;
    };

    static int getNumFaces(const SMikkTSpaceContext* pCtx);
    static int getNumVertsOfFace(const SMikkTSpaceContext*, int);
    static void getPosition(const SMikkTSpaceContext* pCtx, float fvPosOut[], int iFace, int iVert);
    static void getNormal(const SMikkTSpaceContext* pCtx, float fvNormOut[], int iFace, int iVert);
    static void getTexCoord(const SMikkTSpaceContext* pCtx, float fvTexcOut[], int iFace, int iVert);
    static void setTSpaceBasic(const SMikkTSpaceContext* pCtx, const float fvTangent[], const float fSign, int iFace, int iVert);
};
END_NAMESPACE_DECLARATION