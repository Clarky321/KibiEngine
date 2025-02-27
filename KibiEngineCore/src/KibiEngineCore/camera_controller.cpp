/*
#include <KibiEngineCore\camera_controller.h>
#include <raymath.h>

namespace KibiEngine
{
    CameraController::CameraController(const Character& character) :
        m_character(character)
    {
        m_camera.position = { 0.0f, 20.0f, 10.0f };
        m_camera.target = { 0.0f, 0.0f, 0.0f };
        m_camera.up = { 0.0f, 1.0f, 0.0f };
        m_camera.fovy = 15.0f;
        m_camera.projection = CAMERA_ORTHOGRAPHIC;
    }

    void CameraController::Update()
    {
        UpdateIsometricView();
    }

    void CameraController::UpdateIsometricView()
    {
        Vector3 playerPos = m_character.GetPosition();

        m_camera.position = Vector3Add(playerPos, { 10.0f, 20.0f, 10.0f });
        m_camera.target = playerPos;

        m_camera.fovy = 50.0f;
        m_camera.projection = CAMERA_PERSPECTIVE;
    }

    Camera3D CameraController::GetCamera() const
    {
        return m_camera;
    }
}
*/

/*
#include <KibiEngineCore\camera_controller.h>
#include <raymath.h>

namespace KibiEngine {
    CameraController::CameraController(int worldSize)
        : m_worldSize(worldSize)
    {
        // Центр мира (предполагаем, что блоки от 0 до m_worldSize-1)
        m_focusPoint = {
            m_worldSize / 2.0f - 0.5f,
            0.0f,
            m_worldSize / 2.0f - 0.5f
        };

        // Начальные настройки камеры
        m_camera.position = Vector3Add(m_focusPoint, { 20.0f, 30.0f, 20.0f });
        m_camera.target = m_focusPoint;
        m_camera.up = { 0.0f, 1.0f, 0.0f };
        m_camera.fovy = 25.0f;
        m_camera.projection = CAMERA_ORTHOGRAPHIC;
    }

    void CameraController::Update() {
        // Управление зумом колесом мыши
        m_distance -= GetMouseWheelMove() * m_zoomSpeed;
        m_distance = Clamp(m_distance, 10.0f, 50.0f);

        // Управление перемещением камеры
        if (IsKeyDown(KEY_W)) m_focusPoint.z -= 0.5f;
        if (IsKeyDown(KEY_S)) m_focusPoint.z += 0.5f;
        if (IsKeyDown(KEY_A)) m_focusPoint.x -= 0.5f;
        if (IsKeyDown(KEY_D)) m_focusPoint.x += 0.5f;

        // Ограничение движения камеры в пределах мира
        m_focusPoint.x = Clamp(m_focusPoint.x, 0.0f, m_worldSize - 1.0f);
        m_focusPoint.z = Clamp(m_focusPoint.z, 0.0f, m_worldSize - 1.0f);

        // Пересчет позиции камеры
        Vector3 offset = {
            m_distance * cosf(DEG2RAD * m_angle),
            m_distance * sinf(DEG2RAD * m_angle),
            m_distance * cosf(DEG2RAD * m_angle)
        };

        m_camera.position = Vector3Add(m_focusPoint, offset);
        m_camera.target = m_focusPoint;
    }

    Camera3D CameraController::GetCamera() const {
        return m_camera;
    }
}
*/

#include <KibiEngineCore/camera_controller.h>
#include <raymath.h>

namespace KibiEngine {
    CameraController::CameraController(int worldSize)
        : m_worldSize(worldSize)
    {
        m_focusPoint = {
            m_worldSize / 2.0f - 0.5f,
            0.0f,
            m_worldSize / 2.0f - 0.5f
        };

        UpdateCameraPosition();

        m_camera.up = { 0.0f, 1.0f, 0.0f };
        m_camera.fovy = 45.0f;
        m_camera.projection = CAMERA_PERSPECTIVE;
    }

    void CameraController::Update() {
        // Зум колёсиком
        m_distance -= GetMouseWheelMove() * m_zoomSpeed;
        m_distance = Clamp(m_distance, 10.0f, 50.0f);

        // Управление перемещением камеры
        if (IsKeyDown(KEY_W)) m_focusPoint.z -= 0.5f;
        if (IsKeyDown(KEY_S)) m_focusPoint.z += 0.5f;
        if (IsKeyDown(KEY_A)) m_focusPoint.x -= 0.5f;
        if (IsKeyDown(KEY_D)) m_focusPoint.x += 0.5f;

        // Ограничение движения камеры в пределах мира
        m_focusPoint.x = Clamp(m_focusPoint.x, 0.0f, m_worldSize - 1.0f);
        m_focusPoint.z = Clamp(m_focusPoint.z, 0.0f, m_worldSize - 1.0f);

        // Вращение Q/E
        if (IsKeyDown(KEY_Q)) m_yaw -= m_rotateSpeed * GetFrameTime();
        if (IsKeyDown(KEY_E)) m_yaw += m_rotateSpeed * GetFrameTime();

        // Обновляем позицию камеры
        UpdateCameraPosition();
    }

    void CameraController::UpdateCameraPosition() {
        // Переводим углы в радианы
        float yawRad = DEG2RAD * m_yaw;
        float pitchRad = DEG2RAD * m_pitch;

        // Сферические координаты → декартовы
        Vector3 offset = {
            m_distance * cosf(yawRad) * cosf(pitchRad),
            m_distance * sinf(pitchRad),
            m_distance * sinf(yawRad) * cosf(pitchRad)
        };

        m_camera.position = Vector3Add(m_focusPoint, offset);
        m_camera.target = m_focusPoint;
    }

    Camera3D CameraController::GetCamera() const {
        return m_camera;
    }
}