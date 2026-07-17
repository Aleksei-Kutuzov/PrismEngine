#include "assetSpec.h"

bool prism::PGC::MeshTransform::operator==(const MeshTransform& other) const
{
	return position == other.position && rotation == other.rotation && scale == other.scale;
}

bool prism::PGC::MeshTransform::operator!=(const MeshTransform& other) const
{
	return !operator==(other);
}

bool prism::assets::TexturePath::operator==(const TexturePath& other) const
{
	return path == other.path && type == other.type;
}

bool prism::assets::TextureColor::operator==(const TextureColor& other) const
{
	return color == other.color && type == other.type;
}

bool prism::assets::MeshPath::operator==(const MeshPath& other) const
{
	return path == other.path && linkName == other.linkName && transform == other.transform;
}

bool prism::assets::MeshPath::onlyTransformDiff(const MeshPath& other) const
{
	return path == other.path && linkName == other.linkName && transform != other.transform;
}

bool prism::assets::MeshCube::operator==(const MeshCube& other) const
{
	return transform == other.transform;
}

bool prism::assets::MeshCube::onlyTransformDiff(const MeshCube& other) const
{
	return transform != other.transform;;
}

bool prism::assets::MeshPlane::operator==(const MeshPlane& other) const
{
	return transform == other.transform;
}

bool prism::assets::MeshPlane::onlyTransformDiff(const MeshPlane& other) const
{
	return transform != other.transform;
}

bool prism::assets::MeshGrid::operator==(const MeshGrid& other) const
{
	return subdivisionsX == other.subdivisionsX &&
		subdivisionsZ == other.subdivisionsZ &&
		repeatTextureX == other.repeatTextureX &&
		repeatTextureZ == other.repeatTextureZ &&
		transform == other.transform;
}

bool prism::assets::MeshGrid::onlyTransformDiff(const MeshGrid& other) const
{
	return subdivisionsX == other.subdivisionsX &&
		subdivisionsZ == other.subdivisionsZ &&
		repeatTextureX == other.repeatTextureX &&
		repeatTextureZ == other.repeatTextureZ &&
		transform != other.transform;
}

bool prism::assets::MeshIcoSphere::operator==(const MeshIcoSphere& other) const
{
	return subdivisions == other.subdivisions && transform == other.transform;
}

bool prism::assets::MeshIcoSphere::onlyTransformDiff(const MeshIcoSphere& other) const
{
	return subdivisions == other.subdivisions && transform != other.transform;
}

bool prism::assets::MeshUvSphere::operator==(const MeshUvSphere& other) const
{
	return subdivisionsVert == other.subdivisionsVert && subdivisionsHoriz == other.subdivisionsHoriz &&
		transform == other.transform;
}

bool prism::assets::MeshUvSphere::onlyTransformDiff(const MeshUvSphere& other) const
{
	return subdivisionsVert == other.subdivisionsVert && subdivisionsHoriz == other.subdivisionsHoriz &&
		transform != other.transform;
}
