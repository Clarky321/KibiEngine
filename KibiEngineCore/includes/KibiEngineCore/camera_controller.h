/*
#pragma once

#include <raylib.h>
#include <KibiEngineCore\character.h>

namespace KibiEngine
{
	class CameraController
	{
	public:
		CameraController(const Character& character);
		Camera3D GetCamera() const;
		void Update();

	private:
		const Character& m_character;
		Camera3D m_camera;

		void UpdateIsometricView();
	};
}
*/

/*
#pragma once

#include <raylib.h>

namespace KibiEngine
{
    class CameraController
    {
    public:
        CameraController(int worldSize);
        Camera3D GetCamera() const;
        void Update();

    private:
        Camera3D m_camera;
        Vector3 m_focusPoint;      // ����� ����������� (����� ����)
        float m_distance = 30.0f;  // ��������� �� ������ �� ����
        float m_angle = 40.0f;     // ���� ������� ������ (� ��������)
        float m_zoomSpeed = 2.0f;
        int m_worldSize;
    };
}
*/

#pragma once

#include <raylib.h>

namespace KibiEngine
{
    class CameraController
    {
    public:
        CameraController(int worldSize);
        Camera3D GetCamera() const;
        void Update();

    private:
        Camera3D m_camera;
        Vector3 m_focusPoint;      // ����� ����
        float m_distance = 30.0f;  // ��������� �� ����
        float m_yaw = 45.0f;       // ���� �������� �� ����������� (�������)
        float m_pitch = 30.0f;     // ���� ������� (�������)
        float m_zoomSpeed = 2.0f;
        float m_rotateSpeed = 50.0f;
        int m_worldSize;

        void UpdateCameraPosition();
    };
}