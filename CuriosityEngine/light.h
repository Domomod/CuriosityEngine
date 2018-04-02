#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define MAX_LIGHTS 64

enum
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT
};

class Light {
public:
	Light(int type, glm::vec3 posdir, float constantAtt, float linearAtt,
		float quadraticAtt, glm::vec3 color, float ambientCoefficient)
    {
		this->m_type = type;
		this->m_posdir= posdir;
		this->m_attunation = glm::vec3(constantAtt, linearAtt, quadraticAtt);
		this->m_color = color;
		this->m_ambientCoefficient = ambientCoefficient;
    }
    ~Light();

	float CalcPointLightBSphere()
	{
		float col = 1.0f; // fmax(fmax(m_color.r, m_color.g), m_color.b);
		float lin = m_attunation.x;
		float con = m_attunation.y;
		float exp = m_attunation.z;

		float ret = (-lin + sqrt(lin*lin - 4 * exp 
			* (con - 256.0f * col))) / /* 2.0f * */ exp;

		return 2.0f * ret;
	}

	int m_type;
	glm::vec3 m_posdir;
	glm::vec3 m_attunation;
	glm::vec3 m_color;
	float m_ambientCoefficient;
};

#endif // LIGHT_H
