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

        // Изометрическая проекция с углом 45 градусов
        m_camera.position = Vector3Add(playerPos, { 10.0f, 10.0f, 10.0f });
        m_camera.target = playerPos;

        // Фиксируем поворот камеры
        m_camera.up = { 0.0f, 1.0f, 0.0f };
    }

    Camera3D CameraController::GetCamera() const
    {
        return m_camera;
    }
}

/*
#include <KibiEngineCore\camera_controller.h>
#include <raymath.h>

namespace KibiEngine
{
    CameraController::CameraController(Vector3 position, float speed, float sensitivity)
        : m_movementSpeed(speed), m_mouseSensitivity(sensitivity)
    {
        m_camera = {
            m_camera.position = position,
            m_camera.target = Vector3Add(position, Vector3{1.0f, 0.0f, 0.0f}),
            m_camera.up = {0.0f, 1.0f, 0.0f},
            m_camera.fovy = 60.0f,
            m_camera.projection = CAMERA_PERSPECTIVE
        };
    }

    Camera3D CameraController::GetCamera() const
    {
        return m_camera;
    }

    void CameraController::Update()
    {
        Vector2 mouseDelta = GetMouseDelta();

        m_camera.target.x += mouseDelta.x * m_mouseSensitivity;
        m_camera.target.y -= mouseDelta.y * m_mouseSensitivity;

        Vector3 forward = Vector3Normalize(Vector3Subtract(m_camera.target, m_camera.position));
        Vector3 right = Vector3CrossProduct(forward, { 0.0f, 1.0f, 0.0f });

        if (IsKeyDown(KEY_W)) m_camera.position = Vector3Add(m_camera.position, Vector3Scale(forward, m_movementSpeed));
        if (IsKeyDown(KEY_S)) m_camera.position = Vector3Subtract(m_camera.position, Vector3Scale(forward, m_movementSpeed));
        if (IsKeyDown(KEY_A)) m_camera.position = Vector3Subtract(m_camera.position, Vector3Scale(right, m_movementSpeed));
        if (IsKeyDown(KEY_D)) m_camera.position = Vector3Add(m_camera.position, Vector3Scale(right, m_movementSpeed));

        m_camera.target = Vector3Add(m_camera.position, forward);
    }
}
*/