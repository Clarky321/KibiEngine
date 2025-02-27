#include <KibiEngineCore\npc_models.h>
#include <rlgl.h>
#include <stdexcept>
#include <raymath.h>

namespace KibiEngine
{

    // VoxModel implementation
    VoxModel::VoxModel(const std::string& filePath)
    {
        int dataSize = 0;
        unsigned char* voxData = LoadFileData(filePath.c_str(), &dataSize);

        if (!voxData)
        {
            throw std::runtime_error("Failed to load VOX file: " + filePath);
        }

        if (Vox_LoadFromMemory(voxData, dataSize, &m_voxArray) != VOX_SUCCESS)
        {
            UnloadFileData(voxData);
            throw std::runtime_error("Failed to parse VOX file: " + filePath);
        }

        // Инициализация меша
        m_mesh = { 0 };
        m_mesh.vertexCount = m_voxArray.vertices.used;
        m_mesh.triangleCount = m_voxArray.indices.used / 3;

        // Вершины
        m_mesh.vertices = (float*)malloc(m_mesh.vertexCount * 3 * sizeof(float));
        if (!m_mesh.vertices)
        {
            Vox_FreeArrays(&m_voxArray);
            UnloadFileData(voxData);
            throw std::runtime_error("Failed to allocate vertices");
        }

        for (int i = 0; i < m_voxArray.vertices.used; i++)
        {
            m_mesh.vertices[i * 3] = m_voxArray.vertices.array[i].x;
            m_mesh.vertices[i * 3 + 1] = m_voxArray.vertices.array[i].y;
            m_mesh.vertices[i * 3 + 2] = m_voxArray.vertices.array[i].z;
        }

        // Цвета
        m_mesh.colors = (unsigned char*)malloc(m_mesh.vertexCount * 4 * sizeof(unsigned char));
        if (!m_mesh.colors)
        {
            free(m_mesh.vertices);
            Vox_FreeArrays(&m_voxArray);
            UnloadFileData(voxData);
            throw std::runtime_error("Failed to allocate colors");
        }

        for (int i = 0; i < m_voxArray.colors.used; i++)
        {
            m_mesh.colors[i * 4] = m_voxArray.colors.array[i].r;
            m_mesh.colors[i * 4 + 1] = m_voxArray.colors.array[i].g;
            m_mesh.colors[i * 4 + 2] = m_voxArray.colors.array[i].b;
            m_mesh.colors[i * 4 + 3] = m_voxArray.colors.array[i].a;
        }

        // Индексы
        m_mesh.indices = (unsigned short*)malloc(m_voxArray.indices.used * sizeof(unsigned short));
        if (!m_mesh.indices)
        {
            free(m_mesh.vertices);
            free(m_mesh.colors);
            Vox_FreeArrays(&m_voxArray);
            UnloadFileData(voxData);
            throw std::runtime_error("Failed to allocate indices");
        }
        memcpy(m_mesh.indices, m_voxArray.indices.array, m_voxArray.indices.used * sizeof(unsigned short));

        // Загрузка меша в VRAM
        UploadMesh(&m_mesh, false);
        // Материал по умолчанию
        m_material = LoadMaterialDefault();
        UnloadFileData(voxData);
    }

    VoxModel::~VoxModel()
    {
        Vox_FreeArrays(&m_voxArray);
        UnloadMesh(m_mesh);
    }

    void VoxModel::Draw(Vector3 position, float scale, Color tint) const {
        Matrix transform = MatrixMultiply(
            MatrixScale(scale, scale, scale),
            MatrixTranslate(position.x, position.y, position.z)
        );
        DrawMesh(m_mesh, m_material, transform);
    }

    BoundingBox VoxModel::GetBoundingBox(Vector3 position, float scale) const
    {
        Vector3 halfSize = { scale * 0.5f, scale * 0.5f, scale * 0.5f };
        return BoundingBox{
            Vector3Subtract(position, halfSize),
            Vector3Add(position, halfSize)
        };
    }

    // VoxObject implementation
    VoxObject::VoxObject(const VoxModel* model, Vector3 pos, float scl)
        : m_model(model), position(pos), scale(scl) {
    }

    void VoxObject::Draw() const
    {
        m_model->Draw(position, scale);
    }

    bool VoxObject::CheckCollision(const BoundingBox& other) const
    {
        BoundingBox thisBox = m_model->GetBoundingBox(position, scale);
        return CheckCollisionBoxes(thisBox, other);
    }

    BoundingBox VoxObject::GetBoundingBox() const
    {
        return m_model->GetBoundingBox(position, scale);
    }
}