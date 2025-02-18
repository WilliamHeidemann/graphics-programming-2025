#version 330 core

layout (location = 0) in vec2 ParticlePosition;
// (todo) 02.X: Add more vertex attributes
layout (location = 1) in float Size;
layout (location = 2) in float Birth;
layout (location = 3) in float Duration;

// (todo) 02.5: Add Color output variable here


// (todo) 02.X: Add uniforms
uniform float CurrentTime;

void main()
{
	gl_Position = vec4(ParticlePosition, 0.0, 1.0);
	float lifeTime = CurrentTime - Birth;
	float lifeTimeSize = 1.0 - lifeTime / Duration;
	float adjustedSize = max(0, lifeTimeSize);
	gl_PointSize = adjustedSize * 100.0;
}
