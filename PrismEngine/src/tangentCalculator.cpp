#include "tangentCalculator.h"

void prism::PGC::L3::TangentCalculator::generateTangents(Vertex* verticesBegin, size_t verticesCount, uint32_t* indicesBegin, size_t indicesCount)
{
    if (!verticesCount || !indicesCount) return;
    if (indicesCount % 3 != 0) {
        throw std::invalid_argument("Index buffer must contain triangulated faces (size % 3 == 0)");
    }

    MikkTSpaceData data{ verticesBegin, verticesCount, indicesBegin, indicesCount };

    SMikkTSpaceInterface iface{};
    iface.m_getNumFaces = getNumFaces;
    iface.m_getNumVerticesOfFace = getNumVertsOfFace;
    iface.m_getPosition = getPosition;
    iface.m_getNormal = getNormal;
    iface.m_getTexCoord = getTexCoord;
    iface.m_setTSpaceBasic = setTSpaceBasic;

    SMikkTSpaceContext ctx{};
    ctx.m_pInterface = &iface;
    ctx.m_pUserData = &data;

    if (!genTangSpaceDefault(&ctx)) {
        throw std::runtime_error("MikkTSpace: tangent generation failed");
    }
}

int prism::PGC::L3::TangentCalculator::getNumFaces(const SMikkTSpaceContext* pCtx)
{
    auto* mesh = static_cast<MikkTSpaceData*>(pCtx->m_pUserData);
    return static_cast<int>(mesh->indicesCount / 3);
}

int prism::PGC::L3::TangentCalculator::getNumVertsOfFace(const SMikkTSpaceContext*, int)
{
    return 3;
}

void prism::PGC::L3::TangentCalculator::getPosition(const SMikkTSpaceContext* pCtx, float fvPosOut[], int iFace, int iVert)
{
    auto* mesh = static_cast<MikkTSpaceData*>(pCtx->m_pUserData);
    int idx = mesh->indicesBegin[iFace * 3 + iVert];
    fvPosOut[0] = mesh->verticesBegin[idx].pos[0];
    fvPosOut[1] = mesh->verticesBegin[idx].pos[1];
    fvPosOut[2] = mesh->verticesBegin[idx].pos[2];
}

void prism::PGC::L3::TangentCalculator::getNormal(const SMikkTSpaceContext* pCtx, float fvNormOut[], int iFace, int iVert)
{
    auto* mesh = static_cast<MikkTSpaceData*>(pCtx->m_pUserData);
    int idx = mesh->indicesBegin[iFace * 3 + iVert];
    fvNormOut[0] = mesh->verticesBegin[idx].normal[0];
    fvNormOut[1] = mesh->verticesBegin[idx].normal[1];
    fvNormOut[2] = mesh->verticesBegin[idx].normal[2];
}

void prism::PGC::L3::TangentCalculator::getTexCoord(const SMikkTSpaceContext* pCtx, float fvTexcOut[], int iFace, int iVert)
{
    auto* mesh = static_cast<MikkTSpaceData*>(pCtx->m_pUserData);
    int idx = mesh->indicesBegin[iFace * 3 + iVert];
    fvTexcOut[0] = mesh->verticesBegin[idx].texCoord[0];
    fvTexcOut[1] = mesh->verticesBegin[idx].texCoord[1];
}

void prism::PGC::L3::TangentCalculator::setTSpaceBasic(const SMikkTSpaceContext* pCtx, const float fvTangent[], const float fSign, int iFace, int iVert)
{
    auto* mesh = static_cast<MikkTSpaceData*>(pCtx->m_pUserData);
    int idx = mesh->indicesBegin[iFace * 3 + iVert];
    mesh->verticesBegin[idx].tangent[0] = fvTangent[0];
    mesh->verticesBegin[idx].tangent[1] = fvTangent[1];
    mesh->verticesBegin[idx].tangent[2] = fvTangent[2];
    mesh->verticesBegin[idx].tangent[3] = fSign;
}
