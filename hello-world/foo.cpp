#include "Light.h"

#include "Rotation.h"

class FOOA
{
	Engine::FVector3 foadfs;
};


namespace Engine
{
	namespace Graphics
	{
		void foo()
		{
			//Light light(Colors::ALICEBLUE, Colors::ALICEBLUE, Colors::ALICEBLUE);
			//const GameObject* p_light_owner = light.get_owner();

			Rotation rotation;
			Rotation rotation2(0.f, Math::Axis::Z);
			Rotation rotation3(0.f, FVector3::RIGHT);
			/////////////////////////////////////////////Rotation rotation4(FVector3::RIGHT);
			/////////////////////////////////////////////Rotation rotation5(FVector3::RIGHT, FVector3::RIGHT);
			rotation *= rotation;
			rotation * rotation;
			rotation /= rotation;
			rotation / rotation;
			rotation.get_inverse();
			/////////////////////////////////////////////rotation * FVector3::RIGHT;
			rotation == rotation;
			rotation.rotate_over(0.f, Math::Axis::Z);
			/////////////////////////////////////////////rotation.rotate_over(0.f, FVector3::RIGHT);
			/////////////////////////////////////////////rotation.get_euler_angles();
			/////////////////////////////////////////////rotation.get_axis_angle();
			/////////////////////////////////////////////rotation.get_orientation(Math::Axis::Z);
			/////////////////////////////////////////////rotation.get_orientation();
			rotation.get_matrix();

			//static_cast<unsigned>(light.get_type());
			//Math::Angles::degrees_to_radians(light.get_inner_cone_degrees());
			//Math::Angles::degrees_to_radians(light.get_outer_cone_degrees());
			//light.get_attenuation();
			//light.get_ambient();
			//light.get_diffuse();
			//light.get_specular();
		}
	}
}
