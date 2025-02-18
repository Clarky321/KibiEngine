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

        // Изометрическая проекция с правильным смещением
        m_camera.position = Vector3Add(playerPos, { 10.0f, 20.0f, 10.0f });
        m_camera.target = playerPos;

        // Настройка проекции
        m_camera.fovy = 50.0f;
        m_camera.projection = CAMERA_PERSPECTIVE;
    }

    Camera3D CameraController::GetCamera() const
    {
        return m_camera;
    }
}