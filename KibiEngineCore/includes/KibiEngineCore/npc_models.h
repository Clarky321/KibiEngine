#pragma once

#include <external\vox_loader.h>
#include <raylib.h>
#include <vector>
#include <string>

namespace KibiEngine
{

    // Класс для загрузки и хранения воксельной модели
    class VoxModel
    {
    public:
        VoxModel(const std::string& filePath);
        ~VoxModel();

        void Draw(Vector3 position, float scale = 1.0f, Color tint = WHITE) const;
        BoundingBox GetBoundingBox(Vector3 position, float scale = 1.0f) const;

    private:
        VoxArray3D m_voxArray;
        Mesh m_mesh;
        Material m_material;
    };

    // Класс для объектов, использующих VoxModel
    class VoxObject
    {
    public:
        VoxObject(const VoxModel* model, Vector3 position, float scale = 1.0f);

        void Draw() const;
        bool CheckCollision(const BoundingBox& other) const;

        BoundingBox GetBoundingBox() const;

        Vector3 position;
        float scale;

    private:
        const VoxModel* m_model;
    };
}